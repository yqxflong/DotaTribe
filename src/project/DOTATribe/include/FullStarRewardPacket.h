// Name :		FullStarRewardPacket.h
// Function:	�ؿ���ȡȫ���ǽ�����Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_FULLSTARREWARD_H_
#define  _PACKECT_FULLSTARREWARD_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SFullStarRewardPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;

	//����
	unsigned short m_mapID;;				// ��ͼID<br>
public:
	C2SFullStarRewardPacket(int mapID);
	virtual ~C2SFullStarRewardPacket(){};

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
class S2CFullStarRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

	unsigned short m_mapID;
	
public:
	S2CFullStarRewardPacket();
	virtual ~S2CFullStarRewardPacket();

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

class S2CFullStarRewardPacketFactory : public IPacketFactory
{
public:
	S2CFullStarRewardPacketFactory();
	virtual ~S2CFullStarRewardPacketFactory();

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
	static   void  OnS2CFullStarRewardPacketHandler(S2CFullStarRewardPacket* pPacket);
};

#endif