//Name: LoginActivityWindow
//Author: lvyunlong
//Func: Activity of Everyday Login
//Maintainer:lvyunlong

#ifndef  _DOTATRIBE_LOGINACTIVITYWINDOW_H_
#define  _DOTATRIBE_LOGINACTIVITYWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/ActivityDataHandler.h"

class LoginActivityWindow : public IWindow 	,cocos2d::extension::CCTableViewDataSource
	,cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
			udBG1 = 0,
			udTABLE,
			udTABLECELL,
		};

	enum{
		udCELLBG,
		udTODAYNODE,
		udTODAYTTFNODE,
		udGETBTNNODE,
		udGETBTNTTFNODE,
		udGETEFFECTNODE,
		udTIMETTF,
		udLOGINREWARDTTF,
		udCELLREWARDOBJ1,
		udCELLREWARDOBJ2,
		udCELLREWARDOBJ3,
		udCELLREWARDOBJ4,
		udCELLREWARDOBJ5,
	}CELL;
private:
	int m_CurWindowActiviId;
public:
	LoginActivityWindow();
	virtual ~LoginActivityWindow();
public:
	cocos2d::extension::CCTableView* m_pTableAttachment;    //CCTableView�ؼ�
	cocos2d::CCSize m_szCellGift;	//������С
private:
	inline void _initLayout();
	inline void _initControl();
	inline void _initCell();
	inline void _mapCellItemBtn(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setTableView(); //����TableView
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(unsigned int idx,cocos2d::extension::CCTableViewCell* cell);
	
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
		��ʾ�׳�����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		�����׳�����¼�����
	*/
	inline void  OnHideWindowEventHandler(std::list<std::string>& paramList);
	/*
		�����׳�����¼�����
	*/
	inline void  OnUpdateWindowEventHandler(std::list<std::string>& paramList);
private:
  /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
public:
	void On_Click_Get_Enevnt(cocos2d::CCObject* pSender);
	void On_Click_RewardInfo(cocos2d::CCObject* pSender);
};


#endif