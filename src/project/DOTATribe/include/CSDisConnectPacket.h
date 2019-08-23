//Name��CSDisConnectPacket
//Function��c->s ����Ͽ�����
//Written By��lvyunlong

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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

#endif