//Name:ClimbTowerWindow.cpp
//Function:爬塔界面
//Author:方骏
//Date:20130830

#include "../include/ClimbTowerWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include <string>
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/ClimbTowerDataHandler.h"
#include "../include/CSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MaskNode.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/IProcedure.h"
#include "../include/MessageBoxWindow.h"
#include "../include/CProgressInnerBar.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/EngineSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/ClientConstDataManager.h"
#include "../include/config_SoundSystem.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/GuideSystem.h"
#include "../include/config_HomeWindow.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/DTAwardBoard.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

ClimbTowerWindow::ClimbTowerWindow()
:m_pRoot(NULL)
,m_pRNode(NULL)
,m_pMap1(NULL)
,m_pMap2(NULL)
,m_pHero(NULL)
,m_iRunTickTime(DOTATribeApp::get_instance2()->GetFPS() * 2)
,m_iRunTickCount(0)
,m_fHLength(200.0f)
,m_fVLength(190.0f)
,m_bStartRun(false)
,m_iRightShowNode(-1)
,m_pSkeletonNode(NULL)
,m_pAnimationGrayLayer(NULL)
,m_pAnimationPlayNode(NULL)
,m_pAnimationFileData(NULL)
,m_pAnimation(NULL)
,pAnimationAction(NULL)
,m_iJumpTickCount(0)
,m_bStartJump(false)			//冲刺标志
,m_iJumpTickTime(DOTATribeApp::get_instance2()->GetFPS() * 2)		//冲刺时间，默认2秒
,m_fJumpMapSpeed(60.0f)
,_jumptickfloor(-1)
,m_pTableFightResult(NULL)
,m_pTableReward(NULL)
,m_iFastFightRound(0)
,m_bInFashFightMode(false)
{
	m_WindowType = _TYPED_WINDOW_CLIMBWINDOW_;
	m_bModelWindow = false;

}

ClimbTowerWindow::~ClimbTowerWindow()
{
	m_pRoot = NULL;
	m_pRNode = NULL;
	m_pMap1 = NULL;
	m_pMap2 = NULL;
	m_pHero = NULL;
	m_pSkeletonNode = NULL;
	_jumptickfloor = -1;
}

bool    ClimbTowerWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
	RegisterEvent(_TYPED_EVENT_UPDATE_CLIMBTOWERWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_, true);

	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);

	RegisterEvent(_TYPED_EVENT_ENTERTOWER_RESULT_, true);//进入塔
	RegisterEvent(_TYPED_EVENT_CHALLENGETOWER_RESULT, true);//挑战塔
	RegisterEvent(_TYPED_EVENT_CHALLENGETOWER_RUNHERO_, true);//人物可以开始跑了
	RegisterEvent(_TYPED_EVENT_RESETTOWER_RESULT_, true);//重置塔
// 	RegisterEvent(_TYPED_EVENT_TOWER_COMFIRM_PAYTIME_, true);//确认使用道具
// 	RegisterEvent(_TYPED_EVENT_TOWER_ENTER_SHOP_, true);//确认进入商城
	RegisterEvent(_TYPED_EVENT_START_TOWER_TIMES_, true);
	RegisterEvent(_TYPED_EVENT_TOWER_COMFIRM_RESET_, true);//确认重置

	RegisterEvent(_TYPED_EVENT_TOWER_FASTFIGHT_GETDATA_, true);//快速战斗
	RegisterEvent(_TYPED_EVENT_TOWER_JEWELRESET_GETDATA_, true);//钻石重置
	RegisterEvent(_TYPED_EVENT_TOWER_REWARD_GETDATA_, true);//获得奖励列表
	RegisterEvent(_TYPED_EVENT_TOWER_GETREWARD_GETDATA_, true);//领取某个奖励

	RegisterEvent(_TYPED_EVENT_BUYCLIMBTOWERTIMES_GETDATA_, true);//购买次数返回


	RegisterEvent(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY,true);    //网络重连通知
	return IWindow::Init();
}

bool    ClimbTowerWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();//绘制界面

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_, _to_event_param_(_TYPED_WINDOW_CLIMBWINDOW_));

		LevelUpDataHandler::get_instance2()->m_showFlag = false;//禁止自动弹出升级界面
		LevelUpDataHandler::get_instance2()->m_showIsNeed = false;//禁止自动恢复自动弹出功能

		//背景音乐 关主场景，开爬塔
		//char _typeID[64]="";
		//sprintf(_typeID,"%d",kSOUND_STOP_TYPE_EFFECT_AND_BACKGROUND);
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_,_typeID);

		LoadingAnimationData* pData= LoadingAnimationManager::get_instance2()->GeLoadingAnimationDataByID(IProcedure::_TYPED_CLIMB_TOWER_);
		if (pData->mBackgroundSuondID != -1)
		{
			char _soundID[64]="";
			sprintf(_soundID,"%d",pData->mBackgroundSuondID);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
		}

		return true;
	} 
	while (false);

	return false;
}

	/*
		检查新功能开启
	*/
void ClimbTowerWindow::_checkNewFunc(){
	if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_5_TOWER)){
		LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_checkNewFunc");
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,_to_event_param_(UIViewDataManager::kCLIMBTOWERVIEW));
		if (m_pRNode)
		{
			NFC_setNodeVisable(bStartArrow, m_pRNode,true);
		}	
		//======结束新功能开启=======
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_5_TOWER);
	}
}

void ClimbTowerWindow::Tick()
{
	IWindow::Tick();

	//地图和英雄的移动
	_tickRun();

	//冲刺Tick
	_tickJump();
}

void ClimbTowerWindow::Destroy()
{
	PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
	NFC_showCommunicationWating(false);
	_removeGrayLayer();
	m_iRunTickCount = 0;
	m_bStartRun = false;
	m_pSkeletonNode = 0;

	//关闭飘字
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);

	LevelUpDataHandler::get_instance2()->m_showFlag = true;
	LevelUpDataHandler::get_instance2()->m_showIsNeed = true;

	_jumptickfloor = 0;

	m_iFastFightRound = 0;
	m_bInFashFightMode = false;


	IWindow::Destroy();
}

void    ClimbTowerWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::OnEventHandler---event: %d---begin\n", iEventType);
	if (iEventType == _TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_)
	{
		PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_ENTERTOWER_RESULT_)
	{//进入塔结果
		Function_EnterTower();
	}
	else if(iEventType == _TYPED_EVENT_CHALLENGETOWER_RESULT)
	{//挑战他结果
		Function_ChallengeTowerEnd();
	}
	else if(iEventType == _TYPED_EVENT_CHALLENGETOWER_RUNHERO_)
	{
		Function_NotifyHeroRun();
	}
	else if(iEventType == _TYPED_EVENT_RESETTOWER_RESULT_)
	{//重置塔结果
		Function_ResetTower();
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		OnRefreshWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_START_TOWER_TIMES_)
	{
		Function_StartTower();
	}
	else if(iEventType == _TYPED_EVENT_TOWER_COMFIRM_RESET_)
	{
		Function_ComfirmReset();
	}
	/*else if(iEventType == _TYPED_EVENT_TOWER_COMFIRM_PAYTIME_)
	{//提示是否使用道具增加次数，确认功能
		Function_ComfirmPaytime();
	}
	else if(iEventType == _TYPED_EVENT_TOWER_ENTER_SHOP_)
	{
		Function_ComfirmEnterShop();
	}*/
	else if(iEventType == _TYPED_EVENT_TOWER_FASTFIGHT_GETDATA_)
	{//快速战斗结果
		Function_GetFastFightResult();
	}
	else if(iEventType == _TYPED_EVENT_TOWER_JEWELRESET_GETDATA_)
	{//钻石重置结果
		Function_JewelResetResult();
	}
	else if(iEventType == _TYPED_EVENT_TOWER_REWARD_GETDATA_)
	{//奖励面板数据
		Function_EnterRewardData();
	}
	else if(iEventType == _TYPED_EVENT_TOWER_GETREWARD_GETDATA_)
	{//领取奖励成功
		std::string typestr = *(paramList.begin());
		int type = atoi(typestr.c_str());
		std::string idxstr = *(++paramList.begin());
		int idx = atoi(idxstr.c_str());
		Function_GetRewardResult((char)type, idx);
	}
	else if(iEventType == _TYPED_EVENT_BUYCLIMBTOWERTIMES_GETDATA_)
	{//重新请求页面信息，刷新
		CLIMBTOWERDATAHANDLER->ToServerEnterTower();
	}
	else if(iEventType==_TYPED_EVENT_RECONNECT_INGAME_NOTIFY){
		//网络重连处理事件
		Function_LostRetryFastFight();
	}

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::OnEventHandler---event: %d---end\n", iEventType);
}

void   ClimbTowerWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	CheckIfNeedLvUp();
	PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
}

void ClimbTowerWindow::OnRefreshWindowEventHandler(std::list<std::string>& paramList)
{
	
}

void ClimbTowerWindow::_initLayout()
{
	m_pRoot= m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERVIEW, m_pRoot);

	_initAnimationEffect();//初始化动画效果

	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(ctHero);
	m_fHLength = node->GetViewData().width_;
	m_fVLength = node->GetViewData().height_;
	m_iRunTickTime = node->GetViewData().alpha_ * DOTATribeApp::get_instance2()->GetFPS() / 100;
	if(m_iRunTickTime == 0)
	{
		LOGGERSYSTEM->LogError("ClimbTowerWindow::_initLayout -- m_iRunTickTime = 0");
		m_iRunTickTime = 2 * 30;
	}

	node = (MaskNode *)m_pRoot->getChildByTag(ctAnimationNode);
	m_iJumpTickTime = node->GetViewData().alpha_ * DOTATribeApp::get_instance2()->GetFPS() / 100;
	if(m_iJumpTickTime == 0)
	{
		LOGGERSYSTEM->LogError("ClimbTowerWindow::_initLayout -- m_iJumpTickTime = 0");
		m_iJumpTickTime = 2 * 30;
	}


	m_pRNode = m_pRoot->getChildByTag(ctRightPanel);//右侧展板节点
	m_pRewardNode = m_pRoot->getChildByTag(ctRewardPanel);//奖励挂载点

	m_pMap1 = m_pRoot->getChildByTag(ctTowerBg1);//地图1
	m_pMap2 = m_pRoot->getChildByTag(ctTowerBg2);//地图2

	m_pHero = m_pRoot->getChildByTag(ctHero);
	m_fHeroDefaultPosx = m_pHero->getPositionX();
	m_fHeroDefaultPosy = m_pHero->getPositionY();

	_mapMainPageBtn();

	_initMapHero();

	//显示右侧界面
	EnterTower();

}

void ClimbTowerWindow::_mapMainPageBtn()
{
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(ctCloseBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);//关闭
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_MainPage_Btn_Click));
	item->setTag(ctCloseBtn);
	
}

void ClimbTowerWindow::_setHeroPosition(float posx)
{
	if(m_pHero != NULL)
		m_pHero->setPositionX(posx);
}

void ClimbTowerWindow::_tickRun()
{
	if(m_bStartRun)
	{
		//设置移动英雄
		float s = m_fHLength / m_iRunTickTime;
		float posx = 0;
		float posy = 0;
		int herocurfloor = CLIMBTOWERDATAHANDLER->iPreFloor;//英雄站立的层数(跑向战斗的层)，此时层数是上次的层
		if(herocurfloor == -1)
			herocurfloor = 0;

		if(herocurfloor % 2 == 0)
		{
			posx = m_pHero->getPositionX() + s;//向右走
			if(m_pSkeletonNode != NULL)
				if(m_pSkeletonNode->getRotationY() > 0 || m_pSkeletonNode->getRotationY() < 0)
					m_pSkeletonNode->setRotationY(0.0f);
		}
		else
		{
			posx = m_pHero->getPositionX() - s;//向左走
			if(m_pSkeletonNode) 
				if(m_pSkeletonNode->getRotationY() > 180.0f || m_pSkeletonNode->getRotationY() < 180.0f)
					m_pSkeletonNode->setRotationY(180.0f);
		}
		_setHeroPosition(posx);

		//设置flot移动地图
		s = m_fVLength / m_iRunTickTime;
		
		posy = m_pMap1->getPositionY() - s;
		_setMapPosition(m_pMap1, posy, m_pMap2);//图1
		posy = m_pMap2->getPositionY() - s;
		_setMapPosition(m_pMap2, posy, m_pMap1);//图2


		++m_iRunTickCount;
		
		if(m_iRunTickCount >= m_iRunTickTime)
		{//到达目的地
			if(m_bInFashFightMode == false)
			{
				LOGGERSYSTEM->LogInfo("HeroRun -- finish -- begin\n");
				m_bStartRun = false;
				_removeGrayLayer();//移除防触控遮罩层
				if(m_pSkeletonNode) 
					m_pSkeletonNode->setAnimation("DaiJi", true); 
				m_iRunTickCount = 0;

				//Post进入战斗流程通知
				char athleticsProcedure[8]={0};
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_);
				sprintf(athleticsProcedure,"%d",IProcedure::_TYPED_ATHLETICS_PROCEDURE_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,athleticsProcedure);

				//CLIMBTOWERDATAHANDLER->ToClientChallengeTowerResult();//测试直接转向爬塔结果

				LOGGERSYSTEM->LogInfo("HeroRun -- finish -- end\n");
			}
			else
			{//快速战斗模式
				NFC_refreshTableView(m_pTableFightResult);//刷新快速战斗界面面板
				int rsz = CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData.size();
				TowerFastFightResultItem * fresult = CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData[rsz - 1];
				if(fresult->result > 0 && fresult->fightFloor < TOWER_FLOOR_TOTAL)
				{//继续爬
					CLIMBTOWERDATAHANDLER->ToServerFastFight();
				}
				else
				{
					CCMenu * menu = (CCMenu *)m_pRNode->getChildByTag(fConfirmBtn);
					CCMenuItem * item = (CCMenuItem *)menu->getChildByTag(fConfirmBtn + 100);
					item->setEnabled(true);

					CheckIfNeedLvUp();
				}
				m_bStartRun = false;
				m_iRunTickCount = 0;
				if(m_pSkeletonNode) 
					m_pSkeletonNode->setAnimation("DaiJi", true); 
			}
			
		}
	}
}

void ClimbTowerWindow::_tickJump()
{
	if(m_bStartJump)
	{
		//设置flot移动地图
		float posy = m_pMap1->getPositionY() - m_fJumpMapSpeed;
		_setJumpMapPosition(m_pMap1, posy, _jumptickfloor);//图1
		posy = m_pMap2->getPositionY() - m_fJumpMapSpeed;
		_setJumpMapPosition(m_pMap2, posy, _jumptickfloor);//图2

		++m_iJumpTickCount;

		if(m_iJumpTickCount >= m_iJumpTickTime)
		{//冲刺结束
			m_bStartJump = false;
			m_iJumpTickCount = 0;

			m_pAnimationPlayNode->stopAction(pAnimationAction);
			m_pAnimationPlayNode->setVisible(false);
			_removeGrayLayer();
			//显示右侧界面,刷新地图以及更新右侧界面
			CLIMBTOWERDATAHANDLER->enterData.entertype = 1;
			EnterTower();
			//更新为待机状态
			if(m_pSkeletonNode) 
				m_pSkeletonNode->setAnimation("DaiJi", true);

			//显示右侧界面
			m_pRNode->setVisible(true);

			CheckIfNeedLvUp();

			_jumptickfloor = -1;
		}
	}
}


void ClimbTowerWindow::_initMapHero()
{
	//创建骨骼动画
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(ctHero);
	const UIViewData &dd = node->GetViewData();
	if(m_pSkeletonNode) 
		m_pSkeletonNode->removeFromParentAndCleanup(true);
	unsigned short shapeID=NFC_GetTeamHero()->getHeroShapeID();
	assert(shapeID>=0);
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	m_pSkeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage); 
	m_pSkeletonNode->setScale(dd.scale_);
	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("DaiJi", true); 
	m_pSkeletonNode->setAnchorPoint(ccp(dd.anchorx_, dd.anchory_));
	m_pSkeletonNode->setPosition(CCPointZero);
	node->addChild(m_pSkeletonNode, 0, 0);

	//创建层数数字
	//数字1
	_createMapFloorNum(m_pMap1, ctFloorNum1, m_pRoot);
	//数字2
	_createMapFloorNum(m_pMap1, ctFloorNum2, m_pRoot);
	//数字3
	_createMapFloorNum(m_pMap1, ctFloorNum3, m_pRoot);
	//数字4
	_createMapFloorNum(m_pMap1, ctFloorNum4, m_pRoot);
	//数字5
	_createMapFloorNum(m_pMap2, ctFloorNum1, m_pRoot);
	//数字6
	_createMapFloorNum(m_pMap2, ctFloorNum2, m_pRoot);
	//数字7
	_createMapFloorNum(m_pMap2, ctFloorNum3, m_pRoot);
	//数字8
	_createMapFloorNum(m_pMap2, ctFloorNum4, m_pRoot);

/*	int curfloor = CLIMBTOWERDATAHANDLER->iPreFloor;
	_setMapNum(m_pMap1, curfloor, curfloor + 1, curfloor + 2, curfloor + 3);
	_setMapNum(m_pMap2, curfloor + 4, curfloor + 5, curfloor + 6, curfloor + 7);
	//这是20130923号由fangjun注释，原因是不管何时进入都会走EnterTower函数，这个函数负责设置当前页面的层数显示
	*/

}

void ClimbTowerWindow::_refreshMapHero()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_refreshMapHero -- begin\n");

	int curfloor = 0;
	if(CLIMBTOWERDATAHANDLER->enterData.entertype == 0)
	{
		curfloor = 0;
	}
	else
	{
		curfloor = CLIMBTOWERDATAHANDLER->enterData.nowfloor;
	}
	int rest = curfloor % 2;
	//英雄和地图位置
	if(rest == 0)//左侧
	{
		m_pHero->setPositionX(m_fHeroDefaultPosx);
		if(m_pSkeletonNode)
			m_pSkeletonNode->setRotationY(0);
	}
	else
	{
		m_pHero->setPositionX(m_fHeroDefaultPosx + m_fHLength);
		if(m_pSkeletonNode)
			m_pSkeletonNode->setRotationY(180.0f);
	}
	m_pMap1->setPositionY(0 - m_fVLength * rest);
	m_pMap2->setPositionY(768.0f - m_fVLength * rest);

	//刷新地图层数
	if(rest == 0)
	{
		_setMapNum(m_pMap1, curfloor, curfloor + 1, curfloor + 2, curfloor + 3);
		_setMapNum(m_pMap2, curfloor + 4, curfloor + 5, curfloor + 6, curfloor + 7);
	}
	else
	{
		_setMapNum(m_pMap1, curfloor - 1, curfloor, curfloor + 1, curfloor + 2);
		_setMapNum(m_pMap2, curfloor + 3, curfloor + 4, curfloor + 5, curfloor + 6);
	}

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_refreshMapHero -- end\n");
}

void ClimbTowerWindow::_createMapFloorNum(cocos2d::CCNode * hangParent, int maskNodeTag, cocos2d::CCNode * maskParent)
{
	MaskNode *mask = (MaskNode *)maskParent->getChildByTag(maskNodeTag);
	CCLabelTTF * ttf = CCLabelTTF::create();

	ttf->setFontSize(mask->GetViewData().fontsize_);
	ttf->setTag(maskNodeTag);
	ttf->setAnchorPoint(ccp(mask->GetViewData().anchorx_, mask->GetViewData().anchory_));
	ttf->setPosition(ccp(mask->GetViewData().posx_, mask->GetViewData().posy_));

	hangParent->addChild(ttf, mask->GetViewData().zorder_);
}

void ClimbTowerWindow::_setMapPosition(cocos2d::CCNode * map, float posy, cocos2d::CCNode * anotherMap)
{
	int herocurfloor = CLIMBTOWERDATAHANDLER->iPreFloor;//英雄之前站立的层数，这是因为英雄在跑动过程中层数才会动，地图下降时任务其实任务所在层数据已经是当前的层了，而图应该是上次的层加4开始。

	if(posy <= - 768)
	{//向下移出屏幕,需要将图从屏幕移到屏幕顶端
		map->setPositionY(768 * 2 + posy);
		_setMapNum(map, herocurfloor + 4, herocurfloor + 5, herocurfloor + 6, herocurfloor + 7);
	}
	else
	{
		map->setPositionY(posy);
	}

}

void ClimbTowerWindow::_setJumpMapPosition(cocos2d::CCNode * map, float posy, int floor)
{
	if(posy <= - 768)
	{//向下移出屏幕,需要将图从屏幕移到屏幕顶端
		map->setPositionY(768);
		_setMapNum(map, floor, floor + 1, floor + 2, floor + 3);
		_jumptickfloor += 4;
	}
	else
	{
		map->setPositionY(posy);
	}


}

void ClimbTowerWindow::_setMapNum(cocos2d::CCNode * map, int floor1, int floor2, int floor3, int floor4)
{
	if(floor1 > TOWER_FLOOR_TOTAL)
		NFC_showNode(ctFloorNum1, map, false);
	else
		NFC_setLabelStringInt(ctFloorNum1, map, floor1, true);
	if(floor2 > TOWER_FLOOR_TOTAL)
		NFC_showNode(ctFloorNum2, map, false);
	else
		NFC_setLabelStringInt(ctFloorNum2, map, floor2, true);
	if(floor3 > TOWER_FLOOR_TOTAL)
		NFC_showNode(ctFloorNum3, map, false);
	else
		NFC_setLabelStringInt(ctFloorNum3, map, floor3, true);
	if(floor4 > TOWER_FLOOR_TOTAL)
		NFC_showNode(ctFloorNum4, map, false);
	else
		NFC_setLabelStringInt(ctFloorNum4, map, floor4, true);
}

void ClimbTowerWindow::_setText(int tag, cocos2d::CCNode * parent, const char * text)
{
	CCLabelTTF * ttf = (CCLabelTTF *)parent->getChildByTag(tag);
	ttf->setString(text);
	
}

void ClimbTowerWindow::_setText(int tag, cocos2d::CCNode * parent, int num)
{
	char temp[128] = {0};
	sprintf(temp, "%d", num);
	_setText(tag, parent, temp);
}

void ClimbTowerWindow::_setTexture(int tag,  cocos2d::CCNode * parent, const char * picpath)
{
	CCSprite * sp = (CCSprite *)parent->getChildByTag(tag);
	sp->setProperty("File",picpath);
	sp->setVisible(true);
}

void ClimbTowerWindow::_enableBtn(int tag, cocos2d::CCNode * parent, bool enable)
{
	CCMenu * menu = (CCMenu *)parent->getChildByTag(tag);
	CCMenuItem * item = (CCMenuItem *)menu->getChildByTag(tag);
	item->setEnabled(enable);
}


void ClimbTowerWindow::_setVisible(int tag, cocos2d::CCNode * parent, bool visible)
{
	CCNode * node = parent->getChildByTag(tag);
	node->setVisible(visible);
}


void ClimbTowerWindow::_setBeginPageInfo()
{
	char temp[128] = {0};
	//设置开始页
	//排名
	if(CLIMBTOWERDATAHANDLER->enterData.rankNum < 0)
	{
		std::string rank = SysLangDataManager::get_instance2()->GetSysLangById(614);
		NFC_setLabelString(bRankListNumValue, m_pRNode, rank.c_str(), true);
	}
	else
	{
		NFC_setLabelStringInt(bRankListNumValue, m_pRNode, CLIMBTOWERDATAHANDLER->enterData.rankNum, true);
	}

	//今天剩余挑战次数
	int time = CLIMBTOWERDATAHANDLER->enterData.maxTimes - CLIMBTOWERDATAHANDLER->enterData.usedTimes;
	NFC_setLabelStringInt(bTimesValue, m_pRNode, time, true);

	//荣誉奖励
	//NFC_setLabelStringInt(bHonorNum, m_pRNode, CLIMBTOWERDATAHANDLER->enterData.honor, true);

}

void ClimbTowerWindow::_mapBeginPageBtn()
{
	CCMenu * menu = (CCMenu *)m_pRNode->getChildByTag(bListBtn);//排行榜按钮
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bListBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_BeginPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(bStartBtn);//开始按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bStartBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_BeginPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(bBaoXiangBtn);//宝箱按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bBaoXiangBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_BeginPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(bBuyBtn);//宝箱按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(bBuyBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_BeginPage_Btn_Click));

}

void ClimbTowerWindow::_setEndPageInfo()
{
	char temp[128] = {0};
	//设置结束页
	//排名
	if(CLIMBTOWERDATAHANDLER->enterData.rankNum < 0)
	{
		std::string rank = SysLangDataManager::get_instance2()->GetSysLangById(614);
		NFC_setLabelString(eRankListNumValue, m_pRNode, rank.c_str(), true);
	}
	else
	{
		NFC_setLabelStringInt(eRankListNumValue, m_pRNode, CLIMBTOWERDATAHANDLER->enterData.rankNum, true);
	}

	//下一层获得经验
	NFC_setLabelStringInt(eNextExpValue, m_pRNode, CLIMBTOWERDATAHANDLER->enterData.nextexp);

	//累计获得经验
	_setText(eGotExpValue, m_pRNode, CLIMBTOWERDATAHANDLER->enterData.gotexp);

	//设置推荐技能
	_setBox();

	//荣誉奖励
	//NFC_setLabelStringInt(bHonorNum, m_pRNode, CLIMBTOWERDATAHANDLER->enterData.honor, true);

	//设置剩余挑战次数
	int times = CLIMBTOWERDATAHANDLER->enterData.leftChallengeTime;
	if(times > 0)
	{
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2044).c_str(), times);
	}
	else
	{
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2045).c_str(), times);
	}
	NFC_setLabelString(eLeftTimesValue, m_pRNode, temp, true);
}

void ClimbTowerWindow::_mapEndPageBtn()
{
	CCMenu * menu = (CCMenu *)m_pRNode->getChildByTag(eListBtn);//排行榜按钮
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(eListBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_EndPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(eBaoXiangBtn);//宝箱按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(eBaoXiangBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_EndPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(eResetBtn);//重置按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(eResetBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_EndPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(eJewelResetBtn);//钻石重置按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(eJewelResetBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_EndPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(eFastFightBtn);//快速战斗按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(eFastFightBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_EndPage_Btn_Click));

	menu = (CCMenu *)m_pRNode->getChildByTag(eContinueBtn);//继续按钮
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(eContinueBtn);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_EndPage_Btn_Click));

}


void ClimbTowerWindow::_setBox()
{
	TowerSkillItem * item = NULL;
	int size = CLIMBTOWERDATAHANDLER->enterData.skillData.size();
	int j = 0;

	CCMenu * menu = NULL;
	CCSprite * sp = NULL;
	CMenuItemSprite * menuitem = NULL;
	std::string empty_file = varConfig::getCardNormalBGFilePath();
	std::string quality_file;

	//清空展示
	for(j = 0; j < 3; ++j)
	{
		_setVisible(eBox1 + j, m_pRNode, false);
	}

	//设置展示
	for(int i = 0; i < size; ++i)
	{
		item = CLIMBTOWERDATAHANDLER->enterData.skillData[i];
		//icon
		_setTexture(eBox1 + i, m_pRNode, RESOURCEDAIDMANAGER->getDataByID(item->iconId).c_str());
	}
}

void ClimbTowerWindow::ShowBeginPage()
{
	m_iRightShowNode = right_Begin;

	//使用autocreate创建页面
	if(m_pRNode)
	{
		m_pRNode->removeAllChildrenWithCleanup(true);
	}
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERVIEWBEGIN, m_pRNode);
	
	//绑定按钮
	_mapBeginPageBtn();

	//显示更新显示
	_setBeginPageInfo();
	
	//检查是否有未领取的层级奖励
	CheckHaveFloorReward();
}

void ClimbTowerWindow::ShowEndPage()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::ShowEndPage -- begin\n");
	m_iRightShowNode = right_End;

	//使用autocreate创建页面
	if(m_pRNode)
	{
		m_pRNode->removeAllChildrenWithCleanup(true);
	}
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERVIEWEND, m_pRNode);

	//绑定按钮
	_mapEndPageBtn();

	//显示更新显示
	_setEndPageInfo();

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::ShowEndPage -- end\n");

	//检查是否有未领取的层级奖励
	CheckHaveFloorReward();
}

void ClimbTowerWindow::ShowFightResultPage()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::ShowFightResultPage --- begin\n");

	m_iRightShowNode = right_FightResult;

	//显示页面
	if(m_pRNode)
	{
		m_pRNode->removeAllChildrenWithCleanup(true);
	}
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERFIGHTRESULT, m_pRNode);

	//绑定按钮
	_mapFightResultPageBtn();

	//显示信息
	_setFightResultPageInfo();

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::ShowFightResultPage --- end\n");
}

void ClimbTowerWindow::_setFightResultPageInfo()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_setFightResultPageInfo --- begin");

	CCNode * node = m_pRNode->getChildByTag(fTableCell);
	m_szCELLFightResult = node->getContentSize();

	m_pTableReward = NULL;

	m_pTableFightResult =(CCTableView*)m_pRNode->getChildByTag(fTableView);
	m_pTableFightResult->setDataSource(this);
	m_pTableFightResult->setDelegate(this);
	m_pTableFightResult->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);//竖向
	m_pTableFightResult->setTouchEnabled(true);
	m_pTableFightResult->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTableFightResult);

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_setFightResultPageInfo --- end");
}

void ClimbTowerWindow::_mapFightResultPageBtn()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_mapFightResultPageBtn --- begin");

	CCMenu * menu = (CCMenu *)m_pRNode->getChildByTag(fConfirmBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_FightResultPage_Btn_Click));
	item->setTag(fConfirmBtn + 100);


	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_mapFightResultPageBtn --- end");
}

void ClimbTowerWindow::ShowRewardPage()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::ShowRewardPage --- begin\n");

	//显示页面
	if(m_pRewardNode)
	{
		m_pRewardNode->removeAllChildrenWithCleanup(true);
	}
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERREWARD, m_pRewardNode);

	_mapRewardPageBtn();
	
	_setRewardPageInfo();

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::ShowRewardPage --- end\n");
}

void ClimbTowerWindow::_mapRewardPageBtn()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_mapRewardPageBtn --- begin\n");

	CCMenu * menu = (CCMenu *)m_pRewardNode->getChildByTag(rCloseBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_RewardPage_Btn_Click));
	item->setTag(rCloseBtn);

	DTAwardBoard * dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward);
	dtab->setTarget(this, menu_selector(ClimbTowerWindow::On_RewardPage_Btn_Click));
	dtab->setTag(rReward);

	menu = (CCMenu *)m_pRewardNode->getChildByTag(rLingQuBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(ClimbTowerWindow::On_RewardPage_Btn_Click));
	item->setTag(rLingQuBtn);
	item->setEnabled(false);

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_mapRewardPageBtn --- end\n");
}

void ClimbTowerWindow::_setRewardPageInfo()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_setRewardPageInfo --- begin\n");
	
	//设置左侧奖励列表
	CCNode * node = m_pRewardNode->getChildByTag(rTabelCell);
	m_szCellReward = node->getContentSize();

	m_pTableFightResult = NULL;

	m_pTableReward =(CCTableView*)m_pRewardNode->getChildByTag(rTabelView);
	m_pTableReward->setDataSource(this);
	m_pTableReward->setDelegate(this);
	m_pTableReward->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);//竖向
	m_pTableReward->setTouchEnabled(true);
	m_pTableReward->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTableReward);

	//设置右侧终身奖励等
	TowerRewardData * reward = CLIMBTOWERDATAHANDLER->m_pRewardData;
	if(!reward)
		return;
	char temp[512] = {0};
	//最好成绩
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2055).c_str(), reward->topFloor);
	NFC_setLabelString(rBestFloorValue, m_pRewardNode, temp);
	//当前排名
	if(reward->rank > 0)
	{
		sprintf(temp, "%d", reward->rank);
	}
	else
	{
		sprintf(temp, "%s", SysLangDataManager::get_instance2()->GetSysLangById(614).c_str());
	}
	NFC_setLabelString(rRankValue, m_pRewardNode, temp);
	//刷新显示下阶段奖励
	_setRewardPageNext();
	
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::_setRewardPageInfo --- end\n");
}

void ClimbTowerWindow::_setRewardPageNext()
{
	TowerRewardData * reward = CLIMBTOWERDATAHANDLER->m_pRewardData;
	if(!reward)
		return;
	TowerReward * towerReward = reward->getFirstUnOpenTowerReward();
	char temp[512] = {0};
	if(towerReward)
	{//设置下阶段奖励
		//奖励
		DTAwardBoard * dtab = (DTAwardBoard *)m_pRewardNode->getChildByTag(rReward);
		dtab->ChangeObject(towerReward->quality, towerReward->iconId, 1);
		dtab->setIDX(towerReward->templateId);

// 		CCMenu * menu = (CCMenu *)m_pRewardNode->getChildByTag(rQuality);
// 		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(rQuality);
// 		item->setIDX(towerReward->templateId);
// 		CCSprite * sp = CCSprite::create(varConfig::getCardBGFilePath(towerReward->quality).c_str());
// 		item->setNormalImage(sp);
// 		sp = CCSprite::create(varConfig::getCardBGFilePath(towerReward->quality).c_str());
// 		item->setSelectedImage(sp);
// 		//奖励图片
// 		NFC_setPicForCCSprite(rIcon, m_pRewardNode, RESOURCEDAIDMANAGER->getDataByID(towerReward->iconId), true);

		//物品名称
		NFC_setLabelString(rName, m_pRewardNode, towerReward->name, true);
		//领取按钮
		CCMenu * menu = (CCMenu *)m_pRewardNode->getChildByTag(rLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(rLingQuBtn);
		item->setIDX(towerReward->rewardFloor);
		if(towerReward->rewardFloor <= reward->topFloor)//从reward->curFloor改成了reward->topFloor  by fangjun @ 20140317
		{
			item->setEnabled(true);
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2052).c_str(), towerReward->rewardFloor);
			NFC_setLabelString(rLingQuNeed, m_pRewardNode, temp, true);
		}else
		{
			item->setEnabled(false);
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2053).c_str(), towerReward->rewardFloor);
			NFC_setLabelString(rLingQuNeed, m_pRewardNode, temp, true);
		}

	}
	else
	{//已经没有下阶段奖励可领取时，将要隐藏界面
		for(int i = rNextRewardLabel; i <= rLingQuNeed; ++i)
		{
			NFC_showNode(i, m_pRewardNode, false);
		}
	}
}

void ClimbTowerWindow::BeginChallengeTower()
{
	CLIMBTOWERDATAHANDLER->ToServerStartTower();

	/*
	//需要判断次数
	if(CLIMBTOWERDATAHANDLER->HasFreeTimes())
	{
		if(CLIMBTOWERDATAHANDLER->iCurFloor >= 20)
		{
			FirstJump();
		}
		else
		{
			CLIMBTOWERDATAHANDLER->ToServerChallengeTower();
		}
	}
	else if(CLIMBTOWERDATAHANDLER->HasPayTimes())
	{
		//是,弹出提示今日免费此时已用完，是否使用道具增加次数
		std::string title = SysLangDataManager::get_instance2()->GetSysLangById(454);
		std::string message = SysLangDataManager::get_instance2()->GetSysLangById(456);
		char num[32];
		sprintf(num,"%d",kCLIMBTOWERPAYTIME);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_,num,title,message);
	}
	else
	{
		//否，弹出提示没有次数了
		std::string title = SysLangDataManager::get_instance2()->GetSysLangById(454);
		std::string message = SysLangDataManager::get_instance2()->GetSysLangById(455);
		char num[32];
		sprintf(num,"%d",kDEFAULT);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_,num,title,message);
	}
	*/
}

void ClimbTowerWindow::On_BeginPage_Btn_Click(cocos2d::CCObject* pSender)
{
	CCMenuItem * menu = (CCMenuItem *)pSender;
	int tag = menu->getTag();
	if(bListBtn == tag)//排行榜
	{
		NFC_showCommunicationWating(true);
		CLIMBTOWERDATAHANDLER->ToServerRankList();
	}
	else if(bStartBtn == tag)//开始
	{
		if(CLIMBTOWERDATAHANDLER->enterData.nowfloor >= TOWER_FLOOR_TOTAL)
		{
			NFC_showMessageBoxSingle(kDEFAULT, SysLangDataManager::get_instance2()->GetSysLangById(2023));
		}
		else
		{
			BeginChallengeTower();
		}
	}
	else if(bBaoXiangBtn == tag)//宝箱
	{
		CLIMBTOWERDATAHANDLER->ToServerEnterReward();
	}
	else if(bBuyBtn == tag)//购买次数
	{
		CLIMBTOWERDATAHANDLER->ToServerBuyClimbTowerTimes();
	}
}

void ClimbTowerWindow::On_EndPage_Btn_Click(cocos2d::CCObject* pSender)
{
	CCMenuItem * menu = (CCMenuItem *)pSender;
	int tag = menu->getTag();
	if(eListBtn == tag)//排行榜
	{
		CLIMBTOWERDATAHANDLER->ToServerRankList();
	}
	else if(eBaoXiangBtn == tag)
	{//宝箱
		CLIMBTOWERDATAHANDLER->ToServerEnterReward();
	}
	else if(eResetBtn == tag)//重置
	{
		if(CLIMBTOWERDATAHANDLER->enterData.leftChallengeTime <= 0)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_TOWER_COMFIRM_RESET_);
		}
		else
		{
			std::string message = SysLangDataManager::get_instance2()->GetSysLangById(618);
			NFC_showMessageBox(kCLIMBTOWERRESET,message);
		}
		
	}
	else if(eJewelResetBtn == tag)
	{//钻石重置
		CLIMBTOWERDATAHANDLER->ToServerJewelReset();
	}
	else if(eFastFightBtn == tag)
	{//快速战斗
		if(CLIMBTOWERDATAHANDLER->enterData.nowfloor >= TOWER_FLOOR_TOTAL)
		{
			NFC_showMessageBoxSingle(kDEFAULT, SysLangDataManager::get_instance2()->GetSysLangById(2023));
		}
		else
		{
			delete CLIMBTOWERDATAHANDLER->m_pFastFightResultData;

			CLIMBTOWERDATAHANDLER->m_pFastFightResultData = NULL;

			CLIMBTOWERDATAHANDLER->ToServerFastFight();
		}
		
	}
	else if(eContinueBtn == tag)//继续
	{
		if(CLIMBTOWERDATAHANDLER->enterData.nowfloor >= TOWER_FLOOR_TOTAL)
		{
			NFC_showMessageBoxSingle(kDEFAULT, SysLangDataManager::get_instance2()->GetSysLangById(2023));
		}
		else
		{
			CLIMBTOWERDATAHANDLER->ToServerChallengeTower();
		}
	}


	
}

void ClimbTowerWindow::On_FightResultPage_Btn_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(tag == fcChaKan)
	{//查看战斗情况
		//not today

	}
	else if(tag == fConfirmBtn + 100)
	{//确定呢。关闭界面
		m_bInFashFightMode = false;

		_removeGrayLayer();//移除防触控遮罩层

		CLIMBTOWERDATAHANDLER->ToServerEnterTower();//重新进入一次塔
	}
}

void ClimbTowerWindow::On_RewardPage_Btn_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(tag == rCloseBtn)
	{//关闭页面
		m_pRewardNode->removeAllChildrenWithCleanup(true);
	}
	else if(tag == rReward)
	{//查看终身奖励
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(item->getIDX(), _TYPED_WINDOW_CLIMBWINDOW_);
	}
	else if(tag == rLingQuBtn)
	{//领取按钮
		CLIMBTOWERDATAHANDLER->ToServerGetReward(1, item->getIDX());
	}
}

void ClimbTowerWindow::On_RewardPageCell_Btn_Click(cocos2d::CCObject* pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(tag == rcLingQuBtn)
	{//领取当前奖励
		CLIMBTOWERDATAHANDLER->ToServerGetReward(0, item->getIDX());
	}
	else if(tag == rcReward)
	{//查看物品资料
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(item->getIDX(), _TYPED_WINDOW_CLIMBWINDOW_);
	}
}

void ClimbTowerWindow::On_MainPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CCMenuItem * item = (CCMenuItem *)pSender;
	int tag = item->getTag();
	
	if(ctCloseBtn == tag)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
		//背景音乐 关主场景，开爬塔
		char _typeID[64]="";
		sprintf(_typeID,"%d",kSOUND_STOP_TYPE_EFFECT_AND_BACKGROUND);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_,_typeID);

		LoadingAnimationData* pData= LoadingAnimationManager::get_instance2()->GeLoadingAnimationDataByID(IProcedure::_TYPED_HOME_PROCEDURE_);
		if (pData->mBackgroundSuondID != -1)
		{
			char _soundID[64]="";
			sprintf(_soundID,"%d",pData->mBackgroundSuondID);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
		}
	}

}

void ClimbTowerWindow::EnterTower()
{
	if(m_iRightShowNode == right_Begin)
	{
		ShowBeginPage();
	}
	else if(m_iRightShowNode == right_End)
	{
		ShowEndPage();
	}

	//通过获得信息更新地图和人物位置
	_refreshMapHero();


}

void ClimbTowerWindow::Function_EnterTower()
{
	//判断进入塔类型，通过类型显示对应界面
	if(CLIMBTOWERDATAHANDLER->enterData.entertype == 0)
	{//首次进入
		ShowBeginPage();
		_checkNewFunc();
	}
	else if(CLIMBTOWERDATAHANDLER->enterData.entertype == 1)
	{//再次进入
		ShowEndPage();
	}

	//通过获得信息更新地图和人物位置
	_refreshMapHero();

}


void ClimbTowerWindow::Function_ChallengeTowerEnd()
{
	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::Function_ChallengeTowerEnd -- begin\n");

	//显示爬塔第二阶段界面
	ShowEndPage();

	//通过获得信息更新地图和人物位置
	_refreshMapHero();

	LOGGERSYSTEM->LogInfo("ClimbTowerWindow::Function_ChallengeTowerEnd -- end\n");
}

void ClimbTowerWindow::Function_ComfirmReset()
{
	CLIMBTOWERDATAHANDLER->ToServerResetTower();
}

void ClimbTowerWindow::Function_NotifyHeroRun()
{
	NFC_showCommunicationWating(false);
	_createGrayLayer();

	m_bStartRun = true;

	m_iRightShowNode = right_End;

	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("Pao-01", true); 

	//关闭飘字
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);

}

void ClimbTowerWindow::Function_StartTower()
{
	NFC_showCommunicationWating(false);

	if(CLIMBTOWERDATAHANDLER->iCurFloor >= 2)
	{
		FirstJump();
	}
	else
	{
		CLIMBTOWERDATAHANDLER->ToServerChallengeTower();
	}
}

void ClimbTowerWindow::Function_ResetTower()
{
	NFC_showCommunicationWating(false);

	ShowBeginPage();

	//通过获得信息更新地图和人物位置
	_refreshMapHero();
}

void ClimbTowerWindow::Function_GetFastFightResult()
{
	m_iFastFightRound++;
	LOGGERSYSTEM->LogInfo("now fast fight is in round [%d]", m_iFastFightRound);

	m_bStartRun = true;
	int sz = CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData.size();
	CLIMBTOWERDATAHANDLER->iPreFloor = CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData[sz - 1]->fightFloor - 1;
	
	if(!m_bInFashFightMode)
	{
		m_bInFashFightMode = true;

		ShowFightResultPage();

		CCMenu * menu = (CCMenu *)m_pRNode->getChildByTag(fConfirmBtn);
		CCMenuItem * item = (CCMenuItem *)menu->getChildByTag(fConfirmBtn + 100);
		item->setEnabled(false);

		_createGrayLayer();

		//关闭飘字
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);
	}
	
	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("Pao-01", true); 
}

/*
	钻石重置结果
*/
void ClimbTowerWindow::Function_JewelResetResult()
{
	Function_ResetTower();
}

/*
	获得奖励展示数据
*/
void ClimbTowerWindow::Function_EnterRewardData()
{
	ShowRewardPage();

	//NFC_refreshTableView(m_pTableReward);
}

/*
	领取某个奖励的返回
*/
void ClimbTowerWindow::Function_GetRewardResult(char type, int idx)
{
	if(type == 0)
	{//日常奖励
		cocos2d::extension::CCTableViewCell * cell = m_pTableReward->cellAtIndex(idx);
		if(cell)
		{
			CCMenu * menu = (CCMenu *)cell->getChildByTag(rcLingQuBtn);
			CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(rcLingQuBtn);
			item->setEnabled(false);
			NFC_setLabelString(rcLingQuLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2014), true);
		}
	}
	else
	{//终身奖励
		_setRewardPageNext();//设置下一个终身奖励
	}

	//检查是否有未领取的层级奖励
	CheckHaveFloorReward();
}

void ClimbTowerWindow::Function_LostRetryFastFight()
{
	if(m_bInFashFightMode)
	{
		CLIMBTOWERDATAHANDLER->ToServerFastFight();
	}
}

/*void ClimbTowerWindow::Function_ComfirmPaytime()
{
	//判断背包是否有该物品
	int itemcount = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(28002);

	//是否有物品
	if(itemcount > 0)
	{
		if(CLIMBTOWERDATAHANDLER->iCurFloor >= 20)
		{
			FirstJump();
		}
		else
		{
			CLIMBTOWERDATAHANDLER->ToServerChallengeTower();
		}
	}
	else
	{
		//跳出界面，提示，道具不足，是否进入商城购买
		std::string title = SysLangDataManager::get_instance2()->GetSysLangById(457);
		std::string message = SysLangDataManager::get_instance2()->GetSysLangById(458);
		char num[32];
		sprintf(num,"%d",kCLIMBTOWERENTERSHOP);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_,num,title,message);
	}

}*/

/*void ClimbTowerWindow::Function_ComfirmEnterShop()
{
// 	进入商城事件
// 	PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_);
// 	PushEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_);
	CLIMBTOWERDATAHANDLER->ToServerChallengeTower();

}*/

//创建遮罩层，用于特效显示时屏蔽用户点击
void ClimbTowerWindow::_createGrayLayer()
{
	m_pAnimationGrayLayer = CPriorityLayerColor::create(ccc4(0,0,0,0),3000,2000,kPRIORITYLOW2);
	m_pAnimationGrayLayer->setAnchorPoint(ccp(0,0));
	m_pAnimationGrayLayer->setPosition(ccp(0,0));
	m_pRoot->addChild(m_pAnimationGrayLayer,10);
}

void ClimbTowerWindow::_removeGrayLayer()
{
	if(m_pAnimationGrayLayer)
		m_pAnimationGrayLayer->removeFromParentAndCleanup(true);
	m_pAnimationGrayLayer = NULL;
}

void ClimbTowerWindow::_initAnimationEffect()
{
	//特效数据
	m_pAnimationPlayNode = cocos2d::CCSprite::create();
	MaskNode * effectNode = (MaskNode *)m_pRoot->getChildByTag(ctAnimationNode);
	effectNode->addChild(m_pAnimationPlayNode);

}

void ClimbTowerWindow::PlayEffect()
{
	_createGrayLayer();

	MaskNode * effectNode = (MaskNode *)m_pRoot->getChildByTag(ctAnimationNode);
	int effectId = effectNode->GetViewData().colorR_;
	m_pAnimationFileData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(effectId);

	m_pAnimation = EngineSystem::get_instance2()->GetAnimtionByName(m_pAnimationFileData->mAnimationName);

	m_pAnimationPlayNode->setDisplayFrameWithAnimationName(m_pAnimationFileData->mAnimationName, 0);
	m_pAnimationPlayNode->setScale(m_pAnimationFileData->mAnimationScale);
	m_pAnimationPlayNode->setVisible(false);

	//m_pAnimationPlayNode->setDisplayFrameWithAnimationName(m_pAnimationFileData->mAnimationName, 1);
	if(m_pAnimation)
	{
		CCAnimationEffect * pAnimationEffect = CCAnimationEffect::create(m_pAnimationPlayNode,m_pAnimation);
		if(pAnimationEffect)
		{
			pAnimationAction = cocos2d::CCRepeatForever::create(pAnimationEffect);
			m_pAnimationPlayNode->setVisible(true);
			m_pAnimationPlayNode->runAction(pAnimationAction);
		}
	}
}

void ClimbTowerWindow::FirstJump()
{
	LevelUpDataHandler::get_instance2()->m_showFlag = false;

	m_iRightShowNode = right_End;

	m_pRNode->setVisible(false);//冲刺时隐藏右侧界面

	//播放向上冲刺的动画
	PlayEffect();

	//冲刺骨骼
	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("PaTa", false); 

	m_bStartJump = true;

	_jumptickfloor = 8;
}

void ClimbTowerWindow::CheckIfNeedLvUp()
{
	if (LevelUpDataHandler::get_instance2()->LevelUpDataList.size()>0) 
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_, _to_event_param_(m_WindowType));
	}
}

void ClimbTowerWindow::CheckHaveFloorReward()
{
	//显示发光的宝箱提示
	bool show = false;
	if(CLIMBTOWERDATAHANDLER->enterData.haveFloorReward > 0)
		show = true;

	if(m_iRightShowNode == right_Begin)
	{
		NFC_showNode(bBaoXiangEffect, m_pRNode, show);
	}
	else if(m_iRightShowNode == right_End)
	{
		NFC_showNode(eBaoXiangEffect, m_pRNode, show);
	}

}

void ClimbTowerWindow::_createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell)
{
	if(table == m_pTableFightResult)
	{//快速战斗结果
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERFIGHTRESULTCELL, cell);
	}
	else if(table == m_pTableReward)
	{//层级奖励
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCLIMBTOWERREWARDCELL, cell);

		//奖励
		DTAwardBoard * dtab = (DTAwardBoard *)cell->getChildByTag(rcReward);
		dtab->setTarget(this, menu_selector(ClimbTowerWindow::On_RewardPageCell_Btn_Click));
		dtab->setTag(rcReward);

		//领取按钮
		CCMenu * menu = (CCMenu *)cell->getChildByTag(rcLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(rcLingQuBtn);
		item->setTarget(this, menu_selector(ClimbTowerWindow::On_RewardPageCell_Btn_Click));

	}
}

void ClimbTowerWindow::_setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell, int cellIdx)
{
	if(table == m_pTableFightResult)
	{//快速战斗结果
		if(CLIMBTOWERDATAHANDLER->m_pFastFightResultData == NULL)
			return;

		int sz = CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData.size();

		TowerFastFightResultItem * data = CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData[sz - 1 - cellIdx];//让结果倒序显示

		char temp[128] = {0};
		CSprite * sp = (CSprite *)cell->getChildByTag(fcResult);
		//结果
		if(data->result > 0)
			sp->changeToImage1();
		else
			sp->changeToImage2();
		//层数
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2011).c_str(), data->fightFloor);
		NFC_setLabelString(fcFloor, cell, temp, true);
		//经验获得
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2012).c_str(), data->gotExp);
		NFC_setLabelString(fcExpGet, cell, temp, true);
		//荣誉获得
// 		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2013).c_str(), data->gotHonor);
// 		NFC_setLabelString(fcHonorGet, cell, temp, true);
		//查看按钮
		NFC_showNode(fcChaKan, cell, false);
		NFC_showNode(fcChaKanLabel, cell, false);
	}
	else if(table == m_pTableReward)
	{//层级奖励
		char temp[512] = {0};

		TowerRewardData * reward = CLIMBTOWERDATAHANDLER->m_pRewardData;

		if(reward == NULL)
			return;

		TowerTodayReward * todayReward = CLIMBTOWERDATAHANDLER->m_pRewardData->todayRewardVector[cellIdx];
		//奖励
		DTAwardBoard * dtab = (DTAwardBoard *)cell->getChildByTag(rcReward);
		dtab->setIDX(todayReward->templateId);
		if(todayReward->type == kDT_AWARD_OBJECT)
		{//物品
			dtab->ChangeObject(todayReward->quality, todayReward->iconId, 1);
			dtab->setEnabled(true);
		}
		else if(todayReward->type == kDT_AWARD_MONEY)
		{//金钱
			dtab->ChangeObject(_GOLD_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD), 1);
			dtab->setEnabled(false);
			todayReward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_MONEY_TID);
		}
		else if(todayReward->type == kDT_AWARD_EXP)
		{//经验
			dtab->ChangeObject(_EXP_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP), 1);
			dtab->setEnabled(false);
			todayReward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_EXP_TID);
		}
		else if(todayReward->type == kDT_AWARD_DIAMOND)
		{//钻石
			dtab->ChangeObject(_DIAMOND_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND), 1);
			dtab->setEnabled(false);
			todayReward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_DIAMOND_TID);
		}
		else if(todayReward->type == kDT_AWARD_PRESTIGE)
		{//声望
			dtab->ChangeObject(_PREGIST_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE), 1);
			dtab->setEnabled(false);
			todayReward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_PRESTIGE_TID);
		}
		else if(todayReward->type == kDT_AWARD_POWER)
		{//体力
			dtab->ChangeObject(_POWER_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG), 1);
			dtab->setEnabled(false);
			todayReward->name = SysLangDataManager::get_instance2()->GetSysLangById(kDT_POWER_TID);
		}
	
		//名称数量
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(7008).c_str(), todayReward->name.c_str(), todayReward->count);
		NFC_setLabelString(rcNameNum, cell, temp, true);

		//层数
		if(reward->curFloor >= todayReward->rewardFloor)
		{
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2054).c_str(), reward->curFloor, todayReward->rewardFloor);
		}
		else
		{
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2058).c_str(), reward->curFloor, todayReward->rewardFloor);
		}
		NFC_setLabelString(rcFloor, cell, temp);

		CCMenu * menu = (CCMenu *)cell->getChildByTag(rcLingQuBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(rcLingQuBtn);
		if(todayReward->status == 0)
		{//已领取
			NFC_setLabelString(rcLingQuLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2014), true);
			item->setEnabled(false);
		}
		else if(todayReward->status == 1)
		{//可领取
			NFC_setLabelString(rcLingQuLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2010), true);
			item->setEnabled(true);
			item->setIDX(todayReward->rewardFloor);
		}
		else if(todayReward->status == 2)
		{//不可领取
			NFC_setLabelString(rcLingQuLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(2015), true);
			item->setEnabled(false);
		}

		//箭头状态
		cocos2d::extension::CCTableViewCell * cell_end = NULL;
		cell_end = table->cellAtIndex(numberOfCellsInTableView(table) - 1);
		if(cell_end && cell_end->isVisible())
		{
			NFC_setNodeVisable(rDownArrowMove,m_pRewardNode,false);
			NFC_setNodeVisable(rDownArrow,m_pRewardNode,true);
		}
		else
		{
			NFC_setNodeVisable(rDownArrowMove,m_pRewardNode,true);
			NFC_setNodeVisable(rDownArrow,m_pRewardNode,false);
		}
	}
}

cocos2d::CCSize ClimbTowerWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	if(table == m_pTableFightResult)
	{
		return m_szCELLFightResult;
	}
	else if(table == m_pTableReward)
	{
		return m_szCellReward;
	}

	return CCSize(0, 0);
}

cocos2d::extension::CCTableViewCell* ClimbTowerWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int ClimbTowerWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(table == m_pTableFightResult)
	{
		if(CLIMBTOWERDATAHANDLER->m_pFastFightResultData)
			return CLIMBTOWERDATAHANDLER->m_pFastFightResultData->resultData.size();
	}
	else if(table == m_pTableReward)
	{
		if(CLIMBTOWERDATAHANDLER->m_pRewardData)
			return CLIMBTOWERDATAHANDLER->m_pRewardData->todayRewardVector.size();
	}
	
	return 0;
}

