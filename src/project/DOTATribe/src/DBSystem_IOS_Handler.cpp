#include <cocos2d.h>
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include "../include/LoggerSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/MD5Crypto.h>



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


bool DBSystem::LoadDBFile()
{
	do 
	{
		std::string dbFile = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("resource/data/game.data");
		int ret = sqlite3_open(dbFile.c_str(), &m_pSQLite);
		if (ret != SQLITE_OK)
		{
			LOGGERSYSTEM->LogFatal("Init DBSystem Failed, DBFile=%s\n", dbFile.c_str());
			return false;
		}

		dbFile = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("resource/layout/ui.data");
		ret = sqlite3_open(dbFile.c_str(), &m_pUISQLite);
		if (ret != SQLITE_OK)
		{
			LOGGERSYSTEM->LogFatal("Init DBSystem Failed, UI DBFile=%s\n", dbFile.c_str());
			return false;
		}

		return true;
	} 
	while(false);

	return false;
}


#endif
