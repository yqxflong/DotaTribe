//Name:TeamBattlePacket
//Function: ��Ӹ���������
//Author:����
//Date:2013-09-23

#ifndef _DOTATRIBE_TEAMBATTLEPACKET_H_
#define _DOTATRIBE_TEAMBATTLEPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* ��ȡ�����б���Ϣ                                                     */
/************************************************************************/
class CSTeamBattleGetDataPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
//	int m_fubenId;
public:
	CSTeamBattleGetDataPacket();//��������Id
	virtual ~CSTeamBattleGetDataPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

class SCTeamBattleGetDataPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamBattleGetDataPacket(){};
	virtual ~SCTeamBattleGetDataPacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

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


class SCTeamBattleGetDataPacketFactory : public IPacketFactory
{
public:
	SCTeamBattleGetDataPacketFactory(){};
	virtual ~SCTeamBattleGetDataPacketFactory(){};

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


//*******************************************************************
//c-s ���ý���
class CSTeamBattleResetDataPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_fubenId;
public:
	CSTeamBattleResetDataPacket(unsigned char fubenId);//��������Id
	virtual ~CSTeamBattleResetDataPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

//s-c���ý���
class SCTeamBattleResetDataResultPacket:public IPacket
{
 private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamBattleResetDataResultPacket(){};
	virtual ~SCTeamBattleResetDataResultPacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

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

class SCTeamBattleResetDataResultPacketFactory:public IPacketFactory
{
public:
	SCTeamBattleResetDataResultPacketFactory(){};
	~SCTeamBattleResetDataResultPacketFactory(){};

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

//*******************************************************************
//��ȡ����ͨ�ؽ���
class CSTeamBattleGateRewardPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_gateId;
	char m_rewardTag;
public:
	CSTeamBattleGateRewardPacket(unsigned char gateId, char rewardTag);//��������Id
	virtual ~CSTeamBattleGateRewardPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

class SCTeamBattleGateRewardResultPacketFactory:public IPacketFactory
{
public:
	SCTeamBattleGateRewardResultPacketFactory(){};
	~SCTeamBattleGateRewardResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};



/************************************************************************/
/* ����ū���б�     2153,2154                                           */
/************************************************************************/
class CSAskSlaveListPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAskSlaveListPacket();
	virtual ~CSAskSlaveListPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCAskSlaveListResultPacket:public IPacket
{
 private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAskSlaveListResultPacket(){};
	virtual ~SCAskSlaveListResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCAskSlaveListResultPacketFactory:public IPacketFactory
{
public:
	SCAskSlaveListResultPacketFactory(){};
	~SCAskSlaveListResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* �ٻ�ū��    2155                                                         */
/************************************************************************/
class CSHireSlavePacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_playerId;
public:
	CSHireSlavePacket(int playerId);
	virtual ~CSHireSlavePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

/************************************************************************/
/* ����Ӷ���б�     2157,2158                                                    */
/************************************************************************/
class CSAskMercenaryListPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAskMercenaryListPacket();
	virtual ~CSAskMercenaryListPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCAskMercenaryListResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAskMercenaryListResultPacket(){};
	virtual ~SCAskMercenaryListResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCAskMercenaryListResultPacketFactory:public IPacketFactory
{
public:
	SCAskMercenaryListResultPacketFactory(){};
	~SCAskMercenaryListResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* �ٻ�ū��    2155                                                         */
/************************************************************************/
class CSHireMercenaryPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_playerId;
public:
	CSHireMercenaryPacket(int playerId);
	virtual ~CSHireMercenaryPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

#endif
