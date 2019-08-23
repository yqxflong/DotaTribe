//Name��CSQuickRegisterPacket
//Function��c->s �������ע��
//Written By��lvyunlong

#ifndef  _PACKECT_CSACCOUNTFASTREGISTER_H_
#define  _PACKECT_CSACCOUNTFASTREGISTER_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <string>

class CSQuickAccountRegisterPacket : public IPacket
{
	/*
		['Z''R'][n][2019][int���к�]
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