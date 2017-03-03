#include "gstdafx.hpp"
#include "file.hpp"
#include "romtype.hpp"
#include "addressing.hpp"
#include "romfile.hpp"

namespace akmml
{
	const std::array<uint8_t, 13> RomFile::initSpcCode = {
		0x20,		//    clrp
		0xc0,		//    di
		//0xcd, 0xcf,	//    mov   x,#$cf  <- ff4
		0xcd, 0xff,	//    mov   x,#$ff
		0xbd,		//    mov   sp,x
		0xe8, 0x00,	//    mov   a,#0
		0x5d,		//    mov   x,a
		0xaf,		// -  mov   (x)+,a
		//0xc8, 0xe0,	//    cmp   x,#$e0  <- ff4
		0xc8, 0xf0,	//    cmp   x,#$f0
		0xd0, 0xfb,	//    bne   -
	};

	RomFile::RomFile(std::string path) : File(path)
	{
	}

	RomFile::RomFile(RomFile& f) : File(f)
	{
	}

	RomFile::~RomFile()
	{
	}

	bool RomFile::open(std::ios::openmode m)
	{
		if(!m)
		{
			m = std::ios::in | std::ios::binary;
		}

		this->oMode = m;
		return this->_open();
	}

	bool RomFile::checkRomSum(std::ios::pos_type pos)
	{
		uint16_t checksum[2];

		this->stream.seekg(pos, std::ios::beg);
		if(!this->stream.fail())
		{
			this->stream.read((char*)checksum, sizeof(uint16_t)*2);
			if( !this->stream.fail() && (0xffff == (checksum[0] ^ checksum[1])))
			{
				return true;
			}
		}

		stream.clear();
		return false;
	}

	void RomFile::checkType()
	{
		int romLoHi = 0;
		int head = 0;
		size_t romSize;

		// ROMファイルが開けるか
		if(false == this->open())
		{
			// 指定のファイルのオープンに失敗したときは、
			// UnknownROMとします
			this->type = RomType::Unknown;
			return;
		}
		romSize = this->size();
		putdebug("  stream: %s %dbytes", this->sPath.c_str(), romSize);

		// LoRom/HiRom 種別およびヘッダ有無の判定をします
		// ExLoRom / ExHiRomは該当エンジンに対応したゲームないので放置です。
		// ※Romのチェックサムで判断するので、チェックサムが壊れていると
		//   正しく判断できません。
		if(this->checkRomSum(0x7fdc))
		{
			romLoHi--;
			head--;
		}
		if(this->checkRomSum(0x81dc))
		{
			romLoHi--;
			head++;
		}
		if(this->checkRomSum(0xffdc))
		{
			romLoHi++;
			head--;
		}
		if(this->checkRomSum(0x101dc))
		{
			romLoHi++;
			head++;
		}

		// スコアからROM種別判定
		// ヘンなデータの場合はLoRom/NoHeader扱いです
		if(0 < romLoHi)
		{
			this->romMap = RomType::HiRom;
		}
		if(0 < head)
		{
			this->hasHeader = true;
		}
		putdebug("  MEMORY MAP: %s / %s", (this->romMap == RomType::LoRom ? "LoRom" : "HiRom"), (this->hasHeader ? "Include Header" : "No Header"));

		Addressing::SnesAddress snesAdr(this->romMap, this->hasHeader, 0x10000);

		if(snesAdr.getPcAddress() > romSize)
		{
			// ROMサイズが1バンク分にも満たない場合、
			// UnknownRomとします
			this->stream.close();
			this->type = RomType::Unknown;
			return;
		}

		// LoRom / HiRom で、ある程度絞り込む
		switch(this->romMap)
		{
			case RomType::LoRom:
				this->checkLoRomType();
				break;
			case RomType::HiRom:
				this->checkHiRomType();
				break;
			default:
				this->type = RomType::Unknown;
				break;
		}
		this->close();
		return;
	}

	//----------------------------------------------------------
	// LoRom種別判別
	// [ 対象ゲーム ]
	//   - Final Fantasy 4
	//   - Romancing SaGa
	//   - Final Fantasy Mystic Quest
	//   - 半熟英雄
	//----------------------------------------------------------
	void RomFile::checkLoRomType()
	{
		Addressing::SnesAddress snesAdr(this->romMap, this->hasHeader, 0x048000); // bank:4
		std::vector<uint8_t> buffer;

		// バンク4の頭0x4000バイトのデータをバッファに読み出します
		buffer.resize(0x2000);
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );

		// バンク4から、SPC初期化コードを検索します
		auto it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// initSpcCodeの改変なしで発見できた場合は、Romancing SaGa
			// (他にLoRomがなければ)
			this->type = RomType::RomancingSaGa1;
			// TODO: 各種解析
			return;
		}

		// 検索対象をff4用の初期化コードに変更します
		std::array<uint8_t, RomFile::initSpcCode.size()> ff4search(RomFile::initSpcCode);
		ff4search[3] = 0xcf;		// sp = 0xff -> 0xcf
		ff4search[10] = 0xe0;		// clear to 0xf0 -> 0xe0

		// 同じくバンク4から、SPC初期化コードを検索します
		it = std::search(
				buffer.begin(),
				buffer.end(),
				ff4search.begin(),
				ff4search.end()
				);
		if(it != buffer.end())
		{
			// 初期化コードを発見した場合は、FinalFantasy4
			this->type = RomType::FinalFantasy4;
			// TODO: 各種解析
			return;
		}

		// バンク13の頭0x2000バイトのデータをバッファに読み出します
		snesAdr = 0x0d8000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク13から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank13から初期化コードが見つかるのは、以下のゲーム
			//   - Final Fantasy Mystic Quest
			this->type = RomType::MysticQuest;
			// TODO: 各種解析
			return;
		}

		// バンク5の頭0x2000バイトのデータをバッファに読み出します
		snesAdr = 0x058000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク5から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank5から初期化コードが見つかるのは、以下のゲーム
			//   - 半熟英雄
			this->type = RomType::HanjukuHero;
			// TODO: 各種解析
			return;
		}

		return;
	}

	//----------------------------------------------------------
	// HiRom種別判別
	// [ 対象ゲーム ]
	//   - Final Fantasy 5
	//   - Final Fantasy 6
	//   - Romancing SaGa 2
	//   - Romancing SaGa 3
	//   - Chrono Trigger
	//   - 聖剣伝説 2
	//   - 聖剣伝説 3
	//   - Live A Live
	//   - ルドラの秘宝
	//   - FRONT MISSION
	//   - FRONT MISSION GUN HAZARD
	//----------------------------------------------------------
	void RomFile::checkHiRomType()
	{
		Addressing::SnesAddress snesAdr(this->romMap, this->hasHeader, 0xc40000); // bank:4
		std::vector<uint8_t> buffer;

		// バンク4の頭0x4000バイトのデータをバッファに読み出します
		buffer.resize(0x2000);
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );

		// バンク4から、SPC初期化コードを検索します
		auto it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank4から初期化コードが見つかるのは、以下のゲーム
			//   - Final Fantasy 5
			//   - Romancing SaGa 2
			this->type = RomType::RomancingSaGa2;
			// TODO: 各種解析
			return;
		}

		// バンク5の頭0x2000バイトのデータをバッファに読み出します
		snesAdr = 0xc50000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク5から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank5から初期化コードが見つかるのは、以下のゲーム
			//   - Final Fantasy 6
			this->type = RomType::FinalFantasy6;
			// TODO: 各種解析
			return;
		}

		// バンク6の0x2000-0x4000のデータをバッファに読み出します
		snesAdr = 0xc62000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク6から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// この位置から転送コードが見つかるのは、以下のゲーム
			//   - Romancing SaGa 3
			this->type = RomType::RomancingSaGa3;
			// TODO: 各種解析
			return;
		}

		// バンク3の頭0x2000バイトのデータをバッファに読み出します
		snesAdr = 0xc30000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク3から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank3から初期化コードが見つかるのは、以下のゲーム
			//   - 聖剣伝説 2
			//   - LIVE A LIVE
			this->type = RomType::SeikenDensetsu2;
			// TODO: 各種解析
			return;
		}

		// バンク7の0x2000-0x4000のデータをバッファに読み出します
		snesAdr = 0xc72000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク7から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank7から初期化コードが見つかるのは、以下のゲーム
			//   - Chrono Trigger
			this->type = RomType::ChronoTrigger;
			// TODO: 各種解析
			return;
		}

		// バンク42の頭0x2000バイトのデータをバッファに読み出します
		snesAdr = 0xea0000;
		stream.seekg(snesAdr.getPcAddress(), std::ios::beg);
		if(stream.fail())
		{
			return;
		}
		// バンク42から、SPC初期化コードを検索します
		stream.read( (char*)&buffer[0], static_cast<std::streamsize>(buffer.size()) );
		it = std::search(
				buffer.begin(),
				buffer.end(),
				RomFile::initSpcCode.begin(),
				RomFile::initSpcCode.end()
				);
		if(it != buffer.end())
		{
			// Bank42から初期化コードが見つかるのは、以下のゲーム
			//   - FRONT MISSION
			//   - GUN HAZARD
			this->type = RomType::FrontMission;
			// TODO: 各種解析
			return;
		}

		return;
	}
}


