﻿#ifndef   _DOTATRIBE_SCREENEFFECTDATAMANAGER_H_
#define   _DOTATRIBE_SCREENEFFECTDATAMANAGER_H_
 
#include <include/common/Singleton.h>
#include <cocos2d.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   ScreenEffectData: public IData
{
public:
	  int   screenEffectID;
	  int   screenEffectZOrder;
	  char  screenEffectColorStr[16];
	  float screenEffectFadeInTime;  
	  float screenEffectDurationTime;
	  float screenEffectFadeOutTime;
public:
	ScreenEffectData();
	~ScreenEffectData();

   	cocos2d::ccColor4B  GetScreenEffectColor();
	 
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 
 
class ScreenEffectDataManager : public IDataManager, public cobra_win::Singleton2<ScreenEffectDataManager>
{
public:
	std::map<int, ScreenEffectData*>  m_screenEffectMapList;

public:
	ScreenEffectDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~ScreenEffectDataManager();

public:
	
    ScreenEffectData * GetScreenEffectByID(int screenEffectID);

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
	friend   class   cobra_win::Singleton2<ScreenEffectDataManager>;

};
   

#endif