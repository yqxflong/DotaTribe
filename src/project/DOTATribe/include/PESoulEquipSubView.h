
#ifndef  _DOTATRIBE_PESOULEQUIPSUBVIEW_H_
#define  _DOTATRIBE_PESOULEQUIPSUBVIEW_H_

#include "../include/HeroWindowSubView.h" 
#include "spine/spine-cocos2dx.h" 
#include "../include/CMenuItemSprite.h"
#include "../include/DTEquipBoard.h"
#include "../include/SubView.h"
#include "../include/RoleSoulsDataHandler.h"
	

 
class PESoulEquipSubView :public HeroWindowSubView,public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
		kBG,
		kBOTTOM_NODE,
		kBOARD_1,
		kBOARD_2,
		kLEVEL_BG_2,
		kLEVEL_VALUE_2,
		kBOARD_3,
		kLEVEL_BG_3,
		kLEVEL_VALUE_3,
		kBOARD_4, 
		kLEVEL_BG_4,
		kLEVEL_VALUE_4,
		kHERO,
		kSTAR,
		kNAME, 
		kTABLE, 
		kTABLECELL,  
		kPOWERBG,
		kPOWERBTN,
		kPOWEELABEL,
		kQUCIKBG,
		kQUCIKBTN,
		kQUCIKLABEL,
		kINTELIGENBG,
		kINTELIGENBTN,
		kINTELIGENLABEL,
		kSoulEmptyTips,
		kSoulChallengeImage,
		kSoulChallengeLabel,
		kSoulChallengeBtn,
	}WINDOW;
	enum{
		//begin:Equip
		kCELLBG,
		kCELLBOARD,
		kCELLTALENTNAME,
		kCELLATRIBUTENAME,
		kCELLEQUIPBTN,
		kCELLEQUIPLABEL,
		kCELLUPSOULLEVELBTN,
		kCELLUNACTIVITTF,
		kCELLUNACTIVITITLE,
		//end
	};
	SubView* m_pBottomNode; 
	cocos2d::extension::CCTableView* m_pTable;					//�ұ�װ���б���� 
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//Ӣ�۽�ɫ
	cocos2d::CCSize m_szCELL_ITEM;								//װ����cell��С  
public:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
	virtual void onChangeTabIndex(int idx);
public:
	PESoulEquipSubView();
	virtual ~PESoulEquipSubView(){};  
public:
	//@��ǰӢ��idx
	int m_nCurHeroIdx;
private:
	void _refreshData(int idx);				 //��ʼ��һЩ����
	void _initLayout();				 //��ʼ�����֣���Ҫ��create֮�����
	void _mapBtn();					 //UI��ť�¼���
	void _createTableView();			 //����TableView
	void	_refreshHeroShape(int idx = 0);
	void _refreshHeroNameAndStarLv(int index = 0); //ˢ��Ӣ�����ƺ��Ǽ�
	//@����idxˢ�½����ӦӢ������
	void _refreshHeroByIdx(int idx);
 
	//��ʾӢ����Ϣ
	inline void _showHeroInfoNode();
	//��ʾӢ����ϸ��Ϣ
	inline void _showHeroDetailNode(); 

	 
	void    _refreshUIWithData();

	void    _showEquipBuffer(char  equipIndex,int uiIndex);
	  
	void    _refreshSwithState();
	
	void    _handlerEquipClick(char equipIndex);

	void    _handlerEquipSoulWithIndex(char equipIndex);

	void    _handlerUnEquipSoulWithCellIndex(int cellIndex);

	void    _handlerUnEquipBufferTips(int cellIndex);
	 
	void    _dispatchEventHandler(int receiptCode);

	void    _handlerEquipBufferTips(int souleBufferID,int type = 0);

	void    _handlerEquipSoule(int soulBufferID);

	void    _handlerUpSoulLevel(int cellIndex);
private:

	void    createTableCell(cocos2d::extension::CCTableViewCell * pTableCell);

	void    setTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	void    setCellWithData(IHeroSoulItem * pSoulItem,cocos2d::extension::CCTableViewCell * pTableCell,int cellIndex,int type);

	void    mapCellBtn(cocos2d::CCNode* cell);

	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private: 
	void _refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		 tb->reloadData();
	     tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	} 
	void  _refreshEmptySoulTips(bool isSoulEmpty);
public: 
	/*
		�����ڵ�֪ͨ
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);

	/*
	   ҳ����ϸ��Ϣ����¼�
	*/
	void  On_Tab_Click_Event(cocos2d::CCObject* pSender); 
	void  On_Click_Event(cocos2d::CCObject * pSender); 
	void  On_Cell_Click_Event(cocos2d::CCObject * pSender);
	void  On_Cell_Tips_Event(cocos2d::CCObject * pSender);
	void  On_Cell_UpSoulLevel_Event(cocos2d::CCObject * pSender);
private:
	std::vector<IHeroSoulItem *> m_vAllUnESoulBufferVector;				//����ս�����
	std::vector<IHeroSoulItem *> m_vPowerUnESoulBufferVector;			//��������ս�����
	std::vector<IHeroSoulItem *> m_vQuickUnESoulBufferVector;			//��������ս�����
	std::vector<IHeroSoulItem *> m_vInteligenceUnESoulBufferVector;		//��������ս�����
	std::vector<IHeroSoulItem *> m_vEquipSoulBufferVector;				//��װ������
	//////////////////////////////////////////////////////////////////////////
	IRoleSoulsEquipInfo *		 m_RoleSoulsEquipInfo;					//װ��װ��������

	IByte						 m_nCurSoulBufferType;					//��ǰս��bufferType
	 
	bool						 m_bPowerSwitchOn;
	bool						 m_bQucikSwitchOn;
	bool						 m_bInteligenceSwitchOn;
	
	int							 m_nPlayerLevel;
	int m_ArraySoulType[4];
};


#endif
