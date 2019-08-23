//Name:TeamSelectPacket
//Function: 组队副本组队界面
//Author:fangjun
//Date:20130923

#ifndef _DOTATRIBE_TEAMSELECTPACKET_H_
#define _DOTATRIBE_TEAMSELECTPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

/************************************************************************/
/* 进入副本                                                     */
/************************************************************************/
class CSTeamSelectEnterPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_gateId;
public:
	CSTeamSelectEnterPacket(int gateId);//参数副本Id
	virtual ~CSTeamSelectEnterPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	/*
		发送字节流
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
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
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
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

};

/************************************************************************/
/* 获得队伍列表                                                                     */
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
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;};

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
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
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

};

/************************************************************************/
/* 创建/加入队伍                                                                     */
/************************************************************************/
class CSTeamSelectJoinTeamPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_teamId;
public:
	CSTeamSelectJoinTeamPacket(int teamId);//参数队伍Id，-1表示创建队伍
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
/* 关闭队伍列表及我的队伍刷新                                           */
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
/* 移除队员，-1解散队伍；-2离开队伍； >0移除                            */
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
/* 被移除，对被移除队员的反馈                                         */
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
/* 改变出战顺序						                                      */
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
/* 开始关卡                                                             */
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
