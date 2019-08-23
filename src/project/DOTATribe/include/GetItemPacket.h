//Name:GetItemPacket
//Function: 获得物品效果数据来源
//Author:尹强

#ifndef _DOTATRIBE_GetItemPacket_H_
#define _DOTATRIBE_GetItemPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class SCGetItemPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCGetItemPacket(){};
	virtual ~SCGetItemPacket(){};
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
	virtual  void  Send(){};
};

class SCGetItemPacketFactory : public IPacketFactory
{
public:
	SCGetItemPacketFactory(){};
	virtual ~SCGetItemPacketFactory(){};

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