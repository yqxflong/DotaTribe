//Name：CommonUnSkillItemProcedure
//Function：非技能指令流程(添加非技能公共流程 若侦测到角色死亡，等待死亡动作完成后离开)
//Author:	Johny

#include <cocos2d.h>
#include   "../include/CommonUnSkillItemProcedure.h"
#include   "../include/AthleticsSceneManager.h"
#include   "spine/SpineCallBackEvent.h"
 
CommonUnSkillItemProcedure::CommonUnSkillItemProcedure()
{
   objectType_=COMMON_UNSKILLPROCEDUER_OBJECT_TYPE;
   objectSubID_=_UNSKILLPROCEDURE_UNKONW_TYPE_;
   curProcedureState=_UNSKILLPROCEDURE_UNKONW_STATE_;
   hadPlayedRoleDead=false;
   bIsLeftRoleDead=false;
   m_pAthleticsUnitData=NULL;
   m_pExceptionRole=NULL;
}

CommonUnSkillItemProcedure::~CommonUnSkillItemProcedure()
{
   Destroy();
}


CommonUnSkillItemProcedure *  CommonUnSkillItemProcedure::CreateCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData)
{
     CommonUnSkillItemProcedure * pCommonUnSkillItemProcedure=new CommonUnSkillItemProcedure();
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
 
 
bool   CommonUnSkillItemProcedure::InitCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData)
{
     curProcedureState=_UNSKILLPROCEDURE_BEGIN_STATE_;
     return true;
}

void     CommonUnSkillItemProcedure::SetSubObjectTypeID(int subObjectID)
{
       objectSubID_=subObjectID;
}
void      CommonUnSkillItemProcedure::SetObjectIsValid(bool isValid)
{
        SetIsValid(isValid);
}


void CommonUnSkillItemProcedure::Tick()
{
	if(!IsValid())
	return ;
	BaseObject::Tick();

	if(curProcedureState==_UNSKILLPROCEDURE_END_STATE_)
	{
		OnEndUnSkillProcedure();
		return ;
	}
	else if(curProcedureState==_UNSKILLPROCEDURE_BEGIN_STATE_)
	{
        OnBeginUnSkillProcedure();
		return ;
	}
	else if(curProcedureState==_UNSKILLPROCEDURE_NULL_STATE_)
	{
    	OnCheckRoleIsDead();
		if(hadPlayedRoleDead)
		{
			//等待人物死亡动作完毕
			curProcedureState=_UNSKILLPROCEDURE_EXCEPTION_DEAD_STATE_;
			return ;
		}
		else if(OnCheckProcedureFinished())
		{
			curProcedureState=_UNSKILLPROCEDURE_END_STATE_;
			OnEndUnSkillProcedure();
			return ;
		}
	}
}

void CommonUnSkillItemProcedure::Destroy()
{
    hadPlayedRoleDead=false;
	SetIsValid(false);
}


//@指令接收处理
void   CommonUnSkillItemProcedure::OnCommandHanlder(int EventTypeID,std::string attachParam)
{
	if(EventTypeID==_Skeleton_Animation_Change_Event_)
	{    
		int actionID=atoi(attachParam.c_str());
		if(actionID==HeroicRole::SiWang)
		{
			UnRegisterSkeletonCompleteEventHandler();
			curProcedureState=_UNSKILLPROCEDURE_END_STATE_;
			OnEndUnSkillProcedure();
		} 
	}
}

 
void CommonUnSkillItemProcedure::OnBeginUnSkillProcedure()
{     

}

void CommonUnSkillItemProcedure::OnEndUnSkillProcedure()
{  
	Destroy();
}

bool CommonUnSkillItemProcedure::OnCheckProcedureFinished()
{
    return true;
}

void CommonUnSkillItemProcedure::OnCheckRoleIsDead()
{
	if(!hadPlayedRoleDead)
	{  
		if(CheckRoleExceptionEvent(true))
		 return ;
		if(CheckRoleExceptionEvent(false))
		 return	;
	}
} 

void     CommonUnSkillItemProcedure::UnRegisterSkeletonCompleteEventHandler()
{  
	if(m_pExceptionRole!=NULL)
	{
		m_pExceptionRole->unRegisterSkeletonEventDelegate(this);
	}
}

bool    CommonUnSkillItemProcedure::CheckRoleExceptionEvent(bool isLeftRole)
{
	HeroicRole * pHeroicRole=NULL;
	if(isLeftRole)
	pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	else
	pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	if(pHeroicRole&&!pHeroicRole->IsRoleLive())
	{
		if(!pHeroicRole->hadPlayedDeadAnimation()||!pHeroicRole->isAnimationComplete(HeroicRole::SiWang))
		{ 
			ThrowExceptionEvent(pHeroicRole);
			CCLOG("CommonUnSkillItemProcedure +  Make the role dead!");
			return  true;
		}  
	}
	return false;
}

void   CommonUnSkillItemProcedure::ThrowExceptionEvent(HeroicRole * pHeroicRole,bool isPlayAnimation/* =true */)
{
	hadPlayedRoleDead=true;
	pHeroicRole->registerSkeletonEventDelegate(this);
	m_pExceptionRole=pHeroicRole;
	if(isPlayAnimation)
	pHeroicRole->onPlayDeadAnimation();			
}




