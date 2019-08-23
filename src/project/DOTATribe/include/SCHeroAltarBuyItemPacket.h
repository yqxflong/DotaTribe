//Name��SCHeroAltarBuyItemPacket
//Function��s->c �׼��������ظ���Ʒ����
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCHEROALTARBUYITEM_H_
#define  _DOTATRIBE_SCHEROALTARBUYITEM_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCHeroAltarBuyItemPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHeroAltarBuyItemPacket(){};
	virtual ~SCHeroAltarBuyItemPacket(){};

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
	inline void _readServerInfo(cobra_win::DPacket &packet);

};

class SCHeroAltarBuyItemPacketFactory : public IPacketFactory
{
public:
	SCHeroAltarBuyItemPacketFactory(){};
	virtual ~SCHeroAltarBuyItemPacketFactory(){};

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