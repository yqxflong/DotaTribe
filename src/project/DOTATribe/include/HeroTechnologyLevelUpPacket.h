// Name :		HeroTechnologyLevelUpPacket.h
// Function:	����������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_HEROTECHNOLOGRLEVELUP_H_
#define  _PACKECT_HEROTECHNOLOGRLEVELUP_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class C2SHeroTechnologyLevelUpPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int	  m_id;



public:
	C2SHeroTechnologyLevelUpPacket(int id);
	virtual ~C2SHeroTechnologyLevelUpPacket(){};

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
class S2CHeroTechnologyLevelUpPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;



public:
	S2CHeroTechnologyLevelUpPacket();
	virtual ~S2CHeroTechnologyLevelUpPacket();
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

class S2CHeroTechnologyLevelUpPacketFactory : public IPacketFactory
{
public:
	S2CHeroTechnologyLevelUpPacketFactory();
	virtual ~S2CHeroTechnologyLevelUpPacketFactory();

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
	static   void  OnS2CHeroTechnologyLevelUpPacketHandler(S2CHeroTechnologyLevelUpPacket* pPacket);
};

#endif