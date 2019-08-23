//Name：UnSkillNumbericProcedure
//Function： 非技能指令 数值动画流程
//Author:	Johny

#include <cocos2d.h>
#include  "../include/UnSkillNumbericalProcedure.h"
#include  "../include/HeroicRole.h"
#include  "../include/AthleticsSceneManager.h"
#include  "../include/SkillAttachLogicManager.h"
#include  "../include/AthleticsInstructionSystem.h"


UnSkillNumbericalProcedure::UnSkillNumbericalProcedure()
{
	SetSubObjectTypeID(CommonUnSkillItemProcedure::_UNSKILLPROCEDURE_NUMBERICAL_TYPE_);
}

UnSkillNumbericalProcedure::~UnSkillNumbericalProcedure()
{
    Destroy();
}


bool  UnSkillNumbericalProcedure::InitCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData)
{ 
	if(pAthleticsUnitData!=NULL)
	{
		m_pAthleticsUnitData=pAthleticsUnitData;
		curProcedureState=CommonUnSkillItemProcedure::_UNSKILLPROCEDURE_BEGIN_STATE_;
		OnBeginUnSkillProcedure();
		return true;
	}
	return  false;
}
 

void   UnSkillNumbericalProcedure::Tick()
{
	  CommonUnSkillItemProcedure::Tick();
}

void   UnSkillNumbericalProcedure::Destroy()
{
      SetObjectIsValid(false);
}
  

UnSkillNumbericalProcedure *   UnSkillNumbericalProcedure::CreateCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData)
{
	UnSkillNumbericalProcedure * pCommonUnSkillItemProcedure=new UnSkillNumbericalProcedure();
	if(pCommonUnSkillItemProcedure&&pCommonUnSkillItemProcedure->InitCommonUnSkillItemProcedure(pAthleticsUnitData))
	{
		return  pCommonUnSkillItemProcedure;
	}
	if(pCommonUnSkillItemProcedure!=NULL)
	{
		delete  pCommonUnSkillItemProcedure;
		pCommonUnSkillItemProcedure=NULL;
	}
	return NULL;
} 

void   UnSkillNumbericalProcedure::OnBeginUnSkillProcedure()
{
	curProcedureState=CommonUnSkillItemProcedure::_UNSKILLPROCEDURE_RUNNING_STATE_;
	//开始干活了
	if(m_pAthleticsUnitData!=NULL)
	{
		PAthleticData_Numberical  pAthleticDataNumberical=(PAthleticData_Numberical)m_pAthleticsUnitData->athleticsData;
		if(pAthleticDataNumberical!=NULL)
		{
			//附加逻辑指令 	
			std::vector<std::string>  attachParams;
			char attachParas[16]={0};
			sprintf(attachParas,"%d",-1);							  	   //特效无
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticDataNumberical->sourceType); //类型
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticDataNumberical->sourceID);   //目标
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticDataNumberical->numbericalValue);
			attachParams.push_back(attachParas);						   //数值
			int skillattachLogicType=-1;
			switch(m_pAthleticsUnitData->athleticsType)
			{
			case _ATHLETICSINSTRUCTION_RESTORE_HP_TYPE_:
				skillattachLogicType=_ATHLETICS_SKILL_TARGET_HP_HEAL_TYPE_;
				break;
			case _ATHLETICSINSTRUCTION_RESTORE_MP_TYPE_:
				skillattachLogicType=_ATHLETICS_SKILL_TARGET_MP_HEAL_TYPE_;
				break;
			case  _ATHLETICSINSTRUCTION_DAMAGE_HP_TYPE_:
				skillattachLogicType=_ATHLETICS_SKILL_TARGET_HP_DAMAGE_TYPE_;
				break;
			case  _ATHLETICSINSTRUCTION_DAMAGE_MP_TYPE_:
				skillattachLogicType=_ATHLETICS_SKILL_TARGET_MP_DAMAGE_TYPE_;
				break;
			default:
				break;
			}
			SkillAttachLogicManager::get_instance2()->OnCommandHandler(skillattachLogicType,attachParams,false,false);
		}
	}
	curProcedureState=CommonUnSkillItemProcedure::_UNSKILLPROCEDURE_NULL_STATE_;
}


void   UnSkillNumbericalProcedure::OnEndUnSkillProcedure()
{  
    Destroy();
	if(!AthleticsSceneManager::get_instance2()->IsGameOver())
	{
		AthleticsInstructionSystem::get_instance2()->OnCommandHandler(_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_);
	}
} 

bool   UnSkillNumbericalProcedure::OnCheckProcedureFinished()
{    
    bool  isAllRoleEffectFinish=true;
	HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	if(pHeroicRole)
	{  
		isAllRoleEffectFinish&=pHeroicRole->GetAllNumberEffectTriggered();
	}
	pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	if(pHeroicRole)
	{
		isAllRoleEffectFinish&=pHeroicRole->GetAllNumberEffectTriggered();
	} 
	return  isAllRoleEffectFinish;
}

 
 