//Name��SCQuickAccountRegisterPacket
//Function��s->c ACCOUNT_FAST_REGISTER_SERVER 
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCQUICKACCOUNTREGISTER_H_
#define  _DOTATRIBE_SCQUICKACCOUNTREGISTER_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCQuickAccountRegisterPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCQuickAccountRegisterPacket(){};
	virtual ~SCQuickAccountRegisterPacket(){};

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
	virtual  void  Send(){};

};

class SCQuickAccountRegisterPacketFactory : public IPacketFactory
{
public:
	SCQuickAccountRegisterPacketFactory(){};
	virtual ~SCQuickAccountRegisterPacketFactory(){};

public:
	/*
		������ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		���ݰ��������
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


#endif

