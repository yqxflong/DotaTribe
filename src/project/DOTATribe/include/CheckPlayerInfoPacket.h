// Name :		CheckPlayerInfoPacket.h
// Function:	�鿴������Ϣ��Ϣ��
// Author :		�۱�
// Maintainer:  �۱�

#ifndef  _PACKECT_CHECKPLAYERINFO_H_
#define  _PACKECT_CHECKPLAYERINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SCheckPlayerInfoPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_id;


public:
	C2SCheckPlayerInfoPacket(int id);
	virtual ~C2SCheckPlayerInfoPacket(){};

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
class S2CCheckPlayerInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CCheckPlayerInfoPacket();
	virtual ~S2CCheckPlayerInfoPacket();
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

class S2CCheckPlayerInfoPacketFactory : public IPacketFactory
{
public:
	S2CCheckPlayerInfoPacketFactory();
	virtual ~S2CCheckPlayerInfoPacketFactory();

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
	static   void  OnS2CCheckPlayerInfoPacketHandler(S2CCheckPlayerInfoPacket* pPacket);
};

#endif