//Name：SCQuickAccountRegisterPacket
//Function：s->c ACCOUNT_FAST_REGISTER_SERVER 
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCQUICKACCOUNTREGISTER_H_
#define  _DOTATRIBE_SCQUICKACCOUNTREGISTER_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCQuickAccountRegisterPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCQuickAccountRegisterPacket(){};
	virtual ~SCQuickAccountRegisterPacket(){};

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

class SCQuickAccountRegisterPacketFactory : public IPacketFactory
{
public:
	SCQuickAccountRegisterPacketFactory(){};
	virtual ~SCQuickAccountRegisterPacketFactory(){};

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

