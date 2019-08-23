//Name：GuidePakcet
//Function：c->s 完成
//Written By：尹强

#ifndef  _PACKECT_GuidePakcet_H_
#define  _PACKECT_GuidePakcet_H_

#include "../include/DotaPacket.h"
#include <iostream>
#include <string>

/************************************************************************/
/*=====================通知服务器新手引导大模块的完成情况=================
/************************************************************************/
class CSGuideModuleFinishPacket : public DotaPacket
{
public:
	CSGuideModuleFinishPacket(short moduleID);
	virtual ~CSGuideModuleFinishPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};

/************************************************************************/
/*=====================通知服务器每一步新手引导的完成情况=================
/************************************************************************/
class CSGuideStepPacket : public DotaPacket
{
public:
	CSGuideStepPacket(short moduleID,short childStep,unsigned char isSkip);
	virtual ~CSGuideStepPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};

/************************************************************************/
/*=====================通知服务器做完的新功能开启=================
/************************************************************************/
class CSNewFuncOpenFinishPacket : public DotaPacket
{
public:
	CSNewFuncOpenFinishPacket(int module);
	virtual ~CSNewFuncOpenFinishPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};

#endif