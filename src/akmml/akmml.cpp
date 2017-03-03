
#include "gstdafx.hpp"
#include "errcode.hpp"
#include "file.hpp"
#include "mmlfile.hpp"
#include "exefile.hpp"
#include "converter.hpp"
#include "romtype.hpp"
#include "romfile.hpp"
#include "romcatalog.hpp"
#include "option.hpp"
#include "akmml.hpp"

//----------------------------------------------------------
// コンストラクタ
AkMml::AkMml(AkMmlOption& opt) : opt(opt)
{
}

//----------------------------------------------------------
// デストラクタ
AkMml::~AkMml()
{
}

//----------------------------------------------------------
// プログラムの実行
void AkMml::Run()
{
	if(this->opt.isPutUsageEnabled())
	{
		// 使い方表示を行っていた場合、何もせず終了する
		return;
	}

	//------------------------------------------------
	// ROMのデータベースを構築します
	//------------------------------------------------
	std::string romSearchPath = this->opt.programName.getDir();
	romSearchPath.append("roms/");
	akmml::RomCatalog romCatalog(romSearchPath);

	// 対応するROMデータがひとつもない場合は、実行中止
	if(romCatalog.empty())
	{
		putfatal("There is no rom file. Please store rom in \"roms\" directory.");
		this->errorcode = ErrorCode::RomNotFound;
		return;
	}

	//------------------------------------------------
	// 入力ファイルをひとつずつ処理していきます
	//------------------------------------------------
	std::string sInput = this->opt.dequeInputs();
	while(false == sInput.empty())
	{
		// TODO: ここに処理を書く
		akmml::MmlFile f(sInput);
		putdebug("\"%s\" is loaded.", f.getPath().c_str());
		putdebug("  name : %s", f.getName().c_str());
		putdebug("  dir  : %s", f.getDir().c_str());
		putdebug("  ext  : %s", f.getExt().c_str());
		akmml::MmlFile g(f);
		g.changeExt("spc");
		putdebug("\"%s\" will write.", g.getPath().c_str());
		putdebug("  name : %s", g.getName().c_str());
		putdebug("  dir  : %s", g.getDir().c_str());
		putdebug("  ext  : %s", g.getExt().c_str());

		// 次に処理するファイル名を読み出す
		sInput = this->opt.dequeInputs();
	}

	this->errorcode = ErrorCode::OK;
	return;
}

