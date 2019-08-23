#include "../include/PacketHelper.h"
#include "../include/LuaSystem.h"
#include "../include/NFToolController.h"

BaseHelper * PacketHelper::m_pHelper = NULL;
std::string PacketHelper::m_sName = "";


unsigned  int  PacketHelper_RecievedPacket::GetPacketType()
{
	return _TYPE_PACKET_S2C_LUA_;
}

bool  PacketHelper_RecievedPacket::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

/*	return LUASYSTEM->OnLuaPacketHandler(m_pn, &packet);*/
	return true;
}

PacketHelper::PacketHelper()
{
	m_LuaPacket = NULL;
	m_pRecievedDPacket = NULL;
}

PacketHelper::~PacketHelper()
{

}

void PacketHelper::BuildInstance(std::string name, BaseHelper * helper)
{
	m_pHelper = helper;
	m_sName = name;
}

bool PacketHelper::IsLuaPacket(int packetType)
{
	for(unsigned int i = 0; i < m_vRegisterPacketType.size(); ++i)
	{
		if(m_vRegisterPacketType[i] == packetType)
			return true;
	}

	return false;
}

void PacketHelper::SetRecievedDPacket(unsigned short pn, cobra_win::DPacket * packet)
{
	m_iRecievedPacketType = pn;
	m_pRecievedDPacket = packet;
}

BaseHelper * PacketHelper::LuaGetInstance()
{
	return m_pHelper;
}

std::string PacketHelper::LuaGetInstanceName()
{
	return m_sName;
}

void PacketHelper::LuaRegisterPacket(int packetType)
{
	m_vRegisterPacketType.push_back(packetType);
}

void PacketHelper::LuaBuildPacket(int packetType)
{
	if(m_LuaPacket)
	{
		delete m_LuaPacket;
		m_LuaPacket = NULL;
	}
	m_LuaPacket = new PacketHelper_Packet;

	m_LuaPacket->SetPacketType(packetType);
}

void PacketHelper::LuaPutByte(char param)
{
	m_LuaPacket->PushData(param);
}

void PacketHelper::LuaPutShort(short param)
{
	m_LuaPacket->PushData(param);
}

void PacketHelper::LuaPutInt(int param)
{
	m_LuaPacket->PushData(param);
}

void PacketHelper::LuaPutString(std::string param)
{
	m_LuaPacket->PushData(param);
}

void PacketHelper::LuaSendPacket()
{
	m_LuaPacket->Send();
	if(m_LuaPacket)
	{
		delete m_LuaPacket;
		m_LuaPacket = NULL;
	}
}

int PacketHelper::LuaReadPn()
{
	return m_iRecievedPacketType;
}

short PacketHelper::LuaReadShort()
{
	short a = 0;
	m_pRecievedDPacket->read(a);
	return a;
}

char PacketHelper::LuaReadByte()
{
	char a = 0;
	(*m_pRecievedDPacket)>>a;
	return a;
}

int PacketHelper::LuaReadInt()
{
	int a = 0;
	(*m_pRecievedDPacket)>>a;
	return a;
}

std::string PacketHelper::LuaReadString()
{
	std::string str;
	NFC_ParsePacketString(*m_pRecievedDPacket, str);
	return str;
}