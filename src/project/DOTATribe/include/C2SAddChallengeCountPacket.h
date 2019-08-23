#ifndef  _DOTATRIBE_C2SAddChallengeCountPacket_H_
#define  _DOTATRIBE_C2SAddChallengeCountPacket_H_
 
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  冷却时间数据包
//date:   2013/08/30
///////////////////////////////////////////////// 

#include  "IPacket.h"
#include  "PacketFactory.h"
 
class C2SAddChallenegeCountPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
public:
	C2SAddChallenegeCountPacket();
	virtual ~C2SAddChallenegeCountPacket(){};
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