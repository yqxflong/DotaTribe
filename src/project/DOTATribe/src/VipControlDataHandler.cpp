//Name：	VipContrnlDataHandler
//Function：VIP相关的控制器
//Written By：lvyunlong
//Date:20131211

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/VipControlDataHandler.h"
#include "../include/VipInfoPacket.h"


VipControlDataHandler::VipControlDataHandler(){
	m_exp = 0;
	m_maxExp = 0;
	m_isBGetReward = 0; 
}

VipControlDataHandler::~VipControlDataHandler(){
	
}

void VipControlDataHandler::handlePacket(IPacket* packet){

}

bool VipControlDataHandler::init(){
	
	return true;
}

void VipControlDataHandler::onDestroy(){
	
	
}

/*
	请求VIP信息
*/
void VipControlDataHandler::ToServerVIPInfo()
{
	CSVipInfoPacket packet;
	packet.Send();
}
/*
	VIP领取奖励
*/
void VipControlDataHandler::ToServerVIPReward()
{
	CSVipRewardPacket packet;
	packet.Send();
}
