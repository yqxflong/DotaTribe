// Name :		CreateRoleRandomNamePacket.h
// Function:	角色随机姓名消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _PACKECT_CREATEROLERANDOMNAME_H_
#define  _PACKECT_CREATEROLERANDOMNAME_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SCreateRoleRandomNamePacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;

public:
	C2SCreateRoleRandomNamePacket(int serialnum);
	virtual ~C2SCreateRoleRandomNamePacket(){};

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
class S2CCreateRoleRandomNamePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;

	std::string m_playerName;

public:
	S2CCreateRoleRandomNamePacket();
	virtual ~S2CCreateRoleRandomNamePacket();
	std::string GetPlayerName(){return m_playerName;};

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

class S2CCreateRoleRandomNamePacketFactory : public IPacketFactory
{
public:
	S2CCreateRoleRandomNamePacketFactory();
	virtual ~S2CCreateRoleRandomNamePacketFactory();

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
	static   void  OnS2CCreateRoleRandomNamePacketHandler(S2CCreateRoleRandomNamePacket* pPacket);
};

#endif