//Name��SCRrefreshInfoDataPacket
//Function��s->c �����������·���ͬ��������Ϣ
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
	//~~~~����Ƿ�����
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
		case kINFOLEVEL:{//����
			unsigned short lev = 0;
			packet>>lev;
			ROLEINFODATAHANDLER->m_pRIData->level_ = lev;
		}break;
		case kINFOEXP:{//����
			int exp = 0;
			packet>>exp;
			ROLEINFODATAHANDLER->m_pRIData->exp_ = exp;
		}break;
		case kINFOMAXEXP:{//�����
			int maxexp = 0;
			packet>>maxexp;
			ROLEINFODATAHANDLER->m_pRIData->maxExp_ = maxexp;
		}break;
		case kINFOVITALITY:{//����
			unsigned short vi= 0;
			packet>>vi;
			ROLEINFODATAHANDLER->m_pRIData->vitality_ = vi;
		}break;
		case kINFOJEWELS:{//��ʯ
			int jewel = 0;
			packet>>jewel;
			ROLEINFODATAHANDLER->m_pRIData->jewels_ = jewel;
		}break;
		case kINFOMONEY:{//��Ǯ
			int money = 0;
			packet>>money;
			ROLEINFODATAHANDLER->m_pRIData->money_ = money;
		}break;
		case kINFOBAGGRID:{//����
			unsigned short index = 0;
			unsigned short num = 0;
			unsigned char bagType = 0;
			packet>>bagType;
			packet>>index;
			packet>>num;
			int vectorIndex = 0;		//�洢���б��е���ţ�����ȡ���ݺ���ʾ
			if(num > 0)
			{
				//��ȡ��Ʒģ��
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
					needRefreshBagEquip_=true;    //��Ҫ֪ͨˢ��
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

			//����֪ͨ�������������ݸ���
			std::string idx = _to_event_param_((int)vectorIndex);
			std::string scount = _to_event_param_((int)num);
			std::string _bagtype = _to_event_param_((int)bagType);//���㱳���ж����ĸ�������Ʒ
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_BAGREFRESH_BAG_ITEM_, _bagtype, idx, scount);
		}break;
		case kINFOSKILL:{//����
			unsigned char heroindex = 0;
			packet>>heroindex;
			if (NFC_HasTeamHero(heroindex))
			{
				NFC_GetHeroSkillManager(heroindex)->decodeSyncSkillItemPacket(packet);
			}
			 
		}break;
		case kINFOMAXHP:{//���Ѫ��
			SetAttributeData(kMAXHP, packet);
		}break;
		case kINFOMAXMP:{//�������
			SetAttributeData(kMAXMP, packet);
		}break;
		case kINFOMINATTACK:{//��С������
			SetAttributeData(kMINATTACK, packet);
		}break;
		case kINFOMAXATTACK:{//��󹥻���

			SetAttributeData(kMAXATTACK, packet);
		}break;
		case kINFOSPEED:{//�ٶ�

			SetAttributeData(kSPEED, packet);
		}break;
		case kINFOSTR:{//����

			SetAttributeData(kSTRENGTH, packet);
		}break;
		case kINFOAGI:{//����

			SetAttributeData(kAGILITY, packet);
		}break;
		case kINFOINTE:{//����

			SetAttributeData(kINTELLIGENCE, packet);
		}break;
		case kINFOARMOR:{//����

			SetAttributeData(kARMOR, packet);
		}break;
		case kINFOEXPOSEARMOR:{//�Ƽ�

			SetAttributeData(kEXPOSEARMOR, packet);
		}break;
		case kINFOHIT:{//����
			SetAttributeData(kHIT, packet);
		}break;
		case kINFODODGE:{//����
			SetAttributeData(kDODGE, packet);
		}break;
		case kINFOCRIT:{//����
			SetAttributeData(kCRIT, packet);
		}break;
		case kINFOUNCRIT:{//�ⱬ
			SetAttributeData(kUNCRIT, packet);
		}break;
		case kINFOHEROCAPA:{//����ս����
			int a = 0;
			packet>>a;
		}break;
		case kINFOHEROCAPASCORE:{//����ս��������
			int a =0 ;
			packet>>a;
			ROLEINFODATAHANDLER->m_pRIData->heroCapaScore_ = a;
		}break;
		case kINFOEQUIPCAPA:{//װ��ս����
			int a =0 ;
			packet>>a;
		}break;
		case kINFOEQUIPCAPASCORE:{
			int a =0 ;
			packet>>a;
			ROLEINFODATAHANDLER->m_pRIData->equipCapaScore_ = a;
		}break;
		case kINFOTECHCAPA:{//�Ƽ�ս����
			int a =0 ;
			packet>>a;
		}break;
		case kINFOTECHCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOTRAINCAPA:{//����ѵ��ս����
			int a =0 ;
			packet>>a;
		}break;
		case kINFOTRAINCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOSOULCAPA:{//���ս����
			int a =0 ;
			packet>>a;
		}break;
		case kINFOSOULCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOFRIENDCAPA:{//����ս����
			int a =0 ;
			packet>>a;
		}break;
		case kINFOFRIENDCAPASCORE:{
			int a =0 ;
			packet>>a;
		}break;
		case kINFOSUMCAPA:{//��ս������ΪӢ��ս����
			int a =0 ;
			packet>>a;
			ROLEINFODATAHANDLER->isUpdateCapacity_ = true;
			ROLEINFODATAHANDLER->m_pRIData->btlCapacity_ = a;
		}break;
		case kINFOSUMCAPASCORE:{//��ս��������
			int a =0 ;
			packet>>a;
		}break;
		case kINFOVIPLEVEL:{//VIP�ȼ�
			unsigned char a = 0;
			packet>>a;
			ROLEINFODATAHANDLER->m_pRIData->vipLevel_ = a;
		}break;
		case kINFOPRESTIGE:{//����
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
		case kINFOROLESKIN:{//ͬ����������
			 int  newHeroUniqueID=0;
			 packet.read(newHeroUniqueID);
			 if(newHeroUniqueID!=NFC_GetTeamHero()->getHeroUniqueID())
			 {
				 ROLEINFODATAHANDLER->m_pRIData->bHadNewHeroTips=true;
			 }
			 HeroIllustratedDataHandler::get_instance2()->ActiveHeroSkinHandler(newHeroUniqueID);
			  
	    }break;
		case kINFOROLEEQUIP:{//ͬ������װ��
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
			needRefreshRoleEquip_=true;		//֪ͨˢ��
		}break;
		case kINFOROLESKILLNOTCH: {	//ͬ�����ܰ���
			unsigned char  heroindex=0;
			packet.read(heroindex);	
			if (NFC_HasTeamHero(heroindex))
			{
				NFC_GetHeroSkillManager(heroindex)->decodeSyncSkillNotchItemPacket(packet);
			}
		}break;
		case kINFOQUESTTIPS:{//������ʾ
			 //to do
			int  tmpValue=0;
			packet.read(tmpValue);
		}break;
		case kINFOMAILTIPS:{//�ʼ�����
			short count = 0;
			packet.read(count);
			ROLEINFODATAHANDLER->m_pRIData->unReadEmailCounts_ = count;
		}break;
		case kINFOCOLLECTTIPS:{//��������
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
		case kINFOMAINTASKFINISHED:{	//ͬ�����������Ϣ
			 //to do
			IByte  taskNum=0;
			packet>>taskNum;
			ROLEINFODATAHANDLER->m_pRIData->finishTaskCounts_ = taskNum;
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ROLESTATUSWINDOW_);
		}break;
		case  kInfoHeroLevel: {		//ͬ��Ӣ�۵ȼ�
			 short  heroLevel=0;
			 packet.read(heroLevel);
			 ROLEINFODATAHANDLER->m_pRIData->heroLevel_=heroLevel;
		}break;
		case  kInfoHeroExp:{		//ͬ��Ӣ�۾���
			int  heroExp=0;
			packet.read(heroExp);
			ROLEINFODATAHANDLER->m_pRIData->heroopenIndex2_ = heroExp;
		}break;
		case kInfoHeroLeveUpNeedExp:{	//ͬ��Ӣ���������辭��
			int  heroLevelUpNeedExp=0;
			packet.read(heroLevelUpNeedExp);
			ROLEINFODATAHANDLER->m_pRIData->heroopenIndex3_ = heroLevelUpNeedExp;
		}break;
		case kInfoHerohonorLevel:{		//ͬ�������ȼ�
			short  heroHonorLevel=0;
			packet.read(heroHonorLevel);
			ROLEINFODATAHANDLER->m_pRIData->honorLevel_=heroHonorLevel;
		}break;
		case kInfoHerohonorExp:{		//ͬ����������
			int  heroHonorExp=0;
			packet.read(heroHonorExp);
			ROLEINFODATAHANDLER->m_pRIData->honorExp_=heroHonorExp;
		}break;
		case kInfoHerohonorLevelUpExp:{	//ͬ�������������辭��
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
		case  kInfoNewTask:{	//ͬ��������
			IByte newTask = 0;
			packet>>newTask;
			if(newTask>0)
			MainTaskDataHandler::get_instance2()->m_bHadNewTask=true;
		}break;
		case  kACCUMURECH:
			{	//ͬ���ۻ���ֵ��
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
	BAGOTHEROBJECTHANDLER->refreshUI4DataChanged();//֪ͨui������Ʒˢ��

	//������ҳ���ˢ�£��������ݲ��ֵ�
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_REFRESH_UPDATEUI_);

	//�׳�һ������ͨѶתȦ����Ϣ
	NFC_showCommunicationWating(false);

	if (packet.needRefreshBagEquip_)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_EQUIPLIST_REFRESH);//֪ͨװ���б�ˢ��
	}

	if (packet.needRefreshRoleEquip_)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_ROLEEQUIP_REFRESH);
	}
}


