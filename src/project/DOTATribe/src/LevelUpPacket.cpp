// Name :		LevelUpPacket.h
// Function:	角色升级消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/LevelUpPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/config_HomeWindow.h"
#include "../include/RevenueDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SLevelUpPacket::C2SLevelUpPacket(int serialnum){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serialnum;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SLevelUpPacket::GetPacketType()
{
	return 0;
}

unsigned  int  C2SLevelUpPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SLevelUpPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SLevelUpPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CLevelUpPacket::S2CLevelUpPacket()
{
	functionid = -1;
}

S2CLevelUpPacket::~S2CLevelUpPacket()
{

}

unsigned  int  S2CLevelUpPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_LEVELUPRESULT_;
}

unsigned  int  S2CLevelUpPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CLevelUpPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial_;

	packet>>lv;  //升之后等级
	packet>>skill1;//技能id
	packet>>skill2;//技能id2
	packet>>point;//
	packet>>professionalskill;//专精
	packet>>functionid;//功能id

	////收场景信息
	LevelUpData* pData = new LevelUpData();
	pData->lv =lv;
	pData->skill1=skill1;
	pData->skill2=skill2;
	pData->point=point;
	pData->professionalskill=professionalskill;
	pData->functionID=functionid;

	NFC_GetHeroSkillManager()->setLastActiveSkillID(skill1);
	NFC_GetHeroSkillManager()->setLastActiveSkillID(skill2);
	  
	LevelUpDataHandler::get_instance2()->LevelUpDataList.push_back(pData);
	if (pData->lv == _LV_HOMEWINDOW_NEWSCENE_COLLECTION)
		RevenueDataHandler::get_instance2()->m_showArrow =true;


	if(LevelUpDataHandler::get_instance2()->m_showFlag)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LEVELUPNORMALWINDOW_);
		LevelUpDataHandler::get_instance2()->m_showFlag = false;
	}
	
	
	return true;
}


void  S2CLevelUpPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CLevelUpPacketFactory::S2CLevelUpPacketFactory()
{

}


S2CLevelUpPacketFactory::~S2CLevelUpPacketFactory()
{

}

unsigned  int S2CLevelUpPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_C2S_LEVELUPRESULT_;
}

bool S2CLevelUpPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CLevelUpPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CLevelUpPacketHandler(&packet);
	return true;
}	

void S2CLevelUpPacketFactory::OnS2CLevelUpPacketHandler(S2CLevelUpPacket* pPacket)
{

}
