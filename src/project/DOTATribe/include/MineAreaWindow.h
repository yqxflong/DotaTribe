//Name : MineAreaWindow
//Function : 矿场
//Author : 方骏
//Date: 20131128

#ifndef _DOTATRIBE_MINEAREA_WINDOW_H_
#define _DOTATRIBE_MINEAREA_WINDOW_H_

#include "../include/IWindow.h"
#include "cocos-ext.h"
#include "../include/CMenuItemSprite.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"

class MineAreaWindow : public IWindow, public AnimationEffectCallBackProtocol
{
public:
	enum
	{
		_PAGE_UNKNOW_ = 0,
		_PAGE_GOBLINAREA_ = 1,		//地精矿区
		_PAGE_DWARVENAREA_ = 2,		//矮人矿区
		_PAGE_DRAGONAREA_ = 3,		//巨龙矿区
		_PAGE_HUNTMINE_ = 4,		//寻宝区
	}PAGE;

	enum{
		_STRING_SLAVE_LABEL_ = 916,//奴隶数量
		_STRING_GOLD_LABEL_ = 917,//金币效率
		_STRING_START_MINING_ = 921,//开始采集
		_STRING_STOP_MINING_ = 922,//结束采集
		_STRING_LEFT_QIANG_TIMES_ = 6097,//抢夺矿位花费%d
		_STRING_QIANGKUANGWEI_ = 924,//抢矿位
		_STRING_OWNER_NAME_ = 925,//矿主名字
		_STRING_OWNER_CAPA_ = 926,//矿主战斗力
		_STRING_FIGHT_ = 927,//挑战
		_STRING_MINING_ = 928,//采集
		_STRING_MINING_FRIEND_ = 929,//采矿好友数
		_STRING_CAPA_LABEL_ = 527,	//战力
		_STRING_TOTALOUTPUT_LABEL = 920,//累计获得
		_STRING_OWNER_NOT_FRIEND_ = 930,//矿主不是我的好友

		_STRING_HUNT_SAYINGBEGIN_NPC_ = 12000,			//寻宝过程中需要的野兽说的话，随即开始
		_STRING_HUNT_SAYINGBEGIN_HUMAN_ = 12005,	//寻宝过程中需要的玩家说的话，随即开始
		_STRING_HUNT_ADDFRIEND_ = 931,			//加好友
		_STRING_HUNT_QIANGDUO_ = 932,			//抢夺
		_STRING_HUNT_QUZHU_ = 933,				//驱逐
		_STRING_HUNT_BUYMINRAL_ = 934,			//购买矿石
		_STRING_HUNT_MEET_ = 935,				//寻宝过程中遇到%d(战力：%d)
		_STRING_HUNT_HELLOFRIEND_ = 936,		//打招呼
		_STRING_HUNT_BUYMINRALPRICE_ = 937,			//购买矿石价格

		_STRING_NOT_MINING_ = 938,				//不再采矿
	};

private:
	enum{
		gBg = 0,
		gBoard,
		gGrey,
		gMinePic,
		gMineName,
		gSitBg,
		gSitMyTip,
		gSitQuality,
		gSitLevelBg,
		gSitLevel,
		gSitName,
		gSitNameValue,
		gSitNameBg,
		gSitTime,
		gSitTimeValue,
		gSitTimeBg,
		gSitTotal,
		gSitTotalValue,
		gSitTotalBg,
		gStartStopBtn,
		gStartStopLabel,
		gQuickBackHomeBtn,
		gBackUpBtn,
	}Goblin;

	enum{
		dBg,
		dBoard,
		dGrey,
		dMinePic,
		dMineName,
		dLeftArrow,
		dRightArrow,
		dLeftTimeBg,
		dLeftTimeLabel,
		dLeftTimeMoney,
		dPageBg,
		dPageLabel,
		dQuickBackHomeBtn,
		dBackUpBtn,
		dSitBg0,
		dSitMyTip0,
		dSitQuality0,
		dSitLevelBg0,
		dSitLevel0,
		dSitName0,
		dSitNameValue0,
		dSitNameBg0,
		dSitTime0,
		dSitTimeValue0,
		dSitTimeBg0,
		dSitTotal0,
		dSitTotalValue0,
		dSitTotalBg0,
		dStartStopBtn0,
		dStartStopLabel0,
		dSitBg1,
		dSitMyTip1,
		dSitQuality1,
		dSitLevelBg1,
		dSitLevel1,
		dSitName1,
		dSitNameValue1,
		dSitNameBg1,
		dSitTime1,
		dSitTimeValue1,
		dSitTimeBg1,
		dSitTotal1,
		dSitTotalValue1,
		dSitTotalBg1,
		dStartStopBtn1,
		dStartStopLabel1,
		dSitBg2,
		dSitMyTip2,
		dSitQuality2,
		dSitLevelBg2,
		dSitLevel2,
		dSitName2,
		dSitNameValue2,
		dSitNameBg2,
		dSitTime2,
		dSitTimeValue2,
		dSitTimeBg2,
		dSitTotal2,
		dSitTotalValue2,
		dSitTotalBg2,
		dStartStopBtn2,
		dStartStopLabel2,
		dSitBg3,
		dSitMyTip3,
		dSitQuality3,
		dSitLevelBg3,
		dSitLevel3,
		dSitName3,
		dSitNameValue3,
		dSitNameBg3,
		dSitTime3,
		dSitTimeValue3,
		dSitTimeBg3,
		dSitTotal3,
		dSitTotalValue3,
		dSitTotalBg3,
		dStartStopBtn3,
		dStartStopLabel3,

	}Dwarven;

	enum{
		nBg,
		nBoard,
		nGrey,
		nMinePic,
		nMineName,
		nQuickBackHomeBtn,
		nBackUpBtn,
		nOwnerBg0,
		nOwnerQuality0,
		nOwnerLvBg0,
		nOwnerLv0,
		nOwnerNameBg0,
		nOwnerName0,
		nOwnerBg1,
		nOwnerQuality1,
		nOwnerLvBg1,
		nOwnerLv1,
		nOwnerNameBg1,
		nOwnerName1,
		nOwnerBg2,
		nOwnerQuality2,
		nOwnerLvBg2,
		nOwnerLv2,
		nOwnerNameBg2,
		nOwnerName2,
		nOwnerBg3,
		nOwnerQuality3,
		nOwnerLvBg3,
		nOwnerLv3,
		nOwnerNameBg3,
		nOwnerName3,

		nOwnerName,
		nOwnerCapa,
		nOwnerDesc,

		nOwnerTiaoZhan,//show or not
		nOwnerTiaoZhanLabel,
		nOwnerJewelPic,
		nOwnerJewelLabel,

		nOwnerCaiKuang,
		nOwnerCaiKuangLabel,

		nSitBg,//show or not
		nSitMyTip,
		nSitIcon,
		nSitLevelBg,
		nSitLevel,
		nSitName,
		nSitNameValue,
		nSitNameBg,
		nSitTime,
		nSitTimeValue,
		nSitTimeBg,
		nSitTotal,
		nSitTotalValue,
		nSitTotalBg,
		nStartStopBtn,
		nSrartStopLabel,

	}Dragon;

	enum{
		hMap0,
		hMap1,
		hGreyLine,
		hBianKuang,
		hHeroMask,
		hEffectMask,
		hMonsterMask,
		hProgress,
		hProgressBg,
		hProgressLabel,
		hDesc,
		hHuntBtn,
		hQuickBackHomeBtn,
		hBackUpBtn,
		hGrey,
		hTipBg,
		hTipIcon,
		hTipSay,
		hTipMeet,//包含战力
		hTipBtn0,
		hTipBtn0Label,
		hTipBtn1,
		hTipBtn1Label,
		hTipBuyMinralPrice,//购买矿石价格
		hTipBuyMinralJewelPic,	//钻石图标
		hLieRen0,//装备猎人
		hLieRen1,//宝物猎人
		hLieRen2,//宝石猎人
		hLieRen3,//精英猎人
		hLieRenMask0,//装备猎人
		hLieRenMask1,//宝物猎人
		hLieRenMask2,//宝石猎人
		hLieRenMask3,//精英猎人
		hGrey2,					//防触层
		hTipBg2,				//夺宝背景
		hTipTitle2,				//夺宝标题
		hTipLevelDesc2,			//等级说明
		hTipDesc2,				//说明
		hProability2,			//抢夺成功概率
		hTipLine2,				//分割线
		hTipNoLieRenLabel2,		//没有猎人说明文字
		hTipAwardBoard2,		//奖励面板
		hTipAwardName2,			//奖励名字
		hTipNoBtn2,				//放弃抢夺按钮
		hTipNoBtnLabel2,		//放弃抢夺文字
		hTipYesBtn2,			//抢夺按钮
		hTipYesBtnLabel2,		//抢夺按钮文字
		hTipSpentLabel2,		//抢夺花费
		hTipCloseBtn2,				//猎人详细信息界面的关闭
	}Hunt;

private:
	int m_iShowPage;

	int m_iBackWindow;
	cocos2d::CCNode * m_pRoot; 

	int m_iDwarvenShowPage;//矮人矿洞显示的界面

	CMenuItemSprite * m_pDragonSelectOwner;//选中的拥有者

	//寻宝中需要的动画节点	//begin
	cocos2d::extension::CCSkeletonAnimation* m_pSkeletonNode;	//英雄角色,骨骼动画
	cocos2d::CCSprite * m_pAnimationPlayNode;//播放动画节点
	AnimationFileData * m_pAnimationFileData;//特效文件
	cocos2d::CCAnimation * m_pAnimation;//动画
	cocos2d::CCRepeatForever * pAnimationAction;//重复播放动画
	CPriorityLayerColor * m_pAnimationGrayLayer;
	bool m_bHeroRun;//英雄开始跑
	int m_iRunTickTime;//默认跑动时间
	int m_iRunTickCount;//跑动计时器
	CCNode * m_pHuntMap0;//地图0
	CCNode * m_pHuntMap1;//地图1
	bool m_bBoxOpen;//宝箱在开启状态
	int m_iOpenTickTime;//宝箱开启计时

	cocos2d::CCNode * m_pLieRenJiHuoAnimation0;//循环动画
	cocos2d::CCNode * m_pLieRenJiHuoAnimation1;//循环动画
	cocos2d::CCNode * m_pLieRenJiHuoAnimation2;//循环动画
	cocos2d::CCNode * m_pLieRenJiHuoAnimation3;//循环动画
	cocos2d::CCNode * m_pLieRenKaiQiAnimation;//单次动画
	//end
public:
	int m_iDragonSelectOwner;//选中的拥有者

	unsigned char m_iLieRenSelected;//当前打开的猎人类型
public:
	MineAreaWindow();
	virtual ~MineAreaWindow();

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

protected:
	/*
		消息事件响应处理
	*/
	virtual void OnEventHandler(int iEventType, std::list<std::string>& paramList);
	/*
		显示面板事件处理
	*/
	inline void OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		渐隐面板事件处理
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

private:
	/*
		绘制当前页面
	*/
	inline void _initLayout();

	/*
		设置当前页面相关显示内容
	*/
	inline void _setPage();

	inline void _setGoblinPage();
	inline void _setDwarvenPage();
	inline void _setDragonPage();
	inline void _setDragonRightPart();

	inline void _setHuntPage();
	inline void _setHuntTipPage();//设置普通遭遇对话框
	inline void _showHuntTipPage(bool show);
	inline void _setHuntTipPage2();//设置事件遭遇对话框
	inline void _showHuntTipPage2(bool show);

	inline void _clearMonster();
	inline void _playHuntMeetAnimation();
	inline void _initHuntHero();
	inline void _initHuntMap();
	inline void _heroHuntRun();
	inline void _moveHuntMap();

	inline void _workTick();
	/*
		添加阴影
	*/
	inline void _addShadow(cocos2d::CCNode* node);
	void _createGrayLayer();
	void _removeGrayLayer();

	/*
		绑定按钮
	*/
	inline void _mapBtn();

	/*
		请求响应页面数据
	*/
	inline void _requestData();

	//设置页面激活状态特效
	void _setLieRenJiHuoAnimation();


public:
	void HuntAnimationCallBackFunction();
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
public:
	//接收到进入地精矿区信息
	void Function_GetEnterGoblinData();

	//接收到进入矮人矿区信息
	void Function_GetEnterDwarvenData();

	//接收到进入巨龙矿区信息
	void Function_GetEnterDragonData();

	//接收到进入寻宝信息
	void Function_GetEnterHuntData();

	//接收到停止采矿结果
	void Function_GetStopMiningResult();

	//接收到开始采矿结果
	void Function_GetStartMiningResult();

	//接收到寻宝结果数据
	void Function_GetHuntingResult();

	//接收到打招呼结果
	void Function_GetHelloFriendResult();

	//接收到购买原矿结果
	void Function_GetBuyMinralResult();

	//接收到申请好友结果
	void Function_GetAskFriendResult();

	//接收到矮人矿区抢矿位不正常的结果
	void Function_GetDwarvenLootResult();

	//确认矮人矿区信息刷新弹窗
	void Function_GetDwarvenPageInfoChangedConfirm();

	//寻宝因为使用了物品而次数更新
	void Function_HuntLeftTimeUpdate(int lefttime);

	//寻宝查看猎人详细信息结果
	void Function_HuntLieRenChaKan();

	//寻宝放弃抢夺某个猎人
	void Function_HuntLieRenQiangDuoNo();

	
private:
	/*
		地精矿区页面事件
	*/
	void On_GoblinArea_Click(cocos2d::CCObject * pSender);

	/*
		矮人矿区事件
	*/
	void On_DwarvenArea_Click(cocos2d::CCObject * pSender);

	/*
		巨龙矿区事件
	*/
	void On_DragonArea_Click(cocos2d::CCObject * pSender);

	/*
		寻宝事件
	*/
	void On_HuntMine_Click(cocos2d::CCObject * pSender);

	/*
		帮助事件
	*/
	void On_Help(cocos2d::CCObject* pSender);

};

#endif