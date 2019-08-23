#include <cocos2d.h>
#include "../include/IAPSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/VariableSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/NetSystem.h"
#include "../include/TimeSystem.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/IAPProductDataManager.h"
#include <include/common/Random.h>
#include <include/common/String.h>
#include <include/common/MyHash.h>
using  namespace  cobra_win;



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


void IAPSystem::BuyProductByType(int productType)
{
	bool receiveGoods = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_, "NET", "ReceiceGoodsList", receiveGoods);
	if (!receiveGoods)
	{// 尚未收到商品列表，无法购买
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_POP_SYS_TEXT_, SysLangDataManager::get_instance2()->GetSysLangById(SysLangDataManager::_TYPED_SYSLANG_IAP_BUY_LATER_));
		return;
	}

	IAPProductData* pProduct = IAPProductDataManager::get_instance2()->GetIAPProductByProductType(productType);
	if (pProduct == NULL)
		return ;

	char buffer[10240] = "";
	std::string mac = cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceMacAddr();
	if (mac.length() <= 0)
	{
		sprintf(buffer, 
			"%s%lld%u%u%u%u%u%u%u%u%u", 
			cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceIMEI().c_str(), 
			TimeSystem::GetCurrentMicroSecond(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand());
	}
	else
	{
		sprintf(buffer, 
			"%s%u%lld%u%u%u%u%u%u%u%u%u", 
			cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceIMEI().c_str(), 
			MyHash::ap_hash((char*)mac.c_str()),
			TimeSystem::GetCurrentMicroSecond(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand());
	}
	buffer[48] = '\0';

	// 防止丢单，插入本地队列中
	// Android专用的方式
	std::string serverId = "";
	std::string playerId = "";
	LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, pProduct->mProductId, buffer);

	// 购买
	cocos2d::CCDirector::sharedDirector()->getPayment()->pay(pProduct->mProductId, pProduct->mProductName, pProduct->mProductDesc, pProduct->mProductPrice, pProduct->mProductChargePoint, buffer);
}

void IAPSystem::BuyProductById(std::string productId)
{
	IAPProductData* pProduct = IAPProductDataManager::get_instance2()->GetIAPProductByProductId(productId);
	if (pProduct == NULL)
		return ;

	char buffer[10240] = "";
	std::string mac = cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceMacAddr();
	if (mac.length() <= 0)
	{
		sprintf(buffer, 
			"%s%lld%u%u%u%u%u%u%u%u%u", 
			cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceIMEI().c_str(), 
			TimeSystem::GetCurrentMicroSecond(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand());
	}
	else
	{
		sprintf(buffer, 
			"%s%u%lld%u%u%u%u%u%u%u%u%u", 
			cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceIMEI().c_str(), 
			MyHash::ap_hash((char*)mac.c_str()),
			TimeSystem::GetCurrentMicroSecond(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand());
	}
	buffer[48] = '\0';

	// 防止丢单，插入本地队列中
	// Android专用的方式
	std::string serverId = "";
	std::string playerId = "";
	LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, productId, buffer);

	// 购买
	cocos2d::CCDirector::sharedDirector()->getPayment()->pay(productId, pProduct->mProductName, pProduct->mProductDesc, pProduct->mProductPrice, pProduct->mProductChargePoint, buffer);
}

void IAPSystem::SdkBuyProductById(std::string productId)
{
	PayGoodsData* pGoodsData = PAYGOODSCONTROLDATAHANDLER->ByRegisterIdFindGoodsData(productId);
	if (pGoodsData == NULL)
		return ;

	// 一旦发起购买，先将目前玩家所在的服务器Id和PlayerId保存一下
	std::string serverId = _to_event_param_(SERVERINFODATAINFO->GetCurrentServerId());
	std::string playerId = _to_event_param_(ROLEINFODATAHANDLER->m_pRIData->instanceId_);
	LocalPlayerDataManager::get_instance2()->SetLastIAPServerId(serverId);
	LocalPlayerDataManager::get_instance2()->SetLastIAPPlayerId(playerId);

	// 由于在取出IMEI和MAC之后会出现总长度已经超过订单号长度，故去除Mac地址
	char buffer[10240] = "";
	std::string mac = cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceMacAddr();
	if (mac.length() <= 0)
	{
		sprintf(buffer, 
			"%s%lld%u%u%u%u%u%u%u%u%u", 
			cocos2d::CCDirector::sharedDirector()->getSystem()->getDeviceIMEI().c_str(), 
			TimeSystem::GetCurrentMicroSecond(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand());
	}
	else
	{
		sprintf(buffer, 
			"%u%lld%u%u%u%u%u%u%u%u%u", 
			MyHash::ap_hash((char*)mac.c_str()),
			TimeSystem::GetCurrentMicroSecond(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand(), 
			Random::rand(), 
			Random::rand(), 
			Random::rand(),
			Random::rand());
	}
	buffer[30] = '\0';

	// 强制存储本地订单信息，防止异常情况
	// 各种异常导致玩家下线之后，下次再次登录时，玩家所选服务器，所选账号都可以发生改变
	// 所以强制本地来存，增加当前服务器Id和当前玩家Id
	//pp没有用到的参数存在本地
	int goodid = 0;
	std::string transactionId = buffer;
	std::string transactionReceipt = "";
	LOGGERSYSTEM->LogInfo("iap === [%s]", buffer);
	//下面保存订单号的部分已移到外层
	//LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, productId, goodid, transactionId, transactionReceipt);

	// 购买
	char num[10] = "";
	sprintf(num, "%d", 1);
	//附加参数
	std::string arrStrparamet[4];
	for (int i=0;i<4;i++)
	{
		arrStrparamet[i] = "";
	}
	std::vector<std::string>::const_iterator  it = PAYGOODSCONTROLDATAHANDLER->m_AndroidPayStr.begin();
	std::vector<std::string>::const_iterator  it_end = PAYGOODSCONTROLDATAHANDLER->m_AndroidPayStr.end();
	for (int arrindex = 0;it != it_end;it++, arrindex++)
	{
		arrStrparamet[arrindex] = *it;
	}
	
	cocos2d::CCDirector::sharedDirector()->getPlatform()->PayGoods(pGoodsData->goodsPrice_,transactionId,pGoodsData->goodsName_,playerId,serverId,productId,num,arrStrparamet[0],arrStrparamet[1],arrStrparamet[2],arrStrparamet[3]);
}

void IAPSystem::onPayFailed(std::string IAPId, std::string error)
{
	// 删除本地对应的payment
	LocalPlayerDataManager::get_instance2()->DeletePayment(IAPId);
}

void IAPSystem::onPaySuccess(std::string IAPId, std::string transactionId, std::string transactionReceipt)
{
	// 及时去服务器验证吧
	;
}

void IAPSystem::onVerifyFailed(std::string IAPId, std::string error)
{
	// 因为Android下面，无法确保Biling已经收到各个平台
	// push的支付消息（存在延迟），所以客户端本地进行
	// 计数，如果大于某个计数，则表示确实没收到，可以
	// 从本地队列删除订单了
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>& myList = LocalPlayerDataManager::get_instance2()->GetUnVerifyIAPList();
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter = myList.find(IAPId);
	if (iter == myList.end())
		return;
	//106版本做法 收到失败订单直接删除本地存在的订单 因为服务器已经校验完这个订单是失败的
	LocalPlayerDataManager::get_instance2()->DeletePayment(IAPId);

	
	/*
	//105版本的做法
	// 判断计数
	int verifyNumber = 30;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "IAPVerifyNumber", verifyNumber);
	LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_& temp = iter->second;
	if (temp.mVerifyFailedCount > verifyNumber)
	{
		// 验证多次都没有通过，就认为它是非法的吧
		LocalPlayerDataManager::get_instance2()->DeletePayment(IAPId);
		return;
	}

	// 计数加一
	temp.mVerifyFailedCount++;
	// 强制保存玩家数据
	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();
	*/
}

void IAPSystem::onVerifySuccess(std::string IAPId)
{
	// 进行必要提示
	;

	// 验证成功，删除本地队列中的订单
	LocalPlayerDataManager::get_instance2()->DeletePayment(IAPId);
}

void IAPSystem::onRestoreSuccess(std::string IAPId)
{

}

void IAPSystem::insertPayment(std::string productId,std::string transactionId)
{
	char b[512] = "";
	sprintf(b, "-- hi ,i am in c++, productId:%s, transactionId:%s", productId.c_str(), transactionId.c_str());
	LOGGERSYSTEM->LogInfo(b);

	int goodid = 0;
	std::string transactionReceipt = "";
	std::string serverId = LocalPlayerDataManager::get_instance2()->GetLastIAPServerId();
	std::string playerId = LocalPlayerDataManager::get_instance2()->GetLastIAPPlayerId();

	LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, productId, goodid, transactionId, transactionReceipt);
}


#endif
