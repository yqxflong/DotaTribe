//Name： RoleInfoDataHandler
//Function：管理player的信息
//Author：Johny

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
角色基础信息
*/
class RoleInfoData
{
public:
	int			 instanceId_;					//玩家ID
	IString		 name_;							//名称
	short        level_;						//级别 
	int			 exp_;							//当前经验
	int			 maxExp_;						//最大经验 
	int			 vitality_;						//体力 <br>
	int			 maxVitality_;					//体力最大值<br>
	int			 jewels_;						//钻石数量 
	int			 money_;						//金钱数量
	int			 vipLevel_;						//vip等级<br>
	int			 btlCapacity_;					//战斗力<br>
	int			 prestige_;						//声望 <br>
	short		 heroLevel_;					//英雄等级
	int		     heroopenIndex2_;				//第二英雄开启等级<br>
	int			 heroopenIndex3_;				//第三英雄开启等级<br>
	UShort       honorLevel_;					//统率力<br>
    int          honorExp_;						//当前气势<br>
	int		     honorMaxExp_;				    //最大气势
	UShort		 mapId_;						//所在地图ID <br>
	UShort		 stageId_;						//所在关卡ID<br>
	int			 pvpRank_;						//竞技场排名 <br>
	short		 guideStep_;					//新手引导第几步<br>
	int          functionGuide_;				//功能引导，共32位
	IByte		 finishTaskCounts_;				//完成任务数目
	short		 unReadEmailCounts_;			//未读邮件
	IByte		 leftFreeRevenueCount_;			//免费征收次数
	IByte		 shopTipsNum_;					//商店提醒	 		

	int			 heroCapaScore_;				//英雄外套战斗力评分
	int          equipCapaScore_;				//装备外套评分
	IByte		 slaveIdentity_;				//奴隶身份 0：自由身 1：奴隶主 2：奴隶
	IByte		 applyforFriendNum_;			//请求好友个数
	IByte		 rewardprompt_;					//奖励公告提示<br>
	IByte		 activityprompt_;				//精彩活动提示<br>
	IByte		 mineralempty_;					//矿坑没有占
	IByte		 freesupplica_;					//有免费祈愿
	IByte		 vipreward_;					//可以领取VIP奖励
	IByte		 bossCanPlay_;					//boss积分可以玩了
	bool		 arena_awardCanReceive_;		//竞技场有奖励可以领取 false:不闪  true:闪
	IByte		 freesummon_;					//召唤有没有免费 0:没有免费  1:有 2：有
	IByte		 hasrefreshshop_;				//1:已经刷新 0：无
	Attribute*   attribute_;					//14种通用属性<br>

	bool  isFastAthleticSpeed;					//战斗是否加速<br>
	int   athleticsSerialID_;					//战斗序列号<br>  to do delete
	bool  bHadNewHeroTips;						//新英雄提示
	int   accumuRechNum;						//累积充值数
	UShort multiExp_;							//经验倍数*100
	UShort multiMoney_;							//金钱倍数*100

	RoleInfoData();
	~RoleInfoData();
public:
	void ResetRoleData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//用于存储玩家状态---->内存中
class PlayerStatus{
public:
	bool _home_more_isopen;		//home场景中，更多的状态
	PlayerStatus(){
		ResetStatus();
	}
	void ResetStatus(){
		_home_more_isopen=false;
	}
};

class RoleInfoDataHandler:public IDataHandler,public cobra_win::Singleton2<RoleInfoDataHandler>{
public:
	PlayerStatus* playerstatus_;		//玩家状态
	RoleInfoData* m_pRIData;			//角色的数据
	bool isLock;						//接收玩家信息之前不接收其他包
	bool isUpdateCapacity_;				//是否更新战力
public:
	RoleInfoDataHandler();
	virtual ~RoleInfoDataHandler();
 
	virtual bool init();
	virtual void onDestroy();
	/*
		更新人物战斗序列号ID 返回更新之后的序列号  若有异常返回-1
	*/
	int  updateRoleAthleticsSerialID();
	/*
	    获得当前人物战斗序列号ID
	*/
	int  getRoleCurAthleticsSerialID();	
	/*
	解析网络数据包
	*/
	void decodePacketData(cobra_win::DPacket & packet);
	
	bool isOpenScene(int limitLv);

	/*
		检查指定功能是否需要开启引导
	*/
	bool CheckNewFuncOPenGuide(int ModuleID);


	/*
		通知服务器完成新功能开启引导
	*/
	void ToServerFinishNewFunc(int ModuleID);


	/*
		请求增加体力
	*/
	void AddTL_Request();

	/*
		目前到满体需要的时间
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