#include <cocos2d.h>
#include "../include/IAPSystem.h"
#include "../include/VariableSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/NetSystem.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/TimeSystem.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/LoggerSystem.h"
#include "../include/IAPProductDataManager.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include <include/common/Random.h>
#include <include/common/String.h>
#include <include/common/MyHash.h>
using  namespace  cobra_win;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


void IAPSystem::BuyProductByType(int productType)
{

}

void IAPSystem::BuyProductById(std::string productId)
{
	//IAPProductData* pProduct = IAPProductDataManager::get_instance2()->GetIAPProductByProductId(productId);
	PayGoodsData* pGoodsData = PAYGOODSCONTROLDATAHANDLER->ByRegisterIdFindGoodsData(productId);
	if (pGoodsData == NULL)
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

	// 购买
	cocos2d::CCDirector::sharedDirector()->getPayment()->pay(productId, pGoodsData->goodsName_, "", pGoodsData->goodsPrice_, 0, buffer);
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
	buffer[30] = '\0';

	// 强制存储本地订单信息，防止异常情况
	// 各种异常导致玩家下线之后，下次再次登录时，玩家所选服务器，所选账号都可以发生改变
	// 所以强制本地来存，增加当前服务器Id和当前玩家Id
	//pp没有用到的参数存在本地
	int goodid = 0;
	std::string transactionId = buffer;
	std::string transactionReceipt = "";

	//LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, productId, goodid, transactionId, transactionReceipt);

	// 购买
	char num[10] = "";
	sprintf(num, "%d", pGoodsData->goodNumber_);
	cocos2d::CCDirector::sharedDirector()->getPlatform()->PayGoods(pGoodsData->goodsPrice_,transactionId,pGoodsData->goodsName_,playerId,"0",productId,num);
}

void IAPSystem::onPayFailed(std::string IAPId, std::string error)
{

}

void IAPSystem::onPaySuccess(std::string IAPId, std::string transactionId, std::string transactionReceipt)
{

}

void IAPSystem::onVerifyFailed(std::string IAPId, std::string error)
{

}

void IAPSystem::onVerifySuccess(std::string IAPId)
{

}

void IAPSystem::onRestoreSuccess(std::string IAPId)
{

}

void IAPSystem::insertPayment(std::string productId,std::string transactionId)
{

}

#endif
