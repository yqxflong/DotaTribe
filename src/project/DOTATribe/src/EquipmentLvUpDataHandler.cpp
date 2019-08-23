//Name:EquipmentLvUpDataHandler.h
//Author:��ǿ
//Function:װ������������

#include <cocos2d.h>
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/EquipmentLvUpSelectCardPacket.h"
#include "../include/EquipmentLvUpPacket.h"
#include <stdlib.h>
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"
#include "../include/NewEquipremindDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/EquipStrengthenDataHandler.h"
void EquipSwallowData::decodePacket(cobra_win::DPacket & packet)
{
	packet>>this->equipId;
	packet>>this->swallowType;
	packet>>this->addExp;
	packet>>this->useMoney;

}

EquipmentLvUpData::EquipmentLvUpData()
{
	swallowData.clear();
}

EquipmentLvUpData::~EquipmentLvUpData()
{
	for(size_t i = 0; i < swallowData.size(); ++i)
	{
		delete swallowData[i];
	}
	swallowData.clear();
}

void EquipmentLvUpData::decodePacket(cobra_win::DPacket & packet)
{
	packet>>this->level;
	packet>>this->equipExp;
	packet>>this->equipMaxExp;
	packet>>this->mainAttriMin;
	packet>>this->mainAttriMax;

	unsigned char tmp_clen;
	packet>>tmp_clen;
	attribute.mapPropertyList_.clear();
	for (int i=0;i<tmp_clen;i++)
	{
		unsigned char atype;	//0~13
		packet>>atype;
		int avalue;
		packet>>avalue;
		attribute.mapPropertyList_.insert(std::map<int,int>::value_type(atype,avalue));
	}
	//��װ��ͨ������MAX
	packet>>tmp_clen;
	attributeMax.mapPropertyList_.clear();
	for (int i=0;i<tmp_clen;i++)
	{
		unsigned char atype;	//0~13
		packet>>atype;
		int avalue;
		packet>>avalue;
		attributeMax.mapPropertyList_.insert(std::map<int,int>::value_type(atype,avalue));
	}
	//
	this->swallowData.clear();
	packet>>this->changeValue;
	packet>>this->changeValueMax;
	packet>>this->swallowCount;
	for(int i = 0; i < this->swallowCount; ++i)
	{
		EquipSwallowData * esd = new EquipSwallowData();
		esd->decodePacket(packet);
		this->swallowData.push_back(esd);
	}
}

//~~~~~~~~~EquipmentLvUpDataHandler~~~~~~~~~~~
EquipmentLvUpDataHandler::EquipmentLvUpDataHandler()
{
	ClearData();
	equipLvUpData = NULL;//��ֵΪNULL���ⲿ��ֵ���˴�delete
}

EquipmentLvUpDataHandler::~EquipmentLvUpDataHandler()
{
	if(equipLvUpData != NULL)
	{
		delete equipLvUpData;
		equipLvUpData = NULL;
	}
	vecEquipCostCard.clear();
	vecEquipCostMoney.clear();
}

void EquipmentLvUpDataHandler::handlePacket(IPacket* packet)
{

}

void EquipmentLvUpDataHandler::onDestroy()
{
	//add by fangjun @ 2013-12-23, for bug 1738
	ClearData();
}


bool EquipmentLvUpDataHandler::init()
{
	return true;
}

BagEquipData * EquipmentLvUpDataHandler::GetEquipById(int id)
{
	BagEquipData * bed = NULL;
	if(NULL == bed)
		bed = BAGEQUIPDATAHANDLER->getEquipById(id);
	if(NULL == bed){
		for (int i = 0; i < 3; i++)
		{
			RoleEquipDataHandler* pRole = NFC_GetHeroEquipManager(i);

			if (pRole != NULL)
			{
				bed = pRole->getEquipById(id);
				if (pRole->getEquipById(id))
				{
					return pRole->getEquipById(id);
				}
			}
			else
			{
				return NULL;
			}
		}
	}
	return bed;
}

BagEquipData * EquipmentLvUpDataHandler::GetMainCard()
{
	return GetEquipById(this->selectedEquipId);
}

bool EquipmentLvUpDataHandler::HasPurpleCard()
{
	bool has = false;
	for(int i = 0; i < (int)vecEquipCostCard.size(); ++i)
	{
		if(BAGEQUIPDATAHANDLER->getEquipByAllEquips(vecEquipCostCard[i])->template_->quality_ == kCARD_5_STAR)
		{
			has = true;
			break;
		}
	}
	return has;
}

bool EquipmentLvUpDataHandler::HasOrangeCard()
{
	bool has = false;
	for(int i = 0; i < (int)vecEquipCostCard.size(); ++i)
	{
		if(BAGEQUIPDATAHANDLER->getEquipByAllEquips(vecEquipCostCard[i])->template_->quality_ == kCARD_6_STAR)
		{
			has = true;
			break;
		}
	}
	return has;
}

void EquipmentLvUpDataHandler::toServerSelectCard()
{
	std::vector<int> allId;
	allId.clear();
	for(size_t i = 0; i < vecEquipCostCard.size(); ++i)
	{
		allId.push_back(vecEquipCostCard[i]);
	}
	if(allId.size() > 0)
	{
		CSEquipmentLvUpSelectCardPacket packet(allId.size(), allId);
		packet.Send();
	}
}

void EquipmentLvUpDataHandler::toServerLvUp()
{
	std::vector<int> allId;
	allId.clear();
	for(size_t i = 0; i < vecEquipCostCard.size(); ++i)
	{
		//����װ����ʱ���Ƿ��е�ǰ��ʾ��װ��
		NEWEQUIPREMINDDATAHANDLER->SwallowEquip(vecEquipCostCard[i]);
		allId.push_back(vecEquipCostCard[i]);
	}
	CSEquipmentLvUpPacket packet(selectedEquipId, allId.size(), allId);
	packet.Send();
	//��ʾ�ȴ�
	NFC_showCommunicationWating(true);
}

/*
	�����洢����from�������ݿ�����to
*/
void EquipmentLvUpDataHandler::CopyStore(BagEquipData * to,const BagEquipData * from)
{

	to->template_->iconId_ = from->template_->iconId_;
	to->template_->iconBigId_ = from->template_->iconBigId_;
	to->template_->catogory_ = from->template_->catogory_;
	to->template_->name_ = "";
	to->template_->name_.assign(from->template_->name_);
	to->template_->quality_ = from->template_->quality_;
	to->template_->baseAttrType_ = from->template_->baseAttrType_;
	to->template_->type_ = from->template_->type_;

	to->id_ = from->id_;
	to->level_ = from->level_;
	to->exp_ = from->exp_;
	to->maxexp_ = from->maxexp_;
	to->mainAttriValue = from->mainAttriValue;
	to->mainAttriValueMax = from->mainAttriValueMax;
	to->isEquiped_ = from->isEquiped_;

	std::map<int, int>::iterator it = from->attribute_->mapPropertyList_.begin();
	std::map<int, int>::iterator it_end = from->attribute_->mapPropertyList_.end();
	to->attribute_->mapPropertyList_.clear();
	for(; it != it_end; ++it)
	{
		to->attribute_->mapPropertyList_.insert(std::map<int, int>::value_type(it->first, it->second));
	}

	it = from->attributeMAX_->mapPropertyList_.begin();
	it_end = from->attributeMAX_->mapPropertyList_.end();
	to->attributeMAX_->mapPropertyList_.clear();
	for(; it != it_end; ++it)
	{
		to->attributeMAX_->mapPropertyList_.insert(std::map<int, int>::value_type(it->first, it->second));
	}
}

	/*
		����װ������������
	*/
void EquipmentLvUpDataHandler::HandleAfterEquipLvup(){
	//���صȴ�
	NFC_showCommunicationWating(false);
	//
	ResetMoney();
	RemoveCardsFromCostList();
	ChangeEquipInfoByLvUpResult();
}

	/*
		���ز��б���ȥ���Ե��Ŀ���
	*/
void EquipmentLvUpDataHandler::RemoveCardsFromCostList(){
	int swallowCount=this->equipLvUpData->swallowData.size();
	if(swallowCount==this->vecEquipCostCard.size())
		this->vecEquipCostCard.clear();
	else{
		for (int i=0;i<swallowCount;i++)
		{
			EquipSwallowData* sd=(this->equipLvUpData->swallowData)[i];
			int equipID=sd->equipId;
			vector<int>::iterator it=this->vecEquipCostCard.begin();
			vector<int>::iterator it_end=this->vecEquipCostCard.end();
			for(;it!=it_end;)
			{
				vector<int>::iterator tmp=it;
				it++;
				if ((*tmp)==equipID){
					this->vecEquipCostCard.erase(tmp);
					break;
				}
			}
		}
		for(size_t i = 0; i < this->equipLvUpData->swallowData.size(); ++i)
			delete this->equipLvUpData->swallowData[i];
		this->equipLvUpData->swallowData.clear();
	}
}

void EquipmentLvUpDataHandler::ChangeEquipInfoByLvUpResult()
{
	BagEquipData * bed = GetMainCard();
	if(bed && equipLvUpData)
	{
		bed->level_ = equipLvUpData->level;
		bed->exp_ = equipLvUpData->equipExp;
		bed->maxexp_ = equipLvUpData->equipMaxExp;
		bed->mainAttriValue = equipLvUpData->mainAttriMin;
		bed->mainAttriValueMax = equipLvUpData->mainAttriMax;

		bed->attribute_->mapPropertyList_.clear();
		std::map<int, int>::iterator it = equipLvUpData->attribute.mapPropertyList_.begin();
		std::map<int, int>::iterator it_e = equipLvUpData->attribute.mapPropertyList_.end();
		for(; it != it_e; ++it)
		{
			bed->attribute_->mapPropertyList_.insert(std::map<int, int>::value_type(it->first, it->second));
		}

		bed->attributeMAX_->mapPropertyList_.clear();
		it = equipLvUpData->attributeMax.mapPropertyList_.begin();
		it_e = equipLvUpData->attributeMax.mapPropertyList_.end();
		for(; it != it_e; ++it)
		{
			bed->attributeMAX_->mapPropertyList_.insert(std::map<int, int>::value_type(it->first, it->second));
		}

	}
}

	/*
		����Ƿ��������б���
	*/
bool EquipmentLvUpDataHandler::isInCostList(int equipID){
	for (int i=0;i<(int)vecEquipCostCard.size();i++)
	{
		if (vecEquipCostCard[i]==equipID)
			return true;
	}
	return false;
}

	/*
		����Ƿ��������б���
	*/
bool EquipmentLvUpDataHandler::isInMainList(int equipID){
	for(int i = 0; i < (int)EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size(); ++i)
	{
		if(EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard[i]==equipID)
			return true;
	}
	return false;
}

	/*
		���cost�б��Ƿ�����װ����
	*/
void EquipmentLvUpDataHandler::checkCostList(){
	std::vector<int>::iterator it=vecEquipCostCard.begin();
	std::vector<int>::iterator it_end=vecEquipCostCard.end();
	for (;it!=it_end;)
	{
		std::vector<int>::iterator tmp=it;
		it++;
		BagEquipData* bb=BAGEQUIPDATAHANDLER->getEquipByAllEquips(*tmp);
		if (bb->isEquiped_){
			vecEquipCostCard.erase(tmp);
			it=vecEquipCostCard.begin();
			it_end=vecEquipCostCard.end();
		}
	}
}

	/*
		�������
	*/
void EquipmentLvUpDataHandler::ClearData(){
	selectedEquipId = -1;
	vecEquipCostCard.clear();
	vecEquipCostMoney.clear();
	needMoneyAll = 0;
	
}

	/*
		��ʼ��װ�������ز��б�
	*/
std::vector<EquipCardsStructure> EquipmentLvUpDataHandler::GetEquipCostCardList(){
	std::vector<EquipCardsStructure>cardlist;
	//���ݲ�����Ҫ���ǵ���ѡ���װ������װ���Ĳ����ٱ������زĿ���
	//4�Ǽ�����Ʒ��װ������ѡ��Ϊ���ɲ���
	//ȥ����װ����
	for (int i=0;i<(int)BAGEQUIPDATAHANDLER->m_vecList.size();i++)
	{
		BagEquipData* bb=BAGEQUIPDATAHANDLER->m_vecList[i];
		//ȥ����ѡ�ģ�����ɫ��
		//4��Ʒ�����ϲ�����Ϊ�ز�
		if( bb->id_ != EQUIPMENTLVUPDATAHANDLER->selectedEquipId && bb->template_->quality_ < 3 )
		{
			EquipCardsStructure card;
			card.data=bb;
			card.isSelected=EQUIPMENTLVUPDATAHANDLER->isInCostList(bb->id_);
			cardlist.push_back(card);
		}
	}
	return cardlist;
}

	/*
		�������軨��
	*/
void EquipmentLvUpDataHandler::ResetMoney(){
	int swallowcount=equipLvUpData->swallowData.size();
	if (swallowcount==vecEquipCostCard.size())
		needMoneyAll=0;
	else{
		int cost=0;
		for (int i=0;i<swallowcount;i++)
		{
			EquipSwallowData* dd=equipLvUpData->swallowData[i];
			cost+=dd->useMoney;
		}
		needMoneyAll-=cost;
	}
}

	/*
		�����ĵȼ��Ƿ�������������
	*/
bool EquipmentLvUpDataHandler::IsMainCardMeetLevelCondition(){
	BagEquipData* bb=GetMainCard();
	if (bb){
		bool condition1=bb->level_<ROLEINFODATAHANDLER->m_pRIData->level_*2;
		bool condition2=bb->level_<bb->levelMax_;
		if(condition1&&condition2)
			return true;
	}
	return false;
}

	/*
		��黨���Ƿ��㹻
	*/
bool EquipmentLvUpDataHandler::isMoneyEnough(){
		bool condtion1=needMoneyAll<=ROLEINFODATAHANDLER->m_pRIData->money_;
		bool condtion2=EQUIPMENTLVUPDATAHANDLER->needMoneyAll>0;
		return condtion1&&condtion2;
}
