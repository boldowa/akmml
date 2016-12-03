/**
 * Square MML Compiler
 *
 */
#include "gstdafx.h"
#include "errcode.h"
#include "option.h"
#include "exception.h"
#include "akmml.h"

bool vdebug = false;
int main(int argc, char **argv)
{
	ErrorCode::ErrorCodeType errorcode = ErrorCode::OK;
	AkMml* akmml = nullptr;
	AkMmlOption opt;

	// オプションを読み出します
	if(false == opt.parseArgsOption(argc, argv))
	{
		return ErrorCode::ARGSERROR;
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

