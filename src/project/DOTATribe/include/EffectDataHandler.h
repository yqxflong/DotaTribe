//Name： EffectDataHandler
//Function：效果管理器
//Written By：尹强

#ifndef   _DOTATRIBE_EffectDataHandler_H
#define   _DOTATRIBE_EffectDataHandler_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <list>
#include <string>
#include <vector>

enum{
	kEFFECT_OBJECT,	//物品
	kEFFECT_OBJECTBJ,	//物品暴击
	kEFFECT_NUM,	//数值
	kEFFECT_NUMBJ,//数值暴击
};

enum{
	kEFFECT_TYPE_OBJECT=0,			//物品
	kEFFECT_TYPE_MONEY,				//金币
	kEFFECT_TYPE_EXP,						//经验
	kEFFECT_TYPE_DIAMOND,	//钻石
	kEFFECT_TYPE_TL,		//体力
	kEFFECT_TYPE_STR,		//力量
	kEFFECT_TYPE_DEX,		//敏捷
	kEFFECT_TYPE_INTEL,		//智力
	kEFFECT_TYPE_PRESTAGE,	//声望
	kEFFECT_TYPE_EXPLOIT,		//功勋
	kEFFECT_TYPE_HERO_EXP,		//hero Exp
	kEFFECT_TYPE_EQUIP_EXP,		//Equip Exp
	kEFFECT_TYPE_ATTR_MAXHP,					//最大HP
	kEFFECT_TYPE_ATTR_MAXMP,					//最大MP
	kEFFECT_TYPE_ATTR_SPEED,					//速度
	kEFFECT_TYPE_ATTR_MIN_ATTACK,			//最小攻击力
	kEFFECT_TYPE_ATTR_MAX_ATTACK,		//最大攻击力
	kEFFECT_TYPE_ATTR_ARMOR,					//护甲
	kEFFECT_TYPE_ATTR_EXPOSEARMOR,			//破甲
	kEFFECT_TYPE_ATTR_HIT,				//命中
	kEFFECT_TYPE_ATTR_DODGE,		//闪避
	kEFFECT_TYPE_ATTR_CRIT,			//暴击
	kEFFECT_TYPE_ATTR_UNCRIT,		//任性
};


/*
	一个效果数据
*/
class EffectData{
public:
//必填
private:
	int type_;			//类型
	int iconID_;		//物品必填
	std::string iconKey_;		//数值必填
	int count_;		//数值
	int bjcount_;	//如果为暴击，则表示几倍
//~~~~读表获取
public:
	std::string iconPath_;
	float animaTime_;
	float fadeoutStartTime_;	//开始渐隐时间
	float beginPosY_;
	float endPosY_;
	float scale_;
	std::vector<int> vecFonts_;		//每个字对应的索引--数值
	std::vector<int> vecFonts_BJ_;		//每个字对应的索引--数值暴击
public:
	EffectData(int type,int iconID,const char* iconKey,int count,int bjcount){
		type_=type;
		iconID_=iconID;
		iconKey_=iconKey;
		count_=count;
		bjcount_=bjcount;
	}
	int getType()const{
		return type_;
	}
	int getIConID()const{
		return iconID_;
	}
	const char* getIConKey()const{
		return iconKey_.c_str();
	}
	int getCount()const{
		return count_;
	}
	int getBJCount()const{
		return bjcount_;
	}
};


class EffectDataHandler:public IDataHandler,public cobra_win::Singleton2<EffectDataHandler>{
public:
	std::list<EffectData*>	effectList_;
public:
	EffectDataHandler(){};
	virtual ~EffectDataHandler(){};
	virtual bool init();
	virtual void onDestroy();
private:
	inline void _registerEvent();
	inline void _unRegisterEvent();
	/*
		同步数值
	*/
	void Effect_GetNum(int key,int count);
	/*
		同步数值,暴击
	*/
	void Effect_GetNumBJ(int key,int count,int bjcount);
	/*
		同步物品
	*/
	void Effect_GetObject(int iconid,int count);
	/*
		同步物品暴击
	*/
	void Effect_GetObjectBJ(int iconid,int count,int bjcount);

	//使用完会delete的
	void pushToEffectList(EffectData* dd);
private:
	inline void _handleIcon(EffectData* dd);
	inline int _handleAnima(EffectData* dd);
	inline void _handleNum(EffectData* dd,int fonttype);
	inline void _handleBJ(EffectData* dd,int fonttype);
public:
	/*
		解析来自服务器的包，并实现飘字
	*/
	void decodePacketData(cobra_win::DPacket & packet);
	void HandleAfterOnePacket();

	/*
		实现飘字接口
	*/
	void ShowFlowEffect(int type,int count,int bjcount,int itemiconid=0);

	//开启EffectHandler
	void OpenEffectHandler();

	//清空所有效果
	static void ClearEffectList(int iEventType, std::string owerData, std::list<std::string>& paramList);
};
#define EFFECTDATAHANDLER	 EffectDataHandler::get_instance2()
#endif