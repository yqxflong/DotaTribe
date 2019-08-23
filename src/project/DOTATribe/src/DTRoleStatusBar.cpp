//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The RoleStatus Bar will be put in many scenes

#include "../include/DTRoleStatusBar.h"
#include "../include/NFControlsManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MaskNode.h"
#include "../include/CProgressInnerBar.h"
#include "../include/CMenuItemSprite.h"
#include "../include/RoleHeroSkinsDataHandler.h"
USING_NS_CC;

DTRoleStatusBar::DTRoleStatusBar()
:m_isBTickBattle(false)
,m_iTickBattleNum(0)
,m_iCurBatCapacity(0)
,m_addBatMean(0)
,m_pDelegate(NULL){

}
DTRoleStatusBar::~DTRoleStatusBar(){

}

DTRoleStatusBar* DTRoleStatusBar::create(){
	DTRoleStatusBar* cc=new DTRoleStatusBar();
	if (cc&&cc->init())
	{
		cc->autorelease();
		return cc;
	}
	delete cc;cc=NULL;
	return cc;
}

bool DTRoleStatusBar::init(){
	if (!CCNode::init())
		return false;
	_initLayout();
	_setRoleAvatar();
	_mapBtns();
	Refresh();
	return true;
}

void DTRoleStatusBar::ResetPropertyByNode(cocos2d::CCNode* node){
	this->setZOrder(node->getZOrder());
	this->setAnchorPoint(node->getAnchorPoint());
	this->setPosition(node->getPosition());
	this->setVisible(node->isVisible());
}

void DTRoleStatusBar::setDelegate(DTRoleStatusBarDelegate* pDel){
	m_pDelegate=pDel;
}

void DTRoleStatusBar::Refresh(){
	_refreshData();
}
void DTRoleStatusBar::Tick(){
	Tick_Battle();
}

void DTRoleStatusBar::Tick_Battle(){
	if (m_isBTickBattle)
	{
		if (m_iCurBatCapacity <= m_iTickBattleNum)
		{
			m_isBTickBattle = false;
			m_iTickBattleNum = m_iCurBatCapacity;
		}
		NFC_setLabelStringInt(kZL,this,m_iTickBattleNum);
		m_iTickBattleNum += m_addBatMean;
	}
}

void DTRoleStatusBar::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kPUBLIC_ROLESTATUSBAR,this);
}

void DTRoleStatusBar::_mapBtns(){
	CMenuItemSprite* cc= (CMenuItemSprite*)NFC_getMenuItem(kADDBTN,this);
	cc->setIDX(kADDBTN);
	cc->setTarget(this,menu_selector(DTRoleStatusBar::On_Click_Event));
}

void DTRoleStatusBar::_refreshData(){
	_setRoleLv();
	_setName();
	_setZL();
	_setExp();
	_setTL();
	_setGold();
	_setDiamond();
}

void DTRoleStatusBar::_setRoleLv(){
	int level=ROLEINFODATAHANDLER->m_pRIData->level_;
	NFC_setLabelStringInt(kLVVALUE,this,level);
}

void DTRoleStatusBar::_setRoleAvatar(){
	MaskNode* node = (MaskNode*)this->getChildByTag(kAVATAR);
	const UIViewData &dd=node->GetViewData();
	unsigned short iconid= NFC_GetTeamHero()->getHeroIconID();  
	std::string filepath=RESOURCEDAIDMANAGER->getDataByID(iconid);
	CCSprite* nor=CCSprite::create();
	nor->setProperty("File",filepath);
	nor->setScale(dd.scale_);
	//
	CPriorityMenu* menu=CPriorityMenu::create(dd.touchpriority_,dd.swallow_==1);
	menu->setTag(dd.idx_);
	menu->setZOrder(dd.zorder_);
	menu->setVisible(dd.hide_==0);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	CMenuItemSprite* cc=CMenuItemSprite::create(nor,NULL,this,menu_selector(DTRoleStatusBar::On_Click_Event));
	cc->setTag(0);
	cc->setIDX(kAVATAR);
	cc->setSoundID(dd.soundid_);
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	menu->addChild(cc);
}

void DTRoleStatusBar::_setName(){
	NFC_setLabelString(kNAME,this,ROLEINFODATAHANDLER->m_pRIData->name_);
}

void DTRoleStatusBar::_setZL(){
	if (ROLEINFODATAHANDLER->isUpdateCapacity_)
	{
		ROLEINFODATAHANDLER->isUpdateCapacity_ = false;
		m_isBTickBattle = true;
		m_iCurBatCapacity = ROLEINFODATAHANDLER->m_pRIData->btlCapacity_;
		m_iTickBattleNum= m_iCurBatCapacity*9/10;
		MaskNode* mask = (MaskNode*)this->getChildByTag(kUPDATEZL_TIME);
		float second = mask->GetViewData().width_;
		m_addBatMean = (m_iCurBatCapacity - m_iTickBattleNum) /(30*second);
		if (m_addBatMean == 0)
			m_addBatMean = 1;
		return;
	}
	NFC_setLabelString(kZL,this,_to_event_param_(ROLEINFODATAHANDLER->m_pRIData->btlCapacity_));
}

void DTRoleStatusBar::_setExp(){
	int curExp=ROLEINFODATAHANDLER->m_pRIData->exp_;
	int maxExp=ROLEINFODATAHANDLER->m_pRIData->maxExp_;
	float exppercent=(float)(1.0*curExp/maxExp);
	int per=(int)(exppercent*100);
	//
	CProgressInnerBar* bar=(CProgressInnerBar*)this->getChildByTag(kEXPBAR);
	bar->setPercent(exppercent);
}

void DTRoleStatusBar::_setTL(){
	char tmp[64];
	sprintf(tmp,"%d/%d",ROLEINFODATAHANDLER->m_pRIData->vitality_,ROLEINFODATAHANDLER->m_pRIData->maxVitality_);
	NFC_setLabelString(kTL,this,tmp);
}

void DTRoleStatusBar::_setGold(){
	NFC_setLabelString(kMONEY,this,_to_event_param_(ROLEINFODATAHANDLER->m_pRIData->money_));
}

void DTRoleStatusBar::_setDiamond(){
	NFC_setLabelString(kDIAMOND,this,_to_event_param_(ROLEINFODATAHANDLER->m_pRIData->jewels_));
}

void DTRoleStatusBar::On_Click_Event(cocos2d::CCObject* pSender){
	if (!m_pDelegate)
		return;

	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if (cc->getIDX()==kAVATAR)
		m_pDelegate->AvatarClickEvent();
	else if(cc->getIDX()==kADDBTN)
		m_pDelegate->AddTLClickEvent();
}