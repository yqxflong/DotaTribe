//Name:NetObjectTipsPacket
//Function: ������Ʒtips
//Author:����
//Date:20131014

#ifndef _DOTATRIBE_NETOBJECTTIPSPACKET_H_
#define _DOTATRIBE_NETOBJECTTIPSPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSNetObjectTipsPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_iTemplateId;
public:
	CSNetObjectTipsPacket(int templateId);
	virtual ~CSNetObjectTipsPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

class SCNetObjectTipsResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCNetObjectTipsResultPacket(){};
	virtual ~SCNetObjectTipsResultPacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

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


class SCNetObjectTipsResultPacketFactory : public IPacketFactory
{
public:
	SCNetObjectTipsResultPacketFactory(){};
	virtual ~SCNetObjectTipsResultPacketFactory(){};

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
