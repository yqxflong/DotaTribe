//Name:PayGoodsPacket
//Function: ��ֵ����Ʒ�����Э��
//Author:lvyunlong
//Date:20131119

#ifndef _DOTATRIBE_PAYGOODSPACKET_H_
#define _DOTATRIBE_PAYGOODSPACKET_H_

#include <include/mem/DPacket.h> 
#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"
#include "../include/CPublicVarReader.h"
#include <iostream>


/************************************************************************/
/* �����ֵ�б�ͷ���	                                                    */
/************************************************************************/
class CSPayItemListPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_ChannelId;
public:
	CSPayItemListPacket(unsigned char channel);
	virtual ~CSPayItemListPacket();

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


class SCPayItemListPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCPayItemListPacket(){};
	virtual ~SCPayItemListPacket(){};

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

class SCPayItemListPacketFactory : public IPacketFactory
{
public:
	SCPayItemListPacketFactory(){};
	virtual ~SCPayItemListPacketFactory(){};

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
/* �����ֵȷ�Ϻͳ�ֵȷ�Ͻ������											*/
/************************************************************************/
class CSPaySurePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_ChannelId;		//ƽ̨:  0:����  1:91ƽ̨  2:Appstore  3:SDk����
	unsigned short sizegoodsiap;
	std::string m_striapid;			//����ֵ�б��ɳ���billing���� 
	unsigned short sizeOrderld;
	std::string m_strOrderld;			//�����ţ���ֵ�������SDK���ظ��ͻ���
	unsigned short sizetransactReceipt;
	std::string m_strtransactReceipt;		//У��֤��
public:
	CSPaySurePacket(unsigned char channel,std::string iapid,std::string orderld,std::string transactReceipt);
	virtual ~CSPaySurePacket();

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


class SCPaySurePacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCPaySurePacket(){};
	virtual ~SCPaySurePacket(){};

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

class SCPaySurePacketFactory : public IPacketFactory
{
public:
	SCPaySurePacketFactory(){};
	virtual ~SCPaySurePacketFactory(){};

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
/* Androidר�ù���ʱ����													*/
/************************************************************************/
class CSAndroidPayInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAndroidPayInfoPacket();
	virtual ~CSAndroidPayInfoPacket();
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


class SCAndroidPayInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAndroidPayInfoPacket(){};
	virtual ~SCAndroidPayInfoPacket(){};

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

class SCAndroidPayInfoPacketFactory : public IPacketFactory
{
public:
	SCAndroidPayInfoPacketFactory(){};
	virtual ~SCAndroidPayInfoPacketFactory(){};

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
/* �����׳�����������Ϣ													*/
/************************************************************************/
class CSDoublePayInfoPacket : public DotaPacket
{
public:
	CSDoublePayInfoPacket(unsigned char channel);
	~CSDoublePayInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCDoublePayInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCDoublePayInfoPacket(){};
	virtual ~SCDoublePayInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSCDoublePayInfoPacketFactory : public IPacketFactory
{
public:
	SCSCDoublePayInfoPacketFactory(){};
	virtual ~SCSCDoublePayInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};
#endif