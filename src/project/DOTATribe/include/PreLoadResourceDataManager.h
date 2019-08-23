#ifndef  _DOTATRIBE_PRELOADRESOURCEDATAMANAGER_H_
#define  _DOTATRIBE_PRELOADRESOURCEDATAMANAGER_H_


#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <vector>

#pragma pack(push, 1)
class PreLoadResourceItemData : public IData
{
public:
	int  mType;          // 资源类型：0标示plist，1标示图片
	char mFileName[128]; // 资源名称

public:
	PreLoadResourceItemData();
	virtual ~PreLoadResourceItemData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class PreLoadResourceDataManager : public IDataManager, public cobra_win::Singleton2<PreLoadResourceDataManager>
{
public:
	enum
	{
		_TYPED_RESOURCE_PLIST_,
		_TYPED_RESOURCE_IMAGE_,
	};

private:
	std::vector<PreLoadResourceItemData*> m_ResourceList;

public:
	PreLoadResourceDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~PreLoadResourceDataManager();

public:
	/*
		得到加载资源个数
	*/
	unsigned int GetPreLoadResourceNumber();
	/*
		得到对应位置的资源信息
	*/
	PreLoadResourceItemData* GetItemDataByPos(unsigned int pos);

public:
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
	friend   class   cobra_win::Singleton2<PreLoadResourceDataManager>;
};


#endif
