// Name :		MassacrePacket.h
// Function:	ɨ����Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_MASSACRE_H_
#define  _PACKECT_MASSACRE_H_

#include "../include/DotaPacket.h"
#include "../include/PacketFactory.h"

class C2SMassacrePacket : public DotaPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
public:
	C2SMassacrePacket(int mapid ,int stageid);
	virtual ~C2SMassacrePacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
};



//S2C
class S2CMassacrePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;
	
public:
	S2CMassacrePacket(){};
	virtual ~S2CMassacrePacket(){};

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
	virtual  void  Send(){};
};

class S2CMassacrePacketFactory : public IPacketFactory
{
public:
	S2CMassacrePacketFactory(){};
	virtual ~S2CMassacrePacketFactory(){};

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