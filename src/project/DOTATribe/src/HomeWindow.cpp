//Name：HomeWindow
//Function：主场景，通往各个场景的必经之路
//Written By：尹强

#include "../include/HomeWindow.h"
#include "../include/config_HomeWindow.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/DOTATribeApp.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/CCornerNumIcon.h"
#include "../include/UIViewDataManger.h"
#include "../include/LoggerSystem.h"
#include "../include/LevelUpDataHandler.h"
#include "../Include/HomeProcedure.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/CMenuItemSprite.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/HeroTechnologyDataHandler.h"
#include "../include/HWMoreItems.h"
#include "../include/MaskNode.h"
#include "../include/CPublicVarReader.h"
#include "../include/SysLangDataManager.h"
#include "../include/MaskNode.h"
#include "../include/GuideSystem.h"
#include "../include/RevenuePacket.h"
#include "../include/FriendPacket.h"
#include "../include/EmailDataHandler.h"
#include "../include/WindowManager.h"
#include "../include/ErrorTipsWindow.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/CTableView.h"
#include "../include/VariableSystem.h"
#include "../include/ActivityPacket.h"
#include "../include/PESWindow.h"
#include "../include/RevenueDataHandler.h"
#include "../include/NFAnimationController.h"
#include "../include/TimeSystem.h"
#include "../include/BossScoreDataHandler.h"
#include "../include/UISystem.h"

#include <string>

using namespace std;

//time for 快速出城提示
const float HomeWindow::TIME_SHOWHINT_QUICKOUT=6.0f;

HomeWindow::HomeWindow()
:m_pRoot(0)
,m_pRootMenu(0)
,m_pMapScroll(0)
,m_fTick_quickout_hint(0.0f)
,m_bIsShowHint_quickout(false)
{
	m_WindowType = _TYPED_WINDOW_HOME_;
	m_pArrow_Collection = NULL;
	m_pArrow_QuickOut=NULL;
	memset(building_status,0,sizeof(int)*8);
}

HomeWindow::~HomeWindow()
{
}

bool HomeWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_NEWFUNCOPEN_HOMESHOWNEW_,true);
	
	return IWindow::Init();
}

void HomeWindow::_registerRefreshEvent(){
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_REFRESH_UPDATEUI_,Event_RefreshUI_Handler);
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_HOME_MORE_SHOWITEMS_,Event_ShowMoreItems_Handler);
}

void HomeWindow::_unregisterRefreshEvent(){
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_REFRESH_UPDATEUI_,Event_RefreshUI_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_HOME_MORE_SHOWITEMS_,Event_ShowMoreItems_Handler);
}

bool HomeWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();
		_registerRefreshEvent();
		//设置快速出城
		_setQuickOut();
		//设置当前VIp等级文字
		_updateVipNum();
		CheckAllHint();
		CheckFunctionLock();
		//show RoleStatus Bar
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_,_to_event_param_(_TYPED_WINDOW_HOME_));
		return true;
	} 
	while (false);

	return false;
}

void HomeWindow::Tick()
{
	IWindow::Tick();

	//每15s检查快速出城提示是否开启
	if (!m_bIsShowHint_quickout)
	{
		m_fTick_quickout_hint+=TimeSystem::get_instance2()->GetLastTickTime();
		if (m_fTick_quickout_hint>=TIME_SHOWHINT_QUICKOUT){
			m_bIsShowHint_quickout=_showQuickOutHint();	//显示快速出城提示
			m_fTick_quickout_hint=0.0f;
		}
	}
}



void HomeWindow::Destroy()
{
	_hideArrow_Collection();
	_hideArrow_QuickOut();
	_unregisterRefreshEvent();
	//m_pRoot->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void HomeWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{

	if (iEventType == _TYPED_EVENT_SHOW_HOMEWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_HOMEWINDOW_)
	{
		PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
		PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		Destroy();
	}else if(iEventType == _TYPED_EVENT_FADEOUT_HOMEWINDOW_){
		PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
		PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		Destroy();
	}else if(iEventType==_TYPED_EVENT_NEWFUNCOPEN_HOMESHOWNEW_){
		//显示new字样给建筑
		string ModuleID=paramList.front();
		int ModuleID_n=atoi(ModuleID.c_str());
		_showNewFlowICon4Building(ModuleID_n);
		CheckAllHint();
	}
}

void HomeWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if (LevelUpDataHandler::get_instance2()->LevelUpDataList.size()>0)
	{
		//PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_,_to_event_param_(m_WindowType));
	}

	Show(true);	
	PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
}

void HomeWindow::_initLayout(){
	memset(building_status,0,sizeof(int)*8);
	//
	m_pRoot=m_pRootNode;
	m_pRootMenu=CPriorityMenu::create(kPRIORITYLOW-1);
	m_pRootMenu->setPosition(CCPointZero);
	m_pRoot->addChild(m_pRootMenu,m_pRoot->getZOrder()+1);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHOMEWINDOW,m_pRoot);
	_SetHomeMap();
	_mapBtn();
	_mapMoreItems();
	_createBusinessMan();
	_initStrengthenHint();
	_initMineralEmptyHint();
	_initFreeSuppliHint();
	_initFreeSummonHint();
	_initRefreshShopHint();
	checkMoreItems();

}

void HomeWindow::_SetHomeMap(){
	m_pMapScroll=(CMapScrollView*)NFC_getNode(udMAPSCROLL,m_pRootNode);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHOMEWINDOW_MAP,m_pMapScroll->getContainer());
	CCNode* homemap_1=NFC_getNode(udHOMEMAP_1,m_pMapScroll->getContainer());
	CCNode* homemap_2=NFC_getNode(udHOMEMAP_2,m_pMapScroll->getContainer());
	m_pMapScroll->setContentSize(homemap_1->getContentSize()+homemap_2->getContentSize());
}

void HomeWindow::_createBusinessMan(){
	//先这样吧，
	CCNode* node=NFC_getNode(udBUSSINESSMAN,m_pMapScroll->getContainer());
	cocos2d::extension::CCSkeletonAnimation*HeroicSkeleton = cocos2d::extension::CCSkeletonAnimation::createWithFile("resource/spine/shangren.json","resource/spine/shangren.atlas");
	HeroicSkeleton->setAnimation("keshou",true); 
	HeroicSkeleton->setPosition(node->getPosition());
	HeroicSkeleton->setScale(node->getScale());
	m_pMapScroll->addChild(HeroicSkeleton,node->getZOrder(),udREALBUSSINESSMAN);
}

void HomeWindow::_initStrengthenHint(){
	MaskNode* node=(MaskNode*)NFC_getNode(udSTRENTHEN_HINT_NODE,m_pRoot);
	const UIViewData& dd=node->GetViewData();
	vector<float> vec;vec.clear();
	vec.push_back(dd.width_);
	vec.push_back(dd.height_);
	//
	CCNode* node1=NFC_getNode(udSTRENTHEN_HINT_1,m_pRoot);
	node1->removeFromParentAndCleanup(false);
	CSimpleActionSprite* cc1=NFC_getSimpleActionSprite(CSimpleActionSprite::_FLOAT_UP_AND_DOWN_TYPE_,vec);
	cc1->addChild(node1);
	m_pRoot->addChild(cc1,node1->getZOrder(),udSTRENTHEN_HINT_1_NODE);
	//
	CCNode* node2=NFC_getNode(udSTRENTHEN_HINT_2,m_pRoot);
	node2->removeFromParentAndCleanup(false);
	CSimpleActionSprite* cc2=NFC_getSimpleActionSprite(CSimpleActionSprite::_STANDBY_TYPE_,vec);
	cc2->addChild(node2);
	m_pRoot->addChild(cc2,node2->getZOrder(),udSTRENTHEN_HINT_2_NODE);
}

void HomeWindow::_initMineralEmptyHint(){
	MaskNode* node=(MaskNode*)NFC_getNode(udMINERALEMPTY_HINT_NODE,m_pMapScroll->getContainer());
	const UIViewData& dd=node->GetViewData();
	vector<float> vec;vec.clear();
	vec.push_back(dd.width_);
	vec.push_back(dd.height_);
	//
	CCNode* node1=NFC_getNode(udICON_MINERALEMPTYHINT,m_pMapScroll->getContainer());
	node1->removeFromParentAndCleanup(false);
	CSimpleActionSprite* cc=NFC_getSimpleActionSprite(CSimpleActionSprite::_FLOAT_UP_AND_DOWN_TYPE_,vec);
	cc->addChild(node1);
	m_pMapScroll->getContainer()->addChild(cc,node1->getZOrder(),udHINT_MINERALEMPTY);
}


void HomeWindow::_initFreeSuppliHint(){
	MaskNode* node=(MaskNode*)NFC_getNode(udMINERALEMPTY_HINT_NODE,m_pMapScroll->getContainer());
	const UIViewData& dd=node->GetViewData();
	vector<float> vec;
	vec.clear();
	vec.push_back(dd.width_);
	vec.push_back(dd.height_);
	//
	CCNode* node1=NFC_getNode(udICON_FREESUPPLI,m_pMapScroll->getContainer());
	node1->removeFromParentAndCleanup(false);
	CSimpleActionSprite* cc=NFC_getSimpleActionSprite(CSimpleActionSprite::_FLOAT_UP_AND_DOWN_TYPE_,vec);
	cc->addChild(node1);
	m_pMapScroll->getContainer()->addChild(cc,node1->getZOrder(),udHINT_FREESUPPLI);
}

void HomeWindow::_initFreeSummonHint()
{
	MaskNode* node=(MaskNode*)NFC_getNode(udMINERALEMPTY_HINT_NODE,m_pMapScroll->getContainer());
	const UIViewData& dd=node->GetViewData();
	vector<float> vec;
	vec.clear();
	vec.push_back(dd.width_);
	vec.push_back(dd.height_);
	//
	CCNode* node1=NFC_getNode(udICON_FREESUMMON,m_pMapScroll->getContainer());
	node1->removeFromParentAndCleanup(false);
	CSimpleActionSprite* cc=NFC_getSimpleActionSprite(CSimpleActionSprite::_FLOAT_UP_AND_DOWN_TYPE_,vec);
	cc->addChild(node1);
	m_pMapScroll->getContainer()->addChild(cc,node1->getZOrder(),udHINT_FREESUMMON);
}

void HomeWindow::_initRefreshShopHint()
{
	MaskNode* node=(MaskNode*)NFC_getNode(udMINERALEMPTY_HINT_NODE,m_pMapScroll->getContainer());
	const UIViewData& dd=node->GetViewData();
	vector<float> vec;
	vec.clear();
	vec.push_back(dd.width_);
	vec.push_back(dd.height_);
	//
	CCNode* node1=NFC_getNode(udICON_REFRESHSHOP,m_pMapScroll->getContainer());
	node1->removeFromParentAndCleanup(false);
	CSimpleActionSprite* cc=NFC_getSimpleActionSprite(CSimpleActionSprite::_FLOAT_UP_AND_DOWN_TYPE_,vec);
	cc->addChild(node1);
	m_pMapScroll->getContainer()->addChild(cc,node1->getZOrder(),udHINT_REFRESHSHOP);
}

void HomeWindow::_mapMoreItems(){
	_mapRoleInfoItem();
	_mapBagItem();
	//_mapSkillItem();
	_mapStrengthenItem();
	_mapFriendItem();
	_mapSystemItem();
}



void HomeWindow::_mapRoleInfoItem(){
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(udROLEINFO);
	HWMoreItems* hh = (HWMoreItems*)menu->getChildByTag(0);
	hh->setTag(udROLEINFO);
	hh->setIDX(udROLEINFO);
	hh->setTarget(this, menu_selector(HomeWindow::On_Click_BtnClick));
	CCNode* moremenu = m_pRoot->getChildByTag(udMOREBTN);
	CCNode *more = moremenu->getChildByTag(0);
	hh->setOldPoint(ccp(hh->getPositionX(),hh->getPositionY()));
	hh->setNewPoint(more->getPosition());
	hh->gotoNewPoint();
	hh->removeFromParentAndCleanup(false);
	m_pRootMenu->addChild(hh);
	menu->removeFromParentAndCleanup(true);
}


void HomeWindow::_mapBagItem(){
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(udBAG);
	HWMoreItems* hh = (HWMoreItems*)menu->getChildByTag(0);
	hh->setTag(udBAG);
	hh->setIDX(udBAG);
	hh->setTarget(this, menu_selector(HomeWindow::On_Click_BtnClick));
	CCNode* moremenu = m_pRoot->getChildByTag(udMOREBTN);
	CCNode *more = moremenu->getChildByTag(0);
	hh->setOldPoint(ccp(hh->getPositionX(),hh->getPositionY()));
	hh->setNewPoint(more->getPosition());
	hh->gotoNewPoint();
	hh->removeFromParentAndCleanup(false);
	m_pRootMenu->addChild(hh);
	menu->removeFromParentAndCleanup(true);
}
void HomeWindow::_mapSkillItem(){

	/*CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(udSKILL);
	HWMoreItems* hh = (HWMoreItems*)menu->getChildByTag(0);
	hh->setTag(udSKILL);
	hh->setIDX(udSKILL);
	hh->setTarget(this, menu_selector(HomeWindow::On_Click_BtnClick));
	CCNode* moremenu = m_pRoot->getChildByTag(udMOREBTN);
	CCNode *more = moremenu->getChildByTag(0);
	hh->setOldPoint(ccp(hh->getPositionX(),hh->getPositionY()));
	hh->setNewPoint(more->getPosition());
	hh->gotoNewPoint();
	hh->removeFromParentAndCleanup(false);
	m_pRootMenu->addChild(hh);
	menu->removeFromParentAndCleanup(true);*/

}
void HomeWindow::_mapStrengthenItem(){
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(udSMELT);
	HWMoreItems* hh = (HWMoreItems*)menu->getChildByTag(0);
	hh->setTag(udSMELT);
	hh->setIDX(udSMELT);
	hh->setTarget(this, menu_selector(HomeWindow::On_Click_BtnClick));
	CCNode* moremenu = m_pRoot->getChildByTag(udMOREBTN);
	CCNode *more = moremenu->getChildByTag(0);
	hh->setOldPoint(ccp(hh->getPositionX(),hh->getPositionY()));
	hh->setNewPoint(more->getPosition());
	hh->gotoNewPoint();
	hh->removeFromParentAndCleanup(false);
	m_pRootMenu->addChild(hh);
	menu->removeFromParentAndCleanup(true);
}
void HomeWindow::_mapFriendItem(){
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(udFRIEND);
	HWMoreItems* hh = (HWMoreItems*)menu->getChildByTag(0);
	hh->setTag(udFRIEND);
	hh->setIDX(udFRIEND);
	hh->setTarget(this, menu_selector(HomeWindow::On_Click_BtnClick));
	CCNode* moremenu = m_pRoot->getChildByTag(udMOREBTN);
	CCNode *more = moremenu->getChildByTag(0);
	hh->setOldPoint(ccp(hh->getPositionX(),hh->getPositionY()));
	hh->setNewPoint(more->getPosition());
	hh->gotoNewPoint();
	hh->removeFromParentAndCleanup(false);
	m_pRootMenu->addChild(hh);
	menu->removeFromParentAndCleanup(true);
//将好友角标加上
	CCNode* corner_friend=NFC_getNode(udFRIENDCORNER,m_pRoot);
	corner_friend->removeFromParent();
	hh->addChild(corner_friend);
}

void HomeWindow::_mapSystemItem(){
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(udSYSTEM);
	HWMoreItems* hh = (HWMoreItems*)menu->getChildByTag(0);
	hh->setTag(udSYSTEM);
	hh->setIDX(udSYSTEM);
	hh->setTarget(this, menu_selector(HomeWindow::On_Click_BtnClick));
	CCNode* moremenu = m_pRoot->getChildByTag(udMOREBTN);
	CCNode *more = moremenu->getChildByTag(0);
	hh->setOldPoint(ccp(hh->getPositionX(),hh->getPositionY()));
	hh->setNewPoint(more->getPosition());
	hh->gotoNewPoint();
	hh->removeFromParentAndCleanup(false);
	m_pRootMenu->addChild(hh);
	menu->removeFromParentAndCleanup(true);
}
	/*
		检查提示信息
	*/
void HomeWindow::CheckAllHint(){
	_showBossHint();		//提示有Boss活动
	_showRefreshShopHint();		//提示商店可刷新
	_showFreeSupplicaHint();	//提示有免费祈愿
	_showMineralEmptyHint();	//提示矿坑是空的
	_showFreeSummonHint();		//提示有免费召唤
	_showStrengthenHint();	//强化提示
	_showQuickOutHint_DoubleExp();	//快速出城，双倍经验提示
	checkAwardNoticeHint();	//奖励公告提示
	checkAwardActivityHint();		//活动提示
	checkAwardVipHint();			//VIp奖励提示
	setCollectionCorner();
	setEmailCorner();
	setFriendCorner();
	setBossScoreCorner();
}

	/*
		提示有装备可以强化
	*/
void HomeWindow::_showStrengthenHint(){
	CSimpleActionSprite* cc1=(CSimpleActionSprite*)NFC_getNode(udSTRENTHEN_HINT_1_NODE,m_pRoot);
	CSimpleActionSprite* cc2=(CSimpleActionSprite*)NFC_getNode(udSTRENTHEN_HINT_2_NODE,m_pRoot);
	int level=ROLEINFODATAHANDLER->m_pRIData->level_;
	bool cond1=level<=_LV_MAX_HOMEWINDOW_STRENGTHEN_HINT;
	bool cond2=ROLEINFODATAHANDLER->isOpenScene(_LV_MIN_HOMEWINDOW_STRENGTHEN_HINT);
	bool cond3=NFC_GetHeroEquipManager()->CheckAllRoleEquipsCanTopup();
	if (cond1&&cond2&&cond3){
		if (ROLEINFODATAHANDLER->playerstatus_->_home_more_isopen){
			cc1->PlayAction();
			cc2->StopAction();
		}else{
			cc2->PlayAction();
			cc1->StopAction();
		}
	}else{
		cc1->StopAction();
		cc2->StopAction();
	}
}

//快速出城，双倍经验提示
void HomeWindow::_showQuickOutHint_DoubleExp(){
	bool cond=ROLEINFODATAHANDLER->m_pRIData->multiExp_>100?true:false;
	NFC_showNode(udOUT_EXP_DOUBLE_HINT,m_pRootNode,cond);
}

	/*
        ###挖矿状态
        ###byte 0：不可挖矿 1：可挖矿  2：挖矿中  
		提示有矿坑是空的
	*/
void HomeWindow::_showMineralEmptyHint(){
	CSimpleActionSprite* cc=(CSimpleActionSprite*)NFC_getNode(udHINT_MINERALEMPTY,m_pMapScroll->getContainer());
	bool cond1=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MINING);
	bool cond2=ROLEINFODATAHANDLER->m_pRIData->mineralempty_==1;
	bool cond3=building_status[7]==0;
	if (cond1&&cond2&&cond3){
		//显示浮动提示
		cc->PlayAction();
	}else{
		//停止浮动提示
		cc->StopAction();
	}
}

	/*
		提示有世界Boss 活动
	*/
void HomeWindow::_showBossHint(){
	bool condition1=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_BOSSSCORE);
	bool condition2=ROLEINFODATAHANDLER->m_pRIData->bossCanPlay_==0?false:true;
	NFC_setNodeVisable(udBOSS_EFFECT,m_pRootNode,condition1&&condition2);
}

/*
	提示有免费召唤
*/
void HomeWindow::_showFreeSummonHint()
{
	CSimpleActionSprite* cc=(CSimpleActionSprite*)NFC_getNode(udHINT_FREESUMMON,m_pMapScroll->getContainer());
	bool cond1=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROBAR);
	bool cond2=ROLEINFODATAHANDLER->m_pRIData->freesummon_ != 0;
	if (cond1 && cond2)
	{
		if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR))
			//停止浮动提示
			cc->StopAction();
		else
			//显示浮动提示
			cc->PlayAction();


	}else{
		//停止浮动提示
		cc->StopAction();
	}
}

/*		
	提示有免费祈愿
*/
void HomeWindow::_showFreeSupplicaHint()
{
	CSimpleActionSprite* cc=(CSimpleActionSprite*)NFC_getNode(udHINT_FREESUPPLI,m_pMapScroll->getContainer());
	bool cond1=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROTECH);
	bool cond2=ROLEINFODATAHANDLER->m_pRIData->freesupplica_ != 0;
	if (cond1 && cond2)
	{
		if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH))
			//停止浮动提示
			cc->StopAction();
		else
			//显示浮动提示
			cc->PlayAction();
		
	
	}else{
		//停止浮动提示
		cc->StopAction();
	}
}

void HomeWindow::_showRefreshShopHint()
{
	CSimpleActionSprite* cc=(CSimpleActionSprite*)NFC_getNode(udHINT_REFRESHSHOP,m_pMapScroll->getContainer());
	bool cond1=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MARKET);
	bool cond2=ROLEINFODATAHANDLER->m_pRIData->hasrefreshshop_ != 0;
	if (cond1 && cond2)
	{
		//显示浮动提示
		cc->PlayAction();
	}else{
		//停止浮动提示
		cc->StopAction();
	}
}

	/*
		提示快速出城
	*/
bool HomeWindow::_showQuickOutHint(){
	if (ROLEINFODATAHANDLER->m_pRIData->vitality_>=5){
		//体力达到5点才有提示
		if (ROLEINFODATAHANDLER->m_pRIData->level_<=_LV_HOMEWINDOW_QUICKOUT_HINT)
			_showArrow_QuickOut();//显示箭头
		else if(ROLEINFODATAHANDLER->m_pRIData->level_>_LV_HOMEWINDOW_QUICKOUT_HINT)
			NFC_showNode(udOUT_HINT,m_pRoot,true);//显示特效

		return true;
	}

	return false;
}

	/*
		隐藏快速出城提示
	*/
void HomeWindow::_hideQuickOutHint(){
	_hideArrow_QuickOut();
	NFC_showNode(udOUT_HINT,m_pRoot,false);
	m_fTick_quickout_hint=0.0f;
	m_bIsShowHint_quickout=false;
}

	/*
		提示奖励公告有奖励
	*/
void HomeWindow::checkAwardNoticeHint(){
	NFC_showNode(udAWARDNOTICE_EFFECT,m_pRoot,ROLEINFODATAHANDLER->m_pRIData->rewardprompt_>0 ? true:false);
}
	/*
		提示精彩活动有奖励
	*/
void HomeWindow::checkAwardActivityHint(){
	NFC_showNode(udACTIVITY_EFFECT,m_pRoot,ROLEINFODATAHANDLER->m_pRIData->activityprompt_>0 ? true:false);
}

void HomeWindow::checkAwardVipHint()
{
	NFC_showNode(udVIPREWARD_EFFECT,m_pRoot,ROLEINFODATAHANDLER->m_pRIData->vipreward_>0 ? true:false);
}

/*
	设置邮箱角标：显示未读的信
*/

void HomeWindow::setEmailCorner(){
	int unfcount=ROLEINFODATAHANDLER->m_pRIData->unReadEmailCounts_;
	NFC_setCornerNum(udEMAILCORNER,m_pRoot,unfcount);
}
	/*
		设置好友角标：显示申请好友的数量
	*/
void HomeWindow::setFriendCorner(){
	HWMoreItems* cc=(HWMoreItems*)m_pRootMenu->getChildByTag(udFRIEND);
	int unfcount=ROLEINFODATAHANDLER->m_pRIData->applyforFriendNum_;
	bool isshow=unfcount>0;
	NFC_showNode(udFRIENDCORNER,cc,isshow);
	NFC_setCornerNum(udFRIENDCORNER,cc,unfcount);
}

void HomeWindow::setBossScoreCorner()
{
	bool isopen=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_BOSSSCORE);
	
	if(isopen)
	{
		int unfcount = BOSSSCOREDATAHANDLER->m_iFreeTimesSync;
		NFC_setCornerNum(udBOSSCORNER,m_pRoot,unfcount);
	}

}

	/*
		设置征收角标：显示总可征收次数
	*/
void HomeWindow::setCollectionCorner(){
	int unfcount=ROLEINFODATAHANDLER->m_pRIData->leftFreeRevenueCount_;
	NFC_setCornerNum(udCOLLECTIONCORNER,m_pRoot,unfcount);
}

void HomeWindow::_mapBtn()
{
	CCMenu* menu;
	CMenuItemSprite* cc;
	//Building on the map
	for(int i= udBAR;i<=udMINERALHOLE;i++)
	{
		menu = (CCMenu*)NFC_getNode(i,m_pMapScroll->getContainer());
		cc= (CMenuItemSprite*)menu->getChildByTag(0);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(HomeWindow::On_Click_Event_MainBG));
	}

	//Button hangup
	for(int j=udROLEINFO;j<=udMOREBTN;j++)
	{
		menu = (CCMenu*)m_pRoot->getChildByTag(j);
		cc= (CMenuItemSprite*)menu->getChildByTag(0);
		cc->setIDX(j);
		cc->setTarget(this,menu_selector(HomeWindow::On_Click_BtnClick));
	}
}

//点击悬浮按钮事件
void HomeWindow::On_Click_BtnClick(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx=cc->getIDX();
	switch(idx){
		case udROLEINFO:
			_heroIllustrateEvent();
			break;
		case udBAG:
			_bagEvent();
			break;
	/*	case udSKILL:
			_skillEvent();
			break;*/
		case udSMELT:
			_strengthenEvent();
			break;
		case udFRIEND:
			_friendEvent();
			break;
		case udSYSTEM:
			_systemEvent();
			break;
		case udMOREBTN:
			_moreEvent();
			break;
		case udMARKET:
			_marketEvent();
			break;
		case udLUATEST:
			_luaEvent();
			break;		
		case udBOSSSCORE:
			_bossEvent();
			break;
		case udOUT:
			_outEvent();
			break;
		case udEMAIL:
			_emailEvent();
			break;
		case udVIP:
			_vipEvent();
			break;
		case  udLIMITEDACTIVITY://限时活动
			_limitedActivityEvent();
			break;
		case udACTIVITY://精彩活动
			_activityEvent();
			break;
		case udPAYPRESENT:
			_paypresentEvent();
			break;
		case udZHENGSHOU:
			_zhengshouEvent();
			break;
	}
}

void HomeWindow::_luaEvent()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
	EVENTSYSTEM->PushEvent(5001);
}


/*
	商城事件
*/
void HomeWindow::_marketEvent(){
	PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_MARKETPWINDOW_);
}

/*
	Boss积分系统
*/
void HomeWindow::_bossEvent()
{
	PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_BOSSSCOREWINDOW_);
	//BOSSSCOREDATAHANDLER->ToServerEnterBoss();
}

void HomeWindow::_heroIllustrateEvent(){
	PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
}

void HomeWindow::_bagEvent(){
	GUIDESYSTEM->Next();
	PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_BAGWINDOW_, _to_event_param_(0), _to_event_param_(_TYPED_EVENT_SHOW_HOMEWINDOW_));
}
/*
	强化界面
*/
void HomeWindow::_strengthenEvent()
{
	GUIDESYSTEM->Next();
	PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
}
/*
	更多里的技能
*/
void HomeWindow::_skillEvent(){
	GUIDESYSTEM->Next();
	PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_); 
	PushEvent(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
}

void HomeWindow::_friendEvent(){
	C2SFriendPacket crpacket;
	crpacket.Send();
	NFC_showCommunicationWating(true);
}
/*
	系统事件
*/
void HomeWindow::_systemEvent(){
	PushEvent(_TYPED_EVENT_SHOW_SYSTEMSETWINDOW_);
}
/*
	出城事件
*/
void HomeWindow::_outEvent()
{
	MissionDataHandler::get_instance2()->setCurMissionID(MissionDataHandler::get_instance2()->getWorldMapStateNum());
	DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_showWindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
	DOTATribeApp::get_instance2()->m_pHomeProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);

}
void HomeWindow::_paypresentEvent(){
	PushEvent(_TYPED_EVENT_SHOW_RECHARGEWINDOW_);
	PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
}

void HomeWindow::_zhengshouEvent(){
	NFC_showCommunicationWating(true);
	C2SRevenuePacket crpacket;
	crpacket.Send();

	_hideArrow_Collection();
}

void HomeWindow::_emailEvent(){
#ifdef kWin32_VLD_Debug_ON
	DOTATribeApp::get_instance2()->SetRun(false);
#endif
	EMAILDATAHANDLER->QueryEmail();
 }

void HomeWindow::_limitedActivityEvent(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LIMITEDACTIVITYWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
}

void HomeWindow::_activityEvent(){
	NFC_showCommunicationWating(true);
	PushEvent(_TYPED_EVENT_SHOW_ACTIVITYWINDOW_);
	PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
	C2SActivityPacket packet;
	packet.Send();

}

void HomeWindow::_vipEvent(){
	//show vip window;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_RECHARGEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
}


void HomeWindow::_moreEvent(){
	if (!ROLEINFODATAHANDLER->playerstatus_->_home_more_isopen){//打开按钮操作
		openMoreBtn(true);
		GUIDESYSTEM->Next();
	}else{//关闭按钮操作
		closeMoreBtn(true);
	}
	ROLEINFODATAHANDLER->playerstatus_->_home_more_isopen=!ROLEINFODATAHANDLER->playerstatus_->_home_more_isopen;
	_showStrengthenHint();
}

//检查MoreItems当前状态
void HomeWindow::checkMoreItems(){
	if (ROLEINFODATAHANDLER->playerstatus_->_home_more_isopen){
		openMoreBtn(false);
	}
}

//open morebtn
void HomeWindow::openMoreBtn(bool isaction){
	if (isaction){
		showMoreItems();
	}else{
		showMoreItems_normal();
	}
}

//close morebtn
void HomeWindow::closeMoreBtn(bool isaction){
	if (isaction){
		hideMoreItems();
	}else{
		hideMoreItems_normal();
	}
}

//show items
void HomeWindow::showMoreItems(){
	for (int i=udROLEINFO;i<=udSYSTEM;i++)
	{
		HWMoreItems* cc=(HWMoreItems*)m_pRootMenu->getChildByTag(i);
		cc->movetoOldPoint();
	}
	_showBottomBar(true);
}

//hide items
void HomeWindow::hideMoreItems(){
	for (int i=udROLEINFO;i<=udSYSTEM;i++)
	{
		HWMoreItems* cc=(HWMoreItems*)m_pRootMenu->getChildByTag(i);
		cc->movetoNewPoint();
	}
	_showBottomBar(false);
}

//show items
void HomeWindow::showMoreItems_normal(){
	//直接显示在展开的位置
	for (int i=udROLEINFO;i<=udSYSTEM;i++)
	{
		HWMoreItems* cc=(HWMoreItems*)m_pRootMenu->getChildByTag(i);
		cc->gotoOldPoint();
	}
	//黄光
	CCNode* bar=NFC_getNode(udBOTTOM_BAR_DECORATION,m_pRoot);
	bar->setPositionY(0);
}

//hide items
void HomeWindow::hideMoreItems_normal(){
	for (int i=udROLEINFO;i<=udSYSTEM;i++)
	{
		HWMoreItems* cc=(HWMoreItems*)m_pRootMenu->getChildByTag(i);
		cc->gotoNewPoint();
	}
	_showBottomBar(false);
}

//显示亮条
void HomeWindow::_showBottomBar(bool isshow){
	CCNode* bar=NFC_getNode(udBOTTOM_BAR_DECORATION,m_pRoot);
	if (isshow)
	{
		if (bar->getPositionY()<0)
		{
			CCMoveBy* mb=CCMoveBy::create(0.1f,ccp(0,bar->getContentSize().height));
			bar->runAction(mb);
		}
	}else{
		if (bar->getPositionY()>=0)
		{
			CCMoveBy* mb=CCMoveBy::create(0.1f,ccp(0,-bar->getContentSize().height));
			bar->runAction(mb);
		}
	}
}

void HomeWindow::Event_RefreshUI_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	IWindow* window=WINDOWMANAGER->GetWindowByType(_TYPED_WINDOW_HOME_);
	HomeWindow* theWindow=dynamic_cast<HomeWindow*>(window);
	assert(theWindow!=NULL);
	theWindow->CheckAllHint();
	theWindow->CheckFunctionLock();
	theWindow->_updateVipNum();
}
	/*
		接收打开More的事件
	*/
void HomeWindow::Event_ShowMoreItems_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	IWindow* window=WINDOWMANAGER->GetWindowByType(_TYPED_WINDOW_HOME_);
	HomeWindow* theWindow=dynamic_cast<HomeWindow*>(window);
	assert(theWindow!=NULL);
	theWindow->openMoreBtn(true);
}
	/*
		检查功能解锁情况
	*/
void HomeWindow::CheckFunctionLock(){
	_checkBuildingLock();
	_checkHangupItemLock();
	_checkOtherLock();
}

	/*
		检查浮动按钮解锁情况
	*/
void HomeWindow::_checkHangupItemLock(){
	_checkHangupItemLock_Email();
	_checkHangupItemLock_Collect();
	_checkHangupItemLock_Boss();
}
	/*
		检查邮箱解锁情况
	*/
void HomeWindow::_checkHangupItemLock_Email(){
	setEmailCorner();
	CCornerNumIcon* cc=(CCornerNumIcon*)NFC_getNode(udEMAILCORNER,m_pRoot);
	cc->setShow(true);
}
	/*
		检查征收解锁情况
	*/
void HomeWindow::_checkHangupItemLock_Collect(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_COLLECTION))//征收
	{
		//hide the btn
		NFC_showNode(udZHENGSHOU,m_pRoot,false);
		//hide the progress title
		CCornerNumIcon* cc=(CCornerNumIcon*)NFC_getNode(udCOLLECTIONCORNER,m_pRoot);
		cc->setShow(false);
	}else{
		NFC_showNode(udZHENGSHOU,m_pRoot,true);
		if (RevenueDataHandler::get_instance2()->m_showArrow)
			_showArrow_Collection();
		setCollectionCorner();
		CCornerNumIcon* cc=(CCornerNumIcon*)NFC_getNode(udCOLLECTIONCORNER,m_pRoot);
		cc->setShow(true);
	}
}

	/*
		检查世界Boss解锁情况
	*/
void HomeWindow::_checkHangupItemLock_Boss(){
	bool isopen=ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_BOSSSCORE);
	NFC_setNodeVisable(udBOSSSCORE,m_pRootNode,isopen);
}

/*
	更新vip等级
*/
void HomeWindow::_updateVipNum()
{
	NFC_setLabelStringInt(udVIPLEVELTEXT,m_pRoot,ROLEINFODATAHANDLER->m_pRIData->vipLevel_);
}

	/*
		设置快速出城
	*/
void HomeWindow::_setQuickOut(){
	_setOutProgress();
	_hideQuickOutHint();
}

	/*
		设置快速进入副本进度文字
	*/
void HomeWindow::_setOutProgress(){
	char tmp[128];
	sprintf(tmp,"%d-%d",ROLEINFODATAHANDLER->m_pRIData->mapId_,ROLEINFODATAHANDLER->m_pRIData->stageId_);
	NFC_setLabelString(udOUTTITLE,m_pRoot,tmp);
}

	/*
		显示点金箭头
	*/
void HomeWindow::_showArrow_Collection()
{
	m_pArrow_Collection = CCSkeletonAnimation::createWithFile(SPINE_GUIDE_ARROW_JSON,SPINE_GUIDE_ARROW_ALTAS);
	if (m_pArrow_Collection)
		m_pArrow_Collection->setAnimation(SPINE_GUIDE_ARROW_DAIJI,true);
	m_pRoot->addChild(m_pArrow_Collection,5);
	m_pArrow_Collection->setRotationX(180.0f);
	CCNode* pNode = m_pRoot->getChildByTag(udZHENGSHOU);
	m_pArrow_Collection->setPosition(ccp(m_pRoot->getChildByTag(udZHENGSHOU)->getChildByTag(0)->getPositionX(),
							m_pRoot->getChildByTag(udZHENGSHOU)->getChildByTag(0)->getPositionY()-m_pRoot->getChildByTag(udZHENGSHOU)->getChildByTag(0)->getContentSize().height/2));

	RevenueDataHandler::get_instance2()->m_showArrow = false;
}

	/*
		销毁点金箭头
	*/
void HomeWindow::_hideArrow_Collection()
{
	if(m_pArrow_Collection)
		m_pArrow_Collection->removeFromParentAndCleanup(true);
	m_pArrow_Collection = NULL;
}

	/*
		显示快速出城箭头
	*/
void HomeWindow::_showArrow_QuickOut(){
	//如果是新手引导状态，则返回
	if (GUIDESYSTEM->isRunning()||ROLEINFODATAHANDLER->m_pRIData->level_<2)
		return;
	//显示箭头
	if (!m_pArrow_QuickOut)
	{
		m_pArrow_QuickOut = CCSkeletonAnimation::createWithFile(SPINE_GUIDE_ARROW_JSON,SPINE_GUIDE_ARROW_ALTAS);
		if (m_pArrow_QuickOut)
			m_pArrow_QuickOut->setAnimation(SPINE_GUIDE_ARROW_DAIJI,true);
		m_pRoot->addChild(m_pArrow_QuickOut,5);
		m_pArrow_QuickOut->setRotation(-135.0f);
		CCNode* pNode = m_pRoot->getChildByTag(udOUT);
		m_pArrow_QuickOut->setPosition(ccp(NFC_getNode(udOUT,m_pRoot)->getChildByTag(0)->getPositionX()-15.0,
			NFC_getNode(udOUT,m_pRoot)->getChildByTag(0)->getPositionY()-NFC_getNode(udOUT,m_pRoot)->getChildByTag(0)->getContentSize().height/2+10.0));
	}
}
	/*
		销毁快速出城箭头
	*/
void HomeWindow::_hideArrow_QuickOut(){
	if(m_pArrow_QuickOut)
		m_pArrow_QuickOut->removeFromParentAndCleanup(true);
	m_pArrow_QuickOut = NULL;
}