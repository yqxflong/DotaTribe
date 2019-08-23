//Name：CSEnterGamePacket
//Function：c->s 请求进入游戏
//Written By：lvyunlong

#ifndef  _PACKECT_CSENTERGAME_H_
#define  _PACKECT_CSENTERGAME_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSEnterGamePacket : public IPacket
{
	/*
		['Z''R'][n][2019][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	//int m_serial;
	int m_RoleId;
	unsigned short m_szaccountName;
	std::string m_accountName;

public:
	CSEnterGamePacket(int id,std::string accountName);
	virtual ~CSEnterGamePacket(){};

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