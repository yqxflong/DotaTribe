////////////////////////////////////////////////////////////////
//Name:	 ScreenEffect
//Auchor: 	xiaobo.wu
//Func:	 屏幕特效
//Maintainer: 	xiaobo.wu
//date:   2013/07/28
////////////////////////////////////////////////////////////////
#include <cocos2d.h>
#include  "../include/ScreenEffect.h"
#include  "../include/AthleticsSceneManager.h"

using  namespace  cobra_win;

using  namespace cocos2d;

ScreenEffect::ScreenEffect()
{ 
   m_nEffectType=CommonEffect::_COMMONEFFECT_SCREEN_EFFECT_TYPE_;
   pSequenceAction=NULL;
   pLastFadeOutAction=NULL;
   pScreenEffectNode=NULL;
}

ScreenEffect::~ScreenEffect()
{ 
    
}
 

ScreenEffect *  ScreenEffect::CreateScreenEffectWithID(int compositeEffectID,int screenEffectID)
{
	 ScreenEffect * pScreenEffect=new ScreenEffect();
	 if(pScreenEffect&&pScreenEffect->InitScreenEffectWithID(compositeEffectID,screenEffectID))
	 { 
		 return pScreenEffect;
	 } 
	 if(pScreenEffect!=NULL)
	 {
		 delete pScreenEffect;
		 pScreenEffect=NULL;
	 }
	 return  NULL;
}

 

void    ScreenEffect::OnEnterFinishProcedure()
{
	m_bIsEnterFinish=true;
}


bool    ScreenEffect::InitScreenEffectWithID(int compositeEffectID,int screenEffectID)
{
	m_bIsEnterFinish=false;
	m_nCompositeEffectID=compositeEffectID;
	SetSubObjectID(screenEffectID);
	pScreenEffectNode=(cocos2d::CCLayerColor * )AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer()->getChildByTag(ScreenEffectTag);
	 pScreenEffectData=ScreenEffectDataManager::get_instance2()->GetScreenEffectByID(GetSubObjectID());
	if(pScreenEffectNode==NULL)
	{ 
		pScreenEffectNode=cocos2d::CCLayerColor::create();
		AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer()->addChild(pScreenEffectNode,pScreenEffectData->screenEffectZOrder,ScreenEffectTag);
	}
	if(pScreenEffectNode!=NULL)
	{ 
		if(pScreenEffectData!=NULL)
		{ 
			//重新更新ScreenEffect的位置 
			pScreenEffectNode->getParent()->reorderChild(pScreenEffectNode,pScreenEffectData->screenEffectZOrder);

			//设置ScreenEffect的初始颜色
			pScreenEffectNode->setColor(ccc3(0,0,0));
			pScreenEffectNode->setOpacity(0); 
			GradualColorAction * pFadeInAction=GradualColorAction::create(pScreenEffectData->screenEffectFadeInTime/1000,pScreenEffectData->GetScreenEffectColor().r,
				pScreenEffectData->GetScreenEffectColor().g,pScreenEffectData->GetScreenEffectColor().b,pScreenEffectData->GetScreenEffectColor().a);
			cocos2d::CCDelayTime * pDelayTimeAction=cocos2d::CCDelayTime::create(pScreenEffectData->screenEffectDurationTime/1000);
			CallFuncAction *      pEnterFinishCall=CallFuncAction::create(_CALLFUNC_ENTER_FINISH_PRO_TYPE_,this);
			GradualColorAction * pFadeOutAction=GradualColorAction::create(pScreenEffectData->screenEffectFadeInTime/1000,BLACK_COLOR_APHLE);
			pSequenceAction=VariableSpeedSequenceAction::create(pFadeInAction,pDelayTimeAction,pEnterFinishCall,pFadeOutAction,NULL);
			pSequenceAction->setActionFinishCallDelegate(this);
			pSequenceAction->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
			pScreenEffectNode->runAction(pSequenceAction);

			return true;
		}
	}
	return false;
}

void   ScreenEffect::Tick()
{
	 CommonEffect::Tick();
}

void  ScreenEffect::OnBeginEffect()
{

}

void ScreenEffect::OnEndEffect()
{
	m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
    SetIsValid(false);
	Destroy();
}

/*
终止特效
*/
void   ScreenEffect::Stop()
{
	if(!m_bIsEnterFinish)
	{
		pSequenceAction->setForceDelete(true);
		pSequenceAction=NULL;
		pScreenEffectNode=(cocos2d::CCLayerColor * )AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer()->getChildByTag(ScreenEffectTag);
		if(pScreenEffectNode!=NULL)
		{
			pLastFadeOutAction=GradualColorAction::create(pScreenEffectData->screenEffectFadeInTime/1000,BLACK_COLOR_APHLE);
			pLastFadeOutAction->setActionFinishCallDelegate(this);
			pLastFadeOutAction->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
			pScreenEffectNode->runAction(pLastFadeOutAction);
		}
		else
		{
			OnEndEffect();
		}
	}
}

bool   ScreenEffect::IsEffectLoop()
{ 
   return true;
}

 
/*
特效销毁
*/
void ScreenEffect::Destroy()
{ 
	SetIsValid(false);
	m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
	if(pScreenEffectNode!=NULL)
	{
		pScreenEffectNode->setOpacity(0); 
		pScreenEffectNode=NULL;
	}
	if(pSequenceAction!=NULL)
	{
		pSequenceAction->setForceDelete(true);
		pSequenceAction=NULL;
	}
	if(pLastFadeOutAction!=NULL)
	{
		pLastFadeOutAction->setForceDelete(true);
		pLastFadeOutAction->setActionFinishCallDelegate(NULL);
		pLastFadeOutAction=NULL;
	}
}
   
 
void   ScreenEffect::OnCommandHanlder(int EventTypeID)
{

}
   
void   ScreenEffect::SetAnimationSpeedScale(float speedScale)
{
  if(pSequenceAction!=NULL)
  {
	  pSequenceAction->setSpeedScale(speedScale);
  }
  if(pLastFadeOutAction!=NULL)
  {
	  pLastFadeOutAction->setSpeedScale(speedScale);
  }
}
 
void  ScreenEffect::CallFunctionHandler(int eventType,void * attachParam)
{
	switch(eventType)
	{
	case  _CALLFUNC_ENTER_FINISH_PRO_TYPE_:
		{
			OnEnterFinishProcedure();
		}
		break;
	default:
		break;
	}
}
void  ScreenEffect::OnActionFinishCalllHandler()
{
	OnEndEffect();
}


