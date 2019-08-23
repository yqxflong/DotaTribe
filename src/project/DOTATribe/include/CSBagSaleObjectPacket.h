//Name：CSBagSaleObjectPacket
//Function：c->s 出售物品
//Author : 方骏
//date : 2013-8-5

#ifndef  _PACKECT_CSBAGSALEOBJECT_H_
#define  _PACKECT_CSBAGSALEOBJECT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSBagSaleObjectPacket : public IPacket
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
	CSBagSaleObjectPacket(int serial,int itemId, int itemTemplateId, int count);
	virtual ~CSBagSaleObjectPacket(){};

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

