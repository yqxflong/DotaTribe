//Name��CSBagUseObjectPacket
//Function��c->s ʹ����Ʒ
//Author : ����
//date : 2013-8-7

#ifndef  _PACKECT_CSBAGUSEOBJECT_H_
#define  _PACKECT_CSBAGUSEOBJECT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSBagUseObjectPacket : public IPacket
{
	/*
		
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;
	int m_itemId;
	int m_itemTemplateId;
	int m_count;

public:
	CSBagUseObjectPacket(int serial,int itemId, int itemTemplateId, int count);
	virtual ~CSBagUseObjectPacket(){};

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

