// Name :		MultiRewardPacket.h
// Function:	���������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_MULTIREWARD_H_
#define  _PACKECT_MULTIREWARD_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SMultiRewardPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_type;

public:
	C2SMultiRewardPacket();
	virtual ~C2SMultiRewardPacket(){};

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

//S2C
class S2CMultiRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CMultiRewardPacket();
	virtual ~S2CMultiRewardPacket();
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

class S2CMultiRewardPacketFactory : public IPacketFactory
{
public:
	S2CMultiRewardPacketFactory();
	virtual ~S2CMultiRewardPacketFactory();

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
	static   void  OnS2CMultiRewardPacketHandler(S2CMultiRewardPacket* pPacket);
};

#endif
