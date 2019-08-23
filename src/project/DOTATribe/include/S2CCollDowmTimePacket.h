#ifndef  _DOTATRIBE_S2CCOLLTIMEPACKET_H_
#define  _DOTATRIBE_S2CCOLLTIMEPACKET_H_
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class S2CCollTimePacket : public IPacket
{ 
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;

public:
	S2CCollTimePacket(){};
	virtual ~S2CCollTimePacket(){};

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


	bool  LoadClearCollTimePacket(cobra_win::DPacket & packet);

	
	/*
		发送字节流
	*/
	virtual  void  Send(){};

};

class S2CCollTimePacketFactory : public IPacketFactory
{
public:
	S2CCollTimePacketFactory(){};
	virtual ~S2CCollTimePacketFactory(){};

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

