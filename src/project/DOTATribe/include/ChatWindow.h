// Name :		ChatWindow.h
// Function:	聊天窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan, shaobing

#ifndef  _DOTATRIBE_CHATWINDOW_H_
#define  _DOTATRIBE_CHATWINDOW_H_

#include "../include/DOTATribeApp.h"
#include "../include/IWindow.h"
#include "../include/CTableView.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/ChatDataHandler.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include <vector>
#include <list>
using namespace cocos2d;
using namespace cocos2d::extension;
class ChatWindow : public IWindow,public cocos2d::extension::CCTableViewDataSource, cocos2d::extension::CCTableViewDelegate,CPriorityLayerColorDelegate, public cocos2d::extension::CCEditBoxDelegate
{
	enum
	{
		_Chat_BG_,								// 大窗口背景
		_Chat_WorldLabel_,						// 选择频道：标签——世界
		_Chat_WorldLabelImage_,					// 选择频道：底图——世界
		_Chat_PersonalLabel_,					// 选择频道：标签——私聊
		_Chat_PersonalLabelImage_,				// 选择频道：底图——私聊
		_Chat_Close_,							// 隐藏大窗口按钮
		_Chat_SendButton_,						// 发送按钮	
		_Chat_SendButtonImage_,					// 发送按钮背景
		_Chat_TextInput_,						// 世界频道时的EditBox
		_Chat_TextInputPersonal_,				// 私人频道时的EditBox
		_Chat_ChannelButton_,					// 切换频道按钮
		_Chat_ChannelButton_World_,				// 切换频道时弹出的按钮——世界
		_Chat_ChannelButton_Personal_,			// 切换频道时弹出的按钮——私聊
		_Chat_NameInput_,						// 私聊——好友对象EditBox
		_Chat_NameListButton_,					// 私聊——展开历史对象按钮
		_Chat_NameListButtonClose_,				// 私聊——收起历史对象按钮
		_Chat_Cell_,							// 显示聊天内容的TabView
		_Chat_Cell_Block,						// 显示聊天内容的TabView中的Cell
		_Chat_NameListBG,						// 私聊——展开历史对象——背景
		_Chat_NameList_Line1,					// 私聊——展开历史对象——分割线1
		_Chat_NameList_Line2,					// 私聊——展开历史对象——分割线2
		_Chat_NameList_Line3,					// 私聊——展开历史对象——分割线3
		_Chat_NameList_Item1,					// 私聊——展开历史对象——对象1
		_Chat_NameList_Item2,					// ……………………………………………… 对象2
		_Chat_NameList_Item3,					// ……………………………………………… 对象3
		_Chat_NameList_Item4,					// ……………………………………………… 对象4
		_Chat_NameList_Label1,					// ……………………………………………… 对象1 Label
		_Chat_NameList_Label2,					// ……………………………………………… 对象2 Label
		_Chat_NameList_Label3,					// ……………………………………………… 对象3 Label
		_Chat_NameList_Label4,					// ……………………………………………… 对象4 Label
		_Chat_Small_Button,						// 小窗口——展开按钮
		_Chat_Small_BG,							// 小窗口——背景
		_Chat_Small_Label,						// 小窗口——第一行聊天信息
		_Chat_Small_Label2,						// 小窗口——第二行聊天信息
		_Chat_BGLayer_Big_,						// 遮罩层——大
		_Chat_BGLayer_Small_,					// 遮罩层——小
		_Chat_PopWindow_,						// 点击好友名字弹出窗口
		_Chat_NameList_Data_,					// MaskNode
		_Chat_TalkLine_Data_,					// MaskNode 换行长度
		

	};

	// PopWindow 点击好友名字弹出窗口布局
	enum{
		_Chat_EventListBG,						// 背景
		_Chat_EventList_Line1,					// 分割线1 
		_Chat_EventList_Line2,					// 分割线2
		_Chat_EventList_Item1,					// 对象1
		_Chat_EventList_Item2,					// 对象2
		_Chat_EventList_Item3,					// 对象3
		_Chat_EventList_Data_Button				// MaskNode 按钮信息
	};

	enum
	{
		_Chat_Info,
		_Chat_Info_Text,
	};
	
	// 聊天窗口——每条信息布局
	enum
	{
		_Chat_Label_TimeLabel = 1,				// 时间
		_Chat_Label_ChannelLabel,				// 频道
		_Chat_Label_PreNameLabel,				// 玩家名前面部分
		_Chat_Label_NameLabel,					// 玩家名
		_Chat_Label_LastNameLabel,				// 玩家名后面部分
		_Chat_Label_NameButton,					// 玩家名按钮
		_Chat_Label_TextLabel,					// 正文
		_Chat_Label_NameButton_Data,			// MaskNode 玩家名按钮数据
	};



public:
	enum
	{
		_Chat_Channel_World,
		_Chat_Channel_Personal,
		_Chat_Channel_System,
	};

private:
	// 更新显示聊天内容控制器
	bool m_isNeedUpdate;
	void ChatWindowUpdate();

private:
	// ShowControl HideControl 等同于NFC_ShowNode(true) NFC_SHowNode(false)
	void ShowControl(int id);
	void HideControl(int id);
	/*
		控件控制里，将所有聊天窗口的控件分为几个部分：
		大窗口————聊天输入部分（EditBox,频道选择按钮等）
			  ————私聊时弹出的私聊历史对象窗口
			  ————点击好友名字时的弹出窗口
		小窗口

	*/
	/*
		将属于大窗口的控件显示或隐藏
	*/
	void ShowBigWindow();			
	void HideBigWindow();
	/*
		将属于小窗口的控件显示或隐藏
	*/
	void ShowSmallWindow();
	void HideSmallWindow();
	
	// 在大窗口中，聊天输入部分，将控件调整为私聊频道
	void ShowPersonalInputWindow();
	// 在大窗口中，聊天输入部分，将控件调整为世界频道
	void ShowWorldInputWindow();
	// …………………………………………………………，隐藏相关控件
	void HideInputWindow();
	/*
		私聊，历史对象展开与收起控件控制
	*/
	void ShowNameList();
	void HideNameList();
	// 更新NameList内容
	void UpdateNameList();
	/*
		切换频道时控件控制
	*/
	void ShowChannelList();
	void HideChannelList();
	/*
		点击好友名字按钮弹出窗口与隐藏
	*/
	void ShowPopWindow(CCPoint pos);
	void HidePopWindow();
public:
	ChatWindow();
	virtual ~ChatWindow();
public:
	// 小窗口CCNode
	CCNode* m_pSmall;
	// 大窗口CCNode
	CCNode* m_pBig;
	// 点击好友名字按钮窗口CCNode
	CCNode* m_PopWindow;
public:
	// _Chat_NameList_ItemX
	std::vector<CMenuItemSprite*> m_NameList;
	// _Chat_NameList_LabelX
	std::vector<CCLabelTTF*> m_NameListLabel;
	// _Chat_WorldLabelImage_
	CMenuItemSprite* m_WorldLabel;
	// _Chat_PersonalLabelImage_
	CMenuItemSprite* m_PersonalLabel;
	// _Chat_ChannelButton_
	CLabelButtonItem* m_ChannelButton;
	// _Chat_ChannelButton_World_
	CLabelButtonItem* m_ChannelButton_world;
	// _Chat_ChannelButton_Personal_
	CLabelButtonItem* m_ChannelButton_personal;
	// _Chat_BGLayer_Big_
	CPriorityLayerColor* m_BGLayer;
	// _Chat_BGLayer_Small_
	CPriorityLayerColor* m_BGSmallLayer;
	// _Chat_NameInput_
	CCEditBox* pNameInputBox;
	// _Chat_TextInput_
	CCEditBox* pTextInputBox;
	// _Chat_TextInput_Persional
	CCEditBox* pTextInputBoxPersonal;
	// _Chat_NameListButton_
	CMenuItemSprite* pUpButton;
	// _Chat_NameListButtonClose_
	CMenuItemSprite* pDownButton;
	// _Chat_BG_
	CCSprite* m_pBG;
	// _Chat_Small_Label
	CCLabelTTF* m_ChatMultiLineLabel_1;
	// _Chat_Small_Label1
	CCLabelTTF* m_ChatMultiLineLabel_2;
	// _Chat_Cell_
	CTableView *  m_View_layer;
public:
	// 当前频道，0 World, 1 Personal
	int m_curChannel;
	// 最后点击好友名的id
	int m_LastPerson;
	// 发送信息所在频道，0 World, 1 Personal
	int m_SendType;
	// 键盘是否在显示
	bool m_IsKeyBroadShow;
	// 私聊对象玩家信息
	PlayerInfo m_PersonalChatInfo;
	// 聊天发送信息间隔
	float m_CoolDownTime;
	// 聊天信息更新间隔
	float m_timeLast;

public:
	// 切换标签页CallBack
	void On_Change_Label(cocos2d::CCObject* pSender);
	// 显示私聊历史对象CallBack
	void On_Show_NameList(cocos2d::CCObject* pSender);
	// 隐藏私聊历史对象CallBack
	void On_Close_NameList(cocos2d::CCObject* pSender);
	// 私聊历史对象点击CallBack
	void On_SetName(cocos2d::CCObject* pSender);
	// 点击好友名弹出窗口——私聊
	void On_SetEvent_SetName(cocos2d::CCObject* pSender);
	// 点击好友名弹出窗口——查看资料
	void On_SetEvent_CheckData(cocos2d::CCObject* pSender);
	// 点击好友名弹出窗口——添加好友
	void On_SetEvent_AddFriend(cocos2d::CCObject* pSender);
	// 点击好友名CallBack 
	void On_SelectName(cocos2d::CCObject* pSender);
	// 小窗口->大窗口CallBack
	void On_ShowBig(cocos2d::CCObject* pSender);
	// 大窗口->小窗口CallBack
	void On_CloseBig(cocos2d::CCObject* pSender);
	// 发送信息按钮CallBack
	void On_SendMessage(cocos2d::CCObject* pSender);
	// 切换聊天频道按钮CallBack
	void On_Show_ChannelList(cocos2d::CCObject* pSender);
	// 选择新聊天频道按钮CallBack
	void On_Close_ChannelList(cocos2d::CCObject* pSender);

	cocos2d::CCSize m_szCELL;			//初始化从文件中取得
	ShowChatData m_selectData;
	
public:
	// 更新显示聊天信息
	void UpdataShowChatData();
	// 更新最后一条聊天信息，用于小窗口显示
	void UpdateLastChatInfo();
	// 发送信息是否过长？
	std::string checkText(std::string text);
	// 小窗口显示聊天信息，分两行，将文本处理为两行的string
	std::list<std::string> GetShowText(std::string text);
	// SetChatData
	void setChatData(ShowChatData &pData,ShowChatData*tempData);
	
public:
	void _refreshTableView(CTableView * table) const
	{

		if (m_View_layer->isVisible())
		{
			table->reloadData();
			if(table->getViewSize().height > table->getContentSize().height)
				table->setContentOffset(ccp(0,table->getViewSize().height - table->getContentSize().height));
			else
				table->setContentOffset(CCPointZero);
		}
	}
	

	std::string getChatType(int type);
	std::string revertUTF8(std::string a);


public:
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	void OnShowWindowEventHandler(std::list<std::string>& paramList);
public:
	void initLayer();
	void _mapBtn();
	void _mapOthers();
	

	//创建tableView，详见RSSubView.h
	CTableView * _createTableView(cocos2d::extension::CCTableViewDataSource * ds
		, const cocos2d::CCSize & szView) const
	{
		CTableView * table = CTableView::create(ds, szView,kPRIORITYHIGHER);
		table->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
		table->setTouchEnabled(true);
		table->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
		return table;
	}
	
protected:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
private:
	inline void _createTableCell(int index, cocos2d::extension::CCTableViewCell * cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int cellIDX);
private:
	inline void _createPopWindow();
public:
	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox){};
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text){ CCLOG(text.c_str());};
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);

};


#endif

