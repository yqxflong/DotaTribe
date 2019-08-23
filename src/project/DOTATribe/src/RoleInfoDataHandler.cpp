//Name： RoleInfoDataHandler
//Function：管理player的信息
//Author：Johny

#include "../include/RoleInfoDataHandler.h"
#include "../include/GuideSystem.h"
#include "../include/AskForAddEnergyPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/GuidePacket.h"
#include "../include/LeadershipPacket.h"
#include "../include/CheckRoleBaseInfoPacket.h"

using namespace std;

RoleInfoData::RoleInfoData()
{
	attribute_=new Attribute();
	instanceId_=0;
	name_="";
	level_=0;
	exp_=0;
	maxExp_=0;
	vitality_=0;
	maxVitality_=0;
	jewels_=0;
	money_=0;
	vipLevel_=0;
	btlCapacity_=0;
	prestige_=0;
	heroLevel_=0;
	mapId_=0;
	stageId_=0;
	pvpRank_=0;
	guideStep_=0;
	finishTaskCounts_=0;
	unReadEmailCounts_=0;
	leftFreeRevenueCount_=0;
	shopTipsNum_=0;

	isFastAthleticSpeed=true;
	bHadNewHeroTips=false;
	athleticsSerialID_=0;
	heroCapaScore_=0;
	equipCapaScore_=0;
	slaveIdentity_=0;
	applyforFriendNum_=0;
	accumuRechNum = 0;
	freesupplica_ = 0;
	vipreward_ = 0;
	bossCanPlay_=0;
	arena_awardCanReceive_=0;
	freesummon_ = 0;
	hasrefreshshop_ = 0;
	multiExp_=0.0f;
	multiMoney_=0.0f;
}

RoleInfoData::~RoleInfoData()
{
	if(attribute_!=NULL)
	{
		delete attribute_;
		attribute_=NULL;
	} 
	instanceId_=0;
	name_="";
	level_=0;
	exp_=0;
	maxExp_=0;
	vitality_=0;
	maxVitality_=0;
	jewels_=0;
	money_=0;
	vipLevel_=0;
	btlCapacity_=0;
	prestige_=0;
	heroLevel_=0;
	mapId_=0;
	stageId_=0;
	pvpRank_=0;
	guideStep_=0;
	finishTaskCounts_=0;
	unReadEmailCounts_=0;
	leftFreeRevenueCount_=0;
	shopTipsNum_=0;

	isFastAthleticSpeed=true;
	bHadNewHeroTips=false;
	athleticsSerialID_=0;
	heroCapaScore_=0;
	equipCapaScore_=0;
	slaveIdentity_=0;
	applyforFriendNum_=0;
	accumuRechNum = 0;
	freesupplica_ = 0;
	vipreward_ = 0;
	bossCanPlay_=0;
	arena_awardCanReceive_=0;
	freesummon_ = 0;
	hasrefreshshop_ = 0;
}

void RoleInfoData::ResetRoleData()
{
	instanceId_=0;
	name_="";
	level_=0;
	exp_=0;
	maxExp_=0;
	vitality_=0;
	maxVitality_=0;
	jewels_=0;
	money_=0;
	vipLevel_=0;
	btlCapacity_=0;
	prestige_=0;
	heroLevel_=0;
	mapId_=0;
	stageId_=0;
	pvpRank_=0;
	guideStep_=0;
	finishTaskCounts_=0;
	unReadEmailCounts_=0;
	leftFreeRevenueCount_=0;
	shopTipsNum_=0;

	isFastAthleticSpeed=true;
	bHadNewHeroTips=false;
	athleticsSerialID_=0;
	heroCapaScore_=0;
	equipCapaScore_=0;
	slaveIdentity_=0;
	applyforFriendNum_=0;
	accumuRechNum = 0;
	freesupplica_ = 0;
	vipreward_ = 0;
	bossCanPlay_=0;
	arena_awardCanReceive_=0;
	freesummon_ = 0;
	hasrefreshshop_ = 0;
}

void RoleInfoData::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(instanceId_);
	NFC_ParsePacketString(packet,name_);
	packet.read(level_);
	packet.read(exp_);
	packet.read(maxExp_);
	packet.read(vitality_);
	packet.read(maxVitality_);
	packet.read(jewels_);
	packet.read(money_);
	packet.read(vipLevel_);
	packet.read(btlCapacity_);
	packet.read(prestige_);
	packet.read(heroLevel_);
	packet.read(heroopenIndex2_); 
	packet.read(heroopenIndex3_);
	packet.read(honorLevel_);
	packet.read(honorExp_);
	packet.read(honorMaxExp_);
	packet.read(mapId_);
	packet.read(stageId_);
	packet.read(pvpRank_);
	packet.read(guideStep_);
	packet.read(functionGuide_);
	packet.read(finishTaskCounts_);
	packet.read(unReadEmailCounts_);
	packet.read(leftFreeRevenueCount_);
	packet.read(shopTipsNum_);
	packet.read(heroCapaScore_);
	packet.read(equipCapaScore_);
	packet.read(slaveIdentity_);
	packet.read(applyforFriendNum_);
	packet.read(rewardprompt_);
	packet.read(activityprompt_);
	  
	//读人物通用属性

	IByte atributeCount=0;
	packet.read(atributeCount);
	attribute_->mapPropertyList_.clear();
	IByte attrType=0;
	int   attrValue=0;
	COMMON_BEIGIN_ARRAY(IByte,atributeCount)
	  packet.read(attrType);
	  packet.read(attrValue);
	  attribute_->mapPropertyList_.insert(std::map<int,int>::value_type(attrType,attrValue));
	COMMON_END_ARRAY

}



RoleInfoDataHandler::RoleInfoDataHandler(){
	m_pRIData = new RoleInfoData();
	playerstatus_=new PlayerStatus();
	isLock=true;
	isUpdateCapacity_ = false;
}

RoleInfoDataHandler::~RoleInfoDataHandler(){
	assert(m_pRIData!=NULL);
	delete m_pRIData;m_pRIData=NULL;
	assert(playerstatus_!=NULL);
	delete playerstatus_;playerstatus_=NULL;
}

bool RoleInfoDataHandler::init(){
	return true;
}

void RoleInfoDataHandler::onDestroy(){
	isLock=true;
	m_pRIData->ResetRoleData();
	playerstatus_->ResetStatus();
	isUpdateCapacity_ = false;
}


int  RoleInfoDataHandler::updateRoleAthleticsSerialID() 
{
    if(m_pRIData!=NULL&&!isLock)
	{
		m_pRIData->athleticsSerialID_+=1;
		return   m_pRIData->athleticsSerialID_;
	}
	//发送异常返回-1
	return  -1;  
}
int  RoleInfoDataHandler::getRoleCurAthleticsSerialID()
{
	if(m_pRIData!=NULL)
	{
		return   m_pRIData->athleticsSerialID_;
	}
	return  0;  
}

bool RoleInfoDataHandler::isOpenScene(int limitLv){
	return m_pRIData->level_>=limitLv;
}

void RoleInfoDataHandler::decodePacketData(cobra_win::DPacket & packet){
	ROLEINFODATAHANDLER->m_pRIData->decodePacketData(packet);
	isLock=false;
}


	/*
		请求增加体力
	*/
void RoleInfoDataHandler::AddTL_Request(){
	C2SBuyEnergyPacket packet;
	packet.Send();
}

	/*
		检查指定功能是否需要开启引导
	*/
bool RoleInfoDataHandler::CheckNewFuncOPenGuide(int ModuleID){
	int result=0;
	switch(ModuleID){
		case GuideSystem::_TYPED_NEWFUNC_1_HEROBAR://祭坛开启
			result=m_pRIData->functionGuide_&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_2_AREANA://竞技场开启
			ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_1_HEROBAR);
			result=(m_pRIData->functionGuide_>>1)&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_3_LABOR://奴隶开启
			result=(m_pRIData->functionGuide_>>2)&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE://远古遗迹
			ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_3_LABOR);
			result=(m_pRIData->functionGuide_>>3)&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_4_HEROTECH://神庙
			ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE);
			result=(m_pRIData->functionGuide_>>4)&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_5_TOWER://爬塔
			ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE);
			result=(m_pRIData->functionGuide_>>5)&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_7_MINERAL://寻宝开启
			ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_2_AREANA);
			result=(m_pRIData->functionGuide_>>6)&1;
			break;
		case GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE://金矿采集开启
			ToServerFinishNewFunc(GuideSystem::_TYPED_NEWFUNC_4_HEROTECH);
			result=(m_pRIData->functionGuide_>>7)&1;
			break;
		case  GuideSystem::_TYPED_GUIDE_1_://新手引导1
			result=(m_pRIData->functionGuide_>>8)&1;
			break;
		case  GuideSystem::_TYPED_GUIDE_2_://新手引导2
			result=(m_pRIData->functionGuide_>>9)&1;
			break;
		default:
			break;
	}
	if (result==0)
		return true;
	else
		return false;
}

	/*
		通知服务器完成新功能开启引导
	*/
void RoleInfoDataHandler::ToServerFinishNewFunc(int ModuleID){
	int ModuleID_toServer=0;
	switch(ModuleID){
	case GuideSystem::_TYPED_NEWFUNC_1_HEROBAR://祭坛开启
		ModuleID_toServer=1;
		break;
	case GuideSystem::_TYPED_NEWFUNC_2_AREANA://竞技场开启
		ModuleID_toServer=2;
		break;
	case GuideSystem::_TYPED_NEWFUNC_3_LABOR://矿洞开启
		ModuleID_toServer=3;
		break;
	case GuideSystem::_TYPED_NEWFUNC_6_TEAMPVE://远古遗迹
		ModuleID_toServer=4;
		break;
	case GuideSystem::_TYPED_NEWFUNC_4_HEROTECH://神庙
		ModuleID_toServer=5;
		break;
	case GuideSystem::_TYPED_NEWFUNC_5_TOWER://爬塔
		ModuleID_toServer=6;
		break;
	case GuideSystem::_TYPED_NEWFUNC_7_MINERAL://矿洞之寻宝
		ModuleID_toServer=7;
		break;
	case GuideSystem::_TYPED_NEWFUNC_8_GOLDMINE://金矿采集
		ModuleID_toServer=8;
		break;
	case  GuideSystem::_TYPED_GUIDE_1_://新手引导1
		ModuleID_toServer=9;
		break;
	case  GuideSystem::_TYPED_GUIDE_2_://新手引导2
		ModuleID_toServer=10;
		break;
	default:
		break;
	}
	//改变内存的值
	m_pRIData->functionGuide_=m_pRIData->functionGuide_|(1<<(ModuleID_toServer-1));
	//告诉服务器
	CSNewFuncOpenFinishPacket packet(m_pRIData->functionGuide_);
	packet.Send();
}


	/*
		目前到满体需要的时间
		5分钟回1点
	*/
int RoleInfoDataHandler::GetRestTimeToFullTL(){
	int rest=m_pRIData->maxVitality_-m_pRIData->vitality_;
	if (rest>0)
	{
		rest=5*60*rest;
		return rest;
	}

	return 0;
}











/************************************************************************/
/*                             LeadershipHandler                        */
/************************************************************************/

LeadershipHandler::LeadershipHandler(){
	level_ = 0;
	oldherolv_ = 0;
	newherolv_ = 0;
	oldhp_ = 0;
	addhp_ = 0;
	oldmp_ = 0;
	addmp_ = 0;
	oldminattack_ = 0;
	addminattack_ = 0;
	oldmaxattack_ = 0;
	addmaxattack_ = 0;
}

bool LeadershipHandler::init(){
	return true;
}

void LeadershipHandler::onDestroy(){
	;
}

void LeadershipHandler::decodePacketData(cobra_win::DPacket & packet){
	packet>>level_;
	packet>>oldherolv_;
	packet>>newherolv_;
	packet>>oldhp_;
	packet>>addhp_;
	packet>>oldmp_;
	packet>>addmp_;
	packet>>oldminattack_;
	packet>>addminattack_;
	packet>>oldmaxattack_;
	packet>>addmaxattack_;
}

void LeadershipHandler::LeadershipLvup_Quest(){
	CSLeadershipLvupPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void LeadershipHandler::HandleAfterResult(){
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEADERSHIPLVUPWINDOW_);
}

/************************************************************************/
/*                             CheckRoleBaseInfoHandler                 */
/************************************************************************/

CheckRoleBaseInfoHandler::CheckRoleBaseInfoHandler(){
	m_HeroLv = 0;
	m_BaseHP = 0;
	m_BaseMP = 0;
	m_BaseMinAtk = 0;
	m_BaseMaxAtk = 0;
}

bool CheckRoleBaseInfoHandler::init(){
	return true;
}

void CheckRoleBaseInfoHandler::onDestroy(){
	;
}


void CheckRoleBaseInfoHandler::decodePacketData(cobra_win::DPacket & packet){
	packet>>m_HeroLv;
	packet>>m_BaseHP;
	packet>>m_BaseMP;
	packet>>m_BaseMinAtk;
	packet>>m_BaseMaxAtk;
}

void CheckRoleBaseInfoHandler::ToServerRoleBaseInfo(){
	CSCheckRoleBaseInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void CheckRoleBaseInfoHandler::RoleBaseInfoResult(){
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_CHECKLEADERSHIPWINDOW_);
}
