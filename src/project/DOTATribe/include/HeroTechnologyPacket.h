// Name :		HeroTechnologyPacket.h
// Function:	信仰消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_HEROTECHNOLOGR_H_
#define  _PACKECT_HEROTECHNOLOGR_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class C2SHeroTechnologyPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;




public:
	C2SHeroTechnologyPacket();
	virtual ~C2SHeroTechnologyPacket(){};

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
class S2CHeroTechnologyPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;

	unsigned char IsNeedChangeScene;

public:
	S2CHeroTechnologyPacket();
	virtual ~S2CHeroTechnologyPacket();
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

class S2CHeroTechnologyPacketFactory : public IPacketFactory
{
public:
	S2CHeroTechnologyPacketFactory();
	virtual ~S2CHeroTechnologyPacketFactory();

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
	static   void  OnS2CHeroTechnologyPacketHandler(S2CHeroTechnologyPacket* pPacket);
};





class C2SAddTechnologyPointPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;




public:
	C2SAddTechnologyPointPacket();
	virtual ~C2SAddTechnologyPointPacket(){};

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
class S2CAddTechnologyPointPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;

	unsigned char IsNeedChangeScene;

public:
	S2CAddTechnologyPointPacket();
	virtual ~S2CAddTechnologyPointPacket();
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

class S2CAddTechnologyPointPacketFactory : public IPacketFactory
{
public:
	S2CAddTechnologyPointPacketFactory();
	virtual ~S2CAddTechnologyPointPacketFactory();

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
	static   void  OnS2CAddTechnologyPointPacketHandler(S2CAddTechnologyPointPacket* pPacket);
};




class C2SGetTechnologyPointPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;




public:
	C2SGetTechnologyPointPacket();
	virtual ~C2SGetTechnologyPointPacket(){};

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
class S2CGetTechnologyPointPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;

	unsigned char IsNeedChangeScene;

public:
	S2CGetTechnologyPointPacket();
	virtual ~S2CGetTechnologyPointPacket();
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

class S2CGetTechnologyPointPacketFactory : public IPacketFactory
{
public:
	S2CGetTechnologyPointPacketFactory();
	virtual ~S2CGetTechnologyPointPacketFactory();

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
	static   void  OnS2CGetTechnologyPointPacketHandler(S2CGetTechnologyPointPacket* pPacket);
};


#endif