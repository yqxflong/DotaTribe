//Name��SCRoleInfoPacket
//Function��s->c ����װ���󣬽�ɫ��Ϣ
//Written By����ǿ

#ifndef  _DOTATRIBE_SCCHANGEEQUIPPACKET_H_
#define  _DOTATRIBE_SCCHANGEEQUIPPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class SCChangeEquipPacket : public IPacket
{
/*
* ʧ�� ['Z''R'][n][2004][int���к�][int -1][string failureInfo]
* �ɹ� ['Z''R'][n][2004][int���к�][int  1][int count]{[byte type][int attrvalue]}
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

class SCChangeEquipPacketFactory : public IPacketFactory
{
public:
	SCChangeEquipPacketFactory(){};
	virtual ~SCChangeEquipPacketFactory(){};

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