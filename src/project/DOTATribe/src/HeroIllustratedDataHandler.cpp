////////////////////////////////////////////////////////////////
//Name:	 HeroIllustratedDataHandler
//Auchor: 	xiaobo.wu
//Func:	 图鉴系统数据处理器
//Maintainer: 	xiaobo.wu
//date:   2013/11/22
////////////////////////////////////////////////////////////////

#include  "../include/HeroIllustratedDataHandler.h"
#include  "../include/CPublicVarReader.h"
#include  "../include/CSHeroExpandInfoPacket.h"
#include  "../include/NFControlsManager.h"


/*
多键值排序
*/
static void  MutipleKeySortForIllustrated(std::vector<IHeroSkinItem *> & heroSkinVector)
{
	//临时数据域
	std::vector<IHeroSkinItem *> tmpHeroSkinVec=heroSkinVector;
	std::map<int,std::map<int,IHeroSkinItem *> > heroSkinsMap;
	size_t skinsCount=tmpHeroSkinVec.size();
	COMMON_BEIGIN_ARRAY(size_t,skinsCount)
	   std::map<int,std::map<int,IHeroSkinItem *> >::iterator  hero_iter= heroSkinsMap.find(tmpHeroSkinVec.at(index)->getHeroGroupID());
	   if(hero_iter!=heroSkinsMap.end())
	   {   
		   std::map<int,IHeroSkinItem *>::iterator shapelevel_iter=hero_iter->second.find(tmpHeroSkinVec.at(index)->getHeroShapeLevel());
		   if(shapelevel_iter==hero_iter->second.end())
		   { 
			   hero_iter->second.insert(std::map<int,IHeroSkinItem *>::value_type(tmpHeroSkinVec.at(index)->getHeroShapeLevel(),tmpHeroSkinVec.at(index)));
		   }
	   }
	   else
	   {
		   std::map<int,IHeroSkinItem *> shapeLevelMap;
		   shapeLevelMap.insert(std::map<int,IHeroSkinItem *>::value_type(tmpHeroSkinVec.at(index)->getHeroShapeLevel(),tmpHeroSkinVec.at(index)));
		   heroSkinsMap.insert(std::map<int,std::map<int,IHeroSkinItem *> >::value_type(tmpHeroSkinVec.at(index)->getHeroGroupID(),shapeLevelMap));
	   } 
	COMMON_END_ARRAY
    
	heroSkinVector.clear();

	std::map<int,std::map<int,IHeroSkinItem *> >::iterator  hero_iter=heroSkinsMap.begin();
	while(hero_iter!=heroSkinsMap.end())
	{ 
		std::map<int,IHeroSkinItem *>::iterator skin_iter=hero_iter->second.begin();
		while(skin_iter!=hero_iter->second.end())
		{ 
			heroSkinVector.push_back(skin_iter->second);
			++skin_iter;
		}
		++hero_iter;
	}
	heroSkinsMap.clear();
}

 
 
//////////////////////////////////////////////////////////////////////////
IHeroillustated_Base_Tag::IHeroillustated_Base_Tag()
{  
	m_cIllustratedType=_Illustrated_Unkonw_Type_;
	m_vPlayerSelfVector.clear();
	m_vAllRecordCellList.clear();
	m_mInterMap.clear();
}

IHeroillustated_Base_Tag::~IHeroillustated_Base_Tag()
{ 
	m_cIllustratedType=_Illustrated_Unkonw_Type_;
	size_t vectorCount=m_vPlayerSelfVector.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorCount)
		delete m_vPlayerSelfVector.at(index);
	COMMON_END_ARRAY
	m_vPlayerSelfVector.clear();

	vectorCount=m_vAllRecordCellList.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorCount)
		delete m_vAllRecordCellList.at(index);
	COMMON_END_ARRAY
	m_vAllRecordCellList.clear();
	m_mInterMap.clear();
}


void   IHeroillustated_Base_Tag::AddChild(IHeroSkinItem * pHeroItem)
{
	// to do
	if(pHeroItem!=NULL)
	{   
		CCLOG("Hero UUID : %d Qualiy: %d Type: %d",pHeroItem->getHeroUniqueID(),pHeroItem->getHeroQualiy(),getIllustratedType());

		// Modify date: 2013-10-34  修改超过6(5)星的英雄 合并在6星中 有点恶心
		int keyForHeroQualiy=pHeroItem->getHeroQualiy();
		keyForHeroQualiy=keyForHeroQualiy >= _MAX_QUALITY_VALUE_ ? _MAX_QUALITY_VALUE_ : keyForHeroQualiy; 
		std::map<int,std::vector<IHeroSkinItem *> >::iterator hero_iter=m_mInterMap.find(keyForHeroQualiy);
		if(hero_iter!=m_mInterMap.end())
		{ 
			hero_iter->second.push_back(pHeroItem);
		} 
		else
		{
			std::vector<IHeroSkinItem *>  interVector;
			interVector.push_back(pHeroItem);
			m_mInterMap.insert(std::map<int,std::vector<IHeroSkinItem *> >::value_type(keyForHeroQualiy,interVector)); 
		}
	} 
}
void  IHeroillustated_Base_Tag::UpdateAndSort()
{ 
	// 多键值排序
	std::map<int,std::vector<IHeroSkinItem *> >::iterator  inter_iterator= m_mInterMap.begin();
	while(inter_iterator!=m_mInterMap.end())
	{ 
	   MutipleKeySortForIllustrated(inter_iterator->second);
	   //自动合成CellList
	   CombineCellList(inter_iterator->first,inter_iterator->second);
	   ++inter_iterator;
	}
}

void   IHeroillustated_Base_Tag::CombineCellList(int qualiyValue, std::vector<IHeroSkinItem *> & heroItemVec)
{    
	if(qualiyValue>0&&!heroItemVec.empty())
	{
		IHeroCellItem * pStartItem=new IHeroCellItem();
		pStartItem->setIsStarCellType(true);
		pStartItem->setStarsNum(qualiyValue);
		m_vAllRecordCellList.push_back(pStartItem);

		IHeroCellItem * pHeroCellItem=NULL;
		int  cellAllIndex=0;
		int  cellSelfIndex=0;
		bool bIsExistActiveCell=false;
		size_t  itemCount=heroItemVec.size();
		std::vector<IHeroSkinItem *> skinItemAllVec;
		std::vector<IHeroSkinItem *> skinItemSelfVec;

		COMMON_BEIGIN_ARRAY(size_t,itemCount)
			if(heroItemVec.at(index)->getIsActived())
			{  
				if(!bIsExistActiveCell)
				{
					IHeroCellItem * pSelfStartItem=new IHeroCellItem();
					pSelfStartItem->setIsStarCellType(true);
					pSelfStartItem->setStarsNum(qualiyValue);
					m_vPlayerSelfVector.push_back(pSelfStartItem);
					bIsExistActiveCell=true;
				}
				if(cellSelfIndex>=_MODE_CELL_NUM_)
				{
					skinItemSelfVec.push_back(heroItemVec.at(index));
					pHeroCellItem=new IHeroCellItem();
					pHeroCellItem->setStarsNum(qualiyValue);
					pHeroCellItem->setHeroVector(skinItemSelfVec);
					m_vPlayerSelfVector.push_back(pHeroCellItem);
					skinItemSelfVec.clear();
					cellSelfIndex=0;
				} 
				else
				{
					skinItemSelfVec.push_back(heroItemVec.at(index));
					cellSelfIndex++;
				}
			} 
			if(cellAllIndex >=_MODE_CELL_NUM_)
			{  
				skinItemAllVec.push_back(heroItemVec.at(index));
				pHeroCellItem=new IHeroCellItem();
				pHeroCellItem->setStarsNum(qualiyValue);
				pHeroCellItem->setHeroVector(skinItemAllVec);
				m_vAllRecordCellList.push_back(pHeroCellItem);
				skinItemAllVec.clear();
				cellAllIndex=0;
			}
			else
			{
				skinItemAllVec.push_back(heroItemVec.at(index));
				cellAllIndex++;
			}
		COMMON_END_ARRAY 

			if(!skinItemSelfVec.empty())
			{
				pHeroCellItem=new IHeroCellItem();
				pHeroCellItem->setStarsNum(qualiyValue);
				pHeroCellItem->setHeroVector(skinItemSelfVec);
				m_vPlayerSelfVector.push_back(pHeroCellItem);
				skinItemSelfVec.clear();
			}
			if(!skinItemAllVec.empty())
			{
				pHeroCellItem=new IHeroCellItem();
				pHeroCellItem->setStarsNum(qualiyValue);
				pHeroCellItem->setHeroVector(skinItemAllVec);
				m_vAllRecordCellList.push_back(pHeroCellItem);
				skinItemAllVec.clear();
			}  
	}
}

void   IHeroillustated_Base_Tag::RefreshSelfHercData()
{ 
	size_t vectorCount=m_vPlayerSelfVector.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorCount)
	delete m_vPlayerSelfVector.at(index);
	COMMON_END_ARRAY
	m_vPlayerSelfVector.clear();

	std::map<int,std::vector<IHeroSkinItem *> >::iterator  inter_iterator= m_mInterMap.begin();
	while(inter_iterator!=m_mInterMap.end())
	{ 
		//自动合成CellList
		RefreshSelfItem(inter_iterator->first,inter_iterator->second);
		++inter_iterator;
	}
}

void   IHeroillustated_Base_Tag::RefreshSelfItem(int  qualiyValue,std::vector<IHeroSkinItem *> & heroItemVec)
{
	if(!heroItemVec.empty())
	{
		IHeroCellItem * pStartItem=new IHeroCellItem();
		pStartItem->setIsStarCellType(true);
		pStartItem->setStarsNum(qualiyValue);

		IHeroCellItem * pHeroCellItem=NULL;
		int  cellSelfIndex=0;
		bool bIsExistActiveCell=false;
		size_t  itemCount=heroItemVec.size();
		std::vector<IHeroSkinItem *> skinItemSelfVec;

		COMMON_BEIGIN_ARRAY(size_t,itemCount)
			if(heroItemVec.at(index)->getIsActived())
			{  
				if(!bIsExistActiveCell)
				{
					m_vPlayerSelfVector.push_back(pStartItem);
					bIsExistActiveCell=true;
				}
				if(cellSelfIndex>=_MODE_CELL_NUM_)
				{
					skinItemSelfVec.push_back(heroItemVec.at(index));
					pHeroCellItem=new IHeroCellItem();
					pHeroCellItem->setStarsNum(qualiyValue);
					pHeroCellItem->setHeroVector(skinItemSelfVec);
					m_vPlayerSelfVector.push_back(pHeroCellItem);
					skinItemSelfVec.clear();
					cellSelfIndex=0;
				} 
				else
				{
					skinItemSelfVec.push_back(heroItemVec.at(index));
					cellSelfIndex++;
				}
			} 
		COMMON_END_ARRAY

			if(!skinItemSelfVec.empty())
			{
				pHeroCellItem=new IHeroCellItem();
				pHeroCellItem->setStarsNum(qualiyValue);
				pHeroCellItem->setHeroVector(skinItemSelfVec);
				m_vPlayerSelfVector.push_back(pHeroCellItem);
				skinItemSelfVec.clear();
			}

		if(!bIsExistActiveCell)
		{
			delete pStartItem;
			pStartItem=NULL;
		}
	}
}





 
//////////////////////////////////////////////////////////////////////////
/*
力量图鉴列表
*/
IHeroIllustrated_Power_Tag::IHeroIllustrated_Power_Tag()
{ 
	m_cIllustratedType=_Illustrated_Power_Type_;
}
IHeroIllustrated_Power_Tag::~IHeroIllustrated_Power_Tag()
{  

}
void  IHeroIllustrated_Power_Tag::AddChild(IHeroSkinItem * pHeroItem)
{  
	if(pHeroItem->getHeroType()==m_cIllustratedType)
	{
		IHeroillustated_Base_Tag::AddChild(pHeroItem);
	}
}
 
  

/*
智力图鉴列表
*/
IHeroIllustrated_Inteligence_Tag::IHeroIllustrated_Inteligence_Tag()
{ 
	m_cIllustratedType=_Illustrated_Inteligence_Type_;
}

IHeroIllustrated_Inteligence_Tag::~IHeroIllustrated_Inteligence_Tag()
{ 
} 
void   IHeroIllustrated_Inteligence_Tag::AddChild(IHeroSkinItem * pHeroItem)
{ 
	if(pHeroItem->getHeroType()==m_cIllustratedType)
	{
		IHeroillustated_Base_Tag::AddChild(pHeroItem);
	}
}
  

/*
敏捷图鉴列表
*/
IHeroIllustrated_Quick_Tag::IHeroIllustrated_Quick_Tag()
{ 
	m_cIllustratedType=_Illustrated_Quick_Type_;
}
IHeroIllustrated_Quick_Tag::~IHeroIllustrated_Quick_Tag()
{ 
}
void   IHeroIllustrated_Quick_Tag::AddChild(IHeroSkinItem * pHeroItem)
{
	if(pHeroItem->getHeroType()==m_cIllustratedType)
	{
		IHeroillustated_Base_Tag::AddChild(pHeroItem);
	}
}
 

 
/*
所有图鉴列表
*/
IHeroIllustated_All_Tag::IHeroIllustated_All_Tag()
{ 
	m_cIllustratedType=_Illustrated_ALL_Type_;
}
IHeroIllustated_All_Tag::~IHeroIllustated_All_Tag()
{ 

}
void   IHeroIllustated_All_Tag::AddChild(IHeroSkinItem * pHeroItem)
{ 
	 IHeroillustated_Base_Tag::AddChild(pHeroItem);
} 
 
 

//////////////////////////////////////////////////////////////////////////
/*
英雄图鉴列表单元
*/
IHeroCellItem::IHeroCellItem()
{
	m_bIsStarCellType=false;
	m_nStarsNum=0;
	m_vHeroVector.clear();
}
IHeroCellItem::~IHeroCellItem()
{
	m_bIsStarCellType=false;
	m_nStarsNum=0;
	m_vHeroVector.clear();
}

 



//////////////////////////////////////////////////////////////////////////
//英雄图鉴Cell List工厂
HeroIllustratedCellListFactory::HeroIllustratedCellListFactory()
{
	m_pHeroIllustratedMap.clear();
}

HeroIllustratedCellListFactory::~HeroIllustratedCellListFactory()
{ 
	Destroy();
}
void  HeroIllustratedCellListFactory::Init()
{
	m_pHeroIllustratedMap.insert(std::map<int,IHeroillustated_Base_Tag *>::value_type(IHeroillustated_Base_Tag::_Illustrated_Power_Type_,new IHeroIllustrated_Power_Tag()));
	m_pHeroIllustratedMap.insert(std::map<int,IHeroillustated_Base_Tag *>::value_type(IHeroillustated_Base_Tag::_Illustrated_Inteligence_Type_,new IHeroIllustrated_Inteligence_Tag()));
	m_pHeroIllustratedMap.insert(std::map<int,IHeroillustated_Base_Tag *>::value_type(IHeroillustated_Base_Tag::_Illustrated_Quick_Type_,new IHeroIllustrated_Quick_Tag()));
	m_pHeroIllustratedMap.insert(std::map<int,IHeroillustated_Base_Tag *>::value_type(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_,new IHeroIllustated_All_Tag()));
}

void  HeroIllustratedCellListFactory::AddChild(IHeroSkinItem * pHeroItem)
{  
	if(pHeroItem!=NULL)
	{ 
		std::map<int,IHeroillustated_Base_Tag *>::iterator illustrated_type=m_pHeroIllustratedMap.begin();
		while(illustrated_type!=m_pHeroIllustratedMap.end())
		{
			illustrated_type->second->AddChild(pHeroItem);
			++illustrated_type;
		}
	}

}

void  HeroIllustratedCellListFactory::UpdateAndSort()
{  
   std::map<int,IHeroillustated_Base_Tag *>::iterator  hero_iter=m_pHeroIllustratedMap.begin();
   while(hero_iter!=m_pHeroIllustratedMap.end())
   { 
	   hero_iter->second->UpdateAndSort();
	   ++hero_iter;
   }
}

IHeroillustated_Base_Tag *  HeroIllustratedCellListFactory::GetHeroIllustratedByType(IByte illustratedType)
{ 
	std::map<int,IHeroillustated_Base_Tag *>::iterator   illustrated_iter=m_pHeroIllustratedMap.find(illustratedType);
	if(illustrated_iter!=m_pHeroIllustratedMap.end())
	{
		return illustrated_iter->second;
	}
	return NULL;
}

void  HeroIllustratedCellListFactory::Destroy()
{
	//to do
	std::map<int,IHeroillustated_Base_Tag *>::iterator illustrated_type=m_pHeroIllustratedMap.begin();
	while(illustrated_type!=m_pHeroIllustratedMap.end())
	{
		delete illustrated_type->second;
		++illustrated_type;
	} 
	m_pHeroIllustratedMap.clear();
}

void  HeroIllustratedCellListFactory::RefreshSelfHeroCells()
{
	std::map<int,IHeroillustated_Base_Tag *>::iterator  hero_iter=m_pHeroIllustratedMap.begin();
	while(hero_iter!=m_pHeroIllustratedMap.end())
	{ 
		hero_iter->second->RefreshSelfHercData();
		++hero_iter;
	}
}

 
 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//DotaHandler
HeroIllustratedDataHandler::HeroIllustratedDataHandler()
{ 
	m_sameGropHeroSkinMap.clear();
	m_pHeroIllustratedCellListFactory=new HeroIllustratedCellListFactory();
}

void   HeroIllustratedDataHandler::ReInitData()
{
	 m_sameGropHeroSkinMap.clear();
	 if(m_pHeroIllustratedCellListFactory)
	 {
		 m_pHeroIllustratedCellListFactory->Destroy();
		 m_pHeroIllustratedCellListFactory->Init();
	 }

}

void  HeroIllustratedDataHandler::RefreshSelfHeroCellsList()
{    
	if(m_pHeroIllustratedCellListFactory)
	m_pHeroIllustratedCellListFactory->RefreshSelfHeroCells();
}


HeroIllustratedDataHandler::~HeroIllustratedDataHandler()
{
	if(m_pHeroIllustratedCellListFactory)
	{
		delete m_pHeroIllustratedCellListFactory;
		m_pHeroIllustratedCellListFactory=NULL;
	}
} 
void HeroIllustratedDataHandler::onDestroy()
{ 

}
bool HeroIllustratedDataHandler::init()
{
	return true;
}
  

void   HeroIllustratedDataHandler::SendReplaceHeroRequest(int newHeroUniqueID, unsigned char heroPos)
{
	CSReplaceHeroRequestPacket  replaceRequest(newHeroUniqueID,heroPos);
	replaceRequest.Send();
	NFC_showCommunicationWating(true);
}

void   HeroIllustratedDataHandler::ActiveHeroSkinHandler(int & newHeroUniqueID)
{
	//to do
	IHeroSkinItem * pHeroSkinItem=RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(newHeroUniqueID);
	if(pHeroSkinItem)
	{
		//Post Start Fresh
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_START_HERO_INFO_SYNC_);
		pHeroSkinItem->setIsActived(true);
		//to do Lock The HeroIllustratedView
		RefreshSelfHeroCellsList();
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_END_HERO_INFO_SYNC_);
	}
}

std::map<int,IHeroSkinItem *> &  HeroIllustratedDataHandler::GetAdvancedGropHeroSkins()
{ 
	return m_sameGropHeroSkinMap;
}

bool   HeroIllustratedDataHandler::IsTeamHeroSame(int index, IHeroSkinItem * heroskin)
{
	for (int i = 0;i<3;i++)
	{
		if (i != index)
		{
			IHeroSkinItem* pHeroSkinItem = NFC_GetTeamHero(i);
			if (pHeroSkinItem != NULL)
			{
				if (pHeroSkinItem->getHeroGroupID() == heroskin->getHeroGroupID())
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool   HeroIllustratedDataHandler::JudgeHeroAdvancedEnable(IHeroSkinItem * pHeroSkinItem)
{  
	m_sameGropHeroSkinMap.clear();
	return RoleHeroSkinsDataHandler::get_instance2()->JudgeHeroAdvancedEnable(pHeroSkinItem);
}

int	   HeroIllustratedDataHandler::GetFirstHightestActiveSkinUID()
{ 
	std::vector<IHeroCellItem *> & vPlayerSelfVector=m_pHeroIllustratedCellListFactory->GetHeroIllustratedByType(IHeroillustated_Base_Tag::_Illustrated_ALL_Type_)->getPlayerSelfCellList();

	size_t cellListSize=vPlayerSelfVector.size();
	for(size_t cellIndex=cellListSize-1;cellIndex>=0;cellIndex--)
	{
		if(vPlayerSelfVector.at(cellIndex)->getIsStarCellType())
		{
			if(cellIndex<cellListSize-1)
			return vPlayerSelfVector.at(cellIndex+1)->getHeroVector().at(0)->getHeroUniqueID();
			else
			return -1;
		}
	}
	return -1; 
}


 

