//Name：CommonNumberEffectManager
//Function：战斗数值动画管理器
//Author:	Johny

#ifndef   _DOTATRI_COMMONNUMBEREFFECTMANAGER_H_
#define   _DOTATRI_COMMONNUMBEREFFECTMANAGER_H_

#include   "../include/CommonNumberEffect.h" 
#include   "../include/HeroicRole.h"
#include   <cocos2d.h>
#include   <list>

 
class  HeroicRole;
class CommonNumberEffect;

class  CommonNumberEffectManager : public cocos2d::CCNode
{
public:
	CommonNumberEffectManager();
	~CommonNumberEffectManager();
public:
	//@标配
	virtual void  Init();
	virtual void  Tick();
	virtual void  Destroy();

	static   CommonNumberEffectManager *   CreateNumberEffectManager(HeroicRole  * pHeroicRole);
	void    AddNumberEffect(HeroicRole * pOwnRole,int numberType,int numbericalValue,int numberEffectID);
	void    SetDelayTime(float delayTime);
	float   GetDelatTime(); 
	void    SetAnimationSpeedScale(float speedScale);
	void    UpdateCacheList(float dt);
	void    StopAllActions();
    size_t  GetCurNumberEffectCount();
	bool	HadAllEffectTriggeredNumberUpdate();  
 
 
private:
	bool   m_isValid;					
	bool   m_isLoopCall;
	float  m_delayTime;
	std::list<CommonNumberEffect *>    runningNumberEffectList;	  //运行中队列
	std::list<CommonNumberEffect * >   cacheNumberEffectList;     //缓存队列   
 
};
 

#endif