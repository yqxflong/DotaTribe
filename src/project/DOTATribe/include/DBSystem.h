#ifndef  _DOTATRIBE_DBSYSTEM_H_
#define  _DOTATRIBE_DBSYSTEM_H_

#include <spine/SpineCallBackEvent.h> 
#include <include/common/Singleton.h>
#include <include/sqlite3.h>
#include <string>
#include <list>
#include <map>
using  namespace  cobra_win;

class IDataManager;
class ActionSetDataManager;
class DBSystem : public cobra_win::Singleton2<DBSystem>
{
private:
	sqlite3* m_pSQLite;    // 本地静态数据存储器
	sqlite3* m_pUISQLite;  // 本地UI布局数据存储器

private:
	std::list<IDataManager*> m_DataManagerList; 

public:
	DBSystem();
	virtual ~DBSystem();

public:
	/*
		得到DB总体内存占用大小
	*/
	int         GetDBSize();
	/*
		得到SQLite数据库对象
	*/
	sqlite3*    GetSQLite();
	/*
		得到本地UI布局数据存储器
	*/
	sqlite3*    GetUISQLite();
	/*
		是否需要数据校验
	*/
	bool        IsNeedVerify();
	/*
		得到数据文件加密的KEY
	*/
	std::string GetEncryptionKey();
	/*
		得到玩家本地存档文件加密KEY
	*/
	std::string GetLocalDataEncryptionKey();
 

	/*
	   加载动作回调配置
	*/
    void  LoadSkeletonTriggerConfig(int shapeID,int actionConfigID,std::vector<cocos2d::extension::PSkeletonCallBack_Node> * pcallBackVec);

public:
	/*
		初始化数据管理系统
	*/
	bool   Init();
	/*
		数据管理系统帧更新
	*/
	void   Tick();
	/*
		销毁数据管理系统
	*/
	void   Destroy();

private:
	/*
		注册数据管理器
	*/
	void   RegisterDataManager(IDataManager* pDataManager);
 
	/*
		加载指定的SQLite文件
	*/
	bool   LoadDBFile();

	/*
	 加载指令动作配置
	*/
	void   LoadSingleSkeletonConfig(std::vector<cocos2d::extension::PSkeletonCallBack_Node> * pcallBackVec,int & compositeEffectID,int  effectType,int & effectID,float & effectTriggerTime);

public:
	/*
		加密解密操作
	*/
	static  char*  XORBuffer(char* pKey, char* pBuffer, unsigned int iBufferLen);
	/*
		加载指定的数据库表
	*/
	static  bool   LoadDBTable(char* pTableName, char*& pBuffer, unsigned int& iLength);
	/*
		加载指定的UI布局数据库表
	*/
	static  bool   LoadUIDBTable(char* pTableName, char*& pBuffer, unsigned int& iLength);

public:
	/*
		版本更新事件响应处理函数（需要重新加载必要的资源）
	*/
	static  void   OnVersionUpdateFinishedEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList);

public:
	friend  class  cobra_win::Singleton2<DBSystem>;
};

#define   DBSYSTEM   (DBSystem::get_instance2())


#endif
