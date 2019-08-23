// Name :		LoadingAnimationDataManager.h
// Function:	Loading界面数据管理
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_LOADINGANIMATIONDATAMANAGER_H
#define   _DOTATRIBE_LOADINGANIMATIONDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   LoadingAnimationData: public IData
{
public:
	int  mId; 									//ID
	int  mProcedureId; 							//流程ID
	int  mIsNeedAnimation;						//是否需要动画
	int  mBackgroundSuondID; 					//背景音乐ID

public:
	LoadingAnimationData();
	~LoadingAnimationData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class LoadingAnimationManager: public IDataManager, public cobra_win::Singleton2<LoadingAnimationManager>
{
public:
	std::map<int, LoadingAnimationData*> m_LoadingAnimationList;

public:
	LoadingAnimationManager(bool bLoadFromDB, bool bEncryption);
	virtual ~LoadingAnimationManager();

public:
	
    LoadingAnimationData * GeLoadingAnimationDataByID(int Id);

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
	friend   class   cobra_win::Singleton2<LoadingAnimationData>;

};
  
#endif