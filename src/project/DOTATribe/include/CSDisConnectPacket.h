//Name：CSDisConnectPacket
//Function：c->s 请求断开网络
//Written By：lvyunlong

#ifndef  _PACKECT_CSDISCONNECTPACKET_H_
#define  _PACKECT_CSDISCONNECTPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>


class CSDisConnectPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSDisConnectPacket();
	virtual ~CSDisConnectPacket(){};

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

#endif