/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:   非技能移除Buffer (延迟移除)
//date:   2013/10/28
///////////////////////////////////////////////// 
#include "../include/UnSkillRemoveBufferProcedure.h"
#include "../include/AthleticsSceneManager.h"
#include "../include/AthleticsInstructionSystem.h"
#include "../include/ClientConstDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/AthleticProcedureDataType.h"
  

UnSkillRemoveBufferProcedure::UnSkillRemoveBufferProcedure()
{
	SetSubObjectTypeID(CommonUnSkillItemProcedure::_UNSKILLPROCEDURE_REMOVE_BUFFER_TYPE_);
	m_pAutoDelayAnimation=NULL;
	m_bHadTriggerCall=false;
}

UnSkillRemoveBufferProcedure::~UnSkillRemoveBufferProcedure()
{

}

UnSkillRemoveBufferProcedure * UnSkillRemoveBufferProcedure::CreateCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData)
{ 
	 UnSkillRemoveBufferProcedure  * pUnSkillRemoveBufferProcedure=new UnSkillRemoveBufferProcedure();
	 if(pUnSkillRemoveBufferProcedure&&pUnSkillRemoveBufferProcedure->InitCommonUnSkillItemProcedure(pAthleticsUnitData))
	 {  
		 return pUnSkillRemoveBufferProcedure;
	 }
	 if(pUnSkillRemoveBufferProcedure!=NULL)
	 {  
		 delete pUnSkillRemoveBufferProcedure;
		 pUnSkillRemoveBufferProcedure=NULL;
	 }
	 return NULL;
}

void   UnSkillRemoveBufferProcedure::autoDelayEventHandler(int eventType,void * pSender)
{ 
	//等待时间到
	if(eventType==_Move_Animation_Finish_Event_)
	{
	    OnDispatchEventHandler();
		OnEndUnSkillProcedure();
	} 
}


void   UnSkillRemoveBufferProcedure::OnDispatchEventHandler()
{
	if(m_pAthleticsUnitData!=NULL)
	{
		switch(m_pAthleticsUnitData->athleticsType)
		{
		case _ATHLETICSINSTRUCTION_REMOVE_EFFECT_TYPE_:
			{
				OnRemoveEffectHandler();
				break;
			} 
		case  _ATHLETICSINSTRUCTION_REMOVE_STATE_TYPE_:
			{
				OnRemoveStateHandler();
				break;
			}
		default:
			break;
		}  
	}
}


void   UnSkillRemoveBufferProcedure::OnRemoveEffectHandler()
{
	  m_bHadTriggerCall=true;
	  if(m_pAthleticsUnitData!=NULL)
	  {
		  PAthleticsData_Buffer   pAthleticsDataBuffer=(PAthleticsData_Buffer)m_pAthleticsUnitData->athleticsData;
		  if(pAthleticsDataBuffer!=NULL)
		  {
			  HeroicRole  *pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
			  if(pAthleticsDataBuffer->sourceID!=pHeroicRole->GetSubObjectID()||pAthleticsDataBuffer->sourceType!=pHeroicRole->getRoleType())
			  { 
				  pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
			  }
			  if(pHeroicRole!=NULL)
			  {
				  pHeroicRole->OnStopCommonEffect(pAthleticsDataBuffer->effectID);
			  }
		  }
	  }
	  
}

void   UnSkillRemoveBufferProcedure::OnRemoveStateHandler()
{ 
	//to do 
}
 

void   UnSkillRemoveBufferProcedure::Tick()
{
	 CommonUnSkillItemProcedure::Tick();

	  
}
void   UnSkillRemoveBufferProcedure::Destroy()
{    
	 SetObjectIsValid(false);
	 if(!m_bHadTriggerCall)
	 {  
		OnDispatchEventHandler();
	 }
	 if(m_pAutoDelayAnimation!=NULL)
	 { 
		 m_pAutoDelayAnimation->setForceDelete(true);
		 m_pAutoDelayAnimation=NULL;
	 }	
}
 

void   UnSkillRemoveBufferProcedure::OnBeginUnSkillProcedure()   //为了提速因此暂时废弃Tick中调用BeginUnSkill
{
	if(AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer()!=NULL)
	{ 
		float  defaultDelayTime=((float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_EFFECT_REMOVE_DELAY_TIME))/1000.0f;
		m_pAutoDelayAnimation=AutoDelayAnimation::create(defaultDelayTime,this);
		m_pAutoDelayAnimation->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
		AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer()->runAction(m_pAutoDelayAnimation);
	}  
}

void   UnSkillRemoveBufferProcedure::OnEndUnSkillProcedure()
{
	Destroy();
	if(!AthleticsSceneManager::get_instance2()->IsGameOver())
	{
		AthleticsInstructionSystem::get_instance2()->OnCommandHandler(_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_);
	}
}

bool   UnSkillRemoveBufferProcedure::OnCheckProcedureFinished()
{
	return false;
}

void   UnSkillRemoveBufferProcedure::OnCheckRoleIsDead()
{
	//不进行死亡检测
	return ;
}

bool   UnSkillRemoveBufferProcedure::InitCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData)
{
	if(pAthleticsUnitData!=NULL)
	{     
		m_bHadTriggerCall=false;
		//do something and Begin Procedure
		m_pAthleticsUnitData=pAthleticsUnitData;
		OnBeginUnSkillProcedure();
		return true;
	} 
	return false;
}

void   UnSkillRemoveBufferProcedure::SetSpeedScale(float speedScale)
{
	//设置速度参数
	if(m_pAutoDelayAnimation!=NULL)
	{
		m_pAutoDelayAnimation->setSpeedScale(speedScale);
	}

}