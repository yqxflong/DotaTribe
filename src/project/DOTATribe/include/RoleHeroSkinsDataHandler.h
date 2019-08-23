//Name��RoleHeroSkinsDataHandler
//Function��Ӣ�����ݣ��ڴ棩
//Author��Johny

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
//Ӣ�����׽��
class  IHeroSkinItem
{   
	//////////////////////////////////////////////////////////////////////////
	//Base ����ֵ
	property_unit_rw(int,m_nHeroUniqueID,HeroUniqueID)			//Ӣ��ΨһID
	property_unit_rw(UShort,m_nHeroGroupID,HeroGroupID)			//Ӣ����ID
	property_unit_rw(IByte,m_bHeroShapeLevel,HeroShapeLevel)	//Ӣ�����εȼ� ��
	property_unit_rw(IString,m_sHeroName,HeroName)				//Ӣ������
	property_unit_rw(IByte,m_bHeroType,HeroType)				//Ӣ������
	property_unit_rw(IByte,m_bHeroQualiy,HeroQualiy)			//Ӣ��Ʒ��
	property_unit_rw(int,m_nHeroIconID,HeroIconID)				//Ӣ��ͼ��ID
	property_unit_rw(int,m_nHeroShapeID,HeroShapeID)			//Ӣ������ID
	property_unit_rw(bool,m_bExistHeroSoul,IsExistHeroSoul)								//�Ƿ����Ӣ��ս��
	property_unit_rw(short,m_nHeroSoulChallengeLevel,HeroSoulChallenegeLevel)			//Ӣ��ս����ս�ȼ�
	property_unit_rw(bool,m_bIsActive,IsActived)				//Ӣ���Ƿ񼤻�
	//////////////////////////////////////////////////////////////////////////
	//Expand ��չֵ

	property_unit_rw(int,m_nHeroPower,HeroPower)				//Ӣ������
	property_unit_rw(int,m_nHeroQuick,HeroQuick)				//Ӣ������
	property_unit_rw(int,m_nHeroInteligence,HeroIntligence)		//Ӣ������

	property_unit_rw(IByte,m_bHeroAttackGrow,HeroAttackGrow)	//�����ɳ�
	property_unit_rw(IByte,m_bHeroSpeedGrow,HeroSpeedGrow)		//�ٶȳɳ�
	property_unit_rw(IByte,m_bHeroHpGrow,HeroHpGrow)			//HP�ɳ�
	property_unit_rw(IByte,m_bHeroMpGrow,HeroMpGrow)			//MP�ɳ�

	property_unit_rw(UShort,m_nHeroBufferID,HeroBufferID)		//��ЧID
	property_unit_rw(IByte,m_bHeroBufferLevel,HeroBufferLevel)	//��Ч����
	property_unit_rw(int,m_nHeroBufferIconID,HeroBufferIconID)	//��Чͼ��ID
	property_unit_rw(IString,m_sHeroBufferName,HeroBufferName)	//��Ч����
	property_unit_rw(IString,m_sHeroBufferDesc,HeroBufferDesc)	//��Ч����
	property_unit_rw(int, m_nHeroStrength, HeroStrength)						//Ӣ��ս��

	property_unit_rw(Attribute*,m_pAttManager,AttributeManager);	//Ӣ�����Թ�����
	property_unit_rw(RoleEquipDataHandler*,m_pEquipManager,EquipManager);	//Ӣ��װ��������
	property_unit_rw(RoleSkillsDataHandler*,m_pSkillManager,SkillManager);	//Ӣ�ۼ��ܹ�����
	property_unit_rw(IRoleSoulsEquipInfo*, m_pSoulsEquipManager, SoulsEquipManager);	//Ӣ��ս�������



	property_unit_rw(bool,m_bIsNeedUpdate,IsNeedUpdate)			//�Ƿ���Ҫ����
public:
	IHeroSkinItem();
	virtual ~ IHeroSkinItem();
	void resetExpandInfo();
	void decodePacketBaseData(cobra_win::DPacket & packet,bool isPlayerHero=false);
	//@����-Ӣ��ģ��
	void decodePacket_HeroTemplate(cobra_win::DPacket & packet);
	//@����-Ӣ������
	void decodePacket_HeroProp(cobra_win::DPacket & packet);
	//@����-װ��
	void decodePacket_Equip(cobra_win::DPacket & packet);
	//@����-����
	void decodePacket_skill(cobra_win::DPacket & packet);
	//@����-ս��
	void decodePacket_soul(cobra_win::DPacket & packet);
	//@ͬ��Ӣ����Ϣ
	void decodePacketSynInfo(cobra_win::DPacket & packet);	
public:
	IHeroSoulItem* getBuffIdByHeroItem(int buffid);
};



class  RoleHeroSkinsDataHandler : public IDataHandler, public cobra_win::Singleton2<RoleHeroSkinsDataHandler>
{
public:
	//@��ȡ�����е�Ӣ��
	IHeroSkinItem *  GetCurHeroSkinItem(int pos=0);

	//@�滻ָ��λ��Ӣ�۵�����
	void             ChangeHeroByPos(IHeroSkinItem * pHeroSkinItem,int pos=0);

	//@�鿴Ӣ���Ƿ����ڶ�����
	bool	IsHeroInTeam(int uniqueID);

	//@Ӣ��ͼ������Ӣ��
	IHeroSkinItem *  GetHeroSkinItemByID(int heroiUniqueID);
 
	//@��ȡӢ����������
	size_t			 GetHeroSkinsNum();

	//@��ȡ������Ӣ������
	size_t           GetActiveHeroSkinsNum();

	//@���ý�ɫ����չ��Ϣ
	void             ResetHeroExpandInfo();

	//@�жϵ�ǰӢ���Լ����Ƿ���Խ���
	bool		    JudgeHeroAdvancedEnable(IHeroSkinItem * pHeroSkinItem);

	//@���½�Ӣ������ֵ
	void		    SetHeroVector(std::vector<IHeroSkinItem *> herolist);

	//@��ý�Ӣ������ֵ
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
