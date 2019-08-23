//Name : LimitedActivityHandler
//Function : 限时活动
//Author : 尹强

#ifndef _DOTATRIBE_LimitedActivityHandler_H_
#define _DOTATRIBE_LimitedActivityHandler_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>
#include "../include/CPublicVarReader.h"

/*
         * 活动信息返回<br>
         * byte count 活动数量{<br>
         * int id<br>
         * String name 名称<br>
         * String description 介绍<br>
         * byte rcount 奖励数量<br>
         * for(rcount){<br>
         * byte type 类型 0物品 1金钱 2经验 3钻石4声望5体力<br>
         * int amount <br>
         * if(type == 0){<br>
         * byte catagory<br>
         * int templateId<br>
         * string name<br>
		 * byte quality<br>
         * int iconId<br>
         * }<br>
         * String prompt 奖励提示<br>
         * byte canReceive 是否可以领取 0否 1是<br>
         * }
         * }<br>
         */

class ActivityAward{
public:
	int rewardID_;			//奖品id
	unsigned char type_;	//0物品 1金钱 2经验 3钻石4声望5体力<br>
	int amount_;
	//if type=0
	unsigned char catagory_;
	int templateId_;
	std::string name_;
	unsigned char quality_;
	int iconId_;
	//end if
	std::string prompt_;	//奖励提示
	unsigned char canReceive_;	//是否可以领取 0否 1是<br>
};

class ActivityItem{
public:
	int id_;
	std::string name_;
	std::string description_;
	int second_;	//以秒为单位
	std::vector<ActivityAward> ActivityAwards_;
	ActivityItem(){
		id_=0;
		second_=0;
		ActivityAwards_.clear();
	}
	bool hasAwardActive(){
		for (unsigned int i=0;i<ActivityAwards_.size();i++)
		{
			const ActivityAward& award=ActivityAwards_[i];
			if (award.canReceive_==1)
			{
				return true;
			}
		}
		return false;
	}
};

class NoticeData
{
	default_construct_destroy(NoticeData)
public:
	std::string mTitle;
	std::string mContent;
};

class LimitedActivityHandler : public IDataHandler, public cobra_win::Singleton2<LimitedActivityHandler>
{
private:
	int m_nActivityID;		//记录当前领取的活动ID
	int m_nRewardID;		//记录当前领取的奖励ID
	int m_nDuringTickTime;	//经过的tick时间
	int m_iTickCount;		//Tick记时count
	const int CHECK_TICKCOUNT;		//间隔多少TICK刷新界面
public:
	//限时活动
	std::vector<ActivityItem> ActivityItems_;
	int CurShowActivityID_;		//当前显示的活动ID
	//登录公告
	std::string NoticeContent_;
public:
	std::map<int,std::string> m_FontstyleIdMap;
	std::vector<NoticeData> m_ContentVector;
public:
	LimitedActivityHandler();
	virtual ~LimitedActivityHandler(){};

protected:
	virtual void onDestroy();
	virtual bool init();

protected:
	void recordAwardHaveReceived(int aID,int rID);

public:
	void LActivity_Query();
	void decodePacketData_Query(cobra_win::DPacket & packet);
	void decodePacketData_Notice(cobra_win::DPacket & packet);
	void HandleAfterQueryLActivity();
	void GetAwardFromServer(int activityID,int rewardID);
	void HandleAfterGetAward(int result);

	void CaculateAllActivityTime();

	void ToServerExchangeCdkey(std::string cdkey);
	void ToClientExchangeCdKeyResult(char result);

public:
	//获取奖品iconid
	int GetAwardIconID(const ActivityAward& award);
	//获取奖品quality
	int GetAwardQuality(const ActivityAward& award);
	//获取是否需要tips
	bool NeedAwardTips(const ActivityAward& award);
};

#endif