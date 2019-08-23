#ifndef  _PACKECT_C2S_ARENAGIFPACKET_H_
#define  _PACKECT_C2S_ARENAGIFPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:   
//date:   2013/08/29
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"

class C2SArenaGifPacket : public IPacket
{ 
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	C2SArenaGifPacket();
	virtual ~C2SArenaGifPacket(){};

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