#ifndef   _DOTATRIBE_NPCTALKDATAMANAGER_H
#define   _DOTATRIBE_NPCTALKDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
 
typedef struct talknode_tag
{
	enum
	{
		_TALK_PLAYER_TYPE_,
		_TALK_NPC_TYPE_,
	};
	int  contentRoleType;
	int  contentSysID;
public:
	talknode_tag()
	{
		contentRoleType=0;
		contentSysID=-1;
	}
}TalkNode,*PTalkNode;


class   NpcTalkData: public IData
{
public:
     int  npctalkID;
	 int  npcMapID;
	 int  npcStageID;
	 int  beforBattlePageCount;
	 std::vector<TalkNode> beforBattlePageVect;
	 int  winBattlePageCount;
	 std::vector<TalkNode> winBattlePageVect;
	 int  failBattlePageCount;
	 std::vector<TalkNode> failBattlePageVect;
public:
	NpcTalkData();
	~NpcTalkData();
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class NpcTalkDataManager : public IDataManager, public cobra_win::Singleton2<NpcTalkDataManager>
{
public:
	std::map<int, NpcTalkData*>   m_npcTalkDataMap;;

public:
	NpcTalkDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~NpcTalkDataManager();

public:
    NpcTalkData * GetNpcTalkDataWithMapAndStage(int mapID,int stageID);

	/*
		得到对应的数据管理器名称
	*/
	virtual  std::string   GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		初始化数据管理器
	*/
	virtual  bool  Init();
	/*
		数据管理器帧更新处理
	*/
	virtual  void  Tick();
	/*
		销毁数据管理器
	*/
	virtual  void  Destroy();

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<NpcTalkDataManager>;

};
  
#endif