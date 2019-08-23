//Name：RandomShopPacket
//Function： 有关随机商店的网络包信息
//Written By：lvyunlong
//Date:20140215

#ifndef  _PACKECT_RANDOMSHOPINFOPACKET_H_
#define  _PACKECT_RANDOMSHOPINFOPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 随机商店链表信息 2227，2228                                           */
/************************************************************************/
class CSRandomShopInfoPacket : public DotaPacket
{
public:
	CSRandomShopInfoPacket();
	~CSRandomShopInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCRandomShopInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCRandomShopInfoPacket(){};
	virtual ~SCRandomShopInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCRandomShopInfoPacketFactory : public IPacketFactory
{
public:
	SCRandomShopInfoPacketFactory(){};
	virtual ~SCRandomShopInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};
/************************************************************************/
/* 购买随机商店物品 2229，2230                                           */
/************************************************************************/
class CSRandomShopBuyPacket : public DotaPacket
{
public:
	CSRandomShopBuyPacket(unsigned short index,int num);
	~CSRandomShopBuyPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class  SCRandomShopBuyPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCRandomShopBuyPacket(){};
	virtual ~SCRandomShopBuyPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCRandomShopBuyPacketFactory : public IPacketFactory
{
public:
	SCRandomShopBuyPacketFactory(){};
	virtual ~SCRandomShopBuyPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 刷新商店信息2231，2232                                                */
/************************************************************************/
class CSRandomShopRefreshPacket : public DotaPacket
{
public:
	CSRandomShopRefreshPacket();
	~CSRandomShopRefreshPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCRandomShopRefreshPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCRandomShopRefreshPacket(){};
	virtual ~SCRandomShopRefreshPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCRandomShopRefreshPacketFactory : public IPacketFactory
{
public:
	SCRandomShopRefreshPacketFactory(){};
	virtual ~SCRandomShopRefreshPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


#endif

