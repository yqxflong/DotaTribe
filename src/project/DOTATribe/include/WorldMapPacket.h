#ifndef  _PACKECT_WORLDMAP_H_
#define  _PACKECT_WORLDMAP_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SWorldMapPacket : public IPacket
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
	C2SWorldMapPacket(int serialnum);
	virtual ~C2SWorldMapPacket(){};

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
class S2CWorldMapPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;


public:
	S2CWorldMapPacket();
	virtual ~S2CWorldMapPacket();

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

class S2CWorldMapPacketFactory : public IPacketFactory
{
public:
	S2CWorldMapPacketFactory();
	virtual ~S2CWorldMapPacketFactory();

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
	static   void  OnS2CWorldMapPacketHandler(S2CWorldMapPacket* pPacket);
};

#endif