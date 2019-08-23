//Name: PacketHelper.h
//Function: 提供Lua使用UISystem中的部分功能接口
//Date: 20140313
//Author: fangjun

#ifndef _LUA_PACKETHELPER_H_
#define _LUA_PACKETHELPER_H_

#include <vector>
#include <string>
#include <include/mem/DPacket.h>
#include "../include/PacketFactory.h"
#include "../include/PacketTyper.h"
#include "../include/DotaPacket.h"
#include "../include/BaseHelper.h"

class PacketHelper_Packet : public DotaPacket
{
private:
	int packetType;
public:
	virtual  unsigned  int  GetPacketType()
	{
		return packetType;
	}
	void SetPacketType(int type)
	{
		packetType = type;
	}
};

class PacketHelper_RecievedPacket : public IPacketFactory
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType();//统一为5000,,..  _TYPE_PACKET_S2C_LUA_
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

class PacketHelper:public BaseHelper
{
private:
	static BaseHelper * m_pHelper;
	static std::string m_sName;

	std::vector<int> m_vRegisterPacketType;

	PacketHelper_Packet * m_LuaPacket;

	cobra_win::DPacket * m_pRecievedDPacket;
	int m_iRecievedPacketType;

public:
	PacketHelper();
	virtual ~PacketHelper();

	virtual void BuildInstance(std::string name, BaseHelper * helper);

	bool IsLuaPacket(int packetType);

	void SetRecievedDPacket(unsigned short pn, cobra_win::DPacket * packet);

public:
	static BaseHelper * LuaGetInstance();

	static std::string LuaGetInstanceName();

	void LuaRegisterPacket(int packetType);

	void LuaBuildPacket(int packetType);

	void LuaPutByte(char param);

	void LuaPutShort(short param);

	void LuaPutInt(int param);

	void LuaPutString(std::string param);

	void LuaSendPacket();

	int LuaReadPn();

	short LuaReadShort();

	char LuaReadByte();

	int LuaReadInt();

	std::string LuaReadString();


};


#endif