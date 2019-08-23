//Name : StrengthenWindow
//Function : װ����һϵ��ǿ��
//Author : ��ǿ

#ifndef _DOTATRIBE_StrengthenWindow_H_
#define _DOTATRIBE_StrengthenWindow_H_

#include "../include/IWindow.h"
#include "../include/SubView.h"

//ҳǩ����
static int ESTREN_TAB1=1;
static int ESTREN_TAB2=2;
static int ESTREN_TAB3=3;

class CMenuItemSprite;
class BagEquipData;
class StrengthenWindow : public IWindow
						,public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	enum{
		kBG,
		kBG_2,
		kARROW_UP,
		kARROW_UPMOVE,
		kARROW_DOWN,
		kARROW_DOWNMOVE,
		kDECORATION,
		kHELP,
		kCLOSE,
		kDIAMONDBAR,
		kGOLDBAR,
		kDIAMOND_LABEL,
		kGOLD_LABEL,
		kTAB_1,
		kTAB_1_LABEL,
		kTAB_2,
		kTAB_2_LABEL,
		kTAB_3,
		kTAB_3_LABEL,
		kTAB_4,
		kTAB_4_LABEL,
		kTABLE,
		kCELLNODE,
		kTOGGLE,
		kTOGGLEBAR,
		kTOGGLE_LABEL,
		kEMPTY_LABEL,
	};
	enum{
		kCELL_BGBTN,
		kCELL_EBOARD,
		kCELL_EQUIPED,
		kCELL_ENAME,
		kCELL_STAR,
	};
	int m_nCurTab;		//��ǰѡ��Tab==ö���е�Tab
	HLSubView* m_pSubView;
	const int m_nSVZorder;
	int m_nBackWindow;
	std::string m_strParam1;
	cocos2d::CCSize m_szCell;		//cell��С
	cocos2d::extension::CCTableView* m_pTable;		//���װ���б�
	bool m_bIsOnlyShowEquiped;		//��¼�Ƿ����ʾ��װ��
	int m_nLastCellIDX_tab1;				//��¼�ϸ�cell=tab1
	int m_nLastCellIDX_tab2;				//��¼�ϸ�cell=tab2
	int m_nLastCellIDX_tab3;				//��¼�ϸ�cell=tab3
	int m_nLastCellIDX_tab4;				//��¼�ϸ�cell=tab4

	int m_nLastSelectEquipId1;
	int m_nLastSelectEquipId2;
	int m_nLastSelectEquipId3;
	int m_nLastSelectEquipId4;

	int m_HeroIndex;
	//��¼�ϴη��ĸ���ҳ���equipID
	int m_nLastEquipID_ToSubView;
	bool m_bIsForceNotifySubView;		//�Ƿ�ǿ��֪ͨ��ҳ��

	bool m_bShowIsEnd;		//��ʾ����

public:
	enum{
		ESEQUIPLVUP,		//װ������
		ESEQUIPMAKEPROGRESS,	//װ������
		ESEQUIPTRAIN,			//װ��ϴ��
	};
	StrengthenWindow();
	virtual ~StrengthenWindow(){};

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

protected:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		��ʾ����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		��������¼�����
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

private:
	inline void _initLayout();
	inline void _initEmptyLabel();
	inline void _mapBtn();
	inline void _mapTable();
	inline void _resetAllHighlight();
	inline void _highlightTabItem(unsigned int idx);
	inline void _loadSubView(unsigned int idx);
	inline void _selectTabItem(unsigned int idx);
	
	//begin:cell
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(int idx,cocos2d::extension::CCTableViewCell* cell);
	//end


	inline void _toggleSeleted(bool isselected);
	inline void _cellSelected_Tab1(CMenuItemSprite* cc);
	inline void _cellSelected_Tab2(CMenuItemSprite* cc);
	inline void _cellSelected_Tab3(CMenuItemSprite* cc);
	inline void _cellSelected_Tab4(CMenuItemSprite* cc,bool bNofity=false);

	//begin:handle equiplist
	inline void _reloadEquipListByTab();
	inline void _reloadEquipList_lvup();
	inline void _reloadEquipList_lvup_afterResult();
	inline void _reloadEquipList_progress();
	inline void _reloadEquipList_progress_afterResult();
	inline void _reloadEquipList_train();
	inline void _reloadEquipList_Recast();
	inline void _clearEquipList();
	//end

	//refresh Money and diamond
	inline void _mapMoneyAndDiamond();

	/*
		�ָ����ڲ���
	*/
	inline void _resetWindowParams();

	/*
		���б�ʱ֪ͨ��ҳ��
	*/
	inline void _notifySubViewWhenEmpty();

	/*
		���б�ı����Ĭ��ʱ֪ͨ��ҳ��
	*/
	inline void _notifySubViewDefault();

	/*
		֪ͨ��ҳ��ѡ�е�װ��id
	*/
	inline void _notifySubViewEquipID(int equipID);

	/*
		ˢ��װ���б��Ҿ���ûѡ��װ�������
	*/
	void _refreshEquipListAndCheckEquipSelected();

	/*
		ˢ��װ���б��Ҿ���ûѡ��װ�������
		#�ָ�ƫ����
	*/
	void _refreshEquipListAndCheckEquipSelected_setOffSet();

	/*
		����ûѡ��װ�������
	*/
	void _checkEquipSelected();

	/*
		������װ���б��Ƿ�Ϊ��
	*/
	void _checkEquipListIsEmpty(int equipID);
	
	/*
		��ȡҪ��ʾ������
	*/
	std::string _getShowText(int index);

	/*
	    ǿ��ȡ����ѡ��װ����ť
		*/
	void  _forceChancelEquipState();

	void  _activeFirstCellForRecast();
protected:
	/*
		��ť�¼�
	*/
	void On_Click_Event(cocos2d::CCObject* pSender);
	/*
		tab�ص�
	*/
	void On_Tab_Selected(cocos2d::CCObject* pSender);

	/*
		Cell ѡ��ص��¼�
	*/
	void On_Cell_Click_Event(cocos2d::CCObject* pSender);

protected:
	  /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     * 
     * @return number of cells
     */
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	bool					m_bScrollBegin;
	bool					m_bScrollEnd;
	cocos2d::CCPoint		m_offSetPoint;
};


#endif