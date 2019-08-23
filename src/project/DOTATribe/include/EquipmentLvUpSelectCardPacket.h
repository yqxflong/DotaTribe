//Name:EquipLvUpSelectCardPacket.h
//Author;fangjun
//Function:装备升级选卡包

#ifndef _DOTATRIBE_EQUIPLVUPSELECTCARD_PACKET_H_
#define _DOTATRIBE_EQUIPLVUPSELECTCARD_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class CSEquipmentLvUpSelectCardPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
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
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
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
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
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
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

};

#endif