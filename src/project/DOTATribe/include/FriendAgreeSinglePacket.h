// Name :		FriendAgreeSinglePacket.h
// Function:	ͬ�ⵥ��������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _PACKECT_FRIENDAGREESINGLE_H_
#define  _PACKECT_FRIENDAGREESINGLE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendAgreeSinglePacket : public IPacket
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
	C2SFriendAgreeSinglePacket(int id);
	virtual ~C2SFriendAgreeSinglePacket(){};

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
class S2CFriendAgreeSinglePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_id;



public:
	S2CFriendAgreeSinglePacket();
	virtual ~S2CFriendAgreeSinglePacket();
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

class S2CFriendAgreeSinglePacketFactory : public IPacketFactory
{
public:
	S2CFriendAgreeSinglePacketFactory();
	virtual ~S2CFriendAgreeSinglePacketFactory();

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
	static   void  OnS2CFriendAgreeSinglePacketHandler(S2CFriendAgreeSinglePacket* pPacket);
};

#endif