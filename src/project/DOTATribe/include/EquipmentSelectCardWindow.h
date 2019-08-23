//Name��EquipMentSelectWindow
//Function��ѡ��װ���ز�
//Written By����ǿ

#ifndef  _DOTATRIBE_EQUIPMENTSELECTCARDWINDOW_H_
#define  _DOTATRIBE_EQUIPMENTSELECTCARDWINDOW_H_

#include "../include/IWindow.h"
#include <cocos-ext.h>
#include "../include/EquipmentLvUpDataHandler.h"

class BagEquipData;
class EquipmentSelectCardWindow:public IWindow
	, cocos2d::extension::CCTableViewDataSource
{
private:
	enum{
		udGRAYLAYER,
		udBG,
		udTITLE,
		udCLOSEBTN,
		udCONFIRMLB,
		udCONFIRMBTN,
		udTOGGLE1,
		udTOGGLE2,
		udTOGGLE3,
		udTOGGLE1_BG1,
		udTOGGLE1_BG2,
		udTOGGLE1_BG3,
		udTOGGLE1_BG1_LABEL,
		udTOGGLE1_BG2_LABEL,
		udTOGGLE1_BG3_LABEL,
		hTABLE,
		hTABLECELL,
		hCOUNTER,
		hCOUNTERBG,
		hCOUNTER_TITLE,
	}WINDOW;
	enum{
		cellBG1,
		cellBG2,
		cellBG3,
		cellITEMBOARD1,
		cellITEMBOARD2,
		cellITEMBOARD3,
		cellNAME1,
		cellNAME2,
		cellNAME3,
		cellTYPE1,
		cellTYPE2,
		cellTYPE3,
		cellSELECT1_BG,
		cellSELECT2_BG,
		cellSELECT3_BG,
		cellSELECT1,
		cellSELECT2,
		cellSELECT3,
		cellSTAR1,
		cellSTAR2,
		cellSTAR3,
	}CELL;

	cocos2d::CCNode * m_pWRootNode;	//��ǰ���ڽڵ㣬���ڹ��ص�ǰ����
	int m_nShowWindow;			//�뿪ʱȥ�ĸ�window

	cocos2d::CCSize m_nCellSize;	//cell�Ĵ�С
	cocos2d::extension::CCTableView* m_pTable;

	std::vector<EquipCardsStructure> m_vecCardList;

	int  m_nCurCount;//��ǰѡ�е�����
	int m_nTotalCount;//����

public:
	EquipmentSelectCardWindow();
	virtual ~EquipmentSelectCardWindow(){};

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

private:
	/*
		��ʾ����¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		��������¼�����
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);

private:
	inline void _initData();
	inline void _initLayout();
	inline void _mapTable();
	inline void _mapBtn();

	void _createTableCell(cocos2d::extension::CCTableViewCell * cell);

	void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);

	void _setBlockInfo(cocos2d::CCNode * block, int idx);

	void _setBlockStar( int key,cocos2d::CCNode * block,BagEquipData* bb);

	void _setSelectPicVisible(cocos2d::CCNode * cell, int idx, bool visible);

	

	void _setBlockVisiable(cocos2d::CCNode * block, int blockidx, bool visiable);

	//��ȡ��ǰѡ�еĸ���
	void _checkCurTickCount();
	//��ʾ��ǰѡ�еĸ��� 
	void _showCurTickCount();

	//���ƹ���
	void On_Toggle_Click_Event(cocos2d::CCObject * pSender);
	/*
		���ȫѡ״̬
	*/
	inline void _checkTickAll();

	/*
		cell��block����Ӧ����
	*/
	void On_Click_Block(cocos2d::CCObject * pSender);

	void _setToggleSelect(int key, bool selected);

private:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

protected:
	virtual void On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
