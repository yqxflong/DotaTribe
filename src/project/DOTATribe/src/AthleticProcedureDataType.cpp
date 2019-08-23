//Name��AthleticProcedureDataType
//Function��ս������ָ������
//Author:	Johny

#include   <cocos2d.h>
#include "../include/AthleticProcedureDataType.h"
#include "../include/SCAthleticsDataPacket.h"
#include "../include/AthleticProcedureDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFToolController.h"
#include "../include/LocalAthleticsDataManager.h"
  
/*
���﹫����������
*/
void CommonRoleAttribute::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>sword;   //�ǵøĻ�ȥ
	packet>>hpValue;
	packet>>mpValue;
	packet>>minAttack;
	packet>>maxAttack;
	packet>>speed;
	packet>>hit;
	packet>>dodge;
	packet>>armor;
	packet>>exposeArmor;
	packet>>crit;
	packet>>uncrit;
	packet>>skillCount;

	int  skillIconID=0;
	COMMON_BEIGIN_ARRAY(char,skillCount)
		packet>>skillIconID;
		skillIconArray.push_back(skillIconID);
	COMMON_END_ARRAY 
}

/*
�������
*/

void PlayerRole::decodePacketData(cobra_win::DPacket & packet)
{

	packet.read(playerID);
	NFC_ParsePacketString(packet,playerName);
	packet.read(playerLevel);
	packet.read(heroicID);
	NFC_ParsePacketString(packet,heroicName);
	packet.read(shapeID);
	packet.read(iconID);
	 
	ATHLETICPROCEDUREDATA->pushRoleShapesPool(_ATHLETICS_ROLE_PLAYER_TYPE_,playerID,shapeID);
	 
	PCommonRoleAttribute pCRA=new CommonRoleAttribute();
	if(pCRA!=NULL)
	{
		pCRA->decodePacketData(packet);
		this->pCommonRoleAttribute=pCRA;
	}
}

/*
�������� ���
*/
void MonsterRole::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet.read(monsterID); 
	NFC_ParsePacketString(packet,monsterName); 
	packet.read(monsterLevel);
	packet.read(shapeID);
	packet.read(iconID);
	
	ATHLETICPROCEDUREDATA->pushRoleShapesPool(_ATHLETICS_ROLE_MONSTER_TYPE_,monsterID,shapeID);

	PCommonRoleAttribute pCRA=new CommonRoleAttribute();
	if(pCRA!=NULL)
	{
		pCRA->decodePacketData(packet);
		this->pCommonRoleAttribute=pCRA;
	}
}

/*
������ɫ��Ϣ
*/
void BaseRoleInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>roleType;
	switch(roleType)
	{
	case  baseroleinfo_tag::_BASE_ROLE_PLAYER_TYPE_:
		{
			PPlayerRole pPlayerRole=new PlayerRole();
			if(pPlayerRole!=NULL)
			{
				pPlayerRole->decodePacketData(packet);

				pRoleInfoData=pPlayerRole;
			}
			break;
		}
	case  baseroleinfo_tag::_BASE_ROLE_MONSTER_TYPE_:
		{
			PMonsterRole pMonsterRole=new MonsterRole();
			if(pMonsterRole!=NULL)
			{
				pMonsterRole->decodePacketData(packet);

				pRoleInfoData=pMonsterRole;
			}
			break;
		}
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
//ս����ͼ��Ϣ 
//////////////////////////////////////////////////////////////////////////
  
void AthleticsMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>battleType;
	if(AthleticProcedureDataHandler::get_instance2()!=NULL)
	{
		AthleticProcedureDataHandler::get_instance2()->athleticsBattleType=battleType;
	}
	switch (battleType)
	{
	case _ATHLETICS_CUSTOMS_BATTLE_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new CustomsMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}
		break;
	case _ATHLETICS_ARENA_BATTLE_TYPE_:
		{
			 mapInfoData=(PAthleticsBaseMap)new ArenaMapInfo();
			 if(mapInfoData)
			 {
				 mapInfoData->decodePacketData(packet);
			 }
		}
		break;
	case _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new TowerMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}
		break;
	case _ATHLETICS_TEAM_BATTLE_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new TeamMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}
		break;
	case _ATHLETICS_SERVANT_BATTLE_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new ServantMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}break;
	case _ATHLETICS_FRIEND_BATTLE_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new ArenaMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}
		break;
	case _ATHLETICS_KUANGDONG_BATTLE_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new MiningMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
			
		}break;
	case _ATHLETICS_BOSSSCORE_BATTLE_TYPE_:
		{
			mapInfoData = (PAthleticsBaseMap)new BossScoreMapInfo();
			if(mapInfoData)
				mapInfoData->decodePacketData(packet);
		}
		break;
	case _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_:
		{ 
			mapInfoData=(PAthleticsBaseMap)new CustomsMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}
		break;
	case _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_:
		{
			mapInfoData=(PAthleticsBaseMap)new CustomsMapInfo();
			if(mapInfoData)
			{
				mapInfoData->decodePacketData(packet);
			}
		}break;
	default:
		break;
	}
}

/*
�ؿ���ͼ��Ϣ
*/
void CustomsMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(mapID);
	packet.read(stageID);
	packet.read(sceneID); 
	if(getEnableLocalAthletiData())
	{
		if(!ATHLETICPROCEDUREDATA->isDuriningLocal&&ATHLETICPROCEDUREDATA->athleticsBattleType==_ATHLETICS_CUSTOMS_BATTLE_TYPE_)
		{ 
			if((mapID==getWillReplaceMapID1()&&stageID==getWillReplaceStageID1())||(mapID==getWillReplaceMapID2()&&stageID==getWillReplaceStageID2()))
			{  
			}
			else
			{
				LocalAthleticsDataManager::get_instance2()->PushAthleticsDPacket(packet,mapID,stageID);
			}
		} 
	}

	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);
	NFC_ParsePacketString(packet,sceneName);
}

//boss����
void BossScoreMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(mapID);
	packet.read(stageID);
	packet.read(sceneID);
	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);		
	NFC_ParsePacketString(packet,sceneName);
}
  
//��
void MiningMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(mapID);
	packet.read(stageID);
	packet.read(sceneID);
	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);		
	NFC_ParsePacketString(packet,sceneName);
	CCLOG("Scene Name: %s lenght:%d",sceneName.c_str(),sceneName.length());
}

//�ʹ�
void ServantMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(mapID);
	packet.read(stageID);
	packet.read(sceneID);
	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);		
	NFC_ParsePacketString(packet,sceneName);
}

//���
void TeamMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(mapID);
	packet.read(stageID);
	packet.read(sceneID);
	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);		
	NFC_ParsePacketString(packet,sceneName); 
}

/*
������ͼ��Ϣ
*/
void TowerMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sceneID);
	packet.read(mapID);
	packet.read(floor);
	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);
}


/*
������ͼ��Ϣ
*/
void ArenaMapInfo::decodePacketData(cobra_win::DPacket & packet)
{
    packet.read(sceneID);
	ATHLETICPROCEDUREDATA->pushSceneID(sceneID);
}
 

/*
Ψһ��ɫ��ʾ����
*/
void RoleUniqeDefine::decodePacketData(cobra_win::DPacket & packet)
{
    packet.read(unitType);
	packet.read(sourceID);
}

/*
ս�������Ϣ
*/
void RoleResultData::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(unitType);
	packet.read(sourceID);	
	packet.read(winType);
}

/*
 *	�ؿ���������
 */
void CustomsRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(starLevel);
	packet.read(rewardMoney);
	packet.read(rewardExp);
	packet.read(rewarHeroicExp);
	packet.read(rewardItemCount);
	short rewardCount=rewardItemCount;
	FOR_EACH_ATHLETICSUNIT_BEGIN(rewardCount)
       PRewardBaseData pRewardBaseData=new RewardBaseData();
		if(pRewardBaseData!=NULL)
		{	
			pRewardBaseData->decodePacketData(packet);
			rewardVec.push_back(pRewardBaseData);
		}
	FOR_EACH_ATHLETICSUNIT_END
}


void ArenaRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	 packet.read(winType); 
	 packet.read(rewardPrestige);
	 packet.read(rewardMoney);
	  
}

void HuntLieRenRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(rewardMoney);
	packet.read(rewardExp);
	packet>>hasExtra;

	if(hasExtra > 0)
	{
		pRewardItem = new NewRewardItem();
		pRewardItem->decodePacketData(packet);
	}
}

void MiningRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(rewardMoney);
	packet.read(rewardExp);

	packet.read(rewardItemCount);
	short rewardCount=rewardItemCount;
	FOR_EACH_ATHLETICSUNIT_BEGIN(rewardCount)
		PRewardItem pRewardItem=new RewardItem();
	if(pRewardItem!=NULL)
	{	
		pRewardItem->decodePacketData(packet);
		rewardVec.push_back(pRewardItem);
	}
	FOR_EACH_ATHLETICSUNIT_END

}

void BossScoreRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>fightScore;
}

void ServantRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet.read(shengwang);
}

void TeamRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(rewardMoney);
	packet.read(rewardExp);

	packet.read(rewardItemCount);
	short rewardCount=rewardItemCount;
	FOR_EACH_ATHLETICSUNIT_BEGIN(rewardCount)
		PRewardItem pRewardItem=new RewardItem();
	if(pRewardItem!=NULL)
	{	
		pRewardItem->decodePacketData(packet);
		rewardVec.push_back(pRewardItem);
	}
	FOR_EACH_ATHLETICSUNIT_END
}


void TowerRewardInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(rewardMoney);
	packet.read(rewardExp);

	packet.read(rewardItemCount);
	short rewardCount=rewardItemCount;
	FOR_EACH_ATHLETICSUNIT_BEGIN(rewardCount)
		PRewardItem pRewardItem=new RewardItem();
	if(pRewardItem!=NULL)
	{	
		pRewardItem->decodePacketData(packet);
		rewardVec.push_back(pRewardItem);
	}
	FOR_EACH_ATHLETICSUNIT_END
}

 
void AthleticsResultData::decodePacketData(cobra_win::DPacket & packet)
{
   packet.read(firstBattleCount);
   FOR_EACH_ATHLETICSUNIT_BEGIN(firstBattleCount);
     PRoleResultData pRoleResultData=new RoleResultData();
	 if(pRoleResultData!=NULL)
	 {
          pRoleResultData->decodePacketData(packet);
		  firstBattleResultVector.push_back(pRoleResultData);
	 }
   FOR_EACH_ATHLETICSUNIT_END

   packet.read(secondBattleCount);
   FOR_EACH_ATHLETICSUNIT_BEGIN(secondBattleCount);
   PRoleResultData pRoleResultData=new RoleResultData();
   if(pRoleResultData!=NULL)
    {
	   pRoleResultData->decodePacketData(packet);
	   secondBattleResultVector.push_back(pRoleResultData);
    }
   FOR_EACH_ATHLETICSUNIT_END
 
}
 

void AthleticsBaseReward::decodePacketData(cobra_win::DPacket & packet)
{
	battleType=AthleticProcedureDataHandler::get_instance2()->athleticsBattleType;
	packet.read(hasReward);
	if(hasReward==_BASEREWARD_REWARD_TYPE_)
	{
		switch(battleType)
		{
		case _ATHLETICS_CUSTOMS_BATTLE_TYPE_:
			{
				battleType=_ATHLETICS_CUSTOMS_BATTLE_TYPE_;
				rewardDataInfo=(PBaseRewardInfo)new CustomsRewardInfo();
				if(rewardDataInfo)
				rewardDataInfo->decodePacketData(packet); 
			}break;
		case _ATHLETICS_ARENA_BATTLE_TYPE_:
			{
				//��������������
				 battleType=_ATHLETICS_ARENA_BATTLE_TYPE_;
				 rewardDataInfo=(PBaseRewardInfo)new ArenaRewardInfo();
				 if(rewardDataInfo)
				 rewardDataInfo->decodePacketData(packet); 
			}break;
		case _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_:
			{
				battleType = _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_;
				unsigned char win;//�Ƿ�ʤ��
				packet>>win;
				CLIMBTOWERDATAHANDLER->fightResult = win;
				if(win)
				{
					rewardDataInfo=(PBaseRewardInfo)new TowerRewardInfo();
					if(rewardDataInfo)
					rewardDataInfo->decodePacketData(packet);
				}
				//�����Ķ������ݣ���������End����
				CLIMBTOWERDATAHANDLER->enterData.decodePacketData(packet);
			}break;
		case _ATHLETICS_TEAM_BATTLE_TYPE_:
			{
				battleType = _ATHLETICS_TEAM_BATTLE_TYPE_;
				rewardDataInfo=(PBaseRewardInfo)new TeamRewardInfo();
				if(rewardDataInfo)
				rewardDataInfo->decodePacketData(packet);
			 
			}break;
		case _ATHLETICS_SERVANT_BATTLE_TYPE_:
			{
				battleType = _ATHLETICS_SERVANT_BATTLE_TYPE_;
				rewardDataInfo=(PBaseRewardInfo)new ServantRewardInfo();
				if(rewardDataInfo)
				rewardDataInfo->decodePacketData(packet);
			}break;
		case _ATHLETICS_FRIEND_BATTLE_TYPE_:
			{
				battleType = _ATHLETICS_FRIEND_BATTLE_TYPE_;
			}break;
		case _ATHLETICS_KUANGDONG_BATTLE_TYPE_:
			{
				battleType = _ATHLETICS_KUANGDONG_BATTLE_TYPE_;
				rewardDataInfo=(PBaseRewardInfo)new MiningRewardInfo();
				if(rewardDataInfo)
				rewardDataInfo->decodePacketData(packet); 
			}break;
		case _ATHLETICS_BOSSSCORE_BATTLE_TYPE_:
			{
				battleType = _ATHLETICS_BOSSSCORE_BATTLE_TYPE_;
				rewardDataInfo = (PBaseRewardInfo)new BossScoreRewardInfo();
				if(rewardDataInfo)
					rewardDataInfo->decodePacketData(packet);
			}break;
		case _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_:
			{
				battleType = _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_;
				rewardDataInfo = (PHuntLieRenRewardInfo)new HuntLieRenRewardInfo();
				if(rewardDataInfo)
					rewardDataInfo->decodePacketData(packet);
			}break;
		default:
			break;
		}
	}
}



/*
ս��ǰ��ɫ��λ��Ϣ(սǰ������Ϣ��)
*/
void PreAthleticsDataInfo::decodePacketData(cobra_win::DPacket & packet)
{
	short  dequecount=0;
	/*������һ��ս��������Ϣ*/
	packet>>firstDequeCount;
	dequecount=firstDequeCount;
	FOR_EACH_ATHLETICSUNIT_BEGIN(dequecount)
		PBaseRoleInfo  pBaseRoleInfo=new BaseRoleInfo();
		if(pBaseRoleInfo!=NULL)
		{
			pBaseRoleInfo->decodePacketData(packet);
			firstdequeRoleVector.push_back(pBaseRoleInfo);
		}
	FOR_EACH_ATHLETICSUNIT_END

	/*�����ڶ���ս��������Ϣ*/
	packet>>secondDequeCount;
	dequecount=secondDequeCount;
	FOR_EACH_ATHLETICSUNIT_BEGIN(dequecount)
		PBaseRoleInfo  pBaseRoleInfo=new BaseRoleInfo();
		if(pBaseRoleInfo!=NULL)
		{
			pBaseRoleInfo->decodePacketData(packet);
			seconddequeRoleVector.push_back(pBaseRoleInfo);
		}
	FOR_EACH_ATHLETICSUNIT_END

}


/*
���ܸ��ӻ����
*/
void SkillAttach_Base::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(effectID);
	packet.read(targetType);
	packet.read(targetID);
	ATHLETICPROCEDUREDATA->pushEffectsPool(effectID);
}


/*
���ܹ���ָ������
*/
void AthleticsData_SKILL::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(skillItemID);
	packet.read(hurtActionID);
	packet.read(assailantIDType);
	packet.read(assailantID); 
	packet.read(targetIDType);
	packet.read(targetID); 
	packet.read(skillActionType);
	packet.read(counterAttackSkillID); 
	packet>>effectCount;
	 
	//���ܻ��������붯������
	ATHLETICPROCEDUREDATA->pushActionsPool(targetIDType,targetID,hurtActionID);
    //�������߼��뼼�ܳ�
	ATHLETICPROCEDUREDATA->pushSkillsPool(assailantIDType,assailantID,skillItemID);

	if(effectCount>0)
	{
		char  effectType=0;
		FOR_EACH_ATHLETICSUNIT_BEGIN(effectCount)
			packet>>effectType;
		switch(effectType)
		{
		case _ATHLETICS_SKILL_SOURCE_HP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_SOURCE_HP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_SOURCE_MP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_SOURCE_MP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_TARGET_HP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_TARGET_HP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_TARGET_MP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_TARGET_MP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_REDUCE_MP_TYPE_:
		case _ATHLETICS_SKILL_RELIVE_HP_TYPE_:
		case _ATHLETICS_SKILL_RELIVE_MP_TYPE_:
			{
				PSkillAttach_Numberical  pSkillAttachNumberical=new SkillAttach_Numberical();
				if(pSkillAttachNumberical!=NULL)
				{
					pSkillAttachNumberical->effectType=effectType;
					pSkillAttachNumberical->decodePacketData(packet);
					skillAttachEffectVector.push_back(pSkillAttachNumberical);
				}
				break;
			}
		case _ATHLETICS_SKILL_CHANAGE_SHAPE_TYPE_:
			{
				PSkillAttach_ChangeShape pSkillAttachChangeShape=new SkillAttach_ChangeShape();
				if(pSkillAttachChangeShape!=NULL)
				{
					pSkillAttachChangeShape->effectType=effectType;
					pSkillAttachChangeShape->decodePacketData(packet);
					skillAttachEffectVector.push_back(pSkillAttachChangeShape);
				}
				break;
			}

		case _ATHLETICS_SKILL_ADD_STATE_TYPE_:
		case _ATHLETICS_SKILL_REMOVE_STATE_TYPE_:
			{
				PSkillAttach_State  pSkillAttachState=new SkillAttach_State();
				if(pSkillAttachState!=NULL)
				{
					pSkillAttachState->effectType=effectType;
					pSkillAttachState->decodePacketData(packet);
					skillAttachEffectVector.push_back(pSkillAttachState);
				}
				break;
			}
		case _ATHLETICS_SKILL_ADD_EFFECT_TYPE_:
		case _ATHLETICS_SKILL_REMOVE_EFFECT_TYPE_:
			{
				PSkillAttach_Base  pSkillAttachEffect=new SkillAttach_Base();
				if(pSkillAttachEffect!=NULL)
				{
					pSkillAttachEffect->effectType=effectType;
					pSkillAttachEffect->decodePacketData(packet);
					skillAttachEffectVector.push_back(pSkillAttachEffect);
				}
				break;
			}
		case _ATHLETICS_SKILL_CHANGE_POSITION_TYPE_:
			{
				PSkillAttach_Change_Position pSkillAttachChangePostion=new SkillAttach_Change_Position();
				if(pSkillAttachChangePostion!=NULL)
				{
					pSkillAttachChangePostion->effectType=effectType;
					pSkillAttachChangePostion->decodePacketData(packet);
					skillAttachEffectVector.push_back(pSkillAttachChangePostion);
				}
				break;
			}
		default: 
			break;
		}
		FOR_EACH_ATHLETICSUNIT_END
	}
}

 

/*
���ܸ�����������
*/
void SkillAttach_Numberical::decodePacketData(cobra_win::DPacket & packet)
{
	skillattach_base_tag::decodePacketData(packet);
	packet>>numbericalValue;
}

/*
���ܸ��ӱ�������
*/
void SkillAttach_ChangeShape::decodePacketData(cobra_win::DPacket & packet)
{
	skillattach_base_tag::decodePacketData(packet);
	packet.read(shapeId);
}

/*
���ܸ���״̬����
*/
void SkillAttach_State::decodePacketData(cobra_win::DPacket & packet)
{
	skillattach_base_tag::decodePacketData(packet);
	packet>>state;
}

/*
���ܸ��� Buffer����  ��ʱ����
*/	 
void SkillAttach_Buffer::decodePacketData(cobra_win::DPacket & packet)
{//this function not used
	skillattach_base_tag::decodePacketData(packet);
	packet.read(effectID);
	packet.read(sourceID);
	ATHLETICPROCEDUREDATA->pushEffectsPool(effectID);
}

/*
���ܸ���  �ı�λ������
*/
void SkillAttach_Change_Position::decodePacketData(cobra_win::DPacket & packet)
{
	skillattach_base_tag::decodePacketData(packet);
	packet.read(position);
}
 

//////////////////////////////////////////////////////////////////////////
//������ ���ݽṹ
//////////////////////////////////////////////////////////////////////////

void AthleticsData_Buffer::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sourceType);
	packet.read(sourceID);
	packet.read(effectID);
	ATHLETICPROCEDUREDATA->pushEffectsPool(effectID);
}

 
void AthleticsData_State::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sourceType);
	packet>>sourceID;
	packet>>roleState;
}



void AthleticsData_Location::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sourceType);
	packet>>sourceID;
	packet.read(skillItemID);
	packet>>location;
}



void AthleticData_Numberical::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sourceType);
	packet>>sourceID;
	packet>>numbericalValue;
}


void AthleticData_Role_Bring::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(sourceType);
	packet>>sourceID;
	packet>>hpValue;
	packet>>mpValue;
}

//@ս���������ݽ���
void AthleticsUnitData::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(athleticsIndex);
	packet>>athleticsType;

	switch(athleticsType)
	{
	case _ATHLETICSINSTRUCTION_SKILL_TYPE_:
		{
			PAthleticsData_SKILL  pAthleticsSkillData=new AthleticsData_SKILL();
			if(pAthleticsSkillData!=NULL)
			{
				pAthleticsSkillData->decodePacketData(packet);
			}
			athleticsData = pAthleticsSkillData;
			break;
		}
	case _ATHLETICSINSTRUCTION_REMOVE_EFFECT_TYPE_:
	case  _ATHLETICSINSTRUCTION_ADD_EFFECT_TYPE_:
		{
			PAthleticsData_Buffer pAthleticsDataRemoveBuffer=new AthleticsData_Buffer();
			if(pAthleticsDataRemoveBuffer!=NULL)
			{
				pAthleticsDataRemoveBuffer->decodePacketData(packet);
			}
			athleticsData=pAthleticsDataRemoveBuffer;
			break;
		}
	case _ATHLETICSINSTRUCTION_REMOVE_STATE_TYPE_:
	case _ATHLETICSINSTRUCTION_ADD_STATE_TYPE_:
		{
			PAthleticsData_State pAthleticsDataRemoveState=new AthleticsData_State();
			if(pAthleticsDataRemoveState!=NULL)
			{
				pAthleticsDataRemoveState->decodePacketData(packet);
			}
			athleticsData=pAthleticsDataRemoveState;
			break;
		}
	case  _ATHLETICSINSTRUCTION_LOCATION_TYPE_:
		{
			PAthleticsData_Location pAthleticsChangeLocation=new AthleticsData_Location();
			if(pAthleticsChangeLocation!=NULL)
			{
				pAthleticsChangeLocation->decodePacketData(packet);
			}
			athleticsData=pAthleticsChangeLocation;
			break;
		}
	case _ATHLETICSINSTRUCTION_RESTORE_HP_TYPE_:
	case _ATHLETICSINSTRUCTION_RESTORE_MP_TYPE_:
	case  _ATHLETICSINSTRUCTION_DAMAGE_HP_TYPE_:
	case  _ATHLETICSINSTRUCTION_DAMAGE_MP_TYPE_:
		{
			PAthleticData_Numberical pAthleticDataNumberical=new AthleticData_Numberical();
			if(pAthleticDataNumberical!=NULL)
			{
				pAthleticDataNumberical->decodePacketData(packet);
				athleticsData=pAthleticDataNumberical;
			}
			break;
		}
	case  _ATHLETICSINSTRUCTION_ROLE_BRING_TYPE_:
		{
			PAthleticData_Role_Bring pAthleticDataRoleBring=new AthleticData_Role_Bring();
			if(pAthleticDataRoleBring!=NULL)
			{
				pAthleticDataRoleBring->decodePacketData(packet);
				athleticsData=pAthleticDataRoleBring;
			}
			break;
		}
	default:
		break;
	}
}

 

void AthleticsProcedureData::decodePacketData(cobra_win::DPacket & packet)
{
    packet.read(roleType1);
	packet.read(roleID1);
	packet.read(roleType2);
	packet.read(roleID2);
	packet.read(athleticsCount);

	FOR_EACH_ATHLETICSUNIT_BEGIN(athleticsCount)

		PAthleticsUnitData pAthleticsUnitData=new AthleticsUnitData();
		if(pAthleticsUnitData!=NULL)
		{
			pAthleticsUnitData->decodePacketData(packet);
			athleticsDataVector.push_back(pAthleticsUnitData);
		}

	FOR_EACH_ATHLETICSUNIT_END
}


void AthleticsProData::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(totalTurnCount);

	assert(totalTurnCount>0);
	if(totalTurnCount<=0)
		return;
	short athleticsTurnCount=totalTurnCount;

	FOR_EACH_ATHLETICSUNIT_BEGIN(athleticsTurnCount)
		//�������ֻغ���ս������ָ�����ݰ�
		PAthleticsProcedureData  pAthleticsProcedureData=new AthleticsProcedureData();
		if(pAthleticsProcedureData!=NULL)
		{
			pAthleticsProcedureData->decodePacketData(packet);

			totalAthleticsDataVector.push_back(pAthleticsProcedureData);
		}
	FOR_EACH_ATHLETICSUNIT_END
}


//////////////////////////////////////////////////////////////////////////
//������Ʒ�����
//////////////////////////////////////////////////////////////////////////

void RewardBaseData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>itemType;
	switch(itemType)
	{
	case  rewardbase_tag::_REWARDBASE_ITEMS_TYPE_:
		{
			rewardData=(PRewardBaseItem)new RewardItem();
			if(rewardData)
			rewardData->decodePacketData(packet);			 
			break;
		}
	case  rewardbase_tag::_REWARDBASE_GLOD_TYPE_:
	case  rewardbase_tag::_REWARDBASE_PLAYEREXP_TYPE_:
	case  rewardbase_tag::_REWARDBASE_COASTEXP_TYPE_:
		{
			rewardData=(PRewardBaseItem)new RewardNumber();
			if(rewardData)
			rewardData->decodePacketData(packet); 
			break;
		}
	default:
		break;
	}
}

 
/*
������ֵ
*/
void RewardNumber::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>numberValue;
}


void RewardItem::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet>>catogory;
	packet>>templateID;
    NFC_ParsePacketString(packet,itemName);
	packet>>itemQuality;
	packet>>itemCount;
	packet>>iconID;
}

void NewRewardItem::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>type;
	packet>>count;
	if(type == 0)
	{
		packet>>catogory;
		packet>>templateId;
		NFC_ParsePacketString(packet, itemName);
		packet>>quality;
		packet>>iconId;
	}

	if(type == kDT_AWARD_MONEY)
	{//��Ǯ
		iconId = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD);
		itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_MONEY_TID);
	}
	else if(type == kDT_AWARD_EXP)
	{//����
		iconId = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP);
		itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_EXP_TID);
	}
	else if(type == kDT_AWARD_DIAMOND)
	{//��ʯ
		iconId = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND);
		itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_DIAMOND_TID);
	}
	else if(type == kDT_AWARD_PRESTIGE)
	{//����
		iconId = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE);
		itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_PRESTIGE_TID);
	}
	else if(type == kDT_AWARD_POWER)
	{//����
		iconId = CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG);
		itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_POWER_TID);
	}
}