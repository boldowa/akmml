#include "commonBuildTime.h"

commonBuildTime::commonBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

commonBuildTime::~commonBuildTime()
{
}

const char* commonBuildTime::GetDateTime()
{
    return dateTime;
}

