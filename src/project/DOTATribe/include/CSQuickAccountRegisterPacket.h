//Name：CSQuickRegisterPacket
//Function：c->s 请求快速注册
//Written By：lvyunlong

#ifndef  _PACKECT_CSACCOUNTFASTREGISTER_H_
#define  _PACKECT_CSACCOUNTFASTREGISTER_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSQuickAccountRegisterPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_szdeviceId;
	std::string m_StrdeviceId;

public:
	CSQuickAccountRegisterPacket(std::string deviceId);
	virtual ~CSQuickAccountRegisterPacket(){};

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