#ifndef   _DOTATRIBE_ROLEEFFECT_H_
#define   _DOTATRIBE_ROLEEFFECT_H_

////////////////////////////////////////////////////////////////
//Name:	 RoleEffect
//Auchor: 	xiaobo.wu
//Func:	 角色人物特效
//Maintainer: 	xiaobo.wu
//date:    2013/10/28
////////////////////////////////////////////////////////////////
  
#include   "../include/CommonEffect.h"
#include   "../include/RoleEffectDataManager.h"
#include   "../include/AthleticsSceneManager.h"
#include   "../include/CallFuncAction.h" 
#include   <cocos2d.h>

class  GradualColorAction;
class  VariableSpeedSequenceAction;
class  HeroicRole;
 
class  RoleEffect: public CommonEffect,public CallFunctionProtocol,public ActionFinishCallProtocol
{
public:
	RoleEffect();
	~RoleEffect();
	enum
	{
		_CALLFUNC_UNKONW_TYPE_=-1,
		_CALLFUNC_ENTER_FINISH_TYPE_,
		_CALLFUNC_FINISH_CALL_TYPE_,
	};
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
	是否循环特效
	*/
	virtual   bool   IsEffectLoop();
	 
	/*
	设置动画播放速度 
	*/
	virtual   void   SetAnimationSpeedScale(float speedScale);

	/*
	CallFunction回调函数
	*/
	virtual void  CallFunctionHandler(int eventType,void * attachParam);

	/*
	动画删除回调事件通知
	*/
	virtual void   OnActionFinishCalllHandler();
	 
	/*
	 延时关闭动画函数 优雅之举
	*/
	virtual   void   Stop();

public: 

	static   RoleEffect *   CreateRoleEffect(int compositeEffectID,HeroicRole * pHeroicRole,int roleEffectID); 
protected:
    bool	InitRoleEffect(int compositeEffectID,HeroicRole * pHeroicRole,int roleEffectID); 
	void    HadEnterFinishProcedue();
protected:
	bool   m_bIsEnterFinish;
	HeroicRole * m_pHeroicRole; 
	RoleEffectData  * m_pRoleEffectData;
	GradualColorAction * m_pLastFadeOutAction;
	VariableSpeedSequenceAction  * m_pVariableSpeedSequenceAction;
};

#endif