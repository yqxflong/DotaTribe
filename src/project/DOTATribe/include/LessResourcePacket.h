// Name :		LessResourcePacket.h
// Function:	��Դ������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_LESSRESOURCE_H_
#define  _PACKECT_LESSRESOURCE_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SLessResourcePacket : public IPacket
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
	C2SLessResourcePacket();
	virtual ~C2SLessResourcePacket(){};

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
class S2CLessResourcePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CLessResourcePacket();
	virtual ~S2CLessResourcePacket();
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

class S2CLessResourcePacketFactory : public IPacketFactory
{
public:
	S2CLessResourcePacketFactory();
	virtual ~S2CLessResourcePacketFactory();

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
	static   void  OnS2CLessResourcePacketHandler(S2CLessResourcePacket* pPacket);
};


/************************************************************************/
/*====================������=================
/************************************************************************/
class C2SChioseLessResourcePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_index;

public:
	C2SChioseLessResourcePacket();
	virtual ~C2SChioseLessResourcePacket(){};

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
class S2CChioseLessResourcePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	  
public:
	S2CChioseLessResourcePacket();
	virtual ~S2CChioseLessResourcePacket();
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

class S2CChioseLessResourcePacketFactory : public IPacketFactory
{
public:
	S2CChioseLessResourcePacketFactory();
	virtual ~S2CChioseLessResourcePacketFactory();

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
	static   void  OnS2CChioseLessResourcePacketHandler(S2CChioseLessResourcePacket* pPacket);
};
#endif
