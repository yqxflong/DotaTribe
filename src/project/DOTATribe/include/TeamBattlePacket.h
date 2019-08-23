//Name:TeamBattlePacket
//Function: 组队副本主界面
//Author:李茜
//Date:2013-09-23

#ifndef _DOTATRIBE_TEAMBATTLEPACKET_H_
#define _DOTATRIBE_TEAMBATTLEPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* 获取队伍列表信息                                                     */
/************************************************************************/
class CSTeamBattleGetDataPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
//	int m_fubenId;
public:
	CSTeamBattleGetDataPacket();//参数副本Id
	virtual ~CSTeamBattleGetDataPacket();

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

class SCTeamBattleGetDataPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamBattleGetDataPacket(){};
	virtual ~SCTeamBattleGetDataPacket(){};
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


class SCTeamBattleGetDataPacketFactory : public IPacketFactory
{
public:
	SCTeamBattleGetDataPacketFactory(){};
	virtual ~SCTeamBattleGetDataPacketFactory(){};

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


//*******************************************************************
//c-s 重置进度
class CSTeamBattleResetDataPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_fubenId;
public:
	CSTeamBattleResetDataPacket(unsigned char fubenId);//参数副本Id
	virtual ~CSTeamBattleResetDataPacket();

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

//s-c重置进度
class SCTeamBattleResetDataResultPacket:public IPacket
{
 private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTeamBattleResetDataResultPacket(){};
	virtual ~SCTeamBattleResetDataResultPacket(){};
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

class SCTeamBattleResetDataResultPacketFactory:public IPacketFactory
{
public:
	SCTeamBattleResetDataResultPacketFactory(){};
	~SCTeamBattleResetDataResultPacketFactory(){};

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

//*******************************************************************
//获取副本通关奖励
class CSTeamBattleGateRewardPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_gateId;
	char m_rewardTag;
public:
	CSTeamBattleGateRewardPacket(unsigned char gateId, char rewardTag);//参数副本Id
	virtual ~CSTeamBattleGateRewardPacket();

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

class SCTeamBattleGateRewardResultPacketFactory:public IPacketFactory
{
public:
	SCTeamBattleGateRewardResultPacketFactory(){};
	~SCTeamBattleGateRewardResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};



/************************************************************************/
/* 请求奴隶列表     2153,2154                                           */
/************************************************************************/
class CSAskSlaveListPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAskSlaveListPacket();
	virtual ~CSAskSlaveListPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCAskSlaveListResultPacket:public IPacket
{
 private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAskSlaveListResultPacket(){};
	virtual ~SCAskSlaveListResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCAskSlaveListResultPacketFactory:public IPacketFactory
{
public:
	SCAskSlaveListResultPacketFactory(){};
	~SCAskSlaveListResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 召唤奴隶    2155                                                         */
/************************************************************************/
class CSHireSlavePacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_playerId;
public:
	CSHireSlavePacket(int playerId);
	virtual ~CSHireSlavePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

/************************************************************************/
/* 请求佣兵列表     2157,2158                                                    */
/************************************************************************/
class CSAskMercenaryListPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAskMercenaryListPacket();
	virtual ~CSAskMercenaryListPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCAskMercenaryListResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAskMercenaryListResultPacket(){};
	virtual ~SCAskMercenaryListResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCAskMercenaryListResultPacketFactory:public IPacketFactory
{
public:
	SCAskMercenaryListResultPacketFactory(){};
	~SCAskMercenaryListResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 召唤奴隶    2155                                                         */
/************************************************************************/
class CSHireMercenaryPacket :public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_playerId;
public:
	CSHireMercenaryPacket(int playerId);
	virtual ~CSHireMercenaryPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

#endif
