#ifndef  _DOTATRIBE_IAPSYSTEM_H_
#define  _DOTATRIBE_IAPSYSTEM_H_


#include <include/common/Singleton.h>
#include <cocos2d.h>
using  namespace  cobra_win;

class IAPSystem : public cocos2d::CCPaymentDelegate, public cobra_win::Singleton2<IAPSystem>
{
public:
	IAPSystem();
	virtual ~IAPSystem();

public:
	//@支付功能是否可用
	bool  IsAvailable();
	//@本地是否存在指定购买订单
	bool  IsHasIAPId(std::string iapId);

public:
	/*
		开始初始化支付环境
		1:单机游戏在程序启动时即可调用
		2:网络游戏需要确保和服务器建立连接之后再调用
	*/
	void  InitPaymentEnv();

public:
	//@购买指定商品类型的商品
	void  BuyProductByType(int productType);
	//@购买指定商品Id的商品
	void  BuyProductById(std::string productId);
	//@SDk平台购买指定商品ID的商品
	void SdkBuyProductById(std::string productId);
	//@本地购买队列中移除对应IAP订单(IOS专用)
	void  RemoveIAPId(std::string iapId);
	//@结束购买
	void  EndPayment();

public:
	//@校验指定的订单号
	void  VerifyIAPIdentifier();

public:
	//@标配
	bool  Init();
	void  Tick();
	void  Destroy();

public:
	//@购买失败
	virtual  void  onPayFailed(std::string IAPId, std::string error);
	/*
		购买成功
		transactionId: IOS下AppStore订单Id
		transactionReceipt: IOS下AppStore订单回执信息
	*/
	virtual  void  onPaySuccess(std::string IAPId, std::string transactionId, std::string transactionReceipt);
	//@校验订单成功
	virtual  void  onVerifySuccess(std::string IAPId);
	//@校验订单失败
	virtual  void  onVerifyFailed(std::string IAPId, std::string error);
	//@找回Non-Consume商品(IOS专用)
	virtual  void  onRestoreSuccess(std::string IAPId);
	//@插入本地订单数据
	virtual void insertPayment(std::string productId,std::string transactionId);


public:
	IAPSystem* GetLuaInstance(){
		return IAPSystem::get_instance2();
	}
};

#define  IAPSYSTEM  (IAPSystem::get_instance2())


#endif
