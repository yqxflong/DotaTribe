//Name£ºHWBottomBar
//Function£ºHWBottomBar 
//Written By£ºÒüÇ¿

#include "../include/HWBottomBar.h"

USING_NS_CC;

HWBottomBar*  HWBottomBar::create(const char *pszFileName){
	HWBottomBar* cc=new HWBottomBar();
	if (cc&&cc->initWithFile(pszFileName))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool HWBottomBar::initWithFile(const char *pszFilename){
	if (CCSprite::initWithFile(pszFilename))
	{
		return true;
	}
	return false;
}

void HWBottomBar::movetoOldPoint(){
	CCMoveTo* action_moveto=CCMoveTo::create(m_fActionDur,m_oldP);
	CCFadeIn* action_fadein=CCFadeIn::create(m_fActionDur);
	CCSpawn* action_spawn=CCSpawn::createWithTwoActions(action_moveto,action_fadein);
	CCCallFunc* action_func=CCCallFunc::create(this,callfunc_selector(HWBottomBar::_showItem));
	CCSequence* action_seq=CCSequence::createWithTwoActions(action_func,action_spawn);
	this->runAction(action_seq);
}
void HWBottomBar::movetoNewPoint(){
	CCMoveTo* action_moveto=CCMoveTo::create(m_fActionDur,m_newP);
	CCFadeOut* action_fadeout=CCFadeOut::create(m_fActionDur);
	CCSpawn* action_spawn=CCSpawn::createWithTwoActions(action_moveto,action_fadeout);
	CCCallFunc* action_func=CCCallFunc::create(this,callfunc_selector(HWBottomBar::_hideItem));
	CCSequence* action_seq=CCSequence::createWithTwoActions(action_spawn,action_func);
	this->runAction(action_seq);
}

//immediately
void HWBottomBar::gotoNewPoint(){
	this->setPosition(m_newP);
	this->setVisible(false);
}
//immediately
void HWBottomBar::gotoOldPoint(){
	this->setPosition(m_oldP);
	this->setVisible(true);
}

void HWBottomBar::_showItem(){
	this->setVisible(true);
}
void HWBottomBar::_hideItem(){
	this->setVisible(false);
}