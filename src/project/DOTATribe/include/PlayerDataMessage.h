#ifndef   _DOTATRIBE_PLAYERDATAMESSAGE_H
#define   _DOTATRIBE_PLAYERDATAMESSAGE_H

#include   "../include/MessagePacket.h"
#include   <include/common/Singleton.h>
#include   <cocos2d.h>
using  namespace  cobra_win;

class PlayerDataMessage : public cobra_win::Singleton<PlayerDataMessage>
{
	int			mPlayerID;							//ID
	char		mPlayerName[128];					//����
	int			mLevel;								//��ǰ�ȼ�
	long long	mExperience;						//��ǰ����
	int			mStrengh;							//��ǰ����ֵ
	long long	mTotalGold;							//ӵ�н������
	long long	mTotalDiamond;						//ӵ����ʯ����
	int			mPlayVIPLevel;						//���VIP�ȼ�
	int			mRecharge;							//�ۼƳ�ֵ
	int			mReputation;						//����ֵ
	int			mArenaRanking;						//����������
	int			mArenaNum;							//���վ�������
	int			mClimbTower;						//������������
	int			mObtainGem;							//�����ڱ�����
	int			mObtainLandingRewardNum;			//������ȡ��½��������
	int			mTotalLandingDays;					//����ۼƵ�½����
	int			mSkillTalentNum;					//�����츳����
	int			mMaxFightHerioNum;					//��սӢ������
	int			mMaxFightHerioTableNum;				//��ǰӢ���б�����
	int			mMaxEquipmentTableNum;				//��ǰװ���б�����
	int			mMaxPageNum;						//��ǰҳ������
	int			mMaxCustomsPass;					//��ǰ��߹ؿ�
	int			mMaxFriendNum;						//��ǰ��������

	int         mMapId;								//��ǰѡ���ͼId
	int         mThisCustomsPassId;					//��ǰѡ��ؿ�Id
	char		mRoleHeadIcon_[128];				//��ǰ����ͷ��

public:
	PlayerDataMessage();
	~PlayerDataMessage();

public:
	bool  ParseBuffer(char* pBuffer, unsigned int iLen);

	void  SetPlayerId(int iPlayerId);
	int	  GetPlayerId();
	void  SetMapId(int iMapId);
	int   GetMapId();
	void  SetThisCustomsPassId(int iCustomPassId);
	int   GetThisCustomsPassId();
	void  SetRoleHeadIcon(char* pRoleHeadIcon);
	char* GetRoleHeadIcon();

private:
	friend  class  cobra_win::Singleton<PlayerDataMessage>;
};


//class PlayerDataMessage: public MessagePacket
//{
//public:
//	PlayerDataMessage();
//	~PlayerDataMessage();
//
//	std::map<int, PlayData*> m_PlayerDataMapList;
//
//public:
//	virtual  bool  Init();
//	virtual  void  Tick();
//	virtual  void  Destroy();
//	virtual  void  OnCommandHanlder(int EventTypeID,void * ptr);
//
//	virtual  std::string   GetName();
//	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);
//};

#endif