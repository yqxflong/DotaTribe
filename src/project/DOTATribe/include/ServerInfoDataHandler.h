//Name��	ServerInfoDataHandler
//Function����Ϸ��½������̿�����
//					*������Ϸ��½���̼��ο���Ϣ����
//Written By����ǿ

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

//HTTPЭ���ǿ�Ƴ̶�
enum{
	_HTTP_STATE_UNKNOWN_=-1,
	_HTTP_STATE_DISTINCT_,
	_HTTP_STATE_NORMAL,
};

enum
{
		_TYPE_LOGIN_STATE_UNKOWN_ = -1,
		_TYPE_LOGIN_STATE_STANDBY_,						//��Startwindow����
		_TYPE_LOGIN_STATE_GAMESERVER_CONNECT,			//����������
		_TYPE_LOGIN_STATE_GAMESERVER_SUCCESS_,			//���ӷ������ɹ�
		_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME,			//�Ѿ�������Ϸ
};

enum{
	kSI_ATYPE_STANDBY=-1,	//δ��¼״̬
	kSI_ATYPE_LOGIN,		//�ѵ�¼
};

enum{
	_TYPE_NOTICEBOX_GATEWAY_,				//���ط��͹���
	_TYPE_NOTICEBOX_GAMESERVER_,			//��Ϸ���������͹���
};

enum
{
	_TYPE_TITLE_NONE,
	_TYPE_TITLE_SOON,
	_TYPE_TITLE_ALL,
};

enum{
    /**
     * ����ɹ�
     */
	PPPayResultCodeSucceed	= 0,
    /**
     * ��ֹ����
     */
    PPPayResultCodeForbidden = 1,
    /**
     * ���û�������
     */
    PPPayResultCodeUserNotExist = 2,
    /**
     * ��ѡ������ʧ
     */
    PPPayResultCodeParamLost = 3,
    /**
     * PP������
     */
    PPPayResultCodeNotSufficientFunds = 4,
    /**
     * ����Ϸ���ݲ�����
     */
    PPPayResultCodeGameDataNotExist = 5,
    /**
     * ���������ݲ�����
     */
    PPPayResultCodeDeveloperNotExist = 6,
    /**
     * �������ݲ�����
     */
    PPPayResultCodeZoneNotExist = 7,
    /**
     * ϵͳ����
     */
    PPPayResultCodeSystemError = 8,
    /**
     * ����ʧ��
     */
    PPPayResultCodeFail = 9,
    /**
     * �뿪���̷�����ͨ��ʧ�ܣ������ʱ��δ�յ���Ʒ����ϵPP���ͷ��绰��020-38276673�� QQ��800055602
     */
    PPPayResultCodeCommunicationFail = 10,
    /**
     * �����̷�����δ�ɹ�����ö����������ʱ��δ�յ���Ʒ����ϵPP�ͷ����绰��020-38276673�� QQ��800055602
     */
    PPPayResultCodeUntreatedBillNo = 11,
    /**
     * �Ƿ����ʣ������û��Ѿ�����
     */
    PPPayResultCodeUserOffLine = 88,
};

//���ط�������Ϣ
struct	GateWayServerData  
{
	std::string	ip_;
	int port_;
	GateWayServerData()
	{
		port_ = 0;
	}
};

//��Ϸ��������Ϣ
struct	GameServerdata  
{
	bool isNull;		//��־���Ƿ�Ϊ�����ݽṹ
	int id_;
	std::string	name_;
	std::string	ip_;
	int port_;
	unsigned char state_;		//0:ά����  �������0:�鿴level
	unsigned char level_;		//�Ƽ�����: 0Ϊ�·�   ����Ϊ:��
	int title;					//�Ƿ���� 0�ޱ���  1�������¼����  2�����з�����
	bool isshow_;				//�Ƿ���ʾ
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
	int m_nUserType;		//���û�����
	std::string m_nUserAccountName;		//���û����˺�
	std::string m_nUserAccountPWD;		//���û�������
	int m_nCurGameStatus;		//��ǰ��½״̬
	int m_Key;			//��½���ÿ����֤���صģ�
	GameServerdata m_CurServerData;	//��ǰ��ѡ������������
	int m_bIsNewRole;		//�Ƿ�Ϊ������ɫ0:�� 1����
public:
	int	CurSendHttpPacketType_;		//��¼��ǰ���͵�http��������
	std::vector<int>	m_RoleIdlist;
	unsigned char m_Rolenum;
public:
	GameServerListHandler *GSListHandler_;
public:
	bool m_isBNoticeTab;	//��¼����ˢ�±�־λ
	bool m_isSelServerWindow;	//�������б�ˢ�±�־λ

	bool m_isNoticeNeedShow;
	std::map<int,std::string> m_FontStyleIdMap;		//��¼���������ʽ
	std::vector<NoticeData> m_ContentVector;		//��¼��������

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
		����������ʱ�¼�
	*/
	static void OnEventServerRequest(int iEventType, std::string owerData, std::list<std::string>& paramList);


	/*
		ͨ���������������ص�ǰ�ڵ���Ϣ
	*/
	const GameServerdata& ByIndexServerInfo(int index);
	/*
		�����¼������  û�з���-1
	*/
	int GetSoonServerIndex();
	/*
		���з���������
	*/
	int GetAllServerIndex();
	/*
		���ϵ�ǰ��ʾ����������
	*/
	void IntegraServerInfo();
	/*
		����id�ҵ�ĳ�����������
	*/
	GameServerdata GetServerDataByID(int id);

	/*
		����Ĭ����Ϸ������				
	*/				
	void CheckDefaultGameServer();

	/*
		��¼��������Ϣ���ļ����ڴ�
	*/
	void RecordTheGameServerInfo();

	/*
		��¼��������Ϣ���ⲿ���ڴ�
	*/
	void RecordTheGameServerInfo(GameServerdata& gServerData);

	/*
		��ѡ��ķ�����IDд���ļ�
	*/
	void WriteTheGameServerInfo(const GameServerdata& gServerData);
	/*
		���ø��û�����Ϸ�˺ż�����
	*/
	void setCurAccountNameAndPWD(std::string aname,std::string apwd);
	/*
		���ø��û�����Ϸ�˺ż�����Ϊ�ο��˺�����
	*/
	void setCurAccountNameAndPWDByGuest();
	/*
		��ȡ��ǰ����������
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
		��¼�ο��˺ź�����
	*/
	void WriteVisitorAccountNameAndPWD(std::string aname,std::string apwd);
	/*
		��¼��ǰ�˺ź�����Ϊע���û����˺�����
	*/
	void WriteLoginAccountNameAndPWD();
	/*
		���ӷ�����֮��Ĳ���
	*/
	void HandleAfterConnectGameServer();

	/*
		��ȡ��ǰ���ӷ�������״̬
	*/
	int GetCurGameStatus();
	/*
		��ȡ��ǰ���ӷ�������״̬
	*/
	void SetCurGameStatus(int status);
	/*
		�жϵ�ǰ�Ƿ�δѡ������
	*/
	bool HasGameServer();
public:

	/*
		�ͻ��˼���
	*/
	void ToServer_ClientActive();

	/*
		��ȡ�������б�_����
	*/
	void QueryServerListData();
	/*
		��ȡ�������б�_ѡ������
	*/
	void QueryServerListData_selServerWindow();
	/*
		��ȡ���ص�¼����	
	*/
	void QueryNoticeGatewayData();
	/*
		����ǰ�������ӳɹ����������
	*/
	void HandleCurrentOperationAfterConnetNetwork();
	/*
		�������ע��������
	*/
	void HandleAfterQuickRegister();
	/*
		������֤�������
	*/
	void HandleAfterLogin(int result);
	/*
		�����ȡ�����б�������
	*/
	void HandleAfterRoleList();
	/*
		�����ȡ����������Ϣ�������
	*/
	void HandleAfterRoleInfo();

	/*
		ע����Ϸ
	*/
	void LogoutGame();
	/*
		����Ƿ��������������
	*/
	bool CanResetCounter_HeartCheck();
	/*
		���͵�½����
	*/
	void SendAccountLogin();
	/*
		����ע���˺�
	*/
	void SendAccountRegister();
	/*
		������Ϸ������
	*/
	void ConnectToGameServer();
	/*
		�����û���½���
	*/
	void HandleAfterLogin();

	/*
		��½���̳�ʼ��
	*/
	void LoginProcedureInit();

	/*
		����socket����ʧ��
	*/
	void HandleSocketConnectFail();

	/*
		����HTTP����ʧ��
	*/
	void HandleHttpConnectFail();

	/*
		֪ͨsocket�Ͽ���
	*/
	void NotifySocketClosed();

	/*
		֪ͨ����״̬�л���
	*/
	void NotifyNetworkChanged();

	/*
		����socket�Ͽ�
	*/
	void HandleConnectServerFail();
	
	/*
		�����������
	*/
	void HandleDisConnect(bool isreconnect);

	/*
		���ص�½����
	*/
	void BackToStartWindow();
    
    void DelayForCYSDK();

public:
	/*
		���ڴ��л�õ�ǰ�˺�
	*/
	std::string GetCurAccountName();
	/*
		����˺�
	*/
	void CheckAccountBeforeEnterGame();
	/*
		���õ�ǰ�û�����
	*/
	void SetCurUserType(int type){m_nUserType=type;};
	/*
		����ο��˺���Ϣ
	*/
	void DeleteVisitorAccountInfo();
	/*
		��������ʺ���Ϣ
	*/
	void DeleteAllAccountInfo();
	/*
		ע���˺���Ϣ
	*/
	void LogoutAccountInfo();
	/*
		��ǰ�û��Ƿ�Ϊ��½״̬
	*/
	bool IsLoginGame();

	/*
		������֪ͨǿ�жϿ�����
	*/
	void ForceDisconnect();

	/*
		���жϿ���Ϸ������
	*/
	void DisconnectGameServer_Normal();
//==============��ȡ�豸��Ϣ===========
public:
	//����豸����ϵͳ
	std::string Get_Device_OS();
	//����豸ID
	std::string Get_Device_ID();
	//�������ƽ̨
	unsigned char Get_Channel_ID();
	//�������ƽ̨
	unsigned char Get_Channel_ID(int sdktype);
	//��ù���ƹ�ƽ̨
	std::string Get_tuiguang_ad_Channel();

	//����ϵͳ�汾
	std::string Get_Device_OS_Version();
	//MACAddress 
	std::string Get_Device_Mac();
	//Version
	std::string Get_GAME_Version();
	//telecomOperator  
	std::string Get_Device_telecomOperator();
	//AppendParam   
	std::string Get_Other_Param();
	//�Ƿ�Խ��   
	unsigned char Get_Hacked();

//==============��½����=================//
public:
	void LoginNotice_Request(bool istab = false);
	void HandleAfterLoginNoticeResp(const std::string& content);
	
public:
	void CheckOpenFun_Request();


public:
	//���ƽ̨��½����
	SDKLoginParam GetSDKLoginParam();
	
	//�����Ϸ��½����
	GameLoginParam GetGameLoginParam();

	//���ó�ʼ��������
	void SetLoginSdkDelegate();

	//��½sdk
	void LoginSdk(bool isExpired=false);

	//��sdk�ǳ�
	void LogoutSdk();

	//��ʾSdk�˺�����
	void ShowSdkCenter();

	//��ʾ������
	void ShowSuspendWindow(bool status);

	//����㹲����ҽ�ɫ��Ϣ
	void SharePlayerAccountInfo();

	//sdk��½�ɹ��ص�
	virtual void onLoginResultHandler(int sdkType, bool bSuccess, std::string param0 = "", std::string param1 = "", std::string param2 = "", std::string param3 = "", std::string param4 = ""
		, std::string param5 = "", std::string param6 = "", std::string param7 = "", std::string param8 = "", std::string param9 = "");

	virtual void onLogoutCallBack(int sdkType, bool bSuccess, std::string param0 = "", std::string param1 = "", std::string param2 = "", std::string param3 = "", std::string param4 = ""
		, std::string param5 = "", std::string param6 = "", std::string param7 = "", std::string param8 = "", std::string param9 = "");

	//��½����
	void LoginOutOfDate();

	//֧���ص�
	virtual void onPayResultCallBack(int sdkType, int resultCode, std::string param0 = "",std::string param1 = "");

};

#define SERVERINFODATAINFO	 ServerInfoDataHandler::get_instance2()
#endif