//Name：EmailWindow
//Function：邮箱界面
//Written By：尹强
//Edit by: LvYunlong
#ifndef  _DOTATRIBE_EmailWindow_H_
#define  _DOTATRIBE_EmailWindow_H_

#include "../include/IWindow.h"
#include "../include/EmailDataHandler.h"
#include "../include/CMenuItemSprite.h"
#include <cocos-ext.h>

class EmailWindow:public IWindow
	,cocos2d::extension::CCTableViewDataSource
	,cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
		_TABLE_TYPE_QUERY_ = 0,
		_TABLE_TYPE_ATTACHMENT_,
	};
	enum{
		udBEHIND = 0,
		udEMAILBG,
		udTITLEBG,
		udCLOSEBTN,
		udTAB1,
		udTAB2,
		udTAB1TEXT,
		udTAB2TEXT,
		udCHECKFRITEXTBG,
		udSENDERTEXT,
		udLEFTTABLE,
		udLEFTTABLECELL,
		udLEFTTABLE1,
		udLEFTTABLECELL1,
		udWRITEBTN,
		udSENDER,
		udDATE,
		udCONTENT,
		udREMOVEBTN,
		udREMOVEBTNTITLE,
		udGETBTN,
		udGETBTNTITLE,
		udREPLYBTN,
		udREPLYBTNTITLE,
		udGETALLBTN,
		udGETALLBTNTITLE,
		udCHECKINFOBTN,
		udCHECKINFOBTNTITLE,
		udLETTERLINE,
		udNOREADSYSEMAIL,
		udNOREADPERSONEMAIL,
		udMONEYTEXTBG,
		udDIAMONDTEXTBG,
		udMONEYTEXTTTF,
		udDIAMONDTEXTTTF,
		udTIPSEMAILDELETETTF,
	}M_PROOT;
	enum{
		udCELLBG,
		udCELLMAILICON,
		udCELLSELECTICON,
		udCELLMAILTITLE,
	}LISTCELL;

	enum{
		udINFOCELL_OBJ_,
		udINFOCELLNUM,
	}INFOCELL;

	cocos2d::CCNode* m_pRoot;		//

	cocos2d::CCSize m_szCell;			//查询列表的
	cocos2d::CCSize m_szCellAttachment;	//附件大小
	cocos2d::extension::CCTableView* m_pTable;				//CCTableView控件

	cocos2d::extension::CCTableView* m_pTableAttachment;    //CCTableView控件

	unsigned int m_nCurIndex_system;
	unsigned int m_nCurIndex_personal;

	CMenuItemSprite* m_pCurItem;//当前Tabmenu

	int m_CurrSubTabIndex;//当前Tab索引
	
	int m_CurrEmailMenuIndex;
public:
	EmailWindow();
	virtual ~EmailWindow();
public:
	//显示系统信息控件
	void ShowSystemProtocol(EmailInfoData* data);
	void HideSystemProtocol();
	void ShowPersonalProtocol();
	void HidePersonalProtocol();
	
private:
	inline void _initLayout();
	inline void _initData();
	inline void _initCell();
	inline void _initCornerNumIcon();//初始化角标
	inline void _mapBtn();
	inline void _layoutForSystem();
	inline void _layoutForPersonal();
	inline void _showMailDetail(int index);
	inline void _mapCellQueryBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);

	inline void _mapCellAttachmentBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	//
	//Tableview
	void _setTableView();
	
	//AttachmentTableview
//	void _setTableViewAttach();		//获取附件的tableview

	void _createTableCell(cocos2d::extension::CCTableViewCell* cell,int tabletype);
	void _setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell,int tabletype);
	/*
		selectSubTabItem
	*/
	void selectSubTabItem(int idx);
	void selectTabItem(int idx);
	
	void _setAttachmenticon(EmailListDataObject *data,cocos2d::extension::CCTableViewCell* cell);

private:
	void On_TabIndex_Click(cocos2d::CCObject * pSender);
	void On_Event_Click(cocos2d::CCObject * pSender);
	void On_WriteBtn_Click(cocos2d::CCObject * pSender);
	void On_CheckInfoBtn_Click(cocos2d::CCObject * pSender);
	void On_RemoveBtn_Click(cocos2d::CCObject * pSender);
	void On_GetBtn_Click(cocos2d::CCObject * pSender);
	void On_ReplyBtn_Click(cocos2d::CCObject * pSender);
	void On_GetAllBtn_Click(cocos2d::CCObject *pSender);

public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		显示邮箱面板事件处理
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		隐藏邮箱面板事件处理
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);

	/*
		更新邮箱面板事件处理
	*/
	inline void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);
private:
	/*
		TableView Datasource
	*/
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
public:
	/*
		tab回调
	*/
	virtual void On_Tab_Selected(int idx){};
	/*
		当前 系统和个人回调Tab
	*/
	void On_Tab_Sub_Selected(int idx);
	/*
		得到当前子TabIndex
	*/
	unsigned int getCurrentSubTabIndex()const
	{
		return m_CurrSubTabIndex;
	}
	/*
		查看邮件按钮回调
	*/
	void On_Check_Email(cocos2d::CCObject* pSender);

	/*
		查看附件按钮回调
	*/
	void On_CheckAttach_Click(cocos2d::CCObject* pSender);
	/*
		更新UI
	*/
	void refreshUIData();
	
};


#endif
