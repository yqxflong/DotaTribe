//Name�� RoleInfoDataHandler
//Function������player����Ϣ
//Author��Johny

#ifndef   _DOTATRIBE_ROLEINFODATAHANDLER_H
#define   _DOTATRIBE_ROLEINFODATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/CPublicVarReader.h"
#include "../include/IDataHandler.h"
#include "../include/CSMapTable.h"
#include <include/mem/DPacket.h>
#include <string>
#include <map>

/*
��ɫ������Ϣ
*/
class RoleInfoData
{
public:
	int			 instanceId_;					//���ID
	IString		 name_;							//����
	short        level_;						//���� 
	int			 exp_;							//��ǰ����
	int			 maxExp_;						//����� 
	int			 vitality_;						//���� <br>
	int			 maxVitality_;					//�������ֵ<br>
	int			 jewels_;						//��ʯ���� 
	int			 money_;						//��Ǯ����
	int			 vipLevel_;						//vip�ȼ�<br>
	int			 btlCapacity_;					//ս����<br>
	int			 prestige_;						//���� <br>
	short		 heroLevel_;					//Ӣ�۵ȼ�
	int		     heroopenIndex2_;				//�ڶ�Ӣ�ۿ����ȼ�<br>
	int			 heroopenIndex3_;				//����Ӣ�ۿ����ȼ�<br>
	UShort       honorLevel_;					//ͳ����<br>
    int          honorExp_;						//��ǰ����<br>
	int		     honorMaxExp_;				    //�������
	UShort		 mapId_;						//���ڵ�ͼID <br>
	UShort		 stageId_;						//���ڹؿ�ID<br>
	int			 pvpRank_;						//���������� <br>
	short		 guideStep_;					//���������ڼ���<br>
	int          functionGuide_;				//������������32λ
	IByte		 finishTaskCounts_;				//���������Ŀ
	short		 unReadEmailCounts_;			//δ���ʼ�
	IByte		 leftFreeRevenueCount_;			//������մ���
	IByte		 shopTipsNum_;					//�̵�����	 		

	int			 heroCapaScore_;				//Ӣ������ս��������
	int          equipCapaScore_;				//װ����������
	IByte		 slaveIdentity_;				//ū����� 0�������� 1��ū���� 2��ū��
	IByte		 applyforFriendNum_;			//������Ѹ���
	IByte		 rewardprompt_;					//����������ʾ<br>
	IByte		 activityprompt_;				//���ʻ��ʾ<br>
	IByte		 mineralempty_;					//���û��ռ
	IByte		 freesupplica_;					//�������Ը
	IByte		 vipreward_;					//������ȡVIP����
	IByte		 bossCanPlay_;					//boss���ֿ�������
	bool		 arena_awardCanReceive_;		//�������н���������ȡ false:����  true:��
	IByte		 freesummon_;					//�ٻ���û����� 0:û�����  1:�� 2����
	IByte		 hasrefreshshop_;				//1:�Ѿ�ˢ�� 0����
	Attribute*   attribute_;					//14��ͨ������<br>

	bool  isFastAthleticSpeed;					//ս���Ƿ����<br>
	int   athleticsSerialID_;					//ս�����к�<br>  to do delete
	bool  bHadNewHeroTips;						//��Ӣ����ʾ
	int   accumuRechNum;						//�ۻ���ֵ��
	UShort multiExp_;							//���鱶��*100
	UShort multiMoney_;							//��Ǯ����*100

	RoleInfoData();
	~RoleInfoData();
public:
	void ResetRoleData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//���ڴ洢���״̬---->�ڴ���
class PlayerStatus{
public:
	bool _home_more_isopen;		//home�����У������״̬
	PlayerStatus(){
		ResetStatus();
	}
	void ResetStatus(){
		_home_more_isopen=false;
	}
};

class RoleInfoDataHandler:public IDataHandler,public cobra_win::Singleton2<RoleInfoDataHandler>{
public:
	PlayerStatus* playerstatus_;		//���״̬
	RoleInfoData* m_pRIData;			//��ɫ������
	bool isLock;						//���������Ϣ֮ǰ������������
	bool isUpdateCapacity_;				//�Ƿ����ս��
public:
	RoleInfoDataHandler();
	virtual ~RoleInfoDataHandler();
 
	virtual bool init();
	virtual void onDestroy();
	/*
		��������ս�����к�ID ���ظ���֮������к�  �����쳣����-1
	*/
	int  updateRoleAthleticsSerialID();
	/*
	    ��õ�ǰ����ս�����к�ID
	*/
	int  getRoleCurAthleticsSerialID();	
	/*
	�����������ݰ�
	*/
	void decodePacketData(cobra_win::DPacket & packet);
	
	bool isOpenScene(int limitLv);

	/*
		���ָ�������Ƿ���Ҫ��������
	*/
	bool CheckNewFuncOPenGuide(int ModuleID);


	/*
		֪ͨ����������¹��ܿ�������
	*/
	void ToServerFinishNewFunc(int ModuleID);


	/*
		������������
	*/
	void AddTL_Request();

	/*
		Ŀǰ��������Ҫ��ʱ��
	*/
	int GetRestTimeToFullTL();


public:
	static RoleInfoDataHandler * LuaGetInstance(){
		return RoleInfoDataHandler::get_instance2();	
	};
};

#define ROLEINFODATAHANDLER	 RoleInfoDataHandler::get_instance2()











/************************************************************************/
/*                             LeadershipHandler                        */
/************************************************************************/
class LeadershipHandler:public IDataHandler,public cobra_win::Singleton2<LeadershipHandler>{
public:
	unsigned short level_;
	int oldherolv_;
	int newherolv_;
	int oldhp_;
	int addhp_;
	int oldmp_;
	int addmp_;
	int oldminattack_;
	int addminattack_;
	int oldmaxattack_;
	int addmaxattack_;
public:
	LeadershipHandler();
	virtual ~LeadershipHandler(){};
 
	virtual bool init();
	virtual void onDestroy();
	void decodePacketData(cobra_win::DPacket & packet);

	//
	void LeadershipLvup_Quest();
	void HandleAfterResult();

};

/************************************************************************/
/*                             CheckRoleBaseInfoHandler                 */
/************************************************************************/
class CheckRoleBaseInfoHandler:public IDataHandler,public cobra_win::Singleton2<CheckRoleBaseInfoHandler>{
public:
	int m_HeroLv;
	int m_BaseHP;
	int m_BaseMP;
	int m_BaseMinAtk;
	int m_BaseMaxAtk;
public:
	CheckRoleBaseInfoHandler();
	virtual ~CheckRoleBaseInfoHandler(){};

	virtual bool init();
	virtual void onDestroy();
	void decodePacketData(cobra_win::DPacket & packet);

	//
	void ToServerRoleBaseInfo();
	void RoleBaseInfoResult();

};

#define CHECKROLEBASEINFOHANDLER	 CheckRoleBaseInfoHandler::get_instance2()


#endif