#include  <cocos2d.h>
#include  "../include/S2CRestSkillsPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
 

using  namespace  cobra_win;


unsigned  int  S2CRestRoleSkillsPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_RESET_SKILLS_SERVER_;
}

unsigned  int  S2CRestRoleSkillsPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  S2CRestRoleSkillsPacket::readSkills(cobra_win::DPacket &packet)
{ 
	NFC_GetHeroSkillManager(m_heroIndex)->decodeRoleSkillsPacket(packet);
	return true;
}

bool  S2CRestRoleSkillsPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	packet>>m_heroIndex;
	if(NFC_GetHeroSkillManager(m_heroIndex)!=NULL&&readSkills(packet))	 
    return true;
	 
	return false;

} 


unsigned  int S2CRestRoleSkillsPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_C2S_RESET_SKILLS_SERVER_;
}

bool S2CRestRoleSkillsPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CRestRoleSkillsPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false; 
	OnFinishCallBackHandler(packet.m_heroIndex);
	return true;
}	 

void  S2CRestRoleSkillsPacketFactory::OnFinishCallBackHandler(unsigned char index)
{
	NFC_GetHeroSkillManager(index)->resetLastActiveSkillID();
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_UPDATE_SELECTSKILLWINDOW_);
}
