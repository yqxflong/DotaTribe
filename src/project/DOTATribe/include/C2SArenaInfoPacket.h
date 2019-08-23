
#ifndef  _PACKECT_ARENAINFOPACKET_H_
#define  _PACKECT_ARENAINFOPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求竞技场数据包
//date:   2013/08/29
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"

class C2SArenaInfoPacket : public IPacket
{ 

private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;  

public:
	C2SArenaInfoPacket(int serial=0);
	virtual ~C2SArenaInfoPacket(){};

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

class C2SArenaRewardPacket : public IPacket
{  
private:
	char m_head[2];
	int  m_len;
	short m_pn;    
public:
	C2SArenaRewardPacket();
	virtual ~C2SArenaRewardPacket(){}; 
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
 
//////////////////////////////////////////////////////////////////////////

class C2SChallengeCountRewardPacket : public IPacket
{  
private:
	char  m_head[2];
	int   m_len;
	short m_pn;    
	short m_nChallenegeCount;
public:
	C2SChallengeCountRewardPacket(short challengeCount);
	virtual ~C2SChallengeCountRewardPacket(){}; 
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