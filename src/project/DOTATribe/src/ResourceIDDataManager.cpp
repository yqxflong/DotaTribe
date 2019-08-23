//Name£ºResourceIDDataManager
//Written By£ºÒüÇ¿

#include "../include/ResourceIDDataManager.h"
#include "../include/DBSystem.h"
#include <include/common/Parser.h>
#include "../include/LoggerSystem.h"

using  namespace  cobra_win;
using namespace std;

ResourceIDData::ResourceIDData()
:IconID_(0)
{
	  resourceType=_RESOURCETYPE_IMAGE_TYPE_;
	  memset(textureName,0,sizeof(filepath_));
   	  memset(filepath_,0,sizeof(filepath_));
}

bool  ResourceIDData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	bool isErr=false;
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(IconID_))
		isErr=true;

	if (!parser.parser_short_value(resourceType))
		isErr=true;

	if (!parser.parser_string_value(textureName,sizeof(textureName)))
		isErr=true;

	if(!parser.parser_string_value(filepath_,sizeof(filepath_)))
		isErr=true;

	if (isErr)
	{
		LOGGERSYSTEM->LogInfo("Err: ResourceIDData read Error!");
		return false;
	}
	return true; 
}

template<> ResourceIDDataManager* cobra_win::Singleton2<ResourceIDDataManager>::m_pMySelf = NULL;


std::string ResourceIDDataManager::getDataByID(int idx){
 
	std::map<int,ResourceIDData *>::iterator iter_resource=m_resouceDataMap.find(idx);
	if(iter_resource!=m_resouceDataMap.end())
	{
         return iter_resource->second->filepath_;
	}
	return "";
}


ResourceIDData  * ResourceIDDataManager::GetResourceDataByID(int idx)
{ 
	std::map<int,ResourceIDData *>::iterator  iter_resource=m_resouceDataMap.find(idx);
	if(iter_resource!=m_resouceDataMap.end())
	{
		return iter_resource->second;
	}
	return NULL;
}

cocos2d::CCSprite * ResourceIDDataManager::GetSpriteFromID(int idx)
{ 
	std::map<int,ResourceIDData *>::iterator  iter_resource=m_resouceDataMap.find(idx);
	cocos2d::CCSprite * pSprite=NULL;
	if(iter_resource!=m_resouceDataMap.end())
	{ 
		if(iter_resource->second->resourceType!=ResourceIDData::_RESOURCETYPE_PLIST_TYPE_)
		{
			pSprite=cocos2d::CCSprite::create();
			pSprite->setProperty("File",iter_resource->second->filepath_);
			return  pSprite;
	  	} 
		else
		{
			cocos2d::CCSpriteFrame * pSpriteFrame=cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iter_resource->second->textureName);
			if(!pSpriteFrame)
			{
				cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(iter_resource->second->filepath_);
				pSpriteFrame=cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iter_resource->second->textureName);
			} 
			pSprite=cocos2d::CCSprite::createWithSpriteFrame(pSpriteFrame);
			return pSprite;
		} 
	}
	return NULL;
}




std::string   ResourceIDDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/resourceid.txt";

	return "resourceid";
} 


unsigned  int ResourceIDDataManager::GetSize()
{
	return m_resouceDataMap.size()*sizeof(ResourceIDData);
}


bool  ResourceIDDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
		{
			if (!LoadFromDB())
				break;
		}
		else
		{
			if (!LoadFromFile())
				break;
		}

		return true;
	} 
	while(false);
	return false;
}


void  ResourceIDDataManager::Tick()
{

}


void  ResourceIDDataManager::Destroy()
{
	std::map<int, ResourceIDData*>::iterator iter   = m_resouceDataMap.begin();
	std::map<int, ResourceIDData*>::iterator iter_e = m_resouceDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	return m_resouceDataMap.clear();
} 


bool  ResourceIDDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ResourceIDData* item = (ResourceIDData*)pData;
	assert(item != NULL);

	return true;
}

bool  ResourceIDDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ResourceIDDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	ResourceIDData* pItemData = new ResourceIDData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;
	m_resouceDataMap.insert(std::map<int,ResourceIDData *>::value_type(pItemData->IconID_,pItemData));
	return true;
}