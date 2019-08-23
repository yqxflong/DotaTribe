//Name：AthleticProcedureDataHandler
//Function：战斗过程指令管理器
//Author:	Johny

#include   <cocos2d.h>
#include   "../include/AthleticProcedureDataHandler.h"
#include   "../include/SCAthleticsDataPacket.h"
#include   "../include/AthleticProcedureDataType.h"
#include   "../include/CPublicVarReader.h"
#include   "../include/Common.h"
#include   "../include/TimeSystem.h"
#include   "../include/LoggerSystem.h"

 

template<> AthleticProcedureDataHandler* cobra_win::Singleton2<AthleticProcedureDataHandler>::m_pMySelf = NULL;

AthleticProcedureDataHandler::AthleticProcedureDataHandler()
{
   
}

AthleticProcedureDataHandler::~AthleticProcedureDataHandler()
{
	DestroyMemData();
}

bool AthleticProcedureDataHandler::init()
{
	isUsingLocalDataReplace = false;
	isDuriningLocal = false;
	pAthleticsMapInfo=NULL;
	pPreAthleticsData=NULL;
	pAthleticProData=NULL;
	pAthleticResultData=NULL;
	pAthleticBaseReward=NULL;
	isReTryBattle=false;
	athleticsSerialID=0;
	athleticsBattleType=0; 
	athleticsPlayerSkillsPool.clear();
	athleticsMonsterSkillsPool.clear();
	athleticsPlayerShapePool.clear();
	athleticsCompositeEffectPool.clear();
	athleticsPlayerActionPool.clear();
	athleticsMonsterActionPool.clear(); 
	athleticsShapeActionsPool.clear();
	athleticsEffectPlistPool.clear();
	athleticsEffectPlistPool.clear();
	athleticsShapeSkillsPool.clear();
	athleticsSceneID=0;
	return true;
}


void  AthleticProcedureDataHandler::onDestroy()
{
    //在此做的操作时清除加载的Plist
	 
	athleticsSerialID=0;
	athleticsPlayerSkillsPool.clear();
	athleticsMonsterSkillsPool.clear();
	athleticsPlayerShapePool.clear();
	athleticsCompositeEffectPool.clear();
	athleticsPlayerActionPool.clear();
	athleticsMonsterActionPool.clear(); 
	athleticsShapeActionsPool.clear();
	athleticsEffectPlistPool.clear();
	athleticsShapeSkillsPool.clear();
	athleticsSceneID=0;
}

void AthleticProcedureDataHandler::DestroyMemData()
{
	isUsingLocalDataReplace = false;
	isDuriningLocal = false;
	if(pAthleticsMapInfo)
	{
		pAthleticsMapInfo->destroy();
		delete pAthleticsMapInfo;
		pAthleticsMapInfo=NULL;
	}
	if(pPreAthleticsData!=NULL)
	{
		pPreAthleticsData->destroy();
		delete  pPreAthleticsData;
		pPreAthleticsData=NULL;
	}
	if(pAthleticProData!=NULL)
	{
		pAthleticProData->destroy();
		delete  pAthleticProData;
		pAthleticProData=NULL;
	}
	if(pAthleticResultData!=NULL)
	{
		pAthleticResultData->destroy();
		delete  pAthleticResultData;
		pAthleticResultData=NULL;
	}
	if(pAthleticBaseReward!=NULL)
	{
		pAthleticBaseReward->destroy();
		delete  pAthleticBaseReward;
		pAthleticBaseReward=NULL;
	}
	std::set<std::string>::const_iterator plist_iter=athleticsEffectPlistPool.begin();
	while(plist_iter!=athleticsEffectPlistPool.end())
	{
		switch(GetFileTypeFromName(*plist_iter))
		{
		case  _PLIST_FILE_TYPE_:
			_TRACE_UNLOAD_PLIST_((*plist_iter).c_str())
			_TRACE_UNLOAD_IMAGE_(GetPngPathFromPlist(*plist_iter).c_str())
			cocos2d::CCAnimationCache::sharedAnimationCache()->removeAnimationByName(GetAnimationNameFromPlistOrPng(*plist_iter).c_str());
			break;
		case  _IMAGE_FILE_TYPE_:
			_TRACE_UNLOAD_IMAGE_(GetPngPathFromPlist(*plist_iter).c_str())
			cocos2d::CCAnimationCache::sharedAnimationCache()->removeAnimationByName(GetAnimationNameFromPlistOrPng(*plist_iter).c_str());
			break;
		default:
			break;
		}  
		++plist_iter;
	}  
	athleticsPlayerSkillsPool.clear();
	athleticsMonsterSkillsPool.clear();
	athleticsPlayerShapePool.clear();
	athleticsCompositeEffectPool.clear();
	athleticsPlayerActionPool.clear();
	athleticsMonsterActionPool.clear(); 
	athleticsShapeActionsPool.clear();
	athleticsEffectPlistPool.clear();
	athleticsShapeSkillsPool.clear();
	athleticsSceneID=0;
}

/*
	加入预分析技能池
*/
void   AthleticProcedureDataHandler::pushSkillsPool(char roleType,int roleID,int skillID)
{
	if(roleType==_ATHLETICS_ROLE_PLAYER_TYPE_)
	{
	   std::map<int,std::set<int> >::iterator iter_skill=athleticsPlayerSkillsPool.find(roleID);
	   if(iter_skill!=athleticsPlayerSkillsPool.end())
	   {
		   iter_skill->second.insert(skillID);
	   }
	   else
	   {
		   std::set<int>  skillsPool;
		   skillsPool.insert(skillID);
		   athleticsPlayerSkillsPool.insert(std::map<int,std::set<int> >::value_type(roleID,skillsPool));
	   }
	}
	else if(roleType==_ATHLETICS_ROLE_MONSTER_TYPE_)
	{
		std::map<int,std::set<int> >::iterator iter_skill=athleticsMonsterSkillsPool.find(roleID);
		if(iter_skill!=athleticsMonsterSkillsPool.end())
		{
			iter_skill->second.insert(skillID);
		}
		else
		{
			std::set<int>  skillsPool;
			skillsPool.insert(skillID);
			athleticsMonsterSkillsPool.insert(std::map<int,std::set<int> >::value_type(roleID,skillsPool));
		}
	}
}

void   AthleticProcedureDataHandler::pushActionsPool(char roleType,int roleID,int actionID)
{
	if(actionID==-1||actionID==999)
		return ;

	if(roleType==_ATHLETICS_ROLE_PLAYER_TYPE_)
	{
		std::map<int,std::set<int> >::iterator iter_skill=athleticsPlayerActionPool.find(roleID);
		if(iter_skill!=athleticsPlayerActionPool.end())
		{
			iter_skill->second.insert(actionID);
		}
		else
		{
			std::set<int>  skillsAction;
			skillsAction.insert(actionID);
			athleticsPlayerActionPool.insert(std::map<int,std::set<int> >::value_type(roleID,skillsAction));
		}
	}
	else if(roleType==_ATHLETICS_ROLE_MONSTER_TYPE_)
	{
		std::map<int,std::set<int> >::iterator iter_skill=athleticsMonsterActionPool.find(roleID);
		if(iter_skill!=athleticsMonsterActionPool.end())
		{
			iter_skill->second.insert(actionID);
		}
		else
		{
			std::set<int>  skillsAction;
			skillsAction.insert(actionID);
			athleticsMonsterActionPool.insert(std::map<int,std::set<int> >::value_type(roleID,skillsAction));
		}
	}
}



/*
加入预分析的特效池
*/
void   AthleticProcedureDataHandler::pushEffectsPool(int effectID)
{
	if(effectID!=-1)
	athleticsCompositeEffectPool.insert(effectID);
}

/*
加入预分析的场景ID
*/
void    AthleticProcedureDataHandler::pushSceneID(int sceneID)
{
	athleticsSceneID=sceneID;
}

/*
加入角色外形池
*/
void   AthleticProcedureDataHandler::pushRoleShapesPool(char roleType,int roleID,int shapeID)
{
	if(roleType==_ATHLETICS_ROLE_PLAYER_TYPE_)
	{ 
		 RoleShapeInfo  roleShapeInfo;
		 roleShapeInfo.roleID=roleID;
		 roleShapeInfo.roleShapeID=shapeID;
		 athleticsPlayerShapePool.push_back(roleShapeInfo);
	}
	else if(roleType==_ATHLETICS_ROLE_MONSTER_TYPE_)
	{ 
		RoleShapeInfo  roleShapeInfo;
		roleShapeInfo.roleID=roleID;
		roleShapeInfo.roleShapeID=shapeID;
		athleticsMonsterShapePool.push_back(roleShapeInfo);
	}
}

 
void  AthleticProcedureDataHandler::pushAnimationPlistPool(std::string plistName)
{
	if(!plistName.empty())
	{
		athleticsEffectPlistPool.insert(plistName);
	}
}


void  AthleticProcedureDataHandler::startAnalysisShapeSkillsArray()
{
    //开始分析技能池
	FOR_EACH_ELEMENT_BEGIN(athleticsPlayerShapePool.size())
		std::map<int,std::set<int> >::iterator  shape_iter=athleticsPlayerSkillsPool.find(athleticsPlayerShapePool.at(index).roleID);
	if(shape_iter!=athleticsPlayerSkillsPool.end())
	{ 
		athleticsShapeSkillsPool.insert(std::map<int,std::set<int> >::value_type(athleticsPlayerShapePool.at(index).roleShapeID,shape_iter->second));
	} 
	FOR_EACH_ELEMENT_END

	FOR_EACH_ELEMENT_BEGIN(athleticsMonsterShapePool.size())
		std::map<int,std::set<int> >::iterator  shape_iter=athleticsMonsterSkillsPool.find(athleticsMonsterShapePool.at(index).roleID);
	if(shape_iter!=athleticsMonsterSkillsPool.end())
	{ 
		std::map<int,std::set<int> >::iterator second_iter=athleticsShapeSkillsPool.find(athleticsMonsterShapePool.at(index).roleShapeID);
		if(second_iter!=athleticsShapeSkillsPool.end())
		{
			std::set<int>::const_iterator iter=shape_iter->second.begin();
			while(iter!=shape_iter->second.end())
			{
				second_iter->second.insert(*iter);
				++iter;
			}
		}
		else
		{
			athleticsShapeSkillsPool.insert(std::map<int,std::set<int> >::value_type(athleticsMonsterShapePool.at(index).roleShapeID,shape_iter->second));
		}
	} 
	FOR_EACH_ELEMENT_END

	//开始分析受击动作池
	FOR_EACH_ELEMENT_BEGIN(athleticsPlayerShapePool.size())
	std::map<int,std::set<int> >::iterator  action_iter=athleticsPlayerActionPool.find(athleticsPlayerShapePool.at(index).roleID);
	if(action_iter!=athleticsPlayerActionPool.end())
	{ 
		athleticsShapeActionsPool.insert(std::map<int,std::set<int> >::value_type(athleticsPlayerShapePool.at(index).roleShapeID,action_iter->second));
	} 
	FOR_EACH_ELEMENT_END

	FOR_EACH_ELEMENT_BEGIN(athleticsMonsterShapePool.size())
		std::map<int,std::set<int> >::iterator  action_iter=athleticsMonsterActionPool.find(athleticsMonsterShapePool.at(index).roleID);
	if(action_iter!=athleticsMonsterActionPool.end())
	{ 
		std::map<int,std::set<int> >::iterator second_iter=athleticsShapeActionsPool.find(athleticsMonsterShapePool.at(index).roleShapeID);
		if(second_iter!=athleticsShapeActionsPool.end())
		{
			std::set<int>::const_iterator iter=action_iter->second.begin();
			while(iter!=action_iter->second.end())
			{
				second_iter->second.insert(*iter);
				++iter;
			}
		}
		else
		{
			athleticsShapeActionsPool.insert(std::map<int,std::set<int> >::value_type(athleticsMonsterShapePool.at(index).roleShapeID,action_iter->second));
		}
	} 
	FOR_EACH_ELEMENT_END
		 
}

void    AthleticProcedureDataHandler::exportAthleticsShapeArray(std::set<int> & rolesShapeArray)
{
	rolesShapeArray.clear();

    size_t  shapePoolSize=athleticsPlayerShapePool.size();
	FOR_EACH_ELEMENT_BEGIN(shapePoolSize)
	    rolesShapeArray.insert(athleticsPlayerShapePool.at(index).roleShapeID);
	FOR_EACH_ELEMENT_END
	shapePoolSize=athleticsMonsterShapePool.size();
	FOR_EACH_ELEMENT_BEGIN(shapePoolSize)
		rolesShapeArray.insert(athleticsMonsterShapePool.at(index).roleShapeID);
	FOR_EACH_ELEMENT_END
		  
}


int    AthleticProcedureDataHandler::getSkipAthleticVIPLevelByType(char athleticType)
{
	switch(athleticType)
	{
	case _ATHLETICS_CUSTOMS_BATTLE_TYPE_:
		{  
			return CLIENTCONSTDATAMANGER->getValueByKey(COUSTOM_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_ARENA_BATTLE_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(ARENA_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(TOWER_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_TEAM_BATTLE_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(TEAM_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_SERVANT_BATTLE_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(SERVANT_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_FRIEND_BATTLE_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(FRIENT_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_KUANGDONG_BATTLE_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(KUANGDONG_SKIP_VIP_LEVEL);
			break;
		}
	case _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_:
		{
			return CLIENTCONSTDATAMANGER->getValueByKey(KUANGDONG_HUNT_LIEREN_VIP_LEVEL);
			break;
		}
	default:
		return 100;
	}
}
