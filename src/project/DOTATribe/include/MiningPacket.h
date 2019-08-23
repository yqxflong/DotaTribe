//Name:MiningPacket.h
//Function:挖矿网络包
//Author: fangjun
//Date: 20131127

#ifndef _DOTATRIBE_MINING_PACKET_H_
#define _DOTATRIBE_MINING_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 挖矿主界面        2171,2172                                          */
/************************************************************************/
class CSEnterMiningPacket : public IPacket
{
public:
	CSEnterMiningPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCEnterMiningResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEnterMiningResultPacket(){};
	virtual ~SCEnterMiningResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEnterMiningResultPacketFactory : public IPacketFactory
{
public:
	SCEnterMiningResultPacketFactory(){};
	virtual ~SCEnterMiningResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 地精矿区			2173,2174                                           */
/************************************************************************/
class CSEnterGoblinAreaPacket : public IPacket
{
public:
	CSEnterGoblinAreaPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCEnterGoblinResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEnterGoblinResultPacket(){};
	virtual ~SCEnterGoblinResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEnterGoblinResultPacketFactory : public IPacketFactory
{
public:
	SCEnterGoblinResultPacketFactory(){};
	virtual ~SCEnterGoblinResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 结束采集  2175，2176                                                 */
/************************************************************************/
class CSStopMiningPacket : public IPacket
{
public:
	CSStopMiningPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCStopMiningResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCStopMiningResultPacket(){};
	virtual ~SCStopMiningResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCStopMiningResultPacketFactory : public IPacketFactory
{
public:
	SCStopMiningResultPacketFactory(){};
	virtual ~SCStopMiningResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 矮人矿区   2177,2178                                                  */
/************************************************************************/
class CSEnterDwarvenAreaPacket : public IPacket
{
public:
	CSEnterDwarvenAreaPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCEnterDwarvenResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEnterDwarvenResultPacket(){};
	virtual ~SCEnterDwarvenResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEnterDwarvenResultPacketFactory : public IPacketFactory
{
public:
	SCEnterDwarvenResultPacketFactory(){};
	virtual ~SCEnterDwarvenResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 矮人矿区抢矿位  2179	，正常走战斗返回，不正常走2180                  */
/************************************************************************/
class CSDwarvenLootPacket : public IPacket
{
private:
	int serial;
	char m_Index;
public:
	CSDwarvenLootPacket(char index);
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCDwarvenLootResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCDwarvenLootResultPacket(){};
	virtual ~SCDwarvenLootResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCDwarvenLootResultPacketFactory : public IPacketFactory
{
public:
	SCDwarvenLootResultPacketFactory(){};
	virtual ~SCDwarvenLootResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 巨龙矿区   2181,2182                                                */
/************************************************************************/
class CSEnterDragonAreaPacket : public IPacket
{
public:
	CSEnterDragonAreaPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCEnterDragonResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEnterDragonResultPacket(){};
	virtual ~SCEnterDragonResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEnterDragonResultPacketFactory : public IPacketFactory
{
public:
	SCEnterDragonResultPacketFactory(){};
	virtual ~SCEnterDragonResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 挑战矿主  2183,返回走战斗                                                  */
/************************************************************************/
class CSDragonChallengeOwnerPacket : public IPacket
{
private:
	int serial;
	char m_Index;
public:
	CSDragonChallengeOwnerPacket(char index);
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

/************************************************************************/
/* 开始采矿    2183,2184                                                */
/************************************************************************/
class CSStartMiningPacket : public DotaPacket
{
public:
	CSStartMiningPacket(char mineAreaType, char index);
public:
	virtual  unsigned  int  GetPacketType();
};

class SCStartMiningResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCStartMiningResultPacket(){};
	virtual ~SCStartMiningResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCStartMiningResultPacketFactory : public IPacketFactory
{
public:
	SCStartMiningResultPacketFactory(){};
	virtual ~SCStartMiningResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 寻宝界面   2185,2186                                                  */
/************************************************************************/
class CSEnterHuntPacket : public IPacket
{
public:
	CSEnterHuntPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCEnterHuntResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEnterHuntResultPacket(){};
	virtual ~SCEnterHuntResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEnterHuntResultPacketFactory : public IPacketFactory
{
public:
	SCEnterHuntResultPacketFactory(){};
	virtual ~SCEnterHuntResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 开始寻宝  2187,2188                                                  */
/************************************************************************/
class CSHuntMiningPacket : public IPacket
{
public:
	CSHuntMiningPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCHuntMiningResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHuntMiningResultPacket(){};
	virtual ~SCHuntMiningResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCHuntMiningResultPacketFactory : public IPacketFactory
{
public:
	SCHuntMiningResultPacketFactory(){};
	virtual ~SCHuntMiningResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 抢夺/驱逐   2189，返回走战斗                                         */
/************************************************************************/
class CSHuntGrabPacket : public IPacket
{
public:
	int serial;
	CSHuntGrabPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};


/************************************************************************/
/* 加好友/打招呼后领钱  2189,2190                                       */
/************************************************************************/
class CSHuntHelloMoneyPacket : public IPacket
{
public:
	CSHuntHelloMoneyPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCHuntHelloMoneyResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHuntHelloMoneyResultPacket(){};
	virtual ~SCHuntHelloMoneyResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCHuntHelloMoneyResultPacketFactory : public IPacketFactory
{
public:
	SCHuntHelloMoneyResultPacketFactory(){};
	virtual ~SCHuntHelloMoneyResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/*
	购买寻宝次数
*/
class CSBuyHuntTimesPacket:public DotaPacket
{
public:
	virtual  unsigned  int  GetPacketType();
};

class SCBuyHuntTimesPacketFactory : public IPacketFactory
{
public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/*
	寻宝特殊事件查看信息 2247, 2248
*/
class CSHuntLieRenChaKan:public DotaPacket
{
public:
	CSHuntLieRenChaKan(unsigned char index);

public:
	virtual unsigned int GetPacketType();
};

class SCHuntLieRenChaKanResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHuntLieRenChaKanResultPacket(){};
	virtual ~SCHuntLieRenChaKanResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCHuntLieRenChaKanResultPacketFactory : public IPacketFactory
{
public:
	SCHuntLieRenChaKanResultPacketFactory(){};
	virtual ~SCHuntLieRenChaKanResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/*
	寻宝特殊事件放弃寻宝，2249， 2250
*/
class CSHuntLieRenQiangDuoNo:public DotaPacket
{
public:
	CSHuntLieRenQiangDuoNo(unsigned char index);

public:
	virtual unsigned int GetPacketType();
};

class SCHuntLieRenQiangDuoResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHuntLieRenQiangDuoResultPacket(){};
	virtual ~SCHuntLieRenQiangDuoResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCHuntLieRenQiangDuoResultPacketFactory : public IPacketFactory
{
public:
	SCHuntLieRenQiangDuoResultPacketFactory(){};
	virtual ~SCHuntLieRenQiangDuoResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/*
	寻宝特殊事件开始寻宝，2251
*/
class CSHuntLieRenQiangDuoYes:public DotaPacket
{
public:
	CSHuntLieRenQiangDuoYes(unsigned char index);

public:
	virtual unsigned int GetPacketType();
};

#endif