#pragma once

namespace Addressing
{
	class CAddressing
	{
		protected:
			// アドレス
			uint32_t m_uiAddress;
			// メモリマップ
			RomType::Map romMap;
			// ヘッダ有無
			bool hasHeader;
		public:

			//------------------------------------------------
			// コンストラクタ
			//------------------------------------------------
			CAddressing(RomType::Map romMap, bool hasHeader, uint32_t address=0)
			{
				this->romMap = romMap;
				this->hasHeader = hasHeader;
				this->m_uiAddress = address;
			}

			//------------------------------------------------
			// デストラクタ
			//------------------------------------------------
			virtual ~CAddressing(void)
			{
			}

			//------------------------------------------------
			// アドレスの再セット
			//------------------------------------------------
			CAddressing& operator =(const uint32_t address)
			{
				this->m_uiAddress = address;
				return *this;
			}

			//------------------------------------------------
			// アドレス取得
			//------------------------------------------------
			virtual uint32_t getSnesAddress() const = 0;
			virtual uint32_t getPcAddress() const = 0;
	};

	class SnesAddress : public CAddressing
	{
		public:
			SnesAddress(RomType::Map map, bool hasHeader, uint32_t adr=0)
				: CAddressing(map, hasHeader, adr) {}

			// uint32_t値変換
			operator uint32_t() const
			{
				return this->getSnesAddress();
			}

			// PCアドレス -> SNESアドレス変換
			//   値がとても大きい場合、小さい場合の考慮は特にしない。事前判定で回避する。
			CAddressing& operator =(const CAddressing& pc)
			{
				this->m_uiAddress = pc.getSnesAddress();
				return *this;
			}

			//------------------------------------------------
			// 代入処理の継承
			//------------------------------------------------
			CAddressing& operator =(const uint32_t adr)
			{
				return CAddressing::operator=(adr);
			}

			// Snesアドレスの取得
			uint32_t getSnesAddress() const { return this->m_uiAddress; }

			// Pcアドレスの取得
			uint32_t getPcAddress() const
			{
				uint32_t address;
				switch(this->romMap)
				{
					case RomType::LoRom:
						address = ( ((this->m_uiAddress&0x7f0000)>>1) | (this->m_uiAddress & 0x7fff) );
						break;

					case RomType::HiRom:
						address = (m_uiAddress & 0x3fffff);
						break;

					default:
						// TODO: 例外送出
						break;
				}
				if(hasHeader)
				{
					address += 0x200;
				}

				return address;
			}
	};

	class PcAddress : public CAddressing
	{
		public:
			PcAddress(RomType::Map map, bool hasHeader, uint32_t adr=0)
				: CAddressing(map, hasHeader, adr) {}

			// uint32_t変換
			operator uint32_t() const
			{
				return this->getPcAddress();
			}

			//------------------------------------------------
			// 代入処理の継承
			//------------------------------------------------
			CAddressing& operator =(const uint32_t adr)
			{
				return CAddressing::operator=(adr);
			}

			// PCアドレス -> SNESアドレス変換
			//   値がとても大きい場合、小さい場合の考慮は特にしない。事前判定で回避する。
			CAddressing& operator=(const CAddressing& snes)
			{
				this->m_uiAddress = snes.getPcAddress();
				return *this;
			}

			// Pcアドレスの取得
			uint32_t getPcAddress() const { return this->m_uiAddress; }

			// Snesアドレスの取得
			uint32_t getSnesAddress() const
			{
				uint32_t address = this->m_uiAddress;

				if(hasHeader)
				{
					address -= 0x200;
				}
				switch(this->romMap)
				{
					case RomType::LoRom:
						address = ( ((address<<1) & 0x7f0000) | ((address & 0x7fff)|0x8000) );
						break;

					case RomType::HiRom:
						address = ( (address & 0x3fffff)|0xc00000);
						break;

					default:
						// TODO: 例外送出
						break;
				}

				return address;
			}
	};
}
