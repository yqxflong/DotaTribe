//Name : LimitedActivityHandler
//Function : 限时活动
//Author : 尹强

#include <cocos2d.h>
#include "../include/LimitedActivityHandler.h"
#include "../include/MainTaskPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/LimitActivityPacket.h"

using namespace std;

NoticeData::NoticeData()
{
	mTitle = "";
	mContent = "";
};

NoticeData::~NoticeData()
{
	mTitle = "";
	mContent = "";
};

LimitedActivityHandler::LimitedActivityHandler()
:m_nActivityID(0)
,m_nRewardID(0)
,CurShowActivityID_(0)
,m_nDuringTickTime(0)
,m_iTickCount(0)
,CHECK_TICKCOUNT(DOTATribeApp::get_instance2()->GetFPS() * 60){
	ActivityItems_.clear();
}

void LimitedActivityHandler::onDestroy(){
	ActivityItems_.clear();
}
	
bool LimitedActivityHandler::init(){
	return true;
}

//BEGAIN: Query Activity list
void LimitedActivityHandler::LActivity_Query(){
	CSLActivityPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void LimitedActivityHandler::decodePacketData_Query(cobra_win::DPacket & packet){
	ActivityItems_.clear();
	unsigned short len=0;
	unsigned char count=0;
	packet>>count;
	for (int i=0;i<count;i++)
	{
		ActivityItem item;
		packet>>item.id_;
		NFC_ParsePacketString(packet,item.name_);
		NFC_ParsePacketString(packet,item.description_);
		packet>>item.second_;
		unsigned char rcount=0;
		packet>>rcount;
		for (int i=0;i<rcount;i++)
		{
			ActivityAward award;
			packet>>award.rewardID_;
			packet>>award.type_;
			packet>>award.amount_;
			if (award.type_==0)
			{
				packet>>award.catagory_;
				packet>>award.templateId_;
				NFC_ParsePacketString(packet,award.name_);
				packet>>award.quality_;
				packet>>award.iconId_;
			}
			//propt
			NFC_ParsePacketString(packet,award.prompt_);
			//end propt
			packet>>award.canReceive_;
			item.ActivityAwards_.push_back(award);
		}
		ActivityItems_.push_back(item);
	}
}

void LimitedActivityHandler::decodePacketData_Notice(cobra_win::DPacket & packet)
{
	char buff[2048]={0};
	m_FontstyleIdMap;
	IByte num = 0 ;
	packet>>num;
	m_FontstyleIdMap.clear();
	for (IByte i=0;i<num;i++)
	{
		int fontId = 0; //格式编号
		int fontSize= 0 ;//字体大小
		std::string fontName = "";//字体名称
		std::string fontColor = "";//字体颜色
		packet>>fontId;
		packet>>fontSize;
		NFC_ParsePacketString(packet,fontName);
		NFC_ParsePacketString(packet,fontColor);
		sprintf(buff,_RICH_TEXT_TYPE_,fontSize,fontName.c_str(),fontColor.c_str(),"%s");
		std::string temp = buff;
		m_FontstyleIdMap.insert(std::map<int,std::string>::value_type(fontId,buff));
	}
	IByte count = 0;
	packet>>count;
	m_ContentVector.clear();
	for (IByte i=0;i<count;i++)
	{
		NoticeData data;
		int id = 0;
		packet>>id;
		std::map<int,std::string>::iterator it = m_FontstyleIdMap.find(id);
		if (it != m_FontstyleIdMap.end())
		{
			std::string temptitle = "";
			memset(buff,0,sizeof(buff));
			NFC_ParsePacketString(packet,temptitle);
			sprintf(buff,it->second.c_str(),temptitle.c_str());
			data.mTitle = buff;
		}
		int idcontent = 0;
		packet>>idcontent;
		std::map<int,std::string>::iterator it1 = m_FontstyleIdMap.find(idcontent);
		if (it1 != m_FontstyleIdMap.end())
		{
			std::string tempcontent = "";
			memset(buff,0,sizeof(buff));
			NFC_ParsePacketString(packet,tempcontent);
			sprintf(buff,it1->second.c_str(),tempcontent.c_str());
			data.mContent = buff;
		}
		m_ContentVector.push_back(data);
	}
}

void LimitedActivityHandler::HandleAfterQueryLActivity(){
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_);
}
//END

//BEGAIN:Get Award From Server
void LimitedActivityHandler::GetAwardFromServer(int activityID,int rewardID){
	m_nActivityID=activityID;
	m_nRewardID=rewardID;
	CSLActivityGetAwardPacket packet(activityID,rewardID);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void LimitedActivityHandler::HandleAfterGetAward(int result){
	recordAwardHaveReceived(m_nActivityID,m_nRewardID);
	NFC_showCommunicationWating(false);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_);
}
//END

//=======================The Logic Inner Game=========================
//获取奖品图标文件
int LimitedActivityHandler::GetAwardIconID(const ActivityAward& award){
	switch(award.type_){
		case kDT_AWARD_OBJECT:{
			return award.iconId_;
		 }
		case kDT_AWARD_MONEY:{
			int iconid=NFC_getValueFromClientConst(CONST_KEY_ICON_GOLD);
			return iconid;
		 }
		case kDT_AWARD_EXP:{
			int iconid=NFC_getValueFromClientConst(CONST_KEY_ICON_EXP);
			return iconid;
		}			
		case kDT_AWARD_DIAMOND:{
			int iconid=NFC_getValueFromClientConst(CONST_KEY_ICON_DIAMOND);
			return iconid;
		}
		case kDT_AWARD_PRESTIGE:{
			int iconid=NFC_getValueFromClientConst(CONST_KEY_ICON_PRESTAGE);
			return iconid;
		 }
		case kDT_AWARD_POWER:{
			int iconid=NFC_getValueFromClientConst(CONST_KEY_ICON_ENG);
			return iconid;
		 }
		default:
			return -1;
	}
}

//获取奖品quality
int LimitedActivityHandler::GetAwardQuality(const ActivityAward& award){
	if (award.type_==kDT_AWARD_OBJECT){
		return award.quality_;
	}else if(award.type_==kDT_AWARD_MONEY){
		return _GOLD_QUALITY_RESID_;
	}else if(award.type_==kDT_AWARD_EXP){
		return _EXP_QUALITY_RESID_;
	}else if(award.type_==kDT_AWARD_DIAMOND){
		return _DIAMOND_QUALITY_RESID_;
	}else if(award.type_==kDT_AWARD_PRESTIGE){
		return _PREGIST_QUALITY_RESID_;
	}else if(award.type_==kDT_AWARD_POWER){
		return _POWER_QUALITY_RESID_;
	}
	
}

//获取是否需要tips
bool LimitedActivityHandler::NeedAwardTips(const ActivityAward& award){
	return award.type_==kDT_AWARD_OBJECT;
}

void LimitedActivityHandler::recordAwardHaveReceived(int aID,int rID){
	vector<ActivityItem>::iterator it=ActivityItems_.begin();
	for (;it!=ActivityItems_.end();)
	{
		vector<ActivityItem>::iterator tmp=it++;
		ActivityItem &item=*tmp;
		//找到指定的活动
		if (item.id_==aID&&item.ActivityAwards_.size()>0)
		{
			vector<ActivityAward>::iterator it_awards=item.ActivityAwards_.begin();
			for (;it_awards!=item.ActivityAwards_.end();)
			{
				vector<ActivityAward>::iterator tmp_awards=it_awards++;
				ActivityAward& award=*tmp_awards;
				//找到指定奖品
				if (award.rewardID_==rID){
					//删除一个奖品，且迭代指针回到起点
					item.ActivityAwards_.erase(tmp_awards);
					it_awards=item.ActivityAwards_.begin();
					//如果奖品数已为空，则删除该活动
					if (item.ActivityAwards_.size()==0)
					{
						ActivityItems_.erase(tmp);
						it=ActivityItems_.begin();
					}
					break;
				}
			}
		}
	}
}


//计算所有活动剩余时间
void LimitedActivityHandler::CaculateAllActivityTime(){
	m_nDuringTickTime++;
	m_iTickCount++;
	//一秒
	if (m_iTickCount > DOTATribeApp::get_instance2()->GetFPS())
	{
		vector<ActivityItem>::iterator it=ActivityItems_.begin();
		vector<ActivityItem>::iterator it_end=ActivityItems_.end();
		for (;it!=it_end;it++)
		{
			ActivityItem& item=*it;
			if (item.second_>0)
				item.second_--;
			if (item.second_<0)
				item.second_=0;
		}
		m_iTickCount = 0;
	}
	//每分钟刷新一次界面
	if (m_nDuringTickTime>=CHECK_TICKCOUNT)
	{
		m_nDuringTickTime=0;
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_);
	}
}


void LimitedActivityHandler::ToServerExchangeCdkey(std::string cdkey)
{
	CSExchangePacket packet(cdkey);
	packet.Send();

	NFC_showCommunicationWating(true);
}


void  LimitedActivityHandler::ToClientExchangeCdKeyResult(char result)
{
	NFC_showCommunicationWating(false);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_LIMITACTIVITY_EXCHANGE_CDKEY_RESLUT_, _to_event_param_((int)result));
}