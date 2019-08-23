#include "../include/DOTATribeApp.h"
#include "../include/SkillEffectDataManager.h"
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


SkillEffectData::SkillEffectData()
{
    skillEffectItemID=0;					    //��ЧID
    skillEffectZOrder=0;						//��Ч�Ĳ㼶
    skillEffecIsLoop=0;						    //��Ч�Ƿ�ѭ��
    skillEffectSoundTriggerTime=0.0f;			//��Ч��Ч����ʱ�� ��λΪMS
    skillEffectSoundID=0;						//��Ч����ЧID
    skillEffectAnchorPoint=0;					//��Ч�����ê��
    skillEffectXOffSet=0.0f;					//��Ч��X��ƫ��
	skillEffectYOffSet=0.0f;				 	//��Ч��Y��ƫ��
    skillEffectIsFollow=0;						//��Ч�Ƿ����
    skillEffectRoleEffectTime=0.0f;				//��Ч�����ɫ��Ч������ʱ���  ��λMS
    skillEffectRoleEffectID=0;					//��Ч��ɫЧ��ID
    skillEffectAnimationID=0;					//��Ч����ID
	skillEffectShakeTriggerTime=0.0f;			//��Ч�𶯴���ʱ���   ��λMS
	skillEffectShakeID=0;						//��Ч��ID

}

SkillEffectData::~SkillEffectData()
{

}

bool  SkillEffectData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(skillEffectItemID))
		return false;

	if (!parser.parser_short_value(skillEffectZOrder))
		return  false;

	if (!parser.parser_short_value(skillEffecIsLoop))
		return  false;

	if (!parser.parser_float_value(skillEffectSoundTriggerTime))
		return false;

	if (!parser.parser_int_value(skillEffectSoundID))
		return false;

	if (!parser.parser_short_value(skillEffectAnchorPoint))
		return false;

	if (!parser.parser_float_value(skillEffectXOffSet))
		return false;

	if (!parser.parser_float_value(skillEffectYOffSet))
		return false;

	if (!parser.parser_short_value(skillEffectIsFollow))
		return false;

	if (!parser.parser_float_value(skillEffectRoleEffectTime))
		return false;

	if (!parser.parser_int_value(skillEffectRoleEffectID))
		return false;

	if (!parser.parser_int_value(skillEffectAnimationID))
		return false;

	if (!parser.parser_float_value(skillEffectShakeTriggerTime))
		return false;

	if (!parser.parser_int_value(skillEffectShakeID))
		return false;

	return true; 
}



template<> SkillEffectDataManager* cobra_win::Singleton2<SkillEffectDataManager>::m_pMySelf = NULL;

SkillEffectDataManager::SkillEffectDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_skillEffectMapList_.clear();
}

SkillEffectDataManager::~SkillEffectDataManager()
{

}

SkillEffectData * SkillEffectDataManager::GetSkillEffectByID(int skillItemID)
{
	std::map<int,SkillEffectData*>::iterator skillIter=m_skillEffectMapList_.find(skillItemID);
	if(skillIter!=m_skillEffectMapList_.end())
	{
		return skillIter->second;
	}
	return NULL; 
}


std::string   SkillEffectDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/skilleffectdata.txt";

	return "skilleffectdata";
} 


unsigned  int SkillEffectDataManager::GetSize()
{
	return m_skillEffectMapList_.size()*sizeof(SkillEffectData);
}


bool  SkillEffectDataManager::Init()
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


void  SkillEffectDataManager::Tick()
{

}


void  SkillEffectDataManager::Destroy()
{
	std::map<int, SkillEffectData*>::iterator iter   = m_skillEffectMapList_.begin();
	std::map<int, SkillEffectData*>::iterator iter_e = m_skillEffectMapList_.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_skillEffectMapList_.clear();
} 


bool  SkillEffectDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	SkillEffectData* pRoleItem = (SkillEffectData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  SkillEffectDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  SkillEffectDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	SkillEffectData* pItemData = new SkillEffectData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_skillEffectMapList_.insert(std::map<int, SkillEffectData*>::value_type(pItemData->skillEffectItemID, pItemData));

	return true;
}