#ifndef   _DOTATRIBE_FRAMEANIMATEEFFECT_H_ 
#define   _DOTATRIBE_FRAMEANIMATEEFFECT_H_

////////////////////////////////////////////////////////////////
//Name:	 FrameAnimationEffect
//Auchor: 	xiaobo.wu
//Func:	 战斗时 帧动画特效
//Maintainer: 	xiaobo.wu
//date:   2013/09/23
////////////////////////////////////////////////////////////////
 
#include  <cocos2d.h>
#include  <cocos-ext.h>
#include "../include/CommonEffect.h"
#include "../include/FrameAnimateDataManager.h"
#include <spine/spine-cocos2dx.h>
#include <spine/SpineCallBackEvent.h>
#include <spine/Bone.h>

using namespace cocos2d;
using namespace cocos2d::extension; 

class  FrameAnimateEffect: public CommonEffect
{
	enum
	{
		_FRAMEEFFECT_UNLOOP_TYPE_,		//非循环特效
		_FRAMEEFFECT_LOOP_TYPE_,		//循环特效
	};
public:
	FrameAnimateEffect();
	~FrameAnimateEffect();
public:
	static FrameAnimateEffect *  CreateFrameAnimateEffect(int compositeEffectID,int effectID,bool isFlipX=false);
	static FrameAnimateEffect *  CreateFrameAnimateEffectWithBone(int compositeEffectID,int effectID,bool isFlipX=false,cocos2d::extension::Bone * pBindBone=NULL);
protected:
	bool  InitFrameAnimateEffect(int compositeEffectID,int effectID,bool isFlipX=false,cocos2d::extension::Bone * pBindBone=NULL);
	bool  InitFrameAnimateEffectWithBone(int compositeEffectID,int effectID,bool isFlipX=false,cocos2d::extension::Bone * pBindBone=NULL);
public:
	/*
	 帧驱动
	*/
	virtual   void   Tick();

    /*
	 特效销毁 资源释放
    */
	virtual   void   Destroy();

	/*
	  事件通知接口
	*/
	virtual   void   OnCommandHanlder(int EventTypeID);

	/*
	开始技能动画
	*/
	virtual   void   OnBeginEffect();

 
	/*
	结束技能动画
	*/
	virtual   void   OnEndEffect();
 
	/*
	技能动画时间回调接口
	*/
	virtual	   void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
	
	/*
	 获得特效的初始坐标位置
	*/
	virtual   cocos2d::CCPoint  GetInitPosition();
	  
	/*
	设置动画播放速度 
	*/
	virtual   void   SetAnimationSpeedScale(float speedScale);
	
	/*
	更新特效位置
	*/
	virtual   void   UpdatePosition(cocos2d::CCPoint & position);
	
	/*
	更新骨骼绑定特效位置和角度
	*/
	virtual   void   UpdateWithBone(cocos2d::extension::Bone * pBindBone);
  
	/*
	注册动画回调事件队列
	*/ 
	virtual  std::vector<PCallBack_Node>   RegisterCallBackEventVec();
	 
	/*
	判断宿主是否已经死亡
	*/
	bool   IsOwnHadDead();
	 
protected:
	std::string  GetFrameAnimationName();
	float        GetFrameAnimationScale();
	cocos2d::CCPoint GetAnimationBoneInitPosition(cocos2d::extension::Bone * pBindBone);
	cocos2d::CCSprite  *  m_pEffectNode;
	CCAnimationEffect  *  m_pAnimationEffect;
	FrameAnimateData   *  m_pFrameAnimateData;
	bool				  m_bEffectLoop;
};

 

#endif