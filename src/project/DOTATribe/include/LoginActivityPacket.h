//Name:LoginActivityPacket
//Author: lvyunlong
//Func: Activity of login activity net packet
//Maintainer:lvyunlong

#ifndef _DOTATRIBE_LOGINACTIVITY_PACKET_H_
#define _DOTATRIBE_LOGINACTIVITY_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 每日登陆请求信息返回           3119							        */
/************************************************************************/
class SCLoginActivityPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCLoginActivityPacket(){};
	virtual ~SCLoginActivityPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCLoginActivityPacketFactory : public IPacketFactory
{
public:
	SCLoginActivityPacketFactory(){};
	virtual ~SCLoginActivityPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 领取登陆奖励请求信息           3121  3122                             */
/************************************************************************/
class CSGetLoginRewardPacket : public DotaPacket
{
public:
	CSGetLoginRewardPacket();
	~CSGetLoginRewardPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCGetLoginRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCGetLoginRewardPacket(){};
	virtual ~SCGetLoginRewardPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCGetLoginRewardPacketFactory : public IPacketFactory
{
public:
	SCGetLoginRewardPacketFactory(){};
	virtual ~SCGetLoginRewardPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif