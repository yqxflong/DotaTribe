#include "../include/DOTATribeApp.h"
#include "../include/RoleShapePropertyDataManager.h"
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


RoleShapePropertyData::RoleShapePropertyData()
{

    roleShapeID_=0;
	memset(roleImageName,0,sizeof(roleImageName));
	memset(roleXiuXianActionName,0,sizeof(roleXiuXianActionName));
	memset(roleXingZouActionName,0,sizeof(roleXingZouActionName));

	memset(roleNormalAttackActionName,0,sizeof(roleNormalAttackActionName));
    memset(roleRemoteAttackActionName,0,sizeof(roleRemoteAttackActionName)); 
	memset(roleHurtActionName,0,sizeof(roleHurtActionName));
	memset(roleDeadActionName,0,sizeof(roleDeadActionName));

	memset(roleDodgeActionName,0,sizeof(roleDodgeActionName));
	memset(roleCritActionName,0,sizeof(roleCritActionName));
	memset(roleWinActionName,0,sizeof(roleWinActionName));
 
}

RoleShapePropertyData::~RoleShapePropertyData()
{

}

bool  RoleShapePropertyData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	int id = 0;
	if (!parser.parser_int_value(roleShapeID_))
		return false;

	if (!parser.parser_string_value(roleImageName, sizeof(roleImageName)))
		return false;

	if (!parser.parser_string_value(roleXiuXianActionName, sizeof(roleXiuXianActionName)))
		return false;

	if (!parser.parser_string_value(roleXingZouActionName, sizeof(roleXingZouActionName)))
		return false;

	if (!parser.parser_string_value(roleNormalAttackActionName, sizeof(roleNormalAttackActionName)))
		return false;

	if (!parser.parser_string_value(roleRemoteAttackActionName, sizeof(roleRemoteAttackActionName)))
		return false;

	if (!parser.parser_string_value(roleHurtActionName, sizeof(roleHurtActionName)))
		return false;

	if (!parser.parser_string_value(roleDeadActionName, sizeof(roleDeadActionName)))
		return false;

	if (!parser.parser_string_value(roleDodgeActionName, sizeof(roleDodgeActionName)))
		return false;

	if (!parser.parser_string_value(roleCritActionName, sizeof(roleCritActionName)))
		return false;

	if (!parser.parser_string_value(roleWinActionName, sizeof(roleWinActionName)))
		return false;

 	  return true; 
}




template<> RoleShapePropertyDataManager* cobra_win::Singleton2<RoleShapePropertyDataManager>::m_pMySelf = NULL;

RoleShapePropertyDataManager::RoleShapePropertyDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
    m_RoleShapePropertyList.clear();
}

RoleShapePropertyDataManager::~RoleShapePropertyDataManager()
{
 
}

 
RoleShapePropertyData * RoleShapePropertyDataManager::GetRoleShapeDateById(int roleShapeId)
{

	std::map<int,RoleShapePropertyData*>::iterator shapeIter=m_RoleShapePropertyList.find(roleShapeId);
	if(shapeIter!=m_RoleShapePropertyList.end())
	{
		return shapeIter->second;
	}
    return NULL; 
}
 
std::string   RoleShapePropertyDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/roleshapepropertydata.txt";

	return "RoleShapePropertyData";
   
} 

 
unsigned  int RoleShapePropertyDataManager::GetSize()
{
   return m_RoleShapePropertyList.size()*sizeof(RoleShapePropertyData);
}

 
bool  RoleShapePropertyDataManager::Init()
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


void  RoleShapePropertyDataManager::Tick()
{
 
}


void  RoleShapePropertyDataManager::Destroy()
{
	std::map<int, RoleShapePropertyData*>::iterator iter   = m_RoleShapePropertyList.begin();
	std::map<int, RoleShapePropertyData*>::iterator iter_e = m_RoleShapePropertyList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_RoleShapePropertyList.clear();
} 

 
bool  RoleShapePropertyDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	RoleShapePropertyData* pRoleItem = (RoleShapePropertyData*)pData;
	assert(pRoleItem != NULL);
 

	return true;
}
 
bool  RoleShapePropertyDataManager::VarifyAfterLoadAll()
{
   	return true;
}
 
bool  RoleShapePropertyDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	RoleShapePropertyData* pItemData = new RoleShapePropertyData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_RoleShapePropertyList.insert(std::map<int, RoleShapePropertyData*>::value_type(pItemData->roleShapeID_, pItemData));

	return true;
}












