//Name:ClimbTowerPacket
//Function: ������
//Author:fangjun
//Date:20130826

#ifndef _DOTATRIBE_CLIMBTOWERPACKET_H_
#define _DOTATRIBE_CLIMBTOWERPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"


/************************************************************************/
/* �����ħ��                                                           */
/************************************************************************/
class CSEnterTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSEnterTowerPacket();
	virtual ~CSEnterTowerPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

class SCEnterTowerResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	SCEnterTowerResultPacket();
	virtual ~SCEnterTowerResultPacket();

public:

	virtual  unsigned  int  GetPacketType();

	virtual  unsigned  int  GetPacketLength(){	return 1;	};

public:

	virtual  bool  Read(char* pBuffer, unsigned int iLen);

	virtual  void  Send(){};
};

class SCEnterTowerResultPacketFactory : public IPacketFactory
{
public:
	SCEnterTowerResultPacketFactory();
	virtual ~SCEnterTowerResultPacketFactory();

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

/************************************************************************/
/* ��������ʼ����                                                                     */
/************************************************************************/
class CSStartTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSStartTowerPacket();
	virtual ~CSStartTowerPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

class SCStartTowerResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	SCStartTowerResultPacket(){};
	virtual ~SCStartTowerResultPacket(){};

public:

	virtual  unsigned  int  GetPacketType();

	virtual  unsigned  int  GetPacketLength(){	return 1;	};

public:

	virtual  bool  Read(char* pBuffer, unsigned int iLen);

	virtual  void  Send(){};
};

class SCStartTowerResultPacketFactory : public IPacketFactory
{
public:
	SCStartTowerResultPacketFactory(){};
	virtual ~SCStartTowerResultPacketFactory(){};

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


/************************************************************************/
/* ��ս��ħ�ؿ�                                                         */
/************************************************************************/


class CSChallengeTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;

public:
	CSChallengeTowerPacket(int serialId);
	virtual ~CSChallengeTowerPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};


/************************************************************************/
/* ����������¼                                                         */
/************************************************************************/

class CSResetTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSResetTowerPacket();
	virtual ~CSResetTowerPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};


class SCResetTowerResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCResetTowerResultPacket();
	virtual ~SCResetTowerResultPacket();
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

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

class SCResetTowerResultPacketFactory : public IPacketFactory
{
public:
	SCResetTowerResultPacketFactory();
	virtual ~SCResetTowerResultPacketFactory();

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



/************************************************************************/
/* �������а�                                                           */
/************************************************************************/
class CSTowerRankPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSTowerRankPacket();
	virtual ~CSTowerRankPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};


class SCTowerRankResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTowerRankResultPacket();
	virtual ~SCTowerRankResultPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerRankResultPacketFactory : public IPacketFactory
{
public:
	SCTowerRankResultPacketFactory();
	virtual ~SCTowerRankResultPacketFactory();

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* ����,��ʯ����                                                       */
/************************************************************************/
class CSTowerJewelResetPacket : public IPacket
{
public:
	CSTowerJewelResetPacket();
	virtual ~CSTowerJewelResetPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};


class SCTowerJewelResetResultPacket : public IPacket
{
public:
	SCTowerJewelResetResultPacket(){};
	virtual ~SCTowerJewelResetResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerJewelResetResultPacketFactory : public IPacketFactory
{
public:
	SCTowerJewelResetResultPacketFactory(){};
	virtual ~SCTowerJewelResetResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ����,����ս��                                                       */
/************************************************************************/
class CSTowerFastFightPacket : public IPacket
{
public:
	CSTowerFastFightPacket();
	virtual ~CSTowerFastFightPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

class SCTowerFastFightResultPacket : public IPacket
{
public:
	SCTowerFastFightResultPacket(){};
	virtual ~SCTowerFastFightResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerFastFightResultPacketFactory : public IPacketFactory
{
public:
	SCTowerFastFightResultPacketFactory(){};
	virtual ~SCTowerFastFightResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ����,�����б�                                                       */
/************************************************************************/
class CSTowerRewardPacket : public IPacket
{
public:
	CSTowerRewardPacket();
	virtual ~CSTowerRewardPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

class SCTowerRewardResultPacket : public IPacket
{
public:
	SCTowerRewardResultPacket(){};
	virtual ~SCTowerRewardResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerRewardResultPacketFactory : public IPacketFactory
{
public:
	SCTowerRewardResultPacketFactory(){};
	virtual ~SCTowerRewardResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ����,��ȡĳ�㽱��                                                       */
/************************************************************************/
class CSTowerGetRewardPacket : public IPacket
{
private:
	char m_iType;
	unsigned short m_iFloor;
public:
	CSTowerGetRewardPacket(char type, unsigned short floor);
	virtual ~CSTowerGetRewardPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

class SCTowerGetRewardResultPacket : public IPacket
{
public:
	SCTowerGetRewardResultPacket(){};
	virtual ~SCTowerGetRewardResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerGetRewardResultPacketFactory : public IPacketFactory
{
public:
	SCTowerGetRewardResultPacketFactory(){};
	virtual ~SCTowerGetRewardResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/*
	������������
*/
class CSBuyClimbTowerTimesPacket:public DotaPacket
{
public:
	virtual  unsigned  int  GetPacketType();
};

class SCBuyClimbTowerTimesPacketFactory : public IPacketFactory
{
public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif
