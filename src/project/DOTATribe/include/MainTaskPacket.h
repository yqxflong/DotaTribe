//Name:MainTaskPacket
//Function: ���������
//Author:����
//Date:20131015

#ifndef _DOTATRIBE_MAINTASKPACKET_H_
#define _DOTATRIBE_MAINTASKPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* ������������                                                  */
/************************************************************************/

//����������Ϣ����
class CSEnterMainTaskPacket : public IPacket
{
public:
	CSEnterMainTaskPacket();
	virtual ~CSEnterMainTaskPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true; };
	virtual  void  Send();
};
 
 //����������������Ϣ
class SCEnterMainTaskResultPacket : public IPacket
{
public:
	SCEnterMainTaskResultPacket(){};
	virtual ~SCEnterMainTaskResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){ return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

//����������ͬ���ͻ���������Ϣ (������ɺ�����)
class  SCTaskFinishReceiptPacket: public IPacket
{
public:
	SCTaskFinishReceiptPacket(){};
	virtual ~SCTaskFinishReceiptPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};
 
/************************************************************************/
/* ��ȡ����										                        */
/************************************************************************/

//������������������Ϣ
class   SCPushTaskFinishRewardPacket: public IPacket
{
public:
	SCPushTaskFinishRewardPacket(){};
	~SCPushTaskFinishRewardPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
protected:
	bool	 isTaskWindowVisiable();
};
  
//�ͻ��˷�����ȡ����  (����ϵ���ȡ)
class  CSGetTaskRewardRequestPacket: public IPacket
{
public:
	CSGetTaskRewardRequestPacket(int taskID);
	~CSGetTaskRewardRequestPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){ return true ;};
	virtual  void  Send();
	int  m_taskID;
};


//������������ ��ȡ����
class  CSGetTaskRewardSinglePacket: public IPacket
{
public:
	CSGetTaskRewardSinglePacket(int taskID);
	~CSGetTaskRewardSinglePacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){ return true; };
	virtual  void  Send();
	int  m_taskID;
};
   

//////////////////////////////////////////////////////////////////////////
//���ݰ�����

class  SCEnterMainTaskResultPacketFactory : public  IPacketFactory
{
public:
	SCEnterMainTaskResultPacketFactory(){};
	virtual ~SCEnterMainTaskResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
	virtual  void  OnPostNotification();
};

class  SCTaskFinishReceiptPacketFactory: public IPacketFactory
{
public:
	SCTaskFinishReceiptPacketFactory(){};
	virtual ~SCTaskFinishReceiptPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

class  SCPushTaskFinishRewardPacketFactory: public IPacketFactory
{
public:
	SCPushTaskFinishRewardPacketFactory(){};
	virtual ~SCPushTaskFinishRewardPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
	void		   OnPostNotification();
};
 
//////////////////////////////////////////////////////////////////////////

  
 

/************************************************************************/
/*=====================��ʱ��б�����=================
/************************************************************************/
class CSLActivityPacket : public DotaPacket
{
public:
	CSLActivityPacket();
	virtual ~CSLActivityPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};

class SCLActivityPacket : public IPacket
{
public:
	SCLActivityPacket(){};
	virtual ~SCLActivityPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCLActivityPacketFactory : public IPacketFactory
{
public:
	SCLActivityPacketFactory(){};
	virtual ~SCLActivityPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/*=====================��ȡ�����=================
/************************************************************************/
class CSLActivityGetAwardPacket : public DotaPacket
{
public:
	CSLActivityGetAwardPacket(int activityID,int rewardID);
	virtual ~CSLActivityGetAwardPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};

class SCLActivityGetAwardPacket : public IPacket
{
public:
	SCLActivityGetAwardPacket(){};
	virtual ~SCLActivityGetAwardPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCLActivityGetAwardPacketFactory : public IPacketFactory
{
public:
	SCLActivityGetAwardPacketFactory(){};
	virtual ~SCLActivityGetAwardPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif