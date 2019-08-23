// Name :		MassacrePacket.h
// Function:	扫荡消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_MASSACRE_H_
#define  _PACKECT_MASSACRE_H_

#include "../include/DotaPacket.h"
#include "../include/PacketFactory.h"

class C2SMassacrePacket : public DotaPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
public:
	C2SMassacrePacket(int mapid ,int stageid);
	virtual ~C2SMassacrePacket(){};
public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
};



//S2C
class S2CMassacrePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;
	
public:
	S2CMassacrePacket(){};
	virtual ~S2CMassacrePacket(){};

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

class S2CMassacrePacketFactory : public IPacketFactory
{
public:
	S2CMassacrePacketFactory(){};
	virtual ~S2CMassacrePacketFactory(){};

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