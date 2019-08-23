#include <cocos2d.h>
#include "../include/ActionSetDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/DBSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>


ActionSetData::ActionSetData()
{
	mActionId = -1;
	memset(mActionName, 0, sizeof(mActionName));
	mActionCompositeEffectID=-1;

}

ActionSetData::~ActionSetData()
{

}

bool ActionSetData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	int id = 0;
	if (!parser.parser_int_value(mActionId))
		return false; 

	if (!parser.parser_string_value(mActionName, sizeof(mActionName)))
		return false;

	if (!parser.parser_int_value(mActionCompositeEffectID))
		return false; 

	return true;
}


template<> ActionSetDataManager* cobra_win::Singleton2<ActionSetDataManager>::m_pMySelf = NULL;

ActionSetDataManager::ActionSetDataManager(bool bLoadFromDB, bool bEncryption, std::string fileName, std::string tableName) : IDataManager(bLoadFromDB, bEncryption)
{
	m_FileName = fileName;
	m_TableName= tableName;

	m_ActionList.clear();
}

ActionSetDataManager::~ActionSetDataManager()
{

}

std::string ActionSetDataManager::GetTableName()
{
	return m_TableName;
}
 

std::string ActionSetDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return m_FileName;

	return m_TableName;
}

unsigned int ActionSetDataManager::GetSize()
{
	return m_ActionList.size()*sizeof(ActionSetData);
}

bool  ActionSetDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ActionSetData* pAction = (ActionSetData*)pData;
	assert(pAction != NULL);
 
	return true;
}

bool  ActionSetDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool ActionSetDataManager::Init()
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

void ActionSetDataManager::Tick()
{

}

void ActionSetDataManager::Destroy()
{
	std::multimap<int, ActionSetData*>::iterator iter   = m_ActionList.begin();
	while(iter!=m_ActionList.end())
	{ 
		delete iter->second;
		iter++;
	}
	m_ActionList.clear();

}

std::string ActionSetDataManager::GetActionNameByActionId(int actionId)
{
	 std::multimap<int, ActionSetData*>::iterator iter_action = m_ActionList.find(actionId);
	 if(iter_action!=m_ActionList.end())
	 { 
		 return  iter_action->second->mActionName;
	 }
	 return "";
}

ActionSetData* ActionSetDataManager::GetActionSetDataByActionId(int actionId)
{
	std::multimap<int, ActionSetData*>::iterator iter_action = m_ActionList.find(actionId);
	if(iter_action!=m_ActionList.end())
	{
		return iter_action->second;
	}
	return  NULL;
}

int ActionSetDataManager::GetActionIDFromActionName(std::string actionName)
{
    if(!actionName.empty())
	{
		std::multimap<int, ActionSetData*>::iterator iter_action   = m_ActionList.begin();
		while(iter_action!=m_ActionList.end())
		{
			if(iter_action->second!=NULL&&strcmp(iter_action->second->mActionName,actionName.c_str())==0)
			{
				return iter_action->second->mActionId;
			}
			iter_action++;
		}
	}
	return 0;
}

int  ActionSetDataManager::GetCompositeEffectByActionID(int actionID)
{
	std::multimap<int, ActionSetData*>::iterator iter_action  = m_ActionList.find(actionID);
	if(iter_action!=m_ActionList.end())
	{
		return iter_action->second->mActionCompositeEffectID;
	}
	return -1;
}
 

ActionSetData*   ActionSetDataManager::GetActionSetDataByActionName(std::string actionName)
{
	if(!actionName.empty())
	{
		std::multimap<int, ActionSetData*>::iterator iter_action   = m_ActionList.begin();
		while(iter_action!=m_ActionList.end())
		{
			if(iter_action->second!=NULL&&strcmp(iter_action->second->mActionName,actionName.c_str())==0)
			{
				return iter_action->second;
			}
			iter_action++;
		}
	}
	return NULL;
}

 

bool ActionSetDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	ActionSetData* pItemData = new ActionSetData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_ActionList.insert(std::multimap<int, ActionSetData*>::value_type(pItemData->mActionId, pItemData));
	return true;
}
