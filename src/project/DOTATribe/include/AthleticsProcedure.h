//Name：AthleticsProcedure
//Function：战斗流程
//Author:	Johny

#ifndef _DOTATRIBE_ATHLETICSPROCEDURE_H_
#define _DOTATRIBE_ATHLETICSPROCEDURE_H_

#include "../include/IProcedure.h"

#include <cocos2d.h>
#include <string>


class  AthleticsProcedure: public IProcedure
{
public:
	 enum
	 {
		 _TYPE_ATHLETICSPROCUDURE_UNKONW_,
		 _TYPE_ATHLETICSPROCUDURE_BEGIN_,         //战斗开始
		 _TYPE_ATHLETICSPROCUDURE_FIGHT_,         //战斗进行中
		 _TYPE_ATHLETICSPROCUDURE_PAUSE,          //战斗暂停
		 _TYPE_ATHLETICSPROCUDURE_END_,           //战斗结束
		 _TYPE_ATHLETICSPROCUDURE_NUMBER_,        //战斗事件
	 };
protected:
	int  m_SubType;						// 当前所属子流程
	bool m_bInputEnabled;				// 是否处于可输入状态
	bool m_bReStartProcedure;
	bool m_bStartGame;					//开始游戏
	bool m_bSycLoadFinish;
protected:
	long long m_LogicTickCounter;	    // 计时器
	int  m_preLoadTextureCount;		    // 预加载纹理图片数目
public:
	AthleticsProcedure();
	virtual ~AthleticsProcedure();

public:
	/*
		得到当前子流程
	*/
	int   GetSubType();

public:
	 
    //切换到选择副本流程
	void  OnChangeProcedureToSceneLobbyProcure();

	//切换到大厅流程
	void  OnChangeProcedureToMission();
   
	//切换到home界面流程
	void OnChangeProcedureToHome(int windowEventType);

	//切换到组队流程
	void OnChangeProcedureToTeamBattle();
  
	//开始异步分析和加载纹理
	void  StartAnalysisEffectPool();
	  
	//异步加载Texture/Plist回调
	void  SycLoadFinishCallHandler(cocos2d::CCObject * pSender); 

protected:
	/*
	 技能中的组合特效加入特效池
	*/
	void  PushEffectsPoolFromSkills();
	/*
	 额外动作中的特效加入特效池
	*/
	void  PushEffectsPoolFromExtAction();
	/*
	 场景中的特效加入特效池 
	*/
	void  PushEffectsPoolFromScene();
	/*
	 将特效池中的帧动画纹理加入预分析纹理池
	*/
	void  PushPreFrameTextureFromEffects();
	/*
	 将角色皮肤纹理加入预分析纹理池
	*/
	void  PushPreFrameTextureFromRoleShape();
	/*
	启动异步加载纹理和配置
	*/
	void  StartSyncLoadTextureAndPlist();
	/*
	预加载音效队列
	*/
	void  PushPreLoadSoundEffectQueue(); 
	/*
	从技能动作中获取组合特效
	*/
	int   GetCompositeEffectFromShape_Skill(int shapeID,int actionID);
	/*
	将组合特效中的帧动画加入预分析纹理
	*/
    void  PushFrameAnimationPlistFromComEffectID(int compositeEffectID);
	/*
	将帧动画加入预分析纹理
	*/
	void  PushFrameAnimationPlistFromEffectID(int frameAnimateEffectID);
	/*
	将角色皮肤和骨骼特效皮肤加入纹理池
	*/
	void  PushPreTextureImageWithRoleShapeID(int roleShapeID);
	/*
	游戏开始通知
	*/
	void  PostStartGameNotification();
public:
	virtual      bool     Init();
	virtual      void     Tick();
	virtual      void     Destroy();
	virtual      void     DestroyWithOutAthleticsData();

	void Init_Sub();
public:
	virtual      void     OnInputEventHandler(){};
	virtual      void     OnSystemEnterBackEventHandler();
	virtual      void     OnSystemEnterFrontEventHandler();
	virtual      void     OnSystemPauseEventHandler();
	virtual      void     OnSystemResumeEventHandler();


	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
	 
};

#endif