//Name��PESEquipWindow
//Function����Ӣ��װ��
//Written By����ǿ
//AnchorPoint:  (0.5,0.5) can not change

#ifndef  _DOTATRIBE_PESEQUIPSUBVIEW_H_
#define  _DOTATRIBE_PESEQUIPSUBVIEW_H_

#include "../include/HeroWindowSubView.h"
#include "../include/BagEquipDataHandler.h"
#include "spine/spine-cocos2dx.h"
#include "../include/CTouchSprite.h"
#include "../include/CMenuItemSprite.h"
#include "../include/DTEquipBoard.h"

struct _EQUIPITEM_{
	int starCount_;
	BagEquipData *equipdata_;

	_EQUIPITEM_(){
		starCount_=-1;
		equipdata_=NULL;
	}
};

class HEHeroPropertyNode;

class PESEquipSubView :public HeroWindowSubView,public cocos2d::extension::CCTableViewDataSource
	,public DTEquipBoardDelegate
{
private:
	enum{
		kBG,
		kBTN_STRENGTHEN_BTN,
		kBOTTOM_NODE,
		kBOARD_1,
		kBOARD_2,
		kBOARD_3,
		kBOARD_4,
		kBOARD_5,
		kBOARD_6,
		kBOARD_7,
		kBOARD_8,
		kHERO,
		kSTAR,
		kNAME,
		kEQUIPCOUNT_BG,
		kEQUIPCOUNT,
		kLINKNODE,	//��װ������ռλ��
		kTABLE,
		kTABLECELL_SUBTITLE,
		kTABLECELL,
	}WINDOW;
	enum{
		//begin:Equip
		kCELLBG,
		kCELLBOARD,
		kCELLEQUIPNAME,
		kCELLMAINPROP,		//������
		kCELLEQUIPSCOREVALUE,
		kCELLBTN,
		kCELLBTN_LABEL,
		kCELLSCOREARROW,		//ս����ͷ
		kCELLTYPE,		//װ������
		//end
		//begin:Title
		kCELL_TITLE_BG,			//����
		kCELL_TITLE_STAR,		//�Ǽ�
		//end
	};

	//@��ǰӢ��idx
	int m_nCurHeroIdx;
	HEHeroPropertyNode* m_pBottomNode;
	cocos2d::CCNode* m_pLinkNode;
	cocos2d::extension::CCTableView* m_pTable;		//�ұ�װ���б����
	//
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//Ӣ�۽�ɫ
	cocos2d::CCSize m_szCELL_ITEM;			//װ����cell��С
	cocos2d::CCSize m_szCELL_TITLE;			//title��cell��С
	cocos2d::CCPoint m_cpTableCurOffset;		//��ǰ�б��offset
	float m_fTableCurHeight;		//��ǰ�б�����ݸ߶�
	std::vector<_EQUIPITEM_> m_vecList;		//local�ı���װ������
public:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
	virtual void onChangeTabIndex(int idx);
public:
	PESEquipSubView();
	virtual ~PESEquipSubView(){};
	/*
		װ��һ��װ��
	*/
	void equipEquipmentByID(int id,int heroIdx=0);		//instance id

private:		
	void _initLayout();			//��ʼ�����֣���Ҫ��create֮�����
	void _mapBtn();
	void _mapTable();
	//@����idxˢ�½����ӦӢ������
	void _refreshHeroByIdx(int idx);
	void _refreshData();
	void _refreshBagEquip();
	void _refreshEquipCount();
//begin:Ӣ������
	void _refreshHeroNameAndStarLv(int idx=0);
	void _refreshRoleEquip(int idx=0);
	void _refreshHeroShape(int idx=0);
//end
	//
	void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	//
	void _setTableCell(int idx,cocos2d::extension::CCTableViewCell* cell);
	void _setCellEquip(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipType(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipName(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipMainProp(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipScore(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipScoreArrow(BagEquipData* ed,cocos2d::CCNode* cell);
	void _setCellEquipBtn(int idx,BagEquipData* ed,cocos2d::CCNode* cell);
	void _mapCellBtn(cocos2d::CCNode* cell);
	//
	//begin:setcell for expball
	void _setCellExpBall_Descrip(BagEquipData* ed,cocos2d::CCNode* cell);
	//end
	//
	//
	//@��ʾӢ����ϸ��Ϣ
	void _showHeroDetailNode();

	//@����Ӣ����Ϣģ����Ϣ
	void _refreshHeroDetailNodeInfo(int tabidx);

	//���������ж��װ��
	void _request4leaveEquip(int etype);

	//����װ��id�����ﻻװ
	void _equipEquipment(int idx);

	/*
		ˢ�¿�װ������
	*/
	void _refreshLinkNode();

	/*
		Cell ��ʾtitle
	*/
	void _cell_showTitle(cocos2d::CCNode* cell);

	/*
		Cell ��ʾװ��
	*/
	void _cell_showEquip(cocos2d::CCNode* cell);

	/*
		Cell ��ʾ������
	*/
	void _cell_showExpBall(cocos2d::CCNode* cell);


	/*
		ˢ��װ���б����Ǽ�סԭ��λ��
	*/
	void _refreshTableViewButRememberOldPos();
	
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
public:
	void On_Click_Event(cocos2d::CCObject* pSender);

	/*
		ǿ����ť
	*/
	void On_Click_Streng_Event(cocos2d::CCObject* pSender);
	/*
		װ��icon����ص�
	*/
	virtual void CallBack_ClickEquip(int type,int equipID);

	//װ����ť����¼�
	void On_Cell_Click_Event(cocos2d::CCObject* pSender);

	/*
		ˢ������װ��
	*/
	void On_RefreshRoleEquip();

	/*
		ˢ��װ���б�
	*/
	void On_RefreshEquipList();

	/*
		Tips�ص�װ��
	*/
	void On_Tips_CallBack_Equip(int idx);
	/*
		Tips�ص�ж��
	*/
	void On_Tips_CallBack_Disboard(int type);

	/*
		�����ڵ�֪ͨ
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
};


#endif
