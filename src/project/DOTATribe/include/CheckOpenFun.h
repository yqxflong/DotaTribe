// Name:		CheckOpenFun.h
// Function:	是否开启某些功能
// Author:		邵兵

#ifndef _PACKET_CHECKOPENFUN_H_
#define _PACKET_CHECKOPENFUN_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SCheckOpenFunPacket : public IPacket{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SCheckOpenFunPacket();
	virtual ~C2SCheckOpenFunPacket(){};

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

class S2CCheckOpenFunPacket: public IPacket{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	S2CCheckOpenFunPacket();
	virtual ~S2CCheckOpenFunPacket();
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


class S2CCheckOpenFunPacketFactory : public IPacketFactory
{
public:
	S2CCheckOpenFunPacketFactory();
	virtual ~S2CCheckOpenFunPacketFactory();

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
	static   void  OnS2CCheckOpenFunPacketHandler(S2CCheckOpenFunPacket* pPacket);
};


#endif