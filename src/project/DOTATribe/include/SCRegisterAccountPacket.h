//Name：SCRegisterAccountPacket
//Function：s->c 回应账号注册
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCREGISTERACCOUNTPACKET_H_
#define  _DOTATRIBE_SCREGISTERACCOUNTPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCRegisterAccountPacket : public IPacket
{
public:
	unsigned short result_;
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCRegisterAccountPacket(){};
	virtual ~SCRegisterAccountPacket(){};

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

class SCRegisterAccountPacketFactory : public IPacketFactory
{
public:
	SCRegisterAccountPacketFactory(){};
	virtual ~SCRegisterAccountPacketFactory(){};

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

