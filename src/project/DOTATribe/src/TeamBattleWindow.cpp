//Name ; TeamBattleWindow
//Function：组队副本窗口
//Author : fangjun
//Date: 20130918

#include "../include/TeamBattleWindow.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/DOTATribeApp.h"
#include "../include/EventSystem.h"
#include "../include/TeamBattleDataHandler.h"
#include"../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/TeamBattlePacket.h"
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/MaskNode.h"
#include "../include/CProgressInnerBar.h"
#include "../include/NFControlsManager.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/VariableSystem.h"
#include "../include/config_HomeWindow.h"
#include "../include/GuideSystem.h"
#include "../include/MessageBoxWindow.h"
#include "../include/CSelectedSprite.h"
#include "../include/config_HomeWindow.h"
#include "../include/DTAwardBoard.h"
#include "../include/NFAnimationController.h"

USING_NS_CC;
USING_NS_CC_EXT;

TeamBattleWindow::TeamBattleWindow()
:iGateRewardTimeCount(0)
, m_gateRewardNode(NULL)
, bGateRewardTick(false)
, iselectgateidx(-1)
{
	m_WindowType = _TYPED_WINDOW_TEAMBATTLEWINDOW_;
	m_bModelWindow = false;
}

TeamBattleWindow::~TeamBattleWindow()
{

}

bool TeamBattleWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);
	RegisterEvent(_TYPED_EVENT_UPDATE_TEAMBATTLEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_TEAMBATTLE_GETDATA_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_TEAMBATTLE_RESET_RESULT_, true);

	RegisterEvent(_TYPED_EVENT_RESET_COMFIRM_TEAMBATTLEPROGRESS_, true);
	RegisterEvent(_TYPED_EVENT_TEAMBATTLE_GETTONGGUANJIANGLI_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_TEAMBATTLE_CONFIRM_COSTJEWEL_TEAMREWARD_, true);
	RegisterEvent(_TYPED_EVENT_TEAMBATTLE_REFUSE_COSTJEWEL_TEAMREWARD_, true);

	return IWindow::Init();
}

bool TeamBattleWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();//绘制界面

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_, _to_event_param_(_TYPED_WINDOW_TEAMBATTLEWINDOW_));

		//显示通关奖励界面
		if(TEAMBATTLEDATAHANDLER->m_bHaveGateReward)
		{
			TEAMBATTLEDATAHANDLER->m_bHaveGateReward = false;

			//界面
			//_showGateRewardPage();//修改成不弹展示宝箱界面了。直接领金宝箱

			m_iSelectTongGuanJiangLiType = 2;//领取通关奖励
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_CONFIRM_COSTJEWEL_TEAMREWARD_);
		}
		_checkNewFunc();
		return true;
	}
	while (false);

	return false;
}

	/*
		检查新功能开启
	*/
void TeamBattleWindow::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE)){
		//======显示帮助界面======
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,_to_event_param_(UIViewDataManager::kTEAMBATTLE_HELP_));
		NFC_setNodeVisable(tStartArrow,m_pRootNode,true);
		//======结束新功能开启=======
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE);
	}
}

void TeamBattleWindow::Tick()
{
	IWindow::Tick();

	if(bGateRewardTick == true)
	{
		TickGateReward();
	}

}

void TeamBattleWindow::Destroy()
{
	bGateRewardTick = false;
	iGateRewardTimeCount = 0;

	iselectgateidx = -1;

	PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
	IWindow::Destroy();
}

void TeamBattleWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_)
	{
		PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_TEAMBATTLEWINDOW_)
	{

	}
	else if(iEventType == _TYPED_EVENT_TEAMBATTLE_GETDATA_RESULT_)
	{
		Function_SetTeamBattleDate();
	}
	else if(iEventType == _TYPED_EVENT_TEAMBATTLE_RESET_RESULT_)
	{
		Function_TeamBattleReset();
	}
	else if(iEventType == _TYPED_EVENT_RESET_COMFIRM_TEAMBATTLEPROGRESS_)
	{
		TEAMBATTLEDATAHANDLER->ToServerResetGate();
	}
	else if(iEventType == _TYPED_EVENT_TEAMBATTLE_GETTONGGUANJIANGLI_RESULT_)
	{
		Function_GetTongGuanJiangLiResult();
	}
	else if(iEventType == _TYPED_EVENT_TEAMBATTLE_CONFIRM_COSTJEWEL_TEAMREWARD_)
	{
		TEAMBATTLEDATAHANDLER->ToServerGateReward(m_iSelectTongGuanJiangLiType);
	}
	else if(iEventType == _TYPED_EVENT_TEAMBATTLE_REFUSE_COSTJEWEL_TEAMREWARD_)
	{
		bGateRewardTick = true;
	}
}

cocos2d::CCSize TeamBattleWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCELL;
}

cocos2d::extension::CCTableViewCell* TeamBattleWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}

	_setTableCell(cell,idx);
	
	return cell;
}

unsigned int TeamBattleWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	TTeamBattleData * td = TEAMBATTLEDATAHANDLER->m_pTeamBattleData;

	return td->gateVector.size();
}

void TeamBattleWindow::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{

}
void TeamBattleWindow::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{

}
void TeamBattleWindow::scrollViewDidZoom(cocos2d::extension::CCScrollView* view)
{

}

void TeamBattleWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
}

void TeamBattleWindow::On_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	int idx = item->getIDX();
	if(tag == tCloseBtn)
	{
		iselectgateidx = -1;
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeProcedureToHomeWithLoading();
	}
	else if(tag == tStartBtn)
	{
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_WAITTEAMER_);
	}
	else if(tag == tResetBtn)
	{
		//确认框
		NFC_showMessageBox(kTEAMBATTLE_RESETCOMFIRM, SysLangDataManager::get_instance2()->GetSysLangById(705));
	}
	else if(tag == tHelpBtn)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,_to_event_param_(UIViewDataManager::kTEAMBATTLE_HELP_));
		LOGGERSYSTEM->LogInfo("On_Help");
	}
	else if(tag == tShopBtn)
	{//秘宝商店
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMBATTLEWINDOW_);
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_, _to_event_param_(1), _to_event_param_(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_));
	}
}

void TeamBattleWindow::_initLayout()
{
	m_pRoot=m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMBATTLE, m_pRoot);
	m_gateRewardNode = (MaskNode *)m_pRoot->getChildByTag(tGateRewardNode);
	_mapLayout();

	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(tGateSelectFile);
	gate_normal_board = node->GetViewData().filepath_;
	gate_select_board = node->GetViewData().filepath2_;

	_setTableView();

	_refreshRight(TEAMBATTLEDATAHANDLER->m_iStartGateIdx);
}

void TeamBattleWindow::_showGateRewardPage()
{
	MaskNode * node = m_gateRewardNode;
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMBATTLEGATEREWARD, node);

	//绑定按钮
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	menu = (CCMenu *)node->getChildByTag(rTongPic);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(rTongPic);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_RewardClick));
	menu = (CCMenu *)node->getChildByTag(rYingPic);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(rYingPic);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_RewardClick));
	menu = (CCMenu *)node->getChildByTag(rJinPic);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(rJinPic);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_RewardClick));

	//设置宝箱价格
	int price1 = TEAMBATTLEDATAHANDLER->GetSelectGateInfo()->rewardCostJewel1;
	int price2 = TEAMBATTLEDATAHANDLER->GetSelectGateInfo()->rewardCostJewel2;
	int vip2 = TEAMBATTLEDATAHANDLER->GetSelectGateInfo()->rewardNeedVipLevel2;

	//设置银宝箱价格
	NFC_setLabelStringInt(rYingPrice, node, price1, true);
	//设置金宝箱价格
	NFC_setLabelStringInt(rJinPrice, node, price2, true);
	//判断vip
	if(ROLEINFODATAHANDLER->m_pRIData->vipLevel_ >= vip2)
	{
		NFC_showNode(rNeedVip, node, false);
		NFC_showNode(rNeedVipBG, node, false);
	}
	else
	{
		//设置金宝箱vip级别
		char temp[128] = {0};
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(52).c_str(), vip2);
		NFC_setLabelString(rNeedVip, node, temp, true);
		NFC_showNode(rNeedVipBG, node, true);
	}

	if(ROLEINFODATAHANDLER->m_pRIData->jewels_ < price1)
	{
		menu = (CCMenu *)node->getChildByTag(rYingPic);
		item = (CMenuItemSprite *)menu->getChildByTag(rYingPic);
		item->setEnabled(false);
		
		CCLabelTTF * ttf = (CCLabelTTF *)node->getChildByTag(rYingPrice);
		ttf->setColor(color_BagRed);
	}
	
	if(ROLEINFODATAHANDLER->m_pRIData->jewels_ < price2)
	{
		menu = (CCMenu *)node->getChildByTag(rJinPic);
		item = (CMenuItemSprite *)menu->getChildByTag(rJinPic);
		item->setEnabled(false);

		CCLabelTTF * ttf = (CCLabelTTF *)node->getChildByTag(rJinPrice);
		ttf->setColor(color_BagRed);
	}
	
	if(ROLEINFODATAHANDLER->m_pRIData->vipLevel_ < vip2)
	{
		menu = (CCMenu *)node->getChildByTag(rJinPic);
		item = (CMenuItemSprite *)menu->getChildByTag(rJinPic);
		item->setEnabled(false);
	}
	bGateRewardTick = true;
	iGateRewardTimeCount = 0;

	//提示字的闪烁
	NFC_Action_FadeInAndReverse(node->getChildByTag(rTimeCount), 0.5f, true);
}

void TeamBattleWindow::TickGateReward()
{
	iGateRewardTimeCount++;

	if(iGateRewardTimeCount >= 30 * 30)
	{
		bGateRewardTick = false;
		iGateRewardTimeCount = 0;
		TEAMBATTLEDATAHANDLER->ToServerGateReward(0);
		m_gateRewardNode->removeAllChildrenWithCleanup(true);
	}
	else
	{		
		char temp[128] = {0};
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(57).c_str(), 30 - iGateRewardTimeCount / 30);
		NFC_setLabelString(rTimeCount, m_gateRewardNode, temp, true);
	}
}

void TeamBattleWindow::_mapLayout()
{
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(tCloseBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tCloseBtn);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(tHelpBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tHelpBtn);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(tResetBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tResetBtn);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_Click));

	menu = (CCMenu *)m_pRoot->getChildByTag(tStartBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tStartBtn);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_Click));
	item->setEnabled(false);

	menu = (CCMenu *)m_pRoot->getChildByTag(tShopBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tShopBtn);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_Click));

#if 0
	//去掉秘宝按钮
	if(ROLEINFODATAHANDLER->m_pRIData->level_ < _LV_HOMEWINDOW_NEWSCENE_MIBAOSHOP)
	{
		NFC_showNode(tShopBtn, m_pRoot, false);
		NFC_showNode(tShopBtnLabel, m_pRoot, false);
	}
	else
	{
		NFC_showNode(tShopBtn, m_pRoot, true);
		NFC_showNode(tShopBtnLabel, m_pRoot, true);
	}
#endif


}

void TeamBattleWindow::_setTableView()
{
	CCNode * table = m_pRoot->getChildByTag(tGateTableCell);
	m_szCELL = table->getContentSize();
	m_pTable =(CCTableView*)m_pRootNode->getChildByTag(tGateTableView);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);//横向
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	_refreshTableView(m_pTable);

	CCPoint offset = TEAMBATTLEDATAHANDLER->m_fOldGateTableOffset;
	
	int idx = TEAMBATTLEDATAHANDLER->m_iStartGateIdx;
	if(idx > 0)
	{
		offset.x = 0 - (idx - 1) * cellSizeForTable(m_pTable).width;

		NFC_setOffsetForTableView(m_pTable, offset);
	}
}

void TeamBattleWindow::_createTableCell(cocos2d::extension::CCTableViewCell* cell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMBATTLECELL,cell);
}

void TeamBattleWindow::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx)
{	
	TTeamBattleData* td = TEAMBATTLEDATAHANDLER->m_pTeamBattleData;

	if(idx >= td->gateVector.size())
		return;

	TGateItem * tgi =td->gateVector[idx];

	bool open = false;
	if(ROLEINFODATAHANDLER->m_pRIData->level_ >= tgi->minLevel)
		open = true;
	bool prepass = false;
	if (tgi->mIspreMappass)
		prepass = true;
	else
		prepass = false;
	if (!prepass)
	{
		open = false;
	}
	char temp[1024]={0};
	//前置显示
	NFC_setNodeVisable(cPREPASSBG,cell,!prepass);	
	if (idx == 0)
	{
		NFC_setNodeVisable(cPREPASSBG,cell,false);
		NFC_setNodeVisable(cPREPASSTTF,cell,false);
	}
	else
	{
		if (!prepass)
		{
			TGateItem * preTdata =td->gateVector[idx-1];
			if (preTdata!=NULL)
			{
				sprintf(temp,SysLangDataManager::get_instance2()->GetSysLangById(6081).c_str(),preTdata->gateName.c_str());
				NFC_setLabelString(cPREPASSTTF,cell,temp,!prepass);
				memset(temp,0,sizeof(temp));
			}
		}
		else
		{
			NFC_setNodeVisable(cPREPASSBG,cell,false);
			NFC_setNodeVisable(cPREPASSTTF,cell,false);
		}
	}
	//副本名称背景
	NFC_showNode(cNameBg, cell, open);
	//副本名称
	NFC_setLabelString(cName, cell, tgi->gateName, open);
	//参与人数
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(23).c_str(), tgi->totalPlayer);
	NFC_setLabelString(cPeople, cell, temp, open);
	//进度
	if(tgi->nowStage > 0)
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(24).c_str(), tgi->nowStage, tgi->maxStage);
	else
		std::strcpy(temp, SysLangDataManager::get_instance2()->GetSysLangById(58).c_str());
	NFC_setLabelString(cProgress, cell, temp, open);

	//开启等级
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(25).c_str(), tgi->minLevel);
	NFC_setLabelString(cNeedLevel, cell, temp, !open);

	//底板
	CCMenu * menu = (CCMenu*)cell->getChildByTag(cBg);
	CMenuItemSprite* item =(CMenuItemSprite*)menu->getChildByTag(0);
	item->setIDX(idx);
	item->setTarget(this, menu_selector(TeamBattleWindow::On_Btn_CellClick));
	CCSprite * sp = CCSprite::create();
	sp->setProperty("File", gate_normal_board);
	item->setNormalImage(sp);
	CSpriteSelected* sp_sel = CSpriteSelected::create(gate_select_board.c_str(), gate_normal_board.c_str());
	item->setSelectedImage(sp_sel);

	item->setEnabled(tgi->canSelect);

	//关图
	NFC_setPicForCCSprite(cGatePic, cell, RESOURCEDAIDMANAGER->getDataByID(tgi->iconId), true);

	//关图灰层
	NFC_showNode(cGatePicGrey, cell, !open);

	//箭头状态
	cocos2d::extension::CCTableViewCell * cell_begin = NULL;
	cell_begin = m_pTable->cellAtIndex(0);
	if(cell_begin && cell_begin->isVisible())
	{
		NFC_setNodeVisable(tLeftMOVEArrow,m_pRoot,false);
		NFC_setNodeVisable(tLeftArrow,m_pRoot,true);
	}
	else
	{
		NFC_setNodeVisable(tLeftMOVEArrow,m_pRoot,true);
		NFC_setNodeVisable(tLeftArrow,m_pRoot,false);
	}
	cocos2d::extension::CCTableViewCell * cell_end = NULL;
	cell_end = m_pTable->cellAtIndex(numberOfCellsInTableView(m_pTable) - 1);
	if(cell_end && cell_end->isVisible())
	{
		NFC_setNodeVisable(tRightMOVEArrow,m_pRoot,false);
		NFC_setNodeVisable(tRightArrow,m_pRoot,true);
	}
	else
	{
		NFC_setNodeVisable(tRightMOVEArrow,m_pRoot,true);
		NFC_setNodeVisable(tRightArrow,m_pRoot,false);
	}

	//首次进入时需要按照select的关卡判断
	if(iselectgateidx < 0)
	{
		if(TEAMBATTLEDATAHANDLER->m_iStartGateIdx < 0)
		{
			//找到最大可开始的关卡
			TEAMBATTLEDATAHANDLER->m_iStartGateIdx = TEAMBATTLEDATAHANDLER->GetMaxCanStartGateIdx();
			iselectgateidx = TEAMBATTLEDATAHANDLER->m_iStartGateIdx;

			if(iselectgateidx == 0 && idx == 0)
			{//默认选中
				TEAMBATTLEDATAHANDLER->m_iStartGateIdx = idx;
				iselectgateidx = idx;
				item->selected(true);
				_refreshRight(TEAMBATTLEDATAHANDLER->m_iStartGateIdx);
			}
		}
		else
		{
			if(TEAMBATTLEDATAHANDLER->m_iStartGateIdx == item->getIDX())
			{
				item->selected(true);
				iselectgateidx = idx;
			}
			else
			{
				item->unselected();
			}
		}

	}
	else
	{
		if(iselectgateidx == item->getIDX())
		{
			item->selected(true);
		}
		else
		{
			item->unselected();
		}
	}

}


void TeamBattleWindow::On_Btn_CellClick(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int idx = item->getIDX();
	//将上一个按钮取消选中
	cocos2d::extension::CCTableViewCell * cell= m_pTable->cellAtIndex(iselectgateidx);
	if(cell)
	{
		CCMenu * menu = (CCMenu*)cell->getChildByTag(cBg);
		CMenuItemSprite* item =(CMenuItemSprite*)menu->getChildByTag(0);
		item->unselected();
	}

	item->selected(true);

	iselectgateidx = idx;
	_refreshRight(idx);

	TEAMBATTLEDATAHANDLER->m_fOldGateTableOffset = m_pTable->getContentOffset();
	TEAMBATTLEDATAHANDLER->m_fOldGateTableWidth = m_pTable->getContentSize().width;

}

void TeamBattleWindow::On_Btn_RewardClick(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	
	if(tag == rTongPic)
	{
		MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(tGateRewardNode);
		NFC_showNode(rTongSelectPic, node, true);
		NFC_showNode(rYingSelectPic, node, false);
		NFC_showNode(rJinSelectPic, node, false);
		TEAMBATTLEDATAHANDLER->ToServerGateReward(0);
	}
	else if(tag == rYingPic)
	{
		MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(tGateRewardNode);
		NFC_showNode(rTongSelectPic, node, false);
		NFC_showNode(rYingSelectPic, node, true);
		NFC_showNode(rJinSelectPic, node, false);

		char temp[512] = {0};
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(56).c_str(), TEAMBATTLEDATAHANDLER->GetSelectGateInfo()->rewardCostJewel1);
		NFC_showMessageBox(kCOSTJEWEL_TEAMREWARD, temp);
		
		m_iSelectTongGuanJiangLiType = 1;
	}
	else if(tag == rJinPic)
	{
		MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(tGateRewardNode);
		NFC_showNode(rTongSelectPic, node, false);
		NFC_showNode(rYingSelectPic, node, false);
		NFC_showNode(rJinSelectPic, node, true);

		char temp[512] = {0};
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(56).c_str(), TEAMBATTLEDATAHANDLER->GetSelectGateInfo()->rewardCostJewel2);
		NFC_showMessageBox(kCOSTJEWEL_TEAMREWARD, temp);

		m_iSelectTongGuanJiangLiType = 2;
	}
}

void TeamBattleWindow::On_Gate_RewardTipsClick(cocos2d::CCObject * pSender)
{
	TGateItem * tgi = TEAMBATTLEDATAHANDLER->GetGateInfoByIdx(iselectgateidx);
	if(tgi == NULL)
		return;
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int index = item->getIDX();

	TRewardItem * reward = tgi->rewardVector[index];

	NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(reward->templateId, _TYPED_WINDOW_TEAMBATTLEWINDOW_);
}

//刷新右面的信息
void TeamBattleWindow::_refreshRight(int gateIdx)
{
	TGateItem * tgi = TEAMBATTLEDATAHANDLER->GetGateInfoByIdx(gateIdx);
	if(tgi == NULL)
		return;

	if(ROLEINFODATAHANDLER->m_pRIData->level_ >= tgi->minLevel)
	{//设置选中的关卡idx
		TEAMBATTLEDATAHANDLER->m_iStartGateIdx = gateIdx;
	}

	char temp[1024] = {0};

	//当日挑战次数
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(22).c_str(), TEAMBATTLEDATAHANDLER->m_pTeamBattleData->challengeTimes, TEAMBATTLEDATAHANDLER->m_pTeamBattleData->maxChallengeTimes - TEAMBATTLEDATAHANDLER->m_pTeamBattleData->challengeTimes);
	NFC_setLabelString(tTodayTimes, m_pRoot, temp, true);

	//重置按钮
	if(tgi->nowStage > 0)
	{
		NFC_setNodeVisable(tResetBtn, m_pRoot, true);
		NFC_setNodeVisable(tResetBtnLabel, m_pRoot, true);
	}
	else
	{
		NFC_setNodeVisable(tResetBtn, m_pRoot, false);
		NFC_setNodeVisable(tResetBtnLabel, m_pRoot, false);
	}

	//reward
	int i = 0;
	std::string file;
	DTAwardBoard * dtab = NULL;
	for (i = 0; i < (int)tgi->rewardVector.size(); i++)
	{
		dtab = (DTAwardBoard *)m_pRoot->getChildByTag(tReward1 + i);
		dtab->ChangeObject(tgi->rewardVector[i]->quality, tgi->rewardVector[i]->iconId, 1);
		dtab->setTarget(this, menu_selector(TeamBattleWindow::On_Gate_RewardTipsClick));
		dtab->setIDX(i);
		dtab->setVisible(true);
		
	}
	for(; i < 4; ++i)
	{
		dtab = (DTAwardBoard *)m_pRoot->getChildByTag(tReward1 + i);
		dtab->setVisible(false);
	}


// 	CCMenu * menu = NULL;
// 	CMenuItemSprite * item = NULL;
// 	for (i = 0; i < (int)tgi->rewardVector.size(); i++)
// 	{
// 		file = RESOURCEDAIDMANAGER->getDataByID(tgi->rewardVector[i]->iconId);
// 		menu = (CCMenu *)m_pRoot->getChildByTag(tReward1 + i);
// 		item = (CMenuItemSprite *)menu->getChildByTag(0);
// 		CCSprite *sp = CCSprite::create(file.c_str());
// 		if(tgi->rewardVector[i]->catogory == kBAGSKIN)
// 		{
// 			sp->setScale((float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
// 		}
// 		item->setNormalImage(sp);
// 		sp = CCSprite::create(file.c_str());
// 		if(tgi->rewardVector[i]->catogory == kBAGSKIN)
// 		{
// 			sp->setScale((float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
// 		}
// 		item->setSelectedImage(sp);
// 		item->setTarget(this, menu_selector(TeamBattleWindow::On_Gate_RewardTipsClick));
// 		item->setIDX(i);
// 
// 		menu->setVisible(true);
// 
// 		file = varConfig::getCardBGFilePath(tgi->rewardVector[i]->quality);
// 		_set_texture(tReward1Q + i,m_pRoot,file.c_str());
// 	}
// 	std::string normalbg = varConfig::getCardNormalBGFilePath();
// 	for(; i < 3; ++i)
// 	{
// 		_set_visible(tReward1 + i, m_pRoot, false);
// 		_set_texture(tReward1Q + i, m_pRoot, normalbg.c_str());
// 	}

	//开始按钮
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(tStartBtn);
	CMenuItemSprite *item = (CMenuItemSprite *)menu->getChildByTag(tStartBtn);
	item->setEnabled(true);
	if(ROLEINFODATAHANDLER->m_pRIData->level_ >= tgi->minLevel)
	{
		NFC_showNode(tStartBtn, m_pRoot, true);
		if(tgi->nowStage > 0)
		{//继续闯关
			NFC_setLabelString(tStartBtnLabel, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(29), true);
			NFC_showNode(tCostTips, m_pRoot, false);
		}
		else
		{//开始闯关
			NFC_setLabelString(tStartBtnLabel, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(28), true);
			NFC_showNode(tCostTips, m_pRoot, true);
		}
	}
	else
	{
		NFC_showNode(tCostTips, m_pRoot, false);
		NFC_showNode(tStartBtn, m_pRoot, false);
		NFC_showNode(tStartBtnLabel, m_pRoot, false);
	}

}


//设置界面信息
void TeamBattleWindow::Function_SetTeamBattleDate()
{
	TTeamBattleData* td = TEAMBATTLEDATAHANDLER->m_pTeamBattleData;
	TGateItem * tgi = td->gateVector[0];
	TRewardItem * tri = tgi->rewardVector[0];
	char temp[128] = "";

    //显示所有最低等级
	_refreshTableView(m_pTable);

	if(TEAMBATTLEDATAHANDLER->m_iStartGateIdx > 0)
	{
		TEAMBATTLEDATAHANDLER->m_fOldGateTableOffset.x = 0 - (TEAMBATTLEDATAHANDLER->m_iStartGateIdx - 1) * cellSizeForTable(m_pTable).width;
		NFC_setOffsetForTableView(m_pTable, TEAMBATTLEDATAHANDLER->m_fOldGateTableOffset);
	}

	_refreshRight(TEAMBATTLEDATAHANDLER->m_iStartGateIdx);

}


//设置重置进度信息
void TeamBattleWindow::Function_TeamBattleReset()
{
	TGateItem * ti = TEAMBATTLEDATAHANDLER->GetSelectGateInfo();

	cocos2d::extension::CCTableViewCell * cell= m_pTable -> cellAtIndex(TEAMBATTLEDATAHANDLER->m_iStartGateIdx);
	//进度
	NFC_setLabelString(cProgress, cell, SysLangDataManager::get_instance2()->GetSysLangById(58), true);
	//重置按钮
	NFC_setNodeVisable(tResetBtn, m_pRoot, false);
	NFC_setNodeVisable(tResetBtnLabel, m_pRoot, false);
	//开始挑战
	NFC_setLabelString(tStartBtnLabel, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(28), true);
}

void TeamBattleWindow::Function_GetTongGuanJiangLiResult()
{
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(tGateRewardNode);
	node->removeAllChildrenWithCleanup(true);

	bGateRewardTick = false;
}

void TeamBattleWindow::_setTTFText(int key, const char * text)
{
	CCLabelTTF * ttf = (CCLabelTTF *)m_pRoot->getChildByTag(key);
	ttf->setString(text);
}

void TeamBattleWindow::_setTTFText(int key, int text)
{
	char tmp[128] = "";
	sprintf(tmp, "%d", text);
	CCLabelTTF * ttf = (CCLabelTTF *)m_pRoot->getChildByTag(key);
	ttf->setString(tmp);
}

void TeamBattleWindow::_setTexture(int tag,  cocos2d::CCNode * parent, const char *  picpath)
{
	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(picpath);
	CCSprite * sp = (CCSprite*)parent->getChildByTag(tag);
	if(texture)
	{
		sp->setProperty("File",picpath);
		sp->setVisible(true);
	}
}

