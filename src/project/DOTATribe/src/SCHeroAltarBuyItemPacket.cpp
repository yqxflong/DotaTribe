//Name：SCHeroAltarBuyItemPacket
//Function：s->c 献祭服务器回复物品不足
//Author : lvyunlong

#include <cocos2d.h>
#include "../include/SCHeroAltarBuyItemPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ShopInfoDataHandler.h"
#include "../include/ShopGoodsBase.h"
#include "../include/NFControlsManager.h"

using namespace cobra_win;


unsigned  int  SCHeroAltarBuyItemPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROALTAR_BUYITEM_RESULT_;
}

unsigned  int  SCHeroAltarBuyItemPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCHeroAltarBuyItemPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readServerInfo(packet);
	return true;
}
void SCHeroAltarBuyItemPacket::_readServerInfo(cobra_win::DPacket &packet)
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

unsigned  int  SCHeroAltarBuyItemPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_HEROALTAR_BUYITEM_RESULT_;
}

bool  SCHeroAltarBuyItemPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCHeroAltarBuyItemPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	char type[32]={0};
	sprintf(type,"%d",0);
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPINPUTNUMWINDOW_,type);
	return true;
}