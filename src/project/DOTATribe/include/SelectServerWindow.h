//Name��SelectServerWindow
//Function��������ѡ�����
//Written By��������
//Edit:Johny
#ifndef  _DOTATRIBE_SELECTSERVERWINDOW_H_
#define  _DOTATRIBE_SELECTSERVERWINDOW_H_


#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/CTouchSprite.h"

class SelectServerWindow : public IWindow
		,public cocos2d::extension::CCTableViewDataSource
		,public CPriorityLayerColorDelegate
		,public cocos2d::extension::CCTableViewDelegate
		,public CTouchSpriteDelegate
{
public:
	SelectServerWindow();
	virtual ~SelectServerWindow();

	enum{
			SERVERPRIORCOLOR= 0,	//������ѡ��װ�
			SERVERBG,
			TABLEVIEW,
			TABLEVIEWCELL,
			PNODE1,			//CNODE�����洢����
			PNODE2,
			PNODE3,
        };

	enum{
			CELL_SERVERBTN1,		 //����1
			CELL_SERVERBTN2,		 //����2
			CELL_SERVERBG1,		 //����1
			CELL_SERVERBG2,		 //����2
			CELL_NEWSER1,         //״̬1
			CELL_NEWSER2,         //״̬2
			CELL_SERVERNAME1,     //����������1	
			CELL_SERVERNAME2,     //����������2
			CELL_TILENAME,
			CELL_TITLEBG,
	    }CELL;

	CCNode* m_pRoot;
	CCNode* m_pRoot_Server;
	cocos2d::extension::CCTableView* m_pTable;
	cocos2d::CCSize m_szCell;
	unsigned char m_curServerInfostate;
	int m_curServerId;

	int m_SoonTitleIndex;
	int m_AllTitleIndex;
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

	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
private:
	/*
		��ʾ��������¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
    /*
		���´�������¼�����
	*/
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);

private:
	inline void  _initLayout();
	inline void _mapGrayLayer();
	inline void _setTableView();
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);
	inline void _mapCellToggle(cocos2d::extension::CCTableViewCell* cell,int id);

	inline void _setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	inline void _mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx);

	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	void _showTitle(cocos2d::CCNode* cell,bool isShow,std::string str="");
public:
	void On_Click_Table_Block(cocos2d::CCObject * pSender);
	/*
		CPriorityLayerColor CallBack
	*/
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
	/*
		CTouchSprite CallBack
	*/
	virtual void rangeTouched(cocos2d::CCObject* pSender);
};

#endif
