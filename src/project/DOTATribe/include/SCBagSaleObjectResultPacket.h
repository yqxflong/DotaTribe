//Name��SCBagSaleObjectResultPacket
//Function��s->c ������Ϣ�ķ���
//Author : ����

#ifndef  _DOTATRIBE_SCBAGSALEOBJECTRESULTPACKET_H_
#define  _DOTATRIBE_SCBAGSALEOBJECTRESULTPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>



class SCBagSaleObjectResultPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCBagSaleObjectResultPacket(){};
	virtual ~SCBagSaleObjectResultPacket(){};

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

class SCBagSaleObjectResultPacketFactory : public IPacketFactory
{
public:
	SCBagSaleObjectResultPacketFactory(){};
	virtual ~SCBagSaleObjectResultPacketFactory(){};

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

