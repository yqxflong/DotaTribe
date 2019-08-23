// Name :		FriendFindFriendPacket.h
// Function:	查找好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDFINDFRIEND_H_
#define  _PACKECT_FRIENDFINDFRIEND_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendFindFriendPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_szname;
	std::string m_name;

public:
	C2SFriendFindFriendPacket(std::string name);
	virtual ~C2SFriendFindFriendPacket(){};

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
class S2CFriendFindFriendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendFindFriendPacket();
	virtual ~S2CFriendFindFriendPacket();
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

class S2CFriendFindFriendPacketFactory : public IPacketFactory
{
public:
	S2CFriendFindFriendPacketFactory();
	virtual ~S2CFriendFindFriendPacketFactory();

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
	static   void  OnS2CFriendFindFriendPacketHandler(S2CFriendFindFriendPacket* pPacket);
};

#endif