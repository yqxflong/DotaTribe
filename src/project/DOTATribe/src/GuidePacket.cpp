//Name：GuidePakcet
//Function：c->s 角色列表请求
//Written By：尹强

#include <cocos2d.h>
#include "../include/GuidePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

/************************************************************************/
/*=====================通知服务器新手引导大模块的完成情况=================
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
/*=====================通知服务器每一步新手引导的完成情况=================
/************************************************************************/
//isSkip===0:正常  1：跳过
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
/*=====================通知服务器做完的新功能开启=================
/************************************************************************/
CSNewFuncOpenFinishPacket::CSNewFuncOpenFinishPacket(int module)
{
	PushData(module);
}

unsigned  int  CSNewFuncOpenFinishPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_NEWFUNCOPEN_FINISH_;
}