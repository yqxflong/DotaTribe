//Name：BagEquipData
//Function：管理背包装备数据
//Written By：尹强

#include <cocos2d.h>
#include "../include/BagEquipDataHandler.h"
#include "../include/CSBagSaleObjectPacket.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include <algorithm>
#include "../include/EquipStrengthenDataHandler.h"
using namespace std;


BagEquipData * BagEquipData::__set(const BagEquipData * obj)
{
	this->index_ = obj->index_;
	this->itemcount_ = obj->itemcount_;

	this->template_->__set(obj->template_);
	this->id_ = obj->id_;
	this->level_ = obj->level_;
	this->levelMax_ = obj->levelMax_;
	this->exp_ = obj->exp_;
	this->maxexp_ = obj->maxexp_;
	this->advanceLevel_ = obj->advanceLevel_;
	this->advanceLevelMax_ = obj->advanceLevelMax_;
	this->mainAttriValue = obj->mainAttriValue;
	this->mainAttriValueMax = obj->mainAttriValueMax;
	this->equipScore_ = obj->equipScore_;
	this->attribute_->__set(obj->attribute_);
	this->attributeMAX_->__set(obj->attributeMAX_);
	this->isEquiped_ = obj->isEquiped_;

	return this;
}

void BagEquipData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>id_;
	packet>>level_;
	packet>>levelMax_;
	packet>>exp_;
	packet>>maxexp_;
	packet>>advanceLevel_;
	packet>>advanceLevelMax_;
	packet>>mainAttriValue;//主属性值
	packet>>mainAttriValueMax;//若主属性为攻击，为攻击的最大值
	packet>>equipScore_;
	//读装备通用属性
	unsigned char tmp_clen;
	packet>>tmp_clen;
	attribute_->mapPropertyList_.clear();
	for (int i=0;i<tmp_clen;i++)
	{
		unsigned char atype;	//0~13
		packet>>atype;
		int avalue;
		packet>>avalue;
		attribute_->mapPropertyList_.insert(std::map<int,int>::value_type(atype,avalue));
	}
	//读装备通用属性MAX
	packet>>tmp_clen;
	attributeMAX_->mapPropertyList_.clear();
	for (int i=0;i<tmp_clen;i++)
	{
		unsigned char atype;	//0~13
		packet>>atype;
		int avalue;
		packet>>avalue;
		attributeMAX_->mapPropertyList_.insert(std::map<int,int>::value_type(atype,avalue));
	}

}

BagEquipDataHandler::BagEquipDataHandler(){
	m_vecList.clear();

	m_bHaveNewItem = false;

	m_vecLuaFuncReult.clear();
	m_BagEquipTipsData = new BagEquipData;
}

BagEquipDataHandler::~BagEquipDataHandler(){

	ClearBagEquipList();

	CC_SAFE_DELETE(m_BagEquipTipsData);

	m_bHaveNewItem = false;
}

bool BagEquipDataHandler::init(){
	return true;
}

void BagEquipDataHandler::onDestroy(){
	ClearBagEquipList();
}

void BagEquipDataHandler::ClearBagEquipList(){
	vector<BagEquipData*>::iterator it=m_vecList.begin();
	vector<BagEquipData*>::iterator it_end=m_vecList.end();
	for (;it!=it_end;it++)
	{
		delete *it;
		*it = NULL;
	}
	m_vecList.clear();
}

int BagEquipDataHandler::refreshChangeData(BagEquipData * bed)
{
	int tag = 0;
	vector<BagEquipData*>::iterator it=m_vecList.begin();
	vector<BagEquipData*>::iterator it_end=m_vecList.end();
	for(; it != it_end; ++it)
	{
		if((*it)->index_ == bed->index_)
		{
			(*it)->__set(bed);
			bed->__delectflag = true;
			break;
		}
		++tag;
	}
	if(it == it_end)
	{
		m_bHaveNewItem = true;
		m_vecList.push_back(bed);
	}
	return tag;
}

int BagEquipDataHandler::setObjectCount(int index, int count)
{
	int tag = 0;
	vector<BagEquipData*>::iterator it=m_vecList.begin();
	vector<BagEquipData*>::iterator itend=m_vecList.end();
	for(; it != itend; ++it)
	{
		if((*it)->index_ == index)
		{
			(*it)->itemcount_ = count;
			if(count <= 0)
			{
				delete (*it);
				m_vecList.erase(it);
			}
			return tag;
			break;
		}	
		++tag;
	}
	return -1;
}

void BagEquipDataHandler::saleObject(int equipId, int num)
{
	//去背包找到这个物品

	BagEquipData * bed = getEquipByAllEquips(equipId);
	if(bed == NULL)
		return;

	CSBagSaleObjectPacket packet(kBAGSALEOBJECTPACKET, bed->id_, bed->template_->templateid_, num);
	packet.Send();

	NFC_showCommunicationWating(true);
}

/*
	@func1
	@获取指定物品templateid的物品个数
*/
int BagEquipDataHandler::getObjectCountByTemplateId(int tid)
{
	int num = 0;
	std::vector<BagEquipData *>::iterator it = m_vecList.begin();
	std::vector<BagEquipData *>::iterator itend = m_vecList.end();
	for(; it != itend; ++it)
	{
	if((*it)->template_->templateid_ == tid)
	{
	num += (*it)->itemcount_;
	}
	}
	return num;
}

/*
	@func2
	@在背包里取特定装备，根据id
*/
BagEquipData * BagEquipDataHandler::getEquipById(int id)
{
	BagEquipData * bb = NULL;
	vector<BagEquipData*>::iterator it=m_vecList.begin();
	vector<BagEquipData*>::iterator it_end=m_vecList.end();
	for(; it != it_end; it++)
	{
		if((*it)->id_ == id)
		{
			bb = *it;
			break;
		}	
	}
	return bb;
}

/*
	@func3
	@取特定装备，根据id
	 先找身上，再找背包
*/
BagEquipData* BagEquipDataHandler::getEquipByAllEquips(int id){

	for (int i = 0; i < 3; i++)
	{
		RoleEquipDataHandler* pRole = NFC_GetHeroEquipManager(i);
		if (pRole == NULL)
		{
			break;
		}
		if (pRole->getEquipById(id) != NULL)
		{
			return pRole->getEquipById(id);
		}
	}
	return getEquipById(id);;
}

/*
	@func4
	@比较2个装备，根据规则返回Bool值
*/
bool Compare_BagEquips_EquipLvup_CostCards(BagEquipData* it1,BagEquipData* it2){
	int qual_1=it1->template_->quality_;
	int qual_2=it2->template_->quality_;
	if (qual_1<qual_2)
		return true;
	else if(qual_1==qual_2){
		int lv_1=it1->level_;
		int lv_2=it2->level_;
		if (lv_1<lv_2)
			return true;
		else if(lv_1==lv_2)
			return it1->template_->templateid_<it2->template_->templateid_;
		else
			return false;
	}else
		return false;
}
void BagEquipDataHandler::reorderBagEquips_equiplvup_costcards(){
	std::sort(m_vecList.begin(),m_vecList.end(),Compare_BagEquips_EquipLvup_CostCards);
}



/*
	@func5
	@比较2个装备，根据规则返回Bool值
*/
bool Compare_HeroEquips(BagEquipData* it1,BagEquipData* it2){
	int quality_1=it1->template_->quality_;
	int quality_2=it2->template_->quality_;
	int type_1=it1->template_->type_;
	int type_2=it2->template_->type_;
	int level_1=it1->level_;
	int level_2=it2->level_;
	if (quality_1>quality_2)
		return true;
	else if(quality_1==quality_2){
		if (type_1<type_2)
			return true;
		else if(type_1==type_2){
			if (level_1>level_2)
				return true;
			else if(level_1==level_2)
				return it1->template_->templateid_>it2->template_->templateid_;
			else
				return false;
		}else
			return false;
	}else
		return false;
}
void BagEquipDataHandler::reorderEquipListForHeroEquip(){
	std::sort(m_vecList.begin(),m_vecList.end(),Compare_HeroEquips);
}



/*
	@func6
	@比较2个装备，根据规则返回Bool值
*/
bool Compare_EquipStren(BagEquipData* it1,BagEquipData* it2){
	int qual_1=it1->template_->quality_;
	int qual_2=it2->template_->quality_;
	int tp_1=it1->template_->type_;
	int tp_2=it2->template_->type_;
	if (qual_1>qual_2)
		return true;
	else if(qual_1==qual_2){
		if (tp_1<tp_2)
			return true;
		else if(tp_1==tp_2)
			return it1->template_->level_>it2->template_->level_;
		else
			return false;
	}else
		return false;

}
void BagEquipDataHandler::reorderEquipListForEquipStrengthen(){
	std::sort(m_vecList.begin(),m_vecList.end(),Compare_EquipStren);
}


/*
	@func7
	@比较2个装备，根据规则返回Bool值
*/ 
bool  compare_function_recast(const BagEquipData * first,const BagEquipData * second)
{   
	if(second->template_->quality_ < first->template_->quality_)
	{
		return true;
	}
	else if(first->template_->quality_ == second->template_->quality_)
	{
		if(second->advanceLevel_ < first->advanceLevel_)
		{
			return true;
		}
		else if(first->advanceLevel_ == second->advanceLevel_)
		{
			return first->id_ < second->id_ ? true :false;
		}
		else
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
}
std::vector<BagEquipData *> BagEquipDataHandler::getRoleEquipsForEquipRecast()
{
	vector<BagEquipData*> recastVec;
	size_t bagEquipsSize = m_vecList.size();
	bool isSpecial = false;
	for(size_t bagIndex = 0; bagIndex < bagEquipsSize;  bagIndex++)
	{	
		isSpecial = false; 
		if(!m_vecList.at(bagIndex)->isEquiped_ && 2<= m_vecList.at(bagIndex)->template_->quality_)
		{
			if(2 == m_vecList.at(bagIndex)->template_->quality_ && 0 == m_vecList.at(bagIndex)->advanceLevel_)
			{
				isSpecial = true;
			}
			if(!isSpecial)
			recastVec.push_back(m_vecList.at(bagIndex));
		} 
	}   
	if(!recastVec.empty())
	sort(recastVec.begin(),recastVec.end(),compare_function_recast);
	return recastVec;
}