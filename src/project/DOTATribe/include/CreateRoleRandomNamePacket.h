// Name :		CreateRoleRandomNamePacket.h
// Function:	��ɫ���������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _PACKECT_CREATEROLERANDOMNAME_H_
#define  _PACKECT_CREATEROLERANDOMNAME_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SCreateRoleRandomNamePacket : public IPacket
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
	C2SCreateRoleRandomNamePacket(int serialnum);
	virtual ~C2SCreateRoleRandomNamePacket(){};

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
class S2CCreateRoleRandomNamePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;

	std::string m_playerName;

public:
	S2CCreateRoleRandomNamePacket();
	virtual ~S2CCreateRoleRandomNamePacket();
	std::string GetPlayerName(){return m_playerName;};

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

class S2CCreateRoleRandomNamePacketFactory : public IPacketFactory
{
public:
	S2CCreateRoleRandomNamePacketFactory();
	virtual ~S2CCreateRoleRandomNamePacketFactory();

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
	static   void  OnS2CCreateRoleRandomNamePacketHandler(S2CCreateRoleRandomNamePacket* pPacket);
};

#endif