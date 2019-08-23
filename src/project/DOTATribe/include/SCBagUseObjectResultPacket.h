//Name��SCBagUseObjectResultPacket
//Function��s->c ʹ����Ϣ�ķ���
//Author : ����

#ifndef  _DOTATRIBE_SCBAGUSEOBJECTRESULTPACKET_H_
#define  _DOTATRIBE_SCBAGUSEOBJECTRESULTPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>



class SCBagUseObjectResultPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCBagUseObjectResultPacket(){};
	virtual ~SCBagUseObjectResultPacket(){};

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

class SCBagUseObjectResultPacketFactory : public IPacketFactory
{
public:
	SCBagUseObjectResultPacketFactory(){};
	virtual ~SCBagUseObjectResultPacketFactory(){};

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

