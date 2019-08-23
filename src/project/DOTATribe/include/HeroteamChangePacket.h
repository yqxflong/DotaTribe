//Name:HeroteamChangePacket.h
//Function:换英雄网络包
//Author: lvyunlong
//Date: 20140714

#ifndef _DOTATRIBE_HEROTEAMCHANGE_PACKET_H_
#define _DOTATRIBE_HEROTEAMCHANGE_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 请求VIP信息  6001,6002                                               */
/************************************************************************/
class CSHeroteamChangePacket : public DotaPacket
{
public:
	CSHeroteamChangePacket(unsigned char index1,unsigned char index2);
	~CSHeroteamChangePacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCHeroteamChangePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHeroteamChangePacket(){};
	virtual ~SCHeroteamChangePacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCHeroteamChangePacketFactory : public IPacketFactory
{
public:
	SCHeroteamChangePacketFactory(){};
	virtual ~SCHeroteamChangePacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif