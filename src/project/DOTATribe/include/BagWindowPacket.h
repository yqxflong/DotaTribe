//Name:BagWindowPacket
//Function:����ϵͳ��ͨѶ��
//Author:fangjun
//Date:20130909

#ifndef _BAGWINDOW_PACKET_H_
#define _BAGWINDOW_PACKET_H_

#include "../include/IPacket.h"
#include "../include/PacketFactory.h"
#include <iostream>
#include "../include/AthleticProcedureDataHandler.h"
#include  "../include/AthleticProcedureDataType.h"
#include <include/mem/DPacket.h>
 
class  CSOpenLockBagPacket: public IPacket
{
public:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_iBagType;	//��������
	int m_iBagIndex;			//�ͷ�����Э�̣����͵��Ƕ��ٸ�����
public:
	CSOpenLockBagPacket(int bagType, int bagindex){
		m_iBagType = bagType;
		m_iBagIndex = bagindex;
		m_head[0] = 'Z';
		m_head[1] = 'R';
		m_pn = GetPacketType();
		m_len = GetPacketLength();
	};
	virtual ~CSOpenLockBagPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();

};


#endif