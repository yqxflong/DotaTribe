//Name:FirstRechGiftPacket
//Author: lvyunlong
//Func: Activity of first recharge get gift net packet
//Maintainer:lvyunlong

#ifndef _DOTATRIBE_FIRSTRECHGIFT_PACKET_H_
#define _DOTATRIBE_FIRSTRECHGIFT_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 首充活动礼包请求信息           2215  2216                             */
/************************************************************************/
class CSFirstRechInfoPacket : public DotaPacket
{
public:
	CSFirstRechInfoPacket();
	~CSFirstRechInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCFirstRechInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCFirstRechInfoPacket(){};
	virtual ~SCFirstRechInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCFirstRechInfoPacketFactory : public IPacketFactory
{
public:
	SCFirstRechInfoPacketFactory(){};
	virtual ~SCFirstRechInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 领取首充礼包请求信息           2217  2218                             */
/************************************************************************/
class CSGetFirstGiftPacket : public DotaPacket
{
public:
	CSGetFirstGiftPacket();
	~CSGetFirstGiftPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCGetFirstGiftPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCGetFirstGiftPacket(){};
	virtual ~SCGetFirstGiftPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCGetFirstGiftPacketFactory : public IPacketFactory
{
public:
	SCGetFirstGiftPacketFactory(){};
	virtual ~SCGetFirstGiftPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif