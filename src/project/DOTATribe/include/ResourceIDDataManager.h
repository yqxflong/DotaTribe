//Name：ResourceIDDataManager
//Written By：尹强

#ifndef   _DOTATRIBE_RESOURCEIDDATAMANAGER_H
#define   _DOTATRIBE_RESOURCEIDDATAMANAGER_H

#include <cocos2d.h>
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class   ResourceIDData: public IData
{
public:
	enum
	{
		_RESOURCETYPE_UNKOWN_TYPE_=-1,
		_RESOURCETYPE_PLIST_TYPE_,
		_RESOURCETYPE_IMAGE_TYPE_,
	};
public:
	int  IconID_;
	short  resourceType;
	char textureName[128];
	char filepath_[128];
public:
	ResourceIDData();
	virtual ~ResourceIDData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class ResourceIDDataManager : public IDataManager, public cobra_win::Singleton2<ResourceIDDataManager>
{
public:
	std::map<int,ResourceIDData *>  m_resouceDataMap;
public:
	ResourceIDDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){
		m_resouceDataMap.clear();
	};

	virtual ~ResourceIDDataManager(){};

public:
	
	std::string getDataByID(int idx);

	ResourceIDData  * GetResourceDataByID(int idx);
	 
	/*
	 *	根据索引获得精灵 目前仅仅支持 打包图片
	 */
	cocos2d::CCSprite *  GetSpriteFromID(int idx);
 
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
	//
	//
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
	friend   class   cobra_win::Singleton2<ResourceIDDataManager>;
};

#define  RESOURCEDAIDMANAGER  ResourceIDDataManager::get_instance2()
  
#endif