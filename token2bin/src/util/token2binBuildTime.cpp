#include "token2binBuildTime.h"

token2binBuildTime::token2binBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

token2binBuildTime::~token2binBuildTime()
{
}

const char* token2binBuildTime::GetDateTime()
{
    return dateTime;
}

