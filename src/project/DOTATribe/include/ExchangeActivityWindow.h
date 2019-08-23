#ifndef   _DOTATRIBE_EXCHANGEACTIVITYWINDOW_H_
#define   _DOTATRIBE_EXCHANGEACTIVITYWINDOW_H_
   
#include   <cocos2d.h>
#include   "../include/IWindow.h"
#include   "../include/DOTATribeApp.h"
#include   "../include/CMenuItemSprite.h"
#include   "../include/CPublicVarReader.h"
#include   "../include/ActivityDataHandler.h" 
#include   "../include/CTimeLabel.h" 

 

class ExchangeActivityWindow :public IWindow, public  cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate,public CTimerEventProtocol
{
private: 
	//主界面UI索引
	enum
	{
		 _EXCHANGEACTIVITY_BG_MARK_TAG_,
		 _EXCHANGEACTIVITY_COUNTDOWN_LABEL_TAG_,
		 _EXCHANGEACTIVITY_BG_TAG_,
		 _EXCHANGEACTIVITY_TABEL_TAG_,
		 _EXCHANGEACTIVITY_CELL_TAG_, 
		 _TEMP_BTN_TAG_,
	}; 
	//子CellUI索引
	enum
	{
		_EXCHANGE_CELL_BG_TAG_,
		_EXCHANGE_CELL_ITEM_1_TAG,
		_EXCHANGE_CELL_ITEM_1_NUM_TAG, 
		_EXCHANGE_CELL_ITEM_2_TAG,
		_EXCHANGE_CELL_ITEM_2_NUM_TAG, 
		_EXCHANGE_CELL_ITEM_3_TAG,
		_EXCHANGE_CELL_ITEM_3_NUM_TAG, 
		_EXCHANGE_CELL_REWARD_ITEM_TAG,
		_EXCHANGE_CELL_REWARD_NUM_TAG,
		_EXCHANGE_CELL_EXCHANGE_BTN_TAG,
		_EXCHANGE_CELL_EXCHANGE_LABEL_TAG,
		_EXCHANGE_CELL_EXCHANGE_LAST_LABEL_TAG,
		_EXCHANGE_CELL_EXCHANGE_VIP_TIPS_TAG,	 
	};
public:
	ExchangeActivityWindow();
	virtual ~ExchangeActivityWindow(); 
	virtual bool    Init();
	virtual bool    Load();
	virtual void    Tick();
	virtual void    Destroy();
	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
	virtual void	TimerEventHandler(int eventType,std::string attachParam);
private:
	/*
	初始UI
	*/
	void   LoadUILayer(); 
 
	//绑定公共按钮事件通知
	void   CommonSelectorHandler(cocos2d::CCObject * pSender); 
	/*
	 显示事件通知
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
  
	/*
	 设置窗口
	*/
	void			   SetTableView();

	/*
	 创建列表子项
	*/
	void			   CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);
		
	/*
	 设置列表子项内容
	*/
 	void			   SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);
  
private:
	/*
	 TableView的通知事件
	*/  
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
 
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx); 
 
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
 
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

private: 
	/*
	   刷新tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb) const ;
	
	/*
	   分发更新消息
	*/
	void  dispatchReceiptCode(int receiptCode);

	/*
	获取兑换项目的个数
	*/
	unsigned int  getExchangeItemsCount();

	/*
	获取奖励信息
	*/
	void  exchangeItemInfoBtnSelectorHandler(cocos2d::CCObject * pSender);

	/*
	兑换按钮事件处理
	*/
	void  exchangeBtnSelectorHandler(cocos2d::CCObject * pSender);

	/*
	刷新页面
	*/
	void  refreshUIWithExchangeInfoData(); 

	void  showNeedItemInfoWithData(int cellIndex,int cellItemIndex,int iconIndex,int labelIndex,
		TemplateItemInfoData * pTemplateInfoData,cocos2d::extension::CCTableViewCell * pCell);

	void  showTargetItemInfoWithData(int cellIndex,int cellItemIndex,int iconIndex,int labelIndex,
		RewardItemNode * pItemInfoData,cocos2d::extension::CCTableViewCell * pCell);
	 
private: 
	cocos2d::extension::CCTableView *  m_pTable; 
	cocos2d::CCSize					   m_szCELL;  
	cocos2d::CCPoint				   m_offSetPoint; 
	ExchangeInfoData  *				   m_pExchangeInfoData;
	bool							   m_bActivityEnd;
	unsigned short					   m_nActivityItemID;
}; 


#endif