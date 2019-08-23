//Name：ServerListPacket
//Function：请求服务器列表
//Written By：尹强

#ifndef  _PACKECT_ServerListPacket_H_
#define  _PACKECT_ServerListPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include "../include/DotaPacket.h"

class CSServerListPacket :public DotaPacket
{
public:
	CSServerListPacket(unsigned char channelID,std::string version);
	virtual ~CSServerListPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
};

class SCServerListPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCServerListPacket(){};
	virtual ~SCServerListPacket(){};

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
private:
	inline void _readServerInfo(cobra_win::DPacket &packet);

};

class SCServerListPacketFactory : public IPacketFactory
{
public:
	SCServerListPacketFactory(){};
	virtual ~SCServerListPacketFactory(){};

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