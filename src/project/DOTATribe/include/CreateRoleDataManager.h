// Name :		CreateRoleDataManager.h
// Function:	角色创建管理器
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef   _DOTATRIBE_CreateRoleDATAMANAGER_H
#define   _DOTATRIBE_CreateRoleDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   CreateRoleData: public IData
{
public:
	int	mRoleIndexID;								//角色索引ID
	int	mRoleModelID;								//角色模型ID
	int mRoleShapeID;								//角色外套ID
	int	mRoleSelectedAnimationID;					//选中动画ID
	int	mRoleDisabledAnimationID;					//未选中动画ID
	int	mRoleEntranceAnimationID;					//出场动画ID
	int	mRoleLeaveAnimationID;						//入场动画ID
	int	mRoleDescribeInfoID;						//角色介绍信息ID       

public:
	CreateRoleData();
	~CreateRoleData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class CreateRoleDataManager : public IDataManager, public cobra_win::Singleton2<CreateRoleDataManager>
{
public:
	std::map<int, CreateRoleData*> m_CreateRoleDataMapList;

public:
	CreateRoleDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~CreateRoleDataManager();

public:
	
    CreateRoleData * GetCreateRoleDataByID(int roleIndexId);

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
	friend   class   cobra_win::Singleton2<CreateRoleDataManager>;

};
  
#endif