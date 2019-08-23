//Name��CSRegisterAccountPacket
//Function��c->s �����˺�ע��
//Written By��lvyunlong

#ifndef  _PACKECT_CSREGISTERACCOUNT_H_
#define  _PACKECT_CSREGISTERACCOUNT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSRegisterAccountPacket : public IPacket
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
	unsigned short m_szpassword;
	std::string m_Strpassword;

public:
	CSRegisterAccountPacket(std::string accountname,std::string password);
	virtual ~CSRegisterAccountPacket(){};

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