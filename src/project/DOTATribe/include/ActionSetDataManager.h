#ifndef  _DOTATRIBE_ACTIONSETDATAMANAGER_H_
#define  _DOTATRIBE_ACTIONSETDATAMANAGER_H_


#include "IDataManager.h"
#include <map>

//动作事件
enum
{
    _Skeleton_Action_UnKonw_Type_=-1,
	_Skeleton_Action_Effect1_Type_,
	_Skeleton_Action_Effect2_Type_,
	_Skeleton_Action_Effect3_Type_,
	_Skeleton_Action_Shake_Type_,
	_Skeletion_Action_Screen_Type_,
	_Skeletion_Action_Sound_Type_,
};

#pragma pack(push, 1)
class ActionSetData : public IData
{
public:
	int		mActionId;							//动作 ID
	char	mActionName[128];					//动作 名称
	int     mActionCompositeEffectID;			//动作 母特效ID
public:
	ActionSetData();
	virtual ~ActionSetData();
public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)

class ActionSetDataManager : public IDataManager
{
protected:
	std::string m_FileName;  // 对应的文件名称
	std::string m_TableName; // 对应的表格名称

protected:
	std::multimap<int, ActionSetData*> m_ActionList;// 动作列表

public:
	ActionSetDataManager(bool bLoadFromDB, bool bEncryption, std::string fileName, std::string tableName);
	virtual ~ActionSetDataManager();

public:
	/*
		得到动作列表名称
	*/
	std::string GetTableName();

public: 
	/*
	按照指定动作表ID，获取相应动作名称
	*/
	std::string GetActionNameByActionId(int actionId);

	/*
	 根据动作ID获得配置结构
	*/
	ActionSetData* GetActionSetDataByActionId(int actionId);

	/*
	  根据动作名称获得动作ID
	*/
	int GetActionIDFromActionName(std::string actionName);

	/*
	根据动作ID获得组合特效ID
	*/
	int  GetCompositeEffectByActionID(int actionID);

	/*
	 根据动作名称 获得配置结构
	*/
	ActionSetData* GetActionSetDataByActionName(std::string actionName);
public:
	/*
		得到对应的数据管理器名称
	*/
	virtual  std::string    GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int  GetSize();

public:
	/*
        初始化数据管理器
    */
	virtual   bool   Init();
	/*
        数据管理器桢更新
    */
	virtual   void   Tick();
	/*
        销毁数据管理器
    */
	virtual   void   Destroy();

protected:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual   bool   Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的关联性校验)
	*/
	virtual   bool   VarifyAfterLoadAll();
    
protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);
};


#endif
