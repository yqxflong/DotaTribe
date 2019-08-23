//Name：HERoleInfoNode
//Function：英雄装备--人物信息
//Written By：尹强

#include "../include/HERoleInfoNode.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/CProgressInnerBar.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/GuideSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include <string>

USING_NS_CC;
using namespace std;

HERoleInfoNode::HERoleInfoNode(){

}

HERoleInfoNode* HERoleInfoNode::create(){
	HERoleInfoNode* cc=new HERoleInfoNode();
	if (cc&&cc->init())
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return NULL;
}

bool HERoleInfoNode::init(){
	if(!CCNode::init())
		return false;

	_initLayout();
	_mapBtn();
	_refreshInfo();
	return true;
}

void HERoleInfoNode::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROEQUIP_ROLEINFO,this);
}

	/*
		来自英雄装备界面的回调
	*/
void HERoleInfoNode::EventWindowCallBack(int iEventType, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_HEROWINDOW_ROLEINFO_LEADERSHIP_LVUP)
	{
		_refreshInfo();
	}
}

void HERoleInfoNode::_mapBtn(){
	CCMenuItem* cc=NFC_getMenuItem(kHE_CHECKBTN,this);
	cc->setTarget(this,menu_selector(HERoleInfoNode::On_Click_Event));
}

void HERoleInfoNode::_refreshInfo(){
	char tmp[128]="";
	string sys="";
	//leadership
	sys=SysLangDataManager::get_instance2()->GetSysLangById(5014);
	int leadership=ROLEINFODATAHANDLER->m_pRIData->honorLevel_;
	sprintf(tmp,sys.c_str(),leadership);
	NFC_setLabelString(kHE_LEADERVALUE,this,tmp);

	//qishi
	int qishi=ROLEINFODATAHANDLER->m_pRIData->honorExp_;
	int maxqishi=ROLEINFODATAHANDLER->m_pRIData->honorMaxExp_;
	sys=SysLangDataManager::get_instance2()->GetSysLangById(741);
	sprintf(tmp,sys.c_str(),qishi,maxqishi);
	NFC_setLabelString(kHE_QISHIVALUE,this,tmp);
	//qishi progress
	CProgressInnerBar* progress=(CProgressInnerBar*)NFC_getNode(kHE_PROGRESSBAR,this);
	progress->setPercent((float)qishi*1.0/maxqishi);
}

void HERoleInfoNode::On_Click_Event(cocos2d::CCObject* pSender){
	CheckRoleBaseInfoHandler::get_instance2()->ToServerRoleBaseInfo();
}
