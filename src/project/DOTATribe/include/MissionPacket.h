// Name :		MissionPacket.h
// Function:	�ؿ���Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_MISSION_H_
#define  _PACKECT_MISSION_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class C2SMissionPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;
	

public:
	C2SMissionPacket(int serialnum);
	virtual ~C2SMissionPacket(){};

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
class S2CMissionPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;
	

public:


public:
	S2CMissionPacket();
	virtual ~S2CMissionPacket();

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

class S2CMissionPacketFactory : public IPacketFactory
{
public:
	S2CMissionPacketFactory();
	virtual ~S2CMissionPacketFactory();

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
	static   void  OnS2CMissionPacketHandler(S2CMissionPacket* pPacket);
};

#endif