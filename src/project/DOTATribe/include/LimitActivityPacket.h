// Name :		LimitActivityPacket.h
// Function:	活动公告界面包
// Author :		fangjun

#ifndef _PACKET_LIMITACTIVITY_H_
#define _PACKET_LIMITACTIVITY_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"
#include <string>

class CSExchangePacket : public DotaPacket
{
public:
	CSExchangePacket(std::string cdkey);
	virtual ~CSExchangePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};

class SCExchangePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCExchangePacket(){};
	virtual ~SCExchangePacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCExchangePacketFactory : public IPacketFactory
{
public:
	SCExchangePacketFactory(){};
	virtual ~SCExchangePacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif