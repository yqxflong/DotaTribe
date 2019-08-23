//Name:EquipLvUpPacket.h
//Author;fangjun
//Function:装备升级包

#ifndef _DOTATRIBE_EQUIPMENTLVUP_PACKET_H_
#define _DOTATRIBE_EQUIPMENTLVUP_PACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class CSEquipmentLvUpPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int  m_EquipId;
	unsigned short m_SwallowCount;
	std::vector<int> m_SwallowEquipId;


public:
	CSEquipmentLvUpPacket(int equipid,int swallowCount, std::vector<int> & allid);
	virtual ~CSEquipmentLvUpPacket();

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
class SCEquipmentLvUpPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	SCEquipmentLvUpPacket(){};
	virtual ~SCEquipmentLvUpPacket(){};
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
	virtual  void  Send(){};
};

class SCEquipmentLvUpPacketFactory : public IPacketFactory
{
public:
	SCEquipmentLvUpPacketFactory(){};
	virtual ~SCEquipmentLvUpPacketFactory(){};

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