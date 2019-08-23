//Name:ClimbTowerPacket
//Function: 爬塔包
//Author:fangjun
//Date:20130826

#ifndef _DOTATRIBE_CLIMBTOWERPACKET_H_
#define _DOTATRIBE_CLIMBTOWERPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/DotaPacket.h"


/************************************************************************/
/* 进入恶魔塔                                                           */
/************************************************************************/
class CSEnterTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSEnterTowerPacket();
	virtual ~CSEnterTowerPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

class SCEnterTowerResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	SCEnterTowerResultPacket();
	virtual ~SCEnterTowerResultPacket();

public:

	virtual  unsigned  int  GetPacketType();

	virtual  unsigned  int  GetPacketLength(){	return 1;	};

public:

	virtual  bool  Read(char* pBuffer, unsigned int iLen);

	virtual  void  Send(){};
};

class SCEnterTowerResultPacketFactory : public IPacketFactory
{
public:
	SCEnterTowerResultPacketFactory();
	virtual ~SCEnterTowerResultPacketFactory();

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
/* 进入塔开始功能                                                                     */
/************************************************************************/
class CSStartTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSStartTowerPacket();
	virtual ~CSStartTowerPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

class SCStartTowerResultPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	SCStartTowerResultPacket(){};
	virtual ~SCStartTowerResultPacket(){};

public:

	virtual  unsigned  int  GetPacketType();

	virtual  unsigned  int  GetPacketLength(){	return 1;	};

public:

	virtual  bool  Read(char* pBuffer, unsigned int iLen);

	virtual  void  Send(){};
};

class SCStartTowerResultPacketFactory : public IPacketFactory
{
public:
	SCStartTowerResultPacketFactory(){};
	virtual ~SCStartTowerResultPacketFactory(){};

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
/* 挑战恶魔关卡                                                         */
/************************************************************************/


class CSChallengeTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;

public:
	CSChallengeTowerPacket(int serialId);
	virtual ~CSChallengeTowerPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};


/************************************************************************/
/* 重置爬塔记录                                                         */
/************************************************************************/

class CSResetTowerPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSResetTowerPacket();
	virtual ~CSResetTowerPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};


class SCResetTowerResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCResetTowerResultPacket();
	virtual ~SCResetTowerResultPacket();
public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

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

class SCResetTowerResultPacketFactory : public IPacketFactory
{
public:
	SCResetTowerResultPacketFactory();
	virtual ~SCResetTowerResultPacketFactory();

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
/* 爬塔排行榜                                                           */
/************************************************************************/
class CSTowerRankPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;

public:
	CSTowerRankPacket();
	virtual ~CSTowerRankPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};


class SCTowerRankResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCTowerRankResultPacket();
	virtual ~SCTowerRankResultPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerRankResultPacketFactory : public IPacketFactory
{
public:
	SCTowerRankResultPacketFactory();
	virtual ~SCTowerRankResultPacketFactory();

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/************************************************************************/
/* 爬塔,钻石重置                                                       */
/************************************************************************/
class CSTowerJewelResetPacket : public IPacket
{
public:
	CSTowerJewelResetPacket();
	virtual ~CSTowerJewelResetPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};


class SCTowerJewelResetResultPacket : public IPacket
{
public:
	SCTowerJewelResetResultPacket(){};
	virtual ~SCTowerJewelResetResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerJewelResetResultPacketFactory : public IPacketFactory
{
public:
	SCTowerJewelResetResultPacketFactory(){};
	virtual ~SCTowerJewelResetResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 爬塔,快速战斗                                                       */
/************************************************************************/
class CSTowerFastFightPacket : public IPacket
{
public:
	CSTowerFastFightPacket();
	virtual ~CSTowerFastFightPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

class SCTowerFastFightResultPacket : public IPacket
{
public:
	SCTowerFastFightResultPacket(){};
	virtual ~SCTowerFastFightResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerFastFightResultPacketFactory : public IPacketFactory
{
public:
	SCTowerFastFightResultPacketFactory(){};
	virtual ~SCTowerFastFightResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 爬塔,奖励列表                                                       */
/************************************************************************/
class CSTowerRewardPacket : public IPacket
{
public:
	CSTowerRewardPacket();
	virtual ~CSTowerRewardPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

class SCTowerRewardResultPacket : public IPacket
{
public:
	SCTowerRewardResultPacket(){};
	virtual ~SCTowerRewardResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerRewardResultPacketFactory : public IPacketFactory
{
public:
	SCTowerRewardResultPacketFactory(){};
	virtual ~SCTowerRewardResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* 爬塔,领取某层奖励                                                       */
/************************************************************************/
class CSTowerGetRewardPacket : public IPacket
{
private:
	char m_iType;
	unsigned short m_iFloor;
public:
	CSTowerGetRewardPacket(char type, unsigned short floor);
	virtual ~CSTowerGetRewardPacket();

public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	virtual  void  Send();
};

class SCTowerGetRewardResultPacket : public IPacket
{
public:
	SCTowerGetRewardResultPacket(){};
	virtual ~SCTowerGetRewardResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){return 0;};
	virtual  unsigned  int  GetPacketLength(){return sizeof(int);}

public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCTowerGetRewardResultPacketFactory : public IPacketFactory
{
public:
	SCTowerGetRewardResultPacketFactory(){};
	virtual ~SCTowerGetRewardResultPacketFactory(){};

public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

/*
	购买爬塔次数
*/
class CSBuyClimbTowerTimesPacket:public DotaPacket
{
public:
	virtual  unsigned  int  GetPacketType();
};

class SCBuyClimbTowerTimesPacketFactory : public IPacketFactory
{
public:
	virtual  unsigned  int  GetPacketType();

public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif
