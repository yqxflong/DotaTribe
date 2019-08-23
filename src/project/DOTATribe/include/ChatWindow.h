// Name :		ChatWindow.h
// Function:	���촰��
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
		_Chat_BG_,								// �󴰿ڱ���
		_Chat_WorldLabel_,						// ѡ��Ƶ������ǩ��������
		_Chat_WorldLabelImage_,					// ѡ��Ƶ������ͼ��������
		_Chat_PersonalLabel_,					// ѡ��Ƶ������ǩ����˽��
		_Chat_PersonalLabelImage_,				// ѡ��Ƶ������ͼ����˽��
		_Chat_Close_,							// ���ش󴰿ڰ�ť
		_Chat_SendButton_,						// ���Ͱ�ť	
		_Chat_SendButtonImage_,					// ���Ͱ�ť����
		_Chat_TextInput_,						// ����Ƶ��ʱ��EditBox
		_Chat_TextInputPersonal_,				// ˽��Ƶ��ʱ��EditBox
		_Chat_ChannelButton_,					// �л�Ƶ����ť
		_Chat_ChannelButton_World_,				// �л�Ƶ��ʱ�����İ�ť��������
		_Chat_ChannelButton_Personal_,			// �л�Ƶ��ʱ�����İ�ť����˽��
		_Chat_NameInput_,						// ˽�ġ������Ѷ���EditBox
		_Chat_NameListButton_,					// ˽�ġ���չ����ʷ����ť
		_Chat_NameListButtonClose_,				// ˽�ġ���������ʷ����ť
		_Chat_Cell_,							// ��ʾ�������ݵ�TabView
		_Chat_Cell_Block,						// ��ʾ�������ݵ�TabView�е�Cell
		_Chat_NameListBG,						// ˽�ġ���չ����ʷ���󡪡�����
		_Chat_NameList_Line1,					// ˽�ġ���չ����ʷ���󡪡��ָ���1
		_Chat_NameList_Line2,					// ˽�ġ���չ����ʷ���󡪡��ָ���2
		_Chat_NameList_Line3,					// ˽�ġ���չ����ʷ���󡪡��ָ���3
		_Chat_NameList_Item1,					// ˽�ġ���չ����ʷ���󡪡�����1
		_Chat_NameList_Item2,					// ������������������������������������ ����2
		_Chat_NameList_Item3,					// ������������������������������������ ����3
		_Chat_NameList_Item4,					// ������������������������������������ ����4
		_Chat_NameList_Label1,					// ������������������������������������ ����1 Label
		_Chat_NameList_Label2,					// ������������������������������������ ����2 Label
		_Chat_NameList_Label3,					// ������������������������������������ ����3 Label
		_Chat_NameList_Label4,					// ������������������������������������ ����4 Label
		_Chat_Small_Button,						// С���ڡ���չ����ť
		_Chat_Small_BG,							// С���ڡ�������
		_Chat_Small_Label,						// С���ڡ�����һ��������Ϣ
		_Chat_Small_Label2,						// С���ڡ����ڶ���������Ϣ
		_Chat_BGLayer_Big_,						// ���ֲ㡪����
		_Chat_BGLayer_Small_,					// ���ֲ㡪��С
		_Chat_PopWindow_,						// ����������ֵ�������
		_Chat_NameList_Data_,					// MaskNode
		_Chat_TalkLine_Data_,					// MaskNode ���г���
		

	};

	// PopWindow ����������ֵ������ڲ���
	enum{
		_Chat_EventListBG,						// ����
		_Chat_EventList_Line1,					// �ָ���1 
		_Chat_EventList_Line2,					// �ָ���2
		_Chat_EventList_Item1,					// ����1
		_Chat_EventList_Item2,					// ����2
		_Chat_EventList_Item3,					// ����3
		_Chat_EventList_Data_Button				// MaskNode ��ť��Ϣ
	};

	enum
	{
		_Chat_Info,
		_Chat_Info_Text,
	};
	
	// ���촰�ڡ���ÿ����Ϣ����
	enum
	{
		_Chat_Label_TimeLabel = 1,				// ʱ��
		_Chat_Label_ChannelLabel,				// Ƶ��
		_Chat_Label_PreNameLabel,				// �����ǰ�沿��
		_Chat_Label_NameLabel,					// �����
		_Chat_Label_LastNameLabel,				// ��������沿��
		_Chat_Label_NameButton,					// �������ť
		_Chat_Label_TextLabel,					// ����
		_Chat_Label_NameButton_Data,			// MaskNode �������ť����
	};



public:
	enum
	{
		_Chat_Channel_World,
		_Chat_Channel_Personal,
		_Chat_Channel_System,
	};

private:
	// ������ʾ�������ݿ�����
	bool m_isNeedUpdate;
	void ChatWindowUpdate();

private:
	// ShowControl HideControl ��ͬ��NFC_ShowNode(true) NFC_SHowNode(false)
	void ShowControl(int id);
	void HideControl(int id);
	/*
		�ؼ���������������촰�ڵĿؼ���Ϊ�������֣�
		�󴰿ڡ��������������벿�֣�EditBox,Ƶ��ѡ��ť�ȣ�
			  ��������˽��ʱ������˽����ʷ���󴰿�
			  �������������������ʱ�ĵ�������
		С����

	*/
	/*
		�����ڴ󴰿ڵĿؼ���ʾ������
	*/
	void ShowBigWindow();			
	void HideBigWindow();
	/*
		������С���ڵĿؼ���ʾ������
	*/
	void ShowSmallWindow();
	void HideSmallWindow();
	
	// �ڴ󴰿��У��������벿�֣����ؼ�����Ϊ˽��Ƶ��
	void ShowPersonalInputWindow();
	// �ڴ󴰿��У��������벿�֣����ؼ�����Ϊ����Ƶ��
	void ShowWorldInputWindow();
	// ����������������������������������������������������ؿؼ�
	void HideInputWindow();
	/*
		˽�ģ���ʷ����չ��������ؼ�����
	*/
	void ShowNameList();
	void HideNameList();
	// ����NameList����
	void UpdateNameList();
	/*
		�л�Ƶ��ʱ�ؼ�����
	*/
	void ShowChannelList();
	void HideChannelList();
	/*
		����������ְ�ť��������������
	*/
	void ShowPopWindow(CCPoint pos);
	void HidePopWindow();
public:
	ChatWindow();
	virtual ~ChatWindow();
public:
	// С����CCNode
	CCNode* m_pSmall;
	// �󴰿�CCNode
	CCNode* m_pBig;
	// ����������ְ�ť����CCNode
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
	// ��ǰƵ����0 World, 1 Personal
	int m_curChannel;
	// �������������id
	int m_LastPerson;
	// ������Ϣ����Ƶ����0 World, 1 Personal
	int m_SendType;
	// �����Ƿ�����ʾ
	bool m_IsKeyBroadShow;
	// ˽�Ķ��������Ϣ
	PlayerInfo m_PersonalChatInfo;
	// ���췢����Ϣ���
	float m_CoolDownTime;
	// ������Ϣ���¼��
	float m_timeLast;

public:
	// �л���ǩҳCallBack
	void On_Change_Label(cocos2d::CCObject* pSender);
	// ��ʾ˽����ʷ����CallBack
	void On_Show_NameList(cocos2d::CCObject* pSender);
	// ����˽����ʷ����CallBack
	void On_Close_NameList(cocos2d::CCObject* pSender);
	// ˽����ʷ������CallBack
	void On_SetName(cocos2d::CCObject* pSender);
	// ����������������ڡ���˽��
	void On_SetEvent_SetName(cocos2d::CCObject* pSender);
	// ����������������ڡ����鿴����
	void On_SetEvent_CheckData(cocos2d::CCObject* pSender);
	// ����������������ڡ�����Ӻ���
	void On_SetEvent_AddFriend(cocos2d::CCObject* pSender);
	// ���������CallBack 
	void On_SelectName(cocos2d::CCObject* pSender);
	// С����->�󴰿�CallBack
	void On_ShowBig(cocos2d::CCObject* pSender);
	// �󴰿�->С����CallBack
	void On_CloseBig(cocos2d::CCObject* pSender);
	// ������Ϣ��ťCallBack
	void On_SendMessage(cocos2d::CCObject* pSender);
	// �л�����Ƶ����ťCallBack
	void On_Show_ChannelList(cocos2d::CCObject* pSender);
	// ѡ��������Ƶ����ťCallBack
	void On_Close_ChannelList(cocos2d::CCObject* pSender);

	cocos2d::CCSize m_szCELL;			//��ʼ�����ļ���ȡ��
	ShowChatData m_selectData;
	
public:
	// ������ʾ������Ϣ
	void UpdataShowChatData();
	// �������һ��������Ϣ������С������ʾ
	void UpdateLastChatInfo();
	// ������Ϣ�Ƿ������
	std::string checkText(std::string text);
	// С������ʾ������Ϣ�������У����ı�����Ϊ���е�string
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
	

	//����tableView�����RSSubView.h
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

