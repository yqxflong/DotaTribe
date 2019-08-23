//Name ; TeamBattleWindow
//Function：组队副本窗口
//Author : fangjun
//Date: 20130918

#ifndef  _DOTATRIBE_TEAMSELECTWINDOW_H_
#define  _DOTATRIBE_TEAMSELECTWINDOW_H_

#include "../include/IWindow.h"
#include "../include/CDragSprite.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
// #include "../include/AnimationEffect.h"
// #include "../include/AnimationFileDataManager.h"

class TeamSelectWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate, CDragSpriteDelegate
{
private:
	enum{
		mBg = 0,
		mQuality,
		mPlayerName,
		mSkinName,
		mLevel,
		mBtlCapa,
		mBtlCapaValue,
		mGoldIcon,
		mPriceValue,
		mHireBtn,
		mHireBtnLabel,
	}MercenaryCell;
	enum{
		sBg = 0,
		sQuality,
		sPlayerName,
		sSkinName,
		sLevel,
		sBtlCapa,
		sBtlCapaValue,
		sLeftTime,
		sLeftTimeValue,
		sCallBtn,
		sCallBtnLabel,
	}SlaveCell;
	enum{
		vBg = 0,
		vTitle,
		vCloseBtn,
		vTabelview,
		vCell,
	}ViewList;
	enum{
		_VIEW_PAGE_SLAVE_ = 0,//奴隶列表
		_VIEW_PAGE_MERCENARY_,//佣兵列表
	}ViewPageKind;
	enum{
		 udBG = 0,//背景
		 udBoardBG,//底板
		 udFUBENNAMETTF,	//副本名字
		 udCLOSEBTN,		//关闭按钮
		 udBEGINBTN,//开始按钮
		 udBEGINTTF,//开始按钮字
		 udLEAVEBTN,//离开按钮
		 udLEAVETTF,//离开按钮字
		 udDESTROYTEAMBTN,//解散队伍按钮
		 udDESTROYTEAMTTF,//解散队伍按钮字
		 udBUILDTEAMBTN,//创建队伍按钮
		 udBUILDTEAMTTF,//创建队伍按钮字
		 udONEMSGBTN,//一键喊话按钮
		 udONEMSGBG,//一键喊话背景，也做成按钮
		 udONEMSGBTNTTF,	//一键喊话按钮字
		 udPLAYERBG1,	//玩家背板1
		 udQUALITY1,//人物头像质量图1
		 udSKINNAME1,//外套名称1
		 udZHANLIVALUE1,//战力值1
		 udPLAYERNAME1,//人物名称1
		 udSOCIAL1,//社会关系1
		 udPLAYERBG2,	//玩家背板2
		 udQUALITY2,//人物头像质量图2
		 udSKINNAME2,//外套名称2
		 udZHANLIVALUE2,//战力值2
		 udPLAYERNAME2,//人物名称2
		 udSOCIAL2,//社会关系2
		 udPLAYERBG3,	//玩家背板3
		 udQUALITY3,//人物头像质量图3
		 udSKINNAME3,//外套名称3
		 udZHANLIVALUE3,//战力值3
		 udPLAYERNAME3,//人物名称3
		 udSOCIAL3,//社会关系3
		 udROMOVEBTN1,//移除按钮1
		 udROMOVETTF1,//移除按钮字1
		 udCHECKBTN1,//查看按钮1
		 udCHECKTTF1,//查看按钮字1
		 udROMOVEBTN2,//移除按钮2
		 udROMOVETTF2,//移除按钮字2
		 udCHECKBTN2,//查看按钮2
		 udCHECKTTF2,//查看按钮字2
		 udROMOVEBTN3,//移除按钮3
		 udROMOVETTF3,//移除按钮字3
		 udCHECKBTN3,//查看按钮3
		 udCHECKTTF3,//查看按钮字3
		 ud1DOWNBTN,		//1向下
		 ud2UPBTN,			//2向上
		 ud2DOWNBTN,		//2向下
		 ud3UPBTN,			//3向上
		 udTableView,
		 udTableCell,
		 udMaskNode,	//弹出的雇佣奴隶和佣兵挂载点
		}Main;
	enum{
		udCELLBG,//CELL底图
		udTEAMLEADER,//队长名字
		udNUM,
		udMEMBERNUM,//队伍玩家数量
		udJOINBTN,//加入按钮
		udJOINTTF,//加入按钮字
	}Cell;

	cocos2d::CCNode* m_pRoot;//窗口根节点
	cocos2d::extension::CCTableView* m_pTeamTable;
	cocos2d::extension::CCTableView * m_pSlaveTable;//弹出窗口slave
	cocos2d::extension::CCTableView * m_pMercenaryTable;//弹出窗口mercenary
	//bool m_bIsNowSlaveTable;//当前是奴隶列表

	cocos2d::CCSize m_szTeamCell;
	cocos2d::CCSize m_szSlaveCell;
	cocos2d::CCSize m_szMercenaryCell;

	cocos2d::CCNode * onekey0;//喊话0
	cocos2d::CCNode * onekey1;//喊话1
	cocos2d::CCNode * onekey2;//喊话文字


	const int _TAG_CHENG_;//tag间隔，只为了三个列表用

public:
	TeamSelectWindow();
	virtual ~TeamSelectWindow();

private:
	inline void _initLayout();
	
	inline void _initData();

	inline void _setTableView();
	inline void _createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell,int idx);

	void _createGrayLayer();
	void _removeGrayLayer();
	inline void _mapBtn();

public:
	void _removeMember(int idx);//移除排第几的队员
	void _checkMemberInfo(int idx);//查看排第几的队员
	void _refreshMyTeamShow();//刷新我所在队伍显示
	void _switchTwoMember(int firstIdx, int secondIdx);
	void _refreshBtnFunc();//刷新界面底部按钮状态

	void _hireSlave();		//雇佣奴隶
	void _hireMercenary();	//雇佣佣兵
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

private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		刷新
	*/
	void OnRefreshWindowEventHandler(std::list<std::string>& paramList);

public:
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};

public:
	/*
		DragSprite覆盖
	*/
	virtual void clickEvent(int idx,int type=0);
	virtual bool containsTheCopy(cocos2d::CCSprite* copy,int type=0);

private:
	/*
		刷新tableview
	*/
	void _refreshTableView(cocos2d::extension::CCTableView* tb)const {
		tb->reloadData();
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
public:
	void On_Btn_Click(cocos2d::CCObject* pSender);

	void On_JoinTeam_Click(cocos2d::CCObject* pSender);

	void On_View_Close_Click(cocos2d::CCObject* pSender);

	void On_Slave_Hire_Click(cocos2d::CCObject* pSender);

	void On_Mercenary_Hire_Click(cocos2d::CCObject* pSender);

public:
	/*
		获得当前关卡的信息
	*/
	void Function_GetNowStageData();

	/*
		获得队伍列表数据，刷新队伍列表
	*/
	void Function_GetTeamListData();

	/*
		获得自己所在队伍数据, 刷新所在队伍数据
	*/
	void Function_GetMyTeamData();
	
	/*
		服务器通知我被踢了！！
	*/
	void Function_BeRemovedFromTeam(int removedType, int isLeader);

	/*
		获得奴隶列表
	*/
	void Function_GetSlaveList();

	/*
		获得佣兵列表
	*/
	void Function_GetMercenaryList();
};


#endif
