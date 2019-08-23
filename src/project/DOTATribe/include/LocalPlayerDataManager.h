//Name：LocalPlayerDataManager
//Function：管理玩家本地数据
//#存于硬盘，MD5校验
//#每次改变变量，需调用NeedSaveToDisk(),下一帧会被存到硬盘中
//Maintain：尹强

#ifndef  _DOTATRIBE_LOCALPLAYERDATAMANAGER_H_
#define  _DOTATRIBE_LOCALPLAYERDATAMANAGER_H_

#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/mem/MemNode.h>

using  namespace  cobra_win;

class LocalStorage
{
public:
	virtual void Save(cobra_win::EPacket & packet) = 0;
	virtual void Load(cobra_win::DPacket & packet) = 0;
	virtual int PacketLength() = 0;
	virtual void SendParam(MemNode* pNode) = 0;
};

//sdk登陆参数
class SDKLoginParam : public LocalStorage
{
public:
	enum{
		_platform_null_ = 0,//尚未登陆
		_platform_guest_ = 1,	//游客登陆
		_platform_appstore_ = 2,
		_platform_cyou_ = 3,		
		_platform_91_ = 4,			//91助手-全
		_platform_pp_ = 5,			//PP助手-IOS
		_platform_wandoujia_	= 6,	//豌豆荚
		_platform_xiaomi_		= 7,	//小米
		_platform_uc_			= 8,	//UC
		_platform_360_			= 9,	//360
		_platform_tongbutui_	= 10,	//同步推 ios
		_platform_anzhi_		= 11,	//安智
		_platform_duoku_		= 12,	//多酷
		_platform_oppo_			= 13,	//oppo
		_platform_dangle_		= 14,	//当乐
		_platform_jifeng_		= 15,	//机锋
		_platform_huawei_		= 16,	//华为
		_platform_lenovo_		= 17,	//联想
		_platform_aiyouxi_		= 18,	//电信爱游戏
		_platform_yiwan_		= 19,	//益玩
        _platform_cyou_jbreak_	= 20,	//畅游越狱

	};
public:
	int m_iSdkType;//平台类型
	std::string m_Param0;
	std::string m_Param1;
	std::string m_Param2;
	std::string m_Param3;
	std::string m_Param4;
	std::string m_Param5;
	std::string m_Param6;
	std::string m_Param7;
	std::string m_Param8;
	std::string m_Param9;
public:
	SDKLoginParam()
	{
		m_iSdkType = _platform_null_;
	};

	virtual void Save(cobra_win::EPacket & packet);
	virtual void Load(cobra_win::DPacket & packet);
	virtual int PacketLength();
	virtual void SendParam(MemNode* pNode);
};

//游戏登陆参数
class GameLoginParam : public LocalStorage
{
public:
	std::string m_Param0;
	std::string m_Param1;

public:
	virtual void Save(cobra_win::EPacket & packet);
	virtual void Load(cobra_win::DPacket & packet);
	virtual int PacketLength();
	virtual void SendParam(MemNode* pNode);
};

class LocalPlayerDataManager : public IDataManager, public cobra_win::Singleton2<LocalPlayerDataManager>
{
protected:
	bool  m_bNeedSaveToDisk; // 存盘标志位

private:
	SDKLoginParam m_SdkLoginParam;		//sdk登陆参数
	GameLoginParam m_GameLoginParam;	//游戏登陆参数

protected:
	std::string m_LastIAPServerId; // 上一次购买时服务器Id（IOS下异常订单补救措施使用）
	std::string m_LastIAPPlayerId; // 上一次购买时玩家Id（IOS下异常订单补救措施使用）

public:
	/************************************************************************/
	/*IAP支付本地存储订单列表，考虑到兼容IOS和Android平台，并且在切换服务器
	  ，切换账号情况下，不至于丢失玩家支付订单*/
	/************************************************************************/
	struct _LOCAL_PLAYER_UNVERIFY_IAP_
	{
		enum
		{
			_IAP_PLATFORM_IOS_,      // IOS平台订单
			_IAP_PLATFORM_ANDROID_,  // Android平台订单
		};

		int         mPlatform;           // 平台类型
		std::string mServerId;           // 登陆服务器Id
		std::string mPlayerId;           // 登陆玩家Id
		std::string mProductId;          // 购买商品Id
		std::string mTransactionId;      // 订单Id 
		std::string mTransactionReceipt; // 订单回执信息(IOS有用)
		int         mGoodsId;            // 商品唯一Id(畅游支付专用)
		int         mChargePoint;        // Android专用
		int         mVerifyFailedCount;  // IAP校验失败的次数
		_LOCAL_PLAYER_UNVERIFY_IAP_()
		{
			mPlatform = _IAP_PLATFORM_IOS_;
			mGoodsId  = 0;
			mChargePoint = 0;
			mVerifyFailedCount = 0;
		}
	};

	/************************************************************************/
	/*本地存储的服务器ID的结构
	/************************************************************************/
	struct _LOCAL_SERVER_ID_
	{
		int id_;	//记录服务器的ID
		long long lasttime_;	//记录上次登录的时间
		_LOCAL_SERVER_ID_()
		{
			id_=0;
			lasttime_=0;
		}
	};


public:
	std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_> m_UnVerifyIAPList; // 本地尚未验证的支付订单列表

	std::map<int,_LOCAL_SERVER_ID_> m_listLocalServerID;	//存储本地登录过的服务器

public:
	LocalPlayerDataManager(bool bLoadFromDB, bool bEncryption):IDataManager(bLoadFromDB, bEncryption){};
	virtual ~LocalPlayerDataManager(){};

private:
	void _loadServerID_Param(cobra_win::DPacket & packet);
	void _loadIAP_Param(cobra_win::DPacket & packet);
	void _saveServerID_Param(cobra_win::EPacket & packet);
	void _saveIAP_Param(cobra_win::EPacket & packet);

public:
	/*
		平台登陆参数
	*/
	void SetSdkLoginParam(SDKLoginParam & loginParam);
	SDKLoginParam GetSdkLoginParam();

	/*
		游戏登陆参数
	*/
	void SetGameLoginParam(GameLoginParam & loginParam);
	GameLoginParam GetGameLoginParam();

public:
	/*
		设置上一次购买时服务器Id
	*/
	void  SetLastIAPServerId(std::string serverId);
	/*
		获得上一次购买时服务器Id
	*/
	std::string GetLastIAPServerId();
	/*
		设置上一次购买时玩家Id
	*/
	void  SetLastIAPPlayerId(std::string playerId);
	/*
		获得上一次购买时玩家Id
	*/
	std::string GetLastIAPPlayerId();

public:
	/*
		插入IOS下一个支付订单(IOS专用)
	*/
	void  InsertPayment(std::string serverId, std::string playerId, std::string productId, int goodsId, std::string transactionId, std::string transactionReceipt);
	/*
		插入Android下一个支付订单(Android专用)
	*/
	void  InsertPayment(std::string serverId, std::string playerId, std::string productId, std::string transactionId);
	/*
		删除指定的订单
	*/
	void  DeletePayment(std::string transactionId);
	/*
		购买服务器告诉购买成功
	*/
	void  ServerSuccessCheckOrder(std::string IAPId);
	/*
		获得本地尚未校验的订单列表
	*/
	std::map<std::string, _LOCAL_PLAYER_UNVERIFY_IAP_>& GetUnVerifyIAPList();

public:
	//插入需要保存的服务器ID，和插入的时间(s)
	void InsertServerID(int sid,long long time);

	//获取最新的serverid list
	std::list<int> GetLatestServerIDList();

public:
	/*
		设置需要存盘
	*/
	void  NeedSaveToDisk();

public:
    /*
        获得对应数据管理器对应资源的名称（可为文件，也可以为数据库表名称）
    */
    virtual   std::string  GetName();
	/*
        获得对应数据管理器对应资源的名称（可为文件，也可以为数据库表名称）
    */
    virtual   std::string  GetTempName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual   unsigned int GetSize();
    
public:
	/*
        初始化数据管理器
    */
	virtual   bool   Init();
	/*
        数据管理器桢更新
    */
	virtual   void   Tick();
	/*
        销毁数据管理器
    */
	virtual   void   Destroy();
	/*
		重新加载数据管理器
	*/
	virtual   bool   Reload();
    
private:
    /*
        加载对应的资源文件
    */
    virtual   bool   LoadFromFile();
    /*
        加载对应的资源流信息
    */
    virtual   bool   LoadFromDB();

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual   bool   Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/ 
	virtual   bool   VarifyAfterLoadAll();

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual   bool   LoadData(char* pBuffer, unsigned int iBufferLen);

public:
	/*
		系统进入后台事件响应处理
	*/
	void  OnSystemEnterBackEventHandler();
	/*
		系统进入前台事件响应处理
	*/
	void  OnSystemEnterFrontEventHandler();
	/*
		系统暂停事件响应处理
	*/
	void  OnSystemPauseEventHandler();
	/*
		系统恢复事件响应处理
	*/
	void  OnSystemResumeEventHandler();

private:
	/*
		加载文件
	*/
	char* LoadDBFile(std::string fileName, long& length);
	/*
		同步保存
	*/
	void  SaveToFile();
	/*
		同步到初始状态(一般文件校验失败，则直接设置为初始状态)
	*/
	void  SynToInitialization();

private:
	/*
		加载存档文件
	*/
	bool  LoadFromFile(char* pBuffer, unsigned int iBufferLen);
    
private:
	friend   class   Singleton2<LocalPlayerDataManager>;
	
};



#endif
