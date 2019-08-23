#include "../include/DOTATribeApp.h"
#include "../include/NpcTalkDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DBSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;

#define  FOR_EACH_TALK_BEGIN(cout)  for(size_t talkIndex=0;talkIndex<cout;talkIndex++) {
#define  FOR_EACH_TALK_END			}
#define  MAX_TALK_PAGE				6



NpcTalkData::NpcTalkData()
{
 
}

NpcTalkData::~NpcTalkData()
{

}

bool  NpcTalkData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(npctalkID))
		return false;

	if (!parser.parser_int_value(npcMapID))
		return false;	

	if (!parser.parser_int_value(npcStageID))
		return false;
	
	int roleContentType=0;
	int contentSysID=0;
	int talkCount=0;

	  if (!parser.parser_int_value(beforBattlePageCount))
		return false;

	  FOR_EACH_TALK_BEGIN(MAX_TALK_PAGE)
		  if (!parser.parser_int_value(roleContentType))
			  return false;
	  if (!parser.parser_int_value(contentSysID))
		  return false;
	  if(talkCount<beforBattlePageCount)
	  {
		  if(roleContentType!=-1&&contentSysID!=-1)
		  {
			  TalkNode talkNode;
			  talkNode.contentRoleType=roleContentType;
			  talkNode.contentSysID=contentSysID;
			  beforBattlePageVect.push_back(talkNode);
			  talkCount++;
		  }
	  }
	  FOR_EACH_TALK_END
	     
	   talkCount=0;
	   if (!parser.parser_int_value(winBattlePageCount))
		  return false;


	   FOR_EACH_TALK_BEGIN(MAX_TALK_PAGE)
		   if (!parser.parser_int_value(roleContentType))
			   return false;
	   if (!parser.parser_int_value(contentSysID))
		   return false;
	   if(talkCount<winBattlePageCount)
	   {
		   if(roleContentType!=-1&&contentSysID!=-1)
		   {
			   TalkNode talkNode;
			   talkNode.contentRoleType=roleContentType;
			   talkNode.contentSysID=contentSysID;
			   winBattlePageVect.push_back(talkNode);
			   talkCount++;
		   }
	   }
	   FOR_EACH_TALK_END

	 talkCount=0; 

	if (!parser.parser_int_value(failBattlePageCount))
		return false;
	FOR_EACH_TALK_BEGIN(MAX_TALK_PAGE)
		if (!parser.parser_int_value(roleContentType))
			return false;
	if (!parser.parser_int_value(contentSysID))
		return false;
	if(talkCount<failBattlePageCount)
	{
		if(roleContentType!=-1&&contentSysID!=-1)
		{
			TalkNode talkNode;
			talkNode.contentRoleType=roleContentType;
			talkNode.contentSysID=contentSysID;
			failBattlePageVect.push_back(talkNode);
			talkCount++;
		}
	}
	FOR_EACH_TALK_END

	return true; 
}
 


template<> NpcTalkDataManager* cobra_win::Singleton2<NpcTalkDataManager>::m_pMySelf = NULL;

NpcTalkDataManager::NpcTalkDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_npcTalkDataMap.clear();
}

NpcTalkDataManager::~NpcTalkDataManager()
{

}


NpcTalkData *NpcTalkDataManager::GetNpcTalkDataWithMapAndStage(int mapID,int stageID)
{
	//查询Map 和 StageID  对应的ID
	std::map<int,NpcTalkData*>::iterator shapeIter=m_npcTalkDataMap.begin();
	while(shapeIter!=m_npcTalkDataMap.end())
	{
		NpcTalkData * pTmpTalkData=shapeIter->second;
		if(pTmpTalkData!=NULL)
		{
			if(pTmpTalkData->npcMapID==mapID&&pTmpTalkData->npcStageID==stageID)
			{
				return pTmpTalkData;
			}
		}
		shapeIter++;
	}
	return NULL;
}
 

std::string   NpcTalkDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/npctalkdata.txt";

	return "npctalkdata";
} 


unsigned  int NpcTalkDataManager::GetSize()
{
	return m_npcTalkDataMap.size()*sizeof(NpcTalkData);
}


bool  NpcTalkDataManager::Init()
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


void  NpcTalkDataManager::Tick()
{

}


void  NpcTalkDataManager::Destroy()
{
	std::map<int, NpcTalkData*>::iterator iter   = m_npcTalkDataMap.begin();
	std::map<int, NpcTalkData*>::iterator iter_e = m_npcTalkDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_npcTalkDataMap.clear();
} 


bool  NpcTalkDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	NpcTalkData* pRoleItem = (NpcTalkData*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  NpcTalkDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  NpcTalkDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	NpcTalkData* pItemData = new NpcTalkData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_npcTalkDataMap.insert(std::map<int, NpcTalkData*>::value_type(pItemData->npctalkID, pItemData));

	return true;
}