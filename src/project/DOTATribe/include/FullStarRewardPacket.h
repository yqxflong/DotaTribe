// Name :		FullStarRewardPacket.h
// Function:	关卡领取全三星奖励消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FULLSTARREWARD_H_
#define  _PACKECT_FULLSTARREWARD_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SFullStarRewardPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;

	//数据
	unsigned short m_mapID;;				// 地图ID<br>
public:
	C2SFullStarRewardPacket(int mapID);
	virtual ~C2SFullStarRewardPacket(){};

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
class S2CFullStarRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

	unsigned short m_mapID;
	
public:
	S2CFullStarRewardPacket();
	virtual ~S2CFullStarRewardPacket();

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

class S2CFullStarRewardPacketFactory : public IPacketFactory
{
public:
	S2CFullStarRewardPacketFactory();
	virtual ~S2CFullStarRewardPacketFactory();

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
	static   void  OnS2CFullStarRewardPacketHandler(S2CFullStarRewardPacket* pPacket);
};

#endif