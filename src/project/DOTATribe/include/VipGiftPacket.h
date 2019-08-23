//Name:VipGiftPacket
//Author: lvyunlong
//Func: Activity of vip gift net packet
//Maintainer:lvyunlong

#ifndef _DOTATRIBE_VIPGIFT_PACKET_H_
#define _DOTATRIBE_VIPGIFT_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"
#include "../include/CPublicVarReader.h"

/************************************************************************/
/* VIP礼包请求信息           2219  2220		                            */
/************************************************************************/
class CSVipGiftInfoPacket : public DotaPacket
{
public:
	CSVipGiftInfoPacket();
	~CSVipGiftInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCVipGiftInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCVipGiftInfoPacket(){};
	virtual ~SCVipGiftInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCVipGiftInfoPacketFactory : public IPacketFactory
{
public:
	SCVipGiftInfoPacketFactory(){};
	virtual ~SCVipGiftInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* Vip礼包购买请求信息           2221  2222                              */
/************************************************************************/
class CSVipGiftBuyPacket : public DotaPacket
{
public:
	CSVipGiftBuyPacket(IByte viplevel);
	~CSVipGiftBuyPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCVipGiftBuyPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCVipGiftBuyPacket(){};
	virtual ~SCVipGiftBuyPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCVipGiftBuyPacketFactory : public IPacketFactory
{
public:
	SCVipGiftBuyPacketFactory(){};
	virtual ~SCVipGiftBuyPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* Vip礼包预览           2223 2224				                        */
/************************************************************************/
class CSVipGiftPreViewPacket : public DotaPacket
{
public:
	CSVipGiftPreViewPacket(int preview);
	~CSVipGiftPreViewPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

#endif