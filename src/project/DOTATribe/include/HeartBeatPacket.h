//Name:HeartBeatPacket
//Function: 心跳检测包
//Author:fangjun
//Date:20130819

#ifndef _DOTATRIBE_HEARTBEATPACKET_H_
#define _DOTATRIBE_HEARTBEATPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSHeartBeatPacket : public IPacket
{

private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSHeartBeatPacket();
	virtual ~CSHeartBeatPacket();

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



class SCHeartBeatResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;


public:
	SCHeartBeatResultPacket();
	virtual ~SCHeartBeatResultPacket();
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

class SCHeartBeatResultPacketFactory : public IPacketFactory
{
public:
	SCHeartBeatResultPacketFactory();
	virtual ~SCHeartBeatResultPacketFactory();

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

};


#endif