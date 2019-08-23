//Name：SelectServerWindow
//Function：服务器选择界面
//Written By：吕云龙
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
			SERVERPRIORCOLOR= 0,	//服务器选择底板
			SERVERBG,
			TABLEVIEW,
			TABLEVIEWCELL,
			PNODE1,			//CNODE用来存储数据
			PNODE2,
			PNODE3,
        };

	enum{
			CELL_SERVERBTN1,		 //背景1
			CELL_SERVERBTN2,		 //背景2
			CELL_SERVERBG1,		 //背景1
			CELL_SERVERBG2,		 //背景2
			CELL_NEWSER1,         //状态1
			CELL_NEWSER2,         //状态2
			CELL_SERVERNAME1,     //服务器名称1	
			CELL_SERVERNAME2,     //服务器名称2
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

	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
private:
	/*
		显示大厅面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
    /*
		更新大厅面板事件处理
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
