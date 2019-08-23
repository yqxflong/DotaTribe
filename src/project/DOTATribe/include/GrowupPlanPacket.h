//Name:GrowupPlanPacket
//Author: lvyunlong
//Func: Activity of grow up plan activity net packet
//Maintainer:lvyunlong

#ifndef _DOTATRIBE_GROWUPPLANACTIVITY_PACKET_H_
#define _DOTATRIBE_GROWUPPLANACTIVITY_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 成长计划信息返回           3123								        */
/************************************************************************/
class SCGrowupPlanInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCGrowupPlanInfoPacket(){};
	virtual ~SCGrowupPlanInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCGrowupPlanInfoPacketFactory : public IPacketFactory
{
public:
	SCGrowupPlanInfoPacketFactory(){};
	virtual ~SCGrowupPlanInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 购买成长计划请求信息           3124  3125                             */
/************************************************************************/
class CSBuyGrowupPlanPacket : public DotaPacket
{
public:
	CSBuyGrowupPlanPacket();
	~CSBuyGrowupPlanPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCBuyGrowupPlanPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCBuyGrowupPlanPacket(){};
	virtual ~SCBuyGrowupPlanPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCBuyGrowupPlanPacketFactory : public IPacketFactory
{
public:
	SCBuyGrowupPlanPacketFactory(){};
	virtual ~SCBuyGrowupPlanPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 领取成长计划奖励请求信息           3126  3127						    */
/************************************************************************/
class CSGetGrowupPlanRewardPacket : public DotaPacket
{
public:
	CSGetGrowupPlanRewardPacket(int level);
	~CSGetGrowupPlanRewardPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCGetGrowupPlanRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCGetGrowupPlanRewardPacket(){};
	virtual ~SCGetGrowupPlanRewardPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCGetGrowupPlanRewardPacketFactory : public IPacketFactory
{
public:
	SCGetGrowupPlanRewardPacketFactory(){};
	virtual ~SCGetGrowupPlanRewardPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


#endif