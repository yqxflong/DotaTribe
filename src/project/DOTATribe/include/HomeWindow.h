//Name：HomeWindow
//Function：主场景，通往各个场景的必经之路
//Written By：尹强
//Modify By:liqian
//Time:2013-08-29
#ifndef  _DOTATRIBE_HOMEWINDOW_H_
#define  _DOTATRIBE_HOMEWINDOW_H_

#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/RollingBoard.h"
using namespace cocos2d;
using namespace cocos2d::extension;


class CMapScrollView;
class HomeWindow : public IWindow,public cocos2d::CCIMEDelegate 
{
private:
	float m_fTick_quickout_hint;
	const static float TIME_SHOWHINT_QUICKOUT;
	bool m_bIsShowHint_quickout;
	int building_status[8];	//8个显示new的建筑的状态数组


	RollingBoard * roll;
	RollingBoard * roll1;
	RollingBoard * roll2;
	RollingBoard * roll3;
	RollingBoard * roll4;
	RollingBoard * roll5;
public:
	HomeWindow();
	virtual ~HomeWindow();

	enum{
		udMAPSCROLL,	//地图滚动器
		udROLEINFO,//队伍
		udBAG,//背包
		udSMELT,//强化
 		udFRIEND,//好友
		udSYSTEM,//系统
		udOUT,//快速出城
    	udPAYPRESENT,//充值礼包
		udMARKET,//商城
		udLUATEST,			//Lua测试
		udBOSSSCORE,	//世界boss
		udZHENGSHOU,	//征收
		udEMAIL,//邮箱
		udVIP,		//vip
		udLIMITEDACTIVITY,	//限时活动
		udACTIVITY,		//活动
		udMOREBTN,//更多按钮
		udAWARDNOTICE_EFFECT,//奖励公告特效
		udACTIVITY_EFFECT,//精彩活动特效
		udVIPREWARD_EFFECT,//精彩活动特效
		udBOSS_EFFECT,//Boss特效
		udOUTTITLE,	//快速进入副本进度文字
		udVIPLEVELTEXT,			//当前VIp等级文字
		udCOLLECTIONCORNER,				//征收角标
		udEMAILCORNER,					//邮箱角标
		udFRIENDCORNER,					//好友角标
		udBOSSCORNER,					//boss积分角标
		udBOTTOM_BAR_DECORATION,	//底部亮条
		udOUT_HINT,//快速出城提示
		udOUT_EXP_DOUBLE_HINT,	//双倍经验提示
		udSTRENTHEN_HINT_1,	//强化提示，展开
		udSTRENTHEN_HINT_2,	//强化提示，关闭
		udSTRENTHEN_HINT_NODE,	//强化提示占位，存储during，dis
		//
		udSTRENTHEN_HINT_1_NODE=1000,		//强提1节点
		udSTRENTHEN_HINT_2_NODE,			//强提2节点
	}kHomeWindow;

	enum{
		udHOMEMAP_1,//地图1
		udHOMEMAP_2,//地图2，接地图1
		udBAR,//酒吧
		udDOOR,//城门
		udHOME,//城堡
		udSHOP,//神秘商人
		udPKPLACE,//竞技场
		udTDOOR,//远古遗迹
		udTOWER,//传承之塔
		udMINERALHOLE,//矿洞
		udBAR_FILE_NODE,//酒馆文件存储节点
		udDOOR_FILE_NODE,//城门文件存储节点
		udHOME_FILE_NODE,//城堡文件存储节点
		udSHOP_FILE_NODE,//神秘商人文件存储节点
		udPKPLACE_FILE_NODE,//竞技场文件存储节点
		udTDOOR_FILE_NODE,//远古遗迹文件存储节点
		udTOWER_FILE_NODE,//传承之塔文件存储节点
		udMINERALHOLE_FILE_NODE,//矿洞文件存储节点
		udBARTXTBG,//酒吧标题背景
		udDOORTXTBG,//城门标题背景
		udHOMETXTBG,//城堡标题背景
		udMARKETTXTBG,//黑市标题背景
		udPKPLACETXTBG,//竞技场标题背景
		udTDOORTXTBG,//传送之门标题背景
		udTOWERTXTBG, //塔标题背景
		udMINERALBG,	//矿洞标题背景
		udBARTXT,//酒吧标题
		udDOORTXT,//城门标题
		udHOMETXT,//城堡标题
		udMAKETTXT,//黑市标题
		udPKPLACETXT,//竞技场标题
		udTDOORTXT,//传送之门标题
		udTOWERTXT,//xx塔标题标题
		udMINERALTXT,//矿洞标题
		udBUSSINESSMAN,	//商人占位节点
		udSE_TEMPLE_1,//蓝色大火焰==神庙
		udSE_TEMPLE_2,//蓝色大火焰==神庙
		udSE_TEMPLE_3,//黄色大火焰==神庙
		udSE_TEMPLE_4,//黄色大火焰==神庙
		udSE_MAP_1,//黄色小火焰
		udSE_MAP_2,//黄色小火焰
		udSE_MAP_3,//黄色小火焰
		udSE_MAP_4,//黄色小火焰
		udSE_MINERAL,//矿洞特效==矿洞
		udSE_BAR,//BAR特效==酒馆
		udSE_TEAMPVE,//遗迹特效
		udSE_TEAMPVE_2,	//遗迹符文
		udSE_MARKET_1,//宝箱星星
		udSE_MARKET_2,//宝箱光
		udSE_MAP_5,//主城旗子
		udSE_PVP,//竞技场旗子
		udICON_NEW,//建筑上的new字样
		udICON_MINERALEMPTYHINT,//矿洞空闲的字样
		udMINERALEMPTY_HINT_NODE,	//矿洞空闲占位，存储during，dis
		udICON_FREESUPPLI,//免费祈愿字样
		udICON_FREESUMMON,//免费召唤字样
		udICON_REFRESHSHOP,//可刷新字样
		//
		udREALBUSSINESSMAN=1000,		//真正的商人
		udNEW_HEROBAR,					//祭坛开启
		udNEW_AREANA,					//竞技场开启
		udNEW_MINERAL,					//仆从开启
		udNEW_HEROTECH,					//科技开启
		udNEW_TOWER,					//爬塔
		udNEW_TEAMBATTLE,				//组队副本
		udHINT_MINERALEMPTY,			//矿洞空闲节点
		udHINT_FREESUPPLI,				//免费祈愿节点
		udHINT_FREESUMMON,				//免费召唤节点
		udHINT_REFRESHSHOP,				//商店刷新节点
	}kHomeMap;

	CCNode* m_pRoot;					//根部节点
	cocos2d::CCMenu* m_pRootMenu;		//更多附加按钮的menu
	CMapScrollView* m_pMapScroll;		//场景地图滚动轴
	//=======================箭头声明=================================
	cocos2d::extension::CCSkeletonAnimation* m_pArrow_Collection;	//点金箭头
	cocos2d::extension::CCSkeletonAnimation* m_pArrow_QuickOut;		//快速出城箭头
	//
	std::vector<cocos2d::CCPoint*> m_vecMoreitemPos;   //记录所有More的items
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

	//检查MoreItems当前状态
	void checkMoreItems();

	//open morebtn
	void openMoreBtn(bool isaction);

	//close morebtn
	void closeMoreBtn(bool isaction);

	//show items
	void showMoreItems();
	//hide items
	void hideMoreItems();

	//show items
	void showMoreItems_normal();
	//hide items
	void hideMoreItems_normal();

	//显示亮条
	inline void _showBottomBar(bool isshow);
	/*
		检查功能解锁情况
	*/
	void CheckFunctionLock();
	/*
		检查提示信息
	*/
	void CheckAllHint();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		显示大厅面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
private:
	inline void _initLayout();
	inline void _SetHomeMap();
	inline void _createBusinessMan();
	inline void _initStrengthenHint();
	inline void _initMineralEmptyHint();
	inline void _initFreeSuppliHint();
	inline void _initFreeSummonHint();
	inline void _initRefreshShopHint();
	inline void _mapBtn();
	inline void _mapGlodBg();
	inline void _mapMoreItems();
	inline void _mapRoleInfoItem();
	inline void _mapBagItem();
	inline void _mapSkillItem();
	inline void _mapStrengthenItem();
	inline void _mapFriendItem();
	inline void _mapSystemItem();

	/*
		设置快速出城
	*/
	void _setQuickOut();
	/*
		设置快速进入副本进度文字
	*/
	void _setOutProgress();
	/*	
		检查建筑解锁情况
	*/
	void _checkBuildingLock();
	/*	
		检查祭坛解锁情况
	*/
	void _checkBuildingLock_HeroBar();
	/*	
		检查黑市解锁情况
	*/
	void _checkBuildingLock_Market();
	/*	
		检查竞技场解锁情况
	*/
	inline void _checkBuildingLock_PkPlace();
	/*	
		检查爬塔解锁情况
	*/
	inline void _checkBuildingLock_Tower();
	/*	
		检查组队副本解锁情况
	*/
	inline void _checkBuildingLock_TeamPVE();
	/*	
		检查城堡解锁情况
	*/
	inline void _checkBuildingLock_HomeTown();
	/*
		检查仆从解锁情况
	*/
	inline void _checkBuildingLock_Labor();
	/*
		检查浮动按钮解锁情况
	*/
	inline void _checkHangupItemLock();
	/*
		检查邮箱解锁情况
	*/
	inline void _checkHangupItemLock_Email();
	/*
		检查征收解锁情况
	*/
	inline void _checkHangupItemLock_Collect();

	/*
		检查世界Boss解锁情况
	*/
	void _checkHangupItemLock_Boss();

	/*
		检查其他解锁情况解锁情况
	*/
	void _checkOtherLock();

	/*
		检查其他解锁情况解锁情况_矿洞之寻宝
	*/
	void _checkOtherLock_Labor();

	/*
		检查其他解锁情况解锁情况_金矿采集
	*/
	void _checkOtherLock_GoldMine_();
	/*
		更新vip等级
	*/
	void _updateVipNum();

	//===========状态层==============
	inline void _heroIllustrateEvent();
	inline void _skillEvent();
	inline void _moreEvent();
	inline void _bagEvent();
	inline void _strengthenEvent();
	inline void _friendEvent();
	inline void _systemEvent();
	inline void _outEvent();
	inline void _paypresentEvent();
	inline void _zhengshouEvent();
	inline void _shopEvent();
	inline void _emailEvent();
	inline void _limitedActivityEvent();
	inline void _activityEvent();
	inline void _vipEvent();
	//=========建筑事件=========
	inline void _barEvent();
	inline void _doorEvent();
	inline void _homeEvent();
	inline void _marketEvent();
	inline void _luaEvent();
	inline void _bossEvent();
	inline void _pkPlaceEvent();
	inline void _tdoorEvent();
	inline void _towerEvent();
	inline void _mineralhole();

	//检查建筑点击 是否上锁
	bool _buildingCheckOpened(int key);

	//开启指定建筑特效
	void _enableBuildingEffect(int key,bool opened);

	//检查建筑提示
	void _buildingCheckHint(int key,bool opened);

	//检查建筑开启指引
	void _buildingCheckNewOpen(int key);


	//检查建筑的展示状态
	void _buildingCheckDisplay(int key,bool opened);


	/*
		提示有装备可以强化
	*/
	void _showStrengthenHint();

	/*
		快速出城双倍经验提示
	*/
	void _showQuickOutHint_DoubleExp();

	/*
		提示有世界Boss 活动
	*/
	void _showBossHint();
	/*
		提示有免费召唤
	*/
	void _showFreeSummonHint();
	/*
		提示有免费祈愿
	*/
	void _showFreeSupplicaHint();
	/*
		提示可刷新商店
	*/
	void _showRefreshShopHint();

	/*
		提示有矿坑是空的
	*/
	void _showMineralEmptyHint();

	/*
		提示快速出城
	*/
	bool _showQuickOutHint();
	/*
		隐藏快速出城提示
	*/
	void _hideQuickOutHint();
	/*
		提示奖励公告有奖励
	*/
	void checkAwardNoticeHint();
	/*
		提示精彩活动有奖励
	*/
	void checkAwardActivityHint();
	/*
		提示VIP有奖励
	*/
	void checkAwardVipHint();
	/*
		设置任务角标：显示未完成的任务
	*/
	void setTaskCorner();
	/*
		设置征收角标：显示总可征收次数
	*/
	void setCollectionCorner();
	/*
		设置邮箱角标：显示未读的信
	*/
	void setEmailCorner();
	/*
		设置好友角标：显示申请好友的数量
	*/
	void setFriendCorner();
	/*
		设置boss积分角标：显示Boss积分免费次数
	*/
	void setBossScoreCorner();

	/*
		接收刷新UI事件
	*/
	static void Event_RefreshUI_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
	/*
		接收打开More的事件
	*/
	static void Event_ShowMoreItems_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);

	//注册事件
	inline void _registerRefreshEvent();
	inline void _unregisterRefreshEvent();


	/*
		显示new字样给指定建筑
	*/
	void _showNewFlowICon4Building(int ModuleID);
	/*
		创建new字样by坐标
	*/
	inline void _createFlowNewICon(const CCPoint &cp,int key);

	/*
		将地图移动至最右边
	*/
	void _moveMapToRightBottom();
	/*
		将地图移动至最左边
	*/
	void _moveMapToLeftTop();

	//===========================箭头大全============================
	/*
		显示点金箭头
	*/
	void _showArrow_Collection();
	/*
		销毁点金箭头
	*/
	void _hideArrow_Collection();
	/*
		显示快速出城箭头
	*/
	void _showArrow_QuickOut();
	/*
		销毁快速出城箭头
	*/
	void _hideArrow_QuickOut();
public:
	/*
		悬浮按钮的点击事件
	*/
	void On_Click_BtnClick(cocos2d::CCObject* pSender);
	/*
		主场景上建筑的点击事件
	*/
	void On_Click_Event_MainBG(cocos2d::CCObject* pSender);
};

#endif
