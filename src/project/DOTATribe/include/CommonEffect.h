//Name：CommonEffect
//Function：Dota公共特效基类
//Author:	Johny

#ifndef  _DODATRIBE_COMMONEFFECT_H_
#define	 _DODATRIBE_COMMONEFFECT_H_
 
#include <cocos2d.h>
#include "../include/BaseObject.h"
#include "../include/AnimationEffect.h"
#include <spine/spine-cocos2dx.h>
#include <spine/SpineCallBackEvent.h>
 
using namespace cocos2d;
 
class  CommonEffect: public  BaseObject ,public AnimationEffectCallBackProtocol,public cocos2d::CCNode
{
public:
	//@技能特效的状态机
	enum
	{
		_COMMONEFFECT_UNKONW_EFFECT_TYPE_=-1,			//未知特效类型
		_COMMONEFFECT_SOUND_EFFECT_TYPE_,				//音效
		_COMMONEFFECT_FRAME_ANIMATE_EFFECT_TYPE_,		//帧动画特效
		_COMMONEFFECT_PARTICLE_EFFECT_TYPE_,			//粒子动画特效
		_COMMONEFFECT_SKELETON_EFFECT_TYPE_,			//骨骼动画特效
		_COMMONEFFECT_SHAKE_EFFECT_TYPE_,				//屏幕震动特效
		_COMMONEFFECT_ROLE_EFFECT_TYPE_,				//角色颜色特效
		_COMMONEFFECT_SCREEN_EFFECT_TYPE_,				//屏幕颜色特效
	
	};
	 
	enum
	{
		_COMMONSKILLEFFECT_UNKONW_STATE_,				//未知动画状态
		_COMMONSKILLEFFECT_BEGINACTION_STATE_,			//开始动画状态
		_COMMONSKILLEFFECT_RUNNINGACTION_STATE_,		//运行中状态
		_COMMONSKILLEFFECT_PAUSEAACTION_STATE_,			//暂停状态
		_COMMONSKILLEFFECT_ENDACTION_STATE_,			//结束状态
	};
	
	enum
	{
		_COMMONEFFECT_DEFAULT_INVALID_=-1,				 //默认的非法数值
	};
	
	//@特效的挂点
	enum
	{ 
	   _COMMONEFFECT_UNKONW_BIND_TYPE_,					 //未知骨骼挂点
	   _COMMONEFFECT_ROLE_ROOT_TYPE_,					 //人物根节点挂点
	   _COMMONEFFECT_ROLE_BOND_TYPE_,					 //角色骨骼结点挂点
	   _COMMONEFFECT_SCREEN_CENTER_TYPE_,				 //屏幕中心挂点
	};
	CommonEffect();
	virtual ~CommonEffect();
public:
	//@标配
	virtual   void   Tick();
	virtual   void   Destroy(){};

	//@事件通知接口
	virtual   void   OnCommandHanlder(int EventTypeID){};

	//@特效相关接口
	virtual   void   OnBeginEffect(){};
	virtual   void   OnEndEffect(){};
	virtual	   void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr){};
 
	//@获得特效的初始坐标位置
	virtual   cocos2d::CCPoint  GetInitPosition();

	//@获得特效的类型
	virtual   int    GetEffectType();
	
	//@获得特效的配置ID
	virtual   int    GetEffectID();

	//@获得母特效配置ID
	virtual   int    GetCompositeEffectID();
	 
	//@判断是否为循环特效
	virtual   bool   IsEffectLoop();
	 
	//@获得骨骼绑定的名称
	virtual   std::string  GetEffectBindBoneName();
	 
	//@获得特效绑定类型
	virtual   short   GetEffectBindType();
	 
	//@判断是否为骨骼绑定特效
	virtual   bool   IsBoneBindEffect();
	
	//@判断是否位置跟随
	virtual   bool   IsLocationFollow();
	
	//@判断是否角度跟随
	virtual   bool   IsAngleFollow();
	
	//@设置动画播放速度 
	virtual   void   SetAnimationSpeedScale(float speedScale);
	
	//@更新特效位置
	virtual   void   UpdatePosition(cocos2d::CCPoint & position){};
	
	//@更新骨骼绑定特效位置和角度
	virtual   void   UpdateWithBone(cocos2d::extension::Bone * pBindBone){};
 
    //@判断特效是否X轴翻转
	virtual   bool   IsEffectFlipX();

	//@停止特效
	virtual   void   Stop(){};
	
	//@注册动画回调事件队列
	virtual  std::vector<PCallBack_Node>   RegisterCallBackEventVec();

	//@设置可视状态
	virtual  void SetVisible(bool isVisible=false){};

protected:
	int   m_nCurEffectState;
	int   m_nCompositeEffectID;
	int   m_nEffectType; 
	bool  m_bIsEffectFlipX;
	float m_fSpeedScale;
	bool  m_bIsLoopEffect;
	bool  m_bIsBoneEffect;
	bool  m_bIsLocationFollow;
	bool  m_bIsAngleFollow;
	short m_sEffectBindType;
	std::string m_sBoneName;
};


#endif



