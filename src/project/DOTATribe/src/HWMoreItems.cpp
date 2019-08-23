//Name£ºHWMoreItems
//Function£ºMoreItems 
//Written By£ºÒüÇ¿

#include "../include/HWMoreItems.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
USING_NS_CC;

HWMoreItems* HWMoreItems::create(CCNode* normalSprite, CCObject* target, SEL_MenuHandler selector){
	HWMoreItems* cc=new HWMoreItems();
	if(cc&&cc->initWithNormalSprite(normalSprite,NULL,NULL,target,selector)){
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool HWMoreItems::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector){
	if (CCMenuItemSprite::initWithNormalSprite(normalSprite,selectedSprite,disabledSprite,target,selector))
		return true;
	return false;
}
void HWMoreItems::movetoOldPoint(){
	CCMoveTo* action_moveto=CCMoveTo::create(m_fActionDur,m_oldP);
	CCFadeIn* action_fadein=CCFadeIn::create(m_fActionDur);
	CCSpawn* action_spawn=CCSpawn::createWithTwoActions(action_moveto,action_fadein);
	CCCallFunc* action_func=CCCallFunc::create(this,callfunc_selector(HWMoreItems::_showItem));
	CCSequence* action_seq=CCSequence::createWithTwoActions(action_func,action_spawn);
	this->runAction(action_seq);
}
void HWMoreItems::movetoNewPoint(){
	CCMoveTo* action_moveto=CCMoveTo::create(m_fActionDur,m_newP);
	CCFadeOut* action_fadeout=CCFadeOut::create(m_fActionDur);
	CCSpawn* action_spawn=CCSpawn::createWithTwoActions(action_moveto,action_fadeout);
	CCCallFunc* action_func=CCCallFunc::create(this,callfunc_selector(HWMoreItems::_hideItem));
	CCSequence* action_seq=CCSequence::createWithTwoActions(action_spawn,action_func);
	this->runAction(action_seq);
}

//immediately
void HWMoreItems::gotoNewPoint(){
	this->setPosition(m_newP);
	this->setVisible(false);
}
//immediately
void HWMoreItems::gotoOldPoint(){
	this->setPosition(m_oldP);
	this->setVisible(true);
}

void HWMoreItems::_showItem(){
	this->setVisible(true);
}
void HWMoreItems::_hideItem(){
	this->setVisible(false);
}
