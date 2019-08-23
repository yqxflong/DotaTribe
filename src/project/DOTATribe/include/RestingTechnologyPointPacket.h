// Name :		RestingTechnologyPointPacket.h
// Function:	重置信仰点数消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_RESTINGTECHNOLOGYPOINT_H_
#define  _PACKECT_RESTINGTECHNOLOGYPOINT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SRestingTechnologyPointPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	C2SRestingTechnologyPointPacket();
	virtual ~C2SRestingTechnologyPointPacket(){};

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
class S2CRestingTechnologyPointPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CRestingTechnologyPointPacket();
	virtual ~S2CRestingTechnologyPointPacket();
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

class S2CRestingTechnologyPointPacketFactory : public IPacketFactory
{
public:
	S2CRestingTechnologyPointPacketFactory();
	virtual ~S2CRestingTechnologyPointPacketFactory();

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
	static   void  OnS2CRestingTechnologyPointPacketHandler(S2CRestingTechnologyPointPacket* pPacket);
};

#endif