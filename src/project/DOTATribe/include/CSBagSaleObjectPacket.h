//Name��CSBagSaleObjectPacket
//Function��c->s ������Ʒ
//Author : ����
//date : 2013-8-5

#ifndef  _PACKECT_CSBAGSALEOBJECT_H_
#define  _PACKECT_CSBAGSALEOBJECT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSBagSaleObjectPacket : public IPacket
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
	CSBagSaleObjectPacket(int serial,int itemId, int itemTemplateId, int count);
	virtual ~CSBagSaleObjectPacket(){};

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

