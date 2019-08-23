// Name :		FriendCheckPlayerInfoPacket.h
// Function:	好友信息数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/CheckPlayerInfoPacket.h"
#include "../include/FriendDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/FriendRefurbishPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
using namespace std;

FriendDataHandler::FriendDataHandler(){
	m_FriendNum = 0;

	m_iShowedTipsWindow = -1;
	m_isFriend_Apply = false;
}

FriendDataHandler::~FriendDataHandler()
{
	if (MyFriendList.size()>0)
	{
		std::vector<FriendInfoData*>::iterator iter = MyFriendList.begin();
		std::vector<FriendInfoData*>::iterator iter_end = MyFriendList.end();
		for (;iter!=iter_end;++iter)
		{
			delete *(iter);
		}
		MyFriendList.clear();
	}

	if (ApplyList.size()>0)
	{
		std::vector<FriendInfoData*>::iterator iter2 = ApplyList.begin();
		std::vector<FriendInfoData*>::iterator iter2_end = ApplyList.end();
		for (;iter2!=iter2_end;++iter2)
		{
			delete *(iter2);
		}
		ApplyList.clear();
	}

	if (NominateList.size()>0)
	{
		std::vector<FriendInfoData*>::iterator iter3 = NominateList.begin();
		std::vector<FriendInfoData*>::iterator iter3_end = NominateList.end();
		for (;iter3!=iter3_end;++iter3)
		{
			delete *(iter3);
		}
		NominateList.clear();
	}
}

void FriendDataHandler::DeleteFriend(int id)
{
	std::vector<FriendInfoData*>::iterator iter_begin = MyFriendList.begin();
	std::vector<FriendInfoData*>::iterator iter_end = MyFriendList.end();

	for (;iter_begin!=iter_end;++iter_begin)
	{
		if ((*iter_begin)->id == id )
		{
			MyFriendList.erase(iter_begin);
			m_FriendNum--;
			break;
		}
	}
	
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_);
}
void FriendDataHandler::AddFriend(int id)
{
	//std::vector<FriendInfoData*>::iterator iter_begin = ApplyList.begin();
	//std::vector<FriendInfoData*>::iterator iter_end = ApplyList.end();

	//for (;iter_begin!=iter_end;++iter_begin)
	//{
	//	if ((*iter_begin)->id == id )
	//	{
	//		FriendInfoData* pData = new FriendInfoData();
	//		pData->id =(*iter_begin)->id;
	//		pData->name =(*iter_begin)->name;
	//		pData->level =(*iter_begin)->level;
	//		pData->iconId =(*iter_begin)->iconId;
	//		MyFriendList.push_back(pData);
	//		ApplyList.erase(iter_begin);
	//		break;
	//	}

	//}
}
void FriendDataHandler::AgreeSingle(int id)
{
	std::vector<FriendInfoData*>::iterator iter_begin = ApplyList.begin();
	std::vector<FriendInfoData*>::iterator iter_end = ApplyList.end();

	for (;iter_begin!=iter_end;++iter_begin)
	{
		if ((*iter_begin)->id == id )
		{
			FriendInfoData* pData = new FriendInfoData();
			pData->id =(*iter_begin)->id;
			pData->name =(*iter_begin)->name;
			pData->level =(*iter_begin)->level;
			pData->iconId =(*iter_begin)->iconId;
			MyFriendList.push_back(pData);
			m_FriendNum++;
			ApplyList.erase(iter_begin);
			break;
		}
	}
	C2SFriendRefurbishPacket packet;
	packet.Send();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_);
}
void FriendDataHandler::IgnoreSingle(int id)
{
	std::vector<FriendInfoData*>::iterator iter_begin = ApplyList.begin();
	std::vector<FriendInfoData*>::iterator iter_end = ApplyList.end();

	for (;iter_begin!=iter_end;++iter_begin)
	{
		if ((*iter_begin)->id == id )
		{
			ApplyList.erase(iter_begin);
			break;
		}
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_);
}
void FriendDataHandler::AgreeAll()
{
	std::vector<FriendInfoData*>::iterator iter_begin = ApplyList.begin();
	std::vector<FriendInfoData*>::iterator iter_end = ApplyList.end();

	for (;iter_begin!=iter_end;++iter_begin)
	{
		FriendInfoData* pData = new FriendInfoData();
		pData->id =(*iter_begin)->id;
		pData->name =(*iter_begin)->name;
		pData->level =(*iter_begin)->level;
		pData->iconId =(*iter_begin)->iconId;
		MyFriendList.push_back(pData);
		m_FriendNum++;
	}

	std::vector<FriendInfoData*>::iterator iter2 = ApplyList.begin();
	std::vector<FriendInfoData*>::iterator iter2_end = ApplyList.end();
	for (;iter2!=iter2_end;++iter2)
	{
		delete *(iter2);
	}
	ApplyList.clear();
	C2SFriendRefurbishPacket packet;
	packet.Send();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_);
}
void FriendDataHandler::IgnoreAll()
{
	std::vector<FriendInfoData*>::iterator iter2 = ApplyList.begin();
	std::vector<FriendInfoData*>::iterator iter2_end = ApplyList.end();
	for (;iter2!=iter2_end;++iter2)
	{
		delete *(iter2);
	}
	ApplyList.clear();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_FRIENDWINDOW_);
}
void FriendDataHandler::handlePacket(IPacket* packet){

}

bool FriendDataHandler::init(){
	return true;
}

void FriendDataHandler::onDestroy(){

	std::vector<FriendInfoData*>::iterator iter = MyFriendList.begin();
	std::vector<FriendInfoData*>::iterator iter_end = MyFriendList.end();
	for (;iter!=iter_end;++iter)
	{
		delete *(iter);
	}
	MyFriendList.clear();

	std::vector<FriendInfoData*>::iterator iter2 = ApplyList.begin();
	std::vector<FriendInfoData*>::iterator iter2_end = ApplyList.end();
	for (;iter2!=iter2_end;++iter2)
	{
		delete *(iter2);
	}
	ApplyList.clear();


	std::vector<FriendInfoData*>::iterator iter3 = NominateList.begin();
	std::vector<FriendInfoData*>::iterator iter3_end = NominateList.end();
	for (;iter3!=iter3_end;++iter3)
	{
		delete *(iter3);
	}
	NominateList.clear();

	ResetSelectPlayerInfo();
}

void FriendDataHandler::ResetSelectPlayerInfo(){
	std::map<int,BagEquipData*>::iterator iter = m_SelectPlayerInfo.equips.begin();
	std::map<int,BagEquipData*>::iterator iter_end = m_SelectPlayerInfo.equips.end();
	for(;iter != iter_end; ++iter){
		BagEquipData* data = iter->second;
		delete data;
		data = NULL;
	}
	m_SelectPlayerInfo.equips.clear();
	
	std::map<int,SkillItem*>::iterator iter2 = m_SelectPlayerInfo.skills.begin();
	std::map<int,SkillItem*>::iterator iter2_end = m_SelectPlayerInfo.skills.end();
	for(;iter2 != iter2_end; ++iter2){
		SkillItem* data = iter2->second;
		delete data;
		data = NULL;
	}
	m_SelectPlayerInfo.skills.clear();
	
	std::map<int,SoulEquipItem*>::iterator iter3 = m_SelectPlayerInfo.soulStatus.begin();
	std::map<int,SoulEquipItem*>::iterator iter3_end = m_SelectPlayerInfo.soulStatus.end();
	for(;iter3 != iter3_end; ++iter3){
		SoulEquipItem* data = iter3->second;
		delete data;
		data = NULL;
	}
	m_SelectPlayerInfo.soulStatus.clear();

	std::vector<IHeroSoulItem*>::iterator iter4 = m_SelectPlayerInfo.souls.begin();
	std::vector<IHeroSoulItem*>::iterator iter4_end = m_SelectPlayerInfo.souls.end();
	for(; iter4 != iter4_end; ++iter4){
		delete *(iter4);
	}
	m_SelectPlayerInfo.souls.clear();

}

void FriendDataHandler::ToServerCheckPlayerInfo(int playerid, int windowType, bool _isFriend_Apply)
{
	m_iShowedTipsWindow = windowType;
	m_isFriend_Apply = _isFriend_Apply;

	ResetSelectPlayerInfo();

	//C2SFriendCheckPlayerInfoPacket pack(playerid);
	C2SCheckPlayerInfoPacket pack(playerid);
	pack.Send();

	NFC_showCommunicationWating(true);
}


void FriendDataHandler::decodeCheckPlayerDataPacket(cobra_win::DPacket & packet){
	LOGGERSYSTEM->LogDebug("In Function decodeCheckPlayerDataPacket");
	packet>>m_SelectPlayerInfo.id;
	NFC_ParsePacketString(packet,m_SelectPlayerInfo.name);
	packet>>m_SelectPlayerInfo.level;
	packet>>m_SelectPlayerInfo.shapeId;
	NFC_ParsePacketString(packet,m_SelectPlayerInfo.shapeName);
	packet>>m_SelectPlayerInfo.shapeLevel;
	packet>>m_SelectPlayerInfo.hp;
	packet>>m_SelectPlayerInfo.mp;
	packet>>m_SelectPlayerInfo.minAttack;
	packet>>m_SelectPlayerInfo.maxAttack;
	packet>>m_SelectPlayerInfo.speed;
	packet>>m_SelectPlayerInfo.hit;
	packet>>m_SelectPlayerInfo.dodge;
	packet>>m_SelectPlayerInfo.exposeArmor;
	packet>>m_SelectPlayerInfo.armor;
	packet>>m_SelectPlayerInfo.cirt;
	packet>>m_SelectPlayerInfo.uncirt;
	packet>>m_SelectPlayerInfo.btlCapa;
	packet>>m_SelectPlayerInfo.strength;
	packet>>m_SelectPlayerInfo.agility;
	packet>>m_SelectPlayerInfo.intelligence;
	LOGGERSYSTEM->LogDebug("After INT");

	IByte equipCount;
	packet>>equipCount;
	for(int i = 0; i < equipCount; i++){
		BagEquipData* equipData = new BagEquipData();
		IByte index, hasEquip;
		packet>>index;
		packet>>hasEquip;
		equipData->index_ = index;
		if( hasEquip == 1){
			packet>>equipData->template_->catogory_;
			packet>>equipData->template_->type_;
			packet>>equipData->template_->canUse_;
			packet>>equipData->template_->templateid_;
			NFC_ParsePacketString(packet,equipData->template_->name_);
			NFC_ParsePacketString(packet,equipData->template_->description_);
			packet>>equipData->template_->level_;
			packet>>equipData->template_->maxLevel_;
			packet>>equipData->template_->quality_;
			packet>>equipData->template_->iconId_;
			packet>>equipData->template_->iconBigId_;
			packet>>equipData->template_->maxCount_;
			packet>>equipData->template_->price_;
			packet>>equipData->template_->baseAttrType_;
			equipData->decodePacketData(packet);
			equipData->isEquiped_ = true;
		}
		m_SelectPlayerInfo.equips[index] = equipData;
	}
	LOGGERSYSTEM->LogDebug("After Equip");

	IByte skillCount;
	packet>>skillCount;

	for(int i = 0; i < skillCount; i++){
		SkillItem* skillData = new SkillItem();
		IByte index;
		packet>>index;
		IByte level;
		packet>>level;
		unsigned short skillID;
		packet>>skillID;
		short _skillID = (short)skillID;
		skillData->skillID = _skillID;
		if(_skillID > 0){
			packet>>skillData->skillIconID;
			packet>>skillData->skillType;
			packet>>skillData->mpConsumer;
			packet>>skillData->ispro;
			NFC_ParsePacketString(packet,skillData->skillDescription);
			NFC_ParsePacketString(packet,skillData->skillDescription2);
			NFC_ParsePacketString(packet,skillData->skillTriggerRate);
			NFC_ParsePacketString(packet,skillData->skillTriggerCondition);
		}
		m_SelectPlayerInfo.skills[index] = skillData;
	}
	LOGGERSYSTEM->LogDebug("After Skill");

	unsigned short soulCount;
	packet>>soulCount;
	for(int i = 0; i < soulCount; i++){
		IByte index,isOpen;
		int level = 0;
		packet>>index;
		packet>>isOpen;
		if(isOpen == 0){
			packet>>level;
		}
		SoulEquipItem* soulItem = new SoulEquipItem(index,isOpen,level);
		m_SelectPlayerInfo.soulStatus[index] = soulItem;
		LOGGERSYSTEM->LogDebug("Soul: %d, %d, %d",soulItem->m_uHeroSoulEquipIndex, soulItem->m_uHeroSoulEquipIsOpen, soulItem->m_uHeroSoulEquipOpenLevel);
	}
	LOGGERSYSTEM->LogDebug("After SoulCount");

	unsigned short soulinfo;
	packet>>soulinfo;
	for(int i = 0; i < soulinfo; i++){
		IHeroSoulItem* heroSoulItem = new IHeroSoulItem();
		heroSoulItem->decodePacket(packet);
		m_SelectPlayerInfo.souls.push_back(heroSoulItem);
		LOGGERSYSTEM->LogDebug("SoulInfo: %d, %d, %s",heroSoulItem->getHeroSoulEquipIndex(), heroSoulItem->getHeroSoulBufferID(), heroSoulItem->getHeroSoulBufferName().c_str());
	}
	LOGGERSYSTEM->LogDebug("After SoulInfo");




}