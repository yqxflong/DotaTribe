#include <cocos2d.h>
#include "../include/PlayerDataMessage.h"
#include "../include/MessagePacketManager.h"


PlayerDataMessage::PlayerDataMessage()
{
	mPlayerID = 0;													//ID
	memset(mPlayerName, 0, sizeof(mPlayerName));					//名字
	mLevel = 0;														//当前等级
	mExperience = 0;												//当前经验
	mStrengh = 0;													//当前体力值
	mTotalGold = 0;													//拥有金币数量
	mTotalDiamond = 0;												//拥有钻石数量
	mPlayVIPLevel = 0;												//玩家VIP等级
	mRecharge = 0;													//累计充值
	mReputation = 0;												//声望值
	mArenaRanking = 0;												//竞技场排名
	mArenaNum = 0;													//当日竞技次数
	mClimbTower = 0;												//当日爬塔次数
	mObtainGem = 0;													//当日挖宝数量
	mObtainLandingRewardNum = 0;									//当日领取登陆奖励次数
	mTotalLandingDays = 0;											//玩家累计登陆天数
	mSkillTalentNum = 0;											//技能天赋点数
	mMaxFightHerioNum = 0;											//出战英雄上限
	mMaxFightHerioTableNum = 0;										//当前英雄列表上限
	mMaxEquipmentTableNum = 0;										//当前装备列表上限
	mMaxPageNum = 0;												//当前页数上限
	mMaxCustomsPass = 0;											//当前最高关卡
	mMaxFriendNum = 0;												//当前好友上限
	mMapId = 0;														//当前选择地图Id
	mThisCustomsPassId = 0;											//当前选择关卡Id
	memset(mRoleHeadIcon_, 0, sizeof(mRoleHeadIcon_));				//当前人物头像
}

PlayerDataMessage::~PlayerDataMessage()
{

}

bool PlayerDataMessage::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	return true;
}


//PlayerDataMessage::PlayerDataMessage()
//{
//
//}
//
//PlayerDataMessage::~PlayerDataMessage()
//{
//
//}
//
//bool PlayerDataMessage::Init()
//{
//	return true;
//}
//
//void PlayerDataMessage::Tick()
//{
//
//}
//
//void PlayerDataMessage::Destroy()
//{
//	Destroy();
//}
//
//void PlayerDataMessage::OnCommandHanlder(int EventTypeID,void * ptr)
//{
//	if(EventTypeID==PALYERROLE_MESSAGEPACKET_TYPE)
//	{
//		CCLOG("OnCommandHanlder click playerdatamanager~~~");
//	}
//}
//
//std::string PlayerDataMessage::GetName()
//{
//	return NULL;
//}
//
//bool PlayerDataMessage::LoadData(char* pBuffer, unsigned int iBufferLen)
//{
//	return true;
//}

void PlayerDataMessage::SetPlayerId(int iPlayerId)
{
	mPlayerID = iPlayerId;
}
int PlayerDataMessage::GetPlayerId()
{
	return mPlayerID;
}
void PlayerDataMessage::SetMapId(int iMapId)
{
	mMapId = iMapId;
}
int PlayerDataMessage::GetMapId()
{
	return mMapId;
}
void PlayerDataMessage::SetThisCustomsPassId(int iCustomPassId)
{
	mThisCustomsPassId = iCustomPassId;
}
int PlayerDataMessage::GetThisCustomsPassId()
{
	return mThisCustomsPassId;
}

void PlayerDataMessage::SetRoleHeadIcon(char* pRoleHeadIcon)
{
	memcpy(mRoleHeadIcon_, pRoleHeadIcon, sizeof(mRoleHeadIcon_));
}

char* PlayerDataMessage::GetRoleHeadIcon()
{
	char *puffer = mRoleHeadIcon_;
	return puffer;
}

