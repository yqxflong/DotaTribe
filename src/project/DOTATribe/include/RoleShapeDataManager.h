#ifndef  _DOTATRIBE_ROLESHAPEDATAMANAGER_H_
#define  _DOTATRIBE_ROLESHAPEDATAMANAGER_H_

#include "../../extensions/spine/spine-cocos2dx.h"
#include "../include/ActionSetDataManager.h"
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

using  namespace  cocos2d;
using namespace cocos2d::extension;

#pragma pack(push, 1)
class RoleShapeData : public IData
{
public:
	int   mShapeId;									// 角色骨骼ID
	int	  mShowScale;								// 当前骨骼展示时的缩放系数(使用时候/10)
	char  mShapeAnimationFile[128];					// 骨骼文件      JSON
	char  mShapeAnimationFileDaiJi[128];			// 骨骼文件 待机 JSON
	char  mShapeAnimationImage[128];				// 贴图文件      ATLAS

	char  mShapeAnimationEffectFileUp[128];			// 特效骨骼文件(人前)
	char  mShapeAnimationEffectImageUp[128];		// 特效贴图文件
	char  mShapeAnimationEffectFileDown[128];		// 特效骨骼文件(人后)
	char  mShapeAnimationEffectImageDown[128];		// 特效贴图文件
	 
	char  mShapeActionSetFileName[128];				// 动作表文件名称(含相对路径)
	char  mShapeActionSetTableName[128];			// 动作表打包后数据表名称  (作为动作配置表Key)

	int   mShapeCompositeEffectID;					// 骨骼持续特效ID

	ActionSetDataManager *  mActionSetDataManager;	//动作配置管理器

public:
	RoleShapeData();
	virtual ~RoleShapeData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class RoleShapeDataManager : public IDataManager, public cobra_win::Singleton2<RoleShapeDataManager>
{
public:
	std::map<int, RoleShapeData*>					m_ShapeList;  
	std::map<std::string,ActionSetDataManager *>    m_ActionSetDataManagerList;
public:
	RoleShapeDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~RoleShapeDataManager();
public:
	/*
		得到人物外形列表
	*/
	std::map<int, RoleShapeData*>& GetRoleShapeList();
	/*
		根据Id得到人物外形信息
	*/
	RoleShapeData* GetRoleShapeById(int shapeId);

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

	/*
		绑定动作管理器到角色外形	
	*/
	bool	BindActionSetManagerForRoleShape();


	void	RegisterActionSetDataManager(ActionSetDataManager * pActionSetDataManager);

private:
	friend   class   cobra_win::Singleton2<RoleShapeDataManager>;
};


#endif
