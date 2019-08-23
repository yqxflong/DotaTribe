#include "../include/RoleSoulsDataHandler.h"
#include "../include/NFToolController.h"
#include <algorithm> 
#include <vector>
#include "../include/NFControlsManager.h"
using namespace std;
IHeroSoulItem::IHeroSoulItem(bool isindex)
{
	m_nSoulBufferID = 0;
	m_nSoulBufferIconID = 0;
	m_bSoulType = 0;
	m_bCurSoulLevel = 0;
	m_bMaxSoulLevel = 0;
	m_bEquipIndex = -1;
	m_sSoulBufferName = "";
	m_sSoulAtributeName = "";
	m_isIndex = isindex;
}

IHeroSoulItem::~IHeroSoulItem()
{

}
 
void  IHeroSoulItem::decodePacket(cobra_win::DPacket & packet)
{
	if (m_isIndex)
	{
		packet.read(m_bEquipIndex);
	}
	packet.read(m_nSoulBufferID);
	packet.read(m_nSoulBufferIconID);
	packet.read(m_HeroID);
	packet.read(m_bSoulType);  
	packet.read(m_bCurSoulLevel);
	packet.read(m_bMaxSoulLevel);
	
	NFC_ParsePacketString(packet,m_sSoulBufferName);
	NFC_ParsePacketString(packet,m_sSoulAtributeName); 
}

void  IHeroSoulItem::decodeWithOutBufferIDPacket(cobra_win::DPacket & packet)
{ 
	packet.read(m_nSoulBufferIconID);
	packet.read(m_HeroID);
	packet.read(m_bSoulType);  
	packet.read(m_bCurSoulLevel);
	packet.read(m_bMaxSoulLevel);
	NFC_ParsePacketString(packet,m_sSoulBufferName);
	NFC_ParsePacketString(packet,m_sSoulAtributeName); 
}


//////////////////////////////////////////////////////////////////////////
IRoleSoulsEquipInfo::IRoleSoulsEquipInfo()
{
	m_uHeroSoulEuipMaxCount = 0;
	m_uHeroSoulPosVector.clear();

}
IRoleSoulsEquipInfo::~IRoleSoulsEquipInfo()
{
	SoulEquipClearList();
	m_uHeroSoulPosVector.clear();
}


void   IRoleSoulsEquipInfo::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_uHeroSoulEuipMaxCount);
	COMMON_BEIGIN_ARRAY(short,m_uHeroSoulEuipMaxCount)
		IByte soulIndex = 0;
		IByte isOpen = 0;
		int   openLevel = 0;
		packet.read(soulIndex);
		packet.read(isOpen);
		if(isOpen == 0)
		{ 
			packet.read(openLevel); 
		}
		SoulEquipItem  item(soulIndex,isOpen,openLevel);
		m_uHeroSoulPosVector.push_back(item);
	COMMON_END_ARRAY
	unsigned short soulcount = 0;
	packet.read(soulcount);
	COMMON_BEIGIN_ARRAY(short, soulcount)
		IHeroSoulItem* pHeroSoulItem = new IHeroSoulItem();
		if (pHeroSoulItem)
		{
			pHeroSoulItem->decodePacket(packet);
		}
		m_mHeroSoulEquipList.push_back(pHeroSoulItem);
	COMMON_END_ARRAY


}


void   IRoleSoulsEquipInfo::decodeUnLockEquipPacket(cobra_win::DPacket & packet)
{
	IByte soulIndex = 0;
	IByte soulIsOpen = 0;
	packet.read(soulIndex);
	packet.read(soulIsOpen); 
	COMMON_BEIGIN_ARRAY(short,m_uHeroSoulEuipMaxCount) 
		if (m_uHeroSoulPosVector.at(index).m_uHeroSoulEquipIndex == soulIndex)
		{
			bool isOpenSoule = soulIsOpen > 0 ? true : false;
			m_uHeroSoulPosVector.at(index).m_uHeroSoulEquipIsOpen = isOpenSoule;
			return ;
		}
	COMMON_END_ARRAY 
}

void   IRoleSoulsEquipInfo::SoulEquipClearList()
{
	std::vector<IHeroSoulItem *>::iterator it = m_mHeroSoulEquipList.begin();
	std::vector<IHeroSoulItem *>::iterator it_end = m_mHeroSoulEquipList.end();
	for (it;it != it_end;it++)
	{
		CC_SAFE_DELETE(*it);
	}
	m_mHeroSoulEquipList.clear();
}
//////////////////////////////////////////////////////////////////////////

IHeroSoulDataManager::IHeroSoulDataManager()
{
  m_mRoleSoulsDB.clear();
  m_mPowerSoulsDB.clear();
  m_mQuickSoulsDB.clear();
  m_mInteligenceSoulsDB.clear(); 
}
 
IHeroSoulDataManager::~IHeroSoulDataManager()
{
	std::map<int,IHeroSoulItem *>::iterator iter_soul = m_mRoleSoulsDB.begin();
	while(iter_soul != m_mRoleSoulsDB.end())
	{
		if(iter_soul->second)
		{
			delete iter_soul->second;
		}
		++iter_soul;
	}
	m_mRoleSoulsDB.clear();
	m_mPowerSoulsDB.clear();
	m_mQuickSoulsDB.clear();
	m_mInteligenceSoulsDB.clear();
}

std::vector<IHeroSoulItem * > & IHeroSoulDataManager::getRoleAllSoulsVector()
{ 
	return  m_mAllUnESoulsVector;
}
std::vector<IHeroSoulItem * >  & IHeroSoulDataManager::getRolePowerSoulsVector()
{ 
	return  m_mPowerUnEUnESoulsVector;
}
std::vector<IHeroSoulItem * > & IHeroSoulDataManager::getRoleQuickSoulsVector()
{
	return  m_mQuickUnESoulsVector;
}
std::vector<IHeroSoulItem * > & IHeroSoulDataManager::getRoleInteligenceSoulsVector()
{
	return  m_mInteligenceUnESoulsVector;

}
/*109
std::vector<IHeroSoulItem * > &  IHeroSoulDataManager::getRoleEquipSoulVector()
{
	return  m_mHeroSoulEqipVector;
}*/

IHeroSoulItem  *	  IHeroSoulDataManager::getRoleSoulItem(int heroSouleItemID)
{
	std::map<int,IHeroSoulItem *>::iterator iter_soul = m_mRoleSoulsDB.find(heroSouleItemID);
	if(iter_soul!=m_mRoleSoulsDB.end())
	{
		return iter_soul->second;
	}
	return NULL;
}

size_t			IHeroSoulDataManager::getUnEquipSoulBufferCount()
{
	return  m_mAllUnESoulsVector.size();	 
}


void   IHeroSoulDataManager::decodePacket(cobra_win::DPacket & packet)
{
	short roleSoulCount = 0;
	packet.read(roleSoulCount);
	COMMON_BEIGIN_ARRAY(short,roleSoulCount)
		IHeroSoulItem * pHeroSoulItem = new IHeroSoulItem(false);
		if(pHeroSoulItem)
		{
			pHeroSoulItem->decodePacket(packet);
			m_mRoleSoulsDB.insert(std::map<int,IHeroSoulItem *>::value_type(pHeroSoulItem->getHeroSoulBufferID(),pHeroSoulItem));
		}
	COMMON_END_ARRAY

	updateRoleSoul();
}

void  IHeroSoulDataManager::decodeEquipSoulChangePacket(cobra_win::DPacket & packet)
{
	int   heroSoulBufferID = 0;
	char  heroSoulIndex = 0;
	unsigned char heroid = 0;
	packet.read(heroid);
	packet.read(heroSoulBufferID);
	packet.read(heroSoulIndex);

	std::map<int, IHeroSoulItem *>::iterator iter_soul = m_mRoleSoulsDB.find(heroSoulBufferID);
	if(iter_soul!=m_mRoleSoulsDB.end())
	{
		IHeroSkinItem* pHeroskin = NFC_GetTeamHero(heroid);
		if (pHeroskin == NULL)
			return;
		iter_soul->second->setHeroSoulEquipIndex(heroSoulIndex);
		pHeroskin->getSoulsEquipManager()->getHeroSoulEquipList().push_back(iter_soul->second);
		m_mRoleSoulsDB.erase(iter_soul);
		updateRoleSoul();
		return ;
	}
} 

void   IHeroSoulDataManager::decodeUnEquipSoulChangePacket(cobra_win::DPacket & packet)
{
	int   heroSoulBufferID = 0;
	char  heroSoulIndex = 0;
	unsigned char heroid = 0;
	packet.read(heroid);
	packet.read(heroSoulBufferID);
	packet.read(heroSoulIndex);
	IHeroSkinItem* pHeroskin = NFC_GetTeamHero(heroid);
	if (pHeroskin == NULL)
		return;
	std::vector<IHeroSoulItem *>::iterator it = pHeroskin->getSoulsEquipManager()->getHeroSoulEquipList().begin();
	std::vector<IHeroSoulItem *>::iterator it_end = pHeroskin->getSoulsEquipManager()->getHeroSoulEquipList().end();
	for (it;it != it_end;it++)
	{
		if ((*it)->getHeroSoulBufferID() == heroSoulBufferID)
		{
			std::map<int, IHeroSoulItem *>::iterator iter_soul = m_mRoleSoulsDB.find(heroSoulBufferID);
			if (iter_soul == m_mRoleSoulsDB.end())
			{
				(*it)->setHeroSoulEquipIndex(-1);
				m_mRoleSoulsDB.insert(std::map<int, IHeroSoulItem *>::value_type(heroSoulBufferID,(*it)));
				pHeroskin->getSoulsEquipManager()->getHeroSoulEquipList().erase(it);
				updateRoleSoul();
				return;
			}
		}
	}
}

void   IHeroSoulDataManager::deoceAddHeroSoulPacket(cobra_win::DPacket & packet)
{
    int  heroSoulBufferID = 0;
	packet.read(heroSoulBufferID);
	std::map<int,IHeroSoulItem *>::iterator iter_soul = m_mRoleSoulsDB.find(heroSoulBufferID);
	if(iter_soul !=m_mRoleSoulsDB.end())
	{
		iter_soul->second->decodeWithOutBufferIDPacket(packet);
	}
	else
	{
		IHeroSoulItem * pHeroSoulItem = new IHeroSoulItem();
		if(pHeroSoulItem)
		{
			pHeroSoulItem->setHeroSoulBufferID(heroSoulBufferID);
			pHeroSoulItem->decodeWithOutBufferIDPacket(packet);
			m_mRoleSoulsDB.insert(std::map<int,IHeroSoulItem *>::value_type(heroSoulBufferID,pHeroSoulItem));
		}
	} 
	updateRoleSoul();
}

bool   Compare_Activate(IHeroSoulItem* it1, IHeroSoulItem* it2)
{
	return it1->getHeroSoulCurLevel() > it2->getHeroSoulCurLevel();
}

void    IHeroSoulDataManager::updateRoleSoul()
{ 
	m_mPowerSoulsDB.clear();
	m_mQuickSoulsDB.clear();
	m_mInteligenceSoulsDB.clear();
	/*109m_mHeroSoulEqipVector.clear();*/

	//////////////////////////////////////////////////////////////////////////
	m_mAllUnESoulsVector.clear();
	m_mPowerUnEUnESoulsVector.clear();
	m_mQuickUnESoulsVector.clear();
	m_mInteligenceUnESoulsVector.clear();
  
	std::map<int,IHeroSoulItem *>::iterator iter_soul = m_mRoleSoulsDB.begin();
	while(iter_soul != m_mRoleSoulsDB.end())
	{
		IHeroSoulItem * pHeroSoulItem = iter_soul->second; 
		if(pHeroSoulItem)
		{
/*109
			if(pHeroSoulItem->getHeroSoulEquipIndex()>-1)
			{
				m_mHeroSoulEqipVector.push_back(pHeroSoulItem);
			}
			else
			{
				m_mAllUnESoulsVector.push_back(pHeroSoulItem);
			} */
			m_mAllUnESoulsVector.push_back(pHeroSoulItem);
			switch(pHeroSoulItem->getHeroSoulType())
			{
			case IHeroSoulItem::_HeroSoul_Power_Type_:
				{ 

					m_mPowerUnEUnESoulsVector.push_back(pHeroSoulItem);
					
					m_mPowerSoulsDB.insert(std::map<int,IHeroSoulItem *>::value_type(pHeroSoulItem->getHeroSoulBufferID(),pHeroSoulItem));
					break;
				}
			case IHeroSoulItem::_HeroSoul_Quick_Type_:
				{ 

					m_mQuickUnESoulsVector.push_back(pHeroSoulItem);

					m_mQuickSoulsDB.insert(std::map<int,IHeroSoulItem *>::value_type(pHeroSoulItem->getHeroSoulBufferID(),pHeroSoulItem));
					break;
				}
			case IHeroSoulItem::_HeroSoul_Inteligence_Type_:
				{

					m_mInteligenceUnESoulsVector.push_back(pHeroSoulItem);
				
					m_mInteligenceSoulsDB.insert(std::map<int,IHeroSoulItem *>::value_type(pHeroSoulItem->getHeroSoulBufferID(),pHeroSoulItem));
					break;
				}
			default:
				break;
			}
		}
		++iter_soul;
	}
	std::sort(m_mAllUnESoulsVector.begin(), m_mAllUnESoulsVector.end(), Compare_Activate);
	std::sort(m_mPowerUnEUnESoulsVector.begin(), m_mPowerUnEUnESoulsVector.end(), Compare_Activate);
	std::sort(m_mQuickUnESoulsVector.begin(), m_mQuickUnESoulsVector.end(), Compare_Activate);
	std::sort(m_mInteligenceUnESoulsVector.begin(), m_mInteligenceUnESoulsVector.end(), Compare_Activate);
}


//////////////////////////////////////////////////////////////////////////

RoleSoulsDataHandler::RoleSoulsDataHandler()
{
	m_pHeroSoulDataManager = NULL;
}
RoleSoulsDataHandler::~RoleSoulsDataHandler()
{
	destroyData();
} 

void RoleSoulsDataHandler::onDestroy()
{

}
 
void RoleSoulsDataHandler::destroyData()
{
	if(m_pHeroSoulDataManager)
	{
		delete m_pHeroSoulDataManager;
		m_pHeroSoulDataManager = NULL;
	}
}

bool RoleSoulsDataHandler::init()
{ 
	return true;
}

void  RoleSoulsDataHandler::decodePacket(cobra_win::DPacket & packet)
{
	 destroyData();
	 m_pHeroSoulDataManager = new IHeroSoulDataManager();	
	 //@ m_pHeroSoulEquipInfo = new IRoleSoulsEquipInfo();
	 //@m_pHeroSoulEquipInfo->decodePacket(packet);
	 m_pHeroSoulDataManager->decodePacket(packet);
}
 

void  RoleSoulsDataHandler::decodeSoulChangePacket(cobra_win::DPacket & packet)
{
	if(m_pHeroSoulDataManager)
	{
		m_pHeroSoulDataManager->decodeEquipSoulChangePacket(packet);
	}
}
 
void  RoleSoulsDataHandler::decodeSoulUnChangePacket(cobra_win::DPacket & packet)
{
	if (m_pHeroSoulDataManager)
	{
		m_pHeroSoulDataManager->decodeUnEquipSoulChangePacket(packet);
	}
}


void  RoleSoulsDataHandler::decodeAddHeroSoulPacket(cobra_win::DPacket & packet)
{
	if(m_pHeroSoulDataManager)
	{
		m_pHeroSoulDataManager->deoceAddHeroSoulPacket(packet);
	}
}


IHeroSoulItem  *  RoleSoulsDataHandler::getHeroSoulItemByID(int heroSoulBufferID)
{
	if(m_pHeroSoulDataManager)
	{
		return m_pHeroSoulDataManager->getRoleSoulItem(heroSoulBufferID);
	}
	return NULL;
}

int RoleSoulsDataHandler::SoulUnActivIndex(std::vector<IHeroSoulItem *>& vec)
{
	std::vector<IHeroSoulItem*>::iterator it = vec.begin();
	std::vector<IHeroSoulItem*>::iterator it_end = vec.end();
	int index = 0;
	for (it;it != it_end;it++)
	{
		if (*it)
		{
			if ((*it)->getHeroSoulCurLevel() == 0)
			{
				return index;
			}	
		}
		index++;
	}
	return -1;
}

 
//////////////////////////////////////////////////////////////////////////