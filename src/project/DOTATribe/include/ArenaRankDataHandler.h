#ifndef   _DOTATRIBE_ARENARANKDATAHANDLER_H_
#define   _DOTATRIBE_ARENARANKDATAHANDLER_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  竞技场排行榜
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
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet); 
	 
	/*
		销毁接口
	*/
	virtual void onDestroy();

	/*
		初始化接口
	*/
	virtual bool init();
 

public:
	friend   class   cobra_win::Singleton2<ArenaRankDataHandler>;
};

#define   ARENARANKDATAHANDLER			(ArenaRankDataHandler::get_instance2())
 
#endif