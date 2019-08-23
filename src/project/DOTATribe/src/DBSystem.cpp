#include <cocos2d.h>
#include "../include/DBSystem.h"
#include "../include/VariableSystem.h"
#include "../include/EngineSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventDef.h"
#include "../include/EventTyper.h"
#include "../include/IDataManager.h"
#include "../include/LoggerSystem.h"
#include "../include/PreLoadResourceDataManager.h"
#include "../include/UIWindowDataManager.h"
#include "../include/CommonButtonDataManager.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleShapePropertyDataManager.h"
#include "../include/RoleBaseDataManager.h"
#include "../include/SkillTableDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/CreateRoleDataManager.h"
#include "../include/SkillActionDataManager.h"
#include "../include/CameraShakeDataManager.h"
#include "../include/ActionSetDataManager.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/NumberBufferDataManager.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/SoundDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/IDStringDataManager.h"
#include "../include/ScreenEffectDataManager.h"
#include "../include/RoleEffectDataManager.h"
#include "../include/FontStyleDataManager.h"
#include "../include/ArtFontDataManager.h"
#include "../include/ClientConstDataManager.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/GuideDataManager.h"
#include "../include/NpcTalkDataManager.h"
#include "../include/CompositeEffectDataManager.h"
#include "../include/FrameAnimateDataManager.h"
#include "../include/ParticleDataManager.h"
#include "../include/ErrorTipsDataManager.h"
#include "../include/AnnouncementDataManager.h"
#include "../include/IAPProductDataManager.h"
#include "../include/VipFontDataManager.h"
#include "../include/ActivityDataManager.h"
#include "../include/LocalNotificationDataManager.h"
#include "../include/ChatPushDataManager.h"
#include "../include/LocalAthleticsDataManager.h"
#include <map>


template<> DBSystem* cobra_win::Singleton2<DBSystem>::m_pMySelf = NULL;

DBSystem::DBSystem()
{
	m_pSQLite = NULL;
	m_pUISQLite = NULL;

	m_DataManagerList.clear(); 
}

DBSystem::~DBSystem()
{

}

void DBSystem::RegisterDataManager(IDataManager* pDataManager)
{
	assert(pDataManager != NULL);

	m_DataManagerList.push_back(pDataManager);
}

 

int DBSystem::GetDBSize()
{
	unsigned int iDBSystemSize = 0;
	std::list<IDataManager*>::iterator iter   = m_DataManagerList.begin();
	std::list<IDataManager*>::iterator iter_e = m_DataManagerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		iDBSystemSize += (*iter)->GetSize();
	}
  
	return iDBSystemSize;
}

sqlite3* DBSystem::GetSQLite()
{
	return m_pSQLite;
}

sqlite3* DBSystem::GetUISQLite()
{
	return m_pUISQLite;
}

bool DBSystem::IsNeedVerify()
{
	bool bNeedVerify = true;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "IsDataNeedVerify", bNeedVerify);

	return bNeedVerify;
}

std::string DBSystem::GetEncryptionKey()
{
	char buffer[1024] = "com.cyou.mrd.dota97tribe9527";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataEncryptionKey", buffer, sizeof(buffer));

	return buffer;
}

std::string DBSystem::GetLocalDataEncryptionKey()
{
	char buffer[1024] = "&^#*(#*(-%$!^*(-&^%@##$-cyou-inc";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "LocalDataEncryptionKey", buffer, sizeof(buffer));

	return buffer;
}
 

bool DBSystem::Init()
{
	bool bFromDB = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataLoadFromDB", bFromDB);
	bool bResourceEncryption = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataEncryptioned", bResourceEncryption);
	bool bVarify = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataVarifyAfterLoadAll", bVarify);

	// 打开SQLite数据库
	if (bFromDB)
	{
		if (!LoadDBFile())
			return false;
	}

	// 注册数据管理器
	RegisterDataManager(new SysLangDataManager(bFromDB,bResourceEncryption));
	RegisterDataManager(new IDStringDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new UIWindowDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new CommonButtonDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new PreLoadResourceDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new AnimationFileDataManager(bFromDB, bResourceEncryption));
	 
	RegisterDataManager(new SkillTableDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new SkillActionDataManager(bFromDB, bResourceEncryption));
	 
	RegisterDataManager(new CameraShakeDataManager(bFromDB, bResourceEncryption)); 
	RegisterDataManager(new CreateRoleDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new RoleShapeDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new NumberBufferDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new SceneInfoDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new CompositeEffectDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new FrameAnimateDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new ErrorTipsDataManager(bFromDB, bResourceEncryption));
	RegisterDataManager(new IAPProductDataManager(bFromDB, bResourceEncryption));
	   
	//本地音效数据
	RegisterDataManager(new SoundDataManager(bFromDB, bResourceEncryption));

	//屏幕特效数据
    RegisterDataManager(new ScreenEffectDataManager(bFromDB, bResourceEncryption));

	//角色特效数据
	RegisterDataManager(new RoleEffectDataManager(bFromDB, bResourceEncryption));

	//粒子特效数据
	RegisterDataManager(new ParticleDataManager(bFromDB, bResourceEncryption));

	//Loading界面
	RegisterDataManager(new LoadingAnimationManager(bFromDB, bResourceEncryption));

	//活动
	RegisterDataManager(new ActivityManager(bFromDB, bResourceEncryption));
 
	// 第二部注册所有的玩家数据，只有静态数据全部初始化完之后，在初始化玩家数据
	// 因为这里面会存在先后的顺序
	RegisterDataManager(new LocalPlayerDataManager(bFromDB, bResourceEncryption));
	
	//注册UILayoutManager
	RegisterDataManager(new UIViewDataManager(bFromDB,bResourceEncryption));

	//注册ResouceID对应表
	RegisterDataManager(new ResourceIDDataManager(bFromDB,bResourceEncryption));

	//注册FontStyle对应表
	RegisterDataManager(new FontStyleDataManager(bFromDB,bResourceEncryption));
 
	//注册ArtFontData数据表
	RegisterDataManager(new ArtFontDataManager(bFromDB,bResourceEncryption));

	//注册客户端常数表
	RegisterDataManager(new ClientConstDataManager(bFromDB,bResourceEncryption));

	//新手引导
	RegisterDataManager(new GuideDataManager(bFromDB,bResourceEncryption));

	//NPC对话数据
	RegisterDataManager(new NpcTalkDataManager(bFromDB,bResourceEncryption));

	//公告样式表
	RegisterDataManager(new AnnouncementDataManager(bFromDB,bResourceEncryption));
	  
	//Vip字体表
	RegisterDataManager(new VipFontManager(bFromDB,bResourceEncryption));

	//本地通知表
	RegisterDataManager(new LocalNotificationDataManager(bFromDB,bResourceEncryption));

	//本地战斗缓存数据
	RegisterDataManager(new LocalAthleticsDataManager(bFromDB,bResourceEncryption));
	 
	RegisterDataManager(new ChatPushDataManager(bFromDB,bResourceEncryption));

	// 初始化所有的数据管理器
	unsigned int iDBSystemSize = 0;
	std::list<IDataManager*>::iterator iter   = m_DataManagerList.begin();
	std::list<IDataManager*>::iterator iter_e = m_DataManagerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		LOGGERSYSTEM->LogInfo("Start Load Table=%s\n", (*iter)->GetName().c_str());

		if (!(*iter)->Init())
		{
			LOGGERSYSTEM->LogFatal("Init DBSystem Failed, DBTable=%s\n", (*iter)->GetName().c_str());
			return false;
		}

		iDBSystemSize += (*iter)->GetSize();
	}
	   

	// 释放UI布局SQLite数据
	if (m_pUISQLite != NULL)
	{
		sqlite3_close(m_pUISQLite);
		m_pUISQLite = NULL;
	}

	// 释放SQLite数据
	if (m_pSQLite != NULL)
	{
		sqlite3_close(m_pSQLite);
		m_pSQLite = NULL;
	}

	// 所有数据表关联性校验
	if (IsNeedVerify())
	{
		iter   = m_DataManagerList.begin();
		iter_e = m_DataManagerList.end();
		for ( ; bVarify && iter!=iter_e; ++iter)
		{
			if (!(*iter)->VarifyAfterLoadAll())
			{
				LOGGERSYSTEM->LogFatal("Varify DBSystem Failed, DBTable=%s\n", (*iter)->GetName().c_str());
				return false;
			}
		}
	}

	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_VERSIONUPDATE_FINISHED_, DBSystem::OnVersionUpdateFinishedEventHandler, "");
	LOGGERSYSTEM->LogInfo("Init DBSystem Success, DBSystemSize=%u\n", iDBSystemSize);

	return true;
}


void  DBSystem::LoadSkeletonTriggerConfig(int shapeID,int actionConfigID,std::vector<cocos2d::extension::PSkeletonCallBack_Node> * pcallBackVec)
{
	RoleShapeData * pRoleShapeData=RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	if(pRoleShapeData!=NULL)
	{
		ActionSetDataManager *  pActionSetDataManager=pRoleShapeData->mActionSetDataManager;
		if(pActionSetDataManager!=NULL)
		{ 
			ActionSetData *  pActionSetData=pActionSetDataManager->GetActionSetDataByActionId(actionConfigID);
			if(pActionSetData!=NULL)
			{ 
				int  compositeEffectID=pActionSetData->mActionCompositeEffectID;
				if(compositeEffectID!=-1)
				{  
					CompositeEffectData *pCompositeEffectData=CompositeEffectDataManager::get_instance2()->GetCompositeEffectDataByID(compositeEffectID);
					if(pCompositeEffectData!=NULL)
					{
						if(pCompositeEffectData->soundEffectID!=-1)
						{
							LoadSingleSkeletonConfig(pcallBackVec,compositeEffectID,_CompositeEffect_SoundEffect_Type_,
								pCompositeEffectData->soundEffectID,pCompositeEffectData->soundEfefctTriggerTime);
						}
						FOR_EACH_CALL_BEGIN(pCompositeEffectData->compositeEffectVec.size())
							LoadSingleSkeletonConfig(pcallBackVec,compositeEffectID,pCompositeEffectData->compositeEffectVec.at(index).effectType,
							pCompositeEffectData->compositeEffectVec.at(index).effectID,pCompositeEffectData->compositeEffectVec.at(index).effectTriggerTime);
						FOR_EACH_CALL_END
					}
				}
			}
			return ;
		}
	}

}


void   DBSystem::LoadSingleSkeletonConfig(std::vector<cocos2d::extension::PSkeletonCallBack_Node> * pcallBackVec,int & compositeEffectID,int  effectType,int & effectID,float & effectTriggerTime)
{
	FOR_EACH_CALL_BEGIN(pcallBackVec->size())
		if(!pcallBackVec->at(index)->isValid)
		{ 
			pcallBackVec->at(index)->isValid=true;
			pcallBackVec->at(index)->eventType=effectType;
			pcallBackVec->at(index)->triggerTime=effectTriggerTime;
			pcallBackVec->at(index)->pAttachParam->effectID=effectID;
			pcallBackVec->at(index)->pAttachParam->compositeEffectID=compositeEffectID;

			switch(effectType)
			{
			case  _CompositeEffect_FrameAniamteEffect_Type_:
				{
					//帧特效
					FrameAnimateData *pFrameAnimate=FrameAnimateDataManager::get_instance2()->GetFrameAnimateDataByID(effectID);
					if(pFrameAnimate!=NULL)
					{
						if(pFrameAnimate->frameAnimateIsBoneBindEffect)
						{
							pcallBackVec->at(index)->pAttachParam->boneName=pFrameAnimate->frameAnimateEffectBoneName;
							pcallBackVec->at(index)->pAttachParam->isBoneBindEffect=true;
							pcallBackVec->at(index)->pAttachParam->isDurationBoneEffect=pFrameAnimate->frameAnimateEffectPlayType==1 ? true:false;
							pcallBackVec->at(index)->pAttachParam->isFollowBoneEffect=(pFrameAnimate->frameAnimateIsLocationFollow==1? true:false)||
								(pFrameAnimate->frameAnimateIsAngleFollow==1? true:false);
						}
					}
					return;
				}
			case _CompositeEffect_ParticleEffect_Type_:
				{
					//粒子特效
					ParticleData * pParticleData=ParticleDataManager::get_instance2()->GetParticleDataByID(effectID);
					if(pParticleData!=NULL)
					{
						if(pParticleData->particleEffectIsBindBone)
						{
							pcallBackVec->at(index)->pAttachParam->boneName=pParticleData->particleEffectBoneName;
							pcallBackVec->at(index)->pAttachParam->isBoneBindEffect=true;
							pcallBackVec->at(index)->pAttachParam->isDurationBoneEffect=pParticleData->particleEffectPlayType==1 ? true:false;
							pcallBackVec->at(index)->pAttachParam->isFollowBoneEffect=(pParticleData->particleEffectIsLocationFollow==1? true:false)||
								(pParticleData->particleEffectIsAngleFollow==1? true:false);
						} 
					} 
					return;
				}
			case _CompositeEffect_SkeletonEffect_Type_:
				{
					//骨骼特效
					return;
				}
			default:
				break;
			}
			return ;
		}
	 FOR_EACH_CALL_END
}



void DBSystem::Tick()
{
	std::list<IDataManager*>::iterator iter   = m_DataManagerList.begin();
	std::list<IDataManager*>::iterator iter_e = m_DataManagerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		(*iter)->Tick();
	}
}

void DBSystem::Destroy()
{
	std::list<IDataManager*>::iterator iter   = m_DataManagerList.begin();
	std::list<IDataManager*>::iterator iter_e = m_DataManagerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		(*iter)->Destroy();
		delete (*iter);
	}
	m_DataManagerList.clear();
 

	LOGGERSYSTEM->LogInfo("Destroy DBSystem Success\n");
}

char* DBSystem::XORBuffer(char* pKey, char* pBuffer, unsigned int iBufferLen)
{
	assert(pKey != NULL);
	assert(strlen(pKey) > 0);
	assert(pBuffer != NULL);
	assert(iBufferLen > 0);

	// 开始XOR加密解密
	int keyLen = strlen(pKey);
	for (unsigned int i=0; i<iBufferLen; i++)
	{
		char temp = pBuffer[i];
		pBuffer[i] = (char)(temp^pKey[i%keyLen]);
	}

	return pBuffer;
}

bool DBSystem::LoadDBTable(char* pTableName, char*& pBuffer, unsigned int& iLength)
{
	assert(pTableName != NULL);
	assert(strlen(pTableName) > 0);

	sqlite3_stmt* pSTMT  = NULL;
	char*         pError = NULL;

	do 
	{
		char sql[1024] = "";
		sprintf(sql, "select * from %s", pTableName);
		int ret = sqlite3_prepare(DBSYSTEM->GetSQLite(), sql, strlen(sql), &pSTMT, (const char **)&pError);
		if (ret != SQLITE_OK)
			break;

		ret = sqlite3_step(pSTMT);
		if (ret != SQLITE_ROW)
			break;

		char* pText = (char*)sqlite3_column_blob(pSTMT, 0);
		iLength = sqlite3_column_bytes(pSTMT, 0);

		pBuffer = new char[iLength+1];
		memset(pBuffer, 0, iLength+1);
		memcpy(pBuffer, pText, iLength);

		sqlite3_finalize(pSTMT);
		return true;
	}
	while (false);

	if (pSTMT != NULL)
	{
		sqlite3_finalize(pSTMT);
		pSTMT = NULL;
	}
	return false;
}

bool DBSystem::LoadUIDBTable(char* pTableName, char*& pBuffer, unsigned int& iLength)
{
	assert(pTableName != NULL);
	assert(strlen(pTableName) > 0);

	sqlite3_stmt* pSTMT  = NULL;
	char*         pError = NULL;

	do 
	{
		char sql[1024] = "";
		sprintf(sql, "select * from %s", pTableName);
		int ret = sqlite3_prepare(DBSYSTEM->GetUISQLite(), sql, strlen(sql), &pSTMT, (const char **)&pError);
		if (ret != SQLITE_OK)
			break;

		ret = sqlite3_step(pSTMT);
		if (ret != SQLITE_ROW)
			break;

		char* pText = (char*)sqlite3_column_blob(pSTMT, 0);
		iLength = sqlite3_column_bytes(pSTMT, 0);

		pBuffer = new char[iLength+1];
		memset(pBuffer, 0, iLength+1);
		memcpy(pBuffer, pText, iLength);

		sqlite3_finalize(pSTMT);
		return true;
	}
	while (false);

	if (pSTMT != NULL)
	{
		sqlite3_finalize(pSTMT);
		pSTMT = NULL;
	}
	return false;
}

void  DBSystem::OnVersionUpdateFinishedEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList)
{
	if (paramList.size() <= 0)
		return ;

	int bUpdated = 0;
	sscanf(paramList.front().c_str(), "%d", &bUpdated);
	if (bUpdated == 0)
		return;

	do 
	{
		// 更新了，重新加载所有的静态数据
		bool bFromDB = false;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataLoadFromDB", bFromDB);
		bool bResourceEncryption = false;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataEncryptioned", bResourceEncryption);
		bool bVarify = false;
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "DataVarifyAfterLoadAll", bVarify);

		// 打开SQLite数据库
		if (bFromDB)
		{
			if (!DBSYSTEM->LoadDBFile())
				break;
		}

		// 初始化所有的数据管理器
		unsigned int iDBSystemSize = 0;
		std::list<IDataManager*>::iterator iter   = DBSYSTEM->m_DataManagerList.begin();
		std::list<IDataManager*>::iterator iter_e = DBSYSTEM->m_DataManagerList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			LOGGERSYSTEM->LogInfo("Start ReLoad Table=%s\n", (*iter)->GetName().c_str());

			if (!(*iter)->Reload())
			{
				LOGGERSYSTEM->LogFatal("Reload DBSystem Failed, DBTable=%s\n", (*iter)->GetName().c_str());
				return;
			}

			iDBSystemSize += (*iter)->GetSize();
		}

		// 释放UI布局SQLite数据
		if (DBSYSTEM->m_pUISQLite != NULL)
		{
			sqlite3_close(DBSYSTEM->m_pUISQLite);
			DBSYSTEM->m_pUISQLite = NULL;
		}

		// 释放SQLite数据
		if (DBSYSTEM->m_pSQLite != NULL)
		{
			sqlite3_close(DBSYSTEM->m_pSQLite);
			DBSYSTEM->m_pSQLite = NULL;
		}

		// 所有数据表关联性校验
		if (DBSYSTEM->IsNeedVerify())
		{
			iter   = DBSYSTEM->m_DataManagerList.begin();
			iter_e = DBSYSTEM->m_DataManagerList.end();
			for ( ; bVarify && iter!=iter_e; ++iter)
			{
				if (!(*iter)->VarifyAfterLoadAll())
				{
					LOGGERSYSTEM->LogFatal("Varify DBSystem Failed, DBTable=%s\n", (*iter)->GetName().c_str());
					return;
				}
			}
		}

		LOGGERSYSTEM->LogInfo("Reload DBSystem Success, DBSystemSize=%u\n", iDBSystemSize);
		return;
	} 
	while (false);

	LOGGERSYSTEM->LogInfo("Reload DBSystem Failed\n");
}
