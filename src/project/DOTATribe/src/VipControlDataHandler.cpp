//Name��	VipContrnlDataHandler
//Function��VIP��صĿ�����
//Written By��lvyunlong
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
	����VIP��Ϣ
*/
void VipControlDataHandler::ToServerVIPInfo()
{
	CSVipInfoPacket packet;
	packet.Send();
}
/*
	VIP��ȡ����
*/
void VipControlDataHandler::ToServerVIPReward()
{
	CSVipRewardPacket packet;
	packet.Send();
}
