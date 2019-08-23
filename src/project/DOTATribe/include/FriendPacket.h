// Name :		FriendPacket.h
// Function:	好友消息
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIEND_H_
#define  _PACKECT_FRIEND_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SFriendPacket();
	virtual ~C2SFriendPacket(){};

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
class S2CFriendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendPacket();
	virtual ~S2CFriendPacket();
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

class S2CFriendPacketFactory : public IPacketFactory
{
public:
	S2CFriendPacketFactory();
	virtual ~S2CFriendPacketFactory();

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
	static   void  OnS2CFriendPacketHandler(S2CFriendPacket* pPacket);
};


//S2C
class S2CUpdataFriendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CUpdataFriendPacket();
	virtual ~S2CUpdataFriendPacket();
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

class S2CUpdataFriendPacketFactory : public IPacketFactory
{
public:
	S2CUpdataFriendPacketFactory();
	virtual ~S2CUpdataFriendPacketFactory();

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
	static   void  OnS2CUpdataFriendPacketHandler(S2CUpdataFriendPacket* pPacket);
};

#endif