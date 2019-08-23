//Name��SCRoleInfoPacket
//Function��s->c �������׺󣬽�ɫ��Ϣ
//Written By����ǿ

#ifndef  _DOTATRIBE_SCCHANGESKINPACKET_H_
#define  _DOTATRIBE_SCCHANGESKINPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class SCChangeSkinPacket : public IPacket
{
/*
* ʧ�� ['Z''R'][n][2006][int���к�][int -1][string failureInfo]
* �ɹ� ['Z''R'][n][2006][int���к�][int  1][int count]{[byte type][int attrvalue]}
*/
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;
	int m_resultid;

public:
	SCChangeSkinPacket(){};
	virtual ~SCChangeSkinPacket(){};

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
private:
	inline void _readFailPacket(cobra_win::DPacket &packet);
	inline void _readSuccessPacket(cobra_win::DPacket &packet);
};

class SCChangeSkinPacketFactory : public IPacketFactory
{
public:
	SCChangeSkinPacketFactory(){};
	virtual ~SCChangeSkinPacketFactory(){};

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

private:
	/*
		�߼����ݰ�����
	*/
	static   void  OnSCChangeSkinPacketHandler(SCChangeSkinPacket* pPacket);
};


#endif

