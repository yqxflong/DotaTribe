//Name：CSShopInfoPacket
//Function：c->s 请求商店物品
//Written By：lvyunlong

#ifndef  _PACKECT_CSSHOPINFO_H_
#define  _PACKECT_CSSHOPINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSShopInfoPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	short m_shopId;

public:
	CSShopInfoPacket(short shopId);
	virtual ~CSShopInfoPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
	*/
	virtual  void  Send();
};

class CSShopBuyItemPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	short m_shopId;
	short m_shopItemId;
	int	  m_itemcount;

public:
	CSShopBuyItemPacket(short shopId,short shopItemId,int itemcount);
	virtual ~CSShopBuyItemPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
	*/
	virtual  void  Send();
};



#endif