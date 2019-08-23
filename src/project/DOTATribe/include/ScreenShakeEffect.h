#ifndef  _DOTATRIBE_SCREENSHAKEEFFECT_H_
#define  _DOTATRIBE_SCREENSHAKEEFFECT_H_
  
////////////////////////////////////////////////////////////////
//Name:	 ScreenShakeEffect
//Auchor: 	xiaobo.wu
//Func:	 屏幕震动特效动画
//Maintainer: 	xiaobo.wu
//date:  2013/07/28
////////////////////////////////////////////////////////////////

 
#include  <cocos2d.h> 
#include "../include/CommonEffect.h" 
 
class ShakeEffect;

class   ScreenShakeEffect : public CommonEffect,public ActionFinishCallProtocol
{
public:
	ScreenShakeEffect();
	~ScreenShakeEffect();
	enum
	{
		_CALLFUNC_UNKONW_TYPE_=-1,
		_CALLFUNC_ENTER_FINISH_PRO_TYPE_,
		_CALLFUNC_FINISH_CALL_TYPE_,
	};
public: 
	static  ScreenShakeEffect *  CreateScreenShakeEffect(int compositeEffectID,int screenShakeID);
	virtual  void   Tick();
	virtual  void   Destroy();
	virtual  void   Stop();
	virtual  void   OnCommandHanlder(int EventTypeID);
	virtual  void   OnBeginEffect();
	virtual  void   OnEndEffect();
	virtual  void   SetAnimationSpeedScale(float speedScale);
	virtual  void   OnActionFinishCalllHandler();
	virtual  bool   IsEffectLoop();
protected:
	bool    InitScreenShakeEffect(int compositeEffectID,int screenEffectID);
private: 
	ShakeEffect  * pSequenceAction;

};
 

#endif

