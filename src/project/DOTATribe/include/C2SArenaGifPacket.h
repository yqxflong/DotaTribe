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