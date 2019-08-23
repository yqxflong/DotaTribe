////////////////////////////////////////////////////////////////
//Name:	 CAnimationSprite
//Auchor: 	xiaobo.wu
//Func:	 动画精灵(用于建议动画播放)
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include  "../include/CAnimationSprite.h"
#include  "../include/EngineSystem.h"
#include  "../include/EventSystem.h"
#include  "../include/EventTyper.h"
#include  "../include/AnimationFileDataManager.h"

 

CAnimationSprite::CAnimationSprite()
{
	m_nSoundID=-1;
	m_nAnimationID=0;
	m_pDelegate=NULL;
	m_bIsLoopEffect=false;
	m_nScriptEventHandler = 0;
}

CAnimationSprite::~CAnimationSprite()
{
	this->stopAllActions();
}

CAnimationSprite * CAnimationSprite::createAnimationSpriteByID(int aniamtionID,bool isLoopEffect/* =false */,AnimationEffectCallBackProtocol * pDelegate/* =NULL */)
{
	CAnimationSprite * pAnimationSprite=new CAnimationSprite();
	if(pAnimationSprite&&pAnimationSprite->initAnimationSpriteByID(aniamtionID,isLoopEffect,pDelegate))
	{
		pAnimationSprite->autorelease();
		return pAnimationSprite;
	}
	CC_SAFE_DELETE(pAnimationSprite);
	return  NULL;
}

void  CAnimationSprite::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	if(eventType==_Animation_Effect_Finish_Event_)
	{ 
		if(!m_bIsLoopEffect)
		{
			StopEffect();
			if(m_pDelegate)
			{
		        m_pDelegate->EffectCallBackEventHandler(eventType,animationNode,ptr);
			}
			if(m_nScriptEventHandler)
			{  
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptEventHandler, "EffectCallBackEventHandler", eventType, "", animationNode, "CCNode");
			}
		}
	}
	else
	{
		if(m_pDelegate)
		{
			m_pDelegate->EffectCallBackEventHandler(eventType,animationNode,ptr);
		}
		if(m_nScriptEventHandler)
		{
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptEventHandler, "EffectCallBackEventHandler", eventType, "", animationNode, "CCNode");
		}   
	}
}
	
void  CAnimationSprite::RegisterEventHandler(AnimationEffectCallBackProtocol * pDelegate)
{
	m_pDelegate=pDelegate;
}

void  CAnimationSprite::RegisterScriptEventHandler(int scriptEventHandler)
{
	m_nScriptEventHandler = scriptEventHandler;
}

void  CAnimationSprite::PlayEffect()
{
	this->stopAllActions();
	cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(m_nAnimationID);
	AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(m_nAnimationID);
	this->setScale(pAnimationData->mAnimationScale);
	CCAnimationEffect * pAnimationEffect=CCAnimationEffect::create(this,pAnimation,this);
	if(m_bIsLoopEffect)
	{
		cocos2d::CCRepeatForever * pRepeatAction=cocos2d::CCRepeatForever::create(pAnimationEffect);
		this->runAction(pRepeatAction);
	}
	else
	{
		this->runAction(pAnimationEffect);
	} 
	PlaySound();
	this->setVisible(true);
}
void  CAnimationSprite::StopEffect()
{
	this->stopAllActions();
	this->setVisible(false);
	StopSound();
}

void  CAnimationSprite::SetAnimationID(int animationID)
{
	m_nAnimationID=animationID;
	AnimationFileData * pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(m_nAnimationID);
	if(pAnimationFileData)
	m_nSoundID=pAnimationFileData->mAnimationUISoundID;
}

void  CAnimationSprite::setVisible(bool bVisible)
{ 
	//to do
	CCSprite::setVisible(bVisible);
}

bool  CAnimationSprite::initAnimationSpriteByID(int aniamtionID,bool isLoopEffect,AnimationEffectCallBackProtocol * pDelegate)
{
	if(CCSprite::init())
	{
		m_nAnimationID=aniamtionID;
		m_pDelegate=pDelegate; 
		m_bIsLoopEffect=isLoopEffect;
		//初始化音效ID
		AnimationFileData * pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(m_nAnimationID);
		if(pAnimationFileData)
		m_nSoundID=pAnimationFileData->mAnimationUISoundID;
		return true;
	}
	return false;
}

void  CAnimationSprite::PlaySound()
{
	//关闭之前相同音效
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_, _to_event_param_(m_nSoundID)); 
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(m_nSoundID)); 

}

void  CAnimationSprite::StopSound()
{
	//关闭音效
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_, _to_event_param_(m_nSoundID)); 
}

 
void  CAnimationSprite::SetIsUnLoopEffect(bool loopEnable)
{
	m_bIsLoopEffect=loopEnable;
	PlayEffect();
}