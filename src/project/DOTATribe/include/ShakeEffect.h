
////////////////////////////////////////////////////////////////
//Name:	 ShakeEffect
//Auchor: 	qiang.yin
//Func:	 震动动画
//Maintainer: 	xiaobo.wu
//date:   2014/01/02
////////////////////////////////////////////////////////////////

#ifndef _DOTATRIBE_SHAKEEFFECT_H_
#define _DOTATRIBE_SHAKEEFFECT_H_

#include   <cocos2d.h>

using namespace cocos2d;
 
class  ShakeEffect : public  CCActionInterval
{
public:
  ShakeEffect();
  virtual ~ShakeEffect(){};
  
public:
	static ShakeEffect * CreateShakeEffect(int shakeID);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void step(float dt);
	virtual void stop(void);
	virtual void setSpeedScale(float speedScale);
protected:
	void CALLFUNC_EVENT();
	bool   InitShakeEffect(int shakeID);
	inline void _playEffect();
private:
	float m_fSpeedScale;
	bool m_bIsFinish;
	float m_fHalfCircleTime;		//半周期时间
	CCPoint m_startPosition;		//原始位置
	float m_fShakeX;
	float m_fShakeY;
	CCActionInterval * seq;
};

#endif