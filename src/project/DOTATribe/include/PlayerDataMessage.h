#ifndef   _DOTATRIBE_PLAYERDATAMESSAGE_H
#define   _DOTATRIBE_PLAYERDATAMESSAGE_H

#include   "../include/MessagePacket.h"
#include   <include/common/Singleton.h>
#include   <cocos2d.h>
using  namespace  cobra_win;

class PlayerDataMessage : public cobra_win::Singleton<PlayerDataMessage>
{
	int			mPlayerID;							//ID
	char		mPlayerName[128];					//名字
	int			mLevel;								//当前等级
	long long	mExperience;						//当前经验
	int			mStrengh;							//当前体力值
	long long	mTotalGold;							//拥有金币数量
	long long	mTotalDiamond;						//拥有钻石数量
	int			mPlayVIPLevel;						//玩家VIP等级
	int			mRecharge;							//累计充值
	int			mReputation;						//声望值
	int			mArenaRanking;						//竞技场排名
	int			mArenaNum;							//当日竞技次数
	int			mClimbTower;						//当日爬塔次数
	int			mObtainGem;							//当日挖宝数量
	int			mObtainLandingRewardNum;			//当日领取登陆奖励次数
	int			mTotalLandingDays;					//玩家累计登陆天数
	int			mSkillTalentNum;					//技能天赋点数
	int			mMaxFightHerioNum;					//出战英雄上限
	int			mMaxFightHerioTableNum;				//当前英雄列表上限
	int			mMaxEquipmentTableNum;				//当前装备列表上限
	int			mMaxPageNum;						//当前页数上限
	int			mMaxCustomsPass;					//当前最高关卡
	int			mMaxFriendNum;						//当前好友上限

	int         mMapId;								//当前选择地图Id
	int         mThisCustomsPassId;					//当前选择关卡Id
	char		mRoleHeadIcon_[128];				//当前人物头像

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