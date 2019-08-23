#ifndef  _DOTATRIBE_LEVELUPREWARD_ACTIVITY_WINDOW_H_
#define  _DOTATRIBE_LEVELUPREWARD_ACTIVITY_WINDOW_H_

#include  <cocos2d.h>
#include "../include/IWindow.h"
#include "../include/DOTATribeApp.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/ActivityDataHandler.h"

 

class LevelUpRewardActivityWindow :public IWindow, public  cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
private: 
	//主界面UI索引
	enum
	{
		 _LURAW_BG_MARK_TAG_,
		 _LURAW_BG_TAG_,
		 _LURAW_REWARD_TABEL_TAG_,
		 _LURAW_REWARD_CELL_TAG_,
 
	}; 
	//子CellUI索引
	enum
	{
		_LURAW_CELL_BG_TAG_,
		_LURAW_CELL_LEVEL_TAG_, 
		_LURAW_CELL_REWARD_OBJ_1_TAG_,
		_LURAW_CELL_REWARD_OBJ_2_TAG_,
		_LURAW_CELL_REWARD_OBJ_3_TAG_,
		_LURAW_CELL_REWARD_OBJ_4_TAG_,
		_LUEAW_CELL_REWARD_BTN_TAG_,
		_LUEAW_CELL_REWARD_CONTENT_TAG_,
		_LUEAW_CELL_REWARD_EFFECT_TAG_,
	};
private:
	int m_CurWindowActiviId;
public:
	LevelUpRewardActivityWindow();
	virtual ~LevelUpRewardActivityWindow(); 
	virtual bool    Init();
	virtual bool    Load();
	virtual void    Tick();
	virtual void    Destroy();
	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
private:
	/*
	初始UI
	*/
	void   LoadUILayer();
	
	/*
	绑定按钮事件
	*/
	void   BindSelectorForBtn();

	void   CommonSelectorHandler(cocos2d::CCObject * pSender);
	 
	/*
	 显示事件通知
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
	 更新事件通知
	 */
	void   OnUpdateUIHandler(std::list<std::string>& paramList);  

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

	/*
	更新UI处理
	*/
	void			   UpdateUIHandler();
	  
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
	void _refreshTableView(cocos2d::extension::CCTableView* tb) const; 
   
	void  dispatchReceiptCode(int receiptCode);

	unsigned int  getRewardItemCount();

	void  rewardInfoSelectorHandler(cocos2d::CCObject * pSender);

	void  rewardBtnSelectorHandler(cocos2d::CCObject * pSender);

	void  gotRewardUpdateHandler();

private: 
	cocos2d::extension::CCTableView *  m_pTable; 
	cocos2d::CCSize					   m_szCELL; 
	cocos2d::CCPoint				   m_offsetPoint;
	LevelUpRewardData *				   m_pLevelUpRewardData;
	int								   m_nLastPlayerLevel;
	int								   m_nLastRewardLevel;


}; 

#endif