// Name :		FriendCheckPlayerInfoPacket.h
// Function:	好友信息数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_FRIENDDATAHANDLER_H
#define   _DOTATRIBE_FRIENDDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleSkillsDataHandler.h"
#include "../include/RoleSoulsDataHandler.h"


struct  FriendInfoData
{
	int id;							//角色ID<br>
	std::string name;				//名称<br>
	unsigned short level;			//级别<br>
	int iconId;						//头像图标ID<br>

};

struct  PlayerInfoData
{
	int				id;						
	std::string		name;			//名字
	unsigned short	level;			//级别
	int				shapeId;		//玩家形象ID
	std::string		shapeName;		//玩家形象名称
	IByte			shapeLevel;		//玩家形象星级
	int				hp;				//血量
	int				mp;				//蓝量
	int				minAttack;		//最小攻击
	int				maxAttack;		//最大攻击
	int				speed;			//速度
	int				hit;			//命中
	int				dodge;			//闪避
	int				exposeArmor;	//破甲
	int				armor;			//护甲
	int				cirt;			//暴击
	int				uncirt;			//韧性
	int				btlCapa;		//战力
	int				strength;		//力量
	int				agility;		//敏捷
	int				intelligence;	//智力

	std::map<int,BagEquipData*>	equips;		//装备信息
	std::map<int,SkillItem*>	skills;		//技能信息
	
	std::map<int,SoulEquipItem*> soulStatus;
	std::vector<IHeroSoulItem*>	souls;	//战魂信息

};

class FriendDataHandler:public IDataHandler,public cobra_win::Singleton2<FriendDataHandler>{
public:
	unsigned short m_FriendNum;
	unsigned short m_MaxFriendNum;
	std::vector<FriendInfoData*> MyFriendList;
	std::vector<FriendInfoData*> ApplyList;
	std::vector<FriendInfoData*> NominateList;
		
	PlayerInfoData m_SelectPlayerInfo;
	FriendInfoData m_FindPlayer;

	int m_iShowedTipsWindow;//请求好友信息的页面类型
	bool m_isFriend_Apply;//是否是从申请列表界面过来

	bool m_IsFindPlayer;
	void DeleteFriend(int id);
	void AddFriend(int id);
	void AgreeSingle(int id);
	void IgnoreSingle(int id);
	void AgreeAll();
	void IgnoreAll();

	void ResetSelectPlayerInfo();
public:
	FriendDataHandler();
	virtual ~FriendDataHandler();
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();

	/*
		发送给服务器请求玩家信息
	*/
	void ToServerCheckPlayerInfo(int playerid, int windowType, bool _isFriend_Apply = false);

public:
	void decodeCheckPlayerDataPacket(cobra_win::DPacket & packet);
};
#endif