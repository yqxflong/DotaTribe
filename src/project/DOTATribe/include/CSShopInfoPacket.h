//Name��CSShopInfoPacket
//Function��c->s �����̵���Ʒ
//Written By��lvyunlong

#ifndef  _PACKECT_CSSHOPINFO_H_
#define  _PACKECT_CSSHOPINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSShopInfoPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int���к�]
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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

class CSShopBuyItemPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int���к�]
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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};



#endif