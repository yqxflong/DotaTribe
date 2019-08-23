//Name:EquipStrengthenDataHandler.h
//Author:尹强
//Function:装备强化

#include <cocos2d.h>
#include "../include/EquipStrengthenDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/CSMapTable.h"
#include "../include/EquipmentLvUpDataHandler.h"
 
using namespace std;

EquipStrengthenDataHandler::EquipStrengthenDataHandler(){
	ClearEquipList();
	m_HeroIndex = 0;
}
	
void EquipStrengthenDataHandler::onDestroy(){
	ClearEquipList();
	m_HeroIndex = 0;
}

bool EquipStrengthenDataHandler::init(){
	return true;
}

	/*
		过滤装备for装备升级
	*/
void EquipStrengthenDataHandler::LoadEquipList_EquipLvUp(int heroindex){
	ClearEquipList();
	vector<BagEquipData*> vec;
	for (int i = 0;i<3;i++)
	{
		if (NFC_GetHeroEquipManager(i) != NULL)
		{
			vector<BagEquipData*> tempvector = NFC_GetHeroEquipManager(i)->getRoleEquipsForStrengthen();
			vector<BagEquipData*>::iterator it = tempvector.begin();
			vector<BagEquipData*>::iterator it_end = tempvector.end();
			for (; it != it_end;it++)
			{
				if (*it)
				{
					(*it)->RoleHeroindexEquip_ = i;
				}
			}
			vec.insert(vec.end(), tempvector.begin(),tempvector.end() );
		}
		else
		{
			break;
		}
		//人物装备
	}
	
	//装入仅已装备容器
	RoleEquipList_=vec;
	//将背包装备装入容器vec
	_loadBagEquipsToVec(vec);
	_removeExpBall(vec);
	_removeCardInCostList(vec);
	EquipList_=vec;
}

	/*
		过滤装备for装备进阶
		去除：白卡
	*/
void EquipStrengthenDataHandler::LoadEquipList_Progress(int heroindex){
	ClearEquipList();
	vector<BagEquipData*> vec;
	for (int i = 0; i < 3; i++)
	{
		if (NFC_GetHeroEquipManager(i) != NULL)
		{
			vector<BagEquipData*> tempvector = NFC_GetHeroEquipManager(i)->getRoleEquipsForStrengthen();
			vector<BagEquipData*>::iterator it = tempvector.begin();
			vector<BagEquipData*>::iterator it_end = tempvector.end();
			for (; it != it_end; it++)
			{
				if (*it)
				{
					(*it)->RoleHeroindexEquip_ = i;
				}
			}
			vec.insert(vec.end(), tempvector.begin(), tempvector.end());
		}
		else
		{
			break;
		}
		//人物装备
	}
	//装入仅已装备容器
	_removeWhiteCard(vec);
	RoleEquipList_=vec;
	//将背包装备装入容器vec
	_loadBagEquipsToVec(vec);
	_removeWhiteCard(vec);
	EquipList_=vec;
}
	/*
		过滤装备for装备洗练
		去除：白卡
	*/
void EquipStrengthenDataHandler::LoadEquipList_Train(int heroindex){
	ClearEquipList();
	vector<BagEquipData*> vec;
	for (int i = 0; i < 3; i++)
	{
		if (NFC_GetHeroEquipManager(i) != NULL)
		{
			vector<BagEquipData*> tempvector = NFC_GetHeroEquipManager(i)->getRoleEquipsForStrengthen();
			vector<BagEquipData*>::iterator it = tempvector.begin();
			vector<BagEquipData*>::iterator it_end = tempvector.end();
			for (; it != it_end; it++)
			{
				if (*it)
				{
					(*it)->RoleHeroindexEquip_ = i;
				}
			}
			vec.insert(vec.end(), tempvector.begin(), tempvector.end());
		}
		else
		{
			break;
		}
		//人物装备
	}
	_removeWhiteCard(vec);
	RoleEquipList_=vec;
	/*
		将背包装备装入容器vec
	*/
	_loadBagEquipsToVec(vec);
	_removeWhiteCard(vec);
	EquipList_=vec;
}


void EquipStrengthenDataHandler::LoadEquipList_Recast()
{
	ClearEquipList();
	EquipList_ = BagEquipDataHandler::get_instance2()->getRoleEquipsForEquipRecast(); 
}


	/*
		清空容器
	*/
void EquipStrengthenDataHandler::ClearEquipList(){
	RoleEquipList_.clear();
	EquipList_.clear();
}

	/*
		是否存在该装备
		#已装备
	*/
bool EquipStrengthenDataHandler::CheckTheEquipExisted_RoleEquip(int equipID){
	bool ret=false;
	for (int i=0;i<RoleEquipList_.size();i++)
	{
		if (RoleEquipList_[i]->id_==equipID)
			ret=true;
	}
	return ret;
}

	/*
		是否存在该装备
	*/
bool EquipStrengthenDataHandler::CheckTheEquipExisted_All(int equipID){
	bool ret=false;
	for (int i=0;i<EquipList_.size();i++)
	{
		if (EquipList_[i]->id_==equipID)
			ret=true;
	}
	return ret;
}


void EquipStrengthenDataHandler::_loadBagEquipsToVec(std::vector<BagEquipData*>& vec){
	BAGEQUIPDATAHANDLER->reorderEquipListForEquipStrengthen();
	vector<BagEquipData*>::iterator it=BAGEQUIPDATAHANDLER->m_vecList.begin();
	vector<BagEquipData*>::iterator it_end=BAGEQUIPDATAHANDLER->m_vecList.end();
	for (;it!=it_end;it++)
	{
		vec.push_back(*it);
	}
}

void EquipStrengthenDataHandler::_removeExpBall(std::vector<BagEquipData*>& vec){
	vector<BagEquipData*>::iterator it=vec.begin();
	for (;it!=vec.end();)
	{
		if((*it)->template_->canUse_==0){
			it=vec.erase(it);
		}else{
			it++;
		}
	}
}

void EquipStrengthenDataHandler::_removeWhiteCard(std::vector<BagEquipData*>& vec){
	vector<BagEquipData*>::iterator it=vec.begin();
	for (;it!=vec.end();)
	{
		if((*it)->template_->quality_<=kCARD_2_STAR){
			it=vec.erase(it);
		}else{
			it++;
		}
	}
}

void EquipStrengthenDataHandler::_removeMaxAdvancedCard(std::vector<BagEquipData*>& vec){
	vector<BagEquipData*>::iterator it=vec.begin();
	for (;it!=vec.end();)
	{
		if((*it)->advanceLevel_>=(*it)->advanceLevelMax_){
			it=vec.erase(it);
		}else{
			it++;
		}
	}
}

void EquipStrengthenDataHandler::_removeMaxLvCard(std::vector<BagEquipData*>& vec){
	vector<BagEquipData*>::iterator it=vec.begin();
	for (;it!=vec.end();)
	{
		if((*it)->level_>=(*it)->levelMax_){
			it=vec.erase(it);
		}else{
			it++;
		}
	}
}


//装备升级专用
void EquipStrengthenDataHandler::_removeCardInCostList(std::vector<BagEquipData*>& vec){
	vector<int>::iterator it1=EquipmentLvUpDataHandler::get_instance2()->vecEquipCostCard.begin();
	vector<int>::iterator it1_end=EquipmentLvUpDataHandler::get_instance2()->vecEquipCostCard.end();
	for (;it1!=it1_end;it1++)
	{
		vector<BagEquipData*>::iterator it=vec.begin();
		vector<BagEquipData*>::iterator it_end=vec.end();
		for (;it!=it_end;)
		{
			vector<BagEquipData*>::iterator tmp=it++;
			if((*tmp)->id_==(*it1)){
				vec.erase(tmp);
				break;
			}
		}
	}
}



