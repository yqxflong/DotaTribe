// Name :		LessResourcePacket.h
// Function:	资源不足消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_LESSRESOURCE_H_
#define  _PACKECT_LESSRESOURCE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SLessResourcePacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_type;

public:
	C2SLessResourcePacket();
	virtual ~C2SLessResourcePacket(){};

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
class S2CLessResourcePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CLessResourcePacket();
	virtual ~S2CLessResourcePacket();
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

class S2CLessResourcePacketFactory : public IPacketFactory
{
public:
	S2CLessResourcePacketFactory();
	virtual ~S2CLessResourcePacketFactory();

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
	static   void  OnS2CLessResourcePacketHandler(S2CLessResourcePacket* pPacket);
};


/************************************************************************/
/*====================购买不足=================
/************************************************************************/
class C2SChioseLessResourcePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_index;

public:
	C2SChioseLessResourcePacket();
	virtual ~C2SChioseLessResourcePacket(){};

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
class S2CChioseLessResourcePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	  
public:
	S2CChioseLessResourcePacket();
	virtual ~S2CChioseLessResourcePacket();
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

class S2CChioseLessResourcePacketFactory : public IPacketFactory
{
public:
	S2CChioseLessResourcePacketFactory();
	virtual ~S2CChioseLessResourcePacketFactory();

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
	static   void  OnS2CChioseLessResourcePacketHandler(S2CChioseLessResourcePacket* pPacket);
};
#endif
