//Name：BagOtherObject
//Function：背包其他物品数据
//				    与Packet对应
//Written By：尹强

#include "../include/BagOtherObjectHandler.h"
#include "../include/CSMapTable.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/DPacket.h>
#include <string>
#include "../include/NFControlsManager.h"
#include "../include/CSBagSaleObjectPacket.h"
#include "../include/CSBagUseObjectPacket.h"
#include "../include/BagTemplateBaseHandler.h"

using namespace std;


BagOtherObject * BagOtherObject::__set(const BagOtherObject * obj)
{
	this->index_ = obj->index_;
	this->itemcount_ = obj->itemcount_;

	this->template_->__set(obj->template_);
	this->id_ = obj->id_;

	//合成目标物应该是不会更改的，先不用赋值，等到用的时候再说
	//delete this->composeDetail_;
	//this->composeDetail_ = boo->composeDetail_;

	return this;
}

void BagOtherObject::decodePacketData(cobra_win::DPacket & packet)
{
	if(template_->type_ == kOBJECTCOMPOSE)//合成
	{
		composeDetail_ = new ComposeDetail();
		assert(composeDetail_ != NULL);
		composeDetail_->destObject_ = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);

		packet>>composeDetail_->destCount_;//合成数量
		packet>>composeDetail_->costMoney_;//所需金钱

		BagTemplateBase * btb = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);//所需物品
		unsigned short needNum = 0;
		packet>>needNum;//所需物品数量

		composeDetail_->_addObject(btb, needNum);

	}
	else if(template_->type_ == kOBJECTRECIPE)//配方
	{
		composeDetail_ = new ComposeDetail();
		assert(composeDetail_ != NULL);
		composeDetail_->destObject_ = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);

		packet>>composeDetail_->destCount_;//合成数量
		packet>>composeDetail_->costMoney_;//所需金钱
		char tmp_c = 0;
		for(int i = 0; i < 4; ++i)
		{
			packet>>tmp_c;
			if(tmp_c > 0)
			{
				BagTemplateBase * tmp = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);
				unsigned short needNum = 0;
				packet>>needNum;
				composeDetail_->_addObject(tmp, needNum);
			}
		}
	}

	packet>>id_;

}


BagOtherObjectHandler::BagOtherObjectHandler(){
	m_vecList.clear();

	m_bHaveNewItem = false;

}

BagOtherObjectHandler::~BagOtherObjectHandler(){
	
	ClearBagObjectList();

	m_bHaveNewItem = false;
}

void BagOtherObjectHandler::handlePacket(IPacket* packet){
	/*
		将packet转成Data，存入list
	*/
}


bool BagOtherObjectHandler::init(){
	return true;
}

void BagOtherObjectHandler::onDestroy(){
	ClearBagObjectList();
}

void BagOtherObjectHandler::ClearBagObjectList(){
	vector<BagOtherObject*>::iterator it=m_vecList.begin();
	vector<BagOtherObject*>::iterator it_end=m_vecList.end();
	for (;it!=it_end;it++)
	{
		delete *it;
		*it = NULL;
	}
	m_vecList.clear();
}

//此方法的使用是在判断需要出售的物品数量和堆叠数量比较之后再运行。
void BagOtherObjectHandler::saleObject(BagOtherObject * object, int num)
{
	//通知服务器
	CSBagSaleObjectPacket packet(kBAGSALEOBJECTPACKET, object->id_, object->template_->templateid_, num);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void BagOtherObjectHandler::useObject(BagOtherObject * object, int num)
{
	CSBagUseObjectPacket packet(kBAGUSEOBJECTPACKET, object->id_, object->template_->templateid_, num);
	packet.Send();
	NFC_showCommunicationWating(true);
}

int BagOtherObjectHandler::refreshChangeData(BagOtherObject * boo)
{
	int idx = 0;
	std::vector<BagOtherObject *>::iterator it = m_vecList.begin();
	std::vector<BagOtherObject *>::iterator itend = m_vecList.end();
	for(; it != itend; ++it)
	{
		if((*it)->index_ == boo->index_)
		{
// 			BagOtherObject * temp = *it;
// 			//m_vecList.erase(it);
// 			*it = boo;
// 			delete temp;
// 			temp = NULL;
			(*it)->__set(boo);
			boo->__delectflag = true;
			break;
		}
		++idx;
	}
	if(it == itend)
	{
		m_bHaveNewItem = true;
		m_vecList.push_back(boo);
	}
	return idx;
}

int BagOtherObjectHandler::setObjectCount(int index, int count)
{	
	int tag = 0;
	std::vector<BagOtherObject *>::iterator it = m_vecList.begin();
	std::vector<BagOtherObject *>::iterator itend = m_vecList.end();
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

void BagOtherObjectHandler::refreshUI4DataChanged()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_REFRESH_UI_BAGOBJECT_INFO_);
}

int BagOtherObjectHandler::getBagObjectCanComposeNum()
{
	std::vector<BagOtherObject *>::iterator it = m_vecList.begin();
	std::vector<BagOtherObject *>::iterator itend = m_vecList.end();
	int num = 0;
	int type = 0;
	while(it != itend)
	{
		type = (*it)->template_->type_;
		if(type == kOBJECTCOMPOSE || type == kOBJECTRECIPE)
		{
			++num;
		}
		++it;
	}
	return num;
}

BagOtherObject * BagOtherObjectHandler::getBagObjectByCanIndex(int idx)	//index can be 0
{
	int count = m_vecList.size();
	int type = 0;
	for(int j = 0; j < count; ++j)
	{
		type = m_vecList[j]->template_->type_;
		if(type == kOBJECTCOMPOSE || type == kOBJECTRECIPE)
		{
			--idx;
		}
		if(idx < 0)
		{
			return m_vecList[j];
		}
	}
	
	return NULL;
}

int BagOtherObjectHandler::getIndexFromCanComposeList(int objectId, bool includeThisId)
{
	int id = -1;
	int type = -1;
	int temp = 0;
	if(includeThisId)
		temp = objectId;
	else temp = objectId - 1;
	for(int i = 0; i <= temp; ++i)
	{
		type = m_vecList[i]->template_->type_;
		if(type == kOBJECTCOMPOSE || type == kOBJECTRECIPE)
			++id;
	}
	//this is add by fangjun, on 20130918, begin
	if(!includeThisId)
		++id;//此处是因为对于删除的物品来说，不包含当前的位置，则获得的是它前面的物品的id序列号。于是对于此情况，当前物品的Id应该为id+1
	//end
	return id;

}

BagOtherObject * BagOtherObjectHandler::getBagObjectByIndex(int allindex, int & smallidx)
{
	int tag = 0;
	std::vector<BagOtherObject *>::iterator it = m_vecList.begin();
	std::vector<BagOtherObject *>::iterator itend = m_vecList.end();
	for(; it != itend; ++it)
	{
		if((*it)->index_ == allindex)
		{
			smallidx = tag;
			return (*it);
		}
		++tag;
	}
	smallidx = -1;
	return NULL;
}

/*
	获取指定物品templateid的物品个数
*/
int BagOtherObjectHandler::getObjectCountByTemplateId(int tid)
{
	int num = 0;
	std::vector<BagOtherObject *>::iterator it = m_vecList.begin();
	std::vector<BagOtherObject *>::iterator itend = m_vecList.end();
	for(; it != itend; ++it)
	{
		if((*it)->template_->templateid_ == tid)
		{
			num += (*it)->itemcount_;
		}
	}

	return num;
}


BagOtherObject * BagOtherObjectHandler::getObjectByTemplateId(int tid)
{
	
	for(int i =0;i< (int)m_vecList.size();++i)
	{
	//	int b = m_vecList[i]->template_->templateid_;
		if(m_vecList[i]->template_->templateid_ == tid)
		{
			return m_vecList[i];
		}
	}
	return NULL;
}


	/*
		按照规则排序装备
		1.品质	 2.等级		3.物品ID
		装备列表（英雄装备界面、洗炼）
	*/
void BagOtherObjectHandler::reorderBagObject(){
	int size = m_vecList.size();
	BagOtherObject * temp = NULL;
	for(int i = 0; i < size; i++)
	{
		for(int j = size - 1; j > i; j--)
		{
			if(m_vecList[j]->template_->sortIndex < m_vecList[j - 1]->template_->sortIndex)
			{
				temp = m_vecList[j - 1];
				m_vecList[j - 1] = m_vecList[j];
				m_vecList[j] = temp;
			}
		}
	}

// 	for (int i=0; i<(int)m_vecList.size(); i++)
// 	{
// 		for (int j=0;j<i;j++)
// 		{
// 			BagOtherObject* tmp=m_vecList[i];
// 			if (m_vecList[i]->template_->templateid_<m_vecList[j]->template_->templateid_)
// 			{
// 				m_vecList[i]=m_vecList[j];
// 				m_vecList[j]=tmp;
// 			}
// 		}
// 	}

}