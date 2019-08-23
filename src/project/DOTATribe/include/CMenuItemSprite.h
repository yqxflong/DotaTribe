//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: sprite+ selsprite
//
#ifndef  _DOTATRIBE_CMENUITEMSPRITE_H_
#define  _DOTATRIBE_CMENUITEMSPRITE_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/MaskNode.h"


//****************************基本按钮***********************************
class CMenuItemSprite:public cocos2d::CCMenuItemSprite{
protected:
	unsigned int m_nIDX;
	bool m_bIsSelected;
	int m_nSoundID;
	int m_nSelectedType;	//选中效果类型
	cocos2d::ccColor3B m_oldColor;
	int	m_nAttachData1;
	int m_nAttachData2;
public:
	enum{
		kSELECTEDTYPE_NORMAL=0,					//与父类一样，点击换图
		kSELECTEDTYPE_SCALETO_SMALL,			//点击变小
		kSELECTEDTYPE_SCALETO_BIG,				//点击变大
		kSELECTEDTYPE_FADE,						//点击渐变
		kSELECTEDTYPE_DARK,						//点击变暗
	};
	CMenuItemSprite();
	~CMenuItemSprite(){};
	//With No Image Node
	static CMenuItemSprite* create();
	bool init();
	//With Selected Image Node
	static CMenuItemSprite* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	bool initWithNormalSprite(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCNode* disabledSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
	//With Selected Image	 FileName
	static CMenuItemSprite* create(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	bool initWithNormalImage(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	//With Only norimage
	static CMenuItemSprite* create(const char* nor,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	bool initWithNormalImage(const char* nor,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector);
	//With Composite SelectedImage  Normal
	static CMenuItemSprite* createWithCompositeSelectedImage(const char* selImage,const char* norImage);
	bool initWithCompositeSelectedImage(const char* selImage,const char* norImage);
	//
	/*
		设置按钮选中类型
	*/
	void setSelectedType(unsigned int type){
		m_nSelectedType=type;
	}
	//
	void setIDX(unsigned int idx){
		m_nIDX=idx;
	}
	unsigned int getIDX() const{
		return m_nIDX;
	}
	//
	void setIsSelected(bool sel){
		m_bIsSelected=sel;
	}
	bool getIsSeleted() const{
		return m_bIsSelected;
	}
	//
	void setSoundID(int soundid){
		m_nSoundID=soundid;
	}
	void setAttachData1(int attachData){
		m_nAttachData1=attachData;
	} 
	int  getAttachData1(){
		return  m_nAttachData1;
	}
	void setAttachData2(int attachData){
		m_nAttachData2=attachData;
	} 
	int  getAttachData2(){
		return  m_nAttachData2;
	}

	/*
		设置NormalImage并重新定位
	*/
	void setNormalImageAndRelocation(cocos2d::CCNode* nor);
	void setNormalImageAndRelocation(std::string file);

	/*
		更换按钮图标
	*/
	void changeNormalAndSelectedImage(std::string nor,std::string sel);
private:
	void _scaleTo(float ss);
	void _fadeTo(GLubyte ff);
	void _scaleTo_active(float ss);
	void _fadeTo_active(GLubyte ff);
	void _darkTo(const cocos2d::ccColor3B& color);
	void _activeEvent();
public:
	/*
		播放声音
	*/
	void PlaySound();
	/*
		选中事件
	*/
	bool Selected_Event();
	/*
		取消选中事件
	*/
	void UnSelected_Event();
	/*
		取消选中事件=active
	*/
	void UnSelected_Event_Active();
};

//****************************带有Label的按钮***********************************
class CLabelButtonItem:public CMenuItemSprite
{
public:
	CLabelButtonItem();
	virtual ~CLabelButtonItem(){};
	static CLabelButtonItem* create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d::CCLabelTTF* lb);
	bool init(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d::CCLabelTTF* lb);
	//
	const char* GetLabelString();
	void SetLabelString(const char* txt);
protected:
private:
	cocos2d::CCLabelTTF* m_pLabel;
};


//用于普通按钮
class CPriorityMenu:public cocos2d::CCMenu{
	bool m_bSwallow;
	int m_nPriority;
public:
	static CPriorityMenu* create(int priority,bool swallow=true){
		CPriorityMenu* menu=new CPriorityMenu;
		if (menu&&menu->init(priority,swallow))
		{
			menu->autorelease();
			return menu;
		}
		delete menu;
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
	//
private:
	bool _checkTouchEnabled();
};

//用于TabBar
class CTabMenu:public cocos2d::CCMenu{
	bool m_bSwallow;
	int m_nPriority;
public:
	static CTabMenu* create(int priority,bool swallow=true){
		CTabMenu* menu=new CTabMenu;
		if (menu&&menu->init(priority,swallow))
		{
			menu->autorelease();
			return menu;
		}
		delete menu;
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
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch,cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch,cocos2d::CCEvent* event);
	virtual	void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

//用于TableView中
class CImmovableMenu:public cocos2d::CCImmovableMenu{
	bool m_bSwallow;
	int m_nPriority;
public:
	static CImmovableMenu* create(int priority,bool swallow=false){
		CImmovableMenu* menu=new CImmovableMenu;
		if (menu&&menu->init(priority,swallow))
		{
			menu->autorelease();
			return menu;
		}
		delete menu;
		return menu;
	}
	bool init(int priority,bool swallow){
		if (CCImmovableMenu::init())
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

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};


//TabMenuItem + ImmovableMenuItem 组合
class CTabImmovableMenu:public CImmovableMenu{
public:
	static CTabImmovableMenu* create(int priority,bool swallow=false){
		CTabImmovableMenu* menu=new CTabImmovableMenu;
		if (menu&&menu->init(priority,swallow))
		{
			menu->autorelease();
			return menu;
		}
		delete menu;
		return menu;
	}
	bool init(int priority,bool swallow){
		if (CImmovableMenu::init(priority,swallow))
		{
			return true;
		}
		return false;
	}
	//
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
protected:
	virtual bool ccTouchBegan_ccmenu(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

#endif