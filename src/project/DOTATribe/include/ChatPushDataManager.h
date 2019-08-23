//Name：ChatPushDataManager
//Written By：邵兵

#ifndef   _DOTATRIBE_CHATPUSHDATAMANAGER_H
#define   _DOTATRIBE_CHATPUSHDATAMANAGER_H

#include <cocos2d.h>
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <vector>

class   ChatPushData: public IData
{
public:
	int		m_id;	
	int		m_interval;	
	bool	m_isLoginPush;
	int		m_messageNum;
	std::vector<int>	m_messageId;
public:
	ChatPushData();
	virtual ~ChatPushData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
 

class ChatPushDataManager : public IDataManager, public cobra_win::Singleton2<ChatPushDataManager>
{
public:
	std::map<int,ChatPushData *>  m_chatPushDataMap;
public:
	ChatPushDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){
		m_chatPushDataMap.clear();
	};

	virtual ~ChatPushDataManager(){};

public:
	/*
		通过ID得到数据
	*/	
	ChatPushData* getDataByID(int idx);
	/*
		得到数据的个数
	*/
	int GetDataLength();
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
	friend   class   cobra_win::Singleton2<ChatPushDataManager>;
};

#define  CHATPUSHDATAMANAGER  ChatPushDataManager::get_instance2()
  
#endif