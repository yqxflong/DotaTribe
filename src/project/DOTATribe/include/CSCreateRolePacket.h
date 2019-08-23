//Name��CSCreateRolePacket
//Function��c->s ������ɫ
//Written By����ǿ
#ifndef  _dotatribe_PACKECT_CSCREATEROLE_H_
#define  _dotatribe_PACKECT_CSCREATEROLE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSCreateRolePacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�][int�˺�ID][intӢ��ID][string��ɫ����]
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

