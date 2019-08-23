////////////////////////////////////////////////////////////////
//Name:	  EquipReCastPacket
//Auchor: 	xiaobo.wu
//Func:	  装备重铸数据包
//Maintainer: 	xiaobo.wu
//date:   2014/04/01
////////////////////////////////////////////////////////////////

#ifndef _DOTATRIBE_EQUIPCASTPACKT_H
#define _DOTATRIBE_EQUIPCASTPACKT_H

#include "../include/DotaPacket.h"
#include "../include/PacketFactory.h"
#include "../include/PacketTyper.h"

/************************************************************************/
/*  请求装备重铸信息                                   */
/************************************************************************/
class CSEquipRecastInfoPacket : public DotaPacket
{
public:
	CSEquipRecastInfoPacket(int equipID);
	virtual ~CSEquipRecastInfoPacket();

public:
	virtual  unsigned  int  GetPacketType() { return _TYPED_PACKET_C2S_EQUIP_RECAST_INFO_CLIENT_; };
};

class SCEquipRecastInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType()  { return _TYPED_PACKET_S2C_EQUIP_RECAST_INFO_SERVER_; };
	virtual  unsigned  int  GetPacketLength(){ return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEquipRecastInfoPacketFactory : public IPacketFactory
{
public:
	SCEquipRecastInfoPacketFactory(){};
	virtual ~SCEquipRecastInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType()  { return _TYPED_PACKET_S2C_EQUIP_RECAST_INFO_SERVER_;};
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen) ;
};

/************************************************************************/
/* 请求装备装备重铸	                                              */
/************************************************************************/
class CSEquipRecastDoPacket : public DotaPacket
{
public:
	CSEquipRecastDoPacket(int equipID);
	virtual ~CSEquipRecastDoPacket();

public:
	virtual  unsigned  int  GetPacketType() { return _TYPED_PACKET_C2S_EQUIP_RECAST_DO_CLIENT_;};
};


/************************************************************************/
/* 服务器返回装备重铸成功                                 */
/************************************************************************/
 

class SCEquipRecastDoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
public:
	virtual  unsigned  int  GetPacketType(){ return  _TYPED_PACKET_S2C_EQUIP_RECAST_DO_SERVER_;};
	virtual  unsigned  int  GetPacketLength(){	return 1; };
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCEquipRecastDoPacketFactory : public IPacketFactory
{
public:
	SCEquipRecastDoPacketFactory(){};
	virtual ~SCEquipRecastDoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType() { return  _TYPED_PACKET_S2C_EQUIP_RECAST_DO_SERVER_; };
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

  

#endif
