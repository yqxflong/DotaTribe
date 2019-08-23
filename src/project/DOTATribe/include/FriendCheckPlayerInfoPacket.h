// Name :		FriendCheckPlayerInfoPacket.h
// Function:	查看好友信息消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDCHECKPLAYERINFO_H_
#define  _PACKECT_FRIENDCHECKPLAYERINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendCheckPlayerInfoPacket : public IPacket
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
	C2SFriendCheckPlayerInfoPacket(int id);
	virtual ~C2SFriendCheckPlayerInfoPacket(){};

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
class S2CFriendCheckPlayerInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendCheckPlayerInfoPacket();
	virtual ~S2CFriendCheckPlayerInfoPacket();
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

class S2CFriendCheckPlayerInfoPacketFactory : public IPacketFactory
{
public:
	S2CFriendCheckPlayerInfoPacketFactory();
	virtual ~S2CFriendCheckPlayerInfoPacketFactory();

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
	static   void  OnS2CFriendCheckPlayerInfoPacketHandler(S2CFriendCheckPlayerInfoPacket* pPacket);
};

#endif