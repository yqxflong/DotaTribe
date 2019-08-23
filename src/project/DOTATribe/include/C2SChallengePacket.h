#ifndef  _DOTATRIBE_C2SChallengePacket_H_
#define  _DOTATRIBE_C2SChallengePacket_H_
 

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求挑战数据
//date:   2013/08/30
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"
 
class C2SChallengePacket : public IPacket
{
 
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	int   m_serial;
	int   m_targetID;
 
public:
	C2SChallengePacket(int targetID);
	virtual ~C2SChallengePacket(){};

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