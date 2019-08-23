// Name :		HeroTechnologyLevelUpPacket.h
// Function:	信仰升级消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_HEROTECHNOLOGRLEVELUP_H_
#define  _PACKECT_HEROTECHNOLOGRLEVELUP_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class C2SHeroTechnologyLevelUpPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int	  m_id;



public:
	C2SHeroTechnologyLevelUpPacket(int id);
	virtual ~C2SHeroTechnologyLevelUpPacket(){};

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
class S2CHeroTechnologyLevelUpPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;



public:
	S2CHeroTechnologyLevelUpPacket();
	virtual ~S2CHeroTechnologyLevelUpPacket();
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

class S2CHeroTechnologyLevelUpPacketFactory : public IPacketFactory
{
public:
	S2CHeroTechnologyLevelUpPacketFactory();
	virtual ~S2CHeroTechnologyLevelUpPacketFactory();

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
	static   void  OnS2CHeroTechnologyLevelUpPacketHandler(S2CHeroTechnologyLevelUpPacket* pPacket);
};

#endif