#include "../include/DOTATribeApp.h"
#include "../include/SkillTableDataManager.h"
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
#include  "../include/SysLangDataManager.h"
using  namespace  cobra_win;


SkillTableData::SkillTableData()
{
	 skillItemID_=0;       
     skillItemNameSYSID=0;
	 skillItemIconID=0; 
     skillItemActionsID=0;
	 memset(skillItemLaunchTime,0,sizeof(skillItemLaunchTime));
	 memset(skillItemHurt,0,sizeof(skillItemHurt));
	 memset(skillItemDesc,0,sizeof(skillItemDesc));
	 memset(skillItemDurationTime,0,sizeof(skillItemDurationTime));
	 memset(skillItemLaunchLimitDesc,0,sizeof(skillItemLaunchLimitDesc));
	 memset(skillItemProficientDesc,0,sizeof(skillItemProficientDesc));
	 skillItemClientXPos=0;
	 skillItemClientYPos=0;
	 skillItemHurtCallTime=0;
	 skillItemEffetCallTime=0.0f;
	 skillItemResidesEffectID=0; 
	
}

SkillTableData::~SkillTableData()
{
  
}


std::string   SkillTableData::GetSkillItemName()
{ 
	return SysLangDataManager::get_instance2()->GetSysLangById(skillItemNameSYSID);
}

bool  SkillTableData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(skillItemID_))
		return false;
   
	if (!parser.parser_int_value(skillItemNameSYSID))
		return false;

	if (!parser.parser_int_value(skillItemIconID))
		return false;

	if (!parser.parser_int_value(skillItemActionsID))
		return false;

	if (!parser.parser_string_value(skillItemLaunchTime,sizeof(skillItemLaunchTime)))
		return false;

	if (!parser.parser_string_value(skillItemHurt,sizeof(skillItemHurt)))
		return false;

	if (!parser.parser_string_value(skillItemDesc,sizeof(skillItemDesc)))
		return false;

	if (!parser.parser_string_value(skillItemDurationTime,sizeof(skillItemDurationTime)))
		return false;

	if (!parser.parser_string_value(skillItemLaunchLimitDesc,sizeof(skillItemLaunchLimitDesc)))
		return false;

	if (!parser.parser_string_value(skillItemProficientDesc,sizeof(skillItemProficientDesc)))
		return false;

	if (!parser.parser_int_value(skillItemClientXPos))
		return false;

	if (!parser.parser_int_value(skillItemClientYPos))
		return false;

	if (!parser.parser_int_value(skillItemHurtCallTime))
		return false;

	if (!parser.parser_float_value(skillItemEffetCallTime))
		return false;

	if (!parser.parser_int_value(skillItemResidesEffectID))
		return false;

	 return true; 
}

 

template<> SkillTableDataManager* cobra_win::Singleton2<SkillTableDataManager>::m_pMySelf = NULL;

SkillTableDataManager::SkillTableDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_skillTableMapList.clear();
}

SkillTableDataManager::~SkillTableDataManager()
{

}

SkillTableData * SkillTableDataManager::GetSkillTableDataByID(int skillItemID)
{
	std::map<int,SkillTableData*>::iterator skillIter=m_skillTableMapList.find(skillItemID);
	if(skillIter!=m_skillTableMapList.end())
	{
		return skillIter->second;
	}
	return NULL; 
}


size_t  SkillTableDataManager::GetSkillTableCount()
{
     return  m_skillTableMapList.size();	
}



std::string   SkillTableDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/skilltabledata.txt";

	return "skilltabledata";
} 


unsigned  int SkillTableDataManager::GetSize()
{
	return m_skillTableMapList.size()*sizeof(SkillTableData);
}


bool  SkillTableDataManager::Init()
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


void  SkillTableDataManager::Tick()
{

}


void  SkillTableDataManager::Destroy()
{
	std::map<int, SkillTableData*>::iterator iter   = m_skillTableMapList.begin();
	std::map<int, SkillTableData*>::iterator iter_e = m_skillTableMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_skillTableMapList.clear();
} 


bool  SkillTableDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	SkillTableData* pRoleItem = (SkillTableData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  SkillTableDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  SkillTableDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	SkillTableData* pItemData = new SkillTableData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_skillTableMapList.insert(std::map<int, SkillTableData*>::value_type(pItemData->skillItemID_, pItemData));

	return true;
}












