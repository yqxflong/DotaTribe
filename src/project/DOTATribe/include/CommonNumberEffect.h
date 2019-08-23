//Name：CommonNumberEffect
//Function：战斗数值动画
//Author:	Johny

#ifndef   _DOTATRIB_COMMONNUMBEREFFECT_H_
#define   _DOTATRIB_COMMONNUMBEREFFECT_H_


#include    "../include/BaseObject.h"
#include    "../include/MoveAnimation.h"
#include    "../include/NumberBufferDataManager.h"
#include    "../include/HeroicRole.h"
#include    "../include/ArtFontLabelBatchNode.h"
#include    "../include/VariableSpeedSequenceAction.h"
#include   <cocos2d.h>

/*
   _Move_Animation_Finish_Event_    默认 动画完成后回调事件类型  
*/

class  HeroicRole;

class    CommonNumberEffect: public BaseObject,public cocos2d::CCNode,public  MoveAnimationCallBackProtocol
{  
public:
	//回调事件类型
	enum
	{
      _NUMBEREFFECT_UNKONW_EVENT_TYPE_,	
	  _NUMBEREFFECT_FADEOUT_EVENT_TYPE_,
	  _NUMBEREFFECT_UPDATENUMBER_EVENT_TYPE_,
	};

	//数字特效状态机
	enum
	{
		_NUMBEREFFECT_UNKONW_STATE_,
		_NUMBEREFFECT_BEIGIN_STATE_,
		_NUMBEREFFECT_RUNNING_STATE_,
		_NUMBEREFFECT_END_STATE_,
	};

	//艺术字颜色
	enum
	{
	   _NUMBERTYPE_YELLOW_TYPE_=1,
	   _NUMBERTYPE_GREEN_TYPE_=2,
	   _NUMBERTYPE_RED_TYPE_=3,
	   _NUMBERTYPE_BLUE_TYPE=4,
	};

	enum
	{
	   _NUMBERTYPE_SUB_INDEX_VALUE_=10,			//减号
	   _NUMBERTYPE_ADD_INDEX_VALUE_=11,			//加号
	   _NUMBERTYPE_MISS_INDEX_VALUE_=16,		//闪避
	   _NUMBERTYPE_BLOCK_INDEX_VALUE_=17,		//格挡
	};
 
	CommonNumberEffect();
	virtual ~CommonNumberEffect();
public:
	//@标配
	virtual void  Init();
	virtual void  Tick();
	virtual void  Destroy();

	//@监听通知
	virtual void  OnCommandHanlder(int EventTypeID);

    virtual void  OnBeginNumberEffect();
	virtual void  OnEndNumberEffect();
 
	static CommonNumberEffect *  CreateCommonNumberEffect(HeroicRole *  parentNode,char numberType,int numberEffectID,int numbericalValue); 
	void   CallBackEventProtocol(int eventType,void * ptrParam);

	void   SetNumberEffectSpeedScale(float speedScale);
	float  GetNumberEffectSpeedScale();

	bool   GetHadTriggeredNumberUpdate();

protected:
	bool  InitCommonNumberEffect(HeroicRole *  parentNode,char numberType,int numberEffectID,int numbericalValue);  
    NumberBufferData *   GetNumberBufferData();

	void   StartFadeOutAnimation();
	void   UpdateNumbericalValue(); 

	void   DoNumberEffectAction(NumberBufferData * pNumberBufferData);

	void   InitArtFontIndexVector(bool bNeedUpdateNumber,NumberBufferData * pNumberBufferData);

protected:
	HeroicRole * m_parentNode;
	char  m_numberType;
	int   m_numbericalValue;
	char  m_curEffectState;
	ArtFontLabelBatchNode * m_pArtFontLabel;
	MoveAnimation *  m_pMoveAnimation;
	VariableSpeedSequenceAction * m_pNumberBufferEffect;
    float   m_speedScale;
	std::vector<int>  m_numberIndexVector;
	bool  m_bHadTriggeredNumberUpdate;
	bool  m_bNeedUpdateNumber;
	float m_fFadeOutDuration; 
};
 
#endif