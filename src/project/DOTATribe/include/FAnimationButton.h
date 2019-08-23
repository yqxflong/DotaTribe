//name:FAnimationButton
//function:带播放动画的按钮
//author:fangjun
//date:20131206

#ifndef _PUBLIC_CONTROL_FANIMATIONBUTTON_H_
#define _PUBLIC_CONTROL_FANIMATIONBUTTON_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../include/MaskNode.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"

class FAnimationButton : public cocos2d::CCMenuItemSprite, public AnimationEffectCallBackProtocol
{
private:
	unsigned int m_nIDX;
	int m_nSoundID;
	int m_iAnimationId;//动画
	float m_fAnimationPosX;
	float m_fAnimationPosY;

	bool m_bIsPlaying;
	AnimationEffectCallBackProtocol * m_pAnimationEffectCallBack_Extra;
private:
	cocos2d::CCSprite * m_pAnimationPlayNode;//播放动画节点
	AnimationFileData * m_pAnimationFileData;//特效文件
	PAnimation_Call_Node m_pAnimationCallBack;//回调动画
	cocos2d::CCAnimation * m_pAnimation;//动画

public:
	FAnimationButton(){
		m_nIDX=0;
		m_nSoundID = -1;
		m_iAnimationId = 0;
		m_pAnimationPlayNode = NULL;
		m_pAnimationFileData = NULL;
		m_pAnimationCallBack = NULL;
		m_pAnimation = NULL;
		m_bIsPlaying = false;

		m_pAnimationEffectCallBack_Extra = NULL;

		InitAnimation();
	};
	~FAnimationButton(){};
	//With Selected Image Node
	static FAnimationButton* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	bool initWithNormalSprite(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCNode* disabledSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
	static FAnimationButton* create(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	bool initWithNormalImage(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	//
	void setIDX(unsigned int idx){
		m_nIDX=idx;
	}
	unsigned int getIDX() const{
		return m_nIDX;
	}
	//
	void setSoundID(int soundid){
		m_nSoundID=soundid;
	}

	void setAnimationId(int animationId)
	{
		m_iAnimationId = animationId;
	}

	void setAnimationPos(float posx, float posy)
	{
		m_fAnimationPosX = posx;
		m_fAnimationPosY = posy;
	}

	void setAnimationCallBack(AnimationEffectCallBackProtocol * callbackObject)
	{
		m_pAnimationEffectCallBack_Extra = callbackObject;
	}

public:
	virtual void EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

private:
	void InitAnimation();

public:
	void PlayAnimation();

	void StopAnimation();

public:
	/*
		播放声音
	*/
	void PlayTouchSound();

};

//用于动画按钮
class FAPriorityMenu:public cocos2d::CCMenu{
	bool m_bSwallow;
	int m_nPriority;

private:
	bool m_bTreatAsTabMenu;//是否把它当成tabmenu来对待。即按下拖动过程中不取消选中。

public:
	FAPriorityMenu()
	{
		m_bSwallow = false;
		m_nPriority = 0;
		m_bTreatAsTabMenu = false;
	};

public:
	static FAPriorityMenu* create(int priority,bool swallow=true){
		FAPriorityMenu* menu=new FAPriorityMenu;
		if (menu&&menu->init(priority,swallow))
		{
			menu->autorelease();
			return menu;
		}
		delete menu;
		menu = NULL;
		return menu;
	}
	bool init(int priority,bool swallow){
		if (CCMenu::init())
		{
			m_nPriority=priority;
			m_bSwallow=swallow;
			return true;
		}
		return false;
	}
	virtual void registerWithTouchDispatcher()
	{
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, m_bSwallow);
	}
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch,cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch,cocos2d::CCEvent* event);
	virtual	void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);

public:
	/*
		设置它为tabmenu
	*/
	void SetTreatAsTabMenu(bool treat);
};



//=========================================================================//
/*
	动画手动帧拦截节点的处理功能回调
*/
class FrameAnimationDelegate
{
public:
	virtual void FrameAnimationIntercept(int frameId, cocos2d::CCNode * node) = 0;

};
/*
	附带手动设置动画处理中间处理的节点
	例如一张图片从第几帧到第几帧需要透明度，在第几帧需要清楚角色
*/
class FrameAnimationNode : public cocos2d::CCNode
{
private:
	int m_iTotalFrames;
	int m_iFpsInAnimation;
	int m_iFpsInGame;

	std::list<int> m_lFrameIntercepts;
	FrameAnimationDelegate * m_pDelegate;
	int m_iFrameCount;	//帧开始计时
	bool m_bStartTick;	//开始播放计数

private:
	float m_frameScaleTime;		//	

private:
	FrameAnimationNode();

public:
	static FrameAnimationNode * create(int totalFrames, int fpsInAnimation, int fpsInGame);

	void InsertFrameIntercept(int frameId);

	void ClearAllIntercepts();

	void AddDelegate(FrameAnimationDelegate * dlg);

	void Tick();
	
	void Start();

};



#endif