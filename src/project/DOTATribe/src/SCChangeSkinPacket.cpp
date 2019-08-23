//Name��SCRoleInfoPacket
//Function��s->c �������׺󣬽�ɫ��Ϣ
//Written By����ǿ
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
* ʧ�� ['Z''R'][n][2006][int���к�][int -1][string failureInfo]
* �ɹ� ['Z''R'][n][2006][int���к�][int  1][int count]{[byte type][int attrvalue]}
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
	//�ѽ�����ȫ���ڴ��У�����UIˢ��
	//EVENTSYSTEM->PushEvent(_TYPED_EVENT_REFRESH_PESEQUIPSUBVIEW_INFO_);
}
