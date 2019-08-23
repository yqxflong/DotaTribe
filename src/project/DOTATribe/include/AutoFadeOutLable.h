#ifndef   _DOTATRIBE_AUTOFADEOUTLABLE_H_
#define    _DOTATRIBE_AUTOFADEOUTLABLE_H_
 
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  自动渐隐Label管理器
//date:   2013/10/23
///////////////////////////////////////////////// 
#include  <cocos2d.h>
#include "../include/MoveAnimation.h"

class  ErrorTipsData;
 
class  AutoDelayProtocol
{
public:
	virtual void  autoDelayEventHandler(int eventType,void * pSender)=0;
};
  
/*
自动延时动画
*/
class  AutoDelayAnimation :public cocos2d::CCDelayTime
{
private:
	virtual void  update(float time);
	virtual void  step(float dt);
	void   checkTimerEvent(float time);
public:
	static AutoDelayAnimation* create(float d,AutoDelayProtocol * pDelegate=NULL,PCallBackVec pCallBackVec=NULL);
	virtual bool  initDuration(float d,AutoDelayProtocol * pDelegate=NULL,PCallBackVec pCallBackVec=NULL);
	virtual void  setSpeedScale(float speedScale);
	virtual ~AutoDelayAnimation(); 
private:
	AutoDelayProtocol  *   m_pAutoDelayDelage;
	PCallBackVec           m_pCallEventList;
	float				   m_fSpeedScale;
};
 
class  AutoFadeOutLabelManager:public AutoDelayProtocol
{
	enum
	{
		_AUTOLABEL_FADEOUT_TYPE_,
	};
protected: 
	cocos2d::CCLabelTTF * m_pShowLabel;
	cocos2d::CCSprite   * m_pBackSprite;
	bool				  m_bIsValid;
	ErrorTipsData *       m_pErrorTipsData;
	int				   	  m_nIndex;
public:
	AutoFadeOutLabelManager();
	~AutoFadeOutLabelManager();
	static AutoFadeOutLabelManager * CreateAutoFadeOutLabelManager(cocos2d::CCNode * pParent,int lableIndex,std::string message);
public:
	void  autoDelayEventHandler(int eventType,void * pSender);
	void  SetPosition(cocos2d::CCPoint position);
	void  AddParent(cocos2d::CCNode * pParent);
	void  Destroy();
	bool  GetIsValid();
	void  SetIndex(int layoutIndex);
	int   GetIndex();
protected:
	bool   InitAutoFadeOutLabelManager(cocos2d::CCNode * pParent,int lableIndex,std::string message);
	void   SetIsValid();
};



#endif

