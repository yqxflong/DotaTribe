//Name：SCShopInfoPacket
//Function：s->c 回应商店请求
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCSHOPINFO_H_
#define  _DOTATRIBE_SCSHOPINFO_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCShopInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCShopInfoPacket(){};
	virtual ~SCShopInfoPacket(){};

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
	virtual  void  Send(){};
private:
	inline void _readServerInfo(cobra_win::DPacket &packet);

};

class SCShopInfoPacketFactory : public IPacketFactory
{
public:
	SCShopInfoPacketFactory(){};
	virtual ~SCShopInfoPacketFactory(){};

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};



/************************************************************************/
/*      SCShopBuyPacket													*/
/************************************************************************/
class SCShopBuyPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCShopBuyPacket(){};
	virtual ~SCShopBuyPacket(){};

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
	virtual  void  Send(){};
};

class SCShopBuyPacketFactory : public IPacketFactory
{
public:
	SCShopBuyPacketFactory(){};
	virtual ~SCShopBuyPacketFactory(){};

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


#endif

