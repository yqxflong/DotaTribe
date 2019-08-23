//Name：ClientConstDataManager
//Written By：尹强

#ifndef   _DOTATRIBE_ClientConstDataManager_H
#define   _DOTATRIBE_ClientConstDataManager_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class   ClientConstData: public IData
{
public:
	char key_[128];
	int value_;
public:
	ClientConstData();
	virtual ~ClientConstData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)
 


class ClientConstDataManager : public IDataManager, public cobra_win::Singleton2<ClientConstDataManager>
{
private:
	std::map<std::string,int> m_mapList;
public:
	ClientConstDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){};
	virtual ~ClientConstDataManager(){};

public:
	int getValueByKey(const char* key);
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

};

#define  CLIENTCONSTDATAMANGER  ClientConstDataManager::get_instance2()
  
#endif