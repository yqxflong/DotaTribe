//Name��SCRoleInfoPacket
//Function��s->c��ɫ��Ϣ
//Written By����ǿ
#ifndef  _PACKET_SCROLEINFO_H_
#define  _PACKET_SCROLEINFO_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/RoleInfoDataHandler.h"
#include <include/mem/DPacket.h>

/*
	��Packetֻ����������Ϣ��������Ϣ������������handler�ֱ���ȡ
*/
class SCRoleInfoPacket : public IPacket
{
public:
	char head_[2];
	int len_;
	unsigned short pn_;
	int serial_;
public:
	SCRoleInfoPacket(){
		//roleInfo_=0;
	};
	virtual ~SCRoleInfoPacket(){};

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
	void _readRoleInfo(cobra_win::DPacket &packet);
	void _readBag(cobra_win::DPacket &packet);
	void _readMissionInfo(cobra_win::DPacket &packet);
	void _readHeroDB(cobra_win::DPacket &packet);
	void _readRoleSouls(cobra_win::DPacket &packet);
	void _readTeamHero(cobra_win::DPacket &packet);
	void _readCheckFunOpen(cobra_win::DPacket &packet);
};

class SCRoleInfoPacketFactory : public IPacketFactory
{
public:
	SCRoleInfoPacketFactory(){};
	virtual ~SCRoleInfoPacketFactory(){};

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

