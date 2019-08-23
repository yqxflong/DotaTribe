#ifndef _DOTATRIBE_HeroIllustratedDataHandler_H_
#define _DOTATRIBE_HeroIllustratedDataHandler_H_
#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include <vector>
////////////////////////////////////////////////////////////////
//Name:	 HeroIllustratedDataHandler
//Auchor: 	xiaobo.wu
//Func:	 图鉴系统数据处理器
//Maintainer: 	xiaobo.wu
//date:   2013/11/22
////////////////////////////////////////////////////////////////


#define  _MODE_CELL_NUM_      3			//单个Cell横向最大模数
#define  _MAX_QUALITY_VALUE_  5			//最大品质数

/*
英雄图鉴基列表
*/
class  IHeroSkinItem;
class  IHeroCellItem;

class IHeroillustated_Base_Tag
{
public:
	enum
	{   
		_Illustrated_Unkonw_Type_=-1,			//未知图鉴类型
		_Illustrated_Power_Type_,				//力量图鉴类型
		_Illustrated_Quick_Type_,				//敏捷图鉴类型
		_Illustrated_Inteligence_Type_,			//智力图鉴类型
		_Illustrated_ALL_Type_,					//所有图鉴类型
	};
	IHeroillustated_Base_Tag();
	virtual ~IHeroillustated_Base_Tag();
	property_unit_ronly(IByte,m_cIllustratedType,IllustratedType)
	property_unit_ronlyc(std::vector<IHeroCellItem *>,m_vPlayerSelfVector,PlayerSelfCellList)
	property_unit_ronlyc(std::vector<IHeroCellItem *>,m_vAllRecordCellList,AllRecordCellList) 
	
public:
	virtual void   AddChild(IHeroSkinItem * pHeroItem);
	virtual void   UpdateAndSort();
	virtual void   RefreshSelfHercData();
protected:
	void   CombineCellList(int  qualiyValue,std::vector<IHeroSkinItem *> & heroItemVec);
	void   RefreshSelfItem(int  qualiyValue,std::vector<IHeroSkinItem *> & heroItemVec);
protected:
	std::map<int,std::vector<IHeroSkinItem *> > m_mInterMap;  
}; 

/*
力量图鉴列表
*/
class IHeroIllustrated_Power_Tag : public IHeroillustated_Base_Tag
{ 
public:
	IHeroIllustrated_Power_Tag();
    virtual ~IHeroIllustrated_Power_Tag();
	virtual void   AddChild(IHeroSkinItem * pHeroItem);
};

/*
智力图鉴列表
*/
class IHeroIllustrated_Inteligence_Tag : public IHeroillustated_Base_Tag
{
public:
	IHeroIllustrated_Inteligence_Tag();
	virtual ~IHeroIllustrated_Inteligence_Tag();
	virtual void   AddChild(IHeroSkinItem * pHeroItem);
};

/*
敏捷图鉴列表
*/
class IHeroIllustrated_Quick_Tag : public IHeroillustated_Base_Tag
{
public:
	IHeroIllustrated_Quick_Tag();
	virtual ~IHeroIllustrated_Quick_Tag();
	virtual void   AddChild(IHeroSkinItem * pHeroItem);
};

/*
所有图鉴列表
*/
class IHeroIllustated_All_Tag: public IHeroillustated_Base_Tag
{
public:
	IHeroIllustated_All_Tag();
	virtual ~IHeroIllustated_All_Tag();
	virtual void   AddChild(IHeroSkinItem * pHeroItem);
}; 
 
//////////////////////////////////////////////////////////////////////////
 
/*
英雄图鉴列表单元
*/
class  IHeroCellItem
{ 
	property_unit_rw(bool,m_bIsStarCellType,IsStarCellType)
	property_unit_rw(IByte,m_nStarsNum,StarsNum)
	property_unit_rwc(std::vector<IHeroSkinItem *>,m_vHeroVector,HeroVector)  //进过模除后的列表
public:
	IHeroCellItem() ;
	virtual ~IHeroCellItem();
};  
 

//英雄图鉴CellList工厂
class  HeroIllustratedCellListFactory
{
public:
	HeroIllustratedCellListFactory();
	~HeroIllustratedCellListFactory();
public:
	void  Init();
	void  AddChild(IHeroSkinItem * pHeroItem);
	void  UpdateAndSort();
	IHeroillustated_Base_Tag *  GetHeroIllustratedByType(IByte illustratedType);
	void  RefreshSelfHeroCells();
	void  Destroy();
protected:
	std::map<int,IHeroillustated_Base_Tag *>  m_pHeroIllustratedMap;
};

//////////////////////////////////////////////////////////////////////////
//图鉴内存数据管理器 
class  HeroIllustratedDataHandler : public IDataHandler, public cobra_win::Singleton2<HeroIllustratedDataHandler>
{
	property_unit_rwc(HeroIllustratedCellListFactory *, m_pHeroIllustratedCellListFactory,HeroCellListFactory)	//英雄CellList工厂
public:
	HeroIllustratedDataHandler();
	virtual ~HeroIllustratedDataHandler();
	/*
	刷新玩家列表Cell
	*/
	void   RefreshSelfHeroCellsList();
	/*
	发送更换英雄请求
	*/
	void   SendReplaceHeroRequest(int newHeroUniqueID, unsigned char heroPos);
	/*
	激活指定英雄
	*/
	void   ActiveHeroSkinHandler(int & newHeroUniqueID);

	/*
	获取进阶的同组英雄
	*/
	std::map<int,IHeroSkinItem *> & GetAdvancedGropHeroSkins();
	/*
	是否跟换英雄的时候同队有相同的	
	*/
	bool   IsTeamHeroSame(int index,IHeroSkinItem * heroskin);
	/*
	判断英雄是否可以进阶
	*/
	bool   JudgeHeroAdvancedEnable(IHeroSkinItem * pHeroSkinItem);

	/*
	重组CellFactory
	*/
	void   ReInitData();
	 
	/*
	获取Cell中第一个激活的最高星级英雄ID
	*/
	int	   GetFirstHightestActiveSkinUID();

protected:
	virtual void handlePacket(IPacket* packet){};
	virtual void onDestroy();
	virtual bool init();
protected:
	std::map<int,IHeroSkinItem *> m_sameGropHeroSkinMap;	// shapeLevel
};

#define	  HERO_ILLUSTRATED_ADVANCED_MAP	 HeroIllustratedDataHandler::get_instance2()->GetAdvancedGropHeroSkins()

#define   HEROILLUSTRATEDDATAHANDLER    (HeroIllustratedDataHandler::get_instance2())
 
#endif
