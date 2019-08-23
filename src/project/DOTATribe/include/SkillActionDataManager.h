#ifndef   _DOTATRIBE_SKILLACTIONDATAMANAGER_H
#define   _DOTATRIBE_SKILLACTIONDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <vector>
#include <map>

#pragma pack(push, 1)

class   SkillActionData: public IData
{
public:
	  int   skillActionsID_;                     //动作组ID  
	  int   skillSituActionID_;                  //原地动作ID
	  int   skillSituActionType_;                //原地动作类型
 
	  int   skillAdvanceActionID_;			     //前进动作ID
	  int   skillAdvanceType_;				  	 //前进动作类型
	  float skillAdvanceSpeed_;					 //前进动作速度  像素/帧
 
	  int   skillTargetActionID_;				 //目标动作ID	
	  int   skillTargetActionType_;				 //目标动作类型
 
 	  int   skillReturnActionID_;				 //返回动作ID	
	  int   skillReturnActionType_;				 //返回动作类型
	  float skillReturnSpeed_;					 //返回移动速度  像素/帧

	  std::vector<int> skillActiveActionVec_;	 //有效的动作组
	   
public:
	SkillActionData();
	~SkillActionData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SkillActionDataManager : public IDataManager, public cobra_win::Singleton2<SkillActionDataManager>
{
public:
	std::map<int, SkillActionData*>  m_skillActionMapList_;

public:
	SkillActionDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SkillActionDataManager();

public:
	
    SkillActionData * GetSkillActionItemByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<SkillActionDataManager>;

};
  
#endif