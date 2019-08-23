//Name：CheckRoleBaseInfoPacket
//Function：c->s 查看人物基本信息
//Written By：lvyunlong
//Date:20131225

#ifndef  _PACKECT_CHECKROLEBASEINFOPACKET_H_
#define  _PACKECT_CHECKROLEBASEINFOPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

class CSCheckRoleBaseInfoPacket : public DotaPacket
{
public:
	CSCheckRoleBaseInfoPacket();
	~CSCheckRoleBaseInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCCheckRoleBaseInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCCheckRoleBaseInfoPacket(){};
	virtual ~SCCheckRoleBaseInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCCheckRoleBaseInfoPacketFactory : public IPacketFactory
{
public:
	SCCheckRoleBaseInfoPacketFactory(){};
	virtual ~SCCheckRoleBaseInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif

