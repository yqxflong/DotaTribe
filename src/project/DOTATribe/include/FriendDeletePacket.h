// Name :		FriendDeletePacket.h
// Function:	ɾ��������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDDELETE_H_
#define  _PACKECT_FRIENDDELETE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendDeletePacket : public IPacket
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
	C2SFriendDeletePacket(int id);
	virtual ~C2SFriendDeletePacket(){};

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
class S2CFriendDeletePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_id;




public:
	S2CFriendDeletePacket();
	virtual ~S2CFriendDeletePacket();
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

class S2CFriendDeletePacketFactory : public IPacketFactory
{
public:
	S2CFriendDeletePacketFactory();
	virtual ~S2CFriendDeletePacketFactory();

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
	static   void  OnS2CFriendDeletePacketHandler(S2CFriendDeletePacket* pPacket);
};

#endif