//Name：SCRrefreshInfoDataPacket
//Function：s->c 服务器主动下发的同步人物信息
//Author : fangjun
//Date : 2013-8-5
#include <cocos2d.h>
#include "../include/SCRefreshInfoDataPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/HeroIllustratedDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/NewEquipremindDataHandler.h"
#include "../include/RoleSoulsDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/BossScoreDataHandler.h"
#include "../include/ArenaInfoDataHandler.h"
 

#include <string>

using  namespace  cobra_win;


unsigned  int  SCRefreshInfoDataPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_REFRESHINFODATA_;
}

unsigned  int  SCRefreshInfoDataPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCRefreshInfoDataPacket::Read(char* pBuffer, unsigned int iLen)
{
	//~~~~检查是否锁定
	if(ROLEINFODATAHANDLER->isLock)return true;
	//~~~~~~~~~~~~~~~
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//
	unsigned short count;
	packet>>count;
	unsigned char type = 0;
	//4DeBug
	std::map<int,int> tmp=ROLEINFODATAHANDLER->m_pRIData->attribute_->mapPropertyList_;
	//
	for (int i = 0; i < count; ++i)
	{
		packet>>type;
		switch(type)
		{
		case kINFOLEVEL:{//级别
			unsigned short lev = 0;
			packet>>lev;
			ROLEINFODATAHANDLER->m_pRIData->level_ = lev;
		}break;
		case kINFOEXP:{//经验
			int exp = 0;
			packet>>exp;
			ROLEINFODATAHANDLER->m_pRIData->exp_ = exp;
		}break;
		case kINFOMAXEXP:{//最大经验
			int maxexp = 0;
			packet>>maxexp;
			ROLEINFODATAHANDLER->m_pRIData->maxExp_ = maxexp;
		}break;
		case kINFOVITALITY:{//体力
			unsigned short vi= 0;
			packet>>vi;
			ROLEINFODATAHANDLER->m_pRIData->vitality_ = vi;
		}break;
		case kINFOJEWELS:{//钻石
			int jewel = 0;
			packet>>jewel;
			ROLEINFODATAHANDLER->m_pRIData->jewels_ = jewel;
		}break;
		case kINFOMONEY:{//金钱
			int money = 0;
			packet>>money;
			ROLEINFODATAHANDLER->m_pRIData->money_ = money;
		}break;
		case kINFOBAGGRID:{//包格
			unsigned short index = 0;
			unsigned short num = 0;
			unsigned char bagType = 0;
			packet>>bagType;
			packet>>index;
			packet>>num;
			int vectorIndex = 0;		//存储器列表中的序号，方便取数据和显示
			if(num > 0)
			{
				//读取物品模版
				BagTemplateBase * btb = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);
				if(bagType == BAG_ITEM)
				{
					BagOtherObject * boo = new BagOtherObject((ObjectTemplate *)btb);
					boo->decodePacketData(packet);
					boo->index_ = index;
					boo->itemcount_ = num;
					vectorIndex = BAGOTHEROBJECTHANDLER->refreshChangeData(boo);
					if(boo->__delectflag)
					{
						delete  boo;
						boo = NULL;
					}
					
				}
				else if(bagType == BAG_EQUIP)
				{
					BagEquipData * bed = new BagEquipData((EquipTemplate *)btb);
					bed->decodePacketData(packet);
					bed->index_ = index;
					bed->itemcount_ = num;
					vectorIndex = BAGEQUIPDATAHANDLER->refreshChangeData(bed);
					needRefreshBagEquip_=true;    //需要通知刷新
					if (bed->template_->type_ != kEQUIP_TYPE_EXPBALL)
					{
						NEWEQUIPREMINDDATAHANDLER->ComPareNewEquipandRoleEquip(bed->id_);
					}
					if(bed->__delectflag)
					{
						delete bed;
						bed = NULL;
					}
					
				}
			}
			else
			{
				/*
					Warning:if these three method cause fatal error,call fangjun immediately.At 130816.
				*/
				if(bagType == BAG_ITEM)
				{
					vectorIndex = BAGOTHEROBJECTHANDLER->setObjectCount(index, num);
				}
				else if(bagType == BAG_EQUIP)
				{
					vectorIndex = BAGEQUIPDATAHANDLER->setObjectCount(index, num);
					needRefreshBagEquip_=true;
				}
			}

			//用于通知背包，背包数据更新
			std::string idx = _to_event_param_((int)vectorIndex);
			std::string scount = _to_event_param_((int)num);
			std::string _bagtype = _to_event_param_((int)bagType);//方便背包判断是哪个背包物品
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_BAGREFRESH_BAG_ITEM_, _bagtype, idx, scount);
		}break;
		case kINFOSKILL:{//技能
			unsigned char heroindex = 0;
			packet>>heroindex;
			if (NFC_HasTeamHero(heroindex))
			{
				NFC_GetHeroSkillManager(heroindex)->decodeSyncSkillItemPacket(packet);
			}
			 
		}break;
		case kINFOMAXHP:{//最大血量
			SetAttributeData(kMAXHP, packet);
		}break;
		case kINFOMAXMP:{//最大蓝量
			SetAttributeData(kMAXMP, packet);
		}break;
		case kINFOMINATTACK:{//最小攻击力
			SetAttributeData(kMINATTACK, packet);
		}break;
		case kINFOMAXATTACK:{//最大攻击力

			SetAttributeData(kMAXATTACK, packet);
		}break;
		case kINFOSPEED:{//速度

			SetAttributeData(kSPEED, packet);
		}break;
		case kINFOSTR:{//力量

			SetAttributeData(kSTRENGTH, packet);
		}break;
		case kINFOAGI:{//敏捷

			SetAttributeData(kAGILITY, packet);
		}break;
		case kINFOINTE:{//智力

			SetAttributeData(kINTELLIGENCE, packet);
		}break;
		case kINFOARMOR:{//护甲

			SetAttributeData(kARMOR, packet);
		}break;
		case kINFOEXPOSEARMOR:{//破甲

			SetAttributeData(kEXPOSEARMOR, packet);
		}break;
		case kINFOHIT:{//命中
			SetAttributeData(kHIT, packet);
		}break;
		case kINFODODGE:{//闪避
			SetAttributeData(kDODGE, packet);
		}break;
		case kINFOCRIT:{//暴击
			SetAttributeData(kCRIT, packet);
		}break;
		case kINFOUNCRIT:{//免爆
			SetAttributeData(kUNCRIT, packet);
		}break;
		case kINFOHEROCAPA:{//外套战斗力
			int a = 0;
			packet>>a;
		}break;
		case kINFOHEROCAPASCORE:{//外套战斗力评分
			int a =0 ;
			packet>>a;
			ROLEINFODATAHANDLER->m_pRIData->heroCapaScore_ = a;
		}break;
		case kINFOEQUIPCAPA:{//装备战斗力
			int a =0 ;
			packet>>a;
		}break;
		case kINFOEQUIPCAPASCORE:{
			int a =0 ;
			packet>>a;
			ROLEINFODATAHANDLER->m_pRIData->equipCapaScore_ = a;
		}break;
		case kINFOTECHCAPA:{//科技战斗力
			int a =0 ;
			packet>>a;
		}break;
		case kINFOTECHCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOTRAINCAPA:{//属性训练战斗力
			int a =0 ;
			packet>>a;
		}break;
		case kINFOTRAINCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOSOULCAPA:{//灵魂战斗力
			int a =0 ;
			packet>>a;
		}break;
		case kINFOSOULCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOFRIENDCAPA:{//好友战斗力
			int a =0 ;
			packet>>a;
		}break;
		case kINFOFRIENDCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOSUMCAPA:{//总战斗力，为英雄战斗力
			int a =0 ;
			packet>>a;
			ROLEINFODATAHANDLER->isUpdateCapacity_ = true;
			ROLEINFODATAHANDLER->m_pRIData->btlCapacity_ = a;
		}break;
		case kINFOSUMCAPASCORE:{//总战斗力评分
			int a =0 ;
			packet>>a;
		}break;
		case kINFOVIPLEVEL:{//VIP等级
			unsigned char a = 0;
			packet>>a;
			ROLEINFODATAHANDLER->m_pRIData->vipLevel_ = a;
		}break;
		case kINFOPRESTIGE:{//声望
			packet>>ROLEINFODATAHANDLER->m_pRIData->prestige_;
		}break;
		case  kINFOPVPRANK:{
			packet>>ROLEINFODATAHANDLER->m_pRIData->pvpRank_;
			
		}break;
		case kINFOBAGSIZE:{
			int data = 0;
			packet>>data;
			int bagType = 0;
			bagType = data>>16;
			if(bagType == BAG_ITEM)
			{
				BAGOTHEROBJECTHANDLER->m_bagMaxCount = data & 0x0000ffff;
			}
			else if(bagType == BAG_EQUIP)
			{
				BAGEQUIPDATAHANDLER->m_bagMaxCount = data & 0x0000ffff;
			}
			else if(bagType == BAG_SKIN)
			{
				//BAGSKINDATAHANDLER->m_bagMaxCount = data & 0x0000ffff;
			}

			EVENTSYSTEM->PushEvent(_TYPED_EVENT_BAG_OPENLOCK_SIZE_);

		}break;
		case kINFOROLESKIN:{//同步人物外套
			 int  newHeroUniqueID=0;
			 packet.read(newHeroUniqueID);
			 if(newHeroUniqueID!=NFC_GetTeamHero()->getHeroUniqueID())
			 {
				 ROLEINFODATAHANDLER->m_pRIData->bHadNewHeroTips=true;
			 }
			 HeroIllustratedDataHandler::get_instance2()->ActiveHeroSkinHandler(newHeroUniqueID);
			  
	    }break;
		case kINFOROLEEQUIP:{//同步人物装备
			unsigned char idx;
			packet>>idx;
			unsigned char heroPos=0;
			packet>>heroPos;
			unsigned char hasEquip;
			packet>>hasEquip;
			map<int,RoleEquipData*> mmm=NFC_GetHeroEquipManager(heroPos)->m_mapEquipList;
			if (hasEquip)
			{
				BagTemplateBase* btb = BAGTEMPLATEBASEHANDLER->decodeTemplatePacket(packet);
				BagEquipData* bed = new BagEquipData((EquipTemplate *)btb);
				bed->decodePacketData(packet);
				NFC_GetHeroEquipManager(heroPos)->m_mapEquipList[idx]->refreshEquipData(bed);
				NFC_GetHeroEquipManager(heroPos)->m_mapEquipList[idx]->hasEquip_=hasEquip;
				if (bed->__delectflag)
				{
					delete bed;bed=NULL;
				}
			}else{
				if(NFC_GetHeroEquipManager(heroPos)->m_mapEquipList[idx]->equipdata_){
					delete NFC_GetHeroEquipManager(heroPos)->m_mapEquipList[idx]->equipdata_;
					NFC_GetHeroEquipManager(heroPos)->m_mapEquipList[idx]->equipdata_=NULL;
				}
				NFC_GetHeroEquipManager(heroPos)->m_mapEquipList[idx]->hasEquip_=hasEquip;
			}
			needRefreshRoleEquip_=true;		//通知刷新
		}break;
		case kINFOROLESKILLNOTCH: {	//同步技能凹槽
			unsigned char  heroindex=0;
			packet.read(heroindex);	
			if (NFC_HasTeamHero(heroindex))
			{
				NFC_GetHeroSkillManager(heroindex)->decodeSyncSkillNotchItemPacket(packet);
			}
		}break;
		case kINFOQUESTTIPS:{//任务提示
			 //to do
			int  tmpValue=0;
			packet.read(tmpValue);
		}break;
		case kINFOMAILTIPS:{//邮件提醒
			short count = 0;
			packet.read(count);
			ROLEINFODATAHANDLER->m_pRIData->unReadEmailCounts_ = count;
		}break;
		case kINFOCOLLECTTIPS:{//征收提醒
			char times = 0;
			packet>>times;
			ROLEINFODATAHANDLER->m_pRIData->leftFreeRevenueCount_ = times;
		}break;
		case kINFOSHOPTIPS:{
			IByte have = 0;
			packet>>have;
			ROLEINFODATAHANDLER->m_pRIData->shopTipsNum_ = have;
		}break;
		case kINFOSERVANTIDENTITY:{
			char idt = 0;
			packet>>idt;
			int oldidt = ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_;
			int newidt = idt;
			ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_ = idt;
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_PLAYER_IDENTITYCHANGED_, _to_event_param_(oldidt), _to_event_param_(newidt));
		}break;
		case kINFOAPPLYFORFRIENDNUM:
		{
			unsigned char num = 0;
			packet>>num;
			ROLEINFODATAHANDLER->m_pRIData->applyforFriendNum_ = num;
		}break;
		case kINFOMAINTASKFINISHED:{	//同步任务完成信息
			 //to do
			IByte  taskNum=0;
			packet>>taskNum;
			ROLEINFODATAHANDLER->m_pRIData->finishTaskCounts_ = taskNum;
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ROLESTATUSWINDOW_);
		}break;
		case  kInfoHeroLevel: {		//同步英雄等级
			 short  heroLevel=0;
			 packet.read(heroLevel);
			 ROLEINFODATAHANDLER->m_pRIData->heroLevel_=heroLevel;
		}break;
		case  kInfoHeroExp:{		//同步英雄经验
			int  heroExp=0;
			packet.read(heroExp);
			ROLEINFODATAHANDLER->m_pRIData->heroopenIndex2_ = heroExp;
		}break;
		case kInfoHeroLeveUpNeedExp:{	//同步英雄升级所需经验
			int  heroLevelUpNeedExp=0;
			packet.read(heroLevelUpNeedExp);
			ROLEINFODATAHANDLER->m_pRIData->heroopenIndex3_ = heroLevelUpNeedExp;
		}break;
		case kInfoHerohonorLevel:{		//同步荣誉等级
			short  heroHonorLevel=0;
			packet.read(heroHonorLevel);
			ROLEINFODATAHANDLER->m_pRIData->honorLevel_=heroHonorLevel;
		}break;
		case kInfoHerohonorExp:{		//同步荣誉经验
			int  heroHonorExp=0;
			packet.read(heroHonorExp);
			ROLEINFODATAHANDLER->m_pRIData->honorExp_=heroHonorExp;
		}break;
		case kInfoHerohonorLevelUpExp:{	//同步荣誉升级所需经验
			int  heroHonorLevelUpNeedExp=0;
			packet.read(heroHonorLevelUpNeedExp);
			ROLEINFODATAHANDLER->m_pRIData->honorMaxExp_=heroHonorLevelUpNeedExp;
		}break;
		case kINFOAWARDNOTICE:{
			IByte have = 0;
			packet>>have;
			ROLEINFODATAHANDLER->m_pRIData->rewardprompt_ = have;
		}break;
		case kINFOACTIVITY:{
			IByte have = 0;
			packet>>have;
			ROLEINFODATAHANDLER->m_pRIData->activityprompt_ = have;
		}break;
		case  kInfoNewTask:{	//同步新任务
			IByte newTask = 0;
			packet>>newTask;
			if(newTask>0)
			MainTaskDataHandler::get_instance2()->m_bHadNewTask=true;
		}break;
		case  kACCUMURECH:
			{	//同步累积充值数
				int rechnum = 0;
				packet>>rechnum;
				ROLEINFODATAHANDLER->m_pRIData->accumuRechNum = rechnum;
			}
			break;
		case kMERNALEMPTY:
			{
				IByte miningstatus=0;
				packet>>miningstatus;
				ROLEINFODATAHANDLER->m_pRIData->mineralempty_ = miningstatus;
			}
			break;
		case kFREESUPPLICATION:
			{
				IByte freesupplica=0;
				packet>>freesupplica;
				ROLEINFODATAHANDLER->m_pRIData->freesupplica_ = freesupplica;
			}
			break;
		case kVIPREWARD:
			{
				IByte vipreward=0;
				packet>>vipreward;
				ROLEINFODATAHANDLER->m_pRIData->vipreward_ = vipreward;
				break;
			} 
		case kBOSSSCORE:
			{
				char bossscore = 0;
				packet>>bossscore;
				ROLEINFODATAHANDLER->m_pRIData->bossCanPlay_ = bossscore;
			}break;
		case kARENAREWARD_HINT:
			{
				IByte hint=0;	
				packet>>hint;
				ROLEINFODATAHANDLER->m_pRIData->arena_awardCanReceive_ = hint > 0 ? true:false ;
				EVENTSYSTEM->PushEvent(_TYPEF_EVENT_HINT_ARENAWINDOW_AWARD_);
			}break; 
		case kHEROSOUL:
			{ 
				RoleSoulsDataHandler::get_instance2()->decodeAddHeroSoulPacket(packet);
				break;
			}
		case kFREESUMMON_HINT:
			{ 
				IByte freesummon=0;
				packet>>freesummon;
				ROLEINFODATAHANDLER->m_pRIData->freesummon_ = freesummon;
			} 
			break;
		case kREFRESHSHOP:
			{ 
				IByte refreshshop=0;
				packet>>refreshshop;
				ROLEINFODATAHANDLER->m_pRIData->hasrefreshshop_ = refreshshop;
			} 
			break;
		case kBOSSFREETIME:
			{
				char time = 0;
				packet>>time;
				BOSSSCOREDATAHANDLER->m_iFreeTimesSync = time;
			}break;
		case kHUNTOBJECTLEFTTIME:
			{
				int time = 0;
				packet>>time;
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_BOSS_HUNT_LEFTTIME_, _to_event_param_(time));
			}break;
		case kLASTARENATIME:
			{
				ArenaInfoDataHandler::get_instance2()->decodeLastArenaTime(packet); 
			} break;
		case kMULTI_EXP:
			{
				UShort multi=0;
				packet>>multi;
				ROLEINFODATAHANDLER->m_pRIData->multiExp_=multi;
			}break;
		case kMULTI_MONEY:
			{
				UShort multi=0;
				packet>>multi;
				ROLEINFODATAHANDLER->m_pRIData->multiMoney_=multi;
			}break;
		case kUnLockSkill:
			{
				NFC_GetHeroSkillManager()->decodeSynUnLockSixthSkill(packet);
			}break;
		case kONEHEROSTRENGTH:
			{
				unsigned char heroindex = 0;
				int heroStreng = 0;
				packet >> heroindex;
				packet >> heroStreng;
				IHeroSkinItem* pHeroSkin = NFC_GetTeamHero(heroindex);
				if (pHeroSkin)
				{
					pHeroSkin->setHeroStrength(heroStreng);
				}
			}break;
		default:
			break;
		}
	}
	
	return true;
}

void SCRefreshInfoDataPacket::SetAttributeData(int attriIndex, cobra_win::DPacket & packet)
{
	unsigned char heroindex = 0;
	packet >> heroindex;
	int data = 0;
	packet >> data;
	std::map<int, int>::iterator it = NFC_GetHeroAttributeManager(heroindex)->mapPropertyList_.find(attriIndex);
	if (it == NFC_GetHeroAttributeManager(heroindex)->mapPropertyList_.end())
	{
		NFC_GetHeroAttributeManager(heroindex)->mapPropertyList_.insert(std::map<int, int>::value_type(attriIndex, data));
	}
	else
	{
		it->second = data;
	}

}

unsigned  int SCRefreshInfoDataPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_REFRESHINFODATA_;
}

bool SCRefreshInfoDataPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRefreshInfoDataPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	
	//Refresh UI
	this->notifyUIRefreshAffterPacketDecoded(packet);
	
	return true;
}

void SCRefreshInfoDataPacketFactory::notifyUIRefreshAffterPacketDecoded(const SCRefreshInfoDataPacket& packet)
{
	BAGOTHEROBJECTHANDLER->refreshUI4DataChanged();//通知ui背包物品刷新

	//对其他页面的刷新，包含数据部分等
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_REFRESH_UPDATEUI_);

	//抛出一个隐藏通讯转圈的消息
	NFC_showCommunicationWating(false);

	if (packet.needRefreshBagEquip_)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_EQUIPLIST_REFRESH);//通知装备列表刷新
	}

	if (packet.needRefreshRoleEquip_)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_ROLEEQUIP_REFRESH);
	}
}


