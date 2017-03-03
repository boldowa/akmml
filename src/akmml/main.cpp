/**
 * Square MML Compiler
 *
 */
#include "gstdafx.hpp"
#include "errcode.hpp"
#include "file.hpp"
#include "exefile.hpp"
#include "option.hpp"
#include "exception.hpp"
#include "akmml.hpp"

bool vdebug = false;
int main(int argc, char **argv)
{
	ErrorCode::ErrorCodeType errorcode = ErrorCode::OK;
	AkMml* akmml = nullptr;
	AkMmlOption opt(argv[0]);

	// オプションを読み出します
	if(false == opt.parseArgsOption(argc, argv))
	{
		return ErrorCode::ArgsError;
	}

	// akmmlのメインコードを実行します
	try
	{
		akmml = new AkMml(opt);
		akmml->Run();
	}
	catch(AkMmlException &e)
	{
		putfatal("捕捉されない例外が発生しました。");
		putexception(e.getErrorCode(), e.getErrorMessage());
		errorcode = e.getErrorCode();
	}

	delete akmml;

	return errorcode;
}

