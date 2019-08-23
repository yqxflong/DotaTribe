//Name:MainTaskPacket
//Function: 主线任务包
//Author:方骏
//Date:20131015

#ifndef _DOTATRIBE_MAINTASKPACKET_H_
#define _DOTATRIBE_MAINTASKPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"

/************************************************************************/
/* 进入主线任务                                                  */
/************************************************************************/

//发起任务信息请求
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
 
 //服务器推送任务信息
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

//服务器推送同步客户端任务信息 (任务完成后推送)
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
/* 领取奖励										                        */
/************************************************************************/

//服务器推送任务奖励信息
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
  
//客户端发起领取奖励  (面板上的领取)
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


//单独的任务奖励 领取奖励
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
//数据包工厂

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
/*=====================限时活动列表请求=================
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
/*=====================领取活动奖励=================
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