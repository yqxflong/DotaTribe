#include "../include/DOTATribeApp.h"
#include "../include/SkillActionDataManager.h"
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


SkillActionData::SkillActionData()
{

	skillActionsID_=0;                     //动作组ID  
	skillSituActionID_=0;                  //原地动作ID
	skillSituActionType_=0;                //原地动作类型
 

	skillAdvanceActionID_=0;			   //前进动作ID
	skillAdvanceType_=0;				   //前进动作类型
	skillAdvanceSpeed_=0.0f;			   //前进动作速度
 

	skillTargetActionID_=0;				   //目标动作ID	
	skillTargetActionType_=0;			   //目标动作类型
 

	skillReturnActionID_=0;					//返回动作ID
	skillReturnActionType_=0;				//返回动作类型
	skillReturnSpeed_=0.0f;					//返回动作速度


	skillActiveActionVec_.clear();
 
}

SkillActionData::~SkillActionData()
{

}

bool  SkillActionData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(skillActionsID_))
		return false;

	if (!parser.parser_int_value(skillSituActionID_))
		return false;

	if (!parser.parser_int_value(skillSituActionType_))
		return false;
  
	if (!parser.parser_int_value(skillAdvanceActionID_))
		return false;
	 
	if (!parser.parser_int_value(skillAdvanceType_))
		return false;

	if (!parser.parser_float_value(skillAdvanceSpeed_))
		return false;
 
	if (!parser.parser_int_value(skillTargetActionID_))
		return false;

	if (!parser.parser_int_value(skillTargetActionType_))
		return false;
 
	if (!parser.parser_int_value(skillReturnActionID_))
		return false;

	if (!parser.parser_int_value(skillReturnActionType_))
		return false;

	if (!parser.parser_float_value(skillReturnSpeed_))
		return false;

	if(skillSituActionID_!=-1)
	{
		skillActiveActionVec_.push_back(skillSituActionID_);
	}
	if(skillAdvanceActionID_!=-1)
	{
		skillActiveActionVec_.push_back(skillAdvanceActionID_);
	}
	if(skillTargetActionID_!=-1)
	{
		skillActiveActionVec_.push_back(skillTargetActionID_);
	}
	if(skillReturnActionID_!=-1)
	{
		skillActiveActionVec_.push_back(skillReturnActionID_);
	} 
	return true; 
}



template<> SkillActionDataManager* cobra_win::Singleton2<SkillActionDataManager>::m_pMySelf = NULL;

SkillActionDataManager::SkillActionDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_skillActionMapList_.clear();
}

SkillActionDataManager::~SkillActionDataManager()
{

}

SkillActionData * SkillActionDataManager::GetSkillActionItemByID(int skillItemID)
{
	std::map<int,SkillActionData*>::iterator skillIter=m_skillActionMapList_.find(skillItemID);
	if(skillIter!=m_skillActionMapList_.end())
	{
		return skillIter->second;
	}
	return NULL; 
}
 

std::string   SkillActionDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/skillactiondata.txt";

	return "skillactiondata";
} 


unsigned  int SkillActionDataManager::GetSize()
{
	return m_skillActionMapList_.size()*sizeof(SkillActionData);
}


bool  SkillActionDataManager::Init()
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


void  SkillActionDataManager::Tick()
{

}


void  SkillActionDataManager::Destroy()
{
	std::map<int, SkillActionData*>::iterator iter   = m_skillActionMapList_.begin();
	std::map<int, SkillActionData*>::iterator iter_e = m_skillActionMapList_.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_skillActionMapList_.clear();
} 


bool  SkillActionDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	SkillActionData* pRoleItem = (SkillActionData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  SkillActionDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  SkillActionDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	SkillActionData* pItemData = new SkillActionData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_skillActionMapList_.insert(std::map<int, SkillActionData*>::value_type(pItemData->skillActionsID_, pItemData));

	return true;
}












