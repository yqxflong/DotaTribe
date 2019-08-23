#ifndef  _DOTATRIBE_SYSLANGDATAMANAGER_H_
#define  _DOTATRIBE_SYSLANGDATAMANAGER_H_


#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <map>

#pragma pack(push, 1)
class SysLangItemData : public IData
{
public:
	int         mLangId;  // 语言Id
	std::string mLangText;//语言文字

public:
	SysLangItemData();
	virtual ~SysLangItemData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class SysLangDataManager : public IDataManager, public cobra_win::Singleton2<SysLangDataManager>
{
public:
	enum
	{
		_TYPED_SYSLANG_CN_, // 简体中文
		_TYPED_SYSLANG_EN_, // 英文
		_TYPED_SYSLANG_TW_, // 繁体中文
	};

protected:
	std::map<int, SysLangItemData*> m_SysLangList;
public:
	SysLangDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SysLangDataManager(){};

public:
	/*
		获得版本语言类型
	*/
	int GetCurLangType() const;

	/*
		得到指定Id的文字
	*/
	std::string GetSysLangById(int langId);

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
	friend   class   cobra_win::Singleton2<SysLangDataManager>;
};


#endif
