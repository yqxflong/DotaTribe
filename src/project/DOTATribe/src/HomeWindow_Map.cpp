//Name：HomeWindow
//Function：实现地图建筑相关功能
//Written By：尹强
//PS:头文件为HomeWindow.h

#include "../include/HomeWindow.h"
#include "../include/config_HomeWindow.h"
#include "../include/CMenuItemSprite.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/GuideSystem.h"
#include "../Include/MissionDataHandler.h"
#include "../include/DOTATribeApp.h"
#include "../Include/HomeProcedure.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/TeamBattleDataHandler.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/C2SArenaInfoPacket.h"
#include "../include/RoleInfoDataHandler.h"


//点击建筑事件
void HomeWindow::On_Click_Event_MainBG(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	switch(cc->getIDX()){
	case udBAR:
		_barEvent();
		break;
	case udDOOR:
		_doorEvent();
		break;
	case udHOME:
		_homeEvent();
		break;
	case udSHOP:
		_shopEvent();
		break;
	case udPKPLACE:
		_pkPlaceEvent();
		break;
	case udTDOOR:
		_tdoorEvent();
		break;
	case udTOWER:
		_towerEvent();
		break;
	case udMINERALHOLE:
		_mineralhole();
		break;
	default:
		break;
	}
}

//酒馆事件
void HomeWindow::_barEvent(){
	if (_buildingCheckOpened(udBAR))
	{
		PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HEROBARWINDOW_);
		//功能开启下一步
		GUIDESYSTEM->Next();
	}
}

//大门出城
void HomeWindow::_doorEvent(){
	MissionDataHandler::get_instance2()->setCurMissionID(MissionDataHandler::get_instance2()->getMissonInfoDataList().size());
	DOTATribeApp::get_instance2()->m_pHomeProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);
//	GUIDESYSTEM->Next();
	GUIDESYSTEM->NextBegin();
}

//神庙事件
void HomeWindow::_homeEvent(){
	if (_buildingCheckOpened(udHOME))
	{
		PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_TEMPLEWINDOW_);
		NFC_showCommunicationWating(true);
	}
}

//传送门事件
void HomeWindow::_tdoorEvent(){
	if (_buildingCheckOpened(udTDOOR))
	{
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->SetBackWindow(_TYPED_EVENT_SHOW_HOMEWINDOW_);
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_, _to_event_param_(IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_));
	}
}

/*
	黑市商人事件
*/
void HomeWindow::_shopEvent(){
	if (_buildingCheckOpened(udSHOP))
	{
		PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_);
	}
}

/*
	竞技场事件
*/
void HomeWindow::_pkPlaceEvent(){	
	if (_buildingCheckOpened(udPKPLACE))
	{
		C2SArenaInfoPacket  requestArenaInfo;
		requestArenaInfo.Send();	
	} 
}
/*
	爬塔事件
*/
void HomeWindow::_towerEvent(){
	if (_buildingCheckOpened(udTOWER))
	{
		PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
		CLIMBTOWERDATAHANDLER->ToServerEnterTower();
	}
}

/*
	矿洞事件
	*仆从
*/
void HomeWindow::_mineralhole(){
	if (_buildingCheckOpened(udMINERALHOLE))
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
	}
}

	/*	
		检查建筑解锁情况
	*/
void HomeWindow::_checkBuildingLock(){
	_checkBuildingLock_HeroBar();
	_checkBuildingLock_Market();
	_checkBuildingLock_PkPlace();
	_checkBuildingLock_Tower();
	_checkBuildingLock_TeamPVE();
	_checkBuildingLock_HomeTown();
	_checkBuildingLock_Labor();
}

/*	
		检查酒馆解锁情况
	*/
void HomeWindow::_checkBuildingLock_HeroBar(){
	if(!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROBAR)){
		_buildingCheckHint(udBAR,false);
		_enableBuildingEffect(udBAR,false);
		_buildingCheckDisplay(udBAR,false);
	}else{//开启新模块
		_buildingCheckNewOpen(udBAR);
		_buildingCheckHint(udBAR,true);
		_enableBuildingEffect(udBAR,true);
		_buildingCheckDisplay(udBAR,true);
	}
}
	/*	
		检查黑市解锁情况
	*/
void HomeWindow::_checkBuildingLock_Market(){
	if(!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MARKET)){//黑市
		NFC_showNode(udREALBUSSINESSMAN,m_pMapScroll->getContainer(),false);
		_buildingCheckHint(udSHOP,false);
		_enableBuildingEffect(udSHOP,false);
		_buildingCheckDisplay(udSHOP,false);
	}else{//开启新模块
		NFC_showNode(udREALBUSSINESSMAN,m_pMapScroll->getContainer(),true);
		_buildingCheckHint(udSHOP,true);
		_enableBuildingEffect(udSHOP,true);
		_buildingCheckDisplay(udSHOP,true);
	}
}
	/*	
		检查竞技场解锁情况
	*/
void HomeWindow::_checkBuildingLock_PkPlace(){
	if(!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_PKPLACE)){//竞技场
		_buildingCheckHint(udPKPLACE,false);
		_enableBuildingEffect(udPKPLACE,false);
		_buildingCheckDisplay(udPKPLACE,false);
	}else{//开启新模块
		_buildingCheckNewOpen(udPKPLACE);
		_buildingCheckHint(udPKPLACE,true);
		_enableBuildingEffect(udPKPLACE,true);
		_buildingCheckDisplay(udPKPLACE,true);
	}
}
	/*	
		检查爬塔解锁情况
	*/
void HomeWindow::_checkBuildingLock_Tower(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TOWER))//爬塔
	{
		_buildingCheckHint(udTOWER,false);
		_buildingCheckDisplay(udTOWER,false);
	}else{//开启新模块
		_buildingCheckNewOpen(udTOWER);
		_buildingCheckHint(udTOWER,true);
		_buildingCheckDisplay(udTOWER,true);
	}
}
	/*	
		检查组队副本解锁情况
	*/
void HomeWindow::_checkBuildingLock_TeamPVE(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TEAMPVE))//远古之门
	{
		_buildingCheckHint(udTDOOR,false);
		_enableBuildingEffect(udTDOOR,false);
		_buildingCheckDisplay(udTDOOR,false);
	}else{//开启新模块
		_buildingCheckNewOpen(udTDOOR);
		_buildingCheckHint(udTDOOR,true);
		_enableBuildingEffect(udTDOOR,true);
		_buildingCheckDisplay(udTDOOR,true);
	}
}
	/*	
		检查神庙解锁情况
	*/
void HomeWindow::_checkBuildingLock_HomeTown(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROTECH))//神庙
	{
		_buildingCheckHint(udHOME,false);
		_enableBuildingEffect(udHOME,false);
		_buildingCheckDisplay(udHOME,false);
	}else{//开启新模块
		_buildingCheckNewOpen(udHOME);
		_buildingCheckHint(udHOME,true);
		_enableBuildingEffect(udHOME,true);
		_buildingCheckDisplay(udHOME,true);
	}
}
	/*
		检查矿洞解锁情况
	*/
void HomeWindow::_checkBuildingLock_Labor(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HUNT))//矿洞
	{
		_buildingCheckHint(udMINERALHOLE,false);
		_enableBuildingEffect(udMINERALHOLE,false);
		_buildingCheckDisplay(udMINERALHOLE,false);
	}else{
		_buildingCheckNewOpen(udMINERALHOLE);
		_buildingCheckHint(udMINERALHOLE,true);
		_enableBuildingEffect(udMINERALHOLE,true);
		_buildingCheckDisplay(udMINERALHOLE,true);
	}
}

/*
		检查其他解锁情况解锁情况
	*/
void HomeWindow::_checkOtherLock(){
	_checkOtherLock_Labor();
	_checkOtherLock_GoldMine_();
}
	/*
		===开启矿洞
		===第二次
		===奴隶开启
	*/
void HomeWindow::_checkOtherLock_Labor(){
	if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_SERVANT))
	{
		if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_3_LABOR))
		{
			LOGGERSYSTEM->LogInfo("HomeWindow::_checkOtherLock_Labor");
			GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_3_LABOR);
		}
	}
}
	/*
		===开启矿洞
		===第三次
		===金矿采集开启
	*/
void HomeWindow::_checkOtherLock_GoldMine_()
{
	if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MINING))
	{
		if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE))
		{
			LOGGERSYSTEM->LogInfo("HomeWindow::_checkOtherLock_GoldMine_");
			GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE);
		}
	}
}

	/*
		将地图移动至最右边
	*/
void HomeWindow::_moveMapToRightBottom(){
	int second=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_HOMEMAP_MOVE_DURING);
	m_pMapScroll->setContentOffsetInDuration(ccp(-(m_pMapScroll->getContentSize().width-m_pMapScroll->getViewSize().width),0),(float)second*1.0/1000);
}
	/*
		将地图移动至最左边
	*/
void HomeWindow::_moveMapToLeftTop(){
	int second=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_HOMEMAP_MOVE_DURING);
	m_pMapScroll->setContentOffsetInDuration(ccp(0,0),(float)second*1.0/1000);
}

	/*
		创建new字样by坐标
	*/
void HomeWindow::_createFlowNewICon(const CCPoint &cp,int key){
	MaskNode* node=(MaskNode*)NFC_getNode(udICON_NEW,m_pMapScroll->getContainer());
	const UIViewData &dd=node->GetViewData();
	//begin:删除旧节点
	CCNode* cc_old=NFC_getNode(key,m_pMapScroll->getContainer());
	if (cc_old)
		cc_old->removeFromParentAndCleanup(true);
	//end
	CCSprite* cc=NFC_createSpriteByViewData(m_pMapScroll->getContainer(),dd);
	cc->setTag(key);
	cc->setPosition(ccp(cp.x,cp.y+dd.posy_));
	CCPoint cp_move=CCPointZero;
	cp_move.y=dd.height_;
	NFC_Action_MoveAndReverse(cc,dd.width_,cp_move,true);
}

	/*
		显示new字样给指定建筑
	*/
void HomeWindow::_showNewFlowICon4Building(int ModuleID){
	CCNode* node_building=NULL;
	switch(ModuleID){
		case GuideSystem::_TYPED_NEWFUNC_1_HEROBAR:
			node_building=NFC_getMenuItem(udBAR,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_HEROBAR);
			_moveMapToLeftTop();
			building_status[0]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_2_AREANA:
			node_building=NFC_getMenuItem(udPKPLACE,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_AREANA);
			_moveMapToLeftTop();
			building_status[1]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_3_LABOR:
			node_building=NFC_getMenuItem(udMINERALHOLE,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_MINERAL);
			_moveMapToRightBottom();
			building_status[2]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_4_HEROTECH:
			node_building=NFC_getMenuItem(udHOME,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_HEROTECH);
			_moveMapToLeftTop();
			building_status[3]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_5_TOWER:
			node_building=NFC_getMenuItem(udTOWER,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_TOWER);
			_moveMapToRightBottom();
			building_status[4]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE:
			node_building=NFC_getMenuItem(udTDOOR,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_TEAMBATTLE);
			_moveMapToRightBottom();
			building_status[5]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_7_MINERAL:
			node_building=NFC_getMenuItem(udMINERALHOLE,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_MINERAL);
			_moveMapToRightBottom();
			building_status[6]=1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE:
			node_building=NFC_getMenuItem(udMINERALHOLE,m_pMapScroll->getContainer());
			_createFlowNewICon(node_building->getPosition(),udNEW_MINERAL);
			_moveMapToRightBottom();
			building_status[7]=1;
			break;
		default:
			break;
	}
}

//检查建筑点击 是否上锁
bool HomeWindow::_buildingCheckOpened(int key){
	char tmp[256]="";
	switch(key){
		case udBAR:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROBAR))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2091).c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROBAR);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//酒吧   
		case udHOME:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROTECH))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2096).c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROTECH);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//神庙
		case udSHOP:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MARKET))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2093).c_str(),_LV_HOMEWINDOW_NEWSCENE_MARKET);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//神秘商人
		case udPKPLACE:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_PKPLACE))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2092).c_str(),_LV_HOMEWINDOW_NEWSCENE_PKPLACE);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//竞技场
		case udTDOOR:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TEAMPVE))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2095).c_str(),_LV_HOMEWINDOW_NEWSCENE_TEAMPVE);
				NFC_showErrorTips(tmp);
				return false;
			}
		};break;//远古遗迹
		case udTOWER:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TOWER))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2097).c_str(),_LV_HOMEWINDOW_NEWSCENE_TOWER);
				NFC_showErrorTips(tmp);
				return false;
			}
		};break;//传承之塔
		case udMINERALHOLE:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HUNT))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2094).c_str(),_LV_HOMEWINDOW_NEWSCENE_HUNT);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//矿洞
		default:
			break;
	}
}

//开启指定建筑特效
void HomeWindow::_enableBuildingEffect(int key,bool opened){
	switch(key){
		case udBAR:{
			NFC_showNode(udSE_BAR,m_pMapScroll->getContainer(),opened);
		}break;//酒吧   
		case udHOME:{
			NFC_showNode(udSE_TEMPLE_1,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_TEMPLE_2,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_TEMPLE_3,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_TEMPLE_4,m_pMapScroll->getContainer(),opened);
		}break;//神庙
		case udSHOP:{
			NFC_showNode(udSE_MARKET_1,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_MARKET_2,m_pMapScroll->getContainer(),opened);
		}break;//神秘商人
		case udPKPLACE:{
			NFC_showNode(udSE_PVP,m_pMapScroll->getContainer(),opened);
		 }break;//竞技场
		case udTDOOR:{
			NFC_showNode(udSE_TEAMPVE,m_pMapScroll->getContainer(),opened);
		 }break;//远古遗迹
		case udTOWER:{
				;
		}break;//传承之塔
		case udMINERALHOLE:{
			NFC_showNode(udSE_MINERAL,m_pMapScroll->getContainer(),opened);
		 }break;//矿洞
		default:
			break;
	}
}

//检查建筑提示
void HomeWindow::_buildingCheckHint(int key,bool opened){
	switch(key){
	case udBAR:{
		if (!opened)
		{
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROBAR);
			NFC_setLabelString(udBARTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udBARTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(193));
	}break;//酒吧   
	case udHOME:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROTECH);
			NFC_setLabelString(udHOMETXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udHOMETXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(195));
	}break;//神庙
	case udSHOP:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_MARKET);
			NFC_setLabelString(udMAKETTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udMAKETTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(196));
	}break;//神秘商人
	case udPKPLACE:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_PKPLACE);
			NFC_setLabelString(udPKPLACETXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udPKPLACETXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(197));
	 }break;//竞技场
	case udTDOOR:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_TEAMPVE);
			NFC_setLabelString(udTDOORTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udTDOORTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(198));
	 }break;//远古遗迹
	case udTOWER:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_TOWER);
			NFC_setLabelString(udTOWERTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udTOWERTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(199));
	 }break;//传承之塔
	case udMINERALHOLE:{
		if (!opened)
		{
			char tmp[128]="";
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_HUNT);
			NFC_setLabelString(udMINERALTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udMINERALTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(16));
	}break;//矿洞
	default:
		break;
	}
}

//检查建筑开启指引
void HomeWindow::_buildingCheckNewOpen(int key){
	switch(key){
		case udBAR:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_HeroBar");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR);
			}
		}break;//酒吧   
		case udHOME:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_HomeTown");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH);
			}
		}break;//神庙
		case udSHOP:{
			;
		}break;//神秘商人
		case udPKPLACE:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_2_AREANA))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_PkPlace");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_2_AREANA);
			}
		 }break;//竞技场
		case udTDOOR:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_TeamPVE");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE);
			}
		 }break;//远古遗迹
		case udTOWER:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_5_TOWER))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_Tower");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_5_TOWER);
			}
		 }break;//传承之塔
		case udMINERALHOLE:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_7_MINERAL))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkHangupItemLock_Labor");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_7_MINERAL);
			}
		 }break;//矿洞
		default:
			break;
	}
}

//检查建筑的展示状态
void HomeWindow::_buildingCheckDisplay(int key,bool opened){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(key,m_pMapScroll->getContainer());
	switch(key){
		case udBAR:{
			MaskNode* node=(MaskNode*)NFC_getNode(udBAR_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//酒吧   
		case udHOME:{
			MaskNode* node=(MaskNode*)NFC_getNode(udHOME_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		}break;//神庙
		case udSHOP:{
			MaskNode* node=(MaskNode*)NFC_getNode(udSHOP_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		}break;//神秘商人
		case udPKPLACE:{
			MaskNode* node=(MaskNode*)NFC_getNode(udPKPLACE_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//竞技场
		case udTDOOR:{
			MaskNode* node=(MaskNode*)NFC_getNode(udTDOOR_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//远古遗迹
		case udTOWER:{
			MaskNode* node=(MaskNode*)NFC_getNode(udTOWER_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//传承之塔
		case udMINERALHOLE:{
			MaskNode* node=(MaskNode*)NFC_getNode(udMINERALHOLE_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//矿洞
	default:
		break;
	}
}