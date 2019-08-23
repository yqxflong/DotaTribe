#include <cocos2d.h>
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include "../include/LoggerSystem.h"
#include <include/common/FileLoader.h>
#include <include/common/MD5Crypto.h>
#include "../include/CSMapTable.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


bool DBSystem::LoadDBFile()
{
	do 
	{
		char*        pBuffer = NULL;
		unsigned int iLength = 0;
		if (!EngineSystem::LoadAppFile("resource/data/game.data", pBuffer, iLength))
		{
			LOGGERSYSTEM->LogFatal("Init DBSystem Failed, DB Data Invalid\n");
			return false;
		}

		// 保存到SD卡对应目录下面
		std::string dbFile = EngineSystem::GetDocumentDir()+"game.db";
		FileLoader loader;
		if (!loader.load((char*)dbFile.c_str(), FileLoader::_TYPED_CLEAR_WRITE_))
		{
			loader.unload();
			delete []pBuffer;
			return false;
		}

		loader.write(pBuffer, iLength);
		loader.unload();
		delete []pBuffer;

		int ret = sqlite3_open(dbFile.c_str(), &m_pSQLite);
		if (ret != SQLITE_OK)
		{
			LOGGERSYSTEM->LogFatal("Init DBSystem Failed, DBFile=%s\n", dbFile.c_str());
			return false;
		}

		pBuffer = NULL;
		iLength = 0;
		if (!EngineSystem::LoadAppFile("resource/layout/ui.data", pBuffer, iLength))
		{
			LOGGERSYSTEM->LogFatal("Init DBSystem Failed, UI DB Data Invalid\n");
			return false;
		}

		// 保存到SD卡对应目录下面
		dbFile = EngineSystem::GetDocumentDir()+"ui.db";
		if (!loader.load((char*)dbFile.c_str(), FileLoader::_TYPED_CLEAR_WRITE_))
		{
			loader.unload();
			delete []pBuffer;
			return false;
		}

		loader.write(pBuffer, iLength);
		loader.unload();
		delete []pBuffer;

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
