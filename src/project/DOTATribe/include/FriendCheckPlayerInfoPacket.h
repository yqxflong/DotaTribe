// Name :		FriendCheckPlayerInfoPacket.h
// Function:	�鿴������Ϣ��Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIENDCHECKPLAYERINFO_H_
#define  _PACKECT_FRIENDCHECKPLAYERINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendCheckPlayerInfoPacket : public IPacket
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
	C2SFriendCheckPlayerInfoPacket(int id);
	virtual ~C2SFriendCheckPlayerInfoPacket(){};

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
class S2CFriendCheckPlayerInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendCheckPlayerInfoPacket();
	virtual ~S2CFriendCheckPlayerInfoPacket();
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

class S2CFriendCheckPlayerInfoPacketFactory : public IPacketFactory
{
public:
	S2CFriendCheckPlayerInfoPacketFactory();
	virtual ~S2CFriendCheckPlayerInfoPacketFactory();

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
	static   void  OnS2CFriendCheckPlayerInfoPacketHandler(S2CFriendCheckPlayerInfoPacket* pPacket);
};

#endif