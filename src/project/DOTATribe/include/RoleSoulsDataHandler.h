#ifndef  _DOTATRIBE_ROLESOULSDATAHANDLER_H
#define	 _DOTATRIBE_ROLESOULSDATAHANDLER_H

#include	 <include/common/Singleton.h>
#include	 <include/mem/DPacket.h>
#include	 "../include/IDataHandler.h"
#include	 "../include/CPublicVarReader.h"
  
class  IHeroSoulItem
{   
public:
	enum
	{
		_HeroSoul_UnKonw_Type_=-1,				//未知战魂类型
		_HeroSoul_Power_Type_,					//力量战魂类型
		_HeroSoul_Quick_Type_,					//敏捷战魂类型
		_HeroSoul_Inteligence_Type_,			//智力战魂类型
		_HeroSoul_ALL_Type_,					//全类型战魂类型
	};

	IHeroSoulItem(bool isindex=true);
	~IHeroSoulItem();
	property_unit_rw(int,m_nSoulBufferID,HeroSoulBufferID)						//战魂BUfferID
	property_unit_rw(int,m_nSoulBufferIconID,HeroSoulBufferIconID)				//战魂BufferIconID
	property_unit_rw(int, m_HeroID, HeroID)										//战魂对应的HeroID
	property_unit_rw(int,m_bSoulType,HeroSoulType)
	property_unit_rw(int,m_bCurSoulLevel,HeroSoulCurLevel)
	property_unit_rw(int,m_bMaxSoulLevel,HeroSoulMaxLevel)
	property_unit_rw(int,m_bEquipIndex,HeroSoulEquipIndex)						//装备索引号  -1 为未装备 其他为装备
	property_unit_rw(std::string,m_sSoulBufferName,HeroSoulBufferName)
	property_unit_rw(std::string,m_sSoulAtributeName,HeroSoulAtributeName)
public:
	void  decodePacket(cobra_win::DPacket & packet);
	void  decodeWithOutBufferIDPacket(cobra_win::DPacket & packet);
private:
	bool m_isIndex;
};


struct  SoulEquipItem
{
	IByte  m_uHeroSoulEquipIndex;
	bool   m_uHeroSoulEquipIsOpen;
	int    m_uHeroSoulEquipOpenLevel;
public:
	SoulEquipItem(IByte index,IByte isOpen,int openLevel)
	{
		m_uHeroSoulEquipIndex = index;
		m_uHeroSoulEquipIsOpen = isOpen > 0 ? true:false ;
		m_uHeroSoulEquipOpenLevel = openLevel;
	}
	void  decodePacket(cobra_win::DPacket & packet);
};

class  IRoleSoulsEquipInfo
{
	default_construct_destroy(IRoleSoulsEquipInfo)
	property_unit_rw(short,m_uHeroSoulEuipMaxCount,HeroSoulEuipMaxCount)
	//@当前英雄开放位置
	property_unit_rwc(std::vector<SoulEquipItem>, m_uHeroSoulPosVector, HeroSoulPosVector)
	//@当前英雄的战魂列表
	property_unit_rwc(std::vector<IHeroSoulItem *>, m_mHeroSoulEquipList, HeroSoulEquipList)
public:
	/*
	*  解析初始化数据
	*/
	void   decodePacket(cobra_win::DPacket & packet);

	/*
	 *	解析解锁数据包
	*/
	void   decodeUnLockEquipPacket(cobra_win::DPacket & packet);
	//@清空链表
	void   SoulEquipClearList();
};


class  IHeroSoulDataManager
{
	default_construct_destroy(IHeroSoulDataManager)
public:
	std::vector<IHeroSoulItem * > & getRoleAllSoulsVector();
	std::vector<IHeroSoulItem * > & getRolePowerSoulsVector();
	std::vector<IHeroSoulItem * > & getRoleQuickSoulsVector();
	std::vector<IHeroSoulItem * > & getRoleInteligenceSoulsVector();
	/*109std::vector<IHeroSoulItem * > & getRoleEquipSoulVector();*/
	IHeroSoulItem  *			   getRoleSoulItem(int heroSouleItemID);
	size_t						   getUnEquipSoulBufferCount();
	void    updateRoleSoul();
private:
	std::map<int,IHeroSoulItem *> m_mRoleSoulsDB;
	std::map<int,IHeroSoulItem *> m_mPowerSoulsDB;
	std::map<int,IHeroSoulItem *> m_mQuickSoulsDB;
	std::map<int,IHeroSoulItem *> m_mInteligenceSoulsDB;
//////////////////////////////////////////////////////////////////////////
	std::vector<IHeroSoulItem *>  m_mAllUnESoulsVector;
	std::vector<IHeroSoulItem *>  m_mPowerUnEUnESoulsVector;
	std::vector<IHeroSoulItem *>  m_mQuickUnESoulsVector;
	std::vector<IHeroSoulItem *>  m_mInteligenceUnESoulsVector; 
	/*109std::vector<IHeroSoulItem *>  m_mHeroSoulEqipVector;*/
public:
	void   decodePacket(cobra_win::DPacket & packet);
	void   decodeEquipSoulChangePacket(cobra_win::DPacket & packet); 
	void   decodeUnEquipSoulChangePacket(cobra_win::DPacket & packet);
	void   deoceAddHeroSoulPacket(cobra_win::DPacket & packet);
};
  
class RoleSoulsDataHandler : public IDataHandler, public cobra_win::Singleton2<RoleSoulsDataHandler>
{ 
	default_construct_vdestroy(RoleSoulsDataHandler)
	property_unit_rw(IHeroSoulDataManager * ,m_pHeroSoulDataManager,HeroSoulDataManger)
	//property_unit_rw(IRoleSoulsEquipInfo * ,m_pHeroSoulEquipInfo,HeroSoulEquipInfo)
protected:
	virtual void handlePacket(IPacket* packet){};
	virtual void onDestroy();
	virtual bool init(); 
	void    destroyData();
public:
	void  decodePacket(cobra_win::DPacket & packet);
	void  decodeSoulChangePacket(cobra_win::DPacket & packet); 
	void  decodeSoulUnChangePacket(cobra_win::DPacket & packet);
	void  decodeAddHeroSoulPacket(cobra_win::DPacket & packet);
	IHeroSoulItem  *  getHeroSoulItemByID(int heroSoulBufferID);
	int SoulUnActivIndex(std::vector<IHeroSoulItem *>& vec);
};

#define ROLESOULSDATAHANDLE (RoleSoulsDataHandler::get_instance2())



#endif