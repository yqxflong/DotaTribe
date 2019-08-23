//Name:EquipLvUpSelectCardPacket.h
//Author;fangjun
//Function:װ������ѡ����

#ifndef _DOTATRIBE_EQUIPLVUPSELECTCARD_PACKET_H_
#define _DOTATRIBE_EQUIPLVUPSELECTCARD_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class CSEquipmentLvUpSelectCardPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_SwallowCount;
	std::vector<int> m_SwallowEquipId;


public:
	CSEquipmentLvUpSelectCardPacket(int swallowCount, std::vector<int> & allid);
	virtual ~CSEquipmentLvUpSelectCardPacket();

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
class SCEquipmentLvUpSelectCardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	SCEquipmentLvUpSelectCardPacket();
	virtual ~SCEquipmentLvUpSelectCardPacket();
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

class SCEquipmentLvUpSelectCardPacketFactory : public IPacketFactory
{
public:
	SCEquipmentLvUpSelectCardPacketFactory();
	virtual ~SCEquipmentLvUpSelectCardPacketFactory();

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