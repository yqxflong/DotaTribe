#ifndef  _DOTATRIBE_IDATAMANAGER_H_
#define  _DOTATRIBE_IDATAMANAGER_H_


#include <string>


// 富文本内容解析
extern  std::string  _rich_text_parser_(std::string text);


class IData
{
public:
	IData();
	virtual ~IData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen)  =  0;
};

class IDataManager
{
protected:
	bool  m_bLoadFromDB;
	bool  m_bEncryption;

public:
	IDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~IDataManager();

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
	/*
		重新加载数据管理器
	*/
	virtual  bool  Reload();

protected:
	/*
		从文件加载对应的资源
	*/
	virtual  bool  LoadFromFile();
	/*
		从数据库加载对应的资源
	*/
	virtual  bool  LoadFromDB();

public:
	/*
		得到对应的数据管理器名称
	*/
	virtual  std::string   GetName()    =    0;
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int GetSize()    =    0;

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual  bool  Varify(IData* pData)   =   0;
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/
	virtual  bool  VarifyAfterLoadAll()   =   0;

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen)  =  0;
};


#endif
