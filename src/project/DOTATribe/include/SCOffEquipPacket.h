//Name��SCOffEquipPacket
//Function��s->c ж��װ���󣬽�ɫ��Ϣ
//Written By����ǿ

#ifndef  _DOTATRIBE_SCOFFEQUIPPACKET_H_
#define  _DOTATRIBE_SCOFFEQUIPPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class SCOffEquipPacket : public IPacket
{
/*
* ʧ�� ['Z''R'][n][2008][int���к�][int -1][string failureInfo]
* �ɹ� ['Z''R'][n][2008][int���к�][int  1][byte count]{[byte type][int attrvalue]} 
*/
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;

public:
	SCOffEquipPacket(){};
	virtual ~SCOffEquipPacket(){};

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
};

class SCOffEquipPacketFactory : public IPacketFactory
{
public:
	SCOffEquipPacketFactory(){};
	virtual ~SCOffEquipPacketFactory(){};

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

