//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//
//  Note: Manage file name , fontsize ,fontname used by program

#ifndef __PUBLIC__CPUBLICVARREADER__
#define __PUBLIC__CPUBLICVARREADER__

#include <cocos2d.h>
#include "../include/ResourceIDDataManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DotaGameConfig.h"
#include "../include/SysLangDataManager.h"
#include "../include/ClientConstDataManager.h"
#include "../include/VariableSystem.h"
#include "../include/AthleticProcedureDataType.h"
#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>



using namespace cobra_win;
 

//公共简化数据定义 (为了配合lua数据绑定改为define)
#define  IByte    unsigned char
#define  UShort   unsigned short
#define  IString  std::string

//typedef   unsigned char    IByte ;
//typedef   unsigned short   UShort;
//typedef   std::string      IString;
 
//公共构造析构函数
//////////////////////////////////////////////////////////////////////////
//默认构造析构函数
#define  default_construct_destroy(className) \
public:  className(void); \
public:	 ~className();

//////////////////////////////////////////////////////////////////////////
//默认构造虚拟析构函数
#define  default_construct_vdestroy(className) \
public:   className(); \
public:   virtual ~className(); 

 
//公共内成员访问模板
//////////////////////////////////////////////////////////////////////////
//property_unit_rw
#define  property_unit_rw(type,variableName,functionName) \
protected:  type variableName; \
public: type get##functionName(void) { return variableName;} \
public: void set##functionName(type  var)  { variableName=var; } 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//property_unit_rwc 
#define  property_unit_rwc(type,variableName,functionName) \
protected:  type variableName; \
public: type & get##functionName(void) { return variableName;} \
public: void set##functionName(type & var)  { variableName=var; } 
//////////////////////////////////////////////////////////////////////////

 

//////////////////////////////////////////////////////////////////////////
//property_unit_ronly
#define  property_unit_ronly(type,variableName,functionName) \
protected:  type variableName; \
public: type get##functionName(void) { return variableName;}  
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//property_unit_ronlyc
#define  property_unit_ronlyc(type,variableName,functionName) \
protected:  type variableName; \
public: type & get##functionName(void) { return variableName;}  
//////////////////////////////////////////////////////////////////////////


//公共循环模式

#define  COMMON_BEIGIN_ARRAY(type,count)  for(type index=0;index<count;index++) {
#define  COMMON_END_ARRAY				  }


#define  COMMON_BEGIN_VECTOR(count)		  for(size_t index=0;index<count;index++) {
#define  COMMON_END_VECROR				  }

 
//公共迭代器式遍历模板
#define  COMMON_BEGIN_ITRATOR(ireatorType,contain)		 \
			ireatorType::iterator  iter=contain.begin(); \
			while(iter!=contain.end()) \
			{  

#define  COMMON_END_ITRATOR   \
			++iter;\
			}
 

//富文本格式  
#define _RICH_TEXT_TYPE_ "<a type=\'text\' fontsize=\'%d\' fontname=\'%s\' fontcolor=\'%s\' text=\'%s\'></a>"

//Different Resolution
#define SCALEFIT(_N_)			_N_


/************************************************/
/********************宏开关*********************/
/***********************************************/
#if 0
#define ENABLE_GUIDESYSTEM_NEWFUNC_GET1stBOX_DEBUG			//启动新功能开启之领取第一关的盒子的开发者版
#endif

/*
	颜色值管理
*/
//! Purple Color (165,154,235) 
static const cocos2d::ccColor3B ccPURPLE={165,154,235};//紫色
static const cocos2d::ccColor3B ccBROWN={116,33,1};//
static const cocos2d::ccColor3B ccLIGHTBLUE={56,201,255};//浅蓝
static const cocos2d::ccColor3B ccLIGHTYELLOW={255,216,0};
static const cocos2d::ccColor3B ccLIGHTORGANE={255,136,56};

static const cocos2d::ccColor3B color_BagNormal = {255, 255, 255};
static const cocos2d::ccColor3B color_BagRed = {255, 0, 0};

static const cocos2d::ccColor3B color_BagGrap = {100, 100, 100};


//微秒转秒单位 
#define   Microsecond_TIME_UNIT				1000000.0f    
//毫秒转秒单位
#define   Millisecond_TIME_UNIT				1000.0f     
 
/*
	游戏中人物类型
*/
enum{
	UNIT_PLAYER = 0,
	UNIT_MONSTER = 1,
	UNIT_NPC = 2,
	UNIT_SLAVE = 3,
	UNIT_SOILDER = 4,
	//0玩家，3奴隶，4佣兵

};

/*
	每个用户奴隶最大数
*/
#define USER_MAX_SLAVE 3


/*
等级未到提示
*/
#define _COMMON_LESS_LEVEL_TIPS_  7000

/*
	仆从系统中人物身份
*/
enum
{
	SERVANT_ID_FREE = 0,		//自由身
	SERVANT_ID_MASTER = 1,		//奴隶主
	SERVANT_ID_SLAVE = 2,		//奴隶
};

/*
	触摸优先级表
*/
enum{
	kPRIORITYLOW=0,
	kPRIORITYLOW1=-10,
	kPRIORITYLOW2=-20,
	kPRIORITYLOW3=-40,
	kPRIORITYLOW4=-60,
	kPRIORITYLOW5=-80,		//任务等
	kPRIORITYLOWER=-100,	//升级等
	kPRIORITYMID=-138,
	kPRIORITYHIGH=-150,
	kPRIORITYHIGHER=-160,
	kPRIORITYHIGHER2=-170,
	kPRIORITYHIGHER3=-180,			//技能界面专用  
	kPRIORITYHIGHER4=-190,			//装备掉落提示界面
	kPRIORITYGUIDEWINDOW=-200,		//新手引导的优先级
	kPRIORITYNOTICEBOX=-230,			//公告弹窗优先级
	kPRIORITYMESSAGEBOX=-250,		//消息弹窗的优先级
	kPRIORITY_FORBID_ALL_TOUCHES=-500,	//禁止一切响应优先级
};

/*
	服务器对应的文字
*/
enum{
	sNEWSERVER = 1,
	sFIERY,
	sSAFEGUARDING,
	sNOTOPEN,
	sCLOSEREGISTER,
};

//奖励type枚举
enum{
	kDT_AWARD_OBJECT=0,
	kDT_AWARD_MONEY,
	kDT_AWARD_EXP,
	kDT_AWARD_DIAMOND,
	kDT_AWARD_PRESTIGE,
	kDT_AWARD_POWER,
};

//奖励(非物品)文案
enum
{
	kDT_MONEY_TID = 4021,
	kDT_EXP_TID = 4022,
	kDT_DIAMOND_TID = 4023,
	kDT_PRESTIGE_TID = 4024,
	kDT_POWER_TID = 4025,
};

//数值quality枚举
enum
{
	_GOLD_QUALITY_RESID_=100,			//金币
	_EXP_QUALITY_RESID_=101,			//经验
	_DIAMOND_QUALITY_RESID_=102,		//钻石
	_PREGIST_QUALITY_RESID_=103,		//声望
	_POWER_QUALITY_RESID_=104,			//体力
};

//数值iconid枚举
enum
{
	_GOLD_ICON_RESID_=150,			//金币
	_EXP_ICON_RESID_=152,			//经验
	_DIAMOND_ICON_RESID_=149,		//钻石
	_PREGIST_ICON_RESID_=560,		//声望
	_POWER_ICON_RESID_=151,			//体力
};




//英雄类型
enum
{
	_HERO_TYPE_POWRD_TYPE_,			//力量
	_HERO_TYPE_QUICK_TYPE_,			//敏捷
	_HERO_TYPE_INTERLIGENCE_TYPE_,	//智力
};


//图片路径
#define PIC_TIPSBOARD			"resource/image/newtips/wptips_diban.png"

//灰层的透明度
#define ALPHA_GRAYLAYER			125

/*
	商店货币路径路径
*/
#define PIC_ICONGOLD_TIPS			"resource/image/newpublic/jinbi_icon_b.png"
#define PIC_ICONDIAMOND_TIPS		"resource/image/newpublic/zs_icon_b.png"
#define PIC_ICONPRESTIGE_TIPS		"resource/image/newpublic/sw_icon_b.png"
#define PIC_ICONLONGXUE_TIPS		"resource/image/newpublic/hzs_icon_b.png"

/*
	挖矿遭遇宝箱图片
*/
#define PIC_HUNT_BOX_				"resource/image/kuangdong/baoxiang.png"
#define PIC_HUNT_BOX_OPEN			"resource/image/kuangdong/baoxiang_dakai.png"

/*
	邮件界面资源图片路径
*/
//邮件关闭图片
#define EMAIL_CLOSE_ICON			"resource/image/newemail/weikai.png"
//邮件打开图片
#define EMAIL_POENED_ICON			"resource/image/newemail/yichai.png"

//空白图
#define PIC_IMAGE_NULL_			"resource/image/newpublic/null.png"

//shader 纵向
#define cc_shader_blur_vertical		"resource/shader/shader_blur_vertical.fsh"
//shader 横向
#define cc_shader_blur_horizontal		"resource/shader/shader_blur_horizontal.fsh"

class varConfig{
public:
	/*
		获取中文数字
	*/
	static std::string getBigNumBy(unsigned int num){
		assert(num<=10);
		std::string ss=SysLangDataManager::get_instance2()->GetSysLangById(750+num);
		return ss;
	}
	/*
		卡牌底色
	*/
	static std::string getCardBGFilePath(unsigned char quality){
		std::string filepath="";
		switch(quality)
		{
		case 1:
			filepath = "resource/image/newpublic/c_white.png";
			break;
		case 2:
			filepath = "resource/image/newpublic/c_green.png";
			break;
		case 3:
			filepath = "resource/image/newpublic/c_blue.png";
			break;
		case 4:
			filepath = "resource/image/newpublic/c_purple.png";
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			filepath = "resource/image/newpublic/c_orange.png";
			break;
//=======20以后为数值的quality=====
		case 100:	//金钱
			filepath = "resource/image/newpublic/c_purple.png";
			break;
		case 101:	//经验
			filepath = "resource/image/newpublic/c_purple.png";
			break;
		case 102:	//钻石
			filepath = "resource/image/newpublic/c_purple.png";
			break;
		case 103:	//声望
			filepath = "resource/image/newpublic/c_purple.png";
			break;
		case 104:	//体力
			filepath = "resource/image/newpublic/c_purple.png";
			break;
		default:
			filepath = "resource/image/newpublic/c_normal.png";
			break;
		}
		return filepath;
	}

	/*
		卡牌蒙版
	*/
	static std::string getCardMaskFilePath(unsigned char quality){
		std::string filepath="";
		switch(quality)
		{
		case 1:
			filepath = "resource/image/newpublic/c_white_mask.png";
			break;
		case 2:
			filepath = "resource/image/newpublic/c_green_mask.png";
			break;
		case 3:
			filepath = "resource/image/newpublic/c_blue_mask.png";
			break;
		case 4:
			filepath = "resource/image/newpublic/c_purple_mask.png";
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			filepath = "resource/image/newpublic/c_orange_mask.png";
			break;
//=======20以后为数值的quality=====
		case 100:	//金钱
			filepath = "resource/image/newpublic/c_purple_mask.png";
			break;
		case 101:	//经验
			filepath = "resource/image/newpublic/c_purple_mask.png";
			break;
		case 102:	//钻石
			filepath = "resource/image/newpublic/c_purple_mask.png";
			break;
		case 103:	//声望
			filepath = "resource/image/newpublic/c_purple_mask.png";
			break;
		case 104:	//体力
			filepath = "resource/image/newpublic/c_purple_mask.png";
			break;
		default:
			filepath = "resource/image/newpublic/c_normal_mask.png";
			break;
		}
		return filepath;
	}

	/*
		获得普通的背景
	*/
	static std::string getCardNormalBGFilePath(){
		return "resource/image/newpublic/c_normal.png";
	}
	/*
		获得普通的蒙版
	*/
	static std::string getCardNormalMaskFilePath(){
		return "resource/image/newpublic/c_normal_mask.png";
	}

	/*获取大头像框背景*/
	static std::string getLargeHeroBGFilePath(){
		return "resource/image/newpublic/datouxiangkuang.png";
	}

	/*
	获取大头像框蒙板
	*/
	static std::string getLargeHeroMaskFilePath(){
	    return "resource/image/newpublic/datouxiangkuang_mask.png";
	}
	/*
	获取头像品质遮罩
	*/
	static std::string getHeroQualityMaskFilePath(int heroQuality)
	{
		std::string  filepath ="" ;
		switch(heroQuality)
		{
		case 6:
			filepath = "resource/image/newpublic/s.png";
			break;
		case 7:
			filepath = "resource/image/newpublic/ss.png";
			break;
		case 8:
			filepath = "resource/image/newpublic/sss.png";
			break;
		default:
			break;
		}
		return filepath;
	}

	 
	static std::vector<int> getSubInt(int num){
		std::vector<int> numberVector; 
		if(num==0) 
		{ 
			numberVector.push_back(0); 
		} 
		else 
		{ 
			while(num!=0) 
			{ 
				numberVector.push_back(num%10); 
				num/=10; 
			} 
		}   
		size_t  numberCharSize=numberVector.size(); 
		std::vector<int> numberVecor2; 
		for(int numberIndex=numberCharSize-1;numberIndex>=0;numberIndex--) 
		{ 
			numberVecor2.push_back(numberVector.at(numberIndex)); 
		} 
		return numberVecor2;
	}
};

 


//艺术字体库索引枚举
enum
{
	_Art_Font_Index_0_,
	_Art_Font_Index_1_,
	_Art_Font_Index_2_,
	_Art_Font_Index_3_,
	_Art_Font_Index_4_,
	_Art_Font_Index_5_,
	_Art_Font_Index_6_,
	_Art_Font_Index_7_,
	_Art_Font_Index_8_,
	_Art_Font_Index_9_,
	_Art_Font_Index_SUB_, 
	_Art_Font_Index_ADD_,
	_Art_Font_Index_Two_,
	_Art_Font_Index_Four_,
	_Art_Font_Index_Ten_,
	_Art_Font_Index_BaoJi_,
	_Art_Font_Index_Miss_,	
	_Art_Font_Index_Block_,
};

//ClientConst数据表中的Key
#define CONST_KEY_BATTLE_NORSPD				"battle_norspd"
#define CONST_KEY_BATTLE_DOUBLESPD			"battle_doublespd"
#define CONST_KEY_BATTLE_TRIPLESPD			"battle_triplespd"
#define CONST_KEY_USEITEM_NORSTYLE			"useitem_norstyle"
#define CONST_KEY_USEITEM_CRISTYLE			"useitem_cristyle"
#define CONST_KEY_ICON_ENG					"icon_eng"
#define CONST_KEY_ICON_GOLD					"icon_gold"
#define CONST_KEY_ICON_EXP					"icon_exp"
#define CONST_KEY_ICON_DIAMOND				"icon_diamond"
#define CONST_KEY_ICON_STRSKILL				"icon_strskill"
#define CONST_KEY_ICON_DEXSKILL				"icon_dexskill"
#define CONST_KEY_ICON_INISKILL				"icon_iniskill"
#define CONST_KEY_ICON_PRESTAGE				"icon_prestage"
#define CONST_KEY_ICON_EXPLOIT				"icon_exploit"
#define CONST_KEY_ICON_HEROEXP				"icon_heroexp"
#define CONST_KEY_ICON_EQUIPEXP				"icon_equipexp"
#define CONST_KEY_ICON_MAXHP				"icon_maxhp"
#define CONST_KEY_ICON_MAXMP				"icon_maxmp"
#define CONST_KEY_ICON_SPEED				 "icon_speed"
#define CONST_KEY_ICON_MIN_ATTACK			"icon_min_attack"
#define CONST_KEY_ICON_MAX_ATTACK			"icon_max_attack"
#define CONST_KEY_ICON_ATTR_ARMOR			"icon_armor"
#define CONST_KEY_ICON_ATTR_EXPOSEARMOR		"icon_exposearmor"
#define CONST_KEY_ICON_ATTR_HIT				"icon_hit"
#define CONST_KEY_ICON_ATTR_DODGE			"icon_dodge"
#define CONST_KEY_ICON_ATTR_CRIT			"icon_crit"
#define CONST_KEY_ICON_ATTR_UNCRIT			"icon_uncrit"
#define CONST_KEY_GETITEM_EFFECT_DIS		"getitem_effect_dis"
#define CONST_KEY_GUIDE_THUMB_EQUIP_DURING	"guide_thumb_equip_during"
#define CONST_KEY_GUIDE_THUMB_SKILL_DURING	"guide_thumb_skill_during"
#define CONST_KEY_AVATAR_SCALE_TIMES		"avatar_scale_times"				//头像缩放到品质框中的倍数

#define CONST_KEY_MISSION_SCALE_MAX			"mission_scaleMax"
#define CONST_KEY_MISSION_SCALE_MIN			"mission_scaleMin"
#define CONST_KEY_MISSION_SCALE_SPEED		"mission_scaleSpeed"
#define CONST_KEY_MISSION_COLOR_R			"mission_colorR"
#define CONST_KEY_MISSION_COLOR_G			"mission_colorG"
#define CONST_KEY_MISSION_COLOR_B			"mission_colorB"
#define CONST_KEY_MISSION_COLOR_A			"mission_colorA"
#define CONST_KEY_MISSION_MASSACE_LEVEL		"mission_massace_level"
#define CONST_KEY_MISSION_ARROW_NUM			"mission_arrow_num"
#define CONST_KEY_SOUND_COMMON_OPEN			"sound_common_open"
#define CONST_KEY_EFFECT_REMOVE_DELAY_TIME  "effect_remove_delay_time"
#define CONST_KEY_MSGBOX_POP_SCALE_1		"msgbox_pop_scale_1"
#define CONST_KEY_MSGBOX_POP_SCALE_2		"msgbox_pop_scale_2"
#define CONST_KEY_MSGBOX_POP_SCALE_3		"msgbox_pop_scale_3"
#define CONST_KEY_MSGBOX_POP_SCALE_4		"msgbox_pop_scale_4"
#define CONST_KEY_MSGBOX_POP_DURING_2		"msgbox_pop_during_2"
#define CONST_KEY_MSGBOX_POP_DURING_3		"msgbox_pop_during_3"
#define CONST_KEY_MSGBOX_POP_DURING_4		"msgbox_pop_during_4"
#define CONST_KEY_FALLDOWN_TIME				"action_falldown_time"
#define CONST_KEY_HOMEMAP_MOVE_DURING		"homemap_move_during"
#define MAIN_LINE_TASK_FONTID				"main_line_task_font"
#define DAILY_LINE_TASK_FONTID				"daily_line_task_font"
#define POWER_ICON							"power_icon"
#define INTELIGENCE_ICON					"inteligence_icon"
#define QUICK_ICON							"quick_icon"
#define UI_ADPET_EFFECT						"ui_adpet_effect"
#define HERO_ADVANCE_LEVEL					"hero_advance_level"
#define HEROBAR_LEVEL						"herobar_level"
#define MAX_HERO_PROGRESS					"hero_max_progress"
#define EQUIP_PROMOTE_LEVEL					"equip_promote_level"
#define EQUIP_TRAIN_LEVEL					"equip_train_level"
#define HEROSOUL_OPEN_LEVEL					"herosoulopenlevel"
 
#define CONST_KEY_MULTIREWARD_POP_DURING_2		"multireward_pop_during_2"
#define CONST_KEY_MULTIREWARD_POP_DURING_3		"multireward_pop_during_3"
#define CONST_KEY_MULTIREWARD_POP_DURING_4		"multireward_pop_during_4"

#define CONST_KEY_START_SHINT_FADE_DURING		"CONST_KEY_START_SHINT_FADE_DURING"

#define EQUIPS_BEACKDOMN_LEVEL_LIMIT			"equip_beakdown_level_limit"

#define ENABLE_LOCAL_ATHLEICS				"enable_local_athleticsdata"
#define REPLACE_MAP_ID_1						"replace_map_id_1"
#define REPLACE_STAGE_ID_1						"replace_stage_id_1"
#define REPLACE_MAP_ID_2						"replace_map_id_2"
#define REPLACE_STAGE_ID_2						"replace_stage_id_2"


//vip开启功能等级
#define VIP_NULI_PRESS_LEVEL				"vip_nuli_press_level"
#define	EQUIPTRAIN_ONEKEY_CD				"equiptrain_onekey_time"
#define COUSTOM_SKIP_VIP_LEVEL				"custom_skip_vip_level"			
#define ARENA_SKIP_VIP_LEVEL				"arena_skip_vip_level"
#define TOWER_SKIP_VIP_LEVEL				"tower_skip_vip_level"
#define TEAM_SKIP_VIP_LEVEL					"team_skip_vip_level"
#define SERVANT_SKIP_VIP_LEVEL				"servant_skip_vip_level"
#define FRIENT_SKIP_VIP_LEVEL				"friend_skip_vip_level"
#define KUANGDONG_SKIP_VIP_LEVEL			"kuangdong_skip_vip_level"
#define SIX_SKILL_VIP_LEVEL					"six_skill_vip_level"
#define KUANGDONG_HUNT_LIEREN_VIP_LEVEL		"kuangdong_hunt_lieren_vip_level"

#define HERO_CORNER_MARK_INDEX1				"hero_index_1"
#define HERO_CORNER_MARK_INDEX2				"hero_index_2"
#define HERO_CORNER_MARK_INDEX3				"hero_index_3"




//属性锁
#define ATTRIBUTE_TEMPLATEID				"attributelock_templateid"

//灵魂石
#define SOULSTONE_TEMPLATEID				"soulstone_templateid"

//龙血晶石
#define LONGXUEJINGSHI_TEMPLATEID			"longxuejingshi_templateid"

//寻宝中运动时间
#define	HUNT_MINING_MOVETIME				"hunt_mining_movetime"

//公告间隔等待时间
#define ANNOUNCEMENT_WATTING_DURING			"annoucement_watting_during" 
//公告背景ID
#define ANNOUCEMENT_BG_ID					"annoucement_bg_id"
    
//战斗延时入场时间
#define  Athletics_Admisson_Delay			"athletics_admisson_delay"	
//战斗结果页面延时显示时间
#define  Athletics_Result_Delay			    "athletics_result_delay"


//通讯超时时间
#define CONST_KEY_COMMUNICATION_TIMEOUT		"communication_timeout"


#define  Loading_Tip_Total_Num			    "loading_tip_total_num"
#define  Massacre_Interval_Time				"massacre_interval_time"
 
//~~~~~~~新手引导箭头Spine~~~~~
#define SPINE_GUIDE_ARROW_JSON			"resource/spine/dotajt.json"
#define SPINE_GUIDE_ARROW_ALTAS		"resource/spine/dotajt.atlas"
#define SPINE_GUIDE_ARROW_DAIJI			"zzdaiji"
#define SPINE_GUIDE_ARROW_DAIJI_S		"zzdaiji-s"
#define SPINE_GUIDE_ARROW_MOVE		"zzmove"
//~~~~~~~新手引导手指~~~~~~~
#define  GUIDE_THUMB_IMG										"resource/image/newguide/thumb.png"
#define  GUIDE_THUMB_VIRTUAL_IMG						"resource/image/newguide/thumb2.png"

//飘数值纹理Plist
#define  ATHLETICS_NUMBERICAL_PLIST			 "resource/image/artfont/art_numberival.plist"

/*
服务器通信等待时长
*/
#define    _COMMUNICATION_WAIT_LONG_   "5.0"

/*
按钮点击间隔时间
*/
#define    _COMMON_BTN_CLICK_INTERVAL_SMALL  600000
#define    _COMMON_BTN_CLICK_INTERVAL_       1300000    //单位微妙
 

//技能VIP提醒
#define   _VIP_SKILL_SIX_TIPS_		         6023


/*
按钮间隔逻辑
*/
#define    BTN_INTERVAL(BTN_NAME,BTN_INTERVAL_TIME)     long long lastClickMillSecond=0l; \
														VariableSystem::get_instance2()->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"BTN_CLICK_INTERVAL",BTN_NAME,lastClickMillSecond); \
														if(lastClickMillSecond!=0) \
													    {  \
														  long long curTimeSystemMillSecond=TimeSystem::get_instance2()->GetCurrentMicroSecond(); \
														  if((curTimeSystemMillSecond-lastClickMillSecond)<=BTN_INTERVAL_TIME)\
														  return ;\
														}\
														VariableSystem::get_instance2()->SetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"BTN_CLICK_INTERVAL",BTN_NAME,TimeSystem::get_instance2()->GetCurrentMicroSecond());


/*
设置弱提示系统使能
*/
#define    SET_WEAK_TIPS_SYSTEM(isPauseWeakTips)  VariableSystem::get_instance2()->SetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"PAUSE_WEAK_TIPS","IsPauseWeakTips",isPauseWeakTips);

/*
获得弱提示系统使能
*/
#define   GET_WEAK_TIPS_SYSTEM(isPauseWeakTips)  VariableSystem::get_instance2()->GetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"PAUSE_WEAK_TIPS","IsPauseWeakTips",isPauseWeakTips);



//获取中文数字的文字  单个文字
static std::string  getCharByNum(int number)   // 0 - 9
{ 
	int array[]={750,751,752,753,754,755,756,757,758,759};
	if(number<10)
	{
		return  SysLangDataManager::get_instance2()->GetSysLangById(array[number]);
	}
	return "";
}


//获取英雄的类型
static std::string  getHeroTypeStr(int heroType)
{   
	switch(heroType)
	{
	case  _HERO_TYPE_POWRD_TYPE_:
		{
			return  SysLangDataManager::get_instance2()->GetSysLangById(101);
			break;
		}
	case  _HERO_TYPE_QUICK_TYPE_:
		{
			return  SysLangDataManager::get_instance2()->GetSysLangById(102);
			break;
		}
	case _HERO_TYPE_INTERLIGENCE_TYPE_:
		{
			return  SysLangDataManager::get_instance2()->GetSysLangById(103);
			break;
		}
	default:
		break;
	}
	return "";
}


/*获取专精特效ID*/

static int  getUIAdpetEffectID()
{
	return ClientConstDataManager::get_instance2()->getValueByKey(UI_ADPET_EFFECT);
}
 

static bool getEnableLocalAthletiData()
{
	bool bFightRecordEnable = false;
	if(DOTA_CONFIG_MODE==kMODE_DEBUG)
	{
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "FightRecordEnable", bFightRecordEnable);
	}  
	return  bFightRecordEnable;
}

static int  getWillReplaceMapID1()
{
	return ClientConstDataManager::get_instance2()->getValueByKey(REPLACE_MAP_ID_1);
}
static int  getWillReplaceStageID1()
{
	return ClientConstDataManager::get_instance2()->getValueByKey(REPLACE_STAGE_ID_1);
}

static int getWillReplaceMapID2()
{
	return ClientConstDataManager::get_instance2()->getValueByKey(REPLACE_MAP_ID_2);
}
static int getWillReplaceStageID2()
{ 
	return ClientConstDataManager::get_instance2()->getValueByKey(REPLACE_STAGE_ID_2);
}
  
#endif