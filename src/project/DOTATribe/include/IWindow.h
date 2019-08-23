#ifndef  _DOTATRIBE_IWINDOW_H_
#define  _DOTATRIBE_IWINDOW_H_


#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include <list>
#include "LoggerSystem.h"
using  namespace  cocos2d;
using  namespace  cocos2d::extension;


class IWindow : public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	enum
	{
		_TYPED_WINDOW_UNKOWN_,           // 未知类型的UI窗口
		_TYPED_WINDOW_START_,           // 开始窗口
		_TYPED_WINDOW_LOADING_,          // 加载进度条窗口
		_TYPED_WINDOW_DTTIMEDGRAYLAYER_, //倒计时隔绝层
		_TYPED_WINDOW_ROLESTATUS_,              //人物状态层
		_TYPED_WINDOW_MESSAGEBOX_,       // MessageBox窗口
		_TYPED_WINDOW_LOGO_,             // LOGO窗口
		_TYPED_WINDOW_HOME_,			 // 主场景
		_TYPED_WINDOW_ATHLETIC_,         // 主战斗窗口
		_TYPED_WINDOW_ATHLETICSRESULT_,  // 战斗结果界面
		_TYPED_WINDOW_SELECTROLE,		 // 选择角色界面
		_TYPED_WINDOW_STRENGTHEN_,			// 英雄升级界面
		_TYPED_WINDOW_LEVELUPNORMAL_,    // 人物升级界面
		_TYPED_WINDOW_PESWINDOW_,			//玩家信息界面
		_TYPED_WINDOW_SKINSELECTWINDOW_,    //换外套界面
		_TYPED_WINDOW_SELECTSKILLWINDOW_,  //选择技能界面
		_TYPED_WINDOW_SELECTMISSION_,		//世界地图选择界面
		_TYPED_WINDOW_SELECTSONMISSION_,	//关卡选择界面
		_TYPED_WINDOW_MASSACRE_,			//扫荡界面
		_TYPED_WINDOW_SELECTCARDLISTWINDOW_, //选取素材卡界面
		_TYPED_WINDOW_HEROBAR_,			    //英雄酒馆界面
		_TYPED_WINDOW_SELECTSERVER_,	    //选择服务器界面
		_TYPED_WINDOW_INPUTNUMWINDOW_,		//输入数字界面
        _TYPED_WINDOW_RESULTHEROUP_,        //英雄升级结果界面
		_TYPED_WINDOW_HEROTECHNOLOGY_,      //英雄科技界面
		_TYPED_WINDOW_EQUIPMENTSELECT_,		//选择装备界面，供装备升级使用
		_TYPED_WINDOW_EQUIPMENTSELECTCARD_,	//装备升级的选择卡片界面
		_TYPED_WINDOW_SYSTEMSETWINDOW_,		//系统设置界面
		_TYPED_WINDOW_ARENAWINDOW_,			//竞技场界面
		_TYPED_WINDOW_CHATWINDOW_,			//聊天界面
		_TYPED_WINDOW_NOTICEBOXWINDOW_,		//公告界面
		_TYPED_WINDOW_SHOPWINDOW_,			//商店界面
		_TYPED_WINDOW_EFFECTWINDOW_,		//EffectWindow
		_TYPED_WINDOW_CLIMBWINDOW_,			//爬塔界面
		_TYPED_WINDOW_BAGWINDOW_,			//新背包
		_TYPED_WINDOW_SHOPINPUTBUYWINDOW_,	//商店批量够买窗口
		_TYPED_WINDOW_REVENUE_,				//征收窗口
		_TYPED_WINDOW_GUIDE_,				//GuideWindow
	    _TYPEF_WINDOW_TIPSWINDOW_,		    //QA答疑窗口
		_TYPED_WINDOW_MARKETWINDOW_,		//商城窗口
		_TYPED_WINDOW_COMMUNICATIONWAITTINGWINDOW_, //通信等待窗口
		_TYPEF_WINDOW_HEROTIPSWINDOW_,            //英雄tips
		_TYPED_WINDOW_TEAMBATTLEWINDOW_,	//组队副本
		_TYPED_WINDOW_TEAMSELECTWINDOW_,	//组队选择队伍
		_TYPED_WINDOW_FRIEND_,
		_TYPEF_WINDOW_PLAYERTIPSWINDOW_,            //好友玩家tips
		_TYPED_WINDOW_RANK_WINDOW_,			//公共排行榜单
		_TYPED_WINDOW_EMAIL_WINDOW_,			//邮箱窗口
		_TYPED_WINDOW_PUCONG_WINDOW_,			//仆从根窗口
		_TYPED_WINDOW_NETOBJECTTIPSWINDOW_,		//网络物品tips
		_TYPED_WINDOW_EQUIPTIPSWINDOW_,		//装备tips窗口
		_TYPED_WINDOW_WRITEEMAILWINDOW_,		//写信窗口
		_TYPED_WINDOW_ERRORTIPSWINDOW_,		//错误提示窗口

		_TYPED_WINDOW_BATTLECAPABILITYWINDOW_,		//战力提升窗口

		_TYPED_WINDOW_HELPWINDOW_,					//帮助界面

		_TYPED_WINDOW_MAINTASKWINDOW_,			    //主线任务窗口

		_TYPED_WINDOW_ANNOUNCEMENT_WINDOW_,		    //公告窗口

		_TYPED_WINDOW_LIMITEDACTIVITY_WINDOW_,			//限时活动窗口

		_TYPED_WINDOW_RECHARGE_WINDOW_,				 //充值窗口
		_TYPED_WINDOW_RECHARGEWARN_WINDOW_,				 //充值绑定账号提醒窗口
		_TYPED_WINDOW_VIP_WINDOW_,					//VIP窗口
		_TYPED_WINDOW_TEMPLE_,				//神庙窗口
		_TYPED_WINDOW_CONVICTION_,			//信仰窗口

		_TYPED_WINDOW_FORCEPUSHTASKREWARD_WINDOW_,		//服务器强制推送任务奖励窗口

		_TYPED_WINDOW_MINEAREA_WINDOW_,			//矿区窗口
		 
		_TYPED_WINDOW_ACTIVITY_,			//活动主窗口
		_TYPED_WINDOW_ACTIVITY_SPRING,		//温泉活动窗口

		_TYPEF_WINDOW_HeroIllustratedWindow_,	//英雄图鉴窗口

		_TYPEF_WINDOW_LessResourceWindow_,	//资源不足窗口


		_TYPEF_WINDOW_LEADERSHIPLVUPWINDOW_,	//领导力升级窗口
		_TYPED_WINDOW_ALTARWINDOW_,				//献祭窗口
		_TYPED_WINDOW_GAINHEROWINDOW_,			//获得英雄窗口
		_TYPEF_WINDOW_HeroAdvancedWindow_,		//英雄进阶窗口
		_TYPED_WINDOW_GAINSOULDEBRIWINDOW_,		//获得灵碎片窗口
		_TYPED_WINDOW_CHECKLEADERSHIPWINDOW_,	//查看当前统率力窗口
		_TYPED_WINDOW_MULTIREWARDWINDOW_,		//多个奖励框窗口
		_TYPED_WINDOW_FIRSTRECHWINDOW_,			//首充礼包活动窗口
		_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_,	//新装备提醒窗口
		_TYPED_WINDOW_ARENAREWARDWINDOW_,		//查看竞技场奖励窗口
		_TYPED_WINDOW_LEVELUPREWARDACTIVITYWINDOW_,//升级奖励活动窗口
		_TYPED_WINDOW_SHOPTIPSWINDOW_,			//商店TIPS窗口

		_TYPED_WINDOW_BOSSSCORE_,				//boss积分系统
		
		_TYPED_WINDOW_ACTIVITYLOGIN_,			//每日活动窗口

		_TYPED_WINDOW_HEROSOULWINDOW_,			//英雄战魂窗口
		_TYPED_WINDOW_EXCHANGEACTIVITYWINDOW_,	//兑换活动窗口
		_TYPED_WINDOW_ACTIVITYGROWUPPLAN_,		//成长计划活动窗口

		_TYPED_WINDOW_SOULTIPSWINDOW_,			//战魂TIPS窗口

		_TYPED_WINDOW_APPSTOREWAITWINDOW_,		//AppStore支付等待窗口

		_TYPED_WINDOW_VIPGIFTWINDOW_,			//vip礼包界面

		_TYPED_WINDOW_TENCALLWINDOW,			//十连抽显示界面
		_TYPED_WINDOW_GAINCALLITEMWINDOW_,		//获得召唤物品窗口
		_TYPED_WINDOW_TEAMINFOWINDOW_,			//队伍信息窗口

		_TYPED_WINDOW_NUMBER_,					//window总数
	};

public:
	enum
	{
		_TYPED_ALERT_WINDOW_UNKOWN_,                   // 未知子类型的警告提示窗口
 
	};

public:
	enum
	{
		_TYPED_WINDOW_ZORDER_UNKOWN_, // 未知的窗口Z-Order序列
		_TYPED_WINDOW_ZORDER_NORMAL_, // 普通的窗口Z-Order序列
		_TYPED_WINDOW_ZORDER_HIGH_,   // 高等级窗口的Z-Order序列
		_TYPED_WINDOW_ZOREDR_HIGHEST_,// 最高等级窗口的Z-Order序列
		_TYPED_WINDOW_ZOREDR_TOP_,    // 最高更急的窗口Z-Order序列(仅为整个客户端系统的系统信息面板)
	};

public:
	struct _SCRIPT_TIMER_FUNCTION_
	{
		long  long  mStartTime;     // 开始时间
		int         mIntervalTime;  // 间隔时间
		std::string mScriptFunction;// 脚本定时回调函数
		_SCRIPT_TIMER_FUNCTION_()
		{
			mStartTime    = 0;
			mIntervalTime = 0;
		}
	};

protected:
	int                 m_WindowType;       // 窗口所属类型
	std::string         m_WindowName;       // 窗口名称
	bool                m_bModelWindow;     // 是否为模态模式窗口
	int                 m_WindowZOrder;     // 窗口Z-Order序列
	std::string         m_ParentWindowName; // 窗口父窗口的名称
	bool                m_bLoaded;          // 是否已经加载
	bool                m_bShow;            // 该layout对应的根窗口是否可见
	bool                m_bTickListener;    // 是否帧回调处理
	cocos2d::CCNode*    m_pRootNode;        // 该Layout对应的根窗口
	bool				m_bIsForceClearUnUseTex; //是否强制回调未用纹理
	bool				m_bIsForceClearAnimation;//是否强制释放动画纹理


protected:
	long    long        m_TickCounter;      // 逻辑帧计数

protected:
	std::string         m_WindowDataList[16];// 窗口内部数据列表(用于进行保存部分玩家数据)

protected:
	std::list<_SCRIPT_TIMER_FUNCTION_> m_ScriptTimerList;// 脚本定时接口

public:
	IWindow();
	virtual ~IWindow();

public:
	/*
		得到当前LAYOUT名称
	*/
	int                GetWindowType();
	/*
		是否已经加载
	*/
	bool               IsLoad();
	/*
		得到根窗口指针
	*/
	cocos2d::CCNode*   GetRootNode();

public:
	/*
		设置窗口指定索引的数据
	*/
	void  SetWindowDataByPos(std::string str, unsigned int pos);
	/*
		得到
	*/
	std::string GetWindowDataByPos(unsigned int pos);

public:
	/*
		是否帧监听
	*/
	virtual    void    SetTickListenser(bool bListenser);
	/*
		设置LAYOUT显示于隐藏
	*/
	virtual    void    Show(bool bShow);
	/*
		判断LAYOYUT是否可见
	*/
	virtual    bool    IsVisible();

public:
	/*
		设置X坐标
	*/
	virtual    void    SetXPosition(float xPos);
	/*
		得到X坐标
	*/
	virtual    float   GetXPosition();
	/*
		设置Y坐标
	*/
	virtual    void    SetYPosition(float yPos);
	/*
		得到Y坐标
	*/
	virtual    float   GetYPosition();
	/*
		设置X缩放比例
	*/
	virtual    void    SetXScale(float xScale);
	/*
		设置Y缩放比例
	*/
	virtual    void    SetYScale(float yScale);
	/*
		注册UI绑定事件
	*/
	virtual    void    RegisterEvent(int iEventType, bool bNotifyOnlyWhenVisible=false);
	/*
		分发事件
	*/
	virtual    void    PushEvent(int iEventType);
	/*
		分发事件
	*/
	virtual    void    PushEvent(int iEventType, char* pArgs);
	/*
		播放窗口打开时的音效
	*/
	virtual    void    PlayOpenSound();

	/*
		播放窗口关闭时的音效
	*/
	virtual    void    PlayCloseSound();
public:
	/*
		注册脚本定时回调接口
	*/
	virtual    void    RegisterTimerFunction(float time, std::string functionName);

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

	/*
		加载窗口所需图片资源plist
	*/
	void LoadPlistForWindow();
	/*
		清除窗口所需图片资源plist
	*/
	void UnloadPlistForWindow();
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList)   =   0;

public:
	/*
		开始接触操作
	*/
	virtual    bool    ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		移动操作
	*/
	virtual    void    ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		接触结束操作
	*/
	virtual    void    ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		接触取消操作
	*/
	virtual    void    ccTouchCancel(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
};


#endif
