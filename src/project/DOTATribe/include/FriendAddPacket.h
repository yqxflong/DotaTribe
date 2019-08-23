// Name :		FriendAddPacket.h
// Function:	���Ӻ�����Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _PACKECT_FRIENDADD_H_
#define  _PACKECT_FRIENDADD_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendAddPacket : public IPacket
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
	C2SFriendAddPacket(int id);
	virtual ~C2SFriendAddPacket(){};

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
class S2CFriendAddPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendAddPacket();
	virtual ~S2CFriendAddPacket();
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

class S2CFriendAddPacketFactory : public IPacketFactory
{
public:
	S2CFriendAddPacketFactory();
	virtual ~S2CFriendAddPacketFactory();

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
	static   void  OnS2CFriendAddPacketHandler(S2CFriendAddPacket* pPacket);
};

#endif