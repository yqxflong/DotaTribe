// Name :		FriendAgreeAllPacket.h
// Function:	全部同意好友消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _PACKECT_FRIENDAGREEALL_H_
#define  _PACKECT_FRIENDAGREEALL_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendAgreeAllPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SFriendAgreeAllPacket();
	virtual ~C2SFriendAgreeAllPacket(){};

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
class S2CFriendAgreeAllPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;



public:
	S2CFriendAgreeAllPacket();
	virtual ~S2CFriendAgreeAllPacket();
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

class S2CFriendAgreeAllPacketFactory : public IPacketFactory
{
public:
	S2CFriendAgreeAllPacketFactory();
	virtual ~S2CFriendAgreeAllPacketFactory();

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
	static   void  OnS2CFriendAgreeAllPacketHandler(S2CFriendAgreeAllPacket* pPacket);
};

#endif