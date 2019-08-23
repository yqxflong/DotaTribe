// Name :		FriendPacket.h
// Function:	������Ϣ
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FRIEND_H_
#define  _PACKECT_FRIEND_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SFriendPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;


public:
	C2SFriendPacket();
	virtual ~C2SFriendPacket(){};

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
class S2CFriendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CFriendPacket();
	virtual ~S2CFriendPacket();
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

class S2CFriendPacketFactory : public IPacketFactory
{
public:
	S2CFriendPacketFactory();
	virtual ~S2CFriendPacketFactory();

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
	static   void  OnS2CFriendPacketHandler(S2CFriendPacket* pPacket);
};


//S2C
class S2CUpdataFriendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;




public:
	S2CUpdataFriendPacket();
	virtual ~S2CUpdataFriendPacket();
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

class S2CUpdataFriendPacketFactory : public IPacketFactory
{
public:
	S2CUpdataFriendPacketFactory();
	virtual ~S2CUpdataFriendPacketFactory();

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
	static   void  OnS2CUpdataFriendPacketHandler(S2CUpdataFriendPacket* pPacket);
};

#endif