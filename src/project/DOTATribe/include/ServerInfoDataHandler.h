//Name：	ServerInfoDataHandler
//Function：游戏登陆相关流程控制器
//					*包含游戏登陆流程及游客信息处理
//Written By：尹强

#ifndef   _DOTATRIBE_SERVERINFODATAHANDLER_H
#define   _DOTATRIBE_SERVERINFODATAHANDLER_H

#include <cocos2d.h>
#include "../include/DotaGameConfig.h"
#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/LimitedActivityHandler.h"
#include <list>
#include <string>
#include <include/mem/DPacket.h>

//HTTP协议的强制程度
enum{
	_HTTP_STATE_UNKNOWN_=-1,
	_HTTP_STATE_DISTINCT_,
	_HTTP_STATE_NORMAL,
};

enum
{
		_TYPE_LOGIN_STATE_UNKOWN_ = -1,
		_TYPE_LOGIN_STATE_STANDBY_,						//在Startwindow待机
		_TYPE_LOGIN_STATE_GAMESERVER_CONNECT,			//服务器连接
		_TYPE_LOGIN_STATE_GAMESERVER_SUCCESS_,			//连接服务器成功
		_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME,			//已经进入游戏
};

enum{
	kSI_ATYPE_STANDBY=-1,	//未登录状态
	kSI_ATYPE_LOGIN,		//已登录
};

enum{
	_TYPE_NOTICEBOX_GATEWAY_,				//网关发送公告
	_TYPE_NOTICEBOX_GAMESERVER_,			//游戏服务器发送公告
};

enum
{
	_TYPE_TITLE_NONE,
	_TYPE_TITLE_SOON,
	_TYPE_TITLE_ALL,
};

enum{
    /**
     * 购买成功
     */
	PPPayResultCodeSucceed	= 0,
    /**
     * 禁止访问
     */
    PPPayResultCodeForbidden = 1,
    /**
     * 该用户不存在
     */
    PPPayResultCodeUserNotExist = 2,
    /**
     * 必选参数丢失
     */
    PPPayResultCodeParamLost = 3,
    /**
     * PP币余额不足
     */
    PPPayResultCodeNotSufficientFunds = 4,
    /**
     * 该游戏数据不存在
     */
    PPPayResultCodeGameDataNotExist = 5,
    /**
     * 开发者数据不存在
     */
    PPPayResultCodeDeveloperNotExist = 6,
    /**
     * 该区数据不存在
     */
    PPPayResultCodeZoneNotExist = 7,
    /**
     * 系统错误
     */
    PPPayResultCodeSystemError = 8,
    /**
     * 购买失败
     */
    PPPayResultCodeFail = 9,
    /**
     * 与开发商服务器通信失败，如果长时间未收到商品请联系PP：客服电话：020-38276673　 QQ：800055602
     */
    PPPayResultCodeCommunicationFail = 10,
    /**
     * 开发商服务器未成功处理该订单，如果长时间未收到商品请联系PP客服：电话：020-38276673　 QQ：800055602
     */
    PPPayResultCodeUntreatedBillNo = 11,
    /**
     * 非法访问，可能用户已经下线
     */
    PPPayResultCodeUserOffLine = 88,
};

//网关服务器信息
struct	GateWayServerData  
{
	std::string	ip_;
	int port_;
	GateWayServerData()
	{
		port_ = 0;
	}
};

//游戏服务器信息
struct	GameServerdata  
{
	bool isNull;		//标志，是否为空数据结构
	int id_;
	std::string	name_;
	std::string	ip_;
	int port_;
	unsigned char state_;		//0:维护中  如果不是0:查看level
	unsigned char level_;		//推荐级别: 0为新服   其他为:火爆
	int title;					//是否标题 0无标题  1：最近登录标题  2：所有服务器
	bool isshow_;				//是否显示
	GameServerdata()
	{
		isNull=false;
		id_ = 0;
		port_ = 0;
		state_ = -1;
		level_=0;
		title = 0;
		isshow_ = true;
	}
};

enum{
	_FUNCTION_CDKEY_ = 1
};

struct FunctionData{
	int functionId;
	bool isOpen;
	FunctionData(){
		functionId = -1;
		isOpen = false;
	}
};

class GameServerListHandler
{
public:
	std::list<GameServerdata>	m_ServerInfoList;
public:
	GameServerListHandler(){
		ClearServerInfoList();
	}
	void ClearServerInfoList()
	{
		m_ServerInfoList.clear();
	}
};

struct LoginParams;
class ServerInfoDataHandler:public IDataHandler,public cobra_win::Singleton2<ServerInfoDataHandler>, public cocos2d::CCPlatformDelegate{
private:
	int m_nUserType;		//该用户类型
	std::string m_nUserAccountName;		//该用户的账号
	std::string m_nUserAccountPWD;		//该用户的密码
	int m_nCurGameStatus;		//当前登陆状态
	int m_Key;			//登陆口令（每次认证返回的）
	GameServerdata m_CurServerData;	//当前所选服务器的数据
	int m_bIsNewRole;		//是否为创建角色0:否 1：是
public:
	int	CurSendHttpPacketType_;		//记录当前发送的http包的类型
	std::vector<int>	m_RoleIdlist;
	unsigned char m_Rolenum;
public:
	GameServerListHandler *GSListHandler_;
public:
	bool m_isBNoticeTab;	//登录公告刷新标志位
	bool m_isSelServerWindow;	//服务器列表刷新标志位

	bool m_isNoticeNeedShow;
	std::map<int,std::string> m_FontStyleIdMap;		//登录公告字体格式
	std::vector<NoticeData> m_ContentVector;		//登录公告正文

	std::vector<FunctionData> m_FunctionDatas;
private:
	inline LoginParams _getLoginParams();
public:
	ServerInfoDataHandler();
	virtual ~ServerInfoDataHandler();
	virtual bool init();
	virtual void onDestroy();
	void decodePacketData(cobra_win::DPacket & packet);
	void decodePacketData_QuickRegister(cobra_win::DPacket & packet);
	void decodePacketData_Rolelist(cobra_win::DPacket & packet);
	void decodePacketData_Notice_Gateway(cobra_win::DPacket & packet);
	void decodePacketData_CheckOpenFunction(cobra_win::DPacket & packet);
	void AfterDecodeServerList();
	void AfterDecodeNoticeGatewayData();

	/*
		服务器请求超时事件
	*/
	static void OnEventServerRequest(int iEventType, std::string owerData, std::list<std::string>& paramList);


	/*
		通过服务器索引返回当前节点信息
	*/
	const GameServerdata& ByIndexServerInfo(int index);
	/*
		最近登录的索引  没有返回-1
	*/
	int GetSoonServerIndex();
	/*
		所有服务器索引
	*/
	int GetAllServerIndex();
	/*
		整合当前显示服务器链表
	*/
	void IntegraServerInfo();
	/*
		根据id找到某组服务器数据
	*/
	GameServerdata GetServerDataByID(int id);

	/*
		设置默认游戏服务器				
	*/				
	void CheckDefaultGameServer();

	/*
		记录服务器信息从文件到内存
	*/
	void RecordTheGameServerInfo();

	/*
		记录服务器信息从外部到内存
	*/
	void RecordTheGameServerInfo(GameServerdata& gServerData);

	/*
		将选择的服务器ID写入文件
	*/
	void WriteTheGameServerInfo(const GameServerdata& gServerData);
	/*
		设置该用户的游戏账号及密码
	*/
	void setCurAccountNameAndPWD(std::string aname,std::string apwd);
	/*
		设置该用户的游戏账号及密码为游客账号密码
	*/
	void setCurAccountNameAndPWDByGuest();
	/*
		获取当前服务器参数
	*/
	int GetCurrentServerId() const;
	const char* getCurServerName();
	int GetCurServerState() const;
	int GetCurServerLevel() const;
	const char* getCurServerIP();
	int getCurPort();

	void setCurKey(int key){
		m_Key = key;
	}
	int getCurKey()
	{
		return m_Key;
	}
	//
	/*
		记录游客账号和密码
	*/
	void WriteVisitorAccountNameAndPWD(std::string aname,std::string apwd);
	/*
		记录当前账号和密码为注册用户的账号密码
	*/
	void WriteLoginAccountNameAndPWD();
	/*
		连接服务器之后的操作
	*/
	void HandleAfterConnectGameServer();

	/*
		获取当前连接服务器的状态
	*/
	int GetCurGameStatus();
	/*
		获取当前连接服务器的状态
	*/
	void SetCurGameStatus(int status);
	/*
		判断当前是否未选服务器
	*/
	bool HasGameServer();
public:

	/*
		客户端激活
	*/
	void ToServer_ClientActive();

	/*
		获取服务器列表_开机
	*/
	void QueryServerListData();
	/*
		获取服务器列表_选服界面
	*/
	void QueryServerListData_selServerWindow();
	/*
		获取网关登录公告	
	*/
	void QueryNoticeGatewayData();
	/*
		处理当前网络连接成功后相关事宜
	*/
	void HandleCurrentOperationAfterConnetNetwork();
	/*
		处理快速注册后的事宜
	*/
	void HandleAfterQuickRegister();
	/*
		处理认证后的事宜
	*/
	void HandleAfterLogin(int result);
	/*
		处理获取人物列表后的事宜
	*/
	void HandleAfterRoleList();
	/*
		处理获取开机人物信息后的事宜
	*/
	void HandleAfterRoleInfo();

	/*
		注销游戏
	*/
	void LogoutGame();
	/*
		检查是否清空心跳计数器
	*/
	bool CanResetCounter_HeartCheck();
	/*
		发送登陆请求
	*/
	void SendAccountLogin();
	/*
		发送注册账号
	*/
	void SendAccountRegister();
	/*
		连接游戏服务器
	*/
	void ConnectToGameServer();
	/*
		处理用户登陆结果
	*/
	void HandleAfterLogin();

	/*
		登陆流程初始化
	*/
	void LoginProcedureInit();

	/*
		处理socket连接失败
	*/
	void HandleSocketConnectFail();

	/*
		处理HTTP连接失败
	*/
	void HandleHttpConnectFail();

	/*
		通知socket断开了
	*/
	void NotifySocketClosed();

	/*
		通知网络状态切换了
	*/
	void NotifyNetworkChanged();

	/*
		处理socket断开
	*/
	void HandleConnectServerFail();
	
	/*
		处理断线重连
	*/
	void HandleDisConnect(bool isreconnect);

	/*
		返回登陆界面
	*/
	void BackToStartWindow();
    
    void DelayForCYSDK();

public:
	/*
		从内存中获得当前账号
	*/
	std::string GetCurAccountName();
	/*
		检查账号
	*/
	void CheckAccountBeforeEnterGame();
	/*
		设置当前用户类型
	*/
	void SetCurUserType(int type){m_nUserType=type;};
	/*
		清空游客账号信息
	*/
	void DeleteVisitorAccountInfo();
	/*
		清空所有帐号信息
	*/
	void DeleteAllAccountInfo();
	/*
		注销账号信息
	*/
	void LogoutAccountInfo();
	/*
		当前用户是否为登陆状态
	*/
	bool IsLoginGame();

	/*
		服务器通知强行断开连接
	*/
	void ForceDisconnect();

	/*
		自行断开游戏服务器
	*/
	void DisconnectGameServer_Normal();
//==============获取设备信息===========
public:
	//获得设备操作系统
	std::string Get_Device_OS();
	//获得设备ID
	std::string Get_Device_ID();
	//获得上线平台
	unsigned char Get_Channel_ID();
	//获得上线平台
	unsigned char Get_Channel_ID(int sdktype);
	//获得广告推广平台
	std::string Get_tuiguang_ad_Channel();

	//操作系统版本
	std::string Get_Device_OS_Version();
	//MACAddress 
	std::string Get_Device_Mac();
	//Version
	std::string Get_GAME_Version();
	//telecomOperator  
	std::string Get_Device_telecomOperator();
	//AppendParam   
	std::string Get_Other_Param();
	//是否越狱   
	unsigned char Get_Hacked();

//==============登陆公告=================//
public:
	void LoginNotice_Request(bool istab = false);
	void HandleAfterLoginNoticeResp(const std::string& content);
	
public:
	void CheckOpenFun_Request();


public:
	//获得平台登陆参数
	SDKLoginParam GetSDKLoginParam();
	
	//获得游戏登陆参数
	GameLoginParam GetGameLoginParam();

	//设置初始化分派器
	void SetLoginSdkDelegate();

	//登陆sdk
	void LoginSdk(bool isExpired=false);

	//从sdk登出
	void LogoutSdk();

	//显示Sdk账号中心
	void ShowSdkCenter();

	//显示悬浮窗
	void ShowSuspendWindow(bool status);

	//和外层共享玩家角色信息
	void SharePlayerAccountInfo();

	//sdk登陆成功回调
	virtual void onLoginResultHandler(int sdkType, bool bSuccess, std::string param0 = "", std::string param1 = "", std::string param2 = "", std::string param3 = "", std::string param4 = ""
		, std::string param5 = "", std::string param6 = "", std::string param7 = "", std::string param8 = "", std::string param9 = "");

	virtual void onLogoutCallBack(int sdkType, bool bSuccess, std::string param0 = "", std::string param1 = "", std::string param2 = "", std::string param3 = "", std::string param4 = ""
		, std::string param5 = "", std::string param6 = "", std::string param7 = "", std::string param8 = "", std::string param9 = "");

	//登陆过期
	void LoginOutOfDate();

	//支付回调
	virtual void onPayResultCallBack(int sdkType, int resultCode, std::string param0 = "",std::string param1 = "");

};

#define SERVERINFODATAINFO	 ServerInfoDataHandler::get_instance2()
#endif