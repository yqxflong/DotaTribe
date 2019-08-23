#ifndef  _DOTATRIBE_SCREENEFFECT_H_
#define  _DOTATRIBE_SCREENEFFECT_H_
 
////////////////////////////////////////////////////////////////
//Name:	 ScreenEffect
//Auchor: 	xiaobo.wu
//Func:	 屏幕特效
//Maintainer: 	xiaobo.wu
//date:   2013/07/28
////////////////////////////////////////////////////////////////
 
#include  "../include/BaseObject.h"
#include  "../include/CommonEffect.h"
#include  "../include/ScreenEffectDataManager.h"
#include  "../include/VariableSpeedSequenceAction.h"
#include  "../include/CallFuncAction.h"
#include  "../include/GradualColorAction.h"
#include  <cocos2d.h>

class   ScreenEffect: public CommonEffect ,public CallFunctionProtocol ,public ActionFinishCallProtocol
{
public:
    ScreenEffect();
	~ScreenEffect();
	enum
	{
		_CALLFUNC_UNKONW_TYPE_=-1,
		_CALLFUNC_ENTER_FINISH_PRO_TYPE_,
		_CALLFUNC_FINISH_CALL_TYPE_,
	};
public: 
	static  ScreenEffect *  CreateScreenEffectWithID(int compositeEffectID,int screenEffectID);
	virtual  void   Tick();
	virtual  void   Destroy();
	virtual  bool   IsEffectLoop();
	virtual  void   Stop();
	virtual  void   OnCommandHanlder(int EventTypeID);
	virtual  void   OnBeginEffect();
	virtual  void   OnEndEffect();
	virtual  void   SetAnimationSpeedScale(float speedScale);
	virtual  void   CallFunctionHandler(int eventType,void * attachParam);
	virtual  void   OnActionFinishCalllHandler();
protected:
    bool    InitScreenEffectWithID(int compositeEffectID,int screenEffectID);
	void    OnEnterFinishProcedure();
private:
	VariableSpeedSequenceAction * pSequenceAction;
	GradualColorAction * pLastFadeOutAction;
	ScreenEffectData	  *  pScreenEffectData;
	cocos2d::CCLayerColor *  pScreenEffectNode;
	bool  m_bIsEnterFinish;
};

#endif




