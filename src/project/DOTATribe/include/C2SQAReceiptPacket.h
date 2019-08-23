#ifndef  _DOTATRIBE_QARECEIPTPACKET_H
#define  _DOTATRIBE_QARECEIPTPACKET_H

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class  C2SQAReceiptPacket : public IPacket
{
public:
	enum
	{
		_QA_Receipt_Cancel_Type_,
		_QA_Receipt_Sure_Type_,
	};
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
	int   m_qaType;
	char  m_qaSelect;
	char  m_paramCount;
public:
	C2SQAReceiptPacket(char qaSelect);
	virtual ~C2SQAReceiptPacket(){};

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

