//Name��CSChangeSkinPacket
//Function��c->s ��������
//Written By����ǿ
#ifndef  _PACKECT_CSCHANGESKIN_H_
#define  _PACKECT_CSCHANGESKIN_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSChangeSkinPacket : public IPacket
{
	/*
		['Z''R'][n][2003][int���к�][int����ID]   
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;
	int m_skinID;

public:
	CSChangeSkinPacket(int serial,int skinID);
	virtual ~CSChangeSkinPacket(){};

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

