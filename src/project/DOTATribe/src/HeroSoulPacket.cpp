#include  <cocos2d.h>
#include "../include/HeroSoulPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"
#include "../include/IProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/HeroSoulDataHandler.h"
#include   <include/mem/MemNode.h>
#include   <include/mem/EPacket.h>
#include   <include/mem/DPacket.h>
#include "../include/NFControlsManager.h"
#include "../include/HeroIllustratedWindow.h"
#include "../include/WindowManager.h"
#include "../include/PESWindow.h"
using  namespace  cobra_win;
 
//////////////////////////////////////////////////////////////////////////
//  请求进入战魂激活 信息
//////////////////////////////////////////////////////////////////////////
C2SHeroSoulPacket::C2SHeroSoulPacket(int heroUID) {
	m_head[0]='Z';
	m_head[1]='R';
	m_nHeroUID = heroUID;
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SOUL_ENTER_INFO_CLIENT_;
}

unsigned  int  C2SHeroSoulPacket::GetPacketLength()
{
	unsigned int  packetLengt=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_nHeroUID);
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SHeroSoulPacket::Send()
{  
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_nHeroUID); 
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
//  服务器返回 战魂激活信息
//////////////////////////////////////////////////////////////////////////
 
unsigned  int  S2CHeroSoulInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SOUL_ENTER_INFO_SERVER_;
}

unsigned  int  S2CHeroSoulInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CHeroSoulInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	HeroSoulDataHandler::get_instance2()->deoceAllPacket(packet);
	return true;
} 

unsigned  int  S2CHeroSoulInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SOUL_ENTER_INFO_SERVER_;
}

bool  S2CHeroSoulInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CHeroSoulInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;   
	//to do
	if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_ATHLETICS_PROCEDURE_)
	{
		//切换流程到主场景
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_HEROSOULWINDOW_); 
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
	}
	else if (WINDOWMANAGER->IsWindowVisible(IWindow::_TYPED_WINDOW_PESWINDOW_))
	{
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_HIDE_PESWINDOW_);
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_HEROSOULWINDOW_, _to_event_param_(HeroSoulDataHandler::get_instance2()->getBackTab()), _to_event_param_(PESWindow::LOAD_SOUL_VIEW), _to_event_param_(_TYPED_EVENT_FADEIN_PESWINDOW_));
	}
	else
	{  
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_UPDATE_HeroIllustratedWindow_,_to_event_param_(HeroIllustratedWindow::_UPDATE_FOR_HERO_SOUL_TYPE_));
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
//  请求挑战 战魂
//////////////////////////////////////////////////////////////////////////
C2SChallengeHeroSoul::C2SChallengeHeroSoul(int heroUID) {
	m_head[0]='Z';
	m_head[1]='R';
	m_nSerial = RoleInfoDataHandler::get_instance2()->updateRoleAthleticsSerialID();
	m_nHeroUID = heroUID;
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SChallengeHeroSoul::GetPacketType()
{
	return _TYPED_PACKET_C2S_SOUL_CHALLENEG_CLIENT_;
}

unsigned  int  C2SChallengeHeroSoul::GetPacketLength()
{
	unsigned int  packetLengt=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_nSerial)+sizeof(m_nHeroUID);
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SChallengeHeroSoul::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SChallengeHeroSoul::Send()
{  
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_nSerial);
	pNode->push(m_nHeroUID); 
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
//  请求激活 战魂
//////////////////////////////////////////////////////////////////////////
C2SActiveSoulePacket::C2SActiveSoulePacket(int heroUID) {
	m_head[0]='Z';
	m_head[1]='R';
	m_nHeroUID = heroUID; 
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  C2SActiveSoulePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SOUL_ACTIVE_CLIENT_;
}

unsigned  int  C2SActiveSoulePacket::GetPacketLength()
{
	unsigned int  packetLengt=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_nHeroUID);
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SActiveSoulePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SActiveSoulePacket::Send()
{  
	NFC_showCommunicationWating(true);
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn); 
	pNode->push(m_nHeroUID); 
	NETSYSTEM->SendPacket(pNode);
}

//////////////////////////////////////////////////////////////////////////
//   服务器返回 激活 战魂后信息
////////////////////////////////////////////////////////////////////////// 
unsigned  int  S2CActiveHeroSoulPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SOUL_ACTIVE_SERVER_;
}

unsigned  int  S2CActiveHeroSoulPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CActiveHeroSoulPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn; 
	HeroSoulDataHandler::get_instance2()->decodeActivePacket(packet);
	return true;
} 

unsigned  int  S2CActiveHeroSoulPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_C2S_SOUL_ACTIVE_SERVER_;
}

bool  S2CActiveHeroSoulPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CActiveHeroSoulPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;   
	//to do
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_UPDATE_HEROSOULWINDOW_,_to_event_param_(0));
	return true;
}