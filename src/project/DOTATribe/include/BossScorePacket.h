//Name:BoseScorePacket.h
//Function:Boss积分系统
//Author:fangjun
//date:20140217

#ifndef _DOTATRIBE_BOSSSCOREPACKET_H_
#define _DOTATRIBE_BOSSSCOREPACKET_H_

#include "../include/DotaPacket.h"
#include "../include/PacketFactory.h"

/************************************************************************/
/* 进入Boss积分 2233, 2234                                              */
/************************************************************************/
class CSEnterBossScorePacket : public DotaPacket
{
public:
	CSEnterBossScorePacket();
	virtual ~CSEnterBossScorePacket();

public:
	virtual  unsigned  int  GetPacketType();
};

class SCEnterBossScoreResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){	return 1;	};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEnterBossScoreResultPacketFactory : public IPacketFactory
{
public:
	SCEnterBossScoreResultPacketFactory(){};
	virtual ~SCEnterBossScoreResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 挑战Boss积分 2235		                                              */
/************************************************************************/
class CSBossScoreChallengePacket : public DotaPacket
{
public:
	CSBossScoreChallengePacket();
	virtual ~CSBossScoreChallengePacket();

public:
	virtual  unsigned  int  GetPacketType();
};


/************************************************************************/
/* 进入Boss积分排行榜 2237, 2238                                        */
/************************************************************************/
class CSBossScoreRankPacket : public DotaPacket
{
public:
	CSBossScoreRankPacket();
	virtual ~CSBossScoreRankPacket();

public:
	virtual  unsigned  int  GetPacketType();
};

class SCBossScoreRankResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){	return 1;	};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCBossScoreRankResultPacketFactory : public IPacketFactory
{
public:
	SCBossScoreRankResultPacketFactory(){};
	virtual ~SCBossScoreRankResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 进入Boss积分奖励 2239, 2240                                        */
/************************************************************************/
class CSBossScoreRewardPacket : public DotaPacket
{
public:
	CSBossScoreRewardPacket();
	virtual ~CSBossScoreRewardPacket();

public:
	virtual  unsigned  int  GetPacketType();
};

class SCBossScoreRewardResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){	return 1;	};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCBossScoreRewardResultPacketFactory : public IPacketFactory
{
public:
	SCBossScoreRewardResultPacketFactory(){};
	virtual ~SCBossScoreRewardResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* Boss积分奖励领取 2241, 2242                                          */
/************************************************************************/
class CSBossScoreGetRewardPacket : public DotaPacket
{
public:
	CSBossScoreGetRewardPacket(char type, char index);//type:0积分奖励,1排名奖励; index:积分奖励序号
	virtual ~CSBossScoreGetRewardPacket();

public:
	virtual  unsigned  int  GetPacketType();
};

class SCBossScoreGetRewardResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){	return 1;	};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCBossScoreGetRewardResultPacketFactory : public IPacketFactory
{
public:
	SCBossScoreGetRewardResultPacketFactory(){};
	virtual ~SCBossScoreGetRewardResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};




#endif
