//Name：CSRegisterAccountPacket
//Function：c->s 请求账号注册
//Written By：lvyunlong

#ifndef  _PACKECT_CSREGISTERACCOUNT_H_
#define  _PACKECT_CSREGISTERACCOUNT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSRegisterAccountPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_szaccountname;
	std::string m_Straccountname;
	unsigned short m_szpassword;
	std::string m_Strpassword;

public:
	CSRegisterAccountPacket(std::string accountname,std::string password);
	virtual ~CSRegisterAccountPacket(){};

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