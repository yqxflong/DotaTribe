#include "../include/IWindow.h"
 
#ifndef  _DOTATRIBE_ARENAREWARD_H_
#define  _DOTATRIBE_ARENAREWARD_H_

////////////////////////////////////////////////////////////////
//Name:	 ArenaRewardWindow
//Auchor: 	xiaobo.wu
//Func:	 ��������������
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include  "IWindow.h"
#include   "../include/UIViewDataManger.h"
#include   "../include/CMenuItemSprite.h"
#include   "../include/ArenaInfoDataHandler.h"
#include   "../include/CTimeLabel.h"
#include   <string>
 
class ArenaRewardWindow : public IWindow, public  cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate ,public CTimerEventProtocol
{ 
public: 
	//��UI��������
	enum
	{ 
		_ARENAREWARD_BG_TAG_,
		_ARENAREWARD_CLOSE_BTN_TAG_,
		_ARENAREWARD_TITLE_TAG_,
		_ARENAREWARD_LEFT_TITLE_TAG_,
		_ARENAREWARD_LEFT_TABLE_TAG_,
		_ARENAREWARD_LEFT_CELL_TAG_,
		_ARENAREWARD_RIGHT_RANK_LABLE_TAG_,
		_ARENAREWARD_RIGHT_RANK_VALUE_TAG_,
		_AREWAREWARD_RIGHT_SEGMENT_1_TAG_,
		_ARENAREWARD_RIGHT_COMBAT_RECORD_LABLE_TAG_, 
		_ARENAREWARD_RIGHT_COMBAT_RECORD_CONTENT_TAG_,
		_ARENAREWARD_RIGHT_ODDS_LABLE_TAG_,
		_ARENAREWARD_RIGHT_ODDS_CONTENT_TAG_,
		_ARENAREWARD_RIGHT_SEGMENT_2_TAG_,
		_ARENAREWARD_RIGHT_TITLE_TAG_,
		_ARENAREWARD_RIGHT_OBJ_1_TAG_,
		_ARENAREWARD_RIGHT_NUM_1_TAG_,
		_ARENAREWARD_RIGHT_OBJ_2_TAG_,
		_ARENAREWARD_RIGHT_NUM_2_TAG_,
		_ARENAREWARD_RIGHT_REWARD_TBN_TAG_,
		_ARENAREWARD_RIGHT_REWARD_LABLE_TAG_,
		_ARENAREWARD_RIGHT_REWARD_TIME_TAG_,
		_ARENAREWARD_RIGHT_REWARD_TIPS_TAG_,
		_ARENAREWARD_GRAP_COLOR_TAG_,
		_ARENAREWARD_GROW_TAG_,
		_ARENAREWARD_GROW_TAG_ARROWMOVE_,
	}; 
	enum
	{
		_CHANLLENGE_CELL_BG_TAG_,
		_CHALLENEGE_REWARD_OBJ_TAG_,
		_CHALLENEGE_REWARD_CONTENT_TAG_,
		_CHALLENEGE_TASK_CONTENT_BEFOR_TAG_,
		_CHALLENEGE_TASK_CONTENT_FOLLOW_TAG_,
		_CHALLENEGE_REWARD_BTN_TAG_,
		_CHALLENEGE_REWARD_LABEL_TAG_,
	};
	ArenaRewardWindow();
	virtual ~ArenaRewardWindow(); 
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

	/*
	����UI�ؼ�
	*/
    virtual    void    LoadUIControl();

	/*
	���ڴ�����
	*/
	void    InitData();

	/*
	�����ڴ�����
	*/
	void    DestroyData();

  
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		������ʾʱ��֪ͨ
	*/
	void			   OnShowWindowEventHandler(std::list<std::string>& paramList);
 
	/*
	    ��ť��Ӧ�¼�����
	*/
	void			   CommonMenuSelector(cocos2d::CCObject * pSender);

	/*
	  Table Cell ��ť�ص��¼�
	*/
	void			   CommonCellMenuSelector(cocos2d::CCObject * pSender);

	/*
		��UI��ť�¼�
	*/
	void			   InitBindMenuSelector();
	 
	/*
		���ô���
	*/
	void			   SetTableView();

	/*
		�����б�����
	*/
	void			   CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);
		
	/*
		�����б���������
	*/
 	void			   SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	/*
		����ʱlabel�ص�
	*/
	virtual   void	   TimerEventHandler(int eventType,std::string attachParam);
	 
private:
	/*
	 TableView��֪ͨ�¼�
	*/  
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private: 
	/*
	   ˢ��tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		 tb->reloadData();
	     tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}

	void  updateUIWithData();

	void  updateRankRewardData();

	void  dispatchReceiptCode(int receiptCode);

	void  showRewardMenuItem(int bgIndex,int iconIndex,cocos2d::CCNode * pParent,PRewardItemNode pRewardItemNode);
	void  showRewardSpriteItem(int bgIndex,int iconIndex,cocos2d::CCNode * pParent,PRewardItemNode pRewardItemNode);

private:
	cocos2d::CCNode	 *				   m_pViewRoot;
	cocos2d::extension::CCTableView *  m_pTable; 
	cocos2d::CCSize					   m_szCELL;
	bool							   m_bScrollEnd;
	ArenaRewardData *				   m_pArenaRewardData;
	int								   m_nMaxRewardSize;
	unsigned int					   m_nLastRequestCellIndex;
};

#endif
