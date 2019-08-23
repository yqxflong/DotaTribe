// Name :		AskForRoleInfoPacket.h
// Function:	����������Ϣ���ݰ�����¼ʱ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_ASKFORROLEINFO_H_
#define  _PACKECT_ASKFORROLEINFO_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SAskForRoleInfoPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;

	int m_playerID;
	int m_playerIdentifyingCode;

public:
	C2SAskForRoleInfoPacket(int serialnum,int playerID,int code);
	virtual ~C2SAskForRoleInfoPacket(){};

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
class S2CAskForRoleInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;


public:
	S2CAskForRoleInfoPacket();
	virtual ~S2CAskForRoleInfoPacket();

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

class S2CAskForRoleInfoPacketFactory : public IPacketFactory
{
public:
	S2CAskForRoleInfoPacketFactory();
	virtual ~S2CAskForRoleInfoPacketFactory();

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
	static   void  OnS2CAskForRoleInfoPacketHandler(S2CAskForRoleInfoPacket* pPacket);
};

#endif