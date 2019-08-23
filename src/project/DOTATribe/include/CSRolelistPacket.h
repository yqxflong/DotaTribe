//Name��CSRolelistPacket
//Function��c->s ��ɫ�б�����
//Written By��lvyunlong

#ifndef  _PACKECT_CSROLELIST_H_
#define  _PACKECT_CSROLELIST_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSRolelistPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int���к�]
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