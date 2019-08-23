#include <cocos2d.h>
#include "../include/IAPSystem.h"
#include "../include/VariableSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/NetSystem.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/MessageBoxWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/TimeSystem.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/LoggerSystem.h"
#include "../include/IAPProductDataManager.h"
#include <include/common/Random.h>
#include <include/common/String.h>
#include <include/common/MyHash.h>
using  namespace  cobra_win;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


void IAPSystem::BuyProductByType(int productType)
{
	bool receiveGoods = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_, "NET", "ReceiceGoodsList", receiveGoods);
	if (!receiveGoods)
	{// 尚未收到商品列表，无法购买
		//EVENTSYSTEM->PushEvent(_TYPED_EVENT_POP_SYS_TEXT_, SysLangDataManager::get_instance2()->GetSysLangById(SysLangDataManager::_TYPED_SYSLANG_IAP_BUY_LATER_));
		return;
	}

	// 一旦发起购买，先将目前玩家所在的服务器Id和PlayerId保存一下
	std::string serverId = _to_event_param_(SERVERINFODATAINFO->GetCurrentServerId());
	std::string playerId = _to_event_param_(ROLEINFODATAHANDLER->m_pRIData->instanceId_);
	LocalPlayerDataManager::get_instance2()->SetLastIAPServerId(serverId);
	LocalPlayerDataManager::get_instance2()->SetLastIAPPlayerId(playerId);

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

	// 购买
	cocos2d::CCDirector::sharedDirector()->getPayment()->pay(pProduct->mProductId, pProduct->mProductName, pProduct->mProductDesc, pProduct->mProductPrice, pProduct->mProductChargePoint, buffer);
}

void IAPSystem::BuyProductById(std::string productId)
{
	//IAPProductData* pProduct = IAPProductDataManager::get_instance2()->GetIAPProductByProductId(productId);
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
	//IAPProductData* pProduct = IAPProductDataManager::get_instance2()->GetIAPProductByProductId(IAPId);
	PayGoodsData* pGoodsData = PAYGOODSCONTROLDATAHANDLER->ByRegisterIdFindGoodsData(IAPId);
	if (pGoodsData != NULL)
	{
		char buffer[1024] = "";
		sprintf(buffer, SysLangDataManager::get_instance2()->GetSysLangById(43).c_str(), pGoodsData->goodsName_.c_str());
		NFC_showErrorTips(buffer);
	}
}

void IAPSystem::onPaySuccess(std::string IAPId, std::string transactionId, std::string transactionReceipt)
{
	//IAPProductData* pProduct = IAPProductDataManager::get_instance2()->GetIAPProductByProductId(IAPId);
	PayGoodsData* pGoodsData = PAYGOODSCONTROLDATAHANDLER->ByRegisterIdFindGoodsData(IAPId);
	if (pGoodsData != NULL)
	{
		// 购买成功，开始等待验证信息提示
		char buffer[1024] = "";
		sprintf(buffer, SysLangDataManager::get_instance2()->GetSysLangById(42).c_str(), pGoodsData->goodsName_.c_str());
	}

	// 强制存储本地订单信息，防止异常情况
	// 各种异常导致玩家下线之后，下次再次登录时，玩家所选服务器，所选账号都可以发生改变
	// 所以依赖于苹果系统的订单队列完全不能满足我们的需求，所以强制本地来存，增加当前服务器Id和当前玩家Id
	std::string serverId = LocalPlayerDataManager::get_instance2()->GetLastIAPServerId();
	std::string playerId = LocalPlayerDataManager::get_instance2()->GetLastIAPPlayerId();
	int goodid = 0;
	if(pGoodsData!=NULL)
		goodid = atoi(pGoodsData->goodsId_.c_str());
	LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, IAPId, goodid, transactionId, transactionReceipt);

	// 删除系统队列中的订单
	RemoveIAPId(transactionId);

	// 开始服务器订单验证
	;
	PAYGOODSCONTROLDATAHANDLER->ToServerPaySurePacket(SERVERINFODATAINFO->Get_Channel_ID(),IAPId,transactionId,transactionReceipt);
}

void IAPSystem::onVerifyFailed(std::string IAPId, std::string error)
{
	// 进行必要提示
	// 验证失败，删除本地队列中的订单
	LocalPlayerDataManager::get_instance2()->DeletePayment(IAPId);

	// 关闭IAP窗口
	EndPayment();
}

void IAPSystem::onVerifySuccess(std::string IAPId)
{
	// 进行必要提示
	// 验证成功，删除本地队列中的订单
	LocalPlayerDataManager::get_instance2()->DeletePayment(IAPId);

	// 关闭IAP窗口
	EndPayment();
}

void IAPSystem::onRestoreSuccess(std::string IAPId)
{

}

void IAPSystem::insertPayment(std::string productId,std::string transactionId)
{
	int goodid = 0;
	std::string transactionReceipt = "";
	std::string serverId = LocalPlayerDataManager::get_instance2()->GetLastIAPServerId();
	std::string playerId = LocalPlayerDataManager::get_instance2()->GetLastIAPPlayerId();

	LocalPlayerDataManager::get_instance2()->InsertPayment(serverId, playerId, productId, goodid, transactionId, transactionReceipt);
}


#endif
