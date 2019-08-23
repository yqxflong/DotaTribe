//Name:AttributeLockPacket
//Function: ����������
//Author:fangjun
//Date:20130821

#ifndef _DOTATRIBE_ATTRIBUTELOCKPACKET_H_
#define _DOTATRIBE_ATTRIBUTELOCKPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSAttributeLockPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int serial;
	int equipId;
	int attriIndex;

public:
	CSAttributeLockPacket(int serial, int eqid, unsigned char attriIndex);
	virtual ~CSAttributeLockPacket();

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



class SCAttributeLockResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;


public:
	SCAttributeLockResultPacket();
	virtual ~SCAttributeLockResultPacket();
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

class SCAttributeLockResultPacketFactory : public IPacketFactory
{
public:
	SCAttributeLockResultPacketFactory();
	virtual ~SCAttributeLockResultPacketFactory();

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

};



class CSAttributeUnLockPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int serial;
	int equipId;
	unsigned char attriIndex;

public:
	CSAttributeUnLockPacket(int s, int eid, int index);

	virtual ~CSAttributeUnLockPacket();

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



class SCAttributeUnLockResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;


public:
	SCAttributeUnLockResultPacket();
	virtual ~SCAttributeUnLockResultPacket();
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

class SCAttributeUnLockResultPacketFactory : public IPacketFactory
{
public:
	SCAttributeUnLockResultPacketFactory();
	virtual ~SCAttributeUnLockResultPacketFactory();

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

};


#endif