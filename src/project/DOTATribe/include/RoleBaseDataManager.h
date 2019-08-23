#ifndef   _DOTATRIBE_ROLEBASEDATAMANAGER_H
#define   _DOTATRIBE_ROLEBASEDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   RoleBaseData: public IData
{
public:
	  int  roleUniqueID_;                    //角色ID
	  int  roleShapeID_;                     //外形ID
	  char roleHeadIcon_[128];				 //头像
	  int  roleInitLevel_;                   //初始等级
      int  roleTypeId_;                      //类型
	  int  roleWeaponID_;                    //武器             
	  int  roleInitHP_;                      //血量
	  int  roleAttackValue_;                 //攻击力
	  int  roleSpeedValue_;                  //速度
	  int  roleSkillTacticsID_;              //技能策略
      int  roleForceValue_;                  //力量之
	  int  roleAgilityValue_;                //敏捷值
	  int  roleIntelligenceValue_;           //智力值
      int  roleArmorValue_;                  //护甲值 
	  int  roleSunderValue_;                 //破甲值     
	  int  roleCritValue_;                   //暴击值
	  int  roleToughnessValue_;              //韧性值          
	  int  roleHitValue_;                    //命中值
	  int  roleDodgeValue_;                  //闪避值
public:
	RoleBaseData();
	~RoleBaseData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);

};

#pragma pack(pop)
 


class RoleBaseDataManager : public IDataManager, public cobra_win::Singleton2<RoleBaseDataManager>
{
public:
	std::map<int, RoleBaseData*> m_RoleBaseDataMapList;

public:
	RoleBaseDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~RoleBaseDataManager();

public:
	
    RoleBaseData * GetRoleBaseDataByID(int roleUniqueId);

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
	friend   class   cobra_win::Singleton2<RoleBaseDataManager>;

};
  
#endif