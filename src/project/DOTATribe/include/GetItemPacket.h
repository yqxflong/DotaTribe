//Name:GetItemPacket
//Function: �����ƷЧ��������Դ
//Author:��ǿ

#ifndef _DOTATRIBE_GetItemPacket_H_
#define _DOTATRIBE_GetItemPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class SCGetItemPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCGetItemPacket(){};
	virtual ~SCGetItemPacket(){};
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

class SCGetItemPacketFactory : public IPacketFactory
{
public:
	SCGetItemPacketFactory(){};
	virtual ~SCGetItemPacketFactory(){};

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