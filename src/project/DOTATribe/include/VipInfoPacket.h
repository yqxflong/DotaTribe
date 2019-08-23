//Name:Vip.h
//Function:Vip网络包
//Author: lvyunlong
//Date: 20131211

#ifndef _DOTATRIBE_VIP_PACKET_H_
#define _DOTATRIBE_VIP_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 请求VIP信息  1220,1221                                               */
/************************************************************************/
class CSVipInfoPacket : public DotaPacket
{
public:
	CSVipInfoPacket();
	~CSVipInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCVipInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCVipInfoPacket(){};
	virtual ~SCVipInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCVipInfoPacketFactory : public IPacketFactory
{
public:
	SCVipInfoPacketFactory(){};
	virtual ~SCVipInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 请求VIP领取奖励  1224,1225                                            */
/************************************************************************/
class CSVipRewardPacket : public DotaPacket
{
public:
	CSVipRewardPacket();
	~CSVipRewardPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCVipRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCVipRewardPacket(){};
	virtual ~SCVipRewardPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCVipRewardPacketFactory : public IPacketFactory
{
public:
	SCVipRewardPacketFactory(){};
	virtual ~SCVipRewardPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif