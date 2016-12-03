#include "gstdafx.h"
#include "errcode.h"
#include "exception.h"

ErrorCode::ErrorCodeType AkMmlException::getErrorCode()
{
	return ErrorCode::OK;
}

char* AkMmlException::getErrorMessage()
{
	return "";
}
