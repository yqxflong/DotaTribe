
#ifndef _DOTATRIBE_MAINTASKWINDOW_H_
#define _DOTATRIBE_MAINTASKWINDOW_H_

#include "../include/IWindow.h"
#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/NFControlsManager.h"
#include "../include/MainTaskDataHandler.h"
using  namespace  cocos2d;
using namespace cocos2d::extension;

class MainTaskWindow : public IWindow, public  cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate
{
private:
	enum{
	    _TASKUI_BG_TAG_,
		_TASKUI_CLOSE_BTN_TAG_,
		_TASKUI_TASK_TABLEVIEW_TAG_,
		_TASKUI_TASK_CELL_TAG_,
		_TASKUI_TSAK_TILE_BG_TAG_,
		_TASKUI_TASK_TILE_LABEL_TAG_,
		_TASKUI_TASK_CONTENT_TAG_,
		_TASKUI_TASK_GOTO_BTN_TAG_,
		_TASKUI_REWARD_TILE_BG_TAG_,
		_TASKUI_REWARD_LABEL_TAG_,
		_TASKUI_REWARD_MARK_TAG_,
		_TASKUI_REWARD1_OBJ_TAG_,
		_TASKUI_REWARD1_NUM_TAG_,
		_TASKUI_REWARD2_OBJ_TAG_,
		_TASKUI_REWARD2_NUM_TAG_,
		_TASKUI_REWARD3_OBJ_TAG_,
		_TASKUI_REWARD3_NUM_TAG_,
		_TASKUI_REWARD_BTN_TAG_,
		_TASKUI_REWARD_CONTENT_TAG_,
		_TASKUI_DIAMOND_BG_TAG_,
		_TASKUI_DIAMOND_NUM_TAG_,
		_TASKUI_GOLD_BG_TAG_,
		_TASKUI_GLOG_NUM_TAG_,
		_TASKUI_GRAY_COLOR_LAYER_TAG_,
		_TASKUI_BG_MARK_TAG_,
		_TASKUI_BG_IMAGE_TAG_,
		_TASKUI_BG_GOTO_BTN_EFFECT_TAG_,
	};

	enum
	{
		_TASK_CELL_BTN_TAG_,
		_TASK_CELL_CONTENT_TAG_,
	};
public:
	MainTaskWindow();
	virtual ~MainTaskWindow();

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
	void    CommonBtnCallBackHandler(cocos2d::CCObject * pSender);
	void    TaskCellClickHandler(cocos2d::CCObject * pSender);
	void	setMenuSprite(CMenuItemSprite* pMenuItem,std::string nameImageName);

	//��Ʒ����¼�
	void OnAwardClicked(cocos2d::CCObject* pSender);
protected:
	/*
	 Table View ��ؽӿ�
	*/
	//��TableView
	void  SetTableView();
	 
	/*
	  ����TableCell�е�����
	*/
	virtual    void    CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell);

	/*
      ������������Cell������
	*/
	virtual    void    SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex);

	/*
	����Cell�ĸ߿�
	*/
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);

	/*
	���ָ��Cell
	*/
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);

	/*
	����Cell����
	*/
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	/*
	����Cell����¼�
	*/
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){}


	virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){}

 
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){}

	virtual void ActiveCellItemWithCellIndex(int cellIndex);
	  
	/*
	������ϻص�
	*/
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};

	/*
	������ϻص�
	*/
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

	/*
	ˢ��TableView
	*/
	void  refreshTableView(cocos2d::extension::CCTableView* tb) const 
	{
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
	void  refreshTableViewOffCount(cocos2d::extension::CCTableView* tb,int interCount) const 
	{
		tb->reloadData();
		tb->setContentOffset(ccp(0,-m_szCELL.height*interCount));
	}
protected:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		��ʾ����¼�����
	*/
	inline void OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		��������¼�����
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);
private:
	inline void		initUILayout();
	inline void		mapStaticBtn();
	inline void		attachTaskData();
	inline void     bindSelectorBtnByTag(int nodeTag);
	inline void     BindSelectorForTouchSprite(int signID);
	inline void		DispatchUpdateEvent(int updateAttachParam);
	inline void     HideAllTaskContent();

private:
	/*
		�������������ݵĸ��½������
	*/
	void Function_GetMainTaskData();
 
	/*
	  �ر�
	*/
	void  CloseHanlder();

	/*
	��ȡ����
	*/
	void  RewardHandler();

	/*
	 ����Cell״̬
	*/
	void  SetCellBtnState(CCTableViewCell * pTableCell,unsigned int cellIndex);
	/*
	 ����Cell״̬
	*/
	bool  ActiveCellBtnState(cocos2d::CCObject * pSender);

	void  SetMenuState(bool isVisiable,int nodeTag);

	void  ShowTaskLayerWithCellBtn();
	 
	void  ShowGuidWithTaskItem(MainTaskItem * pTaskItem);

	void  ShowTaskRewardInfo(MainTaskItem * pTaskItem);
	 
	void  SetNodeVisiableByTag(bool isVisiable,int nodeTag);

	void  GetRewardBgAndIconTagByIndex(size_t & index,int & bgIconTag,int & IconTag,int & numTag);

	void  ShowStartTaskLayer();

	void  GoToGuidModuleHandler();

	void  DispatchSwitchModule(int moduleType, std::string param);

	void  UpdateTaskDataAndUI(bool bhadNextTask);

	void  UpdateDiamondAndGold();

private:
	cocos2d::extension::CCTableView *  m_pTable;
	cocos2d::CCSize					   m_szCELL;
	int								   m_nActiveTaskIndex;
	int								   m_nBackWindow;				//����ҳ��
	cocos2d::CCNode*				   m_pRoot;						//���ڸ��ڵ�
	MainTaskData *					   m_pMainTaskData;				//�����ڴ����ݾ��
	MainTaskItem *					   m_pActiveTaskItem;			//��ǰ����Ļ��;
	int								   m_nStartFinishCellIndex;		//��ȡ�����Լ���������Cell����
	bool							   m_isNeedToShowTips;
	   
};


#endif