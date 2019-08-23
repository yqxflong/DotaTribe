//Name:NetObjectTipsPacket
//Function: 网络物品tips
//Author:方骏
//Date:20131014

#ifndef _DOTATRIBE_NETOBJECTTIPSPACKET_H_
#define _DOTATRIBE_NETOBJECTTIPSPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSNetObjectTipsPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_iTemplateId;
public:
	CSNetObjectTipsPacket(int templateId);
	virtual ~CSNetObjectTipsPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

class SCNetObjectTipsResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCNetObjectTipsResultPacket(){};
	virtual ~SCNetObjectTipsResultPacket(){};
public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

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


class SCNetObjectTipsResultPacketFactory : public IPacketFactory
{
public:
	SCNetObjectTipsResultPacketFactory(){};
	virtual ~SCNetObjectTipsResultPacketFactory(){};

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
