#ifndef   _DOTATRIBE_CAMERASHAKEDATAMANAGER_H
#define   _DOTATRIBE_CAMERASHAKEDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   CameraShakeData: public IData
{
public:
      int    shakeItemID_;                     //震动ID
	  int    halfCircleTime_;					//半周期时间
	  int    shakeItemType_;                   //震动类型
	  float  shakeX_;           //左右的振幅
      float  shakeY_;           //上下振幅
      int    containTime_;					   //震动持续时间
	 
public:
	CameraShakeData();
	~CameraShakeData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class CameraShakeDataManager : public IDataManager, public cobra_win::Singleton2<CameraShakeDataManager>
{
public:
	std::map<int, CameraShakeData*>  m_CameraShakeDataMap_;

public:
	CameraShakeDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~CameraShakeDataManager();

public:
	
    CameraShakeData * GetCamerShakeDataByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<CameraShakeDataManager>;

};
  
#endif