#ifndef  _PACKECT_C2SARENARANKPACKET_H_
#define  _PACKECT_C2SARENARANKPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求竞技场排行榜数据
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