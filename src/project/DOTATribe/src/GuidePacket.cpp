//Name��GuidePakcet
//Function��c->s ��ɫ�б�����
//Written By����ǿ

#include <cocos2d.h>
#include "../include/GuidePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

/************************************************************************/
/*=====================֪ͨ����������������ģ���������=================
/************************************************************************/
CSGuideModuleFinishPacket::CSGuideModuleFinishPacket(short moduleID)
{
	PushData(moduleID);
}

unsigned  int  CSGuideModuleFinishPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_GUIDE_MODULE_;
}

/************************************************************************/
/*=====================֪ͨ������ÿһ������������������=================
/************************************************************************/
//isSkip===0:����  1������
CSGuideStepPacket::CSGuideStepPacket(short moduleID,short childStep,unsigned char isSkip)
{
	PushData(moduleID);
	PushData(childStep);
	PushData(isSkip);
}

unsigned  int  CSGuideStepPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_NEWGUIDE_STEP_;
}

/************************************************************************/
/*=====================֪ͨ������������¹��ܿ���=================
/************************************************************************/
CSNewFuncOpenFinishPacket::CSNewFuncOpenFinishPacket(int module)
{
	PushData(module);
}

unsigned  int  CSNewFuncOpenFinishPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_NEWFUNCOPEN_FINISH_;
}