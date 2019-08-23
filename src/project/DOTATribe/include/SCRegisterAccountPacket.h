//Name��SCRegisterAccountPacket
//Function��s->c ��Ӧ�˺�ע��
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCREGISTERACCOUNTPACKET_H_
#define  _DOTATRIBE_SCREGISTERACCOUNTPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCRegisterAccountPacket : public IPacket
{
public:
	unsigned short result_;
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCRegisterAccountPacket(){};
	virtual ~SCRegisterAccountPacket(){};

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

class SCRegisterAccountPacketFactory : public IPacketFactory
{
public:
	SCRegisterAccountPacketFactory(){};
	virtual ~SCRegisterAccountPacketFactory(){};

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

