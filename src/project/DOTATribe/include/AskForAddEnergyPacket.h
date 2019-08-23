// Name :		AskForAddEnergyPacket.h
// Function:	��������/����������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_ASKFORADDENERGY_H_
#define  _PACKECT_ASKFORADDENERGY_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SAskForAddEnergyPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	C2SAskForAddEnergyPacket();
	virtual ~C2SAskForAddEnergyPacket(){};

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
class S2CAskForAddEnergyPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CAskForAddEnergyPacket();
	virtual ~S2CAskForAddEnergyPacket();
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

class S2CAskForAddEnergyPacketFactory : public IPacketFactory
{
public:
	S2CAskForAddEnergyPacketFactory();
	virtual ~S2CAskForAddEnergyPacketFactory();

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
	static   void  OnS2CAskForAddEnergyPacketHandler(S2CAskForAddEnergyPacket* pPacket);
};

/*
	��������
*/
class C2SBuyEnergyPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	C2SBuyEnergyPacket();
	virtual ~C2SBuyEnergyPacket(){};
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

//S2C
class S2CBuyEnergyPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CBuyEnergyPacket(){};
	virtual ~S2CBuyEnergyPacket(){};
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);};
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class S2CBuyEnergyPacketFactory : public IPacketFactory
{
public:
	S2CBuyEnergyPacketFactory(){};
	virtual ~S2CBuyEnergyPacketFactory(){};
	virtual  unsigned  int  GetPacketType();
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
	static   void  OnS2CBuyEnergyPacketHandler(S2CBuyEnergyPacket* pPacket){};
};

/*
	�����ս����
*/
class C2SCleanChallengeTimesPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_mapid;
	int m_stageid;
public:
	C2SCleanChallengeTimesPacket(int mapid,int stageid);
	virtual ~C2SCleanChallengeTimesPacket(){};
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

//S2C
class S2CCleanChallengeTimesPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_mapid;
	int m_statesid;
	int m_diamondNum;


public:
	S2CCleanChallengeTimesPacket(){};
	virtual ~S2CCleanChallengeTimesPacket(){};
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);};
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class S2CCleanChallengeTimesPacketFactory : public IPacketFactory
{
public:
	S2CCleanChallengeTimesPacketFactory(){};
	virtual ~S2CCleanChallengeTimesPacketFactory(){};
	virtual  unsigned  int  GetPacketType();
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
	static   void  OnS2CCleanChallengeTimesPacketHandler(S2CCleanChallengeTimesPacket* pPacket){};
};

#endif