//Name：CSRolelistPacket
//Function：c->s 角色列表请求
//Written By：lvyunlong

#ifndef  _PACKECT_CSROLELIST_H_
#define  _PACKECT_CSROLELIST_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSRolelistPacket : public IPacket
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
	int m_key;
public:
	CSRolelistPacket(std::string accountname,int key);
	virtual ~CSRolelistPacket(){};

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