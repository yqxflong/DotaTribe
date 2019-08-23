//Name：RandomShopPacket
//Function： 有关随机商店的网络包信息
//Written By：lvyunlong
//Date:20140215

#include <cocos2d.h>
#include "../include/RandomShopPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include "../include/ShopInfoDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
/************************************************************************/
/* 随机商店链表信息 2227，2228                                           */
/************************************************************************/

CSRandomShopInfoPacket::CSRandomShopInfoPacket()
{

}

CSRandomShopInfoPacket::~CSRandomShopInfoPacket()
{

}

unsigned  int  CSRandomShopInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RANDOMSHOP_INFO_;
}

bool  SCRandomShopInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	packet>>RANDOMSHOPDATAHANDLER->leftSeconds_;
	packet>>RANDOMSHOPDATAHANDLER->leftItemCount_;
	packet>>RANDOMSHOPDATAHANDLER->refreshPrice_;
	unsigned short count = 0;
	packet>>count;
	RANDOMSHOPDATAHANDLER->m_count = count;
	RANDOMSHOPDATAHANDLER->ClearRandomShopInfoList();
	for (int i = 0;i<count;i++)
	{
		RandomGoodsData* temp = new RandomGoodsData;
		temp->decodeTemplatePacketData(packet);
		RANDOMSHOPDATAHANDLER->m_RandomInfoList.push_back(temp);
	}
	ROLEINFODATAHANDLER->m_pRIData->hasrefreshshop_ = 0;
	return true;
}

unsigned  int  SCRandomShopInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_RANDOMSHOP_INFO_RESULT_;
}

bool  SCRandomShopInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRandomShopInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	RANDOMSHOPDATAHANDLER->m_isRandomTick = true;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_SHOPWINDOW_);
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* 购买随机商店物品 2229，2230                                           */
/************************************************************************/
CSRandomShopBuyPacket::CSRandomShopBuyPacket(unsigned short index,int num)
{
	PushData(index);
	PushData(num);
}
CSRandomShopBuyPacket::~CSRandomShopBuyPacket()
{

}
unsigned  int  CSRandomShopBuyPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RANDOMSHOP_BUY_;
}

bool  SCRandomShopBuyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	packet>>RANDOMSHOPDATAHANDLER->m_selledshopItemId;
	packet>>RANDOMSHOPDATAHANDLER->m_selledcount;	

	return true;
}

unsigned  int  SCRandomShopBuyPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_RANDOMSHOP_BUY_RESULT_;
}

bool  SCRandomShopBuyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRandomShopBuyPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	SHOPINFODATAHANDLER->m_isBshopsellupdate = true;
	return true;
}

/************************************************************************/
/* 刷新商店信息2231，2232                                                */
/************************************************************************/
CSRandomShopRefreshPacket::CSRandomShopRefreshPacket()
{
	
}
CSRandomShopRefreshPacket::~CSRandomShopRefreshPacket()
{

}
unsigned  int  CSRandomShopRefreshPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RANDOMSHOP_REFRESH_;
}

bool  SCRandomShopRefreshPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

unsigned  int  SCRandomShopRefreshPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_RANDOMSHOP_REFRESH_RESULT_;
}

bool  SCRandomShopRefreshPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRandomShopRefreshPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);
	RANDOMSHOPDATAHANDLER->m_isRandomTick = false;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_RANDOMMARKETPWINDOW_);
	return true;
}