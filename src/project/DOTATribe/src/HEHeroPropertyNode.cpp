//Name：HEHeroPropertyNode
//Function：英雄装备--属性
//Written By：尹强

#include "../include/HEHeroPropertyNode.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/SysLangDataManager.h"
#include <string>

USING_NS_CC;
using namespace std;

HEHeroPropertyNode::HEHeroPropertyNode()
:m_nCurIdx(0){

}

HEHeroPropertyNode* HEHeroPropertyNode::create(){
	HEHeroPropertyNode* cc=new HEHeroPropertyNode();
	if (cc&&cc->init())
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return NULL;
}

bool HEHeroPropertyNode::init(){
	if (!CCNode::init())
		return false;


	_initLayout();
	return true;
}

void HEHeroPropertyNode::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROEQUIP_HERODETAIL,this);
}

void HEHeroPropertyNode::refreshAllProperty(int tabidx){
	m_nCurIdx=tabidx;
	//更新力敏智
	_setRoleValue(tabidx);
	//更新详细信息
	_setRoleDetail(tabidx);
}

void HEHeroPropertyNode::_setRoleValue(int idx){
	char tmp[128]="";
	Attribute* att=NFC_GetHeroAttributeManager(idx);
	string sys;
	sys = SysLangDataManager::get_instance2()->GetSysLangById(725);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kSTRENGTH]);
	NFC_setLabelString(kHE_STRENGTH,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(726);
	sprintf(tmp,"%d",att->mapPropertyList_[kAGILITY]);
	NFC_setLabelString(kHE_DEX,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(727);
	sprintf(tmp,"%d",att->mapPropertyList_[kINTELLIGENCE]);
	NFC_setLabelString(kHE_INTELLIGENCE,this,tmp);
}

void HEHeroPropertyNode::_setRoleDetail(int idx){
	char tmp[128]="";
	Attribute* att=NFC_GetHeroAttributeManager(idx);
	string sys;
	//力敏智
	sys = SysLangDataManager::get_instance2()->GetSysLangById(725);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kSTRENGTH]);
	NFC_setLabelString(kHE_STRENGTH,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(726);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kAGILITY]);
	NFC_setLabelString(kHE_DEX,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(727);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kINTELLIGENCE]);
	NFC_setLabelString(kHE_INTELLIGENCE,this,tmp);
	//其他属性
	sys = SysLangDataManager::get_instance2()->GetSysLangById(730);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kMINATTACK],att->mapPropertyList_[kMAXATTACK]);
	NFC_setLabelString(kHE_ATTACK,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(728);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kMAXHP]);
	NFC_setLabelString(kHE_HP,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(736);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kHIT]);
	NFC_setLabelString(kHE_HIT,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(735);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kEXPOSEARMOR]);
	NFC_setLabelString(kHE_PJ,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(734);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kCRIT]);
	NFC_setLabelString(kHE_BJ,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(729);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kMAXMP]);
	NFC_setLabelString(kHE_MP,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(731);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kSPEED]);
	NFC_setLabelString(kHE_SPEED,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(733);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kDODGE]);
	NFC_setLabelString(kHE_DODGE,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(732);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kARMOR]);
	NFC_setLabelString(kHE_ARMOR,this,tmp);
	sys = SysLangDataManager::get_instance2()->GetSysLangById(737);
	sprintf(tmp,sys.c_str(),att->mapPropertyList_[kUNCRIT]);
	NFC_setLabelString(kHE_UNCRIT,this,tmp);
}

	/*
		来自英雄装备界面的回调
	*/
void HEHeroPropertyNode::EventWindowCallBack(int iEventType, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		refreshAllProperty(m_nCurIdx);
	}
}
