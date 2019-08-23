////////////////////////////////////////////////////////////////
//Name:	 RoleEffect
//Auchor: 	xiaobo.wu
//Func:	 角色人物特效
//Maintainer: 	xiaobo.wu
//date:    2013/10/28
////////////////////////////////////////////////////////////////
#include   <cocos2d.h>
#include   "../include/RoleEffect.h" 
#include   "../include/HeroicRole.h"
#include   "../include/VariableSpeedSequenceAction.h"
#include   "../include/GradualColorAction.h"
  
 

RoleEffect::RoleEffect()
{ 
    m_pHeroicRole=NULL;
	m_nEffectType=CommonEffect::_COMMONEFFECT_ROLE_EFFECT_TYPE_;
	m_pLastFadeOutAction=NULL;
}

RoleEffect::~RoleEffect()
{
     Destroy();
} 
  
void   RoleEffect::Tick()
{
    CommonEffect::Tick();
}

void   RoleEffect::Destroy()
{
	if(!IsValid())
	 return ;
	SetIsValid(false);
	if(m_pHeroicRole!=NULL)
	{
		m_pHeroicRole->getRoleSkeletonNode()->setColor(ccc3(255,255,255));
		m_pHeroicRole->getRoleSkeletonNode()->setOpacity(255);
	}
	m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
	if(m_pVariableSpeedSequenceAction!=NULL)
	{
		m_pVariableSpeedSequenceAction->setForceDelete(true);
		m_pVariableSpeedSequenceAction->setActionFinishCallDelegate(NULL);
		m_pVariableSpeedSequenceAction=NULL;
	}
	if(m_pLastFadeOutAction!=NULL)
	{ 
		m_pLastFadeOutAction->setForceDelete(true);
		m_pLastFadeOutAction=NULL;
	}
	m_pHeroicRole=NULL;
	 
}

void   RoleEffect::OnCommandHanlder(int EventTypeID)
{

}

void   RoleEffect::OnBeginEffect()
{  
      
}

void   RoleEffect::OnEndEffect()
{
	m_nCurEffectState=_COMMONSKILLEFFECT_ENDACTION_STATE_;
	SetIsValid(false);
	Destroy();
}

 
bool   RoleEffect::IsEffectLoop()
{
     return true;
}


void   RoleEffect::SetAnimationSpeedScale(float speedScale)
{
     if(m_pVariableSpeedSequenceAction!=NULL)
	 {
		 m_pVariableSpeedSequenceAction->setSpeedScale(speedScale);
	 }
}

void  RoleEffect::CallFunctionHandler(int eventType,void * attachParam)
{
	switch(eventType)
	{
	case _CALLFUNC_ENTER_FINISH_TYPE_:
		{ 
			HadEnterFinishProcedue();
			break;
		}
	default:
		break;
	}
}


void   RoleEffect::OnActionFinishCalllHandler()
{
	OnEndEffect();
}

 
RoleEffect *  RoleEffect::CreateRoleEffect(int compositeEffectID,HeroicRole * pHeroicRole,int roleEffectID)
{
	RoleEffect * pRoleEffect=new RoleEffect();
	if(pRoleEffect&&pRoleEffect->InitRoleEffect(compositeEffectID,pHeroicRole,roleEffectID))
	{
		return pRoleEffect;
	}
	if(pRoleEffect!=NULL)
	{
		delete pRoleEffect;
		pRoleEffect=NULL;
	}
	return NULL;
}

bool	RoleEffect::InitRoleEffect(int compositeEffectID,HeroicRole * pHeroicRole,int roleEffectID)
{
   if(pHeroicRole!=NULL)
   {
	    m_bIsEnterFinish=false;
        SetSubObjectID(roleEffectID);
		m_nCompositeEffectID=compositeEffectID;
		m_pHeroicRole=pHeroicRole;
		m_nCurEffectState=_COMMONSKILLEFFECT_RUNNINGACTION_STATE_;
		m_pRoleEffectData=RoleEffectDataManager::get_instance2()->GetRoleEffectDataByID(roleEffectID);
		if(m_pRoleEffectData!=NULL)
		{  
		    GradualColorAction * pFadeInAction=GradualColorAction::create(m_pRoleEffectData->roleEffectFadeInTime/1000,m_pRoleEffectData->GetRoleEffectColor().r,
				m_pRoleEffectData->GetRoleEffectColor().g,m_pRoleEffectData->GetRoleEffectColor().b,m_pRoleEffectData->GetRoleEffectColor().a);
			cocos2d::CCDelayTime * pDelayAction=cocos2d::CCDelayTime::create(m_pRoleEffectData->roleEffectDurationTime/1000);
			CallFuncAction *  pEnterFinishCall=CallFuncAction::create(_CALLFUNC_ENTER_FINISH_TYPE_,this);
			GradualColorAction * pFadeOutAction=GradualColorAction::create(m_pRoleEffectData->roleEffectFadeOutTime/1000,WHITE_COLOR_NO_APHLE);
			m_pVariableSpeedSequenceAction=VariableSpeedSequenceAction::create(pFadeInAction,pDelayAction,pEnterFinishCall,pFadeOutAction,NULL);
			if(m_pVariableSpeedSequenceAction!=NULL)
			{
				m_pVariableSpeedSequenceAction->setActionFinishCallDelegate(this);
				m_pVariableSpeedSequenceAction->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
				m_pHeroicRole->getRoleSkeletonNode()->runAction(m_pVariableSpeedSequenceAction);
				return true;
			}
		}
   }
   return false;
}
 
void   RoleEffect::HadEnterFinishProcedue()
{
	m_bIsEnterFinish=true;
}
 
 
void   RoleEffect::Stop()
{
	//用于移除服务器指定的特效
	if(!m_bIsEnterFinish)
	{ 
		m_pVariableSpeedSequenceAction->setForceDelete(true);
		m_pVariableSpeedSequenceAction->setActionFinishCallDelegate(NULL);
		m_pVariableSpeedSequenceAction=NULL;

		m_pLastFadeOutAction=GradualColorAction::create(m_pRoleEffectData->roleEffectFadeOutTime/1000,WHITE_COLOR_NO_APHLE);
		m_pLastFadeOutAction->setActionFinishCallDelegate(this);
		m_pLastFadeOutAction->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
		m_pHeroicRole->getRoleSkeletonNode()->runAction(m_pLastFadeOutAction);
	}
}



