//Name：CSCreateRolePacket
//Function：c->s 创建角色
//Written By：尹强
#ifndef  _dotatribe_PACKECT_CSCREATEROLE_H_
#define  _dotatribe_PACKECT_CSCREATEROLE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSCreateRolePacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号][int账号ID][int英雄ID][string角色名称]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;
	unsigned short m_szaccountName;
	std::string m_accountName;
	int m_heroid;
	unsigned short m_szrolename;
	std::string m_rolename;

public:
	CSCreateRolePacket(int serialnum,std::string accountname,int heroid,std::string rolename);
	virtual ~CSCreateRolePacket(){};

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

