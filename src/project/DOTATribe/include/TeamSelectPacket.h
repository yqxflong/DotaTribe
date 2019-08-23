//Name:TeamSelectPacket
//Function: ��Ӹ�����ӽ���
//Author:fangjun
//Date:20130923

#ifndef _DOTATRIBE_TEAMSELECTPACKET_H_
#define _DOTATRIBE_TEAMSELECTPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

/************************************************************************/
/* ���븱��                                                     */
/************************************************************************/
class CSTeamSelectEnterPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_gateId;
public:
	CSTeamSelectEnterPacket(int gateId);//��������Id
	virtual ~CSTeamSelectEnterPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};
class SCTeamSelectEnterResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamSelectEnterResultPacket(){};
	virtual ~SCTeamSelectEnterResultPacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

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

class SCTeamSelectEnterResultPacketFactory : public IPacketFactory
{
public:
	SCTeamSelectEnterResultPacketFactory(){};
	virtual ~SCTeamSelectEnterResultPacketFactory(){};

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

/************************************************************************/
/* ��ö����б�                                                                     */
/************************************************************************/
class SCTeamSelectGetListPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamSelectGetListPacket(){};
	virtual ~SCTeamSelectGetListPacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

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

class SCTeamSelectGetListPacketFactory : public IPacketFactory
{
public:
	SCTeamSelectGetListPacketFactory(){};
	virtual ~SCTeamSelectGetListPacketFactory(){};

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

/************************************************************************/
/* ����/�������                                                                     */
/************************************************************************/
class CSTeamSelectJoinTeamPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_teamId;
public:
	CSTeamSelectJoinTeamPacket(int teamId);//��������Id��-1��ʾ��������
	virtual ~CSTeamSelectJoinTeamPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};
class SCTeamSelectJoinTeamResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamSelectJoinTeamResultPacket(){};
	virtual ~SCTeamSelectJoinTeamResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTeamSelectJoinTeamResultPacketFactory : public IPacketFactory
{
public:
	SCTeamSelectJoinTeamResultPacketFactory(){};
	virtual ~SCTeamSelectJoinTeamResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

};

/************************************************************************/
/* �رն����б��ҵĶ���ˢ��                                           */
/************************************************************************/
class CSTeamSelectStopTeamSyncPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSTeamSelectStopTeamSyncPacket();
	virtual ~CSTeamSelectStopTeamSyncPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

/************************************************************************/
/* �Ƴ���Ա��-1��ɢ���飻-2�뿪���飻 >0�Ƴ�                            */
/************************************************************************/
class CSTeamSelectRemoveMemberPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_playerId;
public:
	CSTeamSelectRemoveMemberPacket(int playerId);
	virtual ~CSTeamSelectRemoveMemberPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;};
	virtual  void  Send();
};

/************************************************************************/
/* ���Ƴ����Ա��Ƴ���Ա�ķ���                                         */
/************************************************************************/
class SCTeamSelectBeRemovedPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamSelectBeRemovedPacket(){};
	virtual ~SCTeamSelectBeRemovedPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTeamSelectBeRemovedPacketFactory : public IPacketFactory
{
public:
	SCTeamSelectBeRemovedPacketFactory(){};
	virtual ~SCTeamSelectBeRemovedPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

};

/************************************************************************/
/* �ı��ս˳��						                                      */
/************************************************************************/
class CSTeamSelectReorderTeamPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char count;
	std::vector<int> & m_playerIdVector;
public:
	CSTeamSelectReorderTeamPacket(std::vector<int> & vec);
	virtual ~CSTeamSelectReorderTeamPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;};
	virtual  void  Send();
};

/************************************************************************/
/* ��ʼ�ؿ�                                                             */
/************************************************************************/
class CSTeamSelecStartStagePacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;
public:
	CSTeamSelecStartStagePacket(int serialId);
	virtual ~CSTeamSelecStartStagePacket(){};

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;};
	virtual  void  Send();
};



#endif
