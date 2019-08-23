// Name :		CostRevenuePacket.h
// Function:	点金消耗消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_COSTREVENUE_H_
#define  _PACKECT_COSTREVENUE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SCostRevenuePacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_type;
	unsigned char m_countType;

public:
	C2SCostRevenuePacket(int type,int countType);
	virtual ~C2SCostRevenuePacket(){};

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



//S2C
class S2CCostRevenuePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_type;
	unsigned char m_countType;



public:
	S2CCostRevenuePacket();
	virtual ~S2CCostRevenuePacket();
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

class S2CCostRevenuePacketFactory : public IPacketFactory
{
public:
	S2CCostRevenuePacketFactory();
	virtual ~S2CCostRevenuePacketFactory();

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

private:
	/*
		逻辑数据包处理
	*/
	static   void  OnS2CCostRevenuePacketHandler(S2CCostRevenuePacket* pPacket);
};

#endif