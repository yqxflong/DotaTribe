#ifndef  _DOTATRIBE_S2CAddChallengeCount_H
#define  _DOTATRIBE_S2CAddChallengeCount_H
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class S2CAddChallengeCountPacket : public IPacket
{ 
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;

public:
	S2CAddChallengeCountPacket(){};
	virtual ~S2CAddChallengeCountPacket(){};

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
	virtual  void  Send(){};

};

class S2CAddChallengeCountPacketFactory : public IPacketFactory
{
public:
	S2CAddChallengeCountPacketFactory(){};
	virtual ~S2CAddChallengeCountPacketFactory(){};

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

private:
	void   OnFinishCallBackHandler();
};
 
#endif

