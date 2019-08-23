// Name :		CheckPlayerInfoPacket.h
// Function:	查看好友信息消息包
// Author :		邵兵
// Maintainer:  邵兵

#ifndef  _PACKECT_CHECKPLAYERINFO_H_
#define  _PACKECT_CHECKPLAYERINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SCheckPlayerInfoPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_id;


public:
	C2SCheckPlayerInfoPacket(int id);
	virtual ~C2SCheckPlayerInfoPacket(){};

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
class S2CCheckPlayerInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CCheckPlayerInfoPacket();
	virtual ~S2CCheckPlayerInfoPacket();
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

class S2CCheckPlayerInfoPacketFactory : public IPacketFactory
{
public:
	S2CCheckPlayerInfoPacketFactory();
	virtual ~S2CCheckPlayerInfoPacketFactory();

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
	static   void  OnS2CCheckPlayerInfoPacketHandler(S2CCheckPlayerInfoPacket* pPacket);
};

#endif