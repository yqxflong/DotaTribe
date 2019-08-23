#include <cocos2d.h>
#include "../include/SCChangeSkillsResultPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"



using  namespace  cobra_win;


unsigned  int  SCChangeSkillsResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SELECTSKILLSREULT_;
}

unsigned  int  SCChangeSkillsResultPacket::GetPacketLength()
{
	return sizeof(int);
}



bool  SCChangeSkillsResultPacket::CheckSkillsDataValid()
{
	 if(NFC_GetHeroSkillManager(m_heroIndex)!=NULL)
	 {
		 if(NFC_GetHeroSkillManager(m_heroIndex)->getRoleSkillsData())
			 return true;
	 }
	 return false;
}
 
std::vector<PSkillNotoch>  &  SCChangeSkillsResultPacket::GetUserEquipSkillVec()
{
   return   NFC_GetHeroSkillManager(m_heroIndex)->getRoleSkillsData()->skillNotchList;
}



bool  SCChangeSkillsResultPacket::UpdateLocalSkillsData(cobra_win::DPacket & packetData)
{ 
	NFC_GetHeroSkillManager(m_heroIndex)->decodeSynSkillNotchsChangePacket(packetData);
	return true;
}
 

bool  SCChangeSkillsResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_serial;
	packet>>m_heroIndex;
	if(CheckSkillsDataValid())
	{
		if(UpdateLocalSkillsData(packet))
		{
			return true;
		}
	}
 	return true;
}
 


 
unsigned  int SCChangeSkillsResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SELECTSKILLSREULT_;
}

bool SCChangeSkillsResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCChangeSkillsResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	PostNotification();
	return true;
}	

void SCChangeSkillsResultPacketFactory::PostNotification()
{ 
	//刷新凹槽技能
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_SKILLNOTCH_SELECTWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_COMMUNICATIONWAITTINGWIN_);
}

 