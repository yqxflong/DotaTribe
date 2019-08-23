//Name：	ServerInfoData
//Function：充值相关的控制器
//Written By：lvyunlong

#ifndef   _DOTATRIBE_PAYGOODSDATAHANDLER_H
#define   _DOTATRIBE_PAYGOODSDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>
#include <cocos2d.h>
#include "../include/VariableSystem.h"
#include <include/mem/DPacket.h>
using namespace std;

enum
{
	_ENUM_STATE_PAYORDER_SUCCESS_ = 0,  //0: 验证成功
	_ENUM_STATE_PAYORDER_PAYMONEY_,		//1：该订单已经加过钱
	_ENUM_STATE_PAYORDER_FAIL_,			//2：订单验证失败
	_ENUM_STATE_PAYORDER_PLATFORMRETRY_,//3：平台处理中，押后重试
	_ENUM_STATE_PAYORDER_SERVERRETRY_,	//4：系统繁忙，请稍后再试
};

class PayGoodsData
{
public:
	PayGoodsData();
	~PayGoodsData();
public:
	std::string goodsName_;			//商品的名字
	std::string goodsId_;			//商品的Id	
	std::string goodsRegisterId_;	//商品注册的ID序列号
	float goodsPrice_;				//商品价钱
	int goodNumber_;				//商品数量
	int iconId_;					//商品的iconId
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

class DoublePayData
{
public:
	DoublePayData();
	~DoublePayData();
public:
	std::string goodsRegisterId;
	unsigned char isDoublePay;
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

class PayGoodsControlDataHandler:public IDataHandler,public cobra_win::Singleton2<PayGoodsControlDataHandler>{

public:
	bool m_isBIAPCheck;					//进入游戏是否查看本地游戏IAP订单
	bool m_isBPaylist;					//商品裂变是否收到
	bool m_isBInitmentEnv;				//是否初始化过支付环境
	int m_CurVistorPayIndex;			//游客要买的IndexPay
	std::string m_strTempOrderld;		//确认订单服务器返回订单
	unsigned char m_aSureOrderldState;	//确认订单服务器返回订单状态
	std::string m_strPPOrderId;			//服务器生成PP订单
	std::string m_strPPGoodsId;			//对应服务器生成PP订单商品ID
	unsigned char m_GoodsCount;
	//std::map<std::string ,int> 	m_OrderldList;				//反馈充值订单
	std::vector<PayGoodsData*>	m_PayGoodsList;				//充值商品列表
	std::vector<std::string>	m_AndroidPayStr;
	int m_ShowDoubleArray[3];
	bool m_isBIAPTick;
	int m_IAPTickCount;
public:
	PayGoodsControlDataHandler();
	virtual ~PayGoodsControlDataHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	/*
		请求充值钻石列表信息
	*/
	void  ToServerRechargeListPacket(unsigned char channel);

	/*
		请求充值确认信息
	*/
	void  ToServerPaySurePacket(unsigned char channel,std::string iapid,std::string orderld,std::string transactReceipt);
	/*
		请求创建订单信息forPP
	*/
	void  ToServerCreatePPOrederPacket(std::string goodsid);

	/*
		通过注册id找到商品id
	*/
	PayGoodsData* ByRegisterIdFindGoodsData(std::string registerid);

	/*
		处理确认订单服务器返回操作	
	*/
	void SureServerOrederBack(std::string strorderldTemp,unsigned char orderldstate);
	/*
		将缓存的订单发送给服务器验证
	*/
	void  LocalPayIAPCheck();
	/*
		SDK返回之后30后给服务器发送一次订单
	*/
	void TimeTickToServerIapCheck();
	/*
		清空商品列表	
	*/
	void  ClearPayItemList();
	/*
		请求支付附加信息
	*/
	void ToServerAdditionPayInfo();
	/*
		读取附近支付信息
	*/
	bool ReadPayAddtionPacketData(cobra_win::DPacket &packet);
	/*
		请求充值三档双倍
	*/
	void ToServerDoublePayInfo();
	/*
		请求充值三档双倍返回
	*/
	void ReadDoublePayInfoData(cobra_win::DPacket &packet);
};

#define PAYGOODSCONTROLDATAHANDLER	 PayGoodsControlDataHandler::get_instance2()
#endif