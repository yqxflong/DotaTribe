//Name：CSBagUseObjectPacket
//Function：c->s 使用物品
//Author : 方骏
//date : 2013-8-7

#ifndef  _PACKECT_CSBAGUSEOBJECT_H_
#define  _PACKECT_CSBAGUSEOBJECT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSBagUseObjectPacket : public IPacket
{
	/*
		
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serial;
	int m_itemId;
	int m_itemTemplateId;
	int m_count;

public:
	CSBagUseObjectPacket(int serial,int itemId, int itemTemplateId, int count);
	virtual ~CSBagUseObjectPacket(){};

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


#endif

