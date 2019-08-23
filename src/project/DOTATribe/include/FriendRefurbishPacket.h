// Name :		FriendRefurbishPacket.h
// Function:	刷新好友窗口消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDREFURBISH_H_
#define  _PACKECT_FRIENDREFURBISH_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendRefurbishPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SFriendRefurbishPacket();
	virtual ~C2SFriendRefurbishPacket(){};

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
class S2CFriendRefurbishPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned short nub;



public:
	S2CFriendRefurbishPacket();
	virtual ~S2CFriendRefurbishPacket();
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

class S2CFriendRefurbishPacketFactory : public IPacketFactory
{
public:
	S2CFriendRefurbishPacketFactory();
	virtual ~S2CFriendRefurbishPacketFactory();

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
	static   void  OnS2CFriendRefurbishPacketHandler(S2CFriendRefurbishPacket* pPacket);
};

#endif