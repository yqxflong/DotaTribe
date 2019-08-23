// Name :		FriendIgnoreAllPacket.h
// Function:	忽略所有申请消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDIGNOREALL_H_
#define  _PACKECT_FRIENDIGNOREALL_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendIgnoreAllPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SFriendIgnoreAllPacket();
	virtual ~C2SFriendIgnoreAllPacket(){};

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
class S2CFriendIgnoreAllPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char  m_result;



public:
	S2CFriendIgnoreAllPacket();
	virtual ~S2CFriendIgnoreAllPacket();
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

class S2CFriendIgnoreAllPacketFactory : public IPacketFactory
{
public:
	S2CFriendIgnoreAllPacketFactory();
	virtual ~S2CFriendIgnoreAllPacketFactory();

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
	static   void  OnS2CFriendIgnoreAllPacketHandler(S2CFriendIgnoreAllPacket* pPacket);
};

#endif