#ifndef   _DOTATRIBE_ROLESHAEPROPERTYDATA_H
#define   _DOTATRIBE_ROLESHAEPROPERTYDATA_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   RoleShapePropertyData: public IData
{
public:
	  int  roleShapeID_;
	  char roleImageName[64];
	  char roleXiuXianActionName[64];
	  char roleXingZouActionName[64];
	  char roleNormalAttackActionName[64];
	  char roleRemoteAttackActionName[64];
	  char roleHurtActionName[64];
	  char roleDeadActionName[64];
	  char roleDodgeActionName[64];
	  char roleCritActionName[64];
	  char roleWinActionName[64];
public:
	RoleShapePropertyData();
	~RoleShapePropertyData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class RoleShapePropertyDataManager : public IDataManager, public cobra_win::Singleton2<RoleShapePropertyDataManager>
{
public:
	std::map<int, RoleShapePropertyData*> m_RoleShapePropertyList;

public:
	RoleShapePropertyDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~RoleShapePropertyDataManager();

public:
	
    RoleShapePropertyData * GetRoleShapeDateById(int roleShapeId);

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
	friend   class   cobra_win::Singleton2<RoleShapePropertyDataManager>;

};




#endif