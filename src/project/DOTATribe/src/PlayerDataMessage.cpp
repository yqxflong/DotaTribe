#include <cocos2d.h>
#include "../include/PlayerDataMessage.h"
#include "../include/MessagePacketManager.h"


PlayerDataMessage::PlayerDataMessage()
{
	mPlayerID = 0;													//ID
	memset(mPlayerName, 0, sizeof(mPlayerName));					//����
	mLevel = 0;														//��ǰ�ȼ�
	mExperience = 0;												//��ǰ����
	mStrengh = 0;													//��ǰ����ֵ
	mTotalGold = 0;													//ӵ�н������
	mTotalDiamond = 0;												//ӵ����ʯ����
	mPlayVIPLevel = 0;												//���VIP�ȼ�
	mRecharge = 0;													//�ۼƳ�ֵ
	mReputation = 0;												//����ֵ
	mArenaRanking = 0;												//����������
	mArenaNum = 0;													//���վ�������
	mClimbTower = 0;												//������������
	mObtainGem = 0;													//�����ڱ�����
	mObtainLandingRewardNum = 0;									//������ȡ��½��������
	mTotalLandingDays = 0;											//����ۼƵ�½����
	mSkillTalentNum = 0;											//�����츳����
	mMaxFightHerioNum = 0;											//��սӢ������
	mMaxFightHerioTableNum = 0;										//��ǰӢ���б�����
	mMaxEquipmentTableNum = 0;										//��ǰװ���б�����
	mMaxPageNum = 0;												//��ǰҳ������
	mMaxCustomsPass = 0;											//��ǰ��߹ؿ�
	mMaxFriendNum = 0;												//��ǰ��������
	mMapId = 0;														//��ǰѡ���ͼId
	mThisCustomsPassId = 0;											//��ǰѡ��ؿ�Id
	memset(mRoleHeadIcon_, 0, sizeof(mRoleHeadIcon_));				//��ǰ����ͷ��
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

