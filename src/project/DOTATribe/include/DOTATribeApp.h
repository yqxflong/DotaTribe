//Name：DOTATribeApp
//Function：游戏C++层总入口
//Author：Johny

#ifndef  _DOTATRIBE_DOTATRIBEAPP_H_
#define  _DOTATRIBE_DOTATRIBEAPP_H_

#include <cocos2d.h>
#include <include/common/Singleton.h>
#include <CCApplication.h>
#include <CCAdDelegate.h>
#include <CCSystemDelegate.h>
#include <base_nodes/CCNode.h>
using  namespace  cobra_win;

class IProcedure;
class LogoProcedure;
class LoginProcedure;
class LoadingProcedure;
class HomeProcedure;
class BossLobbyProcedure;
class AthleticsProcedure;
class SelectCustomsPassProcedure;
class CreateRoleProcedure;
class SelectMissionProcedure;
class TeamBattleProcedure;
class ArenaProcedure;
class DOTATribeApp : public cocos2d::CCNode, public cocos2d::CCApplication, public cocos2d::CCSystemDelegate, public cobra_win::Singleton2<DOTATribeApp>
{
public:
	LogoProcedure*							m_pLogoProcedure;				// LOGO处理流程
	LoadingProcedure*						m_pLoadingProcedure;			// Loading处理流程
	LoginProcedure*							m_pLoginProcedure;				// 登陆处理流程
	HomeProcedure*							m_pHomeProcedure;				//主场景流程
	SelectCustomsPassProcedure*				m_pSelectCustomsPassProcedure;	//选择关卡处理流程
    AthleticsProcedure*						m_pAthleticsProcudure;			//对战竞技流程
	TeamBattleProcedure*					m_pTeamBattleProcedure;			//组队副本流程
	CreateRoleProcedure*					m_pCreateRoleProcedure;			//创建角色流程
	SelectMissionProcedure*					m_pSelectMissionProcedure;		//世界地图选择流程
	ArenaProcedure*							m_pArenaProcedure;				//竞技场流程

public:
	IProcedure* m_pPreProcedure;    // 上一帧对应的处理流程
	IProcedure* m_pActiveProcedure; // 当前激活的处理流程

public:
	bool        m_bRun;    // 添加变量,在每一帧最后执行退出操作
	bool        m_bActive; // 当前窗口是否激活
	bool		m_IsProcedureChanged;//是否切换过流程

public:
	DOTATribeApp();
	virtual ~DOTATribeApp();

public:
	//@得到游戏版本号
	std::string  GetVersion();

	//@设置是否运行
	void         SetRun(bool bRun);

	//@得到客户端帧率
	int          GetFPS();

	//@得到客户端窗口宽度
	int          GetAppWidth();
	//@得到客户端窗口高度
	int          GetAppHeight();

	//@游戏重置
	void ResetAllGame();

	//@清除所有游戏界面
	void ClearAllWindow();

	//@清除游戏界面所有可见窗口
	void ClearAllVisibleWindow();

	//@清除游戏界面所有可见窗口除了某一窗口
	void ClearAllVisibleWindow(int iType);

	//@清除所有游戏数据
	void ClearAllData();

public:
	//@切换流程
	void         SetActiveProcedure(IProcedure* pProcedure);

	//@得到当前流程
	IProcedure*  GetActiveProcedure();

	//@得到指定流程
	IProcedure*  GetProcedure(int idx);

	//@检查当前流程与欲切换流程相同
	bool IsActiveProcedureEqualNextProcedure(int nextProcedure);

	//@检查当前流程与欲切换流程相同
	bool IsActiveProcedureEqualNextProcedure(IProcedure* nextProcedure);

	//@检查当前流程是否为登陆流程
	bool IsLoginProcedureAsActiveProcedure();

	//@检查当前流程是否为创建角色流程
	bool IsCreateRoleProcedureAsActiveProcedure();

	//@检查当前流程是否为大厅流程
	bool IsHomeProcedureAsActiveProcedure();

	//@检查当前流程是否为组队副本流程
	bool IsTeamBattleAsActiveProcedure();

	//@检查当前流程是否为世界地图流程
	bool IsSelectMissionAsActiveProcedure();

	//@检查当前流程是否为竞技场流程
	bool IsArenaAsActiveProcedure();

	//@强制进行内存回收处理
    void         ForceFreeMemory();

	//@强制进行帧动画特效回收处理
	void        ForceClearAnimationCache();

public:
	//@定时验证尚未验证的订单
	void         VerifyIAPList(float dt);

public:
	//@标配
	bool         Init();
	void         Tick(float interval);
	void         Destroy();
    
public:
	//@为了解决CY SDK1.0.7问题，做的延时方法
    void DelayForCYSDK(float time);

public:
	//@外部退出游戏回调事件
	virtual  void  onAppExit();

	//@外围关闭WebDialog回调事件
	virtual  void  onWebDialogClose(int type);

	//@系统网络发生切换回调事件(wifi->3g or 3g->wifi)
	virtual  void  onNetworkChanged();

	//@系统网络断开回调事件
	virtual  void  onNetworkDisConnected();

	//@查询到系统远程推送唯一key事件
	virtual  void  onQueryAppServerPushId(std::string pushId);
public:
	//@游戏失去焦点处理操作
	virtual  void  applicationDidPaused();
	//@游戏获得焦点处理操作
	virtual  void  applicationDidResumed();
	//@初始化完成之后，进行必要操作处理
    virtual  bool  applicationDidFinishLaunching();
	//@游戏进入后台处理操作
    virtual  void  applicationDidEnterBackground();
	//@游戏进入前台运行处理操作
    virtual  void  applicationWillEnterForeground();
};


#endif
