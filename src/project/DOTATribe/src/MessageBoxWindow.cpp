//Name：MessageBoxWindow
//Function：信息弹窗
//Written By：尹强

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/MessageBoxWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/NetSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/IProcedure.h"
#include "../include/LoginProcedure.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/InputCommand.h"
#include "../include/WindowManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/GuideSystem.h"
#include "../include/UpdateSystem.h"
#include "../include/EmailDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EmailDataHandler.h"
#include "../include/MassacreDataHandler.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


MessageBoxWindow::MessageBoxWindow()
:m_pRoot(0)
,m_nType(0)
,m_bInSingleMode(false)
,m_confirmEvent(-1)
,m_cancelEvent(-1)
{
	m_WindowType   = _TYPED_WINDOW_MESSAGEBOX_;
	m_bModelWindow = true;
}

MessageBoxWindow::~MessageBoxWindow()
{

}

bool MessageBoxWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_);
	RegisterEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_1_);
	RegisterEvent(_TYPED_EVENT_HIDE_MESSAGEBOXWINDOW_, true);

	return IWindow::Init();
}

void MessageBoxWindow::_initLayout(){
	m_pRoot= m_pRootNode;
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMESSAGEBOXWINDOW,m_pRoot);
	_mapBtn();
	_mapText();
}

void MessageBoxWindow::_mapBtn(){
	//back btn
	CCMenu* menu_back=(CCMenu*)m_pRoot->getChildByTag(udBACKBTN);
	CMenuItemSprite* cc_back=(CMenuItemSprite*)menu_back->getChildByTag(0);
	cc_back->setIDX(udBACKBTN);
	cc_back->setTarget(this,menu_selector(MessageBoxWindow::On_Click_Event));
	//ok btn
	CCMenu* menu_ok=(CCMenu*)m_pRoot->getChildByTag(udOKBTN);
	CMenuItemSprite* cc_ok=(CMenuItemSprite*)menu_ok->getChildByTag(0);
	cc_ok->setIDX(udOKBTN);
	cc_ok->setTarget(this,menu_selector(MessageBoxWindow::On_Click_Event));
}
void MessageBoxWindow::_mapText(){
	CCLabelTTF* cc=(CCLabelTTF*)m_pRoot->getChildByTag(udTEXT);
	cc->setHorizontalAlignment(kCCTextAlignmentLeft);
	cc->setVerticalAlignment(kCCVerticalTextAlignmentTop);
}

bool MessageBoxWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();

		return true;
	} 
	while (false);

	return false;
}

void MessageBoxWindow::Tick()
{
	IWindow::Tick();
}

void MessageBoxWindow::Destroy()
{
	IWindow::Destroy();

	m_bInSingleMode = false;
}

void MessageBoxWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_1_)
	{
		ShowSingleBtnMessage();

		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_MESSAGEBOXWINDOW_)
	{
		Destroy();
	}
}

void MessageBoxWindow::ShowSingleBtnMessage()
{
	CCMenu* menu_back=(CCMenu*)m_pRoot->getChildByTag(udBACKBTN);
	CMenuItemSprite* cc_back=(CMenuItemSprite*)menu_back->getChildByTag(0);
	CCMenu* menu_ok=(CCMenu*)m_pRoot->getChildByTag(udOKBTN);
	CMenuItemSprite* cc_ok=(CMenuItemSprite*)menu_ok->getChildByTag(0);

	float middle = (cc_back->getPositionX() + cc_ok->getPositionX()) / 2.0f;
	CCNode * node = m_pRoot->getChildByTag(udOKBTNTXTIMAGE);
	if(m_bInSingleMode == false)
	{
		cc_ok->setPositionX(middle);
		node->setPositionX(middle);
	}

	m_bInSingleMode = true;

	menu_back->setVisible(false);
	node = m_pRoot->getChildByTag(udBackBTNTXTIMAGE);
	node->setVisible(false);

}

/*
	paramList: 0:Title  1:Text
*/
void MessageBoxWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	Show(true);
	if (paramList.size()>=3)
	{
		std::list<std::string>::iterator it=paramList.begin();
		m_nType=atoi((*it).c_str());
		m_strTitle=*(++it);
		m_strText=*(++it);
		if(paramList.size() == 5)
		{
			m_confirmEvent = atoi((*(++it)).c_str());
			m_cancelEvent = atoi((*(++it)).c_str());
		}
	}
	NFC_setLabelString(udTEXT,m_pRoot,m_strText.c_str());
}

void MessageBoxWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{

}

void MessageBoxWindow::On_Click_Event(cocos2d::CCObject* pSender)
{
	//关闭窗口
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MESSAGEBOXWINDOW_);

	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	switch(m_nType){
		case kDEFAULT:
			break;
		case kLOGIN_UPDATEHINT:
			_handle_Login_update(cc->getIDX());
			break;
		case kLOGIN_APPSTOREHINT:
			_handle_Login_appstore(cc->getIDX());
			break;
		case kLOGIN_NOSURPOTHINT:
			_handle_Login_nosupport(cc->getIDX());
			break;
		case kNETWORKDISCONNECTED:
			_handleNetWorkDisconnect(cc->getIDX());
			break;
		case kSERVERMESSAGEPACKET:
			_handleServerMessagePacket(cc->getIDX());
			break;
		case kSELECTPURPLECARD:
			_handleSelectPurpleCard(cc->getIDX());
			break;
		case kCLIMBTOWERRESET:
			_handleTowerReset(cc->getIDX());
			break;
		case kGUIDESTART:
			_handleGuideStart(cc->getIDX());
			break;
		case kGUIDESKIP:
			_handleGuideSkip(cc->getIDX());
			break;
		case kSERVANTIDENTITYCHANGED:
			_handleServantIdentityChanged(cc->getIDX());
			break;
		case kEMAIL_REMOVE_MESSAGE:
			_handle_Email_remove(cc->getIDX());
			break;
		case kBAGSALEIMPORTANTOBJECT: 
			_handle_Sale_Important_object(cc->getIDX());
			break;
		case kTEAMBATTLE_RESETCOMFIRM:
			_handle_Reset_Team_Progress(cc->getIDX());
			break;
		case kFRIEND_DELETEFRIEND:
			_handle_Delete_Friend(cc->getIDX());
			break;
		case kCOSTJEWEL_TEAMREWARD:
			_handle_CostJewel_TeamReward(cc->getIDX());
			break;
		case kALTARQUALITYHIGH:
			_handle_Soul_Altar(cc->getIDX());
			break;
		case kUSEONEKEY_TRAIN:
			_handle_UseEquip_OneKeyTrain(cc->getIDX());
			break;
		case kEQUIPTIPSSELL:
			_handle_EquipTips_Sell(cc->getIDX());
			break;
		case kWARNINGUNLOCKATTRIBUTE:
			_handle_Unlock_EquipAttribute(cc->getIDX());
			break;
		case kDWARVEN_PAGEINFOCHANGED:
			_handle_Dwarven_PageInfoChanged(cc->getIDX());
			break;
		case kGATEWAY_CONNECTFAIL:
			_handle_GateWay_ConnectFail(cc->getIDX());
			break;
		case kMISSION_GOTONEXTMAP:
			_handle_GoTo_NextMap(cc->getIDX());
			break;
		case kMISSION_GETSTARREWARD:
			_handle_GetStarReward(cc->getIDX());
			break;	
		case kMISSION_VIPGIFTBOX:
			_handle_HasVipGift(cc->getIDX());
			break;
		case kAUTOMESSAGEBOX:
			_handle_AutoMessageBox(cc->getIDX());
			break;
		case kUPDATE_FINISH:
			_handle_update_finish(cc->getIDX());
			break;
		default:
			break;
	}
}
void MessageBoxWindow::_handle_Delete_Friend(int tag){
	if (tag==udBACKBTN)
	{
		
	}else if(tag==udOKBTN){
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_DELETE_FRIEND_);
	}
}
void MessageBoxWindow::_handle_Login_update(int tag){
	if (tag==udBACKBTN)
	{
		NFC_quitGame();
	}else if(tag==udOKBTN){
		UPDATESYSTEM->StartUpdateOnline();
	}
}
void MessageBoxWindow::_handle_Login_appstore(int tag){
	//到外壳去跳转到商店
	UPDATESYSTEM->HandleAppStoreDownload();
}
void MessageBoxWindow::_handle_Login_nosupport(int tag){
	//版本不对，服务器无法支持，退出游戏
	NFC_quitGame();
}

	/*
		处理各种类型的事件
	*/
void MessageBoxWindow::_handleNetWorkDisconnect(int tag){
	bool isReconnect=true;
	if (tag==udBACKBTN)
		isReconnect=false;
	else if(tag==udOKBTN)
		isReconnect=true;
	MassacreDataHandler::get_instance2()->MassacreCanForceClose = true;
	EMAILDATAHANDLER->GetAllStop();
	SERVERINFODATAINFO->HandleDisConnect(isReconnect);
}

void MessageBoxWindow::_handleServerMessagePacket(int tag){
	if (tag==udBACKBTN)
	{

	}else if(tag==udOKBTN){

	}
}

void MessageBoxWindow::_handleSelectPurpleCard(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_CONFIRMUSE_CONTAINPURPLECARD_);
	}
}

void MessageBoxWindow::_handleTowerReset(int tag)
{
	if(tag == udBACKBTN)
	{

	}
	else if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_TOWER_COMFIRM_RESET_);
	}
}


void MessageBoxWindow::_handleGuideStart(int tag){
	if(tag == udOKBTN){
		//用户开始新手引导
		GUIDESYSTEM->StartGuide();
	}
	else if(tag==udBACKBTN){
		//用户不想做新手引导
		GUIDESYSTEM->Finish();
		ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_GUIDE_1_);
	}
}

void MessageBoxWindow::_handleGuideSkip(int tag){
	if(tag == udOKBTN){
		GUIDESYSTEM->ToServerSkipGuide();
		GUIDESYSTEM->Finish();
	}
}

void MessageBoxWindow::_handleServantIdentityChanged(int tag)
{
	if(tag == udBACKBTN)
	{

	}
	else if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_COMFIRM_IDENTITYCHANGED_);
	}
}

void MessageBoxWindow::_handle_Email_remove(int tag){
	if (tag==udBACKBTN)
	{

	}else if(tag==udOKBTN){
		EMAILDATAHANDLER->RemoveEmail(EMAILDATAHANDLER->m_pEmailInfo->mailID_,kSYSTEM);
	}
}

void MessageBoxWindow::_handle_Sale_Important_object(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_REFRESH_BAGSALEIMPORTANTOBJECT_COMFIRM_);
	}
}

void MessageBoxWindow::_handle_Reset_Team_Progress(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_RESET_COMFIRM_TEAMBATTLEPROGRESS_);
	}
}

void MessageBoxWindow::_handle_CostJewel_TeamReward(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_CONFIRM_COSTJEWEL_TEAMREWARD_);
	}
	else if(tag == udBACKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_TEAMBATTLE_REFUSE_COSTJEWEL_TEAMREWARD_);
	}
}

void MessageBoxWindow::_handle_Soul_Altar(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_CALLBACK_ALTARWINDOW_);
	}
	else if(tag == udBACKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEALTAROVER_ALTARWINDOW_);
	}
}

void MessageBoxWindow::_handle_UseEquip_OneKeyTrain(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_CONFIRM_EQUIP_USEONEKEYTRAIN_);
	}
	else if(tag == udBACKBTN)
	{

	}
}

void MessageBoxWindow::_handle_EquipTips_Sell(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SELL_CALLBACK_EQUIPTIPSWINDOW_);
	}
	else if(tag == udBACKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);	
	}
}

void MessageBoxWindow::_handle_Unlock_EquipAttribute(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UNLOCK_EQUIPATTRIBUTELOCK_);
	}
	else if(tag == udBACKBTN)
	{

	}
}

void MessageBoxWindow::_handle_Dwarven_PageInfoChanged(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_DWARVEN_PAGEINFO_REFRESH_CONFIRM_);
	}
	else if(tag == udBACKBTN)
	{

	}
}

void MessageBoxWindow::_handle_GateWay_ConnectFail(int tag){
	if(tag == udOKBTN)
	{
		NFC_quitGame();
	}
	else if(tag == udBACKBTN)
	{

	}
}

void MessageBoxWindow::_handle_GoTo_NextMap(int tag){
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_GOTO_NEXTMISSION_);
	}
	else if(tag == udBACKBTN)
	{

	}
}
void MessageBoxWindow::_handle_GetStarReward(int tag){
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_GETSTARREWARD_);
	}
	else if(tag == udBACKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MISSIONMESSAGEBOX_);
	}
}

void MessageBoxWindow::_handle_HasVipGift(int tag)
{
	if(tag == udOKBTN)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_BACKQA_VIPGIFTWINDOW_);
	}
	else if(tag == udBACKBTN)
	{

	}
}

void MessageBoxWindow::_handle_AutoMessageBox(int tag)
{
	if(tag == udOKBTN)
	{
		if(m_confirmEvent > 0)
		{
			EVENTSYSTEM->PushEvent(m_confirmEvent);
			m_confirmEvent = -1;
		}
	}
	else if(tag == udBACKBTN)
	{
		if(m_cancelEvent > 0)
		{
			EVENTSYSTEM->PushEvent(m_cancelEvent);
			m_cancelEvent = -1;
		}
	}
}

void MessageBoxWindow::_handle_update_finish(int tag){
	NFC_quitGame();
}