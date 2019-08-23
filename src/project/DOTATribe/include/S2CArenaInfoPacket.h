#ifndef  _DOTATRIBE_S2CARENAINFOPACKET_H_
#define  _DOTATRIBE_S2CARENAINFOPACKET_H_
 
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h> 
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
using namespace cobra_win;

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器返回竞技场数据
//date:   2013/08/29
///////////////////////////////////////////////// 
  

#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
 

class S2CArenaInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial;

public:
	S2CArenaInfoPacket(){};
	virtual ~S2CArenaInfoPacket(){};
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


	bool	 LoadArenaInfoData(cobra_win::DPacket & packetData);

};

class S2CArenaInfoPacketFactory : public IPacketFactory
{
public:
	S2CArenaInfoPacketFactory(){};
	virtual ~S2CArenaInfoPacketFactory(){}; 
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

	void   PostShowArenaSceneNotification();
};


//////////////////////////////////////////////////////////////////////////

//竞技场奖励数据结构
class  S2CArenaRewardPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	S2CArenaRewardPacket(){};
	virtual ~S2CArenaRewardPacket(){};
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

	bool	 LoadArenaRewardData(cobra_win::DPacket & packetData);
 
};

class S2CArenaRewardPacketFactory : public IPacketFactory
{
public:
	S2CArenaRewardPacketFactory(){};
	virtual ~S2CArenaRewardPacketFactory(){};

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
	 
	void   PostShowArenaRewardNotification();
};

//////////////////////////////////////////////////////////////////////////
 
//竞技场奖励数据结构
class  S2CChallenegeCountRewardPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	S2CChallenegeCountRewardPacket(){};
	virtual ~S2CChallenegeCountRewardPacket(){};
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

	bool	 LoadConfimData(cobra_win::DPacket & packetData);
 
};

class S2CChallenegeCountRewardPacketFactory : public IPacketFactory
{
public:
	S2CChallenegeCountRewardPacketFactory(){};
	virtual ~S2CChallenegeCountRewardPacketFactory(){};

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
	  
};

 


 

#endif


