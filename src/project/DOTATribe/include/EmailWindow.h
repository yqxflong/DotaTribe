//Name��EmailWindow
//Function���������
//Written By����ǿ
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

	cocos2d::CCSize m_szCell;			//��ѯ�б��
	cocos2d::CCSize m_szCellAttachment;	//������С
	cocos2d::extension::CCTableView* m_pTable;				//CCTableView�ؼ�

	cocos2d::extension::CCTableView* m_pTableAttachment;    //CCTableView�ؼ�

	unsigned int m_nCurIndex_system;
	unsigned int m_nCurIndex_personal;

	CMenuItemSprite* m_pCurItem;//��ǰTabmenu

	int m_CurrSubTabIndex;//��ǰTab����
	
	int m_CurrEmailMenuIndex;
public:
	EmailWindow();
	virtual ~EmailWindow();
public:
	//��ʾϵͳ��Ϣ�ؼ�
	void ShowSystemProtocol(EmailInfoData* data);
	void HideSystemProtocol();
	void ShowPersonalProtocol();
	void HidePersonalProtocol();
	
private:
	inline void _initLayout();
	inline void _initData();
	inline void _initCell();
	inline void _initCornerNumIcon();//��ʼ���Ǳ�
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
//	void _setTableViewAttach();		//��ȡ������tableview

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
		��ʼ������
	*/
	virtual    bool    Init();
	/*
		���ش���
	*/
	virtual    bool    Load();
	/*
		����´���
	*/
	virtual    void    Tick();
	/*
		���ٴ���
	*/ 
	virtual    void    Destroy();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		��ʾ��������¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		������������¼�����
	*/
	inline void   OnHideWindowEventHandler(std::list<std::string>& paramList);

	/*
		������������¼�����
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
		tab�ص�
	*/
	virtual void On_Tab_Selected(int idx){};
	/*
		��ǰ ϵͳ�͸��˻ص�Tab
	*/
	void On_Tab_Sub_Selected(int idx);
	/*
		�õ���ǰ��TabIndex
	*/
	unsigned int getCurrentSubTabIndex()const
	{
		return m_CurrSubTabIndex;
	}
	/*
		�鿴�ʼ���ť�ص�
	*/
	void On_Check_Email(cocos2d::CCObject* pSender);

	/*
		�鿴������ť�ص�
	*/
	void On_CheckAttach_Click(cocos2d::CCObject* pSender);
	/*
		����UI
	*/
	void refreshUIData();
	
};


#endif
