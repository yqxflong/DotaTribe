// Name:		CheckOpenFun.h
// Function:	�Ƿ���ĳЩ����
// Author:		�۱�

#ifndef _PACKET_CHECKOPENFUN_H_
#define _PACKET_CHECKOPENFUN_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SCheckOpenFunPacket : public IPacket{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SCheckOpenFunPacket();
	virtual ~C2SCheckOpenFunPacket(){};

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

class S2CCheckOpenFunPacket: public IPacket{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	S2CCheckOpenFunPacket();
	virtual ~S2CCheckOpenFunPacket();
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


class S2CCheckOpenFunPacketFactory : public IPacketFactory
{
public:
	S2CCheckOpenFunPacketFactory();
	virtual ~S2CCheckOpenFunPacketFactory();

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

private:
	/*
		�߼����ݰ�����
	*/
	static   void  OnS2CCheckOpenFunPacketHandler(S2CCheckOpenFunPacket* pPacket);
};


#endif