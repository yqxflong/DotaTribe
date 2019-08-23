//Name：AthleticsUIManager
//Function：战斗UI管理器
//Author:	Johny

#ifndef     _DOTATRIBE_ATHLETICSUIMANGER_H_
#define     _DOTATRIBE_ATHLETICSUIMANGER_H_

#include    <cocos2d.h>
#include    "../include/AthleticProcedureDataType.h"
#include    "../include/UITwoSideStretchNodeLayer.h"
#include    "../include/AthleticsSkillPanel.h"
#include    "../include/CTeamIconProgress.h"


using namespace cocos2d;
class    AthleticsUIManager : public  cocos2d::CCNode
{
public:
	AthleticsUIManager();
   ~AthleticsUIManager();
public:
	virtual  void  Init();
	virtual  void  Tick();
	virtual  void  Destroy();
public:

    //@加载战斗地图信息数据包
	void   LoadAthleticsMapInfoUIData(PAthleticsMapInfo pAthleticsMapInfo);
 
	//@加载战前人物信息数据包
	void   LoadPreAthleticsUIData(PPreAthleticsData pPreAthleticsData);

	//@分析玩家组是否在第一队列中
	void   CheckPlayGroupIsInFirstDeque();

	//@获取当前玩家是否在第一组队列中
	bool   GetIsPlayGroupInFirstDeque();
 
    //@初始化场景UI
	void   InitSceneUI(); 

	//@销毁角色属性UI
	void   DestroySceneUI();


	//@分析左右战队列人物 显示组队人员
	void   AnlayseTeamRoleNumber(int playGroupNum,int enemGroupNum);
	 
	//@重置组队头像队列
	void   ResetTeamIconList();

	//@更新组队头像队列
	void   UpdateTeamIconList(bool isPlayerGroup);

	//@清空组队队列
	void  UnActiveAllTeamIcon(bool isPlayerGroup);

public:
    PBaseRoleInfo  GetPlayGroupRoleInfo(RoleUniqeDefine & role);
	PBaseRoleInfo  GetFirstPlayGroupRoleInfo();
	bool		   CheckPBaseInfoEquipUniqeDefine(PBaseRoleInfo pBaseRoleInfo,RoleUniqeDefine & role);
	PBaseRoleInfo  GetEnemyGroupRoleInfo(RoleUniqeDefine & role);
	PBaseRoleInfo  GetFirstEnemyGroupRoleInfo();

	//@获得战斗场景的根节点
	cocos2d::CCNode *   GetAthleticsRootLayer();

	//@初始化场景特效
	void	InitSceneUIEffect();
	  
	//@根据当前的轮次 更新场景角色属性UI
	void   UpdateAthleticRoleInfoUI();

	//@更新左右的RoleInfoData
	void   UpdateRoleInfoData(bool isPlayerGroup=true);
	void   UpdateRoleInfoData(PBaseRoleInfo pBaseRoleInfo,bool isPlayerGroup);


	//@更新血条和蓝条
	void   ReInitRectImage(bool isLeftGroup=true);
 
	//@更新Role的RoleInfoData
	void   UpdateRoleInfoData(RoleUniqeDefine role,bool isPlayGroup);
	 
	//@显示VIPLayout  Speed Exit
	void  ShowVIPLayouBtn();

	//@显示Replay Speed Exit For Normal
	void  ShowNormalAllLayoutBtn();
 
	//@初始化角色的属性面板  技能面板
	void   InitRolePropertyUI();

    void   UpdateRoleHPValue(bool isLeftRole=true);
	void   UpdateRoleMPValue(bool isLeftRole=true);

	void   UpdateAthleticSpeedBtnUI();

	//@更新角色的属性面包 各种属性值
	void   UpdateRolePropertyUI(SKILLPENLDATA  skillData,bool isLeftSkillPanel=true);

    //@左技能面板点击事件
	void  OnLeftSkillPanelClick(cocos2d::CCObject * pSenderObj);

	//@右技能面板点击事件
	void  OnRightSkillPanelClick(cocos2d::CCObject * pSenderObj);


protected:
	//@播放场景特效
	void  PlaySceneEffect(int sceneEffectID);

	//@播放场景帧特效
	void   PlaySceneFrameEffect(int sceneFrameEffectID);

	//@播放场景粒子特效
	void   PlaySceneParticelEffect(int sceneParticleEffectID);

	//@加入场景特效
	void   AddScenceEffectList(cocos2d::CCNode * pSceneEffect);
	
protected:
	PAthleticsMapInfo	pAthleticsMapInfo_;					 //战斗地图数据包
	PPreAthleticsData   pPreAthleticsData_;					 //战前人物数据包
 
	std::vector<PBaseRoleInfo>     firstAthleticsDeque;

	std::vector<PBaseRoleInfo>     secondAthleticsDeque;
   
	short      totalAthleticsTurnCount;						 //总的战斗轮数	
	short      curAthleticsTurnIndex;					     //当期战斗轮索引ID  
	bool	   isPlayerGroupInFirstDeque;				     //玩家组是否在第一参战队列
 
	UITowSideStretchNodeLayer *  pSkillPanelLayer;			 //左右伸缩控件
	AthleticsSkillPanel *  pLeftAthleticSkillPanel;		     //左边的技能面板
	AthleticsSkillPanel *  pRightAthleticSkillPanel;		 //右边的技能面板

	float   m_bloodWidth_;
	float   m_blueWidth_;

	int     sceneID;				//场景ID
	std::string  sceneName;			//场景名称

	std::vector<cocos2d::CCNode *> sceneEffectList;		//场景特效列表
	char   tmpStr[32];

	CTeamIconProgress   *  pLeftTeamIconProgress;		//左边组队头像进度条

	CTeamIconProgress	*  pRightTeamIconProgress;		//右边组队头像进度条

	bool    m_bVIPLayOut;

};

 
#endif