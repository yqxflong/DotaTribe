#include "../include/RoleShapeDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>
 
#define	 _MAX_ROLE_ACTION_TABLE_LEN_   128			//最大动作表名称长度

RoleShapeData::RoleShapeData()
{
	mShapeId = -1;
	mShowScale = 1;
	mActionSetDataManager=NULL;
	mShapeCompositeEffectID=-1;
	memset(mShapeAnimationFile, 0, sizeof(mShapeAnimationFile));
	memset(mShapeAnimationImage, 0, sizeof(mShapeAnimationImage));
	memset(mShapeAnimationEffectFileUp, 0, sizeof(mShapeAnimationEffectFileUp));
	memset(mShapeAnimationEffectImageUp, 0, sizeof(mShapeAnimationEffectImageUp));
	memset(mShapeAnimationEffectFileDown, 0, sizeof(mShapeAnimationEffectFileDown));
	memset(mShapeAnimationEffectImageDown, 0, sizeof(mShapeAnimationEffectImageDown));
	memset(mShapeAnimationFileDaiJi, 0, sizeof(mShapeAnimationFileDaiJi));
	memset(mShapeActionSetFileName, 0, sizeof(mShapeActionSetFileName));
	memset(mShapeActionSetTableName, 0, sizeof(mShapeActionSetTableName));
}

RoleShapeData::~RoleShapeData()
{

}

bool RoleShapeData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	int id = 0;
	if (!parser.parser_int_value(mShapeId))
		return false;

	if (!parser.parser_int_value(mShowScale))
		return false;

	if (!parser.parser_string_value(mShapeAnimationFile, sizeof(mShapeAnimationFile)))
		return false;

	if (!parser.parser_string_value(mShapeAnimationFileDaiJi, sizeof(mShapeAnimationFileDaiJi)))
		return false;
	
	if (!parser.parser_string_value(mShapeAnimationImage, sizeof(mShapeAnimationImage)))
		return false;

	if (!parser.parser_string_value(mShapeAnimationEffectFileUp, sizeof(mShapeAnimationEffectFileUp)))
		return false;

	if (!parser.parser_string_value(mShapeAnimationEffectImageUp, sizeof(mShapeAnimationEffectImageUp)))
		return false;

	if (!parser.parser_string_value(mShapeAnimationEffectFileDown, sizeof(mShapeAnimationEffectFileDown)))
		return false;

	if (!parser.parser_string_value(mShapeAnimationEffectImageDown, sizeof(mShapeAnimationEffectImageDown)))
		return false;
 
	if (!parser.parser_string_value(mShapeActionSetFileName, sizeof(mShapeActionSetFileName)))
		return false;

	if (!parser.parser_int_value(mShapeCompositeEffectID))
		return false; 

	std::string  fileName=mShapeActionSetFileName;
	size_t tableNameStartIndex=fileName.rfind("/");
	if(tableNameStartIndex<_MAX_ROLE_ACTION_TABLE_LEN_)
	{
		size_t tableNameEndIndex=fileName.rfind(".");
	    fileName=fileName.substr(tableNameStartIndex+1,(tableNameEndIndex-tableNameStartIndex-1));
	} 
	memcpy(mShapeActionSetTableName,fileName.c_str(),fileName.length());
	 
	return true;
}

template<> RoleShapeDataManager* cobra_win::Singleton2<RoleShapeDataManager>::m_pMySelf = NULL;

RoleShapeDataManager::RoleShapeDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_ShapeList.clear();
	m_ActionSetDataManagerList.clear();
}	

RoleShapeDataManager::~RoleShapeDataManager()
{

}

std::map<int, RoleShapeData*>& RoleShapeDataManager::GetRoleShapeList()
{
	return m_ShapeList;
}

RoleShapeData* RoleShapeDataManager::GetRoleShapeById(int shapeId)
{
	std::map<int, RoleShapeData*>::iterator iter = m_ShapeList.find(shapeId);
	if (iter == m_ShapeList.end())
		return NULL;

	return iter->second;
}

std::string RoleShapeDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/roleshape.txt";

	return "roleshape";
}

unsigned  int RoleShapeDataManager::GetSize()
{
	return m_ShapeList.size()*sizeof(RoleShapeData);
}

bool  RoleShapeDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
		{
			if (!LoadFromDB())
				break;
		}
		else
		{
			if (!LoadFromFile())
				break;
		}
		 
		if(!BindActionSetManagerForRoleShape())
	    break;
		 
		return true;
	} 
	while(false);

	return false;
}

void  RoleShapeDataManager::Tick()
{

}

void  RoleShapeDataManager::Destroy()
{
	std::map<int, RoleShapeData*>::iterator iter   = m_ShapeList.begin();
	std::map<int, RoleShapeData*>::iterator iter_e = m_ShapeList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	
	std::map<std::string,ActionSetDataManager *>::iterator action_iter   = m_ActionSetDataManagerList.begin();
	std::map<std::string,ActionSetDataManager *>::iterator action_iter_e = m_ActionSetDataManagerList.end();
	for ( ; action_iter!=action_iter_e; ++action_iter)
	{
		action_iter->second->Destroy();
		delete action_iter->second;
	} 
	m_ShapeList.clear();
	m_ActionSetDataManagerList.clear();
}

bool  RoleShapeDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	RoleShapeData* pShape = (RoleShapeData*)pData;
	assert(pShape != NULL);

	return true;
}

bool  RoleShapeDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  RoleShapeDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	RoleShapeData* pItemData = new RoleShapeData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	//注意防止出现相同ID 可能导致内存泄露
	m_ShapeList.insert(std::map<int, RoleShapeData*>::value_type(pItemData->mShapeId, pItemData));
  
	return true;
}



void	RoleShapeDataManager::RegisterActionSetDataManager(ActionSetDataManager * pActionSetDataManager)
{
	if(pActionSetDataManager)
	m_ActionSetDataManagerList.insert(std::map<std::string,ActionSetDataManager *>::value_type(pActionSetDataManager->GetTableName(),pActionSetDataManager));
}


bool  RoleShapeDataManager::BindActionSetManagerForRoleShape()
{
	std::map<int, RoleShapeData*>::iterator iter   = m_ShapeList.begin();
	std::map<int, RoleShapeData*>::iterator iter_e = m_ShapeList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		std::map<std::string, ActionSetDataManager*>::iterator tempiter = m_ActionSetDataManagerList.find(iter->second->mShapeActionSetTableName);
		if (tempiter == m_ActionSetDataManagerList.end())
		{
			ActionSetDataManager * pActionSetDataManager = new ActionSetDataManager(m_bLoadFromDB, m_bEncryption, iter->second->mShapeActionSetFileName, iter->second->mShapeActionSetTableName);
			iter->second->mActionSetDataManager = pActionSetDataManager;
			RegisterActionSetDataManager(pActionSetDataManager);
		}
		else
		{
			iter->second->mActionSetDataManager=tempiter->second;
		}
	}
	 
	//初始化动作配置表
	std::map<std::string, ActionSetDataManager*>::iterator iter_manager=m_ActionSetDataManagerList.begin();
	while(iter_manager!=m_ActionSetDataManagerList.end())
	{
		iter_manager->second->Init();
		iter_manager++;
	}
	return true;
}
