//Name ; TeamBattleWindow
//Function：组队副本窗口
//Author : fangjun
//Date: 20130918

#include "../include/TeamSelectWindow.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/TeamBattleDataHandler.h"
#include "../include/DOTATribeApp.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include <string>
#include "../include/CMenuItemSprite.h"
#include "../include/EventSystem.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/ClientConstDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/CSprite.h"
#include "../include/TimeSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/ChatWindow.h"
#include "../include/ChatPacket.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MessageBoxWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/MaskNode.h"
#include "../include/FriendDataHandler.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

TeamSelectWindow::TeamSelectWindow()
:_TAG_CHENG_(udPLAYERBG2 - udPLAYERBG1)
{
	m_WindowType = _TYPED_WINDOW_TEAMSELECTWINDOW_;
	m_bModelWindow = false;
}
TeamSelectWindow::~TeamSelectWindow()
{

}

bool TeamSelectWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_TEAMSELECTWINDOW_);
	RegisterEvent(_TYPED_EVENT_CHANGETO_TEAMBATTLE_);
	RegisterEvent(_TYPED_EVENT_UPDATE_TEAMSELECTWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_TEAMSELECTWINDOW_, true);

	RegisterEvent(_TYPED_EVENT_TEAMSELECT_GETSTAGEDATA_RESULT_, true);
	RegisterEvent(_TYPED_EVENT_TEAMSELECT_GETTEAMLIST_, true);//获得队伍列表
	RegisterEvent(_TYPED_EVENT_TEAMSELECT_GETMYTEAM_, true);//获得自己所在队伍数据
	RegisterEvent(_TYPED_EVENT_TEAMSELECT_BEREMOVED_, true);//我被踢出游戏

	RegisterEvent(_TYPED_EVENT_TEAMSELECT_GETSLAVElIST_RESULT_, true);//获得奴隶列表
	RegisterEvent(_TYPED_EVENT_TEAMSELECT_GETMERCENARYLIST_RESULT_, true);//获得我的可雇佣佣兵列表
	return IWindow::Init();
}

bool TeamSelectWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();//绘制界面
		return true;
	}
	while (false);

	return false;
}

void TeamSelectWindow::Tick()
{
	IWindow::Tick();

	if(TEAMBATTLEDATAHANDLER->m_bOneMsgIsCoolDowning)
	{
		double waitTime = 1.0*(TimeSystem::get_instance2()->GetCurrentMicroSecond() - TEAMBATTLEDATAHANDLER->m_lCoolDownTimeCount)/1000000;
		if(waitTime >= 60.0)
		{
			TEAMBATTLEDATAHANDLER->m_bOneMsgIsCoolDowning = false;
			NFC_setEnabledForMenuItem(udONEMSGBTN, udONEMSGBTN, m_pRoot, true);
			NFC_setEnabledForMenuItem(udONEMSGBG, udONEMSGBG, m_pRoot, true);
			cocos2d::CCLabelTTF * cc = (cocos2d::CCLabelTTF *)m_pRoot->getChildByTag(udONEMSGBTNTTF);
			cc->setString(SysLangDataManager::get_instance2()->GetSysLangById(601).c_str());
		}
		else
		{
			int last = 60 - (int)waitTime;
			char temp[8] = {0};
			std::sprintf(temp, "%02d:%02d", last / 60, last % 60);
			cocos2d::CCLabelTTF * cc = (cocos2d::CCLabelTTF *)m_pRoot->getChildByTag(udONEMSGBTNTTF);
			cc->setString(temp);
		}
	}

}

void TeamSelectWindow::Destroy()
{
	PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);//显示聊天界面

	//Fadeout(0.5f);
	IWindow::Destroy();
}

void TeamSelectWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_TEAMSELECTWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_CHANGETO_TEAMBATTLE_)
	{
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pTeamBattleProcedure);
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_WAITTEAMER_);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_TEAMSELECTWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_TEAMSELECTWINDOW_)
	{

	}
	else if(iEventType == _TYPED_EVENT_TEAMSELECT_GETSTAGEDATA_RESULT_)
	{
		Function_GetNowStageData();
	}
	else if(iEventType == _TYPED_EVENT_TEAMSELECT_GETTEAMLIST_)
	{//获得队伍列表数据
		Function_GetTeamListData();
	}
	else if(iEventType == _TYPED_EVENT_TEAMSELECT_GETMYTEAM_)
	{//获得自己队伍数据
		Function_GetMyTeamData();
	}
	else if(iEventType == _TYPED_EVENT_TEAMSELECT_BEREMOVED_)
	{//我被踢了
		std::list<std::string>::iterator it = paramList.begin();
		int removedType = 0;
		int isLeader = 0;
		removedType = atoi((*it).c_str());
		it++;
		isLeader = atoi((*it).c_str());
		Function_BeRemovedFromTeam(removedType, isLeader);
	}
	else if(iEventType == _TYPED_EVENT_TEAMSELECT_GETSLAVElIST_RESULT_)
	{
		Function_GetSlaveList();
	}
	else if(iEventType == _TYPED_EVENT_TEAMSELECT_GETMERCENARYLIST_RESULT_)
	{
		Function_GetMercenaryList();
	}
}

void TeamSelectWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);//显示聊天界面

}

void TeamSelectWindow::_initLayout()
{
	m_pRoot= m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMSELECT, m_pRoot);
	_mapBtn();

	//显示副本关卡名称
	if(TEAMBATTLEDATAHANDLER->m_pTeamStageData != NULL)
	{
		NFC_setLabelString(udFUBENNAMETTF, m_pRoot, TEAMBATTLEDATAHANDLER->m_pTeamStageData->stageName.c_str(),true);
	}

	//初始化部分界面数据
	_initData();

	_setTableView();

	_refreshMyTeamShow();
}

void TeamSelectWindow::_initData()
{
	

}

void TeamSelectWindow::_setTableView()
{
	CCNode * table = m_pRoot->getChildByTag(udTableCell);
	m_szTeamCell = table->getContentSize();

	m_pTeamTable =(CCTableView*)m_pRoot->getChildByTag(udTableView);//modify from m_pRootNode
	m_pTeamTable->setDataSource(this);
	m_pTeamTable->setDelegate(this);
	m_pTeamTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTeamTable->setTouchEnabled(true);
	m_pTeamTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	_refreshTableView(m_pTeamTable);
}

void TeamSelectWindow::_createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell)
{
	if(table == m_pTeamTable)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMSELECTCELL,cell);
	}
	else if(table == m_pSlaveTable)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMSELECTVIEWCELL_SLAVE, cell);
	}
	else if(table == m_pMercenaryTable)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMSELECTVIEWCELL_MERCENARY, cell);
	}
}

void TeamSelectWindow::_setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell,int idx)
{
	if(table == m_pTeamTable)
	{
		//设置cell中的信息，并且绑定事件
		if(TEAMBATTLEDATAHANDLER->m_pTeamListData->teamVector.size() == 0)
			return;
		TTeamListItem * ti = TEAMBATTLEDATAHANDLER->m_pTeamListData->teamVector[idx];
		assert(ti);
		//队伍名字
		NFC_setLabelString(udTEAMLEADER, cell, ti->leaderName.c_str(),true);
		//人数
		char temp[8] = {0};
		sprintf(temp, "%d/3", ti->memberCount);
		NFC_setLabelString(udMEMBERNUM, cell, temp,true);
		//加入按钮

		CCMenu * menu = (CCMenu *)cell->getChildByTag(udJOINBTN);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(TeamSelectWindow::On_JoinTeam_Click));
		item->setIDX(idx);
		item->setVisible(true);
		NFC_showNode(udJOINTTF, cell, true);

		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData)
		{
			if(ti->leaderPlayerId == TEAMBATTLEDATAHANDLER->GetMyTeamLeaderId())
			{
				item->setVisible(false);
				NFC_showNode(udJOINTTF, cell, false);
			}
			else
			{
				item->setVisible(true);
				NFC_showNode(udJOINTTF, cell, true);
			}
		}


	}
	else if(table == m_pSlaveTable)
	{
		if(TEAMBATTLEDATAHANDLER->m_pSlaveList == NULL)
			return;
		TSlaveItem * slave = TEAMBATTLEDATAHANDLER->m_pSlaveList->slaveVector[idx];
		if(slave == NULL)
			return;


		NFC_setDTHeroIcon(sQuality,cell,slave->iconId,true);
		NFC_setDTHeroQualiy(sQuality,cell,slave->quality);


		//NFC_setPicForCCSprite(sQuality, cell, varConfig::getCardBGFilePath(slave->quality).c_str(), true);
		//NFC_setPicForCCSprite(sIcon, cell, RESOURCEDAIDMANAGER->getDataByID(slave->iconId).c_str(), true);
		//NFC_setPicScale(sIcon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
		NFC_setLabelString(sPlayerName, cell, slave->playerName,true);
		char temp[128] = {0};
		sprintf(temp, "%s", slave->skinName.c_str());
		NFC_setLabelString(sSkinName, cell, temp, true);
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(374).c_str(), slave->playerLevel);
		NFC_setLabelString(sLevel, cell, temp, true);
		NFC_setLabelStringInt(sBtlCapaValue, cell, slave->btlCapa, true);
		int time = slave->leftMinute / 60;
		if(time > 0)
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(660).c_str(), time);	
		else
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(661).c_str(), slave->leftMinute);
		NFC_setLabelString(sLeftTimeValue, cell, temp, true);

		CCMenu * menu = (CCMenu *)cell->getChildByTag(sCallBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(TeamSelectWindow::On_Slave_Hire_Click));
		item->setIDX(idx);
	}
	else if(table == m_pMercenaryTable)
	{
		if(TEAMBATTLEDATAHANDLER->m_pMercenaryList == NULL)
			return;
		TMercenaryItem * mercenary = TEAMBATTLEDATAHANDLER->m_pMercenaryList->mercenaryVector[idx];
		if(mercenary == NULL)
			return;

		NFC_setDTHeroIcon(mQuality,cell,mercenary->iconId,true);
		NFC_setDTHeroQualiy(mQuality,cell,mercenary->quality);

		//NFC_setPicForCCSprite(mQuality, cell, varConfig::getCardBGFilePath(mercenary->quality).c_str(), true);
		//NFC_setPicForCCSprite(mIcon, cell, RESOURCEDAIDMANAGER->getDataByID(mercenary->iconId).c_str(), true);
		//NFC_setPicScale(sIcon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
		NFC_setLabelString(mPlayerName, cell, mercenary->playerName,true);
		char temp[128] = {0};
		sprintf(temp, "%s", mercenary->skinName.c_str());
		NFC_setLabelString(mSkinName, cell, temp, true);
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(374).c_str(), mercenary->playerLevel);
		NFC_setLabelString(mLevel, cell, temp, true);
		NFC_setLabelStringInt(mBtlCapaValue, cell, mercenary->btlCapa, true);
		NFC_setLabelStringInt(mPriceValue, cell, mercenary->hirePrice, true);

		CCMenu * menu = (CCMenu *)cell->getChildByTag(mHireBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(TeamSelectWindow::On_Mercenary_Hire_Click));
		item->setIDX(idx);
	}

}

cocos2d::CCSize TeamSelectWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	if(table == m_pTeamTable)
	{
		return m_szTeamCell;
	}
	else if(table == m_pSlaveTable)
	{
		return m_szSlaveCell;
	}
	else if(table == m_pMercenaryTable)
	{
		return m_szMercenaryCell;
	}
	else
	{
		return m_szTeamCell;
	}
}

cocos2d::extension::CCTableViewCell* TeamSelectWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(table, cell);
	}
	_setTableCell(table, cell, idx);

	return cell;
}

unsigned int TeamSelectWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(table == m_pTeamTable)
	{
		return TEAMBATTLEDATAHANDLER->m_pTeamListData->teamVector.size();
	}
	else if(table == m_pSlaveTable)
	{
		return TEAMBATTLEDATAHANDLER->m_pSlaveList->slaveVector.size();
	}
	else if(table == m_pMercenaryTable)
	{
		return TEAMBATTLEDATAHANDLER->m_pMercenaryList->mercenaryVector.size();
	}
	else
	{
		return 0;
	}
}

void TeamSelectWindow::_createGrayLayer()
{
	// 	m_pAnimationGrayLayer = CPriorityLayerColor::create(ccc4(0,0,0,0),3000,2000,kPRIORITYLOW2);
	// 	m_pAnimationGrayLayer->setAnchorPoint(ccp(0,0));
	// 	m_pAnimationGrayLayer->setPosition(ccp(0,0));
	// 	this->addChild(m_pAnimationGrayLayer,10);
}

void TeamSelectWindow::_removeGrayLayer()
{
	// 	if(m_pAnimationGrayLayer)
	// 		m_pAnimationGrayLayer->removeFromParentAndCleanup(true);
	// 	m_pAnimationGrayLayer = NULL;
}

void TeamSelectWindow::_mapBtn()
{
	//关闭
	CCMenu* menu = (CCMenu*)m_pRoot->getChildByTag(udCLOSEBTN);
	CMenuItemSprite* item = (CMenuItemSprite*)menu->getChildByTag(0);
    item->setIDX(udCLOSEBTN);
    item->setTag(udCLOSEBTN);
	item->setTarget(this,menu_selector(TeamSelectWindow::On_Btn_Click));

	//开始按钮
	menu = (CCMenu*)m_pRoot->getChildByTag(udBEGINBTN);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(udBEGINBTN);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));

	//离开队伍按钮
	menu = (CCMenu*)m_pRoot->getChildByTag(udLEAVEBTN);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(udLEAVEBTN);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));

	//创建队伍按钮
	menu = (CCMenu*)m_pRoot->getChildByTag(udBUILDTEAMBTN);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(udBUILDTEAMBTN);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));

	//解散队伍按钮
	menu = (CCMenu*)m_pRoot->getChildByTag(udDESTROYTEAMBTN);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(udDESTROYTEAMBTN);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));

	//一键喊话按钮
	menu = (CCMenu*)m_pRoot->getChildByTag(udONEMSGBTN);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	onekey0 = item;
	item->setTag(udONEMSGBTN);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));
	if(TEAMBATTLEDATAHANDLER->m_bOneMsgIsCoolDowning)
	{
		item->setEnabled(false);
	}
	menu = (CCMenu *)m_pRoot->getChildByTag(udONEMSGBG);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	onekey1 = item;
	item->setTag(udONEMSGBG);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));
	if(TEAMBATTLEDATAHANDLER->m_bOneMsgIsCoolDowning)
	{
		item->setEnabled(false);
	}

	onekey2 = m_pRoot->getChildByTag(udONEMSGBTNTTF);

	onekey0->setVisible(false);
	onekey1->setVisible(false);
	onekey2->setVisible(false);

	//移除和查看资料按钮
	for(int i = udROMOVEBTN1; i <= udCHECKBTN3;)
	{
		menu = (CCMenu*)m_pRoot->getChildByTag(i);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(i);
		item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));
		i += 2;
	}

	//上下箭头
	for(int i = ud1DOWNBTN; i <= ud3UPBTN; ++i)
	{
		menu = (CCMenu*)m_pRoot->getChildByTag(i);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(i);
		item->setTarget(this, menu_selector(TeamSelectWindow::On_Btn_Click));
	}

}

void TeamSelectWindow::clickEvent(int idx,int type)
{
	
}

bool TeamSelectWindow::containsTheCopy(cocos2d::CCSprite* copy, int type)
{
	assert(copy!=NULL);
	//判断有多少个物品从而生成多少个矩形
	int size = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector.size();
	CCRect * destRect = new CCRect[size];//此rect组合包含自己所在的rect
	for(int i = 0; i < size; ++i)
	{
		CCSprite * iconr = (CCSprite *)m_pRoot->getChildByTag(udQUALITY1 + i * _TAG_CHENG_);
		const CCPoint & anchor = iconr->getAnchorPoint();
		const CCSize & sz = iconr->getContentSize();
		CCPoint cp = iconr->getPosition();
		cp = convertToWorldSpaceAR(cp);
		destRect[i].setRect(cp.x - anchor.x * sz.width, cp.y - anchor.y * sz.height, sz.width, sz.height);
	}

	//获得copy的rect
	const CCPoint & anchorCopy = copy->getAnchorPoint();
	const CCPoint & cpCopy = copy->getPosition();
	const CCSize & szCopy = copy->getContentSize();
	CCRect rect = CCRectMake(cpCopy.x - anchorCopy.x * szCopy.width, cpCopy.y - anchorCopy.y * szCopy.height, szCopy.width, szCopy.height);

	//判断重叠，需要判断是否是和自己框的重合，这必须注意,从tag判断列表第几个
	for(int i = 0; i < size; ++i)
	{
		int tag = copy->getTag();
		if(tag == i)
			continue;
		if(rect.intersectsRect(destRect[i]))
		{
			//交换这两个队员,两次交换是为了不改变内存中的数据排列顺序
			TEAMBATTLEDATAHANDLER->ToServerSwitchMemberPlace(i, tag);
		}
	}

	return true;
}

void TeamSelectWindow::On_Btn_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;
	int tag = cc->getTag();
	if(tag == udCLOSEBTN)
	{
		TEAMBATTLEDATAHANDLER->ToServerStopTeamSync();
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData)
		{
			delete TEAMBATTLEDATAHANDLER->m_pMyTeamData;
			TEAMBATTLEDATAHANDLER->m_pMyTeamData = NULL;
		}
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMSELECTWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);

	}
	else if(tag == udBEGINBTN)
	{//开始
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->isIamLeader <= 0)
		{
			return;
		}
		TEAMBATTLEDATAHANDLER->ToServerStartStage();
	}
	else if(tag == udLEAVEBTN)
	{//离开队伍
		TEAMBATTLEDATAHANDLER->m_iMyTeamId = -1;//这步可能没什么作用
		TEAMBATTLEDATAHANDLER->ToServerRemoveMember(-2);//离开队伍
	}
	else if(tag == udBUILDTEAMBTN)
	{//创建队伍
		TEAMBATTLEDATAHANDLER->m_iMyTeamId = -1;
		TEAMBATTLEDATAHANDLER->ToServerJoinTeam();
	}
	else if(tag == udDESTROYTEAMBTN)
	{//解散队伍
		TEAMBATTLEDATAHANDLER->m_iMyTeamId = -1;//这步可能没什么作用
		TEAMBATTLEDATAHANDLER->ToServerRemoveMember(-1);//解散
	}
	else if(tag == udONEMSGBTN || tag == udONEMSGBG)
	{
		//一键喊话,内容
		int sysid = rand() % 10 + 2025;
		std::string msgtemplate = SysLangDataManager::get_instance2()->GetSysLangById(sysid);
		char temp[1024] = {0};

		if(TEAMBATTLEDATAHANDLER->m_pTeamStageData == NULL)
			return;

		sprintf(temp, msgtemplate.c_str(), TEAMBATTLEDATAHANDLER->m_pTeamStageData->stageName.c_str());
		//喊话
		C2SChatPacket packet(ChatWindow::_Chat_Channel_World, -1, temp);
		packet.Send();

		//喊完之后冷却60秒
		TEAMBATTLEDATAHANDLER->m_lCoolDownTimeCount = TimeSystem::get_instance2()->GetCurrentMicroSecond();
		TEAMBATTLEDATAHANDLER->m_bOneMsgIsCoolDowning = true;
		NFC_setEnabledForMenuItem(udONEMSGBTN, udONEMSGBTN, m_pRoot, false);
		NFC_setEnabledForMenuItem(udONEMSGBG, udONEMSGBG, m_pRoot, false);

	}
	else if(tag == udROMOVEBTN1)
	{//移除或者使用佣兵
		if(cc->getIDX() == 1)
		{
			_removeMember(0);
		}
		else
		{//租用佣兵
			_hireMercenary();
		}
	}
	else if(tag == udCHECKBTN1)
	{//查看或者使用奴隶
		if(cc->getIDX() == 1)
		{
			_checkMemberInfo(0);
		}
		else
		{//租用奴隶
			_hireSlave();
		}
	}
	else if(tag == udROMOVEBTN2)
	{
		if(cc->getIDX() == 1)
		{
			_removeMember(1);
		}
		else
		{
			_hireMercenary();
		}
	}
	else if(tag == udCHECKBTN2)
	{
		if(cc->getIDX() == 1)
		{
			_checkMemberInfo(1);
		}
		else
		{
			_hireSlave();
		}
	}
	else if(tag == udROMOVEBTN3)
	{
		if(cc->getIDX() == 1)
		{
			_removeMember(2);
		}
		else
		{
			_hireMercenary();
		}
	}
	else if(tag == udCHECKBTN3)
	{
		if(cc->getIDX() == 1)
		{
			_checkMemberInfo(2);
		}
		else
		{
			_hireSlave();
		}
	}
	else if(tag == ud1DOWNBTN || tag == ud2UPBTN)
	{//1和2交换位置
		//交换这两个队员,两次交换是为了不改变内存中的数据排列顺序
		TEAMBATTLEDATAHANDLER->ToServerSwitchMemberPlace(0, 1);
	}
	else if(tag == ud3UPBTN || tag == ud2DOWNBTN)
	{//2和3交换位置
		//交换这两个队员,两次交换是为了不改变内存中的数据排列顺序
		TEAMBATTLEDATAHANDLER->ToServerSwitchMemberPlace(1, 2);
	}

}

void TeamSelectWindow::On_JoinTeam_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;
	int idx = cc->getIDX();

	TTeamListItem *ti = TEAMBATTLEDATAHANDLER->m_pTeamListData->teamVector[idx];
	if(ti)
	{
		TEAMBATTLEDATAHANDLER->m_iMyTeamId = ti->teamId;
		TEAMBATTLEDATAHANDLER->ToServerJoinTeam();
	}
}

void TeamSelectWindow::On_View_Close_Click(cocos2d::CCObject* pSender)
{
	CCNode * node = m_pRoot->getChildByTag(udMaskNode);
	node->removeAllChildrenWithCleanup(true);
}

void TeamSelectWindow::On_Slave_Hire_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int index = item->getIDX();
	TSlaveItem * slave = TEAMBATTLEDATAHANDLER->m_pSlaveList->slaveVector[index];
	if(slave)
	{
		TEAMBATTLEDATAHANDLER->ToServerRendSlave(slave->playerId);
	}

	CCNode * node = m_pRoot->getChildByTag(udMaskNode);
	node->removeAllChildrenWithCleanup(true);
}

void TeamSelectWindow::On_Mercenary_Hire_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int index = item->getIDX();
	TMercenaryItem * mercenary = TEAMBATTLEDATAHANDLER->m_pMercenaryList->mercenaryVector[index];
	if(item)
	{
		TEAMBATTLEDATAHANDLER->ToServerRendMercenary(mercenary->playerId);
	}

	CCNode * node = m_pRoot->getChildByTag(udMaskNode);
	node->removeAllChildrenWithCleanup(true);
}

void TeamSelectWindow::_removeMember(int idx)
{
	if(idx >= (int)TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector.size())
	{
		return;
	}
	else
	{
		TMyTeamMember * ttm = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[idx];
		if(ttm)
		{//移除队员
			TEAMBATTLEDATAHANDLER->ToServerRemoveMember(ttm->index);
		}
	}
}

void TeamSelectWindow::_checkMemberInfo(int idx)
{
	if(idx >= (int)TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector.size())
	{
		return;
	}
	else
	{
		TMyTeamMember * ttm = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[idx];
		if(ttm)
		{
			//TEAMBATTLEDATAHANDLER->ToServerGetPlayerInfo(ttm->playerId);
			FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(ttm->playerId, _TYPED_WINDOW_TEAMSELECTWINDOW_);
		}
	}
}

void TeamSelectWindow::_hireSlave()
{
	//请求获得奴隶列表
	TEAMBATTLEDATAHANDLER->ToServerGetSlaveList();
}

void TeamSelectWindow::_hireMercenary()
{
	//请求获得佣兵列表
	TEAMBATTLEDATAHANDLER->ToServerGetMercenaryList();
}

void TeamSelectWindow::_refreshBtnFunc()
{
	//先判断有没有队伍
	if(TEAMBATTLEDATAHANDLER->m_pMyTeamData)
	{//有队伍
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->isIamLeader == 1)
		{//我是队长
			NFC_setNodeVisable(udBEGINBTN, m_pRoot, true);//可见开始
			NFC_setNodeVisable(udBEGINTTF, m_pRoot, true);//可见开始字
			if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector.size() ==3)
			{//队伍满员
				NFC_setEnabledForMenuItem(udBEGINBTN, udBEGINBTN, m_pRoot, true);//可按开始
			}
			else if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector.size() > 0)
			{//队伍未满员
				NFC_setEnabledForMenuItem(udBEGINBTN, udBEGINBTN, m_pRoot, false);//不可按开始
			}
			NFC_setNodeVisable(udDESTROYTEAMBTN, m_pRoot, true);//可见解散队伍
			NFC_setNodeVisable(udDESTROYTEAMTTF, m_pRoot, true);//可见解散队伍字
			NFC_setEnabledForMenuItem(udDESTROYTEAMBTN, udDESTROYTEAMBTN, m_pRoot, true);//可按解散队伍
			NFC_setNodeVisable(udBUILDTEAMBTN, m_pRoot, false);//不可见创建队伍
			NFC_setNodeVisable(udBUILDTEAMTTF, m_pRoot, false);//不可见创建队伍字
			NFC_setNodeVisable(udLEAVEBTN, m_pRoot, false);//不可见离开队伍
			NFC_setNodeVisable(udLEAVETTF, m_pRoot, false);//不可见离开队伍字
		}
		else
		{//我不是队长
			NFC_setNodeVisable(udBEGINBTN, m_pRoot, false);//不可见开始
			NFC_setNodeVisable(udBEGINTTF, m_pRoot, false);//不可见开始字
			NFC_setNodeVisable(udBUILDTEAMBTN, m_pRoot, false);//不可见创建队伍
			NFC_setNodeVisable(udBUILDTEAMTTF, m_pRoot, false);//不可见创建队伍字
			NFC_setNodeVisable(udDESTROYTEAMBTN, m_pRoot, false);//不可见解散队伍
			NFC_setNodeVisable(udDESTROYTEAMTTF, m_pRoot, false);//不可见解散队伍字
			NFC_setNodeVisable(udLEAVEBTN, m_pRoot, true);//可见离开队伍
			NFC_setNodeVisable(udLEAVETTF, m_pRoot, true);//可见离开队伍字
		}
	}
	else
	{//没有队伍
		//不显示雇佣召唤啥的
		for(int i = udROMOVEBTN1; i <= udCHECKTTF3; ++i)
		{
			NFC_setNodeVisable(i, m_pRoot, false);
		}		

		NFC_setNodeVisable(udBEGINBTN, m_pRoot, false);//不可见开始
		NFC_setNodeVisable(udBEGINTTF, m_pRoot, false);//不可见开始字
		NFC_setNodeVisable(udBUILDTEAMBTN, m_pRoot, true);//可见创建队伍
		NFC_setNodeVisable(udBUILDTEAMTTF, m_pRoot, true);//可见创建队伍字
		NFC_setNodeVisable(udDESTROYTEAMBTN, m_pRoot, false);//不可见解散队伍
		NFC_setNodeVisable(udDESTROYTEAMTTF, m_pRoot, false);//不可见解散队伍字
		NFC_setNodeVisable(udLEAVEBTN, m_pRoot, false);//可见离开队伍
		NFC_setNodeVisable(udLEAVETTF, m_pRoot, false);//可见离开队伍字
	}



}

void TeamSelectWindow::_refreshMyTeamShow()
{	//设置我所在的队伍的数据
	//设置时需要判断我是不是队长，队长的话拥有换队伍权利

	std::string file;
	std::string defaultfile = varConfig::getCardNormalBGFilePath();
	char temp[128] = {0};
	TMyTeamMember * member = NULL;
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	//队员资料
	int i = 0;
	int teamsize = 0;

	if(TEAMBATTLEDATAHANDLER->m_pMyTeamData)
	{
		teamsize = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector.size();
	}
	else
	{
		teamsize = 0;
	}
	CCSprite * hIcon_ = NULL;
	for(; i < teamsize; ++i)
	{
		member = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[i];
		////外套质量
		//file = varConfig::getCardBGFilePath(member->quality);
		//_set_texture(udQUALITY1 + i * _TAG_CHENG_, m_pRoot, file.c_str());
		////人物头像
		//file = RESOURCEDAIDMANAGER->getDataByID(member->iconId);
		//CDragSprite* drag=CDragSprite::create(file.c_str(), m_pRoot, this);
		//drag->setIDX(i);
		//drag->copyzOrder(10);
		//TEAMBATTLEDATAHANDLER->m_pMyTeamData->isIamLeader > 0 ? drag->isDragEabled(true) : drag->isDragEabled(false);
		//drag->setScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
		//CCNode * node = m_pRoot->getChildByTag(udICON1 + i * _TAG_CHENG_);
		//drag->setAnchorPoint(node->getAnchorPoint());
		//node->setVisible(true);
		//node->removeAllChildrenWithCleanup(true);
		//node->addChild(drag);
		NFC_setDTHeroIcon(udQUALITY1 + i * _TAG_CHENG_,m_pRoot,member->iconId,true);
		NFC_setDTHeroQualiy(udQUALITY1 + i * _TAG_CHENG_,m_pRoot,member->quality);


		//外套名、强化等级值
		sprintf(temp, "%s", member->skinName.c_str());
		NFC_setLabelString(udSKINNAME1 + i * _TAG_CHENG_, m_pRoot, temp,true);
		//战力值
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(41).c_str(), member->btlCapacity);
		NFC_setLabelString(udZHANLIVALUE1 + i * _TAG_CHENG_, m_pRoot, temp, true);
		//人物名称
		NFC_setLabelString(udPLAYERNAME1 + i * _TAG_CHENG_, m_pRoot, member->playerName.c_str(),true);
		//社会关系
		NFC_setLabelString(udSOCIAL1 + i * _TAG_CHENG_, m_pRoot, member->markName.c_str(),true);

		//按钮
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->isIamLeader > 0)
		{
			if(member->gameUnitType == UNIT_PLAYER)
			{//是人
				if(member->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
				{//这个成员是自身，则自身不需要显示操作
					NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, false);
				}
				else
				{
					menu = (CCMenu *)m_pRoot->getChildByTag(udROMOVEBTN1 + i * 4);
					item = (CMenuItemSprite *)menu->getChildByTag(udROMOVEBTN1 + i * 4);
					NFC_setLabelString(udROMOVETTF1 + i * 4, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(32), true);//移除字
					item->setIDX(1);
					NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, true);
					NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, true);

					menu = (CCMenu *)m_pRoot->getChildByTag(udCHECKBTN1 + i * 4);
					item = (CMenuItemSprite *)menu->getChildByTag(udCHECKBTN1 + i * 4);
					NFC_setLabelString(udCHECKTTF1 + i * 4, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(33), true);//查看字
					NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, true);
					item->setIDX(1);
					NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, true);
					NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, true);
				}

			}
			else
			{//不是人
				menu = (CCMenu *)m_pRoot->getChildByTag(udROMOVEBTN1 + i * 4);
				item = (CMenuItemSprite *)menu->getChildByTag(udROMOVEBTN1 + i * 4);
				NFC_setLabelString(udROMOVETTF1 + i * 4, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(32), true);//移除字
				item->setIDX(1);
				NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, true);
				NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, true);

				NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, false);
				NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, false);
			}
		}
		else
		{//是队员
			if(member->gameUnitType == UNIT_PLAYER)
			{//是人
				if(member->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
				{//这个成员是自身，则自身不需要显示操作
					NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, false);
				}
				else
				{
					NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, false);
					NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, false);

					menu = (CCMenu *)m_pRoot->getChildByTag(udCHECKBTN1 + i * 4);
					item = (CMenuItemSprite *)menu->getChildByTag(udCHECKBTN1 + i * 4);
					NFC_setLabelString(udCHECKTTF1 + i * 4, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(33), true);//查看字
					NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, true);
					item->setIDX(1);
					NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, true);
					NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, true);
				}

			}
			else
			{//不是人
				NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, false);
				NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, false);

				NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, false);
				NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, false);
			}
		}
	}
	for(; i < 3; ++i)
	{
		//CCNode * node = m_pRoot->getChildByTag(udICON1 + i * _TAG_CHENG_);
		//node->removeAllChildrenWithCleanup(true);

		NFC_setNodeVisable(udQUALITY1 + i * _TAG_CHENG_, m_pRoot, false);
		//NFC_setNodeVisable(udICON1 + i * _TAG_CHENG_, m_pRoot, false);
		NFC_setNodeVisable(udSKINNAME1 + i * _TAG_CHENG_, m_pRoot, false);
		NFC_setNodeVisable(udZHANLIVALUE1 + i * _TAG_CHENG_, m_pRoot, false);
		NFC_setNodeVisable(udPLAYERNAME1 + i * _TAG_CHENG_, m_pRoot, false);
		NFC_setNodeVisable(udSOCIAL1 + i * _TAG_CHENG_, m_pRoot, false);

		//按钮
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData)
		{
			if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->isIamLeader > 0)
			{
				menu = (CCMenu *)m_pRoot->getChildByTag(udROMOVEBTN1 + i * 4);
				item = (CMenuItemSprite *)menu->getChildByTag(udROMOVEBTN1 + i * 4);
				NFC_setLabelString(udROMOVETTF1 + i * 4, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(34), true);//雇佣佣兵
				item->setIDX(2);
				NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, true);
				NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, true);

				menu = (CCMenu *)m_pRoot->getChildByTag(udCHECKBTN1 + i * 4);
				item = (CMenuItemSprite *)menu->getChildByTag(udCHECKBTN1 + i * 4);
				NFC_setLabelString(udCHECKTTF1 + i * 4, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(35), true);//雇佣奴隶
				item->setIDX(2);
				NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, true);
				NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, true);
			}
			else
			{
				NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, false);
				NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, false);
				NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, false);
				NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, false);
			}
		}
		else
		{
			NFC_setNodeVisable(udROMOVEBTN1 + i * 4, m_pRoot, false);
			NFC_setNodeVisable(udROMOVETTF1 + i * 4, m_pRoot, false);
			NFC_setNodeVisable(udCHECKBTN1 + i * 4, m_pRoot, false);
			NFC_setNodeVisable(udCHECKTTF1 + i * 4, m_pRoot, false);
		}


	}
	
	char onoff = 0;
	//向下按钮
	if(teamsize == 0)
	{
		onoff = 0;
	}
	else if(teamsize == 1)
	{
		onoff = 0;
	}
	else if(teamsize == 2)
	{
		onoff = 0 | (1) | (1 << 1);
	}
	else if(teamsize == 3)
	{
		onoff = 0 | (1) | (1 << 1) | (1 << 2) | (1 << 3);
	}

	NFC_showNode(ud1DOWNBTN, m_pRoot, (onoff & (1)) > 0 ? true : false);
	NFC_showNode(ud2UPBTN, m_pRoot, (onoff & (1 << 1)) > 0 ? true : false);
	NFC_showNode(ud2DOWNBTN, m_pRoot, (onoff & (1 << 2)) > 0 ? true : false);
	NFC_showNode(ud3UPBTN, m_pRoot, (onoff & (1 << 3)) > 0 ? true : false);

	if(TEAMBATTLEDATAHANDLER->m_pMyTeamData != NULL)
	{
		if(TEAMBATTLEDATAHANDLER->m_pMyTeamData->isIamLeader <= 0)
		{
			NFC_showNode(ud1DOWNBTN, m_pRoot, false);
			NFC_showNode(ud2UPBTN, m_pRoot, false);
			NFC_showNode(ud2DOWNBTN, m_pRoot, false);
			NFC_showNode(ud3UPBTN, m_pRoot, false);
		}
	}


	//设置按钮
	_refreshBtnFunc();
}

//交换两个队员
void TeamSelectWindow::_switchTwoMember(int firstIdx, int secondIdx)
{
	TMyTeamMember * temp = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[firstIdx];
	
	TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[firstIdx] = TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[secondIdx];
	TEAMBATTLEDATAHANDLER->m_pMyTeamData->memberVector[secondIdx] = temp;

}

void TeamSelectWindow::Function_GetNowStageData()
{
	//设置关卡信息
	NFC_setLabelString(udFUBENNAMETTF, m_pRoot, TEAMBATTLEDATAHANDLER->m_pTeamStageData->stageName.c_str(),true);
}

/*
获得队伍列表数据，刷新队伍列表
*/
void TeamSelectWindow::Function_GetTeamListData()
{
	_refreshTableView(m_pTeamTable);
}

/*
获得自己所在队伍数据, 刷新所在队伍数据
*/
void TeamSelectWindow::Function_GetMyTeamData()
{
	_refreshMyTeamShow();

	onekey0->setVisible(true);
	onekey1->setVisible(true);
	onekey2->setVisible(true);
}
	
/*
服务器通知我被踢了！！
*/
void TeamSelectWindow::Function_BeRemovedFromTeam(int removedType, int isLeader)
{
	//0队伍解散, 1被踢出, 2主动离开
	if(removedType == 0 && isLeader == 0)
	{
		NFC_showMessageBox(kDEFAULT, SysLangDataManager::get_instance2()->GetSysLangById(676));
	}
	else if(removedType == 1)
	{
		NFC_showMessageBox(kDEFAULT, SysLangDataManager::get_instance2()->GetSysLangById(633));
	}

	_refreshMyTeamShow();

	onekey0->setVisible(false);
	onekey1->setVisible(false);
	onekey2->setVisible(false);
}

/*
	获得奴隶列表
*/
void TeamSelectWindow::Function_GetSlaveList()
{
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(udMaskNode);
	if(node)
		node->removeAllChildrenWithCleanup(true);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMSELECTVIEWLIST, node);

	m_pMercenaryTable = NULL;

	//显示奴隶列表
	NFC_setLabelString(vTitle, node, SysLangDataManager::get_instance2()->GetSysLangById(2041), true);

	CCMenu * menu = (CCMenu *)node->getChildByTag(vCloseBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_View_Close_Click));

	CCNode * cell = node->getChildByTag(vCell);
	m_szSlaveCell = cell->getContentSize();
	m_pSlaveTable =(CCTableView*)node->getChildByTag(vTabelview);
	m_pSlaveTable->setDataSource(this);
	m_pSlaveTable->setDelegate(this);
	m_pSlaveTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pSlaveTable->setTouchEnabled(true);
	m_pSlaveTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);

	_refreshTableView(m_pSlaveTable);

}

/*
	获得佣兵列表
*/
void TeamSelectWindow::Function_GetMercenaryList()
{
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(udMaskNode);
	if(node)
		node->removeAllChildrenWithCleanup(true);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMSELECTVIEWLIST, node);

	m_pSlaveTable = NULL;

	//显示雇佣列表
	NFC_setLabelString(vTitle, node, SysLangDataManager::get_instance2()->GetSysLangById(2039), true);

	CCMenu * menu = (CCMenu *)node->getChildByTag(vCloseBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(TeamSelectWindow::On_View_Close_Click));

	CCNode * cell = node->getChildByTag(vCell);
	m_szMercenaryCell = cell->getContentSize();

	m_pMercenaryTable =(CCTableView*)node->getChildByTag(vTabelview);
	m_pMercenaryTable->setDataSource(this);
	m_pMercenaryTable->setDelegate(this);
	m_pMercenaryTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pMercenaryTable->setTouchEnabled(true);
	m_pMercenaryTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	_refreshTableView(m_pMercenaryTable);

}