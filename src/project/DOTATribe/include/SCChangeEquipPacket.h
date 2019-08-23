//Name：SCRoleInfoPacket
//Function：s->c 更换装备后，角色信息
//Written By：尹强

#ifndef  _DOTATRIBE_SCCHANGEEQUIPPACKET_H_
#define  _DOTATRIBE_SCCHANGEEQUIPPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class SCChangeEquipPacket : public IPacket
{
/*
* 失败 ['Z''R'][n][2004][int序列号][int -1][string failureInfo]
* 成功 ['Z''R'][n][2004][int序列号][int  1][int count]{[byte type][int attrvalue]}
*/
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;
	int m_resultid;

public:
	SCChangeEquipPacket(){};
	virtual ~SCChangeEquipPacket(){};

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

class SCChangeEquipPacketFactory : public IPacketFactory
{
public:
	SCChangeEquipPacketFactory(){};
	virtual ~SCChangeEquipPacketFactory(){};

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