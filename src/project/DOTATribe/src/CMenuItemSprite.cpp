//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: sprite+ selsprite
//

#include "../include/CMenuItemSprite.h"
#include <cocos-ext.h>
#include "../include/CSelectedSprite.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include "../include/UISystem.h"

USING_NS_CC;
USING_NS_CC_EXT;


//****************************基本按钮***********************************
static const ccColor3B& BTN_GRAY=ccc3(150,150,150);

CMenuItemSprite::CMenuItemSprite()
:m_nIDX(0)
,m_bIsSelected(0)
,m_nSoundID(-1)
,m_nSelectedType(0)
,m_nAttachData1(0)
,m_nAttachData2(0)
{

};

//With No Image Node
CMenuItemSprite* CMenuItemSprite::create(){
	CMenuItemSprite* cc=new CMenuItemSprite();
	if (cc&&cc->init())
	{
		cc->autorelease();
		return cc;
	}
	CC_SAFE_DELETE(cc);
	return NULL;
}

bool CMenuItemSprite::init(){

	return CCMenuItemSprite::init();
}


CMenuItemSprite* CMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector){
	CMenuItemSprite *cc=new CMenuItemSprite();
	if (cc&&cc->initWithNormalSprite(normalSprite,selectedSprite,NULL,target,selector))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool CMenuItemSprite::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector){
	if (CCMenuItemSprite::initWithNormalSprite(normalSprite,selectedSprite,disabledSprite,target,selector))
	{
		if (normalSprite&&selectedSprite)
		{
			float scale_nor=normalSprite->getScale();
			float scale_sel=selectedSprite->getScale();
			const CCSize &sz_nor=normalSprite->getContentSize();
			const CCSize &sz_sel=selectedSprite->getContentSize();
			selectedSprite->setPosition(ccp((sz_nor.width*scale_nor-sz_sel.width*scale_sel)/2,(sz_nor.height*scale_nor-sz_sel.height*scale_sel)/2));
		}
		return true;
	}
	return false;
}

CMenuItemSprite* CMenuItemSprite::create(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector){
	CMenuItemSprite* cc=new CMenuItemSprite();
	if (cc&&cc->initWithNormalImage(nor,sel,target,selector))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CMenuItemSprite::initWithNormalImage(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector){
	CCSprite* cc_nor=NULL;
	if (strcmp(nor,"0")!=0)
	{
		cc_nor=CCSprite::create();
		cc_nor->setProperty("File",nor);
	}
	CCSprite* cc_sel=NULL;
	if (strcmp(sel,"0")!=0)
	{
		cc_sel=CCSprite::create();
		cc_sel->setProperty("File",sel);
	}
	return initWithNormalSprite(cc_nor,cc_sel,NULL,target,selector);
}

CMenuItemSprite* CMenuItemSprite::create(const char* nor,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector){
	CMenuItemSprite* cc=new CMenuItemSprite();
	if (cc&&cc->initWithNormalImage(nor,target,selector))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool CMenuItemSprite::initWithNormalImage(const char* nor,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector){
	CCSprite* cc_nor=CCSprite::create();
	cc_nor->setProperty("File",nor);
	return CCMenuItemSprite::initWithNormalSprite(cc_nor,NULL,NULL,target,selector);
}

//With Composite SelectedImage  Normal
CMenuItemSprite* CMenuItemSprite::createWithCompositeSelectedImage(const char* selImage,const char* norImage){
	CMenuItemSprite* cc=new CMenuItemSprite();
	if (cc&&cc->initWithCompositeSelectedImage(selImage,norImage)){
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CMenuItemSprite::initWithCompositeSelectedImage(const char* selImage,const char* norImage){
	CSpriteSelected* sp_sel=CSpriteSelected::create(selImage,norImage);
	CCSprite* sp=CCSprite::create();
	sp->setProperty("File",norImage);
	if (CMenuItemSprite::initWithNormalSprite(sp,sp_sel,NULL,NULL,NULL))
		return true;

	return false;
}

	/*
		设置NormalImage并重新定位
	*/
void CMenuItemSprite::setNormalImageAndRelocation(cocos2d::CCNode* nor){
	float scale=nor->getScale();
	const CCSize &sz=nor->getContentSize();
	nor->setContentSize(CCSizeMake(sz.width*scale,sz.height*scale));
	this->setNormalImage(nor);
}

	/*
		设置NormalImage并重新定位
	*/
void CMenuItemSprite::setNormalImageAndRelocation(std::string file){
	cocos2d::CCSprite* nor=cocos2d::CCSprite::create();
	nor->setProperty("File",file);
	float scale=nor->getScale();
	const CCSize &sz=nor->getContentSize();
	nor->setContentSize(CCSizeMake(sz.width*scale,sz.height*scale));
	this->setNormalImage(nor);
}

	/*
		更换按钮图标
	*/
void CMenuItemSprite::changeNormalAndSelectedImage(std::string nor,std::string sel){
	CCSprite* norSP = CCSprite::create();
	CCSprite* selSP = CCSprite::create();
	norSP->setProperty("File",nor);
	selSP->setProperty("File",sel);
	this->setNormalImage(norSP);
	this->setSelectedImage(selSP);
}

	/*
		播放按钮的声音
	*/
void CMenuItemSprite::PlaySound(){
	NFC_playSoundByID(this->m_nSoundID);
}

	/*
		选中事件
	*/
bool CMenuItemSprite::Selected_Event(){
	PlaySound();
	switch(m_nSelectedType){
		case kSELECTEDTYPE_NORMAL:
			selected(true);
			break;
		case kSELECTEDTYPE_SCALETO_SMALL:
			_scaleTo(0.9f);
			break;
		case kSELECTEDTYPE_SCALETO_BIG:
			_scaleTo(1.1f);
			break;
		case kSELECTEDTYPE_FADE:
			_fadeTo(180);
			break;
		case kSELECTEDTYPE_DARK:
			m_oldColor=getColor();
			_darkTo(BTN_GRAY);
			break;
		default:
			selected(true);
			break;
	}
	return true;
}
	/*
		取消选中事件
	*/
void CMenuItemSprite::UnSelected_Event(){
	switch(m_nSelectedType){
		case kSELECTEDTYPE_NORMAL:
			unselected();
			break;
		case kSELECTEDTYPE_SCALETO_SMALL:
			_scaleTo(1.0f);
			break;
		case kSELECTEDTYPE_SCALETO_BIG:
			_scaleTo(1.0f);
			break;
		case kSELECTEDTYPE_FADE:
			_fadeTo(255);
			break;
		case kSELECTEDTYPE_DARK:
			_darkTo(m_oldColor);
			break;
		default:
			unselected();
			break;
	}
}

	/*
		取消选中事件=active
	*/
void CMenuItemSprite::UnSelected_Event_Active(){
	switch(m_nSelectedType){
	case kSELECTEDTYPE_NORMAL:
		unselected();
		activate();
		break;
	case kSELECTEDTYPE_SCALETO_SMALL:
		_scaleTo_active(1.0f);
		break;
	case kSELECTEDTYPE_SCALETO_BIG:
		_scaleTo_active(1.0f);
		break;
	case kSELECTEDTYPE_FADE:
		_fadeTo_active(255);
		break;
	case kSELECTEDTYPE_DARK:
		_darkTo(m_oldColor);
		activate();
		break;
	default:
		unselected();
		activate();
		break;
	}
}

void CMenuItemSprite::_activeEvent(){
	activate();
}

void CMenuItemSprite::_scaleTo(float ss){
	CCScaleTo* action=CCScaleTo::create(0.05f,ss);
	action->setTag(900);
	stopActionByTag(900);
	runAction(action);
}

void CMenuItemSprite::_fadeTo(GLubyte ff){
	CCFadeTo* action=CCFadeTo::create(0.1f,ff);
	action->setTag(900);
	stopActionByTag(900);
	runAction(action);
}

void CMenuItemSprite::_scaleTo_active(float ss){
	CCScaleTo* action=CCScaleTo::create(0.05f,ss);
	CCCallFunc* action2=CCCallFunc::create(this,callfunc_selector(CMenuItemSprite::_activeEvent));
	CCSequence* seq=CCSequence::createWithTwoActions(action,action2);
	seq->setTag(900);
	stopActionByTag(900);
	runAction(seq);
}

void CMenuItemSprite::_fadeTo_active(GLubyte ff){
	CCFadeTo* action=CCFadeTo::create(0.2f,ff);
	CCCallFunc* action2=CCCallFunc::create(this,callfunc_selector(CMenuItemSprite::_activeEvent));
	CCSequence* seq=CCSequence::createWithTwoActions(action,action2);
	seq->setTag(900);
	stopActionByTag(900);
	runAction(seq);
}

void CMenuItemSprite::_darkTo(const cocos2d::ccColor3B& color){
	setColor(color);
}

//****************************带有Label的按钮***********************************
CLabelButtonItem::CLabelButtonItem()
	:m_pLabel(NULL)
{

}

CLabelButtonItem* CLabelButtonItem::create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d::CCLabelTTF* lb){
	CLabelButtonItem* cc=new CLabelButtonItem();
	if (cc->init(normalSprite,selectedSprite,lb))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;cc=NULL;
	return cc;
}

bool CLabelButtonItem::init(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d::CCLabelTTF* lb){
	if(!CMenuItemSprite::initWithNormalSprite(normalSprite,selectedSprite,NULL,NULL,NULL))
		return false;

	assert(lb!=NULL);
	m_pLabel=lb;
	m_pLabel->setAnchorPoint(ccp(0.5,0.5));
	m_pLabel->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	m_pLabel->setZOrder(10);
	this->addChild(m_pLabel);
	return true;
}

void CLabelButtonItem::SetLabelString(const char* txt){
	m_pLabel->setString(txt);
}

const char* CLabelButtonItem::GetLabelString(){
	return m_pLabel->getString();
}


//**************************CPriorityMenu**********************
bool CPriorityMenu::_checkTouchEnabled(){
	//如果全局禁用则直接返回
	if (!UISYSTEM->Get_Global_menuitem_enabled())
		return false;
	else
		return true;
}

bool CPriorityMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	
	if(!_checkTouchEnabled())
		return false;
	
	if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !m_bEnabled)
	{
		return false;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem&&m_bEnabled)
	{
		m_eState = kCCMenuStateTrackingTouch;
		CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
		if(item){
			item->Selected_Event();
		}else
			m_pSelectedItem->selected(true);
		return true;
	}
	return false;
}

void CPriorityMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem&&m_bEnabled)
	{
		CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
		if (item)
			item->UnSelected_Event_Active();
		else{
			m_pSelectedItem->unselected();
			m_pSelectedItem->activate();
		}
	}
	m_eState = kCCMenuStateWaiting;
}

void CPriorityMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
	if (m_pSelectedItem&&m_bEnabled)
	{
		CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
		if (item)
			item->UnSelected_Event();
		else
			m_pSelectedItem->unselected();
	}
	m_eState = kCCMenuStateWaiting;
}

void CPriorityMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		if (m_pSelectedItem&&m_bEnabled)
		{
			CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
			if (item)
				item->UnSelected_Event();
			else
				m_pSelectedItem->unselected();
		}
		m_pSelectedItem=NULL;
#if 0
		m_pSelectedItem = currentItem;
		if (m_pSelectedItem&&m_bEnabled)
		{
			CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
			if(item){
				item->Selected_Event();
			}else
				m_pSelectedItem->selected(true);
		}
#endif
	}
}

//**************************CTabMenu**********************
void CTabMenu::registerWithTouchDispatcher()
{
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, m_bSwallow);
}
bool CTabMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !m_bEnabled)
	{
		return false;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
		if(item)
			item->PlaySound();
		return true;
	}
	return false;
}

void CTabMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem)
	{
		m_pSelectedItem->activate();
	}
	m_eState = kCCMenuStateWaiting;
}
void CTabMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		m_pSelectedItem = currentItem;
	}
}

//**************************CImmovableMenu**********************
bool CImmovableMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	bool result = false;
	result=CCMenu::ccTouchBegan(touch,event);
	if (result){
		CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
		if(item)
			item->PlaySound();
	}
	return result;
}

//**************************TabMenuItem + ImmovableMenuItem 组合**********************
bool CTabImmovableMenu::ccTouchBegan_ccmenu(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !m_bEnabled)
	{
		return false;
	}
	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		//m_pSelectedItem->selected(true);
		return true;
	}
	return false;
}

bool CTabImmovableMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	bool result = false;
	result=ccTouchBegan_ccmenu(touch,event);
	return result;
}

void CTabImmovableMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem)
	{
		//m_pSelectedItem->unselected();
		CMenuItemSprite* item=dynamic_cast<CMenuItemSprite*>(m_pSelectedItem);
		if(item)
			item->PlaySound();
		m_pSelectedItem->activate();
	}
	m_eState = kCCMenuStateWaiting;
}

void CTabImmovableMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");

	CCPoint startPoint   = touch->getStartLocation();
	CCPoint currentPoint = touch->getLocation();
	if (fabs(startPoint.x-currentPoint.x) >= m_fXMoveLimitDiff)
	{
		if (m_pSelectedItem)
		{
			//m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}

		return;
	}

	if (fabs(startPoint.y-currentPoint.y) >= m_fYMoveLimitDiff)
	{
		if (m_pSelectedItem)
		{
			//m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}

		return;
	}

	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		if (m_pSelectedItem)
		{
			//m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}
	}
}