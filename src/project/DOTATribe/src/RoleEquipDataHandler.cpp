//Name： RoleEquipDataHandler
//Function：管理英雄的装备
//Author：Johny

#include <cocos2d.h>
#include <algorithm> 
#include "../include/RoleEquipDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CSChangEquipPacket.h"
#include "../include/CSOffEquipPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/GuideSystem.h"

using namespace std;

void RoleEquipData::refreshEquipData(BagEquipData * bed)
{
	if(bed != NULL)
	{
		bed->isEquiped_ = 1;
		if(this->equipdata_)
		{
			this->equipdata_->__set(bed);
			bed->__delectflag = true;
		}
		else
		{
			this->equipdata_ = bed;
		}
	}
}

RoleEquipDataHandler::RoleEquipDataHandler(){
	m_mapEquipList.clear();
	m_offequip_type=-1;
	HeroEquip_Tab_IsSelected=-1;
}

bool RoleEquipDataHandler::init(){

	return true;
}

void RoleEquipDataHandler::onDestroy(){

	std::map<int,RoleEquipData*>::iterator iter=m_mapEquipList.begin();
	while(iter!=m_mapEquipList.end())
	{ 
		delete iter->second;
		iter++;
	}
	m_mapEquipList.clear();
}

void RoleEquipDataHandler::decodePacketData(cobra_win::DPacket & packet){
	LOGGERSYSTEM->LogInfo("IHeroSkinItem-- decodePacket_Equip	--start");

	unsigned char equipCount;
	BagTemplateBase * btb = NULL;
	BagEquipData * bed = NULL;
	RoleEquipData * red = NULL;
	unsigned char index = 0;
	unsigned char hasequip = 0;

	packet>>equipCount;		//装备数量
	for (unsigned char i=0;i<equipCount;i++)
	{
		packet>>index;
		packet>>hasequip;

		RoleEquipData * red = new RoleEquipData();

		if(hasequip)
		{
			btb = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);
			bed = new BagEquipData((EquipTemplate *)btb);
			bed->decodePacketData(packet);
		}

		red->index_ = index;
		red->hasEquip_ = hasequip;
		red->refreshEquipData(bed);
		if(bed && bed->__delectflag)
		{
			delete bed;
		}
		bed = NULL;
		m_mapEquipList.insert(std::map<int,RoleEquipData*>::value_type(red->index_,red));
	}
	assert(m_mapEquipList.size()==8);
	LOGGERSYSTEM->LogInfo("IHeroSkinItem-- decodePacket_Equip	--end");
}


/*
	@func1
	@根据id在身上找指定装备
*/
BagEquipData * RoleEquipDataHandler::getEquipById(int id)
{
	BagEquipData * bb = NULL;
	map<int,RoleEquipData*>::iterator it=m_mapEquipList.begin();
	map<int,RoleEquipData*>::iterator it_end=m_mapEquipList.end();
	for (;it!=it_end;it++)
	{
		if(it->second->hasEquip_&&it->second->equipdata_->id_ == id)
		{	
			bb = it->second->equipdata_;
			break;
		}
	}
	return bb;
}

/*
	@func2
	@根据位置在身上找指定装备
*/
BagEquipData * RoleEquipDataHandler::getEquipByType(int etype){
	RoleEquipData* rd=m_mapEquipList[etype];
	if (rd->hasEquip_)
		return rd->equipdata_;

	return NULL;
}

/*
	@func3
	@获得人物所有装备
*/
std::vector<BagEquipData*> RoleEquipDataHandler::getRoleEquips(){
	vector<BagEquipData*> vec;
	map<int,RoleEquipData*>::iterator it=m_mapEquipList.begin();
	map<int,RoleEquipData*>::iterator it_end=m_mapEquipList.end();
	for (;it!=it_end;it++)
	{
		RoleEquipData* rr=it->second; 
		if (rr->hasEquip_)
			vec.push_back(rr->equipdata_);
	}
	return vec;
}

/*
	@func4
	@升序排列
*/
bool Compare_RoleEquips_Ascend(const BagEquipData* it1,const BagEquipData* it2){
	return it1->template_->type_<it2->template_->type_;
}

std::vector<BagEquipData*> RoleEquipDataHandler::getRoleEquipsByType(){
	vector<BagEquipData*> vec=getRoleEquips();
	std::sort(vec.begin(),vec.end(),Compare_RoleEquips_Ascend);
	return vec;
}

/*
	@func5
	@升序排列
*/
bool Compare_RoleEquips_Stren(BagEquipData* it1,BagEquipData* it2){
	int quality_1=it1->template_->quality_;
	int quality_2=it2->template_->quality_;
	if(quality_1>quality_2)
		return true;
	else if(quality_1==quality_2){
		int type_1=it1->template_->type_;
		int type_2=it2->template_->type_;
		if (type_1<type_2)
			return true;
		else if(type_1==type_2)
			return it1->level_>it2->level_;
		else
			return false;
	}else
		return false;
}
std::vector<BagEquipData*> RoleEquipDataHandler::getRoleEquipsForStrengthen(){
	vector<BagEquipData*> vec=getRoleEquips();
	std::sort(vec.begin(),vec.end(),Compare_RoleEquips_Stren);
	return vec;
}


/*
	@func6
	@获取一件默认升级的装备
*/
BagEquipData* RoleEquipDataHandler::GetDefaultRoleEquip_EquipLvup(){
	std::vector<BagEquipData*> vec=getRoleEquipsByType();
	if (vec.size()>0)
		return vec.front();
	else
		return NULL;
}

/*
	@func7
	@检查是否有装备可以强化
*/
bool RoleEquipDataHandler::CheckAllRoleEquipsCanTopup(){
	map<int,RoleEquipData*>::iterator it=m_mapEquipList.begin();
	for (;it!=m_mapEquipList.end();it++)
	{
		RoleEquipData* dd=it->second;
		if (!dd->hasEquip_)
			continue;
		if (dd->equipdata_->level_<dd->equipdata_->levelMax_&&dd->equipdata_->level_<ROLEINFODATAHANDLER->m_pRIData->level_)
			return true;
	}

	return false;
}

//begin:下装备
void RoleEquipDataHandler::OffEquip_Request(int equipid,int heroPos){
	assert(equipid>=0);
	CSOffEquipPacket packet(kOFFEQUIPPACKET,equipid,heroPos);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void RoleEquipDataHandler::decodePacketData_OffEquip(cobra_win::DPacket & packet){
	unsigned char equiptype;
	packet>>equiptype;
	OffEquip_Local(equiptype);
}


void RoleEquipDataHandler::HanldeAfterOffEquip(){
	NFC_showCommunicationWating(false);
}

void RoleEquipDataHandler::OffEquip_Local(int equipType){
	RoleEquipData* re=m_mapEquipList[equipType];
	re->hasEquip_=0;
}
//end

//begin:换装
void RoleEquipDataHandler::ChangeEquip_Request(int equipid,int heroPos){
	assert(equipid>=0);
	CSChangeEquipPacket packet(kCHANGEEQUIPPACKET,equipid,heroPos);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void RoleEquipDataHandler::decodePacketData_ChangeEquip(cobra_win::DPacket & packet){
	unsigned char tmp_clen=0;
	packet>>tmp_clen;
	ROLEINFODATAHANDLER->m_pRIData->attribute_->mapPropertyList_.clear();
	for (int i=0;i<tmp_clen;i++)
	{
		unsigned char atype;	//0~13
		packet>>atype;
		int avalue;
		packet>>avalue;
		ROLEINFODATAHANDLER->m_pRIData->attribute_->mapPropertyList_.insert(std::map<int,int>::value_type(atype,avalue));
	}
}

void RoleEquipDataHandler::HanldeAfterChangeEquip(){
	NFC_showCommunicationWating(false);
	GUIDESYSTEM->Next();
}
//end