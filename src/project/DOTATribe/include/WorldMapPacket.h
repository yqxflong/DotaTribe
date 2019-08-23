#ifndef  _PACKECT_WORLDMAP_H_
#define  _PACKECT_WORLDMAP_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SWorldMapPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;

public:
	C2SWorldMapPacket(int serialnum);
	virtual ~C2SWorldMapPacket(){};

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
class S2CWorldMapPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;


public:
	S2CWorldMapPacket();
	virtual ~S2CWorldMapPacket();

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

class S2CWorldMapPacketFactory : public IPacketFactory
{
public:
	S2CWorldMapPacketFactory();
	virtual ~S2CWorldMapPacketFactory();

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
	static   void  OnS2CWorldMapPacketHandler(S2CWorldMapPacket* pPacket);
};

#endif