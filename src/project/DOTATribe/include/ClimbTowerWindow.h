//Name ; ClimbTowerWindow
//Function : 爬塔
//Author : fangjun
//Date: 20130827

#ifndef  _DOTATRIBE_CLIMBTOWERWINDOW_H_
#define  _DOTATRIBE_CLIMBTOWERWINDOW_H_


#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"

class ClimbTowerWindow : public IWindow, cocos2d::extension::CCTableViewDataSource
	, cocos2d::extension::CCTableViewDelegate
{
private:
	enum
	{
		right_Begin,//右侧显示开始
		right_End,//右侧显示结束
		right_FightResult,	//战报界面
	};

	enum
	{
		rcBg = 0,
		rcReward,
		rcNameNum,
		rcFloor,
		rcLingQuBtn,
		rcLingQuLabel,
	}RewardCell;

	enum
	{
		rGreyLayer = 0,
		rBg,
		rFloorRewardLabel,//层数奖励文字
		rBestFloor,//最好成绩
		rBestFloorValue,	//最好成绩值
		rRank,//我的排名
		rRankValue,//我的排名值
		rNextRewardLabel,//下一阶段奖励
		rReward,
		rName,
		rLingQuBtn,
		rLingQuLabel,
		rLingQuNeed,
		rTabelView,
		rTabelCell,
		rCloseBtn,
		rBgTitle,
		rLine,
		rDownArrow,
		rDownArrowMove,
	}Reward;

	enum
	{
		fcResult = 0,
		fcFloor,//层数
		fcExpGet,
		fcChaKan,
		fcChaKanLabel,
	}FightResultCell;

	enum{
		fBg = 0,
		fTableView,
		fTableCell,
		fConfirmBtn,
		fConfirmLabel,
	}FightResult;

	enum{
		bBg = 0,
		bRankListNum,
		bRankListNumValue,
		bListBtn,
		bListBtnLabel,
		bBaoXiangBtn,
		bBaoXiangEffect,
		bLine1,
		bTips,
		bLine2,
		bTimes,
		bTimesValue,
		bBuyBtn,
		bStartBtn,
		bStartLabel,
		bStartArrow,

	}Begin;

	enum{
		eBg = 0,
		eRankListNum,
		eRankListNumValue,
		eListBtn,
		eListBtnLabel,
		eBaoXiangBtn,
		eBaoXiangEffect,
		eLine1,
		eNextExp,	//下一层获得经验
		eNextExpValue,	//下一层获得经验值
		eGotExp, //累计获得经验
		eGotExpValue,//累计获得经验值
		eDesc,//说明
		eLine2,
		eTuiJianJiNeng,
		eBlock1,
		eBlock2,
		eBlock3,
		eBox1,
		eBox2,
		eBox3,
		eResetBtnLabel,
		eResetBtn,			//重置按钮
		eFastFightBtnLabel,
		eFastFightBtn,			//快速战斗按钮
		eJewelResetBtnLabel,
		eJewelResetBtn,			//钻石重置按钮
		eContinueBtnLabel,
		eContinueBtn,		//继续按钮

		eLeftTimesBg,		//剩余挑战次数底板
		eLeftTimesValue,	//剩余挑战次数值
	}End;

	enum{
		ctTowerBg1 = 0,
		ctTowerBg2,
		ctCloseBtn,
		ctHero,			//移动的骨骼,masknode
		ctRightPanel,		//右侧面板的挂载点，CCNode
		ctFloorNum1,	//层数数字1
		ctFloorNum2,	//层数数字2
		ctFloorNum3,	//层数数字3
		ctFloorNum4,	//层数数字3
		ctAnimationNode,	//动画挂载及定义节点
		ctRewardPanel,		//奖励页面挂载点
	}Main;

	cocos2d::CCNode* m_pRoot;//窗口根节点

	cocos2d::CCNode * m_pRNode;	//右边的根节点
	cocos2d::CCNode * m_pRewardNode;	//奖励节点

	cocos2d::CCNode * m_pMap1;//地图1
	cocos2d::CCNode * m_pMap2;//地图2

	cocos2d::CCNode * m_pHero;//移动的英雄

	int m_iRunTickCount;	//英雄和地图移动tick计数
	bool m_bStartRun;		//移动标志
	int m_iRunTickTime;		//默认2秒,,2*FPS
	float m_fHLength;		//移动横向长度
	float m_fVLength;		//移动纵向长度

	float m_fHeroDefaultPosx;
	float m_fHeroDefaultPosy;

	int m_iRightShowNode;//右侧显示界面

	int m_iJumpTickCount;		//冲刺tick计数
	bool m_bStartJump;			//冲刺标志
	int m_iJumpTickTime;			//冲刺时间，默认2秒 * FPS
	float m_fJumpMapSpeed;		//地图下降速度，像素/帧

	//
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//英雄角色,骨骼动画
	cocos2d::CCSprite * m_pAnimationPlayNode;//播放动画节点
	AnimationFileData * m_pAnimationFileData;//特效文件
	//PAnimation_Call_Node m_pAnimationCallBack;//回调动画
	cocos2d::CCAnimation * m_pAnimation;//动画
	cocos2d::CCRepeatForever * pAnimationAction;//重复播放动画
	CPriorityLayerColor * m_pAnimationGrayLayer;

	int _jumptickfloor;//跳跃时的层数

	cocos2d::CCSize m_szCELLFightResult;	//快速战斗
	cocos2d::CCSize m_szCellReward;			//奖励

	cocos2d::extension::CCTableView * m_pTableFightResult;
	cocos2d::extension::CCTableView * m_pTableReward;

	int m_iFastFightRound;		//快速战斗回合计数
	bool m_bInFashFightMode;	//在快速战斗模式
public:
	ClimbTowerWindow();
	virtual ~ClimbTowerWindow();
private:
	inline void _checkNewFunc();
	inline void _initLayout();
	inline void _mapMainPageBtn();

	inline void _tickRun();
	inline void _tickJump();
	inline void _setHeroPosition(float posx);
	inline void _setMapPosition(cocos2d::CCNode * map, float posy, cocos2d::CCNode * anotherMap);
	inline void _setJumpMapPosition(cocos2d::CCNode * map, float posy, int floor);

	inline void _initMapHero();
	inline void _refreshMapHero();//用于每次进入塔页面更新英雄和地图位置及地图层数
	inline void _createMapFloorNum(cocos2d::CCNode * hangParent, int maskNodeTag, cocos2d::CCNode * maskParent);
	inline void _setMapNum(cocos2d::CCNode * map, int floor1, int floor2, int floor3, int floor4);
	
	inline void _setText(int tag, cocos2d::CCNode * parent, const char * text);
	inline void _setText(int tag, cocos2d::CCNode * parent, int num);
	inline void _setTexture(int tag,  cocos2d::CCNode * parent, const char * picpath);
	inline void _enableBtn(int tag, cocos2d::CCNode * parent, bool enable);
	inline void _setVisible(int tag, cocos2d::CCNode * parent, bool visible);

	inline void _setMainPageInfo();
	
	void ShowBeginPage();
	inline void _mapBeginPageBtn();
	inline void	_setBeginPageInfo();

	void ShowEndPage();
	inline void _mapEndPageBtn();
	inline void	_setEndPageInfo();

	void ShowFightResultPage();
	inline void _mapFightResultPageBtn();
	inline void _setFightResultPageInfo();

	void ShowRewardPage();
	void _mapRewardPageBtn();
	void _setRewardPageInfo();
	void _setRewardPageNext();//设置当前将要领取的下阶段终身奖励

	inline void _setBox();//设置推荐技能显示

	void BeginChallengeTower();//开始挑战塔

	void On_BeginPage_Btn_Click(cocos2d::CCObject* pSender);		//右侧子页面1
	void On_EndPage_Btn_Click(cocos2d::CCObject* pSender);			//右侧子页面2
	void On_FightResultPage_Btn_Click(cocos2d::CCObject* pSender);	//右侧子页面3
	void On_RewardPage_Btn_Click(cocos2d::CCObject* pSender);		//右侧子页面4
	void On_RewardPageCell_Btn_Click(cocos2d::CCObject* pSender);

	void On_MainPage_Btn_Click(cocos2d::CCObject * pSender);

	void EnterTower();//进入塔,负责显示右侧界面

	void _createGrayLayer();
	void _removeGrayLayer();

	//特效相关
	inline void _initAnimationEffect();//初始化特效数据
	//播放动画
	inline void PlayEffect();

	//冲刺过程
	inline void FirstJump();

	//判断是否需要显示英雄升级
	void CheckIfNeedLvUp();

	//判断显示宝箱按钮的状态
	void CheckHaveFloorReward();

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

public:
	void _createTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell);
	void _setTableCell(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell* cell, int cellIdx);

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){		};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){		};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){		};
private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		Refresh金钱等处理
	*/
	void OnRefreshWindowEventHandler(std::list<std::string>& paramList);



private:
	/*
		进入塔结果，由外部调用
	*/
	void Function_EnterTower();

	/*
		挑战塔结果面板，middle，由外部调用
	*/
	void Function_ChallengeTowerEnd();

	/*
		重置塔结果，由外部调用
	*/
	void Function_ResetTower();

	/*
		确认使用道具增加次数确认事件
	*/
	//void Function_ComfirmPaytime();

	/*
		确认进入商城购买道具
	*/
	//void Function_ComfirmEnterShop();

	/*
		确认重置
	*/
	void Function_ComfirmReset();

	/*
		表示可以播放爬塔了
	*/
	void Function_NotifyHeroRun();

	/*
		开始塔，表示有次数可以开始塔
	*/
	void Function_StartTower();

	/*
		获得快速战斗结果
	*/
	void Function_GetFastFightResult();

	/*
		钻石重置结果
	*/
	void Function_JewelResetResult();

	/*
		获得奖励展示数据
	*/
	void Function_EnterRewardData();

	/*
		领取某个奖励的返回
	*/
	void Function_GetRewardResult(char type, int idx);

	/*
		断线重连在快速爬塔时需要重新请求一次爬塔
	*/
	void Function_LostRetryFastFight();

};


#endif
