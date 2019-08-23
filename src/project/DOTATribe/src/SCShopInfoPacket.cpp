//Name：SCShopInfoPacket
//Function：s->c 回应商店请求
//Author : lvyunlong

#include <cocos2d.h>
#include "../include/SCShopInfoPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ShopInfoDataHandler.h"
#include "../include/ShopGoodsBase.h"
#include "../include/NFControlsManager.h"

using namespace cobra_win;


unsigned  int  SCShopInfoPacket::GetPacketType()
{
	return _TYPED_PACEKT_S2C_SHOP_INFO_;
}

unsigned  int  SCShopInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCShopInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readServerInfo(packet);
	return true;
}
void SCShopInfoPacket::_readServerInfo(cobra_win::DPacket &packet)
{
	packet>>SHOPINFODATAHANDLER->m_shopId;
	packet>>SHOPINFODATAHANDLER->m_count;
	
	SHOPINFODATAHANDLER->ClearShopInfoList();
	
	unsigned short index = 0;
	for (index;index<SHOPINFODATAHANDLER->m_count;index++)
	{
		ShopInfoGoodsData* temp = new ShopInfoGoodsData();
		temp->decodeTemplatePacketData(packet);
		SHOPINFODATAHANDLER->m_ShopGoodsBaselist.push_back(temp);
	}
}

unsigned  int  SCShopInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACEKT_S2C_SHOP_INFO_;
}

bool  SCShopInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCShopInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	unsigned short index =0;
	NFC_showCommunicationWating(false);
	char butter[128] = {0};

	SHOPINFODATAHANDLER->m_isBshopinfoupdate = true;
	if (SHOPINFODATAHANDLER->m_shopId == 0 ||SHOPINFODATAHANDLER->m_shopId == 1|| SHOPINFODATAHANDLER->m_shopId == 4)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_SHOPWINDOW_);
	}
	else
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_MARKETPWINDOW_);
	}
	
	return true;
}

/************************************************************************/
/*                        SCShopBuyPacket                               */
/************************************************************************/


unsigned  int  SCShopBuyPacket::GetPacketType()
{
	return _TYPED_PACEKT_S2C_SHOP_BUY_RESULT_;
}

unsigned  int  SCShopBuyPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCShopBuyPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	
	packet>>SHOPINFODATAHANDLER->m_selledshopid;
	packet>>SHOPINFODATAHANDLER->m_selledshopItemId;
	packet>>SHOPINFODATAHANDLER->m_selledcount;

	return true;
}



unsigned  int  SCShopBuyPacketFactory::GetPacketType()
{
	return _TYPED_PACEKT_S2C_SHOP_BUY_RESULT_;
}

bool  SCShopBuyPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCShopBuyPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	NFC_showCommunicationWating(false);
	SHOPINFODATAHANDLER->m_isBshopsellupdate = true;
	if (SHOPINFODATAHANDLER->m_selledshopid == 0 ||SHOPINFODATAHANDLER->m_selledshopid == 1|| SHOPINFODATAHANDLER->m_selledshopid == 4)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_SHOPWINDOW_);
	}
	else
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_MARKETPWINDOW_);
	}
	
	return true;
}