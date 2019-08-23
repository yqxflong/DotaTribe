#include "../include/DOTATribeApp.h"
#include "../include/RoleBaseDataManager.h"
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


RoleBaseData::RoleBaseData()
{

	 roleUniqueID_=0;                    //��ɫID
	 roleShapeID_=0;                     //����ID
	 memset(roleHeadIcon_,0,sizeof(roleHeadIcon_));		//ͷ��	
	 roleInitLevel_=0;                   //��ʼ�ȼ�
	 roleTypeId_=0;                      //����
	 roleWeaponID_=0;                    //����             
	 roleInitHP_=0;                      //Ѫ��
	 roleAttackValue_=0;                 //������
	 roleSpeedValue_=0;                  //�ٶ�
	 roleSkillTacticsID_=0;              //���ܲ���
	 roleForceValue_=0;                  //����֮
	 roleAgilityValue_=0;                //����ֵ
	 roleIntelligenceValue_=0;           //����ֵ
	 roleArmorValue_=0;                  //����ֵ 
	 roleSunderValue_=0;                 //�Ƽ�ֵ     
	 roleCritValue_=0;                   //����ֵ
	 roleToughnessValue_=0;              //����ֵ          
	 roleHitValue_=0;                    //����ֵ
	 roleDodgeValue_=0;                  //����ֵ
}

RoleBaseData::~RoleBaseData()
{

}

bool  RoleBaseData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(roleUniqueID_))
		return false;

    if(!parser.parser_int_value(roleShapeID_))
		return false;

	if (!parser.parser_string_value(roleHeadIcon_,sizeof(roleHeadIcon_)))
		return false;

	if(!parser.parser_int_value(roleInitLevel_))
		return false;

	if(!parser.parser_int_value(roleTypeId_))
		return false;

	if(!parser.parser_int_value(roleWeaponID_))
		return false;

	if(!parser.parser_int_value(roleInitHP_))
		return false;

	if(!parser.parser_int_value(roleAttackValue_))
		return false;

	if(!parser.parser_int_value(roleSpeedValue_))
		return false;

	if(!parser.parser_int_value(roleSkillTacticsID_))
		return false;

	if(!parser.parser_int_value(roleForceValue_))
		return false;

	if(!parser.parser_int_value(roleAgilityValue_))
		return false;

	if(!parser.parser_int_value(roleIntelligenceValue_))
		return false;

	if(!parser.parser_int_value(roleArmorValue_))
		return false;

	if(!parser.parser_int_value(roleSunderValue_))
		return false;

	if(!parser.parser_int_value(roleCritValue_))
		return false;

	if(!parser.parser_int_value(roleToughnessValue_))
		return false;

	if(!parser.parser_int_value(roleHitValue_))
		return false;

	if(!parser.parser_int_value(roleDodgeValue_))
		return false;

	return true; 
}




template<> RoleBaseDataManager* cobra_win::Singleton2<RoleBaseDataManager>::m_pMySelf = NULL;

RoleBaseDataManager::RoleBaseDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	 
}

RoleBaseDataManager::~RoleBaseDataManager()
{

}


RoleBaseData * RoleBaseDataManager::GetRoleBaseDataByID(int roleUniqueId)
{

	std::map<int,RoleBaseData*>::iterator shapeIter=m_RoleBaseDataMapList.find(roleUniqueId);
	if(shapeIter!=m_RoleBaseDataMapList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}

std::string   RoleBaseDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/rolebasedata.txt";

	return "rolebasedata";
} 


unsigned  int RoleBaseDataManager::GetSize()
{
	return m_RoleBaseDataMapList.size()*sizeof(RoleBaseData);
}


bool  RoleBaseDataManager::Init()
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


void  RoleBaseDataManager::Tick()
{

}


void  RoleBaseDataManager::Destroy()
{
	std::map<int, RoleBaseData*>::iterator iter   = m_RoleBaseDataMapList.begin();
	std::map<int, RoleBaseData*>::iterator iter_e = m_RoleBaseDataMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_RoleBaseDataMapList.clear();
} 


bool  RoleBaseDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	RoleBaseData* pRoleItem = (RoleBaseData*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  RoleBaseDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  RoleBaseDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	RoleBaseData* pItemData = new RoleBaseData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_RoleBaseDataMapList.insert(std::map<int, RoleBaseData*>::value_type(pItemData->roleUniqueID_, pItemData));

	return true;
}












