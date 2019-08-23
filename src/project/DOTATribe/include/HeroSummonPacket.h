//Name:HeroSummonPacket
//Function: Ӣ���ٻ����Э��
//Author:lvyunlong
//Date:20131205

#ifndef _DOTATRIBE_HEROSUMMONPACKET_H_
#define _DOTATRIBE_HEROSUMMONPACKET_H_

#include <include/mem/DPacket.h> 
#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* �������Ӣ���ٻ���Ϣ		                                            */
/************************************************************************/
class CSHeroSummonInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSHeroSummonInfoPacket();
	virtual ~CSHeroSummonInfoPacket();

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


class SCHeroSummonInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroSummonInfoPacket(){};
	virtual ~SCHeroSummonInfoPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCHeroSummonInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroSummonInfoPacketFactory(){};
	virtual ~SCHeroSummonInfoPacketFactory(){};

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
/* �������Ӣ���ٻ�														*/
/************************************************************************/
class CSHeroSoulSummonPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_type;
	unsigned char m_times;
	unsigned char m_freetype;
public:
	CSHeroSoulSummonPacket(unsigned char type,unsigned char times,unsigned char freetype);
	virtual ~CSHeroSoulSummonPacket();

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


class SCHeroSoulSummonPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroSoulSummonPacket(){};
	virtual ~SCHeroSoulSummonPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCHeroSoulSummonPacketFactory : public IPacketFactory
{
public:
	SCHeroSoulSummonPacketFactory(){};
	virtual ~SCHeroSoulSummonPacketFactory(){};

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
/* ʮ������Ӣ��														*/
/************************************************************************/
class SCTenCallPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCTenCallPacket(){};
	virtual ~SCTenCallPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCSCTenCallPacketFactory : public IPacketFactory
{
public:
	SCSCTenCallPacketFactory(){};
	virtual ~SCSCTenCallPacketFactory(){};

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
/* ʹ����Ʒ���Ӣ��														*/
/************************************************************************/
class SCUserItemGainHeroPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCUserItemGainHeroPacket(){};
	virtual ~SCUserItemGainHeroPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCUserItemGainHeroPacketFactory : public IPacketFactory
{
public:
	SCUserItemGainHeroPacketFactory(){};
	virtual ~SCUserItemGainHeroPacketFactory(){};

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