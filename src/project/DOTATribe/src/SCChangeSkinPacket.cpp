//Name：SCRoleInfoPacket
//Function：s->c 更换外套后，角色信息
//Written By：尹强
#include <cocos2d.h>
#include "../include/SCChangeSkinPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

using  namespace  cobra_win;


unsigned  int  SCChangeSkinPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHANGESKIN_;
}

unsigned  int  SCChangeSkinPacket::GetPacketLength()
{
	return sizeof(int);
}

/*
* 失败 ['Z''R'][n][2006][int序列号][int -1][string failureInfo]
* 成功 ['Z''R'][n][2006][int序列号][int  1][int count]{[byte type][int attrvalue]}
*/
bool  SCChangeSkinPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_serial;
	packet>>m_resultid;
	if(m_resultid==1)
		_readSuccessPacket(packet);

	return true;
}

void SCChangeSkinPacket::_readSuccessPacket(DPacket &packet){
	unsigned char tmp_clen=0;
	packet>>tmp_clen;
	ROLEINFODATAHANDLER->m_pRIData->attribute_->mapPropertyList_.clear();
	for (int i=0;i<tmp_clen;i++)
	{
		unsigned char atype;	//0~13
		packet>>atype;
		int avalue;
		packet>>avalue;
		ROLEINFODATAHANDLER->m_pRIData->attribute_->mapPropertyList_.insert(std::map<int,int>::value_type(atype,avalue));
	}
}


unsigned  int SCChangeSkinPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHANGESKIN_;
}

bool SCChangeSkinPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCChangeSkinPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnSCChangeSkinPacketHandler(&packet);
	return true;
}	

void SCChangeSkinPacketFactory::OnSCChangeSkinPacketHandler(SCChangeSkinPacket* pPacket)
{
	//已解析到全局内存中，呼叫UI刷新
	//EVENTSYSTEM->PushEvent(_TYPED_EVENT_REFRESH_PESEQUIPSUBVIEW_INFO_);
}
