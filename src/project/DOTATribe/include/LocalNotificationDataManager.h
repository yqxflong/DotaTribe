#ifndef  _DOTATRIBE_LOCALNOTIFICATIONDATAMANAGER_H_
#define  _DOTATRIBE_LOCALNOTIFICATIONDATAMANAGER_H_


#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <list>

#pragma pack(push, 1)
class LocalNotificationItemData : public IData
{
public:
	int  mNotifyType;           // 提示类型
	int  mNotifyIntervalDay;    // 间隔天数
	int  mNotifyIntervalHour;   // 间隔小时
	int  mNotifyIntervalMinite; // 间隔分钟
	std::string mHint;    // 提示文字

public:
	LocalNotificationItemData();
	virtual ~LocalNotificationItemData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class LocalNotificationDataManager : public IDataManager, public cobra_win::Singleton2<LocalNotificationDataManager>
{
private:
	std::list<LocalNotificationItemData*> m_LocalNotifyList;

public:
	LocalNotificationDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~LocalNotificationDataManager();

public:
	/*
        得到本地通知的个数
    */
	unsigned int GetLocalNotifyNumber();
	/*
		根据索引得到本地通知信息
	*/
	LocalNotificationItemData* GetLocalNotifyByPos(unsigned int pos);

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
	friend   class   cobra_win::Singleton2<LocalNotificationDataManager>;
};


#endif
