//Name : 分类ID维护表
//Function : ID与string的对应
//Author : 方骏
//Data : 2013-7-29


#ifndef   _DOTATRIBE_IDSTRINGDATAMANAGER_H
#define   _DOTATRIBE_IDSTRINGDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <vector>

#pragma pack(push, 1)

class   IDStringData: public IData
{
public:
	int mTag;
	int mSubTag;
	std::string mString;
public:
	IDStringData();
	~IDStringData(){};

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class IDStringDataManager: public IDataManager, public cobra_win::Singleton2<IDStringDataManager>
{
public:
	std::map<int, std::vector<std::string> > m_IDStringDataList;

public:
	IDStringDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~IDStringDataManager();

public:
	
	std::string GetIDStringByID(int tag, int subTag);

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
	friend   class   cobra_win::Singleton2<IDStringDataManager>;

};

#define IDSTRINGDATAMANAGER (IDStringDataManager::get_instance2())

#endif