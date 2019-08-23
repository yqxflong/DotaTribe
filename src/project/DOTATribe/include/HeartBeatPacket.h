//Name:HeartBeatPacket
//Function: ��������
//Author:fangjun
//Date:20130819

#ifndef _DOTATRIBE_HEARTBEATPACKET_H_
#define _DOTATRIBE_HEARTBEATPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSHeartBeatPacket : public IPacket
{

private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSHeartBeatPacket();
	virtual ~CSHeartBeatPacket();

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



class SCHeartBeatResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;


public:
	SCHeartBeatResultPacket();
	virtual ~SCHeartBeatResultPacket();
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

class SCHeartBeatResultPacketFactory : public IPacketFactory
{
public:
	SCHeartBeatResultPacketFactory();
	virtual ~SCHeartBeatResultPacketFactory();

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