/*
	服务器与客户端的关系表
*/
#ifndef _GLOBAL_CSMAPTABLE_
#define _GLOBAL_CSMAPTABLE_

#include <map>
#include <include/mem/DPacket.h>
/*
	serial Num
*/
enum{
	kCREATEROLEPACKET=0,
	kCHANGEEQUIPPACKET=1,
	kOFFEQUIPPACKET=2,
	kCHANGESKINPACKET=10,
	kSKINSTRENCONDITION=11,
	kSKINSTRENMAIN=12,
	kBAGSALEOBJECTPACKET = 20,
	kBAGUSEOBJECTPACKET = 21,

};
/*
	商店物品对应的货币
*/
enum
{
	_TYPE_GOLD_ = 0,
	_TYPE_JEWEL_ ,
	_TYPE_PRESTIGE_,
	_TYPE_EXCHANGE_ITEM_,
};

/*
	背包类型
*/
enum{
	BAG_ITEM = 0,		//普通物品
	BAG_EQUIP = 1,		//装备
	BAG_SKIN = 2,		//外套
};

/*
	装备类型
*/
enum{
	kEQUIP_TYPE_MAINWEAPON=0,		//主手
	kEQUIP_TYPE_CLOTH,							//衣服
	kEQUIP_TYPE_HAND,							//手部
	kEQUIP_TYPE_SHOES,							//鞋子
	kEQUIP_TYPE_2ndWEAPON,				//副手
	kEQUIP_TYPE_BALL,								//法球
	kEQUIP_TYPE_HAT,								//头饰
	kEQUIP_TYPE_DECORATION,				//饰品
	kEQUIP_TYPE_EXPBALL,				//经验珠
};

/*
	卡片品质
*/
enum{
	kCARD_1_STAR=0,//白色		====1星
	kCARD_2_STAR,//白色			====2星
	kCARD_3_STAR,//绿色			====3星
	kCARD_4_STAR,//蓝色			====4星
	kCARD_5_STAR,//紫色			====5星
	kCARD_6_STAR,//橙色			====6星
};

/*
	普通物品的种类
*/
enum{
	kOBJECTDRUG = 0,		//药品
	kOBJECTBOX = 1,			//宝箱
	kOBJECTCOMPOSE = 2,		//合成
	kOBJECTRECIPE = 3,		//配方
	kOBJECTOTHER = 4,		//其他
};

enum{
	kBAGOBJECT=0,		//普通物品
	kBAGEQUIP,				//装备
	kBAGSKIN,				//外套
};

enum{
	kPLAYER=0,				//人物信息
	kATTRIBUTES,			//14种通用属性
};

enum{
	kLEVEL=0,			//角色等级 <br>
	kEXP,					//角色经验 <br>
	kVITALITY,			//体力 <br>
	kJEWELS,				//钻石 <br>
    kMONEY,				//金钱 <br>
	kVIPLEVEL,			//VIP等级 <br>
	kBTLCAPACITY,	//战斗力 <br>
	kPRESTIGE,			//声望 <br>
};

//add by fangjun begin， use for 1018
enum {
	kINFOLEVEL,		//等级
	kINFOEXP,		//经验
	kINFOMAXEXP,		//最大经验
	kINFOVITALITY,		//体力
	kINFOJEWELS,		//钻石
	kINFOMONEY,		//金钱
	kINFOBAGGRID,		//包格
	kINFOSKILL,		//技能
	kINFOMAXHP,		//最大血量
	kINFOMAXMP,		//最大蓝量
	kINFOMINATTACK,		//最小攻击
	kINFOMAXATTACK,		//最大攻击
	kINFOSPEED,		//速度
	kINFOSTR,		//力量
	kINFOAGI,		//敏捷
	kINFOINTE,		//智力
	kINFOARMOR,		//护甲
	kINFOEXPOSEARMOR,		//破甲
	kINFOHIT,		//命中
	kINFODODGE,		//闪避
	kINFOCRIT,		//暴击
	kINFOUNCRIT,		//免爆
	kINFOHEROCAPA,			//英雄战斗力
	kINFOHEROCAPASCORE,		//英雄战斗评分
	kINFOEQUIPCAPA,			//装备战斗力
	kINFOEQUIPCAPASCORE,	//装备战斗评分
	kINFOTECHCAPA,			//科技战斗力
	kINFOTECHCAPASCORE,		//科技战斗力评分
	kINFOTRAINCAPA,			//属性训练战斗力
	kINFOTRAINCAPASCORE,	//属性训练战斗力评分
	kINFOSOULCAPA,			//灵魂战斗力
	kINFOSOULCAPASCORE,		//灵魂战斗力评分
	kINFOFRIENDCAPA,		//好友战斗力
	kINFOFRIENDCAPASCORE,		//好友战斗力评分
	kINFOSUMCAPA,			//总战斗力
	kINFOSUMCAPASCORE,			//总战斗力评分
	kINFOVIPLEVEL,			//VIP级别
	kINFOPRESTIGE,			//声望
	kINFOPVPRANK,			//竞技场排名
	kINFOBAGSIZE,			//背包格数
	kINFOROLESKIN,			//身上外套
	kINFOROLEEQUIP,		    //身上装备
	kINFOROLESKILLNOTCH,	//同步技能凹槽
	kINFOQUESTTIPS,			//任务提醒
	kINFOMAILTIPS,			//邮件提醒
	kINFOCOLLECTTIPS,		//剩余免费征收次数
	kINFOSHOPTIPS,			//商店打折提醒
	kINFOSERVANTIDENTITY,	//人物在仆从系统的身份
	kINFOAPPLYFORFRIENDNUM,	//好友申请个数
	kINFOMAINTASKFINISHED,	//主线任务完成
	kInfoHeroLevel,			//英雄等级
	kInfoHeroExp,			//当前英雄经验
	kInfoHeroLeveUpNeedExp,	//升级所需经验
	kInfoHerohonorLevel,	//英雄统计力级别
	kInfoHerohonorExp,		//英雄荣誉值
	kInfoHerohonorLevelUpExp,//升级所需荣誉值
	kINFOAWARDNOTICE,		 //奖励公告
	kINFOACTIVITY,			 //精彩活动
	kInfoNewTask,			 //新任务提醒
	kACCUMURECH,			 //累积充值
	kMERNALEMPTY,		     //矿坑没占
	kFREESUPPLICATION,		 //有免费的祈愿
	kVIPREWARD,				 //vip奖励提示
	kBOSSSCORE,				//boss积分奖励
	kARENAREWARD_HINT,		//竞技奖励提示
	kHEROSOUL,				//获得新战魂		
	kFREESUMMON_HINT,		//召唤是否免费
	kREFRESHSHOP,		//神秘商店是否可以刷新
	kBOSSFREETIME,			//boss积分免费次数
	kHUNTOBJECTLEFTTIME,		//寻宝剩余次数（当使用物品时会同步次数）
	kLASTARENATIME,			 //剩余竞技场挑战次数
	kMULTI_EXP,				//经验倍数
	kMULTI_MONEY,			//金钱倍数
	kUnLockSkill,			//解锁技能
	kONEHEROSTRENGTH,		//单个英雄战力同步
};
//end

enum{
	kSTRENGTH=0,		//力量
	kAGILITY,					//敏捷
	kINTELLIGENCE,		//智力
	kMAXHP,					//最大血量
	kMAXMP,					//最大蓝量
	kSPEED,					//速度
	kMINATTACK,			//最小攻击
	kMAXATTACK,			//最大攻击
	kARMOR,					//护甲
	kEXPOSEARMOR,		//破甲
	kHIT,						//命中
	kDODGE,					//闪避
	kCRIT,						//暴击
	kUNCRIT,					//韧性
	kCOUNT=14,			//总数
};
/*
	14种通用属性
*/
class  Attribute
{
public:
	std::map<int,int> mapPropertyList_;		//该list的index与通用属性枚举一一对应
	~Attribute()
	{
		mapPropertyList_.clear();
	}
	Attribute * __set(Attribute * obj)
	{
		mapPropertyList_.clear();
		std::map<int,int>::iterator it = obj->mapPropertyList_.begin();
		std::map<int,int>::iterator it_e = obj->mapPropertyList_.end();
		for(; it != it_e; ++it)
		{
			mapPropertyList_.insert(std::map<int,int>::value_type(it->first, it->second));
		}
		
		return this;
	}
public:
	void decodePacketData_ChangeEquip(cobra_win::DPacket & packet, int heroindex);
};

//当前支持的活动类型
enum
{
	_ACTIVITY_UNKONW_TYPE_ = 0,			//未知活动类型
	_ACTIVITY_SPRING_TYPE_,				//温泉活动
	_ACTIVITY_FIRSTRECHGIFT_TYPE_,		//首充活动
	_ACTIVITY_LEVELUPREWARD_TYPE_,		//升级活动
	_ACTIVITY_LOGINREWARD_TYPE_,		//登录领奖励
	_ACTIVITY_VIPBAGREWARD_TYPE_,		//VIP包裹领取奖励活动
	_ACTIVITY_EXCHANGEREWARD_TYPE_,		//兑换奖励活动
	_ACTIVITY_GROWUPPLAN_TYPE_,			//成长计划奖励活动
	_ACTIVITY_LIANJIN_TYPE_,			//炼金活动
};

#define NEWBAG_ITEMCOUNT			120
#define NEWBAG_NUMPERPAGE			20
#define NEWBAG_PAGENUM				6

#define BAG_GUIDE_USE_LEVEL						30
#define BAG_GUIDE_BACKOBJECT_LEVEL				40
#define HUNT_GUIDE_LEVEL						30

#define KUANGDONG_DWARVEN_PAGES		8

#define TOWER_FLOOR_TOTAL			400

#endif