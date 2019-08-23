//Name：RoleHeroSkinsDataHandler
//Function：英雄数据（内存）
//Author：Johny

#ifndef _DOTATRIBE_RoleHeroSkinsDataHandler_H_
#define _DOTATRIBE_RoleHeroSkinsDataHandler_H_

#include <cocos2d.h>
#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include "../include/CPublicVarReader.h"
 
class Attribute;
class RoleEquipDataHandler;
class RoleSkillsDataHandler;
class IRoleSoulsEquipInfo;
class IHeroSoulItem;
//英雄外套结点
class  IHeroSkinItem
{   
	//////////////////////////////////////////////////////////////////////////
	//Base 基础值
	property_unit_rw(int,m_nHeroUniqueID,HeroUniqueID)			//英雄唯一ID
	property_unit_rw(UShort,m_nHeroGroupID,HeroGroupID)			//英雄组ID
	property_unit_rw(IByte,m_bHeroShapeLevel,HeroShapeLevel)	//英雄外形等级 阶
	property_unit_rw(IString,m_sHeroName,HeroName)				//英雄名称
	property_unit_rw(IByte,m_bHeroType,HeroType)				//英雄类型
	property_unit_rw(IByte,m_bHeroQualiy,HeroQualiy)			//英雄品质
	property_unit_rw(int,m_nHeroIconID,HeroIconID)				//英雄图标ID
	property_unit_rw(int,m_nHeroShapeID,HeroShapeID)			//英雄外形ID
	property_unit_rw(bool,m_bExistHeroSoul,IsExistHeroSoul)								//是否存在英雄战魂
	property_unit_rw(short,m_nHeroSoulChallengeLevel,HeroSoulChallenegeLevel)			//英雄战魂挑战等级
	property_unit_rw(bool,m_bIsActive,IsActived)				//英雄是否激活
	//////////////////////////////////////////////////////////////////////////
	//Expand 扩展值

	property_unit_rw(int,m_nHeroPower,HeroPower)				//英雄力量
	property_unit_rw(int,m_nHeroQuick,HeroQuick)				//英雄敏捷
	property_unit_rw(int,m_nHeroInteligence,HeroIntligence)		//英雄智力

	property_unit_rw(IByte,m_bHeroAttackGrow,HeroAttackGrow)	//攻击成长
	property_unit_rw(IByte,m_bHeroSpeedGrow,HeroSpeedGrow)		//速度成长
	property_unit_rw(IByte,m_bHeroHpGrow,HeroHpGrow)			//HP成长
	property_unit_rw(IByte,m_bHeroMpGrow,HeroMpGrow)			//MP成长

	property_unit_rw(UShort,m_nHeroBufferID,HeroBufferID)		//特效ID
	property_unit_rw(IByte,m_bHeroBufferLevel,HeroBufferLevel)	//特效级别
	property_unit_rw(int,m_nHeroBufferIconID,HeroBufferIconID)	//特效图标ID
	property_unit_rw(IString,m_sHeroBufferName,HeroBufferName)	//特效名称
	property_unit_rw(IString,m_sHeroBufferDesc,HeroBufferDesc)	//特效描述
	property_unit_rw(int, m_nHeroStrength, HeroStrength)						//英雄战力

	property_unit_rw(Attribute*,m_pAttManager,AttributeManager);	//英雄属性管理器
	property_unit_rw(RoleEquipDataHandler*,m_pEquipManager,EquipManager);	//英雄装备管理器
	property_unit_rw(RoleSkillsDataHandler*,m_pSkillManager,SkillManager);	//英雄技能管理器
	property_unit_rw(IRoleSoulsEquipInfo*, m_pSoulsEquipManager, SoulsEquipManager);	//英雄战魂管理器



	property_unit_rw(bool,m_bIsNeedUpdate,IsNeedUpdate)			//是否需要更新
public:
	IHeroSkinItem();
	virtual ~ IHeroSkinItem();
	void resetExpandInfo();
	void decodePacketBaseData(cobra_win::DPacket & packet,bool isPlayerHero=false);
	//@解析-英雄模板
	void decodePacket_HeroTemplate(cobra_win::DPacket & packet);
	//@解析-英雄属性
	void decodePacket_HeroProp(cobra_win::DPacket & packet);
	//@解析-装备
	void decodePacket_Equip(cobra_win::DPacket & packet);
	//@解析-技能
	void decodePacket_skill(cobra_win::DPacket & packet);
	//@解析-战魂
	void decodePacket_soul(cobra_win::DPacket & packet);
	//@同步英雄信息
	void decodePacketSynInfo(cobra_win::DPacket & packet);	
public:
	IHeroSoulItem* getBuffIdByHeroItem(int buffid);
};



class  RoleHeroSkinsDataHandler : public IDataHandler, public cobra_win::Singleton2<RoleHeroSkinsDataHandler>
{
public:
	//@获取队伍中的英雄
	IHeroSkinItem *  GetCurHeroSkinItem(int pos=0);

	//@替换指定位置英雄的外套
	void             ChangeHeroByPos(IHeroSkinItem * pHeroSkinItem,int pos=0);

	//@查看英雄是否已在队伍中
	bool	IsHeroInTeam(int uniqueID);

	//@英雄图鉴中找英雄
	IHeroSkinItem *  GetHeroSkinItemByID(int heroiUniqueID);
 
	//@获取英雄外套总数
	size_t			 GetHeroSkinsNum();

	//@获取当激活英雄总数
	size_t           GetActiveHeroSkinsNum();

	//@重置角色的扩展信息
	void             ResetHeroExpandInfo();

	//@判断当前英雄以及组是否可以进阶
	bool		    JudgeHeroAdvancedEnable(IHeroSkinItem * pHeroSkinItem);

	//@重新将英雄链表赋值
	void		    SetHeroVector(std::vector<IHeroSkinItem *> herolist);

	//@获得将英雄链表赋值
	std::vector<IHeroSkinItem *>&		    GetHeroVector();
public:
	RoleHeroSkinsDataHandler();
	virtual ~RoleHeroSkinsDataHandler();	
	void decodePacket_TeamHero(cobra_win::DPacket & packet);
	void decodePacket_HeroDB(cobra_win::DPacket & packet);
	void decodePacket_One_HeroSkinsData(cobra_win::DPacket & packet,bool isPlayerHeroSkin,unsigned int idx);
	void parseHeroSkinsDBCompleteCall();
	size_t TeamHeroCount();
	bool HasTeamHero(int idx=0);
protected:
	virtual void handlePacket(IPacket* packet);
	virtual void onDestroy();
	virtual bool init();
protected:
	std::vector<IHeroSkinItem *> m_vecHeroList;
	std::map<int,IHeroSkinItem *>  m_mHeroSkinsDB;

private:
	void _clearHeroDB();
	void _clearTeamHero();
};
#define   ROLEHEROSKINSDATAHANDLER     (RoleHeroSkinsDataHandler::get_instance2())

#endif
