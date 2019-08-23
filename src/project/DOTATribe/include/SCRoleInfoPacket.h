//Name：SCRoleInfoPacket
//Function：s->c角色信息
//Written By：尹强
#ifndef  _PACKET_SCROLEINFO_H_
#define  _PACKET_SCROLEINFO_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/RoleInfoDataHandler.h"
#include <include/mem/DPacket.h>

/*
	此Packet只接收人物信息，其余信息由其他的数据handler分别来取
*/
class SCRoleInfoPacket : public IPacket
{
public:
	char head_[2];
	int len_;
	unsigned short pn_;
	int serial_;
public:
	SCRoleInfoPacket(){
		//roleInfo_=0;
	};
	virtual ~SCRoleInfoPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
	*/
	virtual  void  Send(){};
private:
	void _readRoleInfo(cobra_win::DPacket &packet);
	void _readBag(cobra_win::DPacket &packet);
	void _readMissionInfo(cobra_win::DPacket &packet);
	void _readHeroDB(cobra_win::DPacket &packet);
	void _readRoleSouls(cobra_win::DPacket &packet);
	void _readTeamHero(cobra_win::DPacket &packet);
	void _readCheckFunOpen(cobra_win::DPacket &packet);
};

class SCRoleInfoPacketFactory : public IPacketFactory
{
public:
	SCRoleInfoPacketFactory(){};
	virtual ~SCRoleInfoPacketFactory(){};

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

};


#endif

