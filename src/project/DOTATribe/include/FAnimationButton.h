//name:FAnimationButton
//function:�����Ŷ����İ�ť
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
	int m_iAnimationId;//����
	float m_fAnimationPosX;
	float m_fAnimationPosY;

	bool m_bIsPlaying;
	AnimationEffectCallBackProtocol * m_pAnimationEffectCallBack_Extra;
private:
	cocos2d::CCSprite * m_pAnimationPlayNode;//���Ŷ����ڵ�
	AnimationFileData * m_pAnimationFileData;//��Ч�ļ�
	PAnimation_Call_Node m_pAnimationCallBack;//�ص�����
	cocos2d::CCAnimation * m_pAnimation;//����

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
		��������
	*/
	void PlayTouchSound();

};

//���ڶ�����ť
class FAPriorityMenu:public cocos2d::CCMenu{
	bool m_bSwallow;
	int m_nPriority;

private:
	bool m_bTreatAsTabMenu;//�Ƿ��������tabmenu���Դ����������϶������в�ȡ��ѡ�С�

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
		������Ϊtabmenu
	*/
	void SetTreatAsTabMenu(bool treat);
};



//=========================================================================//
/*
	�����ֶ�֡���ؽڵ�Ĵ����ܻص�
*/
class FrameAnimationDelegate
{
public:
	virtual void FrameAnimationIntercept(int frameId, cocos2d::CCNode * node) = 0;

};
/*
	�����ֶ����ö��������м䴦��Ľڵ�
	����һ��ͼƬ�ӵڼ�֡���ڼ�֡��Ҫ͸���ȣ��ڵڼ�֡��Ҫ�����ɫ
*/
class FrameAnimationNode : public cocos2d::CCNode
{
private:
	int m_iTotalFrames;
	int m_iFpsInAnimation;
	int m_iFpsInGame;

	std::list<int> m_lFrameIntercepts;
	FrameAnimationDelegate * m_pDelegate;
	int m_iFrameCount;	//֡��ʼ��ʱ
	bool m_bStartTick;	//��ʼ���ż���

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