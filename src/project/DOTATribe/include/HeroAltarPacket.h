//Name:HeroAltarPacket
//Function: Ӣ���׼����Э��
//Author:lvyunlong
//Date:20131202

#ifndef _DOTATRIBE_HEROALTARPACKET_H_
#define _DOTATRIBE_HEROALTARPACKET_H_

#include <include/mem/DPacket.h> 
#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* �����̳��Ϣ		                                                    */
/************************************************************************/
class CSHeroTotemInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSHeroTotemInfoPacket();
	virtual ~CSHeroTotemInfoPacket();

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


class SCHeroTotemInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroTotemInfoPacket(){};
	virtual ~SCHeroTotemInfoPacket(){};

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

class SCHeroTotemInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroTotemInfoPacketFactory(){};
	virtual ~SCHeroTotemInfoPacketFactory(){};

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
/* �����׼���Ϣ�ͷ����������׼���Ϣ										*/
/************************************************************************/
class CSHeroAltarInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSHeroAltarInfoPacket();
	virtual ~CSHeroAltarInfoPacket();

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


class SCHeroAltarInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroAltarInfoPacket(){};
	virtual ~SCHeroAltarInfoPacket(){};

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

class SCHeroAltarInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroAltarInfoPacketFactory(){};
	virtual ~SCHeroAltarInfoPacketFactory(){};

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
/* �ͻ��˷����׼���Ƭ��Ϣ�ͷ�����������Ƭ�׼������Ϣ						*/
/************************************************************************/
class CSHeroDebrisAltarPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_type;
	unsigned char m_count;
public:
	CSHeroDebrisAltarPacket(unsigned char type,unsigned char count);
	virtual ~CSHeroDebrisAltarPacket();

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


class SCHeroDebrisAltarPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroDebrisAltarPacket(){};
	virtual ~SCHeroDebrisAltarPacket(){};

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

class SCHeroDebrisAltarPacketFactory : public IPacketFactory
{
public:
	SCHeroDebrisAltarPacketFactory(){};
	virtual ~SCHeroDebrisAltarPacketFactory(){};

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
/* �����׼� ÿ�������ı�/player/xianji.xlsx<br>						*/
/************************************************************************/
class CSAltarCheckInfoTablePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAltarCheckInfoTablePacket();
	virtual ~CSAltarCheckInfoTablePacket();

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


class SCAltarCheckInfoTablePacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAltarCheckInfoTablePacket(){};
	virtual ~SCAltarCheckInfoTablePacket(){};

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

class SCAltarCheckInfoTablePacketFactory : public IPacketFactory
{
public:
	SCAltarCheckInfoTablePacketFactory(){};
	virtual ~SCAltarCheckInfoTablePacketFactory(){};

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