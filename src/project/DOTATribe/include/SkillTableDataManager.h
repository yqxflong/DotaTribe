#ifndef   _DOTATRIBE_SKILLTABLEDATAMANAGER_H
#define   _DOTATRIBE_SKILLTABLEDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#define    CHARARRAYSIZE   128

#pragma pack(push, 1)

class   SkillTableData: public IData
{
public:
     int   skillItemID_;							 //技能ID
	 int   skillItemNameSYSID;						 //技能名称ID
	 int   skillItemIconID;							 //技能图标ID
	 int   skillItemActionsID;						 //技能动作组
	 char  skillItemLaunchTime[CHARARRAYSIZE];		 //技能发射时机
	 char  skillItemHurt[CHARARRAYSIZE];
	 char  skillItemDesc[CHARARRAYSIZE];
	 char  skillItemDurationTime[CHARARRAYSIZE];
	 char  skillItemLaunchLimitDesc[CHARARRAYSIZE];
	 char  skillItemProficientDesc[CHARARRAYSIZE];
     int   skillItemClientXPos;
	 int   skillItemClientYPos;
	 int   skillItemHurtCallTime;					//单位为 ms
	 float skillItemEffetCallTime;					//单位为 ms
	 int   skillItemResidesEffectID;

public:
	SkillTableData();
	~SkillTableData();

	std::string   GetSkillItemName();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SkillTableDataManager : public IDataManager, public cobra_win::Singleton2<SkillTableDataManager>
{
public:
	std::map<int, SkillTableData*>  m_skillTableMapList;

public:
	SkillTableDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SkillTableDataManager();

public:
	
    SkillTableData * GetSkillTableDataByID(int skillItemID);

	size_t  GetSkillTableCount(); 

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
	friend   class   cobra_win::Singleton2<SkillTableDataManager>;

};
  
#endif