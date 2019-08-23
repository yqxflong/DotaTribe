// Name :		FriendAgreeSinglePacket.h
// Function:	同意单个好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _PACKECT_FRIENDAGREESINGLE_H_
#define  _PACKECT_FRIENDAGREESINGLE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendAgreeSinglePacket : public IPacket
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
	C2SFriendAgreeSinglePacket(int id);
	virtual ~C2SFriendAgreeSinglePacket(){};

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
class S2CFriendAgreeSinglePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_id;



public:
	S2CFriendAgreeSinglePacket();
	virtual ~S2CFriendAgreeSinglePacket();
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

class S2CFriendAgreeSinglePacketFactory : public IPacketFactory
{
public:
	S2CFriendAgreeSinglePacketFactory();
	virtual ~S2CFriendAgreeSinglePacketFactory();

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
	static   void  OnS2CFriendAgreeSinglePacketHandler(S2CFriendAgreeSinglePacket* pPacket);
};

#endif