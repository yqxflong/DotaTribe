////////////////////////////////////////////////////////////////
//Name:	 ScreenShakeEffect
//Auchor: 	xiaobo.wu
//Func:	 屏幕震动特效动画
//Maintainer: 	xiaobo.wu
//date:  2013/07/28
////////////////////////////////////////////////////////////////
#include "../include/ScreenShakeEffect.h"
#include "../include/ShakeEffect.h"
#include  "../include/AthleticsSceneManager.h"

using  namespace cocos2d;


ScreenShakeEffect::ScreenShakeEffect()
{
	m_nEffectType=CommonEffect::_COMMONEFFECT_SHAKE_EFFECT_TYPE_;
	pSequenceAction=NULL;
}


ScreenShakeEffect::~ScreenShakeEffect()
{
	Destroy();
}

 ScreenShakeEffect *  ScreenShakeEffect::CreateScreenShakeEffect(int compositeEffectID,int screenShakeID)
 {
	  ScreenShakeEffect * pScreenShakeEffect=new ScreenShakeEffect();
	  if(pScreenShakeEffect&&pScreenShakeEffect->InitScreenShakeEffect(compositeEffectID,screenShakeID))
	  {
		  return pScreenShakeEffect;
	  }
	  return NULL;
 }

 bool   ScreenShakeEffect::InitScreenShakeEffect(int compositeEffectID,int screenEffectID)
 {
	   m_nCompositeEffectID=compositeEffectID;
	   SetSubObjectID(screenEffectID);
	   pSequenceAction=ShakeEffect::CreateShakeEffect(screenEffectID);
	   cocos2d::CCNode * pAthleticsRootLayer=AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer();
	   if(pSequenceAction!=NULL&&pAthleticsRootLayer!=NULL)
	   { 
			pSequenceAction->setActionFinishCallDelegate(this);
			pSequenceAction->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
			pAthleticsRootLayer->runAction(pSequenceAction);
		   return true;
	   }
	   return false;
 }
  
 void   ScreenShakeEffect::Tick()
 {
	 CommonEffect::Tick();
 }
void   ScreenShakeEffect::Destroy()
{
	 SetIsValid(false);
	 m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
	 if(pSequenceAction!=NULL)
	 { 
		 pSequenceAction->stop();
		 pSequenceAction->setForceDelete(true);
		 pSequenceAction=NULL;
	 }
}

void   ScreenShakeEffect::Stop()
{

}

bool   ScreenShakeEffect::IsEffectLoop()
{
	return  true;
}


 void   ScreenShakeEffect::OnCommandHanlder(int EventTypeID)
 {

 }
 void   ScreenShakeEffect::OnBeginEffect()
 {

 }
 void   ScreenShakeEffect::OnEndEffect()
 {
	 m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
	 SetIsValid(false);
	 Destroy();
 }
 void   ScreenShakeEffect::SetAnimationSpeedScale(float speedScale)
 {
	 if(pSequenceAction!=NULL)
	 {
		 pSequenceAction->setSpeedScale(speedScale);
	 }
 }
  
void ScreenShakeEffect::OnActionFinishCalllHandler()
{
	OnEndEffect();
}

  
