#include <cocos2d.h>
#include "../include/ArtFontDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>

#define  MAX_FONT_SIZE    18


ArtFontData::ArtFontData()
{ 
     artFontDataID=0;							//字体ID
	 artFontDataMap.clear();
  
}

ArtFontData::~ArtFontData()
{

}

bool ArtFontData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(artFontDataID))
		return false;

	int  artIndex=0;
	int  artValue=0;

	for(int artIndex=0;artIndex<MAX_FONT_SIZE;artIndex++)
	{
		if (!parser.parser_int_value(artValue))
			return false;
		artFontDataMap.insert(std::map<int,int>::value_type(artIndex,artValue));
	} 

	return true;
}

template<> ArtFontDataManager* cobra_win::Singleton2<ArtFontDataManager>::m_pMySelf = NULL;

ArtFontDataManager::ArtFontDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_ArtFontDataMap.clear();
}	

ArtFontDataManager::~ArtFontDataManager()
{

}


int    ArtFontDataManager::GetArtFontValueFromID(int artFontType,int artFontIndex)
{
	std::map<int,ArtFontData *>::iterator   iter_art=m_ArtFontDataMap.find(artFontType);
	if(iter_art!=m_ArtFontDataMap.end())
	{
		if(iter_art->second!=NULL)
		{
			std::map<int,int>::iterator iter_font=iter_art->second->artFontDataMap.find(artFontIndex);
			if(iter_font!=iter_art->second->artFontDataMap.end())
			{
				return  iter_font->second;
			}
		}
	}
	return -1;
}


 
ArtFontData* ArtFontDataManager::GetArtFontDataByID(int artFontID)
{
	std::map<int , ArtFontData*>::iterator  iter_animation = m_ArtFontDataMap.find(artFontID);
	if(iter_animation!=m_ArtFontDataMap.end())
	{	
		return iter_animation->second;
	}
	return NULL;
}
 

std::string ArtFontDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/artfontdefine.txt";

	return "artfontdefine";
}

unsigned  int ArtFontDataManager::GetSize()
{
	return m_ArtFontDataMap.size()*sizeof(ArtFontData);
}

bool  ArtFontDataManager::Init()
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

void  ArtFontDataManager::Tick()
{

}

void  ArtFontDataManager::Destroy()
{
	std::map<int, ArtFontData*>::iterator iter   = m_ArtFontDataMap.begin();
	std::map<int, ArtFontData*>::iterator iter_e = m_ArtFontDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	return m_ArtFontDataMap.clear();
}

bool  ArtFontDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ArtFontData* pAnimation = (ArtFontData*)pData;
	assert(pAnimation != NULL);

	return true;
}

bool  ArtFontDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ArtFontDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	ArtFontData* pItemData = new ArtFontData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;
	if (!Varify(pItemData))
		return false;
	m_ArtFontDataMap.insert(std::map<int , ArtFontData*>::value_type(pItemData->artFontDataID, pItemData));
	return true;
}
