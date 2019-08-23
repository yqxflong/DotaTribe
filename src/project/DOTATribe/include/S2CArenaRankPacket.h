#ifndef  _DOTATRIBE_S2CARENARANKPACKET_H_
#define  _DOTATRIBE_S2CARENARANKPACKET_H_
 
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h> 
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
using namespace cobra_win;

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器返回竞技场排行榜数据
//date:   2013/08/29
///////////////////////////////////////////////// 
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
 

class S2CArenaRankPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial;

public:
	S2CArenaRankPacket(){};
	virtual ~S2CArenaRankPacket(){};
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

	bool	 LoadArenaRankData(cobra_win::DPacket & packetData);

};

class S2CArenaRankPacketFactory : public IPacketFactory
{
public:
	S2CArenaRankPacketFactory(){};
	virtual ~S2CArenaRankPacketFactory(){};

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


	void   PostShowRankWindowNotification();
};

 

#endif


