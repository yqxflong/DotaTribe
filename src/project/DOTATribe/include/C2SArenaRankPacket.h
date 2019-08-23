#ifndef  _PACKECT_C2SARENARANKPACKET_H_
#define  _PACKECT_C2SARENARANKPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ���󾺼������а�����
//date:   2013/08/29
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"

class C2SArenaRankPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;  

public:
	C2SArenaRankPacket(int serial);
	virtual ~C2SArenaRankPacket(){};

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