#include "mml2tokenBuildTime.h"

mml2tokenBuildTime::mml2tokenBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

mml2tokenBuildTime::~mml2tokenBuildTime()
{
}

const char* mml2tokenBuildTime::GetDateTime()
{
    return dateTime;
}

