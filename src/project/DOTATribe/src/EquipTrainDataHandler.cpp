//Name:EquipTrainDataHandler
//Function:装备洗练
//Author:	fangjun
//Date:20130820

#include <cocos2d.h>
#include "../include/EquipTrainDataHandler.h"
#include "../include/EquipTrainPacket.h"
#include "../include/AttributeLockPacket.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include "../include/EquipStrengthenDataHandler.h"
void AttributeLock::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>serial;
	packet>>equipId;
	packet>>attributeIndex;

}

void TrainData::decodePacketData(cobra_win::DPacket & packet)
{
	unsigned char tmp_clen = 0;
	
	packet>>equipId;

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

	packet>>moneyEnough;
}

EquipTrainDataHandler::EquipTrainDataHandler()
{
	ClearData();
}

EquipTrainDataHandler::~EquipTrainDataHandler()
{
	m_iCurEquipId = -1;
	m_vecEquipId.clear();
	m_pTrainData.attribute.mapPropertyList_.clear();
	m_pTrainData.attributeMax.mapPropertyList_.clear();

	m_iAttriPrice = 0;
}

int EquipTrainDataHandler::GetCurEquipId()
{
	return m_iCurEquipId;
}

void EquipTrainDataHandler::SetCurEquipId(int id)
{
	if(m_iCurEquipId == id)
		return;
	m_iCurEquipId = id;

	m_vecEquipLockStatus.clear();
}

void EquipTrainDataHandler::decodePacketData(cobra_win::DPacket & packet)
{
	//装备属性锁状态解包,解码当前装备的属性锁状态
	unsigned char count = 0;
	unsigned char index = 0;
	int equipId = 0;
	packet>>equipId;

	packet>>m_iAttriPrice;

	bool save = false;
	m_iCurEquipId == equipId ? save = true : save = false;
	
	packet>>count;
	m_vecEquipLockStatus.clear();
	for(; count > 0; --count)
	{
		packet>>index;
		if(save)
			m_vecEquipLockStatus.push_back(index);
	}

}

//锁定属性
void EquipTrainDataHandler::ToServerLockAttribute(int serial, int equipId, int attriIndex)
{
	CSAttributeLockPacket packet(serial, equipId, attriIndex);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void EquipTrainDataHandler::ToClientLockAttributeResult()
{
	//接收到属性加锁结果，通知UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_LOCK_ATTRIBUTE_RESULT_);

	NFC_showCommunicationWating(false);
}

//解锁属性
void EquipTrainDataHandler::ToServerUnLockAttribute(int serial, int equipId, int attriIndex)
{
	CSAttributeUnLockPacket packet(serial, equipId, attriIndex);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void EquipTrainDataHandler::ToClientUnLockAttributeResult()
{
	//接收到属性解锁消息通知ui
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UNLOCK_ATTRIBUTE_RESULT_);

	NFC_showCommunicationWating(false);
}

//洗练
void EquipTrainDataHandler::ToServerTrain(int equipId)
{
	CSEquipTrainPacket packet(equipId);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void EquipTrainDataHandler::ToClientTrainResult()
{
	//洗练完成，通知界面
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_EQUIPTRAIN_RESULT_);

	NFC_showCommunicationWating(false);
}

//获得装备锁状态
void EquipTrainDataHandler::ToServerGetAttributeLockStatus(int equipId)
{
	if(equipId > 0)
	{
		CSEquipTrainGetLockStatus packet(equipId);
		packet.Send();

		NFC_showCommunicationWating(true);
	}
}

void EquipTrainDataHandler::ToClientGetAttributeLockStatusResult()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_EQUIPTRAIN_GETLOCKSTATUS_RESULT_);

	NFC_showCommunicationWating(false);
}

void EquipTrainDataHandler::ToServerGetCurrentAttributeLockStatus()
{
	ToServerGetAttributeLockStatus(m_iCurEquipId);
}

BagEquipData * EquipTrainDataHandler::GetEquipById(int id)
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

BagEquipData * EquipTrainDataHandler::GetCurEquip()
{
	BagEquipData * bed = NULL;
	if(NULL == bed)
		bed = BAGEQUIPDATAHANDLER->getEquipById(m_iCurEquipId);
	if(NULL == bed){
		for (int i = 0; i < 3; i++)
		{
			RoleEquipDataHandler* pRole = NFC_GetHeroEquipManager(i);

			if (pRole != NULL)
			{
				bed = pRole->getEquipById(m_iCurEquipId);
				if (pRole->getEquipById(m_iCurEquipId))
				{
					return pRole->getEquipById(m_iCurEquipId);
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

void EquipTrainDataHandler::AddLock(unsigned char index)
{
	std::vector<int>::iterator i = m_vecEquipLockStatus.begin();
	std::vector<int>::iterator i_e = m_vecEquipLockStatus.end();
	for(; i != i_e; ++i)
	{
		if(*i == index)
			break;
	}
	if(i == i_e)
		m_vecEquipLockStatus.push_back(index);
}

void EquipTrainDataHandler::DeleteLock(unsigned char index)
{
	std::vector<int>::iterator i = m_vecEquipLockStatus.begin();
	std::vector<int>::iterator i_e = m_vecEquipLockStatus.end();
	for(; i != i_e; ++i)
	{
		if(*i == index)
			break;
	}
	if(i != i_e)
		m_vecEquipLockStatus.erase(i);
}


//通过获得的洗练结果改变内存中装备的数据
void EquipTrainDataHandler::ChangeEquipAttributeByTrainResult()
{
	BagEquipData * bed = GetEquipById(m_pTrainData.equipId);

	bed->attribute_->mapPropertyList_.clear();
	std::map<int, int>::iterator it = m_pTrainData.attribute.mapPropertyList_.begin();
	std::map<int, int>::iterator it_e = m_pTrainData.attribute.mapPropertyList_.end();
	for(; it != it_e; ++it)
	{
		bed->attribute_->mapPropertyList_.insert(std::map<int, int>::value_type(it->first, it->second));
	}

	bed->attributeMAX_->mapPropertyList_.clear();
	it = m_pTrainData.attributeMax.mapPropertyList_.begin();
	it_e = m_pTrainData.attributeMax.mapPropertyList_.end();
	for(; it != it_e; ++it)
	{
		bed->attributeMAX_->mapPropertyList_.insert(std::map<int, int>::value_type(it->first, it->second));
	}
}


bool EquipTrainDataHandler::IsCurEquipCanOneKeyTrain()
{
	BagEquipData * bed = GetCurEquip();
	std::map<int, int>::iterator it = bed->attribute_->mapPropertyList_.begin();
	std::map<int, int>::iterator it_e = bed->attribute_->mapPropertyList_.end();

	if(bed->attribute_->mapPropertyList_.size() == 0)
		return false;
	
	for(; it != it_e; ++it)
	{
		bool b = false;
		for(int i = 0; i < m_vecEquipLockStatus.size(); ++i)
		{
			if(m_vecEquipLockStatus[i] == it->first)
				b = true;
		}
		if(b == false)
		{
			if(it->second == bed->attributeMAX_->mapPropertyList_.find(it->first)->second)
				return false;
		}
	}

	return true;

}

	/*
		清除数据
	*/
void EquipTrainDataHandler::ClearData(){
	m_iCurEquipId = -1;
	m_iAttriPrice = 0;
	m_vecEquipId.clear();
	m_vecEquipLockStatus.clear();
	m_pTrainData.attribute.mapPropertyList_.clear();
	m_pTrainData.attributeMax.mapPropertyList_.clear();
	m_mapAttributeLockPosition.clear();
}