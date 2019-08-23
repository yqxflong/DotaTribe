#ifndef  _DOTATRIBE_C2SBATTLERECORDPACKET_H_
#define  _DOTATRIBE_C2SBATTLERECORDPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求查看战斗记录ID 竞技场
//date:   2013/08/29
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"

class C2SBattleRecordPacket : public IPacket
{
 
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;  
	int m_battleID;

public:
	C2SBattleRecordPacket(int battleID);
	virtual ~C2SBattleRecordPacket(){};

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
