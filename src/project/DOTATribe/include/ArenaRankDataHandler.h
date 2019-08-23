#ifndef   _DOTATRIBE_ARENARANKDATAHANDLER_H_
#define   _DOTATRIBE_ARENARANKDATAHANDLER_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ���������а�
//date:   2013/07/22
///////////////////////////////////////////////// 
#include   <include/common/Singleton.h>
#include   "../include/IDataHandler.h" 
#include   <string>
#include   <include/mem/DPacket.h>
#include   <string>
#include   <vector>
 
typedef struct rolerankinfo
{
	int  roleID;
	int  roleIconID;
	std::string  roleName;
	short  roleLevel;
	int  roleRankScore;
	int  roleBltScore;
public:
	rolerankinfo()
	{
		roleID=0;
		roleIconID=0;
		roleName="";
		roleLevel=0;
		roleRankScore=0;
		roleBltScore=0;
	}
}RoleRankInfo,* PRoleRankInfo;

class  ArenaRankData
{
public:
	short rankCount;
	std::vector<PRoleRankInfo> rankListVec;	
	ArenaRankData()
	{
		rankCount=0;
		rankListVec.clear();
	}
	~ArenaRankData()
	{
		rankCount=0;
		size_t rankSize=rankListVec.size();
		for(size_t rankIndex=0;rankIndex<rankSize;rankIndex++)
		{
			PRoleRankInfo pRoleRankInfo=rankListVec.at(rankIndex);
		    delete pRoleRankInfo;
		}
		rankListVec.clear();
	}
	void decodePacketData(cobra_win::DPacket & packet);
};

class   ArenaRankDataHandler: public IDataHandler,public cobra_win::Singleton2<ArenaRankDataHandler>
{
public: 
     ArenaRankData * m_pArenaRankData;
public:
	 ArenaRankDataHandler();
	~ArenaRankDataHandler();

	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet); 
	 
	/*
		���ٽӿ�
	*/
	virtual void onDestroy();

	/*
		��ʼ���ӿ�
	*/
	virtual bool init();
 

public:
	friend   class   cobra_win::Singleton2<ArenaRankDataHandler>;
};

#define   ARENARANKDATAHANDLER			(ArenaRankDataHandler::get_instance2())
 
#endif