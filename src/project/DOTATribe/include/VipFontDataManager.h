//Name：VipFontManager
//Func:		读取Vip界面特权信息
//Written By：lvyunlong
//Date:20131126
#ifndef   _DOTATRIBE_VIPFONTMANAGER_H
#define   _DOTATRIBE_VIPFONTMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <vector>

#pragma pack(push, 1)
class   VipFontData: public IData
{
public:
	int viptype_;
	int id_;
	int syslangid_;
	int fsyleid_;
public:
	VipFontData();
	virtual ~VipFontData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)
 


class VipFontManager : public IDataManager, public cobra_win::Singleton2<VipFontManager>
{
public:
	std::map<int,std::vector<VipFontData*> > m_mapList;
public:
	VipFontManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){};
	virtual ~VipFontManager(){};

public:
	
	std::vector<VipFontData*> getDataByID(size_t idx);

	VipFontData* getVipFontData(size_t idx,size_t subIdx);

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
	friend   class   cobra_win::Singleton2<VipFontManager>;
};

#define  VIPFONTMANAGER  VipFontManager::get_instance2()
  
#endif