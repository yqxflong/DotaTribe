// Name :		FriendCheckPlayerInfoPacket.h
// Function:	������Ϣ����
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
	int id;							//��ɫID<br>
	std::string name;				//����<br>
	unsigned short level;			//����<br>
	int iconId;						//ͷ��ͼ��ID<br>

};

struct  PlayerInfoData
{
	int				id;						
	std::string		name;			//����
	unsigned short	level;			//����
	int				shapeId;		//�������ID
	std::string		shapeName;		//�����������
	IByte			shapeLevel;		//��������Ǽ�
	int				hp;				//Ѫ��
	int				mp;				//����
	int				minAttack;		//��С����
	int				maxAttack;		//��󹥻�
	int				speed;			//�ٶ�
	int				hit;			//����
	int				dodge;			//����
	int				exposeArmor;	//�Ƽ�
	int				armor;			//����
	int				cirt;			//����
	int				uncirt;			//����
	int				btlCapa;		//ս��
	int				strength;		//����
	int				agility;		//����
	int				intelligence;	//����

	std::map<int,BagEquipData*>	equips;		//װ����Ϣ
	std::map<int,SkillItem*>	skills;		//������Ϣ
	
	std::map<int,SoulEquipItem*> soulStatus;
	std::vector<IHeroSoulItem*>	souls;	//ս����Ϣ

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

	int m_iShowedTipsWindow;//���������Ϣ��ҳ������
	bool m_isFriend_Apply;//�Ƿ��Ǵ������б�������

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
		���͸����������������Ϣ
	*/
	void ToServerCheckPlayerInfo(int playerid, int windowType, bool _isFriend_Apply = false);

public:
	void decodeCheckPlayerDataPacket(cobra_win::DPacket & packet);
};
#endif