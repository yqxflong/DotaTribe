// Name :		ActivityPacket.h
// Function:	�������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_ACTIVITY_H_
#define  _PACKECT_ACTIVITY_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SActivityPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_type;

public:
	C2SActivityPacket();
	virtual ~C2SActivityPacket(){};

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
class S2CActivityPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CActivityPacket();
	virtual ~S2CActivityPacket();
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

class S2CActivityPacketFactory : public IPacketFactory
{
public:
	S2CActivityPacketFactory();
	virtual ~S2CActivityPacketFactory();

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
	static   void  OnS2CActivityPacketHandler(S2CActivityPacket* pPacket);
};


/************************************************************************/
/*====================ѡ��=================
/************************************************************************/
class C2SChioseActivityPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_index;

public:
	C2SChioseActivityPacket(int index);
	virtual ~C2SChioseActivityPacket(){};

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

/************************************************************************/
/*=====================����Ȫ=================
/************************************************************************/
class C2SInSpringPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_index;
public:
	C2SInSpringPacket();
	virtual ~C2SInSpringPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send();
};

//S2C
class S2CInSpringPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CInSpringPacket();
	virtual ~S2CInSpringPacket();
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

class S2CInSpringPacketFactory : public IPacketFactory
{
public:
	S2CInSpringPacketFactory();
	virtual ~S2CInSpringPacketFactory();

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
	static   void  OnS2CInSpringPacketHandler(S2CInSpringPacket* pPacket);
};

/************************************************************************/
/* ��ȡ��Ȫ��������                                                      */
/************************************************************************/
class S2CSpringRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CSpringRewardPacket();
	virtual ~S2CSpringRewardPacket();
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType(){return 1;}
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;}

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
 
class S2CSpringRewardPacketFactory : public IPacketFactory
{
public:
	S2CSpringRewardPacketFactory();
	virtual ~S2CSpringRewardPacketFactory();

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
/*====================��������=================
/************************************************************************/
  
//S2C
class S2CLevelUpRewardInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CLevelUpRewardInfoPacket();
	virtual ~S2CLevelUpRewardInfoPacket();
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
 
class S2CLevelUpRewardInfoPacketFactory : public IPacketFactory
{
public:
	S2CLevelUpRewardInfoPacketFactory();
	virtual ~S2CLevelUpRewardInfoPacketFactory();

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
	  �¼�֪ͨ
	*/
	void  S2CPacketNotification();
};

//������ȡ��������
class  C2SGetLevelUpRewardPacket : public IPacket
{
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	int	  m_nRewardLevel;
public:
	C2SGetLevelUpRewardPacket(int rewardLevel);
	virtual ~C2SGetLevelUpRewardPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send();
};
 
//S2C
class  S2CLevelUpRewardRecepitPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CLevelUpRewardRecepitPacket();
	virtual ~S2CLevelUpRewardRecepitPacket();
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


class S2CLevelUpRewardRecepitPacketFactory : public IPacketFactory
{
public:
	S2CLevelUpRewardRecepitPacketFactory();
	virtual ~S2CLevelUpRewardRecepitPacketFactory();

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
	  �¼�֪ͨ
	*/
	void  S2CPacketNotification();
};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// �һ�����ݰ�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// �����������ݰ�
////////////////////////////////////////////////////////////////////////// 
//S2C
class  S2CExchangeInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CExchangeInfoPacket();
	virtual ~S2CExchangeInfoPacket();
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


class S2CExchangeInfoPacketFactory : public IPacketFactory
{
public:
	S2CExchangeInfoPacketFactory();
	virtual ~S2CExchangeInfoPacketFactory();

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
	  �¼�֪ͨ
	*/
	void  S2CPacketNotification();
};

//////////////////////////////////////////////////////////////////////////
//     �ͻ��˷���һ�����
//////////////////////////////////////////////////////////////////////////
class  C2SExchangeExchangePacket : public IPacket
{
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	short m_nActivityID;
	short m_nExchangeID;
public:
	C2SExchangeExchangePacket(short activityID,short exchangeID);
	virtual ~C2SExchangeExchangePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send();
};
 
//////////////////////////////////////////////////////////////////////////
//     ���������سɹ��һ���ִ
//////////////////////////////////////////////////////////////////////////

//S2C
class  S2CExchangeExchangePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CExchangeExchangePacket();
	virtual ~S2CExchangeExchangePacket();
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


class S2CExchangeExchangePacketFactory : public IPacketFactory
{
public:
	S2CExchangeExchangePacketFactory();
	virtual ~S2CExchangeExchangePacketFactory();

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
	  �¼�֪ͨ
	*/
	void  S2CPacketNotification();
}; 

#endif
