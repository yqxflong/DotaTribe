// Name :		AskForRoleInfoPacket.h
// Function:	请求人物信息数据包（登录时）
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_ASKFORROLEINFO_H_
#define  _PACKECT_ASKFORROLEINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SAskForRoleInfoPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;

	int m_playerID;
	int m_playerIdentifyingCode;

public:
	C2SAskForRoleInfoPacket(int serialnum,int playerID,int code);
	virtual ~C2SAskForRoleInfoPacket(){};

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
class S2CAskForRoleInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;


public:
	S2CAskForRoleInfoPacket();
	virtual ~S2CAskForRoleInfoPacket();

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

class S2CAskForRoleInfoPacketFactory : public IPacketFactory
{
public:
	S2CAskForRoleInfoPacketFactory();
	virtual ~S2CAskForRoleInfoPacketFactory();

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
	static   void  OnS2CAskForRoleInfoPacketHandler(S2CAskForRoleInfoPacket* pPacket);
};

#endif