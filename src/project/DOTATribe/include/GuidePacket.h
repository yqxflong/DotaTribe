//Name��GuidePakcet
//Function��c->s ���
//Written By����ǿ

#ifndef  _PACKECT_GuidePakcet_H_
#define  _PACKECT_GuidePakcet_H_

#include "../include/DotaPacket.h"
#include <iostream>
#include <string>

/************************************************************************/
/*=====================֪ͨ����������������ģ���������=================
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
/*=====================֪ͨ������ÿһ������������������=================
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
/*=====================֪ͨ������������¹��ܿ���=================
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