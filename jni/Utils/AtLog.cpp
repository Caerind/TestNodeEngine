#include "AtLog.hpp"

AtLog* AtLog::mInstance = nullptr;

AtLog& AtLog::instance()
{
    if(mInstance == nullptr)
        mInstance = new AtLog();
    return *mInstance;
}

void AtLog::setAppName(std::string appName)
{
    mAppName = appName;
}

void AtLog::setAppVersion(std::string appVersion)
{
    mAppVersion = appVersion;
}

void AtLog::setUsername(std::string username)
{
    mUsername = username;
}
