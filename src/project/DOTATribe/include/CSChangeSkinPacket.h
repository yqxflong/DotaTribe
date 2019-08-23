//Name：CSChangeSkinPacket
//Function：c->s 更换外套
//Written By：尹强
#ifndef  _PACKECT_CSCHANGESKIN_H_
#define  _PACKECT_CSCHANGESKIN_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSChangeSkinPacket : public IPacket
{
	/*
		['Z''R'][n][2003][int序列号][int外套ID]   
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;
	int m_skinID;

public:
	CSChangeSkinPacket(int serial,int skinID);
	virtual ~CSChangeSkinPacket(){};

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

