#include  <cocos2d.h>
#include  "../include/AnnouncementDataManager.h"
#include  "../include/DBSystem.h"
#include  "../include/EngineSystem.h"
#include  <include/mem/DPacket.h>
#include  <include/common/String.h>
#include  <include/common/Parser.h>
#include  <assert.h>


AnnouncementData::AnnouncementData()
{
    announcementStyleID=0;
    announcementFontStyleID=0;
	announcementVisiableLeftX=0.0f;
	announcementVisiableRightX=0.0f;
	announcementVisiableY=0.0f;
	announcemenrScrollSpeed=0.0f;
	announcementIntervalTime=0.0f;
	announcementRepeatCount=0;

}

AnnouncementData::~AnnouncementData()
{

}

bool AnnouncementData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(announcementStyleID))
		return false;
	if (!parser.parser_int_value(announcementFontStyleID))
		return false; 
	if (!parser.parser_float_value(announcementVisiableRightX))
		return false;
	if (!parser.parser_float_value(announcementVisiableLeftX))
		return false;
	if (!parser.parser_float_value(announcementVisiableY))
		return false;
	if (!parser.parser_float_value(announcemenrScrollSpeed))
		return false;
	if (!parser.parser_float_value(announcementIntervalTime))
		return false;
	if (!parser.parser_short_value(announcementRepeatCount))
		return false;
	 
	announcementIntervalTime/=1000;

	return true;
}

template<> AnnouncementDataManager* cobra_win::Singleton2<AnnouncementDataManager>::m_pMySelf = NULL;

AnnouncementDataManager::AnnouncementDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	 m_AnnouncementDataList.clear();
}	

AnnouncementDataManager::~AnnouncementDataManager()
{

} 

AnnouncementData* AnnouncementDataManager::GetAnnouncementDataByID(int announcementStyleID)
{
	std::map<int , AnnouncementData*>::iterator  announcement_iter  = m_AnnouncementDataList.find(announcementStyleID);
	if(announcement_iter!=m_AnnouncementDataList.end())
	{	
		return announcement_iter->second;
	}
	return NULL;
}
  

std::string AnnouncementDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/announcementdata.txt";

	return "announcementdata";
}

unsigned  int AnnouncementDataManager::GetSize()
{
	return m_AnnouncementDataList.size()*sizeof(AnnouncementData);
}

bool  AnnouncementDataManager::Init()
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

void  AnnouncementDataManager::Tick()
{

}

void  AnnouncementDataManager::Destroy()
{
	std::map<int, AnnouncementData*>::iterator iter   = m_AnnouncementDataList.begin();
	std::map<int, AnnouncementData*>::iterator iter_e = m_AnnouncementDataList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	return m_AnnouncementDataList.clear();
}

bool  AnnouncementDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	AnnouncementData* pAnimation = (AnnouncementData*)pData;
	assert(pAnimation != NULL);

	return true;
}

bool  AnnouncementDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  AnnouncementDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	AnnouncementData* pItemData = new AnnouncementData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_AnnouncementDataList.insert(std::map<int , AnnouncementData*>::value_type(pItemData->announcementStyleID, pItemData));
	return true;
}
