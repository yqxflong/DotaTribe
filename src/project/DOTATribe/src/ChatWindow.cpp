// Name :		ChatWindow.h
// Function:	聊天窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan,shaobing

#include "../include/ChatWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/VariableSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/PlayerDataMessage.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/FriendCheckPlayerInfoPacket.h"
#include "../include/FriendAddPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/WindowManager.h"
#include "../include/ChatDataHandler.h"
#include "../include/UIViewDataManger.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/ChatPacket.h"
#include "../include/PersonalChatPacket.h"
#include "../include/TimeSystem.h"
#include "../include/MessageBoxWindow.h"
#include "cocos-ext.h"
#include <include/common/Random.h>
#include "../include/Common.h"
#include <cocos2d.h>
#include <string.h>
#include <vector>
#include <list>


using  namespace  cocos2d;
using  namespace  cocos2d::extension;
#define FontName	"ArialRoundedMTBold" //默认字体
#define SCROLLNODELAYERITEM     10
#define COOLDOWNTIME	3
#define WORLD		176
#define PERSONAL	177
#define SYSTEM		178

#define PERSONALCHAT		156
#define CHECKDATA			157
#define ADDFRIEND			158
#define TO					159
#define ME					160
#define SAY					161

#define	BG_LAYER			200
#define BG_SMALLLAYER		210
#define MaxFontNum			500
#define UpdateTime			0.5
#define CLEARTIME			120

#define	NameLengthMax		65
#define ccWHITE2	ccc3(246,237,216)

#define CellWidth	680
#define CellHeight	30

ChatWindow::ChatWindow()
{
	m_View_layer = 0;
	m_curChannel=0;
	m_CoolDownTime = 0.0f;
	m_WindowType = _TYPED_WINDOW_CHATWINDOW_;
	m_LastPerson = -1;
	m_PersonalChatInfo.m_id = -1;
	m_IsKeyBroadShow = false;
	m_SendType =_Chat_Channel_World;
	m_timeLast = 0.0f;
	m_isNeedUpdate = false;
	m_NameList.clear();
	m_NameListLabel.clear();
}

ChatWindow::~ChatWindow()
{

}

bool ChatWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_CHATWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_CLOSE_CHATWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_CHATWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_CHATVIEW_, true);

	return IWindow::Init();
}

bool ChatWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		initLayer();
		
		return true;
	} 
	while (false);

	return false;
}

void ChatWindow::Tick()
{
	m_CoolDownTime -= TIMESYSTEM->GetLastTickTime();
	m_timeLast += TIMESYSTEM->GetLastTickTime();

	if( m_isNeedUpdate){
		ChatWindowUpdate();
	}
	IWindow::Tick();
}

void ChatWindow::Destroy()
{
	m_View_layer->removeAllChildrenWithCleanup(true);
	m_View_layer->removeFromParentAndCleanup(true);
	m_NameList.clear();
	m_NameListLabel.clear();
	m_ChannelButton =NULL;
	m_PersonalLabel =NULL;
	m_WorldLabel =NULL;
	m_View_layer=NULL;
	pUpButton=NULL;
	pDownButton=NULL;
	m_IsKeyBroadShow = false;
	m_SendType =_Chat_Channel_World;
	
	IWindow::Destroy();
}

void ChatWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_CHATWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_CHATWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_CLOSE_CHATWINDOW_)
	{
		//显示小窗口
		ShowSmallWindow();
		//隐藏大窗口
		HideBigWindow();
		//更新聊天信息，并刷新
		UpdataShowChatData();
		_refreshTableView(m_View_layer);
		UpdateLastChatInfo();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_CHATVIEW_)
	{
		m_isNeedUpdate = true;
	}
}

void ChatWindow::ChatWindowUpdate(){
	if (m_timeLast > UpdateTime)
	{
		// 大窗口显示时更新大窗口信息
		if (m_View_layer->isVisible())
		{
			UpdataShowChatData();
			_refreshTableView(m_View_layer);
		}
		// 小窗口显示时更新小窗口信息
		if (m_ChatMultiLineLabel_1->isVisible() && m_ChatMultiLineLabel_2->isVisible())
			UpdateLastChatInfo();
		m_timeLast = 0.0f;
		m_isNeedUpdate = false;
	}
}
void ChatWindow::ShowControl(int id){
	CCNode *p = NFC_getNode(id, m_pRootNode);
	if(p != NULL)
		p->setVisible(true);
}

void ChatWindow::HideControl(int id){
	CCNode *p = NFC_getNode(id, m_pRootNode);
	if(p != NULL)
		p->setVisible(false);

}
void ChatWindow::_mapBtn(){
	// _Chat_WorldLabel, _Chat_PersonalLabel
	CCMenu* tabmenu = (CCMenu*)NFC_getNode(_Chat_WorldLabel_, m_pRootNode);
	CMenuItemSprite* item = (CMenuItemSprite*)tabmenu->getChildByTag(0);
	item->setTag(_Chat_WorldLabel_);
	m_WorldLabel = item;
	tabmenu = (CCMenu*)NFC_getNode(_Chat_PersonalLabel_, m_pRootNode);
	item = (CMenuItemSprite*)tabmenu->getChildByTag(0);
	item->setTag(_Chat_PersonalLabel_);
	m_PersonalLabel = item;
	m_WorldLabel->setTarget(this, menu_selector(ChatWindow::On_Change_Label));
	m_PersonalLabel->setTarget(this, menu_selector(ChatWindow::On_Change_Label));
	//关闭
	CCMenu* menu = (CCMenu*)NFC_getNode(_Chat_Close_, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_Close_);
	item->setTarget(this, menu_selector(ChatWindow::On_CloseBig));
	//发送
	menu = (CCMenu*)NFC_getNode(_Chat_SendButton_, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_SendButton_);
	item->setTarget(this, menu_selector(ChatWindow::On_SendMessage));
	
	//ChannelSelect Button
	menu = (CCMenu*)NFC_getNode(_Chat_ChannelButton_, m_pRootNode);
	CLabelButtonItem* _item = (CLabelButtonItem*)menu->getChildByTag(0);
	_item->setTag(_Chat_ChannelButton_);
	_item->setTarget(this, menu_selector(ChatWindow::On_Show_ChannelList));
	m_ChannelButton = _item;

	
	//Input channel World
	menu = (CCMenu*)NFC_getNode(_Chat_ChannelButton_World_, m_pRootNode);
	_item = (CLabelButtonItem*)menu->getChildByTag(0);
	_item->setTag(_Chat_ChannelButton_World_);
	_item->setTarget(this, menu_selector(ChatWindow::On_Close_ChannelList));
	m_ChannelButton_world = _item;

	//Input channel Personal	
	menu = (CCMenu*)NFC_getNode(_Chat_ChannelButton_Personal_, m_pRootNode);
	_item = (CLabelButtonItem*)menu->getChildByTag(0);
	_item->setTag(_Chat_ChannelButton_Personal_);
	_item->setTarget(this, menu_selector(ChatWindow::On_Close_ChannelList));
	m_ChannelButton_personal = _item;
	//Show Name List
	menu = (CCMenu*)NFC_getNode(_Chat_NameListButton_, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_NameListButton_);
	item->setTarget(this, menu_selector(ChatWindow::On_Show_NameList));
	pUpButton = item;
	//Hide Name List
	menu = (CCMenu*)NFC_getNode(_Chat_NameListButtonClose_, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_NameListButtonClose_);
	item->setTarget(this, menu_selector(ChatWindow::On_Close_NameList));
	pDownButton = item;

	MaskNode* pData = (MaskNode*)NFC_getNode(_Chat_NameList_Data_, m_pRootNode);
	//NameList Item1
	menu = (CCMenu*)NFC_getNode(_Chat_NameList_Item1, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_NameList_Item1);
	item->setTarget(this, menu_selector(ChatWindow::On_SetName));
	CCScale9Sprite* image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setNormalImage(image);
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath2_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setSelectedImage(image);
	m_NameList.push_back(item);
	// NameList Label1
	CCLabelTTF* label = (CCLabelTTF*)NFC_getNode(_Chat_NameList_Label1, m_pRootNode);
	m_NameListLabel.push_back(label);
	// NameList Item2
	menu = (CCMenu*)NFC_getNode(_Chat_NameList_Item2, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_NameList_Item2);
	item->setTarget(this, menu_selector(ChatWindow::On_SetName));
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setNormalImage(image);
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath2_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setSelectedImage(image);
	m_NameList.push_back(item);
	// NameList Label2
	label = (CCLabelTTF*)NFC_getNode(_Chat_NameList_Label2, m_pRootNode);
	m_NameListLabel.push_back(label);
	// NameList Item3
	menu = (CCMenu*)NFC_getNode(_Chat_NameList_Item3, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_NameList_Item3);
	item->setTarget(this, menu_selector(ChatWindow::On_SetName));
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setNormalImage(image);
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath2_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setSelectedImage(image);
	m_NameList.push_back(item);
	// NameList Label3
	label = (CCLabelTTF*)NFC_getNode(_Chat_NameList_Label3, m_pRootNode);
	m_NameListLabel.push_back(label);
	// NameList Item4
	menu = (CCMenu*)NFC_getNode(_Chat_NameList_Item4, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_NameList_Item4);
	item->setTarget(this, menu_selector(ChatWindow::On_SetName));
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setNormalImage(image);
	image = CCScale9Sprite::create();
	image->setProperty("File",pData->GetViewPData()->filepath2_);
	image->setContentSize(CCSizeMake(pData->GetViewPData()->width_, pData->GetViewPData()->height_));
	item->setSelectedImage(image);
	m_NameList.push_back(_item);
	// NameList Label4
	label = (CCLabelTTF*)NFC_getNode(_Chat_NameList_Label4, m_pRootNode);
	m_NameListLabel.push_back(label);
	// 小窗口->大窗口 按钮
	menu = (CCMenu*)NFC_getNode(_Chat_Small_Button, m_pRootNode);
	item = (CMenuItemSprite*)menu->getChildByTag(0);
	item->setTag(_Chat_Small_Button);
	item->setTarget(this, menu_selector(ChatWindow::On_ShowBig));
	m_pSmall = item;
}

void ChatWindow::_mapOthers(){
	// BG
	m_pBG = (CCSprite*)NFC_getNode(_Chat_BG_, m_pRootNode);
	// 大遮罩层，全屏
	m_BGLayer= (CPriorityLayerColor*)NFC_getNode(_Chat_BGLayer_Big_, m_pRootNode); 
	m_BGLayer->setPosition(CCPointZero);
	m_BGLayer->setDelegate(this);
	m_BGLayer->setVisible(false);

	// 小遮罩层，BG大小
	m_BGSmallLayer = (CPriorityLayerColor*)NFC_getNode(_Chat_BGLayer_Small_, m_pRootNode);
	m_BGSmallLayer->setContentSize(m_pBG->getContentSize());
	m_BGSmallLayer->setDelegate(this);
	m_BGSmallLayer->setVisible(false);

	// TabView
	m_View_layer = (CTableView *)NFC_getNode(_Chat_Cell_, m_pRootNode);
	m_View_layer->setDataSource(this);
	m_View_layer->setDelegate(this);
	m_View_layer->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_View_layer->setTouchEnabled(true);
	m_View_layer->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	// _Chat_TextInput_
	pTextInputBox = (CCEditBox*)NFC_getNode(_Chat_TextInput_, m_pRootNode);
	pTextInputBox->setDelegate(this);
	pTextInputBox->setMaxLength(65);
	pTextInputBox->setInputMode(kEditBoxInputModeSingleLine);
	pTextInputBox->setReturnType(kKeyboardReturnTypeDone);
	// _Chat_NameInput_
	pNameInputBox = (CCEditBox*)NFC_getNode(_Chat_NameInput_, m_pRootNode);
	pNameInputBox->setDelegate(this);
	pNameInputBox->setMaxLength(10);
	pNameInputBox->setInputMode(kEditBoxInputModeSingleLine);
	pNameInputBox->setReturnType(kKeyboardReturnTypeDone);
	// _Chat_NameInputPersonal_
	pTextInputBoxPersonal = (CCEditBox*)NFC_getNode(_Chat_TextInputPersonal_, m_pRootNode);
	pTextInputBoxPersonal->setDelegate(this);
	pTextInputBoxPersonal->setMaxLength(65);
	pTextInputBoxPersonal->setInputMode(kEditBoxInputModeSingleLine);
	pTextInputBoxPersonal->setReturnType(kKeyboardReturnTypeDone);
	// 小窗口CCNode
	m_pSmall = (CCSprite*)NFC_getNode(_Chat_Small_BG, m_pRootNode);
	m_ChatMultiLineLabel_1 = (CCLabelTTF*)NFC_getNode(_Chat_Small_Label, m_pRootNode);
	m_ChatMultiLineLabel_2 = (CCLabelTTF*)NFC_getNode(_Chat_Small_Label2, m_pRootNode);
	// 弹出窗口CCNode
	m_PopWindow = (CCNode*)NFC_getNode(_Chat_PopWindow_, m_pRootNode);

}

void ChatWindow::_createPopWindow(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCHAT_POP_,m_PopWindow);

	MaskNode *btnData = (MaskNode*)NFC_getNode(_Chat_EventList_Data_Button,m_PopWindow);
	float btnwidth = btnData->GetViewPData()->width_;
	float btnheight = btnData->GetViewPData()->height_;
	// Add Friend	
	CCMenu* pMenu = (CCMenu*)NFC_getNode(_Chat_EventList_Item1,m_PopWindow);
	CLabelButtonItem* item = (CLabelButtonItem*)pMenu->getChildByTag(0);
	item->setTarget(this, menu_selector(ChatWindow::On_SetEvent_SetName));
	CCScale9Sprite* normalImage = CCScale9Sprite::create();
	normalImage->setProperty("File", btnData->GetViewPData()->filepath_);
	normalImage->setContentSize(CCSizeMake(btnwidth, btnheight));
	CCScale9Sprite* selectImage = CCScale9Sprite::create();
	selectImage->setProperty("File", btnData->GetViewPData()->filepath2_);
	selectImage->setContentSize(CCSizeMake(btnwidth, btnheight));
	item->setNormalImage(normalImage);
	item->setSelectedImage(selectImage);
	
	// Check Data
	pMenu = (CCMenu*)NFC_getNode(_Chat_EventList_Item2,m_PopWindow);
	item = (CLabelButtonItem*)pMenu->getChildByTag(0);
	item->setTarget(this, menu_selector(ChatWindow::On_SetEvent_CheckData));
	normalImage = CCScale9Sprite::create();
	normalImage->setProperty("File", btnData->GetViewPData()->filepath_);
	normalImage->setContentSize(CCSizeMake(btnwidth, btnheight));
	selectImage = CCScale9Sprite::create();
	selectImage->setProperty("File", btnData->GetViewPData()->filepath2_);
	selectImage->setContentSize(CCSizeMake(btnwidth, btnheight));
	item->setNormalImage(normalImage);
	item->setSelectedImage(selectImage);
	// Talk Personal	
	pMenu = (CCMenu*)NFC_getNode(_Chat_EventList_Item3,m_PopWindow);
	item = (CLabelButtonItem*)pMenu->getChildByTag(0);
	item->setTarget(this, menu_selector(ChatWindow::On_SetEvent_AddFriend));
	normalImage = CCScale9Sprite::create();
	normalImage->setProperty("File", btnData->GetViewPData()->filepath_);
	normalImage->setContentSize(CCSizeMake(btnwidth, btnheight));
	selectImage = CCScale9Sprite::create();
	selectImage->setProperty("File", btnData->GetViewPData()->filepath2_);
	selectImage->setContentSize(CCSizeMake(btnwidth, btnheight));
	item->setNormalImage(normalImage);
	item->setSelectedImage(selectImage);



}

void ChatWindow::ShowPopWindow(CCPoint pos){
	if( m_PopWindow == NULL)
		_createPopWindow();
	m_PopWindow->setVisible(true);
	m_PopWindow->setPosition(pos);
}

void ChatWindow::HidePopWindow(){
	if( m_PopWindow == NULL)
		_createPopWindow();
	m_PopWindow->setVisible(false);
}

void ChatWindow::initLayer()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCHAT, m_pRootNode);
	m_NameList.clear();
	m_NameListLabel.clear();

	_mapBtn();
	_mapOthers();
	
	_createPopWindow();	

	// 初始化，当前频道与聊天频道都是世界频道 
	m_WorldLabel->selected(true);
	m_PersonalLabel->unselected();
	m_curChannel = _Chat_Channel_World;
	m_SendType = _Chat_Channel_World;
	UpdataShowChatData();
	_refreshTableView(m_View_layer);
	UpdateLastChatInfo();
}

void ChatWindow::On_Change_Label(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* pItem = (CMenuItemSprite*)pSender;
	if (pItem->getTag() == _Chat_WorldLabel_ && m_curChannel != _Chat_Channel_World)
	{
		m_WorldLabel->selected(true);
		m_PersonalLabel->unselected();
		m_curChannel = _Chat_Channel_World;
		
		UpdataShowChatData();
		_refreshTableView(m_View_layer);
		UpdateLastChatInfo();
	}
	else if (pItem->getTag() == _Chat_PersonalLabel_ && m_curChannel != _Chat_Channel_Personal)
	{
		m_WorldLabel->unselected();
		m_PersonalLabel->selected(true);
		m_curChannel = _Chat_Channel_Personal;
		UpdataShowChatData();
		_refreshTableView(m_View_layer);
		UpdateLastChatInfo();
	}

	int a = ChatDataHandler::get_instance2()->World_Show_Chat_List.size();
	int b = ChatDataHandler::get_instance2()->Personal_Show_Chat_List.size();
	CCLOG("Channel %d size: %d. Channel %d size: %d",_Chat_Channel_World,a,_Chat_Channel_Personal,b);

	CCLOG("Change Channel to %d", m_curChannel);
}
void ChatWindow::ShowNameList(){
	ShowControl(_Chat_NameList_Line1);
	ShowControl(_Chat_NameList_Line2);
	ShowControl(_Chat_NameList_Line3);
	ShowControl(_Chat_NameList_Item1);
	ShowControl(_Chat_NameList_Item2);
	ShowControl(_Chat_NameList_Item3);
	ShowControl(_Chat_NameList_Item4);
	ShowControl(_Chat_NameList_Label1);
	ShowControl(_Chat_NameList_Label2);
	ShowControl(_Chat_NameList_Label3);
	ShowControl(_Chat_NameList_Label4);
	ShowControl(_Chat_NameListBG);

	ShowControl(_Chat_NameListButtonClose_);
	HideControl(_Chat_NameListButton_);
}

void ChatWindow::HideNameList(){
	HideControl(_Chat_NameList_Line1);
	HideControl(_Chat_NameList_Line2);
	HideControl(_Chat_NameList_Line3);
	HideControl(_Chat_NameList_Item1);
	HideControl(_Chat_NameList_Item2);
	HideControl(_Chat_NameList_Item3);
	HideControl(_Chat_NameList_Item4);
	HideControl(_Chat_NameList_Label1);
	HideControl(_Chat_NameList_Label2);
	HideControl(_Chat_NameList_Label3);
	HideControl(_Chat_NameList_Label4);
	HideControl(_Chat_NameListBG);

	HideControl(_Chat_NameListButtonClose_);
	if( m_SendType == _Chat_Channel_Personal)
		ShowControl(_Chat_NameListButton_);
	else
		HideControl(_Chat_NameListButton_);
}

void ChatWindow::ShowChannelList(){
	HideControl(_Chat_ChannelButton_);
	ShowControl(_Chat_ChannelButton_World_);
	ShowControl(_Chat_ChannelButton_Personal_);
}

void ChatWindow::HideChannelList(){
	ShowControl(_Chat_ChannelButton_);
	HideControl(_Chat_ChannelButton_World_);
	HideControl(_Chat_ChannelButton_Personal_);
}

void ChatWindow::On_Show_NameList(cocos2d::CCObject* pSender)
{
	CCLOG("On_Show_NameList!");
	UpdateNameList();

	ShowNameList();

}

void ChatWindow::On_Close_NameList(cocos2d::CCObject* pSender)
{
	HideNameList();
	
}

void ChatWindow::On_SetName(cocos2d::CCObject* pSender)
{
	CCLOG("Tag%d",((CLabelButtonItem*)pSender)->getTag());
	int Tag = ((CLabelButtonItem*)pSender)->getTag() - _Chat_NameList_Item1;
	if ( (int)ChatDataHandler::get_instance2()->PlayerInfoList.size()>Tag)
	{

		m_PersonalChatInfo = *(ChatDataHandler::get_instance2()->PlayerInfoList[ChatDataHandler::get_instance2()->PlayerInfoList.size()-(1+Tag)]);
		std::string name = ChatDataHandler::get_instance2()->PlayerInfoList[ChatDataHandler::get_instance2()->PlayerInfoList.size()-(1+Tag)]->m_name;
		pNameInputBox->setText(name.c_str());

	}
	HideNameList();

}

void ChatWindow::On_SetEvent_SetName(cocos2d::CCObject* pSender)
{
	if (m_LastPerson != -1)
	{
		if( m_selectData.m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_ )
		{
			m_PersonalChatInfo.m_id = m_selectData.m_receivePlayerID;
			m_PersonalChatInfo.m_name = m_selectData.m_receivePlayerName;
		}
		else
		{
			m_PersonalChatInfo.m_id = m_selectData.m_sendPlayerID;
			m_PersonalChatInfo.m_name = m_selectData.m_sendPlayerName;
		}
	}

	if (m_PersonalChatInfo.m_id != -1)
	{
		std::string name =m_PersonalChatInfo.m_name;
		if( m_SendType == _Chat_Channel_Personal){
			pNameInputBox->setText(name.c_str());
			pTextInputBoxPersonal->setText("");
		}
		else if( m_SendType == _Chat_Channel_World){
			ShowPersonalInputWindow();
			CCPoint a,b;
			a = m_ChannelButton_world->getPosition();
			b = m_ChannelButton_personal->getPosition();
			m_ChannelButton_world->setPosition(b);
			m_ChannelButton_personal->setPosition(a);
			m_SendType = _Chat_Channel_Personal;
			pNameInputBox->setText(name.c_str());
		
			pTextInputBoxPersonal->setText(	pTextInputBox->getText() );
			pTextInputBox->setText("");
		}


	}
	m_PopWindow->setVisible(false);

}

void ChatWindow::On_SetEvent_CheckData(cocos2d::CCObject* pSender)
{
	int id = -1;
	if (m_LastPerson != -1)
	{
		if( m_selectData.m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_ )
			id = m_selectData.m_receivePlayerID;
		else
			id = m_selectData.m_sendPlayerID;
	}

	if (id != -1)
	{
		FriendDataHandler::get_instance2()->ToServerCheckPlayerInfo(id, _TYPED_WINDOW_CHATWINDOW_);
		m_PopWindow->setVisible(false);
	}
	
}

void ChatWindow::On_SetEvent_AddFriend(cocos2d::CCObject* pSender)
{
	CCLOG("AddFriend");
	int id = -1;
	if (m_LastPerson != -1)
	{
		if( m_selectData.m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_ )
			id = m_selectData.m_receivePlayerID;
		else
			id = m_selectData.m_sendPlayerID;
	}

	if (id != -1)
	{
		C2SFriendAddPacket pack(id);
		pack.Send();
		m_PopWindow->setVisible(false);
	}

}

void ChatWindow::On_SelectName(cocos2d::CCObject* pSender)
{
	CCLOG("OnSelectName");
	CMenuItemSprite* pItem = (CMenuItemSprite*)pSender;
	CCLOG("Cell Index: %d",pItem->getParent()->getTag());
	CCLOG("Cell Index: %d",pItem->getTag());
	CCLOG("Cell Index: %d",pItem->getParent()->getParent()->getTag());
	int index = pItem->getIDX();


	ShowChatData* tempData = NULL;

	CCLOG("CurrentChannel: %d",m_curChannel);

	int a = ChatDataHandler::get_instance2()->World_Show_Chat_List.size();
	int b = ChatDataHandler::get_instance2()->Personal_Show_Chat_List.size();
	CCLOG("Channel %d size: %d. Channel %d size: %d",_Chat_Channel_World,a,_Chat_Channel_Personal,b);

	if (m_curChannel == _Chat_Channel_World)
	{
		//if(pItem->getParent()->getParent()->getTag() < ChatDataHandler::get_instance2()->World_Show_Chat_List.size())
		//	tempData = ChatDataHandler::get_instance2()->World_Show_Chat_List[pItem->getParent()->getParent()->getTag()];
		tempData = ChatDataHandler::get_instance2()->World_Show_Chat_List[index];
		//else
		//	return;
	}
	else if(m_curChannel == _Chat_Channel_Personal)
	{
		//if(pItem->getParent()->getParent()->getTag() < ChatDataHandler::get_instance2()->Personal_Show_Chat_List.size())
		tempData = ChatDataHandler::get_instance2()->Personal_Show_Chat_List[index];
		//else
		//	return;
	}
	

	setChatData(m_selectData,tempData);
	CCLOG("SendPlayer: %d",m_selectData.m_sendPlayerID);
	CCLOG("ReceivePlayer: %d",m_selectData.m_receivePlayerID);
	CCLOG("%d",RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_);
	if (m_selectData.m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_ &&
		m_selectData.m_sendPlayerID == m_selectData.m_receivePlayerID)
	{
			return;
	}
	m_LastPerson = pItem->getParent()->getParent()->getTag();
	CCPoint pos = ccp(pItem->getPositionX() + pItem->getParent()->getPositionX() + pItem->getParent()->getParent()->getPositionX() + pItem->getParent()->getParent()->getParent()->getPositionX()
		, pItem->getPositionY() + pItem->getParent()->getPositionY() + pItem->getParent()->getParent()->getPositionY() + pItem->getParent()->getParent()->getParent()->getPositionY());
	CCLOG("%f", pItem->getPositionY());
	CCLOG("%f", pItem->getParent()->getPositionY());
	CCLOG("%f", pItem->getParent()->getParent()->getPositionY());
	CCLOG("%f", pItem->getParent()->getParent()->getParent()->getPositionY());
	CCLOG("%f %f", pos.x, pos.y);
	m_PopWindow->setVisible(true);
	m_PopWindow->setPosition(pos);
	CCLOG("On Select Name Done");
}

void ChatWindow::On_Close_ChannelList(cocos2d::CCObject* pSender)
{
	int Tag = ((CMenuItemSprite*)pSender)->getTag();
	CCPoint a,b;
	HideChannelList();
	switch(Tag){
	case _Chat_ChannelButton_World_:
		ShowWorldInputWindow();

		if( m_SendType == _Chat_Channel_Personal){
		m_SendType = _Chat_Channel_World;
		a = m_ChannelButton_world->getPosition();
		b = m_ChannelButton_personal->getPosition();
		m_ChannelButton_world->setPosition(b);
		m_ChannelButton_personal->setPosition(a);
		pTextInputBox->setText(pTextInputBoxPersonal->getText());
		pTextInputBoxPersonal->setText("");
		}
		break;
	case _Chat_ChannelButton_Personal_:
		ShowPersonalInputWindow();

		if( m_SendType == _Chat_Channel_World){
		m_SendType = _Chat_Channel_Personal;
		a = m_ChannelButton_world->getPosition();
		b = m_ChannelButton_personal->getPosition();
		m_ChannelButton_world->setPosition(b);
		m_ChannelButton_personal->setPosition(a);
		pTextInputBoxPersonal->setText(pTextInputBox->getText());
		pTextInputBox->setText("");
		}
		break;
	}

}

void ChatWindow::On_Show_ChannelList(cocos2d::CCObject* pSender)
{
	ShowChannelList();
}

void ChatWindow::HideInputWindow(){
	HideControl(_Chat_TextInputPersonal_);
	HideControl(_Chat_TextInput_);
	HideControl(_Chat_ChannelButton_Personal_);
	HideControl(_Chat_NameInput_);
	HideControl(_Chat_NameListButton_);
	HideControl(_Chat_NameListButtonClose_);
	HideControl(_Chat_NameListBG);
	HideControl(_Chat_NameList_Line1);
	HideControl(_Chat_NameList_Line2);
	HideControl(_Chat_NameList_Line3);
	HideControl(_Chat_NameList_Item1);
	HideControl(_Chat_NameList_Item2);
	HideControl(_Chat_NameList_Item3);
	HideControl(_Chat_NameList_Item4);
	HideControl(_Chat_NameList_Label1);
	HideControl(_Chat_NameList_Label2);
	HideControl(_Chat_NameList_Label3);
	HideControl(_Chat_NameList_Label4);

	HideControl(_Chat_ChannelButton_World_);
	HideControl(_Chat_ChannelButton_);
}

void ChatWindow::ShowPersonalInputWindow(){
	ShowControl(_Chat_ChannelButton_);
	m_ChannelButton->SetLabelString(SysLangDataManager::get_instance2()->GetSysLangById(168).c_str());
	

	ShowControl(_Chat_TextInputPersonal_);
	HideControl(_Chat_TextInput_);
	HideControl(_Chat_ChannelButton_Personal_);
	ShowControl(_Chat_NameInput_);
	ShowControl(_Chat_NameListButton_);
	HideControl(_Chat_NameListButtonClose_);
	HideControl(_Chat_NameListBG);
	HideControl(_Chat_NameList_Line1);
	HideControl(_Chat_NameList_Line2);
	HideControl(_Chat_NameList_Line3);
	HideControl(_Chat_NameList_Item1);
	HideControl(_Chat_NameList_Item2);
	HideControl(_Chat_NameList_Item3);
	HideControl(_Chat_NameList_Item4);
	HideControl(_Chat_NameList_Label1);
	HideControl(_Chat_NameList_Label2);
	HideControl(_Chat_NameList_Label3);
	HideControl(_Chat_NameList_Label4);

	HideControl(_Chat_ChannelButton_World_);
}

void ChatWindow::ShowWorldInputWindow(){
	ShowControl(_Chat_ChannelButton_);
	m_ChannelButton->SetLabelString(SysLangDataManager::get_instance2()->GetSysLangById(167).c_str());
	HideControl(_Chat_ChannelButton_World_);

	HideControl(_Chat_ChannelButton_Personal_);

	ShowControl(_Chat_TextInput_);
	HideControl(_Chat_TextInputPersonal_);
	HideControl(_Chat_NameInput_);
	HideControl(_Chat_NameListButton_);
	HideControl(_Chat_NameListButtonClose_);
	HideControl(_Chat_NameListBG);
	HideControl(_Chat_NameList_Line1);
	HideControl(_Chat_NameList_Line2);
	HideControl(_Chat_NameList_Line3);
	HideControl(_Chat_NameList_Item1);
	HideControl(_Chat_NameList_Item2);
	HideControl(_Chat_NameList_Item3);
	HideControl(_Chat_NameList_Item4);
	HideControl(_Chat_NameList_Label1);
	HideControl(_Chat_NameList_Label2);
	HideControl(_Chat_NameList_Label3);
	HideControl(_Chat_NameList_Label4);

}

void ChatWindow::ShowBigWindow(){
	m_BGLayer->setVisible(true);
	m_BGSmallLayer->setVisible(true);
	ShowControl(_Chat_BG_);
	ShowControl(_Chat_WorldLabel_);
	ShowControl(_Chat_PersonalLabel_);
	ShowControl(_Chat_WorldLabelImage_);
	ShowControl(_Chat_PersonalLabelImage_);
	ShowControl(_Chat_Close_);
	ShowControl(_Chat_SendButton_);
	ShowControl(_Chat_SendButtonImage_);
	ShowControl(_Chat_Cell_);
	

	if(m_SendType == _Chat_Channel_World ){
		ShowWorldInputWindow();
	}
	else if(m_SendType == _Chat_Channel_Personal){
		ShowPersonalInputWindow();
	}
	pTextInputBox->setText("");
	pTextInputBoxPersonal->setText("");
}
void ChatWindow::HideBigWindow(){
	m_BGLayer->setVisible(false);
	m_BGSmallLayer->setVisible(false);
	HideControl(_Chat_BG_);
	HideControl(_Chat_WorldLabel_);
	HideControl(_Chat_PersonalLabel_);
	HideControl(_Chat_WorldLabelImage_);
	HideControl(_Chat_PersonalLabelImage_);
	HideControl(_Chat_Close_);
	HideControl(_Chat_SendButton_);
	HideControl(_Chat_SendButtonImage_);
	HideControl(_Chat_Cell_);

	HideInputWindow();
	
	pTextInputBox->setText("");
	pTextInputBoxPersonal->setText("");
}

void ChatWindow::ShowSmallWindow(){
	ShowControl(_Chat_Small_Label);
	ShowControl(_Chat_Small_Label2);
	ShowControl(_Chat_Small_BG);
	ShowControl(_Chat_Small_Button);
}
void ChatWindow::HideSmallWindow(){
	HideControl(_Chat_Small_Label);
	HideControl(_Chat_Small_Label2);
	HideControl(_Chat_Small_BG);
	HideControl(_Chat_Small_Button);
}
void ChatWindow::On_ShowBig(cocos2d::CCObject* pSender)
{
	HideSmallWindow();
	ShowBigWindow();
	UpdataShowChatData();
	_refreshTableView(m_View_layer);
	UpdateLastChatInfo();
}

void ChatWindow::On_CloseBig(cocos2d::CCObject* pSender)
{
	ShowSmallWindow();

	HideBigWindow();
	m_PopWindow->setVisible(false);
	UpdataShowChatData();
	_refreshTableView(m_View_layer);
	UpdateLastChatInfo();
}

void ChatWindow::On_SendMessage(cocos2d::CCObject* pSender)
{
	CCLOG("Send Message.");
	switch(m_SendType)
	{
	case _Chat_Channel_World:
		{
			std::string msg =pTextInputBox->getText();
			if (msg!="")
			{
				if (m_CoolDownTime >0)
				{
					std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(607);
					NFC_showErrorTips_2(str2);
				}
				else
				{
					std::string temp = checkText(msg);
					if (temp != "")
					{
						C2SChatPacket packet(_Chat_Channel_World,-1,temp);
						packet.Send();
						pTextInputBox->setText("");
						m_CoolDownTime = COOLDOWNTIME;
					}
				}
			}
			else
			{
				std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(610);
				NFC_showMessageBox(kDEFAULT,str2);
			}
			break;
		}
	case _Chat_Channel_Personal:
		{
			std::string tempName =pNameInputBox->getText();
			std::string msg =pTextInputBoxPersonal->getText();
			if (tempName !="" && msg !="")
			{
				if (m_PersonalChatInfo.m_id != RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_ && tempName != RoleInfoDataHandler::get_instance2()->m_pRIData->name_)
				{
					if (m_PersonalChatInfo.m_id != -1&& m_PersonalChatInfo.m_name == tempName)
					{
						std::string temp = checkText(msg);
						if (temp != "")
						{
							C2SChatPacket packet(_Chat_Channel_Personal,m_PersonalChatInfo.m_id,temp);
							packet.Send();
							pTextInputBoxPersonal->setText("");
						}
					}
					else
					{
						std::string temp = checkText(msg);
						if (temp != "")
						{
							C2SPersonalChatPacket packet(pNameInputBox->getText(),temp);
							packet.Send();
							pTextInputBoxPersonal->setText("");
						}
					}
				}
				else
				{
					std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(608);
					NFC_showMessageBox(kDEFAULT,str2);
				}
			}
			else
			{
				std::string str2;
				if (tempName == "")
					str2=SysLangDataManager::get_instance2()->GetSysLangById(609);
				else
					str2=SysLangDataManager::get_instance2()->GetSysLangById(610);
				NFC_showMessageBox(kDEFAULT,str2);
			}
			break;
		}
	default:
		break;
	}


}

void ChatWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}



void ChatWindow::UpdateNameList()
{
	for (int i=0;i<(int)m_NameList.size();i++)
	{
		CMenuItemSprite* pName = m_NameList[i];
		CCLabelTTF* pLabel = m_NameListLabel[i];
		if ( (int)ChatDataHandler::get_instance2()->PlayerInfoList.size()>i)
		{
			std::string name = ChatDataHandler::get_instance2()->PlayerInfoList[ChatDataHandler::get_instance2()->PlayerInfoList.size()-(i+1)]->m_name;
			pLabel->setString(name.c_str());
		}
	}
}

void ChatWindow::UpdataShowChatData()
{
	CCLOG("---------------------------Updata Beging!----------------------------");
	MaskNode *pMaskNode = (MaskNode*)NFC_getNode(_Chat_TalkLine_Data_, m_pRootNode);
	std::string fontName = FontStyleDataManager::get_instance2()->getDataByID(pMaskNode->GetViewPData()->m_nFontStyleID)->fontname_;
	float fontSize = FontStyleDataManager::get_instance2()->getDataByID(pMaskNode->GetViewPData()->m_nFontStyleID)->fontsize_;
	float tabView_Width = pMaskNode->GetViewPData()->width_;
	if (m_curChannel == _Chat_Channel_World)
	{
		std::vector<ChatData*>::iterator itor= ChatDataHandler::get_instance2()->World_Chat_List.begin();
		std::vector<ChatData*>::iterator itor_end= ChatDataHandler::get_instance2()->World_Chat_List.end();
		for (;itor!=itor_end;++itor)
		{
			ChatData* pData = *(itor);
			if(pData)
			{
				ChatDataHandler::get_instance2()->UpdateChatData(_Chat_Channel_World,pData,false, tabView_Width,fontName,fontSize);
				CCLOG("%s say to %s: %s", pData->m_sendPlayerName.c_str(), pData->m_receivePlayerName.c_str(),pData->m_text.c_str());
			}
		}

		std::vector<ChatData*>::iterator iter1 = ChatDataHandler::get_instance2()->World_Chat_List.begin();
		std::vector<ChatData*>::iterator iter1_end = ChatDataHandler::get_instance2()->World_Chat_List.end();
		for (;iter1!=iter1_end;++iter1)
		{
			delete (*iter1);
		}
		ChatDataHandler::get_instance2()->World_Chat_List.clear();
	}
	else if(m_curChannel == _Chat_Channel_Personal)
	{

		std::vector<ChatData*>::iterator itor= ChatDataHandler::get_instance2()->Personal_Chat_List.begin();
		std::vector<ChatData*>::iterator itor_end= ChatDataHandler::get_instance2()->Personal_Chat_List.end();
	
		for (;itor!=itor_end;++itor)
		{	
			ChatData* pData = *(itor);
			if(pData)
			{
				ChatDataHandler::get_instance2()->UpdateChatData(pData->m_Type,pData,false,tabView_Width,fontName,fontSize); 
				CCLOG("%s say to %s: %s", pData->m_sendPlayerName.c_str(), pData->m_receivePlayerName.c_str(),pData->m_text.c_str());
			}
		}

		std::vector<ChatData*>::iterator iter1 = ChatDataHandler::get_instance2()->Personal_Chat_List.begin();
		std::vector<ChatData*>::iterator iter1_end = ChatDataHandler::get_instance2()->Personal_Chat_List.end();
		for (;iter1!=iter1_end;++iter1)
		{
			delete (*iter1);
		}
		ChatDataHandler::get_instance2()->Personal_Chat_List.clear();
	}
	CCLOG("---------------------------UPdata End!----------------------------");
}



cocos2d::CCSize ChatWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	m_szCELL = CCSizeMake(CellWidth,CellHeight);
	return m_szCELL;
}

cocos2d::extension::CCTableViewCell* ChatWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCLOG("Update Cell Index: %d",idx);
	CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(idx,cell);
	}
	_setTableCell(cell, idx);//展示cell的信息
	return cell;
}

unsigned int ChatWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if (m_curChannel == _Chat_Channel_World)
		return ChatDataHandler::get_instance2()->World_Show_Chat_List.size();
	else
		return ChatDataHandler::get_instance2()->Personal_Show_Chat_List.size();
}

void ChatWindow::_createTableCell(int index,cocos2d::extension::CCTableViewCell * cell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kCHAT_CELL_, cell);

	cell->setTag(index);
}

void ChatWindow::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int cellIDX)
{
	CCLOG("Cell Index %d",cellIDX);

	ShowChatData* pData;
	if (m_curChannel == _Chat_Channel_World)
	{
		pData = ChatDataHandler::get_instance2()->World_Show_Chat_List[cellIDX];
	}
	else
	{
		pData = ChatDataHandler::get_instance2()->Personal_Show_Chat_List[cellIDX];
	}
	if (!pData)
		return;

	ccColor3B TimeColor = ccYELLOW;
	ccColor3B ChannelColor = ccGREEN;
	ccColor3B PreNameColor = ccRED;
	ccColor3B NameColor = ccRED;
	ccColor3B LastNameColor = ccRED;
	ccColor3B TextColor = ccWHITE2;
	if (pData->m_ChatType ==_Chat_Channel_World)
	{
		if (pData->m_sendPlayerID == -1)
		{
			TimeColor = ccLIGHTYELLOW; 
			ChannelColor = ccLIGHTYELLOW;
			PreNameColor = ccLIGHTYELLOW;
			NameColor = ccLIGHTYELLOW; 
			LastNameColor = ccLIGHTYELLOW;
			TextColor = ccLIGHTYELLOW;
		}
		else
		{
			TimeColor =ccWHITE2;
			ChannelColor =ccWHITE2;
			if (pData->m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_)
			{
				NameColor = ccLIGHTORGANE;
				PreNameColor = ccLIGHTORGANE;
				LastNameColor = ccLIGHTORGANE;
			}
			else
			{
				NameColor = ccLIGHTBLUE;
				PreNameColor = ccLIGHTBLUE;
				LastNameColor = ccLIGHTBLUE;
			}
			TextColor =ccWHITE2;
		}

	}
	else if (pData->m_ChatType ==_Chat_Channel_Personal)
	{
		TimeColor =ccPURPLE;
		ChannelColor =ccPURPLE;
		PreNameColor = ccPURPLE;
		NameColor =ccLIGHTBLUE;
		LastNameColor = ccPURPLE;
		TextColor =ccPURPLE;
	}
	
	CCLabelTTF* pTimeLabel = (CCLabelTTF*)NFC_getNode(_Chat_Label_TimeLabel,cell);
	CCLabelTTF* pChannelLabel = (CCLabelTTF*)NFC_getNode(_Chat_Label_ChannelLabel,cell);
	CCMenu* pMenu = (CCMenu*)NFC_getNode(_Chat_Label_NameButton,cell);
	CMenuItemSprite* pNameButton = (CMenuItemSprite*)pMenu->getChildByTag(0);
	CCLabelTTF* pPreNameLabel = (CCLabelTTF*)NFC_getNode(_Chat_Label_PreNameLabel, cell);
	CCLabelTTF* pNameLabel = (CCLabelTTF*)NFC_getNode(_Chat_Label_NameLabel, cell);
	CCLabelTTF* pLastNameLabel = (CCLabelTTF*)NFC_getNode(_Chat_Label_LastNameLabel, cell);
	CCLabelTTF* pTextLabel = (CCLabelTTF*)NFC_getNode(_Chat_Label_TextLabel,cell);
	MaskNode* pMaskNode = (MaskNode*)NFC_getNode(_Chat_Label_NameButton_Data, cell);
	pTimeLabel->setVisible(true);
	pChannelLabel->setVisible(true);
	pMenu->setVisible(true);
	pNameButton->setVisible(true);
	pNameLabel->setVisible(true);
	pPreNameLabel->setVisible(true);
	pLastNameLabel->setVisible(true);
	pTextLabel->setVisible(true);

	if (pData->m_Type ==_Chat_Info)
	{	
	
		char time_[128]="";
		sprintf(time_,"%s",pData->m_time.c_str());
		pTimeLabel->setColor(TimeColor);
		pTimeLabel->setString(time_);
		pTimeLabel->setPositionX(0);
		pTimeLabel->setPositionY(0);
		char channel_[128]="";
		if (pData->m_sendPlayerID == -1)
		{
			sprintf(channel_,"%s",getChatType(_Chat_Channel_System).c_str());
		}
		else
		{
			sprintf(channel_,"%s",getChatType(pData->m_ChatType).c_str());
		}
		pChannelLabel->setColor(ChannelColor);
		pChannelLabel->setString(channel_);
		pChannelLabel->setPositionX(pTimeLabel->getPositionX() + pTimeLabel->getContentSize().width);
		if (pData->m_sendPlayerID == -1)		//系统
		{
			//pNameLabel->setColor(NameColor);
			//pNameLabel->setString("");
			//pNameLabel->setPositionX(pChannelLabel->getPositionX()+pChannelLabel->getContentSize().width);
			pNameLabel->setVisible(false);
			pPreNameLabel->setVisible(false);
			pLastNameLabel->setVisible(false);
		}
		if (pData->m_ChatType ==_Chat_Channel_World)	//世界
		{
			char name_[128]="";
			sprintf(name_,"%s:",pData->m_sendPlayerName.c_str());	
			pNameLabel->setColor(NameColor);
			pNameLabel->setString(name_);
			pNameLabel->setPositionX(pChannelLabel->getPositionX()+pChannelLabel->getContentSize().width);
			pPreNameLabel->setVisible(false);
			pLastNameLabel->setVisible(false);
		}
		else if(pData->m_ChatType ==_Chat_Channel_Personal)
		{
			char str_[128]="";
			memset(str_,0,128);
			if (pData->m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_)
			{
				sprintf(str_,"%s%s",SysLangDataManager::get_instance2()->GetSysLangById(ME).c_str(), SysLangDataManager::get_instance2()->GetSysLangById(TO).c_str());
				pPreNameLabel->setColor(PreNameColor);
				pPreNameLabel->setString(str_);
				pPreNameLabel->setPositionX(pChannelLabel->getPositionX() + pChannelLabel->getContentSize().width);

				pNameLabel->setColor(NameColor);
				pNameLabel->setString(pData->m_receivePlayerName.c_str());
				pNameLabel->setPositionX(pPreNameLabel->getPositionX() + pPreNameLabel->getContentSize().width);

				memset(str_, 0, 128);
				sprintf(str_,"%s:", SysLangDataManager::get_instance2()->GetSysLangById(SAY).c_str());
				pLastNameLabel->setColor(LastNameColor);
				pLastNameLabel->setString(str_);
				pLastNameLabel->setPositionX(pNameLabel->getPositionX() + pNameLabel->getContentSize().width);
				
			}
			else
			{
				pPreNameLabel->setVisible(false);
				
				pNameLabel->setColor(NameColor);
				pNameLabel->setString(pData->m_sendPlayerName.c_str());
				pNameLabel->setPositionX(pChannelLabel->getPositionX() + pChannelLabel->getContentSize().width);

				sprintf(str_,"%s%s%s:",SysLangDataManager::get_instance2()->GetSysLangById(TO).c_str(),SysLangDataManager::get_instance2()->GetSysLangById(ME).c_str(),SysLangDataManager::get_instance2()->GetSysLangById(SAY).c_str());
				pLastNameLabel->setColor(LastNameColor);
				pLastNameLabel->setString(str_);
				pLastNameLabel->setPositionX(pNameLabel->getPositionX() + pNameLabel->getContentSize().width);


			}

		}

		if (pData->m_sendPlayerID == -1)
		{
			pNameButton->setVisible(false);
		}
		else
		{
			
			CCScale9Sprite* normalImage = CCScale9Sprite::create();
			normalImage->setProperty("File", pMaskNode->GetViewPData()->filepath_);
			normalImage->setContentSize(pNameLabel->getContentSize());
			CCScale9Sprite* selectedImage = CCScale9Sprite::create();
			selectedImage->setProperty("File", pMaskNode->GetViewPData()->filepath2_);
			selectedImage->setContentSize(pNameLabel->getContentSize());
			pNameButton->setVisible(true);
			pNameButton->setNormalImage(normalImage);
			pNameButton->setSelectedImage(selectedImage);
			pNameButton->setPositionX(pNameLabel->getPositionX());
			pNameButton->setIDX(cellIDX);
			pNameButton->setTarget(this,menu_selector(ChatWindow::On_SelectName));
		}
		char text_[128]="";
		sprintf(text_,"%s",pData->m_text.c_str());
		pTextLabel->setColor(TextColor);
		pTextLabel->setString(text_);
		if( pLastNameLabel->isVisible() == true )
			pTextLabel->setPositionX(pLastNameLabel->getPositionX() + pLastNameLabel->getContentSize().width);
		else
		{
			if( pNameLabel->isVisible() == true )
				pTextLabel->setPositionX(pNameLabel->getPositionX()+pNameLabel->getContentSize().width);
			else
				pTextLabel->setPositionX(pChannelLabel->getPositionX() + pChannelLabel->getContentSize().width);
		}
	}
	
	else if (pData->m_Type ==_Chat_Info_Text)
	{
		pTimeLabel->setVisible(false);

		pChannelLabel->setVisible(false);

		pNameLabel->setVisible(false);

		pPreNameLabel->setVisible(false);

		pLastNameLabel->setVisible(false);

		pMenu->setVisible(false);
		

		pTextLabel->setString(pData->m_text.c_str());
		pTextLabel->setPositionX(0);
		pTextLabel->setColor(TextColor);
	}
}

std::string ChatWindow::getChatType(int type)
{
	switch(type)
	{
	case ChatDataHandler::_Type_World_:
		{
			return SysLangDataManager::get_instance2()->GetSysLangById(WORLD);
		}
	case ChatDataHandler::_Type_Personal_:
		{
			return	SysLangDataManager::get_instance2()->GetSysLangById(PERSONAL);
		}
	case ChatDataHandler::_Type_System_:
		{
			return	SysLangDataManager::get_instance2()->GetSysLangById(SYSTEM);
		}
	default:
		return "";
	}
}

void ChatWindow::UpdateLastChatInfo()
{
	ChatData* pData = ChatDataHandler::get_instance2()->m_LastChatData;
	if (!pData)
		return;
	std::list<std::string> text;

	if (pData->m_sendPlayerID == -1)
	{
		text = GetShowText(pData->m_text);
		m_ChatMultiLineLabel_1->setColor(ccLIGHTYELLOW);
		m_ChatMultiLineLabel_2->setColor(ccLIGHTYELLOW);
	}
	else
	{
		text = GetShowText(pData->m_text);

		if (pData->m_Type == _Chat_Channel_Personal)
		{
			m_ChatMultiLineLabel_1->setColor(ccPURPLE);
			m_ChatMultiLineLabel_2->setColor(ccPURPLE);
		}
		else
		{
			m_ChatMultiLineLabel_1->setColor(ccWHITE2);
			m_ChatMultiLineLabel_2->setColor(ccWHITE2);
		}

	}
	m_ChatMultiLineLabel_1->setString("");
	m_ChatMultiLineLabel_2->setString("");
	std::list<std::string>::iterator itor = text.begin();
	int index = 0;
	for(;itor!=text.end();++itor)
	{
		if(index == 0)	
			m_ChatMultiLineLabel_1->setString((*itor).c_str());
		else if(index == 1)
			m_ChatMultiLineLabel_2->setString((*itor).c_str());
		else
			break;
		index++;
	}

	//m_ChatMultiLineLabel->setString(text.c_str());
	CCLOG("UpdateLastLine:%s%s",m_ChatMultiLineLabel_1->getString(), m_ChatMultiLineLabel_2->getString());
	
}

void ChatWindow::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{	
	
	if (editBox == pNameInputBox)
		 pNameInputBox->setText("");

	m_IsKeyBroadShow = true;
	CCLOG("EditingDidBegin!");
}

void ChatWindow::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
	m_IsKeyBroadShow = false;
	CCLOG("Return!");
}

void ChatWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	CCLOG("Touch!! %d", pLayerColor->getTag());
	if( pLayerColor == m_BGLayer){
		On_CloseBig(NULL);
	}
	else if( pLayerColor == m_BGSmallLayer){
		HideChannelList();
		HideNameList();
		m_PopWindow->setVisible(false);
	}
}

std::string ChatWindow::revertUTF8(std::string a){
	std::list<std::string> temp = parser_utf8_string(a);
	std::list<std::string>::iterator itor = temp.begin();
	std::list<std::string>::iterator iend = temp.end();
	std::list<std::string> result;
	std::string _result = "";
	for(;itor != iend; ++itor){
		result.push_front(*itor);
	}
	for(itor = result.begin();itor!=result.end();itor++){
		_result += (*itor);
	}
	return _result;

}

std::list<std::string> ChatWindow::GetShowText(std::string text)
{
	std::list<std::string> result;
	CCImage pImage;
	pImage.getStringSize(text.c_str(),0,0,CCImage::kAlignTopLeft,m_ChatMultiLineLabel_1->getFontName(),m_ChatMultiLineLabel_1->getFontSize());
	MaskNode *pNode = (MaskNode*)NFC_getNode(_Chat_TalkLine_Data_,m_pRootNode);
	float mutiLabelWidth = pNode->GetViewPData()->height_;
	std::list<std::string> templist = parser_utf8_string(text);
	std::list<std::string>::iterator itor = templist.end();
	std::list<std::string>::iterator _itor = templist.end();
	std::list<std::string>::iterator _tmp = templist.end();
	int index = templist.size();
	std::string temp = "";
	std::string _temp = "";
	bool isLong = false;
	for(;index > 0; index--){
		itor--;
		temp = temp + (*itor);
		CCImage pImage1;
		pImage1.getStringSize(temp.c_str(),0,0,CCImage::kAlignTopLeft,m_ChatMultiLineLabel_1->getFontName(),m_ChatMultiLineLabel_1->getFontSize());
		if(pImage1.getWidth() > mutiLabelWidth*2){
			isLong = true;
			_temp = revertUTF8(temp);
			break;

		}
	}
	if(!isLong){
		_temp = revertUTF8(temp);
	}
	CCLOG("%s",_temp.c_str());
	templist = parser_utf8_string(_temp);
	temp = "";
	for(itor = templist.begin(); itor!= templist.end();itor++){
		temp = temp + (*itor);
		CCImage pImage1;
		pImage1.getStringSize(temp.c_str(),0,0,CCImage::kAlignTopLeft,m_ChatMultiLineLabel_1->getFontName(),m_ChatMultiLineLabel_1->getFontSize());
		if(pImage1.getWidth() > mutiLabelWidth){
			result.push_back(temp);
			CCLOG("%s",temp.c_str());
			temp = "";
		}
	}
	if(temp != ""){
		result.push_back(temp);
		CCLOG("%s",temp.c_str());
	}

	return result;

}

void ChatWindow::setChatData(ShowChatData &pData,ShowChatData*tempData)
{
	pData.m_ChatType = tempData->m_ChatType;
	pData.m_receivePlayerID = tempData->m_receivePlayerID;
	pData.m_receivePlayerName = tempData->m_receivePlayerName;
	pData.m_sendPlayerID = tempData->m_sendPlayerID;
	pData.m_sendPlayerName = tempData->m_sendPlayerName;
	pData.m_text = tempData->m_text;
	pData.m_time = tempData->m_time;
	pData.m_Type = tempData->m_Type;
}



std::string ChatWindow::checkText(std::string text)
{
	std::string temp;
	int _size = 0;
	std::list<std::string> templist = parser_utf8_string(text.c_str());
	std::list<std::string>::iterator itor = templist.begin();
	std::list<std::string>::iterator itor_end = templist.end();
	for(;itor != itor_end;itor++)
	{
		if((*itor).size() >1 )
			_size += 2;
		else
			_size += 1;
		temp +=(*itor);
	}
	if (_size > NameLengthMax)
	{
		std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(148);
		NFC_showMessageBox(kDEFAULT,str2);
		return "";
	}
	else
	{
		return temp;
	}

}