//Name£∫AtheleticConfig
//Function£∫’Ω∂∑œ‡πÿ≈‰÷√
//Author:	Johny

#ifndef   _DOTA_ATHELETICCONFIG_H
#define   _DOTA_ATHELETICCONFIG_H

#include   "../include/CPublicVarReader.h"
#include   "../include/ResourceIDDataManager.h"
#include   "../include/SysLangDataManager.h"
#include   "../include/ClientConstDataManager.h"
#include   "../include/VariableSystem.h"
#include   "../include/SceneInfoDataManager.h"
#include "../include/ParticleDataManager.h"
#include "../include/CompositeEffectDataManager.h"
//
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

//@AthleticsUIManager
//#resource
#define    _SPEED_NORMAL_NORAML_UP			659
#define    _SPEED_NORAML_SELECT_DONW		660

#define    _SPEED_DOUBLE_NORMAL_UP			661
#define	   _SPEED_DOUBLE_SELECT_DOWN	    662

#define	   _SPEED_TRIPLE_NORMAL_UP			829
#define	   _SPEED_TRIPLE_SELECT_DOWN		830

#define    _SKILLDESC_EXPAND_BTN_UP			663
#define    _SKILLDESC_EXPAND_BTN_DOWN		664

#define    _SKILLDESC_BG_					665

#define   _LITTER_BOY_LIGHT_				666
#define   _LITTER_BOY_GRAP_					667
////////////////////////////////////////////////////////////////
#define    _ADDCOAT_LEVEL_TXT_				606			// + 
#define    _SWORD_LABEL_TXT_				682 


#define  FOR_EACH_ATHLETICSUNIT_BEGIN(athleticsCount)    for(short athleticsIndex=0;athleticsIndex<athleticsCount;athleticsIndex++) {
#define  FOR_EACH_ATHLETICSUNIT_END						 }


//@AtheleticsSceneManager
//
#define  FOR_EACH_ATHLETICSUNIT_BEGIN(athleticsCount)    for(short athleticsIndex=0;athleticsIndex<athleticsCount;athleticsIndex++) {
#define  FOR_EACH_ATHLETICSUNIT_END						 }

#define  VARIABLESYSTEM_START_ATHLETICS				VariableSystem::get_instance2()->SetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"DotaAthletics","isInAthletics",true);
#define  VARIABLESYSTEM_END_ATHLETICS				VariableSystem::get_instance2()->SetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"DotaAthletics","isInAthletics",false);
#define  VARIABLESYSTEM_SET_PLAY_MODE(playSpeed)	VariableSystem::get_instance2()->SetVariable(VariableSystem::_TYPED_CONFIG_MEM_,"DotaAthletics","AthleticsSpeed",playSpeed);


//@CommonEffectManager
//
#define  FOR_EACH_EFFECT_BEGIN(count)  for(size_t index=0;index<count;index++) {
#define  FOR_EACH_EFFECT_END           }
#endif