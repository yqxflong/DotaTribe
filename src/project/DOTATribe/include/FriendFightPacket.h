// Name :		FriendFightPacket.h
// Function:	与好友切磋消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDFIGHT_H_
#define  _PACKECT_FRIENDFIGHT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendFightPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serverid;
	int m_playerid;


public:
	C2SFriendFightPacket(int serverid,int playerid);
	virtual ~C2SFriendFightPacket(){};

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
class S2CFriendFightPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendFightPacket();
	virtual ~S2CFriendFightPacket();
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

class S2CFriendFightPacketFactory : public IPacketFactory
{
public:
	S2CFriendFightPacketFactory();
	virtual ~S2CFriendFightPacketFactory();

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
	static   void  OnS2CFriendFightPacketHandler(S2CFriendFightPacket* pPacket);
};

#endif