//Name��CSEnterGamePacket
//Function��c->s ���������Ϸ
//Written By��lvyunlong

#ifndef  _PACKECT_CSENTERGAME_H_
#define  _PACKECT_CSENTERGAME_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSEnterGamePacket : public IPacket
{
	/*
		['Z''R'][n][2019][int���к�]
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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};


#endif