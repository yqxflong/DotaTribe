//Name：AtheleticsSceneManager
//Function：战斗系统总入口
//Author:	Johny

#ifndef   _DOTATRIBE_ATHLETICSSCENEMANAGER_H
#define   _DOTATRIBE_ATHLETICSSCENEMANAGER_H

#include  <cocos2d.h>
#include  <include/common/Singleton.h>
#include  "../include/HeroicRole.h"
#include  "../include/AthleticProcedureDataType.h"
#include  "../include/AthleticsUIManager.h"
#include  "../include/RoleInfoDataHandler.h"
#include  "../include/UIBaseDialog.h"
#include  "../include/CommonEffect.h"
#include  "../include/NpcTalkView.h"
 
#include  <map>
#include  <set>
#include <math.h>
using  namespace  cobra_win;
 
#define   LowRoleZOrder		  6				//低角色ZOrder值
#define   LeftRoleTag		  111			//左角色Tag值
#define   HighRoleZOrder	  9				//高角色ZOrder值
#define   RightRoleTag		  112			//右角色Tag值
#define   SkillsPanelZOrder	  15			//技能信息面板的ZOrder层级
#define   ScreenEffectTag	  3333			//屏幕特效ColorLayer的Tag

class UIBaseDialogProtory;
  
class AthleticsSceneManager : public cocos2d::CCNode, public UIBaseDialogProtory, public cobra_win::Singleton2<AthleticsSceneManager> 
{ 

public:
    //@战斗记录类型
	enum
	{
		_ATHLETICS_UNKONW_RECORD_TYPE_=-1,			//未知记录类型
		_ATHLETICS_LIVE_RECORD_TYPE_,				//直播战斗记录类型
		_ATHLETICS_REPLAY_RECORD_TYPE_,				//转播战斗记录类型
	};

	//@战斗观看类型
	enum
	{
		_ATHLECTICS_UNKONW_WATCH_TYPE_,				//未知观看类型	
		_ATHLECTICS_SELFT_WATCH_TYPE_,				//上台表演类型
		_ATHLECTICS_OTHER_WATCH_TYPE_,				//凑热闹观看类型
	};
		 
	 
	//@内部事件通知
	enum
	{
		_ATHLETICS_UNKOWN_EVENT_,					//未知内部事件通知
		_ATHLETICS_ADMITTANCE_FINISH_CALL_EVENT_,	//角色入场动画回调完毕
		_ATHLETICS_GAME_OVER_CALL_EVENT_,			//游戏完毕

	};
	 
	AthleticsSceneManager();
	virtual ~AthleticsSceneManager();
public:
	//@标配
	bool  Init();
	void  Tick();
	void  Destroy();

	//@获得战斗场景的Root层
	cocos2d::CCNode *  GetAthleticsRootLayer();

	//@获得战斗禁用层
	cocos2d::CCNode *  GetAthleticsDiableMark();

	//@获得NPC对话层
	cocos2d::CCNode *  GetAthleticsNpcTalkLayer();

    //@获得角色的目标攻击位置
	cocos2d::CCPoint  GetRoleTargetPositon(bool isLeft=true);
	 
	//@设置NPC对话层可视状态
	void    SetAthleticsNpcTalkLayerVisible(bool isVisible);

	//@事件通知接口
	void   OnCommandHanlder(int EventTypeID,void * ptr); 

	//@对话回调处理函数
	void   BaseDialogCallBackHandler(int eventType,void * ptr);
	 
	//@删除战斗特效纹理数据
	void  DestroySkillsEffectTextureData();
 
	//@战斗地图信息数据包
	bool  LoadAthleticsMapInfo();

    //@战前角色信息包加载
	bool   LoadAthleticPreData();

	//@战斗结果信息包加载
	bool   LoadAthleticResultData();

	//@检测是否为查看战斗类型
	bool  LoadAthleticRecordType();

	//@检测是否需要播放NPCTalk
	bool  LoadNpcTalkConfigData();

	//@检测Npc处理管理器
	void  NpcTalkManagerHandler(int eventType);
 
	//@初始化战斗场景UI   负责场景环境配置以及人物基础属性UI更新
	void   InitAthleticSceneUI();
 
	//@根据当前的轮次  创建战斗角色骨骼纹理  延时回调入场动画
	void   OnUpdateAthleticsRoleSkeleton(RoleUniqeDefine role1,RoleUniqeDefine role2);			

    //@延时入场回调  播放入场动画
	void   CallBackPlayAdmittance();

	//@延迟战斗结果回调 播放战斗结算界面
	void   CallBackPlayResultUI();

    //@预加载战斗角色骨骼角色
	bool   PreLoadAthleticRole();

	//@获取战斗类型(副本 竞技 组队 切磋等)
	char  GetAthleticBattleType();
	 
    //@获取左边战斗对象  (玩家组)
	HeroicRole *  GetLeftFightRole();

    //@获取右边战斗对象  (敌方组)
	HeroicRole *  GetRightFightRole();

	//@获取主控者的对象
	HeroicRole *  GetExecuteRole(bool isLeft);
	 
	//@判断游戏是否已经结束
	bool  IsGameOver();

	//@设置游戏是否结束
	void  SetGameOver();

	//@播放胜利者的动画
	void  OnPlayWinAnimation();

	//@更新用户的血量
	void  OnUpdateRoleHPValue();

	//@更新角色的蓝量
	void  OnUpdateRoleMPValue();

	//@重播战斗
	void  OnRePlayAthleticsGame();   
  
	//@更新角色BufferTick
	void  OnUpdateRoleTickBuffer();

	//@Post战斗结果UI通知
	void  PostGameOverUINofitication();

	//@重置所有人的血量和蓝量
	void  OnResetAllRoleHPAndMP();

    //@获得血条和蓝条的矩形纹理宽度
	float GetHPRectWidth();
	float GetMPRectWidth();

	//@开启禁用层
	void   ShowAthleticsDisableLayer();

	//@关闭禁用层
	void   HideAthleticsDiableLayer();
	 
	//@屏幕震动特效   
	void  OnPlayScreenShake(int compositeEffectID,int shakeItemID);

	//@关闭特效
	void  OnStopScreenShake(int compositeEffectID=-1);


	//@设置震动速度
	void  OnSetScreenShakeEffectSpeedScale();

	//@更新屏幕震动特效
	void  UpdateScreenShakeEffect();

	//@设置异步加载的纹理
	void  SetSycLoadTexurePlistPool(std::set<std::string> & texturePlistPool);
	 
	//@改变场景播放速度切换
	void  OnChangeAthleticsSpeed();				
	void  UpdateAthleticsSystemSpeed(float athleticsSpeed);
	void  UpdateAthleticSpeedUI();
 
												
	//@加入小伙伴战队
	void   AddHeroicRoleInGroup(PBaseRoleInfo pBaseRoleInfo,bool isPlayerGronp);		
  
	//@获得玩家组指定Role
	HeroicRole *     IsRoleInPlayGroup(RoleUniqeDefine & role);

	//@获得敌方组指定Role
	HeroicRole *     IsRoleInEnmeyGroup(RoleUniqeDefine & role);

	//@更新RoleInfo
	void			 SetRoleWithRoleData(RoleUniqeDefine & role);
	 
	//@获得当前战斗的观看类型
	char    GetAthelticsWatchType();

	//@设置当前战斗的观看类型
	void    SetAthleticsWatchType(char watchType);

	//@获取左队战斗结果
	bool    GetAthleticsResult();

	//@检测胜利者是否在初始位置
	bool	IsWinRoleNeedHoming();
	
	//@获取待归位的角色信息
	void    GetNeedHomingRoleInfo(RoleUniqeDefine & roleInfo);

	//@单轮战斗即将结束通知
	void    PostCurRoundWillDid();

	//@更新组队更新
	void    UpdateTeamIcon(bool isPlayerGroup);

	//@清空战败队列头像
	void    UnActiveAllTeamIcon(bool isPlayerGroup);
  
	//@是否可以触发VIP跳过战斗
	bool    IsTriggerVIPSkipHandler();
private:
	//@分析战斗结果
	void  AnalyseAthleticsResult();

	//@判断当前VIP等级是否可以跳过此战斗
	bool  IsVIPCanSkipAthletics();

	//@VIP跳过战斗处理
	void  VipSkipAthleicsHandler();

	//@关闭角色所有Action 
	void  StopActiveRoleAllAction();
	  
private:	 
	/*
	 to do  统一变量名称命名规则
	*/
	PAthleticsMapInfo		 pAthleticsMapInfo;				//战斗地图信息
	PPreAthleticsData		 pPreAthleticsData;			    //战前人物信息数据包
	PAthleticsResultData     pAthleticResultData;			//战斗结果数据包
 
    AthleticsUIManager  *    pAthleticsUIManager;			//战斗场景UI管理器

	NpcTalkView   *			 pNpcTalkView;					//NPC对话视图
     
	std::vector<HeroicRole *>       playGroupHeroicList;    //玩家组
	std::vector<HeroicRole *>       enemyGroupHeroicList;	//敌方组
  
    int  curPlayGroupRoleID;		//当前玩家组角色ID
	char curPlayGroupRoleType;		//当前战斗角色类型
 
	int  curEnmeyGroupRoleID;		//当前敌方组角色ID
	char curEnmeyGroupRoleType;		//当前战斗角色类型

    bool isPlayGroupRoleChange;		//当前玩家组角色是否改变 
	bool isEnemyGroupRoleChange;	//当前敌军组角色是否改变
	 
	bool isTryPlayNpcTack;			//是否播放NPCTalk
	char npcBattleTalkState;		// NPCTack播放状态
 
  //////////////////////////////////////////////////////////////////////////
	  
	HeroicRole *  leftFightRole_;		//左角色
	HeroicRole *  rightFightRole_;		//右角色
	  
	float     hpRectWidth_;				//HP矩形条宽度
	float     mpRectWidth_;				//MP矩形条宽度
 		
	bool      isGameOver_;				//判断游戏是否结束

	bool      isRePlayAthletics_;		//是否重播战斗

	std::multimap<int,CommonEffect *> m_shakeEffectList;
	 
	std::set<std::string>  preLoadPlistTexturePool;
	  
	unsigned char     athleticBattleType;  //战斗类型
 
	short	 callBackAdmittanceCount;	//角色入场动画完成回调次数

	short    admittanceTickCount;		//入场动画回调次数计数器

	char     athleticRecordType;		//战斗记录类型

	char     athleticWatchType;			//战斗观看类型
	  
	bool	 isBattleWin;				//战斗是否胜利 

	float    m_fRoleAdmissonDelayTime;   //战斗角色入场延迟时间 

	float    m_fResultWinDelayTime;		 //战斗结果延时时间

	bool	 m_bIsTriggerVIPSkip;		//是否触发跳过VIP战斗

	bool	 m_bIsLayOutUIData;		//是否已经删除UI数据

	bool	m_bStartGame;

//@战斗速度管理
//#点击变速按钮，变换顺序为1->2->3->1倍
//begin
public:
	//是否为1倍速度
	bool IsNormalSpeed(){
		return fabs(AthleticsSpeed-NormalSpeed)<0.001;
	}
	bool IsDoubleSpeed(){
		return fabs(AthleticsSpeed-NormalSpeedx2)<0.001;
	}
	bool IsTripleSpeed(){
		return fabs(AthleticsSpeed-NormalSpeedx3)<0.001;
	}

	static float AthleticsSpeed;		//当前战斗速度
private:
	float	  NormalSpeed;				//1倍速度
	float     NormalSpeedx2;			//2倍速度
	float	  NormalSpeedx3;			//3倍速度
//end
};

#define  ATHLETICSSCENEMANAGER  (AthleticsSceneManager::get_instance2())

#endif