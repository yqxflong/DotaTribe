#include <cocos2d.h>
#include "../include/IAPSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/VariableSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/TimeSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/IAPProductDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include <CCPaymentDelegate.h>
#include <include/common/Random.h>
#include <include/common/String.h>
#include <include/common/MyHash.h>
using  namespace  cobra_win;


template<> IAPSystem* cobra_win::Singleton2<IAPSystem>::m_pMySelf = NULL;

IAPSystem::IAPSystem()
{

}

IAPSystem::~IAPSystem()
{

}

bool IAPSystem::IsAvailable()
{	
	return cocos2d::CCDirector::sharedDirector()->getPayment()->isAvailable();
}

bool IAPSystem::IsHasIAPId(std::string iapId)
{
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>& myList = LocalPlayerDataManager::get_instance2()->GetUnVerifyIAPList();
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter = myList.find(iapId);
	if (iter == myList.end())
		return false;

	return true;
}

void IAPSystem::InitPaymentEnv()
{
	// 初始化支付环境
	cocos2d::CCDirector::sharedDirector()->getPayment()->init();
}

void IAPSystem::RemoveIAPId(std::string iapId)
{
	cocos2d::CCDirector::sharedDirector()->getPayment()->deletePayment(iapId);
}

void IAPSystem::VerifyIAPIdentifier()
{
	
}

void  IAPSystem::EndPayment()
{
	cocos2d::CCDirector::sharedDirector()->getPayment()->end();
}

bool  IAPSystem::Init()
{
	//  注册PAY回调处理
	cocos2d::CCPaymentDelegate* pDelegate = dynamic_cast<cocos2d::CCPaymentDelegate*>(this);
	cocos2d::CCDirector::sharedDirector()->getPayment()->setDelegate(pDelegate);

	LOGGERSYSTEM->LogInfo("Init IAPSystem Success\n");
	return true;
}

void  IAPSystem::Tick()
{
	PAYGOODSCONTROLDATAHANDLER->TimeTickToServerIapCheck();
}

void  IAPSystem::Destroy()
{
	cocos2d::CCDirector::sharedDirector()->getPayment()->setDelegate(NULL);

	LOGGERSYSTEM->LogInfo("Destroy IAPSystem Success\n");
}