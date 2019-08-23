//Name:EquipTrainPacket
//Function: ����������
//Author:fangjun
//Date:20130821

#ifndef _DOTATRIBE_EQUIPTRAINPACKET_H_
#define _DOTATRIBE_EQUIPTRAINPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* ��ȡװ����������״̬                                                                     */
/************************************************************************/
class CSEquipTrainGetLockStatus : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int equipId;
public:
	CSEquipTrainGetLockStatus(int eqid);
	virtual ~CSEquipTrainGetLockStatus();

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
class SCEquipTrainGetLockStatusResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEquipTrainGetLockStatusResultPacket();
	virtual ~SCEquipTrainGetLockStatusResultPacket();
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

class SCEquipTrainGetLockStatusResultPacketFactory : public IPacketFactory
{
public:
	SCEquipTrainGetLockStatusResultPacketFactory();
	virtual ~SCEquipTrainGetLockStatusResultPacketFactory();

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
/* ϴ��                                                                     */
/************************************************************************/


class CSEquipTrainPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int equipId;

public:
	CSEquipTrainPacket(int eqid);
	virtual ~CSEquipTrainPacket();

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


class SCEquipTrainResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEquipTrainResultPacket();
	virtual ~SCEquipTrainResultPacket();
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

class SCEquipTrainResultPacketFactory : public IPacketFactory
{
public:
	SCEquipTrainResultPacketFactory();
	virtual ~SCEquipTrainResultPacketFactory();

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