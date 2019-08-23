//Name：AthleticProcedureDataType
//Function：战斗过程指令类型
//Author:	Johny

#ifndef   _DOTATRIBE_ATHLETICPROCEDUREDATATYPE_H_
#define   _DOTATRIBE_ATHLETICPROCEDUREDATATYPE_H_
 
#include   <cocos2d.h>
#include   <vector>
#include   <string>
#include   <include/mem/DPacket.h> 
#include "../include/ClimbTowerDataHandler.h"

#define   FOR_EACH_ELEMENT_BEGIN(count)   for(size_t index=0;index<count;index++) {
#define   FOR_EACH_ELEMENT_END			  }

   

//战斗过程指令中特殊数值
enum
{
	_ATHLETICPROCEDURE_DEFAULT_VALUE_=-1,	     //战斗过程指令中  默认非法数值
};

//战斗过程指令类型
enum
{
    _ATHLETICSINSTRUCTION_UNKONW_TYPE_=-1,		 //未知战斗过程指令类型
	_ATHLETICSINSTRUCTION_SKILL_TYPE_,			 //技能属性		  战斗过程指令
    _ATHLETICSINSTRUCTION_REMOVE_EFFECT_TYPE_,	 //删除Effect     战斗过程指令
    _ATHLETICSINSTRUCTION_REMOVE_STATE_TYPE_,	 //删除State      战斗过程指令
	_ATHLETICSINSTRUCTION_LOCATION_TYPE_,		 //位置属性       战斗过程指令
	_ATHLETICSINSTRUCTION_RESTORE_HP_TYPE_,		 //回血指令		  
	_ATHLETICSINSTRUCTION_RESTORE_MP_TYPE_,		 //回蓝指令
	_ATHLETICSINSTRUCTION_DAMAGE_HP_TYPE_,		 //失血指令
	_ATHLETICSINSTRUCTION_DAMAGE_MP_TYPE_,		 //失蓝指令
	_ATHLETICSINSTRUCTION_ADD_EFFECT_TYPE_,		 //加特效指令
	_ATHLETICSINSTRUCTION_ADD_STATE_TYPE_,		 //加状态指令
	_ATHLETICSINSTRUCTION_ROLE_BRING_TYPE_,		 //复活指令		  //暂时无此技能过程
 
    _ATHLETICSINSTRUCTION_TYPE_NUMBER_,			 //战斗过程指令类型数目
}; 


//技能附加效果类型
enum
{  
	_ATHLETICS_SKILL_UNKONW_TYPE_=-1,					//未知附加效果类型
	_ATHLETICS_SKILL_SOURCE_HP_DAMAGE_TYPE_,			//攻击者失血
	_ATHLETICS_SKILL_SOURCE_HP_HEAL_TYPE_,				//攻击者回血
	_ATHLETICS_SKILL_SOURCE_MP_DAMAGE_TYPE_,			//攻击者失蓝
	_ATHLETICS_SKILL_SOURCE_MP_HEAL_TYPE_,				//攻击者回蓝
	_ATHLETICS_SKILL_TARGET_HP_DAMAGE_TYPE_,			//目标者失血
	_ATHLETICS_SKILL_TARGET_HP_HEAL_TYPE_,				//目标者回血
	_ATHLETICS_SKILL_TARGET_MP_DAMAGE_TYPE_,			//目标者失蓝
	_ATHLETICS_SKILL_TARGET_MP_HEAL_TYPE_,				//目标者回蓝
	_ATHLETICS_SKILL_CHANAGE_SHAPE_TYPE_,				//变身效果
	_ATHLETICS_SKILL_ADD_STATE_TYPE_,					//添加状态
	_ATHLETICS_SKILL_REMOVE_STATE_TYPE_,				//移除状态
	_ATHLETICS_SKILL_ADD_EFFECT_TYPE_,					//添加特效
	_ATHLETICS_SKILL_REMOVE_EFFECT_TYPE_,				//移除特效
	_ATHLETICS_SKILL_CHANGE_POSITION_TYPE_,				//改变位置
	_ATHLETICS_SKILL_REDUCE_MP_TYPE_,					//技能扣篮
	_ATHLETICS_SKILL_RELIVE_HP_TYPE_,					//复活血量
	_ATHLETICS_SKILL_RELIVE_MP_TYPE_,					//复活蓝量

	_ATHLETICS_SKILL_HIT_NOTE_TYPE_,					//命中注释类型 (命中附加旁注 仅UI显示 非直属服务器通知 故放在最后 切记)
	_ATHLETICS_SKILLATTACH_TYPE_NUMBER_,				//技能附加效果类型数目
};


//技能命中类型
enum
{
    _ATHLETICS_SKILL_UNKONW_ACTION_TYPE_=-1,			//未知技能命中率
	_ATHLETICS_SKILL_HIT_ACTION_TYPE_,					//命中类型
	_ATHLETICS_SKILL_DODGE_ACTION_TYPE_,				//闪避类型
	_ATHLETICS_SKILL_CRIT_ACTION_TYPE_,					//暴击类型
	_ATHLETICS_SKILL_BLOCK_ACTION_TYPE_,				//格挡类型
	_ATHLETICS_SKILL_BATTER2_ACTION_TYPE_,				//二次连击
	_ATHLETICS_SKILL_BATTER3_ACTION_TYPE_,				//三次连击
	_ATHLETICS_SKILL_BATTER4_ACTION_TYPE_,				//四次连击
	_ATHLETICS_SKILL_BATTER5_ACTION_TYPE_,				//五次连击
};

 
//战役类型
enum
{
	_ATHLETICS_UNKONW_BATTLE_TYPE_=-1,					//未知战役类型
	_ATHLETICS_CUSTOMS_BATTLE_TYPE_,					//普通关卡类型
	_ATHLETICS_ARENA_BATTLE_TYPE_,						//竞技战役类型
	_ATHLETICS_CLIMPTOWER_BATTLE_TYPE_,					//爬塔战役类型
	_ATHLETICS_TEAM_BATTLE_TYPE_,						//组队副本战役类型
	_ATHLETICS_SERVANT_BATTLE_TYPE_,					//仆从战役类型
	_ATHLETICS_FRIEND_BATTLE_TYPE_,						//好友切磋战斗类型
	_ATHLETICS_KUANGDONG_BATTLE_TYPE_,					//矿洞战斗
	_ATHLETICS_BOSSSCORE_BATTLE_TYPE_,					//boss积分
	_ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_,				//挑战战魂类型
	_ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_,				//寻宝猎人抢夺类型
};


//角色类型
enum
{
	_ATHLETICS_UNKONW_ROLE_TYPE_=-1,			   	   //未知角色类型
	_ATHLETICS_ROLE_PLAYER_TYPE_,					   //玩家
	_ATHLETICS_ROLE_MONSTER_TYPE_,					   //NPC怪物
};


//战斗结果数据类型
enum
{
	_ATHLETICS_RESULT_UNKONW_TYPE_=-1,				   //未知类型
	_ATHLETICS_RESULT_PEACE_TYPE_,					   //和平类型
	_ATHLETICS_RESULT_WIN_TYPE_,					   //胜利类型
	_ATHLETICS_RESULT_FAIL_TYPE_,					   //失败类型
};

//战斗过程中默认全动作组普通攻击技能
enum
{
	_ATHLETICS_NORMAL_SKILL_ID_=45,					  //普通攻击 (用于归位指令)
};
 
//////////////////////////////////////////////////////////////////////////
/*
预分析角色外形结构
*/
//////////////////////////////////////////////////////////////////////////
typedef struct  roleshapeinfo_tag
{ 
	int  roleID;
	int  roleShapeID;
public:
roleshapeinfo_tag()
{ 
	roleID=_ATHLETICPROCEDURE_DEFAULT_VALUE_;
	roleShapeID=_ATHLETICPROCEDURE_DEFAULT_VALUE_;
}
}RoleShapeInfo,*PRoleShapeInfo;
 
/*
发起挑战的关卡信息
*/
typedef struct premapinfo_tag
{ 
	int  preMapID;											//发起请求MapID
	int  preStageID;										//发起请求的StageID
	bool preIsClear;										//发起请求的关卡是否成功挑战过
public:
	premapinfo_tag()
	{
		preMapID=0;
		preStageID=0;
		preIsClear=false;
	}
}PreMapInfoData,*PPreMapInfoData;

//////////////////////////////////////////////////////////////////////////
/*
公共人物属性结构
*/
//////////////////////////////////////////////////////////////////////////
typedef  struct  commonroleattribute_tag
{
	int   sword;			//战力 武力
	int   hpValue;			//HP数值
	int   mpValue;			//MP数值
	int   minAttack;		//最小攻击值
	int   maxAttack;		//最大攻击值
	int   speed;			//速度
	int   hit;				//命中
	int   dodge;			//闪避
	int   armor;			//护甲
	int   exposeArmor;		//破甲
	int   crit;				//暴击
	int   uncrit;			//韧性
	char  skillCount;		//技能
	std::vector<int> skillIconArray;
public:
	commonroleattribute_tag()
	{
		sword=0;
		hpValue=0;
		mpValue=0;
		minAttack=0;
		maxAttack=0;
		speed=0;
		hit=0;
		dodge=0;
		armor=0;
		exposeArmor=0;
		crit=0;
		uncrit=0;
		skillCount=0;
		skillIconArray.clear();
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);

}CommonRoleAttribute,*PCommonRoleAttribute;

//////////////////////////////////////////////////////////////////////////
/*
玩家角色模型
*/
//////////////////////////////////////////////////////////////////////////
typedef struct  playerrole_tag
{
	int  playerID;								//玩家ID
	std::string playerName;						//玩家昵称
	short playerLevel;							//玩家等级
	int  heroicID;								//玩家当前外套 英雄ID
	std::string heroicName;						//玩家当前外套 英雄名称
	int  shapeID;								//玩家当前外形ID
	int  iconID;								//玩家图标ID
	PCommonRoleAttribute  pCommonRoleAttribute; //玩家属性
public:
	playerrole_tag()
	{
		playerID=0;
		playerName="";
		playerLevel=0;
		heroicID=0;
		heroicName="";
		shapeID=0;
		iconID=0;
		pCommonRoleAttribute=NULL;
	}
	void  destroy()
	{ 
		if(pCommonRoleAttribute!=NULL)
		{
			delete pCommonRoleAttribute;
			pCommonRoleAttribute=NULL;
		}
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);

}PlayerRole,*PPlayerRole;

//////////////////////////////////////////////////////////////////////////
/*
NPC怪物角色模型
*/
//////////////////////////////////////////////////////////////////////////
typedef struct  monsterrole_tag
{
	int			 monsterID;								//怪物ID
	std::string  monsterName;							//怪物名称
	short		 monsterLevel;							//怪物等级
	int			 shapeID;								//怪物外形ID
	int			 iconID;								//怪物头像ID
	PCommonRoleAttribute  pCommonRoleAttribute;
public:
	monsterrole_tag()
	{
		monsterID=0;
		monsterName="";
		monsterLevel=0;
		shapeID=0;
		iconID=0;
	}
	void  destroy()
	{
		if(pCommonRoleAttribute!=NULL)
		{
			delete  pCommonRoleAttribute;
			pCommonRoleAttribute=NULL;
		}
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);

}MonsterRole,*PMonsterRole;

//////////////////////////////////////////////////////////////////////////
/*
 基础人物属性
*/
//////////////////////////////////////////////////////////////////////////
typedef  struct  baseroleinfo_tag
{
   enum
   {
	   _BASE_ROLE_UNKONW_TYPE_=-1,
	   _BASE_ROLE_PLAYER_TYPE_,					
	   _BASE_ROLE_MONSTER_TYPE_,
   };
   char   roleType;				//人物的类型
   void   *  pRoleInfoData;		//人物数据结点   (暂时设计如此，之后会设置基类 用于释放回收) //to do
public:
	baseroleinfo_tag()
	{
	   roleType=0;
	   pRoleInfoData=NULL;
	}
	void  destroy()
	{
		if(pRoleInfoData!=NULL)
		{
			switch(roleType)
			{
			case  _BASE_ROLE_PLAYER_TYPE_:
				{
					PPlayerRole pPlayerRole=(PPlayerRole)pRoleInfoData;
					pPlayerRole->destroy();
					delete pPlayerRole;
					pRoleInfoData=NULL;
					break;
				}
			case  _BASE_ROLE_MONSTER_TYPE_:
				{
					PMonsterRole pMonsterRole=(PMonsterRole)pRoleInfoData;
					pMonsterRole->destroy();
					delete pMonsterRole;
					pRoleInfoData=NULL;
					break;
				}
			default:
				delete pRoleInfoData;
				pRoleInfoData=NULL;
				return ;
			}
		}
		roleType=0; 
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}BaseRoleInfo,*PBaseRoleInfo;


//////////////////////////////////////////////////////////////////////////
// 地图信息
//////////////////////////////////////////////////////////////////////////

typedef struct  athleicsbasemap_tag
{ 
public:
   athleicsbasemap_tag() {}
   virtual ~ athleicsbasemap_tag(){}
   virtual   void  destroy()=0;
   virtual   void  decodePacketData(cobra_win::DPacket & packet)=0;
}AthleticsBaseMap,*PAthleticsBaseMap;
 
 
typedef struct  athleticmapinfo_tag
{
   unsigned char  battleType;		  //战斗类型  (关卡 竞技场 爬塔)
   PAthleticsBaseMap  mapInfoData;    //地图信息数据
public:
	athleticmapinfo_tag()
	{
		battleType=_ATHLETICS_UNKONW_BATTLE_TYPE_;
		mapInfoData=NULL;
	}
	~ athleticmapinfo_tag()
	{ 
		if(mapInfoData)
		{
			mapInfoData->destroy();
			delete mapInfoData;
			mapInfoData=NULL;
		}
	}
	void  destroy()
	{ 
		if(mapInfoData)
		mapInfoData->destroy();
	} 
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsMapInfo,*PAthleticsMapInfo;


//关卡地图信息类
typedef struct  customsmapinfo_tag : public athleicsbasemap_tag
{
	short		  mapID;							//地图ID
	short		  stageID;							//关卡ID
	short	      sceneID;							//场景ID
	std::string   sceneName;						//关卡名称
public:
	customsmapinfo_tag()
	{
		mapID=0;
		stageID=0;
		sceneID=0;
		sceneName="";
	}
	virtual ~ customsmapinfo_tag(){
		CCLOG("customsmapinfo_tag Delete Handler!");
	}
	virtual void  destroy() {}
	virtual void  decodePacketData(cobra_win::DPacket & packet);
}CustomsMapInfo,*PCustomsMapInfo;

//采矿地图信息
typedef struct bossscoremapinfo_tag : public athleicsbasemap_tag
{
	short		  mapID;					//地图ID
	short		  stageID;					//关卡ID
	short		  sceneID;					//场景ID
	std::string   sceneName;				//关卡名称
public:
	bossscoremapinfo_tag()
	{
		mapID=0;
		stageID=0;
		sceneID=0;
		sceneName="";
	}
	virtual ~ bossscoremapinfo_tag(){}
	virtual void  destroy() {}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}BossScoreMapInfo, *PBossScoreMapInfo;

//采矿地图信息
typedef struct miningmapinfo_tag : public athleicsbasemap_tag
{
	short		  mapID;					//地图ID
	short		  stageID;					//关卡ID
	short		  sceneID;					//场景ID
	std::string   sceneName;				//关卡名称
public:
	miningmapinfo_tag()
	{
		mapID=0;
		stageID=0;
		sceneID=0;
		sceneName="";
	}
	virtual ~ miningmapinfo_tag(){}
	virtual void  destroy() {}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}MiningMapInfo, *PMiningMapInfo;

//仆从地图
typedef struct servantmapinfo_tag : public athleicsbasemap_tag
{
	short		  mapID;					//地图ID
	short		  stageID;					//关卡ID
	short		  sceneID;					//场景ID
	std::string   sceneName;				//关卡名称
public:
	servantmapinfo_tag()
	{
		mapID=0;
		stageID=0;
		sceneID=0;
		sceneName="";
	}
	virtual ~ servantmapinfo_tag(){}
	virtual void  destroy() {}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}ServantMapInfo, *PServantMapInfo;

//组队副本地图
typedef struct teammapinfo_tag : public  athleicsbasemap_tag
{
	short			 mapID;					//地图ID
	short			 stageID;				//关卡ID
	short			 sceneID;				//场景ID
    std::string		 sceneName;				//关卡名称
public:
	teammapinfo_tag()
	{
		mapID=0;
		stageID=0;
		sceneID=0;
		sceneName="";
	}
	virtual ~ teammapinfo_tag(){}
	virtual void  destroy() {}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}TeamMapInfo, *PTeamMapInfo;

//爬塔地图
typedef struct towermapinfo_tag : public athleicsbasemap_tag
{
	short sceneID;		  //场景ID
    short mapID;		  //地图ID 
	unsigned char floor;  //当前塔层级
public:
	towermapinfo_tag()
	{
		sceneID = 0;
		mapID=0;
		floor = 1;
	}
	virtual ~ towermapinfo_tag(){}
	virtual void  destroy() {}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}TowerMapInfo, *PTowerMapInfo;
 
//竞技地图
typedef struct arenamapinfo_tag : public  athleicsbasemap_tag
{
	short sceneID; 
public:
	arenamapinfo_tag()
	{	
		sceneID=0;
	}
	virtual ~ arenamapinfo_tag(){}
	virtual void  destroy() {}
    virtual void decodePacketData(cobra_win::DPacket & packet);
}ArenaMapInfo,*PArenaMapInfo;

 


//////////////////////////////////////////////////////////////////////////
//战斗结果数据 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//角色唯一标示结构体
//////////////////////////////////////////////////////////////////////////
typedef  struct  roleuniqedefine_tag
{
   char  unitType;  //类型  
   int   sourceID;  //ID 
public:
	roleuniqedefine_tag()
	{
		unitType=0;
		sourceID=0;
	}
   void decodePacketData(cobra_win::DPacket & packet);
}RoleUniqeDefine,*PRoleUniqeDefine;


//角色胜利情况结果
typedef  struct  roleresultdata_tag
{
	char unitType;
	int  sourceID;
	char winType;
public:
	roleresultdata_tag()
	{
		unitType=0;
		sourceID=0;
		winType=0;
	}
 void decodePacketData(cobra_win::DPacket & packet);
}RoleResultData,*PRoleResultData;
 

//战斗结果数据
typedef  struct   athleticsresultdata_tag
{
	char  firstBattleCount; 
	std::vector<PRoleResultData> firstBattleResultVector;
	char  secondBattleCount; 
	std::vector<PRoleResultData> secondBattleResultVector;

public:
	athleticsresultdata_tag()
	{
      firstBattleCount=0;
	  secondBattleCount=0; 
	  firstBattleResultVector.clear();
	  secondBattleResultVector.clear();
	}
	void  destroy()
	{
		size_t dataCount=firstBattleResultVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount)
		delete firstBattleResultVector.at(index);
		FOR_EACH_ELEMENT_END
		firstBattleResultVector.clear();   
		dataCount=secondBattleResultVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount) 
		delete secondBattleResultVector.at(index);
		FOR_EACH_ELEMENT_END
		secondBattleResultVector.clear();   
	}
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsResultData,*PAthleticsResultData;


 
//////////////////////////////////////////////////////////////////////////
//战前数据包(战队信息)
//////////////////////////////////////////////////////////////////////////

//战斗前数据包
typedef struct	pre_athleticsdatainfo_tag
{ 
	char   firstDequeCount;					//第一组人数
	std::vector<PBaseRoleInfo>  firstdequeRoleVector;
	char   secondDequeCount;				//第二组人数
	std::vector<PBaseRoleInfo>  seconddequeRoleVector;
public:
	pre_athleticsdatainfo_tag()
	{
		firstDequeCount=0;
		secondDequeCount=0;
		firstdequeRoleVector.clear();
		seconddequeRoleVector.clear();
	}
	~pre_athleticsdatainfo_tag()
	{
		destroy();
	}
	void   destroy()
	{
		size_t dataCount=firstdequeRoleVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount)
			firstdequeRoleVector.at(index)->destroy();
			delete firstdequeRoleVector.at(index);
		FOR_EACH_ELEMENT_END
			firstdequeRoleVector.clear();   

		dataCount=seconddequeRoleVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount)
			seconddequeRoleVector.at(index)->destroy();
			delete seconddequeRoleVector.at(index);
		FOR_EACH_ELEMENT_END
			seconddequeRoleVector.clear();   
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);
 
}PreAthleticsDataInfo,*PPreAthleticsData;

 
//////////////////////////////////////////////////////////////////////////
// 战斗过程数据
//////////////////////////////////////////////////////////////////////////

//效果附加类型基结构
typedef  struct  skillattach_base_tag
{
	char   effectType;			//附加效果类型
	short  effectID;			//附加效果ID
	char   targetType;			//附加效果目标类型
	int    targetID;			//附加效果目标ID
public:
	skillattach_base_tag()
	{
		effectType=0;
		effectID=0;
		targetType=0;
		targetID=0;	
	}
	virtual ~ skillattach_base_tag()
	{
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);

}SkillAttach_Base,*PSkillAttach_Base;



//技能属性   战斗过程指令
typedef struct  athleticdata_skill_tag
{
	short   skillItemID;						//战斗过程技能ID
	short   hurtActionID;						//受击动作ID
	char    assailantIDType;					//攻击者的类型
	int     assailantID;						//攻击者ID
	char    targetIDType;						//目标者类型
	int     targetID;						 	//目标者ID
	char    skillActionType;					//命中类型  
	short   counterAttackSkillID;				//反击技能ID   大于0 为 存在反击
	char    effectCount;						//附加效果数目
	std::vector<PSkillAttach_Base> skillAttachEffectVector; 
public:
	athleticdata_skill_tag()
	{
		Init();
		skillAttachEffectVector.clear();
	}
	~athleticdata_skill_tag()
	{
		Destroy();
	}
	void  Init()
	{
		skillItemID=0;
		hurtActionID=0;
		assailantIDType=0;
		assailantID=0;
		targetIDType=0;
		targetID=0;
		skillActionType=0;
		counterAttackSkillID=0;
		effectCount=0;  
	}
    void Destroy()
	{
		Init();  
		size_t dataCount=skillAttachEffectVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount)
		  delete skillAttachEffectVector.at(index);
		  skillAttachEffectVector.at(index)=NULL;
		FOR_EACH_ELEMENT_END
		skillAttachEffectVector.clear();   
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);

}AthleticsData_SKILL,*PAthleticsData_SKILL;

 

//飘 数值 型附加效果结果
typedef  struct  skillattach_numberical_tag: public skillattach_base_tag
{
	int    numbericalValue;			//附加数值			
public:
	skillattach_numberical_tag()
	{
		numbericalValue=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}SkillAttach_Numberical,*PSkillAttach_Numberical; 

 


//变身属性结构(暂时无用)
typedef struct skillattach_changeshape_tag: public skillattach_base_tag
{
	short  shapeId;				   //外形ID
public:
	skillattach_changeshape_tag()
	{
       shapeId=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}SkillAttach_ChangeShape,*PSkillAttach_ChangeShape;


//改变状态属性结构
typedef struct  skillattach_state_tag: public skillattach_base_tag
{
	int  state;					   //状态 
public:
	skillattach_state_tag()
	{ 
		state=0;		
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}SkillAttach_State,*PSkillAttach_State;



//改变Efffect属性结构  已经废弃 等待删除
typedef struct skillattach_buffer_tag: public skillattach_base_tag
{
	short effectID;				   //特效ID
	int   sourceID;				   //目标ID
	 
public:
	skillattach_buffer_tag()
	{
		effectID=0;
		sourceID=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}SkillAttach_Buffer,*PSkillAttach_Buffer;



typedef struct  skillattach_change_position: public skillattach_base_tag
{
   char  position;				   //位置参数  0 自己初始位置  1 对手初始位置
public:
   skillattach_change_position()
   {
		position=0;
   }

public:
	void decodePacketData(cobra_win::DPacket & packet);
}SkillAttach_Change_Position,*PSkillAttach_Change_Position;
 

//////////////////////////////////////////////////////////////////////////
//技能外 数据结构
//////////////////////////////////////////////////////////////////////////


 //buffer数据
typedef struct  athleticdata_buffer_tag
{
	char   sourceType;
	int    sourceID;
	short  effectID;
public:
	athleticdata_buffer_tag()
	{
		sourceType=0;
		sourceID=0;
		effectID=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsData_Buffer,*PAthleticsData_Buffer;


 

//state数据
typedef struct athleticdata_state_tag
{
	char sourceType;
	int  sourceID;
	int  roleState;
public:
	athleticdata_state_tag()
	{ 
		sourceType=0;
		sourceID=0;
		roleState=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsData_State,*PAthleticsData_State;


//改变位置指令
typedef struct athleticdata_location_tag
{
	char sourceType;
	int  sourceID;
	short skillItemID;
	char location;
public:
	athleticdata_location_tag()
	{
		sourceType=0;
		sourceID=0;
		skillItemID=0;
		location=0;
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsData_Location,*PAthleticsData_Location;


//数值数据
typedef struct athleticdata_numberical_tag
{
	char sourceType;
	int  sourceID;
	int  numbericalValue;
public:
	athleticdata_numberical_tag()
	{
		sourceType=0;
		sourceID=0;
		numbericalValue=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticData_Numberical,*PAthleticData_Numberical;
 


//复活指令
typedef struct  athleticdata_role_bring_tag
{
   char sourceType;
   int  sourceID;
   int  hpValue;
   int  mpValue;
public:
	athleticdata_role_bring_tag()
	{
		sourceType=0;
		sourceID=0;
		hpValue=0;
		mpValue=0;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticData_Role_Bring,*PAthleticData_Role_Bring;
  

//战斗过程指令单元数据
typedef struct   athleticsunitdata_tag
{
	short   athleticsIndex;					//战斗过程指令的索引
	char    athleticsType;					//战斗过程指令的类型
	void *  athleticsData;				    //战斗过程指令的数据     (todo 之后会统一除掉 void *  罪恶之极)
public:
	athleticsunitdata_tag()
	{
		athleticsIndex=0;
		athleticsType=_ATHLETICPROCEDURE_DEFAULT_VALUE_;      //之后会统一管理默认值
		athleticsData=NULL;
	}
	void Destroy()
	{
		if(athleticsData!=NULL)
		{
			switch(athleticsType)
			{
			case  _ATHLETICSINSTRUCTION_SKILL_TYPE_:
				{
                    PAthleticsData_SKILL  pAthleticData_Skill=(PAthleticsData_SKILL)athleticsData;
					pAthleticData_Skill->Destroy();
					delete pAthleticData_Skill;
					pAthleticData_Skill=NULL;
					athleticsData=NULL;
					break;
				}
			case  _ATHLETICSINSTRUCTION_LOCATION_TYPE_:
				{
					PAthleticsData_Location pAthleticsData_Location=(PAthleticsData_Location)athleticsData;
					delete pAthleticsData_Location;
					athleticsData=NULL;
					pAthleticsData_Location=NULL;
					break;
				}
			default:
				delete athleticsData;
				athleticsData=NULL;
				break;
			}
		}
		athleticsIndex=0;
		athleticsType=_ATHLETICPROCEDURE_DEFAULT_VALUE_;
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsUnitData,*PAthleticsUnitData;

 

//战斗单轮过程数据
typedef struct   athleticsproceduredata_tag
{
	char     roleType1;
	int      roleID1;
	char     roleType2;
	int      roleID2;
	short    athleticsCount;        //当轮战斗回合数
	std::vector<PAthleticsUnitData>  athleticsDataVector;
public:
	athleticsproceduredata_tag()
	{
		athleticsCount=0;
		roleType1=0;
		roleID1=0;
		roleType2=0;
		roleID2=0;
		athleticsDataVector.clear();
	}
	~athleticsproceduredata_tag()
	{
		Destroy();
	}  
	void Destroy()
	{
		athleticsCount=0;
		size_t dataCount=athleticsDataVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount)
			athleticsDataVector.at(index)->Destroy();
		delete athleticsDataVector.at(index);
		FOR_EACH_ELEMENT_END
			athleticsDataVector.clear();   
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsProcedureData,*PAthleticsProcedureData;


//全战斗过程数据包
typedef struct  athleticsdata
{
	/*
	战斗总轮次数
	*/
	char   totalTurnCount;
	/*
	 轮次战斗信息列表
	*/
	std::vector<PAthleticsProcedureData> totalAthleticsDataVector;
public:
	athleticsdata()
	{
		totalTurnCount=0;
		totalAthleticsDataVector.clear();
	}
	~athleticsdata()
	{
		destroy();
	}
	void  destroy()
	{
		size_t dataCount=totalAthleticsDataVector.size();
		FOR_EACH_ELEMENT_BEGIN(dataCount)
			totalAthleticsDataVector.at(index)->Destroy();
		delete totalAthleticsDataVector.at(index);
		FOR_EACH_ELEMENT_END
			totalAthleticsDataVector.clear();   
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);

}AthleticsProData,*PAthleticsProData;


//////////////////////////////////////////////////////////////////////////
//奖励数据
//////////////////////////////////////////////////////////////////////////
/*
 *	奖励ITEM基类
 */
typedef  struct  rewardbaseitem_tag
{
public:
	rewardbaseitem_tag(){};
	virtual ~rewardbaseitem_tag(){};
	virtual  void  destroy() {};
	virtual  void  decodePacketData(cobra_win::DPacket & packet)=0;
}RewardBaseItem,*PRewardBaseItem;

 /*
 战斗奖励数据结点
 */
typedef  struct  rewardbase_tag
{
	//奖励类型
	enum
	{
		_REWARDBASE_UNKONW_TYPE_=-1,	 //未知类型
		_REWARDBASE_ITEMS_TYPE_,		 //物品
		_REWARDBASE_GLOD_TYPE_,			 //金钱
		_REWARDBASE_PLAYEREXP_TYPE_,	 //玩家经验
		_REWARDBASE_COASTEXP_TYPE_,		 //外套英雄经验
	};
	char  itemType;						 //奖励项类型
	PRewardBaseItem  rewardData;		 //奖励数据
public:
	rewardbase_tag()
	{
		itemType=_REWARDBASE_UNKONW_TYPE_;
		rewardData=NULL;
	}
	~rewardbase_tag()
	{
		destroy();
	}
	void destroy()
	{
		if(rewardData)
		{
			rewardData->destroy();
			delete rewardData;
			rewardData=NULL;
		}
	}

public:
	void decodePacketData(cobra_win::DPacket & packet);
}RewardBaseData,*PRewardBaseData;




//奖励物品
typedef struct rewarditem_tag : public rewardbaseitem_tag
{
	char  catogory;			//分类
	int   templateID;		//模板ID
	std::string  itemName;	//名称
	char  itemQuality;		//品质
	int   itemCount;		//数量
	int   iconID;			//图标
public:
	rewarditem_tag()
	{
		catogory = 0;
		templateID=0;
		itemName="";
		itemQuality=0;
		itemCount=0;
		iconID=0;
	} 
	virtual ~ rewarditem_tag() {}
public:
	virtual void decodePacketData(cobra_win::DPacket & packet);
}RewardItem,*PRewardItem;


//新的奖励物品
typedef struct newrewarditem_tag : public rewardbaseitem_tag
{
	char type;		// 掉落		//0物品 1金钱 2经验 3钻石 4声望 5体力<br>
	int count;
	char catogory;
	int templateId;
	std::string itemName;
	char quality;
	int iconId;
public:
	newrewarditem_tag()
	{
	} 
	virtual ~ newrewarditem_tag() {}
public:
	virtual void decodePacketData(cobra_win::DPacket & packet);
}NewRewardItem,*PNewRewardItem;

//奖励数值 经验 金钱
typedef struct rewardnumber_tag : public rewardbaseitem_tag
{
	int  numberValue;	 
public:
	rewardnumber_tag() { numberValue=0;} 
	virtual ~ rewardnumber_tag(){};
	virtual void decodePacketData(cobra_win::DPacket & packet);
}RewardNumber,*PRewardNumber;


//奖励基类
typedef struct  baserewardInfo_tag
{
public:
	baserewardInfo_tag() {};
	virtual ~baserewardInfo_tag() {};
	virtual  void destroy() {};
	virtual  void decodePacketData(cobra_win::DPacket & packet)=0;
}BaseRewardInfo,*PBaseRewardInfo;
 

/*
关卡类型战役 奖励数据
*/
typedef  struct  customsrewardinfo_tag : public baserewardInfo_tag
{
	char    starLevel;
	int     rewardMoney;
	int     rewardExp;
	int     rewarHeroicExp;
	char    rewardItemCount;
	std::vector<PRewardBaseData>  rewardVec;
public:
	customsrewardinfo_tag()
	{
		starLevel=0;
		rewardMoney=0;
		rewardExp=0;
		rewarHeroicExp=0;
		rewardItemCount=0;
		rewardVec.clear();
	}
	virtual ~ customsrewardinfo_tag() { destroy();}
	virtual void destroy()
	{
		FOR_EACH_ELEMENT_BEGIN(rewardVec.size())
			delete rewardVec.at(index);
		FOR_EACH_ELEMENT_END
			rewardVec.clear();
	}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}CustomsRewardInfo,*PCustomsRewardInfo;



// 竞技奖励
typedef  struct  arenareardinfo_tag : public baserewardInfo_tag
{
	enum
	{
		_Arena_Reward_Peace_Type_,
		_Arena_Reward_Win_Type_,
		_Arena_Reward_Fail_Type_,
	};
	char winType;
    int  rewardPrestige;
	int  rewardMoney;
public:
	arenareardinfo_tag()
	{
	   winType=0;
	   rewardPrestige=0;
	   rewardMoney=0;
	}
	virtual ~ arenareardinfo_tag(){}
	virtual void destroy() {}
    virtual void decodePacketData(cobra_win::DPacket & packet);
}ArenaRewardInfo,*PArenaRewardInfo;
 

typedef struct huntlierenrewardinfo_tag : public baserewardInfo_tag
{
	int rewardMoney;
	int rewardExp;
	unsigned char hasExtra;

	PNewRewardItem pRewardItem;
public:
	huntlierenrewardinfo_tag()
	{
		pRewardItem = NULL;
	}
	virtual ~ huntlierenrewardinfo_tag() { destroy();}
	virtual void destroy()
	{
		if(pRewardItem)
		{
			delete pRewardItem;
			pRewardItem = NULL;
		}
	}
	virtual void decodePacketData(cobra_win::DPacket & packet);

}HuntLieRenRewardInfo, *PHuntLieRenRewardInfo;
 
/*
	矿洞奖励
*/
typedef  struct  miningrewardinfo_tag : public baserewardInfo_tag
{
	int     rewardMoney;
	int     rewardExp; 
	char    rewardItemCount;
	std::vector<PRewardItem>  rewardVec;
public:
	miningrewardinfo_tag()
	{
		rewardMoney=0;
		rewardExp=0;
		rewardItemCount=0;
		rewardVec.clear();
	}
	virtual ~ miningrewardinfo_tag() { destroy();}
	virtual void destroy()
	{
		FOR_EACH_ELEMENT_BEGIN(rewardVec.size())
			delete rewardVec.at(index);
		FOR_EACH_ELEMENT_END
		rewardVec.clear();
	}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}MiningRewardInfo, *PMiningRewardInfo;

/*
	boss积分奖励
*/
typedef  struct  bossscorerewardinfo_tag : public baserewardInfo_tag
{
	int fightScore;
public:
	bossscorerewardinfo_tag()
	{
		fightScore = 0;
	}
	virtual ~ bossscorerewardinfo_tag() { destroy();}
	virtual void destroy()
	{
		fightScore = 0;
	}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}BossScoreRewardInfo, *PBossScoreRewardInfo;

/*
	仆从奖励
*/
typedef  struct  servantrewardinfo_tag : public baserewardInfo_tag
{
	int		shengwang;//声望
public:
	servantrewardinfo_tag()
	{
		shengwang = -1;
	}
	virtual ~ servantrewardinfo_tag() {}
	virtual void destroy(){}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}ServantRewardInfo, *PServantRewardInfo;

/*
	组队副本奖励
*/
typedef  struct  teamrewardinfo_tag : public baserewardInfo_tag
{
	int     rewardMoney;
	int     rewardExp; 
	char    rewardItemCount;
	std::vector<PRewardItem>  rewardVec;
public:
	teamrewardinfo_tag()
	{
		rewardMoney=0;
		rewardExp=0;
		rewardItemCount=0;
		rewardVec.clear();
	}
	virtual ~ teamrewardinfo_tag() { destroy(); }
	virtual void destroy()
	{
		FOR_EACH_ELEMENT_BEGIN(rewardVec.size())
			delete rewardVec.at(index);
		FOR_EACH_ELEMENT_END
		rewardVec.clear();
	} 
	virtual void decodePacketData(cobra_win::DPacket & packet);
}TeamRewardInfo, *PTeamRewardInfo;

/*
	爬塔类型奖励
*/
typedef  struct  towerrewardinfo_tag  : public baserewardInfo_tag
{
	int     rewardMoney;
	int     rewardExp; 
	char    rewardItemCount;
	std::vector<PRewardItem>  rewardVec;
public:
	towerrewardinfo_tag()
	{
		rewardMoney=0;
		rewardExp=0;
		rewardItemCount=0;
		rewardVec.clear();
	}
	virtual ~ towerrewardinfo_tag() { destroy();}
	virtual void destroy()
	{
		FOR_EACH_ELEMENT_BEGIN(rewardVec.size())
			delete rewardVec.at(index);
		FOR_EACH_ELEMENT_END
			rewardVec.clear();
	}
	virtual void decodePacketData(cobra_win::DPacket & packet);
}TowerRewardInfo,*PTowerRewardInfo;
 

/*
战斗奖励数据
*/ 
typedef  struct  athleticsbasereward_tag
{
   enum
   {
	   _BASEREWARD_UNKONW_TYPE_=-1,
	   _BASEREWARD_NOREWARD_TYPE_,
	   _BASEREWARD_REWARD_TYPE_,
   };
   unsigned char    hasReward;
   unsigned char    battleType;
   PBaseRewardInfo  rewardDataInfo;
public:
	athleticsbasereward_tag()
	{
		hasReward=0;
		battleType=0;
		rewardDataInfo=NULL;
	}
	~ athleticsbasereward_tag()
	{
		if(rewardDataInfo)
		{
			rewardDataInfo->destroy();
			delete rewardDataInfo;
			rewardDataInfo=NULL;
		}
	}
	void destroy()
	{
	   if(rewardDataInfo)
	   {
		   rewardDataInfo->destroy();
	   }
	}
	void decodePacketData(cobra_win::DPacket & packet);
}AthleticsBaseReward,*PAthleticsBaseReward;

 
 

#endif