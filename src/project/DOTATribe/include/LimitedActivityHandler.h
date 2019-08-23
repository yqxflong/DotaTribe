//Name : LimitedActivityHandler
//Function : ��ʱ�
//Author : ��ǿ

#ifndef _DOTATRIBE_LimitedActivityHandler_H_
#define _DOTATRIBE_LimitedActivityHandler_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>
#include "../include/CPublicVarReader.h"

/*
         * ���Ϣ����<br>
         * byte count �����{<br>
         * int id<br>
         * String name ����<br>
         * String description ����<br>
         * byte rcount ��������<br>
         * for(rcount){<br>
         * byte type ���� 0��Ʒ 1��Ǯ 2���� 3��ʯ4����5����<br>
         * int amount <br>
         * if(type == 0){<br>
         * byte catagory<br>
         * int templateId<br>
         * string name<br>
		 * byte quality<br>
         * int iconId<br>
         * }<br>
         * String prompt ������ʾ<br>
         * byte canReceive �Ƿ������ȡ 0�� 1��<br>
         * }
         * }<br>
         */

class ActivityAward{
public:
	int rewardID_;			//��Ʒid
	unsigned char type_;	//0��Ʒ 1��Ǯ 2���� 3��ʯ4����5����<br>
	int amount_;
	//if type=0
	unsigned char catagory_;
	int templateId_;
	std::string name_;
	unsigned char quality_;
	int iconId_;
	//end if
	std::string prompt_;	//������ʾ
	unsigned char canReceive_;	//�Ƿ������ȡ 0�� 1��<br>
};

class ActivityItem{
public:
	int id_;
	std::string name_;
	std::string description_;
	int second_;	//����Ϊ��λ
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
	int m_nActivityID;		//��¼��ǰ��ȡ�ĻID
	int m_nRewardID;		//��¼��ǰ��ȡ�Ľ���ID
	int m_nDuringTickTime;	//������tickʱ��
	int m_iTickCount;		//Tick��ʱcount
	const int CHECK_TICKCOUNT;		//�������TICKˢ�½���
public:
	//��ʱ�
	std::vector<ActivityItem> ActivityItems_;
	int CurShowActivityID_;		//��ǰ��ʾ�ĻID
	//��¼����
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
	//��ȡ��Ʒiconid
	int GetAwardIconID(const ActivityAward& award);
	//��ȡ��Ʒquality
	int GetAwardQuality(const ActivityAward& award);
	//��ȡ�Ƿ���Ҫtips
	bool NeedAwardTips(const ActivityAward& award);
};

#endif