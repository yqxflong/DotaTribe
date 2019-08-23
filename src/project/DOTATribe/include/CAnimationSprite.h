#ifndef _COCOS_ANIMATION_SPRITE_H
#define _COCOS_ANIMATION_SPRITE_H

#include  <cocos2d.h>
#include  "../include/AnimationEffect.h"

////////////////////////////////////////////////////////////////
//Name:	 CAnimationSprite
//Auchor: 	xiaobo.wu
//Func:	 动画精灵(用于建议动画播放)
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////


class  CAnimationSprite: public cocos2d::CCSprite,public AnimationEffectCallBackProtocol
{
public:
	CAnimationSprite();
	virtual ~CAnimationSprite();
public:
    static CAnimationSprite * createAnimationSpriteByID(int aniamtionID,bool isLoopEffect=false,AnimationEffectCallBackProtocol * pDelegate=NULL);
public:
	void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
	void  RegisterEventHandler(AnimationEffectCallBackProtocol * pDelegate);
	void  RegisterScriptEventHandler(int scriptEventHandler);
	void  PlayEffect();
	void  StopEffect();
	void  SetAnimationID(int animationID);
	virtual void setVisible(bool bVisible);
	void  SetIsUnLoopEffect(bool loopEnable);
protected:
	bool  initAnimationSpriteByID(int aniamtionID,bool isLoopEffect,AnimationEffectCallBackProtocol * pDelegate);
	void  PlaySound();
	void  StopSound();
protected:
	int								   m_nAnimationID;
	int								   m_nSoundID;
	AnimationEffectCallBackProtocol *  m_pDelegate;
	bool							   m_bIsLoopEffect;
	int								   m_nScriptEventHandler;
};

 

#endif
