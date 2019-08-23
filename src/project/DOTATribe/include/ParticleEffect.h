#ifndef  _DOTATRIBE_PATICLEEFFECT_H_
#define  _DOTATRIBE_PATICLEEFFECT_H_

////////////////////////////////////////////////////////////////
//Name:	 ParicelEffect
//Auchor: 	xiaobo.wu
//Func:	 粒子特效
//Maintainer: 	xiaobo.wu
//date:   2013/09/22
////////////////////////////////////////////////////////////////
 
#include   <cocos2d.h>
#include   <spine/spine-cocos2dx.h>
#include "../include/CommonEffect.h"
#include <spine/SpineCallBackEvent.h>
#include <spine/Bone.h>

class  ParticleData ;

using  namespace  cocos2d;

class  ParticleEffect : public CommonEffect 
{
	enum
	{
		_PARTICLEEFFECT_SELFTIME_TYPE_,				//粒子固有时间播放
		_PARTICCLEFFECT_BIND_ACTION_TYPE_,			//绑定动作播放方式
		_PARTICLEEFFECT_LOOP_TYPE_,					//持续播放方式
	};
	enum
	{
		_PATICLEEFFECT_NOBLEND_MODE_,			    //无叠加模式
		_PATICLEEFFECT_BLEND_MODE_,					//启用混合模式
	};
public:
	ParticleEffect();
	~ParticleEffect();
public:
	virtual  void   Tick();
	virtual  void   Destroy();
	virtual  void   Stop();
	virtual  void   OnCommandHanlder(int EventTypeID);
	virtual  void   OnBeginEffect();
	virtual  void   OnEndEffect();
	virtual  void   SetAnimationSpeedScale(float speedScale);
	virtual  void   SetVisible(bool isVisible/* =false */);
public:
	static ParticleEffect *  CreateParticleEffect(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone=NULL);
	static ParticleEffect *  CreateParticleEffectWithBone(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone);
public:
	virtual   cocos2d::CCPoint  GetInitPosition();
	virtual   void   UpdatePosition(cocos2d::CCPoint & position);
	virtual   void   UpdateWithBone(cocos2d::extension::Bone * pBindBone);
protected:
	bool  InitParticleEffect(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone=NULL);
	bool  InitParticleEffectWithBone(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone);
protected:
	cocos2d::CCPoint GetAnimationBoneInitPosition(cocos2d::extension::Bone * pBindBone);
protected: 
	ParticleData *			m_pParticleEffectData;
	CCParticleSystemQuad *  m_pParticleEffectNode;
	bool				    m_bIsHandover;       	//是否拖尾
	short					m_nEffectPlayType;		//播放方式
};
	  

#endif



