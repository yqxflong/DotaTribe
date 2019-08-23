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


//****************************������ť***********************************
class CMenuItemSprite:public cocos2d::CCMenuItemSprite{
protected:
	unsigned int m_nIDX;
	bool m_bIsSelected;
	int m_nSoundID;
	int m_nSelectedType;	//ѡ��Ч������
	cocos2d::ccColor3B m_oldColor;
	int	m_nAttachData1;
	int m_nAttachData2;
public:
	enum{
		kSELECTEDTYPE_NORMAL=0,					//�븸��һ���������ͼ
		kSELECTEDTYPE_SCALETO_SMALL,			//�����С
		kSELECTEDTYPE_SCALETO_BIG,				//������
		kSELECTEDTYPE_FADE,						//�������
		kSELECTEDTYPE_DARK,						//����䰵
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
		���ð�ťѡ������
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
		����NormalImage�����¶�λ
	*/
	void setNormalImageAndRelocation(cocos2d::CCNode* nor);
	void setNormalImageAndRelocation(std::string file);

	/*
		������ťͼ��
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
		��������
	*/
	void PlaySound();
	/*
		ѡ���¼�
	*/
	bool Selected_Event();
	/*
		ȡ��ѡ���¼�
	*/
	void UnSelected_Event();
	/*
		ȡ��ѡ���¼�=active
	*/
	void UnSelected_Event_Active();
};

//****************************����Label�İ�ť***********************************
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


//������ͨ��ť
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

//����TabBar
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

//����TableView��
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


//TabMenuItem + ImmovableMenuItem ���
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