#ifndef  _DOTATRIBE_S2CARENAGIGPACKET_H_
#define  _DOTATRIBE_S2CARENAGIGPACKET_H_
 
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h> 
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
using namespace cobra_win;

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器返回竞技场礼包
//date:   2013/08/29
///////////////////////////////////////////////// 
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
 
class S2CArenaGifPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	S2CArenaGifPacket(){};
	virtual ~S2CArenaGifPacket(){};
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


	bool	 LoadArenaGifData(cobra_win::DPacket & packetData);

};

class S2CArenaGifPacketFactory : public IPacketFactory
{
public:
	S2CArenaGifPacketFactory(){};
	virtual ~S2CArenaGifPacketFactory(){};

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


	void   PostNotification();
};

 

#endif


