//Name��HomeWindow
//Function��ʵ�ֵ�ͼ������ع���
//Written By����ǿ
//PS:ͷ�ļ�ΪHomeWindow.h

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


//��������¼�
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

//�ƹ��¼�
void HomeWindow::_barEvent(){
	if (_buildingCheckOpened(udBAR))
	{
		PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HEROBARWINDOW_);
		//���ܿ�����һ��
		GUIDESYSTEM->Next();
	}
}

//���ų���
void HomeWindow::_doorEvent(){
	MissionDataHandler::get_instance2()->setCurMissionID(MissionDataHandler::get_instance2()->getMissonInfoDataList().size());
	DOTATribeApp::get_instance2()->m_pHomeProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);
//	GUIDESYSTEM->Next();
	GUIDESYSTEM->NextBegin();
}

//�����¼�
void HomeWindow::_homeEvent(){
	if (_buildingCheckOpened(udHOME))
	{
		PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_TEMPLEWINDOW_);
		NFC_showCommunicationWating(true);
	}
}

//�������¼�
void HomeWindow::_tdoorEvent(){
	if (_buildingCheckOpened(udTDOOR))
	{
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->SetBackWindow(_TYPED_EVENT_SHOW_HOMEWINDOW_);
		DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);

		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_, _to_event_param_(IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_));
	}
}

/*
	���������¼�
*/
void HomeWindow::_shopEvent(){
	if (_buildingCheckOpened(udSHOP))
	{
		PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_);
	}
}

/*
	�������¼�
*/
void HomeWindow::_pkPlaceEvent(){	
	if (_buildingCheckOpened(udPKPLACE))
	{
		C2SArenaInfoPacket  requestArenaInfo;
		requestArenaInfo.Send();	
	} 
}
/*
	�����¼�
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
	���¼�
	*�ʹ�
*/
void HomeWindow::_mineralhole(){
	if (_buildingCheckOpened(udMINERALHOLE))
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
	}
}

	/*	
		��齨���������
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
		���ƹݽ������
	*/
void HomeWindow::_checkBuildingLock_HeroBar(){
	if(!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROBAR)){
		_buildingCheckHint(udBAR,false);
		_enableBuildingEffect(udBAR,false);
		_buildingCheckDisplay(udBAR,false);
	}else{//������ģ��
		_buildingCheckNewOpen(udBAR);
		_buildingCheckHint(udBAR,true);
		_enableBuildingEffect(udBAR,true);
		_buildingCheckDisplay(udBAR,true);
	}
}
	/*	
		�����н������
	*/
void HomeWindow::_checkBuildingLock_Market(){
	if(!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MARKET)){//����
		NFC_showNode(udREALBUSSINESSMAN,m_pMapScroll->getContainer(),false);
		_buildingCheckHint(udSHOP,false);
		_enableBuildingEffect(udSHOP,false);
		_buildingCheckDisplay(udSHOP,false);
	}else{//������ģ��
		NFC_showNode(udREALBUSSINESSMAN,m_pMapScroll->getContainer(),true);
		_buildingCheckHint(udSHOP,true);
		_enableBuildingEffect(udSHOP,true);
		_buildingCheckDisplay(udSHOP,true);
	}
}
	/*	
		��龺�����������
	*/
void HomeWindow::_checkBuildingLock_PkPlace(){
	if(!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_PKPLACE)){//������
		_buildingCheckHint(udPKPLACE,false);
		_enableBuildingEffect(udPKPLACE,false);
		_buildingCheckDisplay(udPKPLACE,false);
	}else{//������ģ��
		_buildingCheckNewOpen(udPKPLACE);
		_buildingCheckHint(udPKPLACE,true);
		_enableBuildingEffect(udPKPLACE,true);
		_buildingCheckDisplay(udPKPLACE,true);
	}
}
	/*	
		��������������
	*/
void HomeWindow::_checkBuildingLock_Tower(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TOWER))//����
	{
		_buildingCheckHint(udTOWER,false);
		_buildingCheckDisplay(udTOWER,false);
	}else{//������ģ��
		_buildingCheckNewOpen(udTOWER);
		_buildingCheckHint(udTOWER,true);
		_buildingCheckDisplay(udTOWER,true);
	}
}
	/*	
		�����Ӹ����������
	*/
void HomeWindow::_checkBuildingLock_TeamPVE(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TEAMPVE))//Զ��֮��
	{
		_buildingCheckHint(udTDOOR,false);
		_enableBuildingEffect(udTDOOR,false);
		_buildingCheckDisplay(udTDOOR,false);
	}else{//������ģ��
		_buildingCheckNewOpen(udTDOOR);
		_buildingCheckHint(udTDOOR,true);
		_enableBuildingEffect(udTDOOR,true);
		_buildingCheckDisplay(udTDOOR,true);
	}
}
	/*	
		�������������
	*/
void HomeWindow::_checkBuildingLock_HomeTown(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROTECH))//����
	{
		_buildingCheckHint(udHOME,false);
		_enableBuildingEffect(udHOME,false);
		_buildingCheckDisplay(udHOME,false);
	}else{//������ģ��
		_buildingCheckNewOpen(udHOME);
		_buildingCheckHint(udHOME,true);
		_enableBuildingEffect(udHOME,true);
		_buildingCheckDisplay(udHOME,true);
	}
}
	/*
		���󶴽������
	*/
void HomeWindow::_checkBuildingLock_Labor(){
	if (!ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HUNT))//��
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
		���������������������
	*/
void HomeWindow::_checkOtherLock(){
	_checkOtherLock_Labor();
	_checkOtherLock_GoldMine_();
}
	/*
		===������
		===�ڶ���
		===ū������
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
		===������
		===������
		===���ɼ�����
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
		����ͼ�ƶ������ұ�
	*/
void HomeWindow::_moveMapToRightBottom(){
	int second=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_HOMEMAP_MOVE_DURING);
	m_pMapScroll->setContentOffsetInDuration(ccp(-(m_pMapScroll->getContentSize().width-m_pMapScroll->getViewSize().width),0),(float)second*1.0/1000);
}
	/*
		����ͼ�ƶ��������
	*/
void HomeWindow::_moveMapToLeftTop(){
	int second=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_HOMEMAP_MOVE_DURING);
	m_pMapScroll->setContentOffsetInDuration(ccp(0,0),(float)second*1.0/1000);
}

	/*
		����new����by����
	*/
void HomeWindow::_createFlowNewICon(const CCPoint &cp,int key){
	MaskNode* node=(MaskNode*)NFC_getNode(udICON_NEW,m_pMapScroll->getContainer());
	const UIViewData &dd=node->GetViewData();
	//begin:ɾ���ɽڵ�
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
		��ʾnew������ָ������
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

//��齨����� �Ƿ�����
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
		}break;//�ư�   
		case udHOME:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HEROTECH))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2096).c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROTECH);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//����
		case udSHOP:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_MARKET))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2093).c_str(),_LV_HOMEWINDOW_NEWSCENE_MARKET);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//��������
		case udPKPLACE:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_PKPLACE))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2092).c_str(),_LV_HOMEWINDOW_NEWSCENE_PKPLACE);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//������
		case udTDOOR:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TEAMPVE))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2095).c_str(),_LV_HOMEWINDOW_NEWSCENE_TEAMPVE);
				NFC_showErrorTips(tmp);
				return false;
			}
		};break;//Զ���ż�
		case udTOWER:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_TOWER))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2097).c_str(),_LV_HOMEWINDOW_NEWSCENE_TOWER);
				NFC_showErrorTips(tmp);
				return false;
			}
		};break;//����֮��
		case udMINERALHOLE:{
			if (ROLEINFODATAHANDLER->isOpenScene(_LV_HOMEWINDOW_NEWSCENE_HUNT))
				return true;
			else{
				sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(2094).c_str(),_LV_HOMEWINDOW_NEWSCENE_HUNT);
				NFC_showErrorTips(tmp);
				return false;
			}
		}break;//��
		default:
			break;
	}
}

//����ָ��������Ч
void HomeWindow::_enableBuildingEffect(int key,bool opened){
	switch(key){
		case udBAR:{
			NFC_showNode(udSE_BAR,m_pMapScroll->getContainer(),opened);
		}break;//�ư�   
		case udHOME:{
			NFC_showNode(udSE_TEMPLE_1,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_TEMPLE_2,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_TEMPLE_3,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_TEMPLE_4,m_pMapScroll->getContainer(),opened);
		}break;//����
		case udSHOP:{
			NFC_showNode(udSE_MARKET_1,m_pMapScroll->getContainer(),opened);
			NFC_showNode(udSE_MARKET_2,m_pMapScroll->getContainer(),opened);
		}break;//��������
		case udPKPLACE:{
			NFC_showNode(udSE_PVP,m_pMapScroll->getContainer(),opened);
		 }break;//������
		case udTDOOR:{
			NFC_showNode(udSE_TEAMPVE,m_pMapScroll->getContainer(),opened);
		 }break;//Զ���ż�
		case udTOWER:{
				;
		}break;//����֮��
		case udMINERALHOLE:{
			NFC_showNode(udSE_MINERAL,m_pMapScroll->getContainer(),opened);
		 }break;//��
		default:
			break;
	}
}

//��齨����ʾ
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
	}break;//�ư�   
	case udHOME:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_HEROTECH);
			NFC_setLabelString(udHOMETXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udHOMETXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(195));
	}break;//����
	case udSHOP:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_MARKET);
			NFC_setLabelString(udMAKETTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udMAKETTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(196));
	}break;//��������
	case udPKPLACE:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_PKPLACE);
			NFC_setLabelString(udPKPLACETXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udPKPLACETXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(197));
	 }break;//������
	case udTDOOR:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_TEAMPVE);
			NFC_setLabelString(udTDOORTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udTDOORTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(198));
	 }break;//Զ���ż�
	case udTOWER:{
		if (!opened)
		{
			//set title to -> level limited
			char tmp[128];
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_TOWER);
			NFC_setLabelString(udTOWERTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udTOWERTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(199));
	 }break;//����֮��
	case udMINERALHOLE:{
		if (!opened)
		{
			char tmp[128]="";
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(619).c_str(),_LV_HOMEWINDOW_NEWSCENE_HUNT);
			NFC_setLabelString(udMINERALTXT,m_pMapScroll->getContainer(),tmp);
		}else
			NFC_setLabelString(udMINERALTXT,m_pMapScroll->getContainer(),SysLangDataManager::get_instance2()->GetSysLangById(16));
	}break;//��
	default:
		break;
	}
}

//��齨������ָ��
void HomeWindow::_buildingCheckNewOpen(int key){
	switch(key){
		case udBAR:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_HeroBar");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR);
			}
		}break;//�ư�   
		case udHOME:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_HomeTown");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH);
			}
		}break;//����
		case udSHOP:{
			;
		}break;//��������
		case udPKPLACE:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_2_AREANA))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_PkPlace");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_2_AREANA);
			}
		 }break;//������
		case udTDOOR:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_TeamPVE");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE);
			}
		 }break;//Զ���ż�
		case udTOWER:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_5_TOWER))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkBuildingLock_Tower");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_5_TOWER);
			}
		 }break;//����֮��
		case udMINERALHOLE:{
			if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_NEWFUNC_7_MINERAL))
			{
				LOGGERSYSTEM->LogInfo("HomeWindow::_checkHangupItemLock_Labor");
				GUIDESYSTEM->StartGuide4NewFunc(GuideSystem::_TYPED_NEWFUNC_7_MINERAL);
			}
		 }break;//��
		default:
			break;
	}
}

//��齨����չʾ״̬
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
		 }break;//�ư�   
		case udHOME:{
			MaskNode* node=(MaskNode*)NFC_getNode(udHOME_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		}break;//����
		case udSHOP:{
			MaskNode* node=(MaskNode*)NFC_getNode(udSHOP_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		}break;//��������
		case udPKPLACE:{
			MaskNode* node=(MaskNode*)NFC_getNode(udPKPLACE_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//������
		case udTDOOR:{
			MaskNode* node=(MaskNode*)NFC_getNode(udTDOOR_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//Զ���ż�
		case udTOWER:{
			MaskNode* node=(MaskNode*)NFC_getNode(udTOWER_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//����֮��
		case udMINERALHOLE:{
			MaskNode* node=(MaskNode*)NFC_getNode(udMINERALHOLE_FILE_NODE,m_pMapScroll->getContainer());
			const UIViewData &dd=node->GetViewData();
			if (opened)
			{
				cc->setNormalImageAndRelocation(dd.filepath_);
			}else
				cc->setNormalImageAndRelocation(dd.filepath2_);
		 }break;//��
	default:
		break;
	}
}