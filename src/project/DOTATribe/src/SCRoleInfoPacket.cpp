//Name：SCRoleInfoPacket
//Function：s->c角色信息
//Written By：尹强
#include <cocos2d.h>
#include "../include/SCRoleInfoPacket.h"
#include "../include/DOTATribeApp.h"
#include "../include/CreateRoleProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/LoggerSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/DPacket.h>
#include "../include/BagEquipDataHandler.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/CSMapTable.h"
#include "../include/BagTemplateBaseHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/RoleSoulsDataHandler.h"

using  namespace  cobra_win;

unsigned  int  SCRoleInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ROLEINFO_;
}

unsigned  int  SCRoleInfoPacket::GetPacketLength()
{
	return sizeof(int);
}

void SCRoleInfoPacket::_readRoleInfo(DPacket &packet)
{
	LOGGERSYSTEM->LogInfo("==================SCRolInfoPacket-- Read Role Info==============");
	ROLEINFODATAHANDLER->decodePacketData(packet);
}

void SCRoleInfoPacket::_readTeamHero(cobra_win::DPacket &packet)
{
	ROLEHEROSKINSDATAHANDLER->decodePacket_TeamHero(packet);
}

void SCRoleInfoPacket::_readBag(DPacket &packet){
	int tmp_nlen=0;
	unsigned short tmp_len=0;
	unsigned char tmp_clen=0;
	char *tmpChar=0;
 
	LOGGERSYSTEM->LogInfo("SCRolInfoPacket-- Read Bag Data	--start");

	unsigned char bagCount = 0;
	packet>>bagCount;
	for(int n = 0; n < bagCount; ++n)
	{
		char bagtype = 0;
		packet>>bagtype;
		unsigned short thisBagCount = 0;
		unsigned short thisBagMaxCount = 0;
		packet>>thisBagMaxCount;//包格数量
		packet>>thisBagCount;//物品数量

		if(bagtype == BAG_ITEM)
		{
			BAGOTHEROBJECTHANDLER->m_bagMaxCount = thisBagMaxCount;
		}
		else if(bagtype == BAG_EQUIP)
		{
			BAGEQUIPDATAHANDLER->m_bagMaxCount = thisBagMaxCount;
		} 

		for(int i = 0; i < thisBagCount; ++i)
		{
			unsigned short idx;
			unsigned short itemcount;
			packet>>idx;
			packet>>itemcount;

			//读取物品模版
			BagTemplateBase * btb = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);

			if(bagtype == BAG_ITEM)
			{
				BagOtherObject * boo = new BagOtherObject((ObjectTemplate *)btb);
				boo->decodePacketData(packet);
				boo->index_ = idx;
				boo->itemcount_ = itemcount;
				if(boo->itemcount_ > 0)
				{
					BAGOTHEROBJECTHANDLER->refreshChangeData(boo);
					if(boo->__delectflag)
					{
						delete boo;
						boo = NULL;
					}
				}
				else
				{
					delete boo;
					boo = NULL;
				}
			}
			else if(bagtype == BAG_EQUIP)
			{
				BagEquipData * bed = new BagEquipData((EquipTemplate *)btb);
				bed->decodePacketData(packet);
				bed->index_ = idx;
				bed->itemcount_ = itemcount;
				if(bed->itemcount_ > 0)
				{
					BAGEQUIPDATAHANDLER->refreshChangeData(bed);
					if(bed->__delectflag)
					{
						delete bed;
						bed = NULL;
					}
				}
				else
				{
					delete bed;
					bed = NULL;
				}
			}
		}
	}

	LOGGERSYSTEM->LogInfo("SCRolInfoPacket-- Read Bag Data	--Reorder BagEquip");
}


void SCRoleInfoPacket::_readMissionInfo(cobra_win::DPacket &packet)
{   
	MissionDataHandler::get_instance2()->decodeTotalMissionsPacket(packet);  
}
 
void SCRoleInfoPacket::_readHeroDB(cobra_win::DPacket &packet)
{ 
	ROLEHEROSKINSDATAHANDLER->decodePacket_HeroDB(packet);
}

void SCRoleInfoPacket::_readRoleSouls(cobra_win::DPacket &packet)
{
	RoleSoulsDataHandler::get_instance2()->decodePacket(packet);
}

void SCRoleInfoPacket::_readCheckFunOpen(cobra_win::DPacket &packet){
	ServerInfoDataHandler::get_instance2()->decodePacketData_CheckOpenFunction(packet);
}


bool  SCRoleInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	LOGGERSYSTEM->LogInfo("SCRoleInfoPacket::Read");
	DPacket packet(pBuffer, iLen);
	packet.read(head_,2);
	packet>>len_;
	packet>>pn_;
	packet>>serial_;
	//@读取player信息
	_readRoleInfo(packet);
	//@Bag
	_readBag(packet);
	//@任务信息
	_readMissionInfo(packet);
	//@英雄库
	_readHeroDB(packet);
	//@战魂
	_readRoleSouls(packet);
	//@读取英雄信息
	_readTeamHero(packet);
	//@功能开启
	_readCheckFunOpen(packet);
	return true;
}

unsigned  int SCRoleInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ROLEINFO_;
}

bool SCRoleInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRoleInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	SERVERINFODATAINFO->HandleAfterRoleInfo();
	return true;
}	
