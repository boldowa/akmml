#include "gstdafx.hpp"
#include "errcode.hpp"
#include "exception.hpp"

ErrorCode::ErrorCodeType AkMmlException::getErrorCode()
{
	return ErrorCode::OK;
}

char* AkMmlException::getErrorMessage()
{
	return "";
}
