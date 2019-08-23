//Name：HeroicRole
//Function：战斗人物
//Author:	Johny

#ifndef   _TODAOTRIBE_HEROICROLE_H
#define   _TODAOTRIBE_HEROICROLE_H

#include  "../include/BaseObject.h"
#include  "../include/RoleBaseDataManager.h"
#include  "../include/HeroicRoleSkeletonNode.h"
#include  "../include/ActionSetDataManager.h"
#include  "../include/CommonNumberEffectManager.h"
#include  "../include/CommonEffectManager.h"
#include  "../include/VariableSpeedSequenceAction.h"
#include  "../include/CallFuncAction.h"
 

#include  "spine/spine-cocos2dx.h"
#include  "spine/SpineCallBackEvent.h"
  
#include   <cocos2d.h>
#include   <vector>
#include   <set>
  
const  float		Animation_Mix_Time= 0.15f;			//动作融合时间
const  std::string  Death_Action_Name="SiWang";			//死亡动作名称
 
using namespace cocos2d;
using namespace cocos2d::extension; 
 
class  CommonNumberEffectManager;

class   HeroicRole : public cocos2d::CCNode,public BaseObject,public SkeletonCallBackProtocol
{
public:
	//@角色通用基本动作单元  动作表中ID保持一致 
	enum
	{	
		UNKONW,
		DaiJi,              //待机
		Walk,				//行走
		GongJi,				//攻击
		ShouJi,				//受击
		ShengLi,			//胜利
		SiWang,				//死亡
		ShanBi,				//闪避
		BiSha,				//必杀
		GeDang,				//格挡
		ChuChang,			//出场
		XuanYun=13,			//眩晕
		ShunYi=15,			//瞬移 
		Active=17,			//激活
		Inactive=18,		//非激活
		Out=19,				//淡出
		In=20,				//淡入
		FuHuo=22,			//复活
	}; 
  
	//@角色状态属性 
	enum
	{
		_ROLE_DIZZY_STATE_,					    //眩晕状态
		_ROLE_SILENCE_STATE_,				    //沉默状态
		_ROLE_INVINCIBIE_STATE_,			    //无敌状态
		_ROLE_CASTING_STATE_,					//蓄力
		_ROLE_DECISIVE_STATE_,				    //决斗
		_ROLE_XUWU_STATE_,						//虚无
		_ROLE_DISAPPEAR_STATE_,					//隐身
	};

	enum
	{
		_ROLE_DEAD_INSTRUCTION_=999,			//服务器赋予的正常死亡指令
	};
 
public:
	HeroicRole();
	~HeroicRole();	
public:
	//@基本接口
	virtual   void   InitRole(int shapeID);
	virtual   void   Tick();
	virtual   void   Destroy();
	virtual   void   OnCommandHanlder(int EventTypeID);
	virtual   void   OnCommandHanlder(int EventTypeID,std::string attachParam);
public:
	//@更新角色自身Buffer管理器
	void   UpdateEffectManager();
    bool   isRoleInState(int state);				//获取和设置人物自身状态属性
	void   setRoleNoneState();						//清空角色当前状态
    void   addRoleState(int roleState);				//添加角色状态
	void   removeRoleState(int roleState);			//删除角色状态
	void   removeRoleAllState();					//删除角色所有状态
	void   excuteRoleStateAction();					//执行角色状态动作
public:
    //@角色属性数值相关接口
	void   setRoleType(char type);					//设置角色类型
	char   getRoleType();							//获得角色类型

	int    getHeroicShapeID();						//获得角色外形ID
	bool   IsRoleLive();							//判断角色血量是否减为0

	void   reduceRoleHPValue(int hpValue);			//减少血量
	void   increaseRoleHPValue(int hpValue);		//增加血量
	void   updateRoleHPValue(int hpValue);          //更新角色血量

	void   reduceRoleMPValue(int mpValue);			//减少蓝量
	void   increaseRoleMPValue(int mpValue);		//增加蓝量
	void   updateRoleMPValue(int mpValue);			//更新角色蓝量

	int    getCurHPValue();						    //获得角色当前血量
	int    getCurMpValue();						    //获得角色当前蓝量

	int    getInitHpValue();					    //获得角色初始血量
	int    getInitMPValue();					    //获得角色初始蓝量

	void   setInitHpValue(int initHpValue);		//设置角色初始HP值
	void   setInitMpValue(int initMpValue);		//设置角色初始MP值

	void   reSetRoleHPAndMPValue();

	bool   isRoleHPChange();					    //血量是否改变
	bool   isRoleMPChange();					    //蓝量是否改变

	void   setRoleIconID(int iconID);				//设置角色的头像ID
	int    getRoleIconID();							//获得角色的头像ID

	void   setRoleName(std::string name);			//设置角色名称
	std::string getRoleName();						//获取角色名称

public:
	//获得骨骼相关接口 
	cocos2d::extension::CCSkeletonAnimation* getRoleSkeletonNode();		  //获得骨骼结点   
	bool   setAnimationTimaScale(float timeScale);						  //设置动画速度系数
	bool   isCurAnimationLoop();										  //判断当前动画是否循环
	std::string  getCurAnimationName();									  //获得当前骨骼动画名称
	void   runExtAction(cocos2d::CCFiniteTimeAction * pAction);			  //运行额外动画指令
	void   setAnimationByID(int actionID,bool isLoop=false);			  //使用动作ID设置当前的动作				
	void   setAnimationByName(std::string animationName,bool isLoop=false);//使用动作名称设置当前动作
	bool   checkHeroicEffect(CCSkeletonAnimation* pEffectNode ,std::string animationName);//检测特效骨骼是否有
	int    getAnimationCount();											  //获得当前骨骼动画个数
	float  getCurAnimationTime();										  //获得当前动画播放时刻
	float  getCurAnimationDuration();									  //获得当前动画播放时长
	void   changeToIdleAnimation(bool isLoop=true);						  //切换至空闲状态

	void   playAdmissonAnimation();										  //播放角色入场动画			
	void   roleAdmissonEndCallBack();									  //角色入场动画完成回调事件
	void   reInitRoleAdmissonState();									  //复位角色各种状态   (重要函数接口)

	void   registerSkeletonEventDelegate(BaseObject *  pActionCompleteDelegate);   //注册骨骼动作完毕回调代理	 
	void   unRegisterSkeletonEventDelegate(BaseObject * pActionCompleteDelegate);  //注销骨骼动作完毕回调代理
	void   removeAllSkeletonEventDelegate();							  //移除所有的骨骼注册代理

public:
	/*
	 继承基类的方法
	*/
	virtual float        getPositionX(void);							   //设置当前Root结点的X坐标
	virtual float        getPositionY(void);							   //获取当前Root结点的Y坐标
	virtual void		 setPositionX(float x);							   //设置当前Root结点的X坐标  特效 & 阴影伴随	
	virtual	void		 setPositionY(float y);							   //设置当前Root结点的Y坐标  无阴影伴随 
	virtual void		 setVisible(bool visible);						   //设置结点的可视状态
	virtual void         setPosition(const CCPoint& newPosition);		   //设置当前Root的结点的坐标 (描点默认为 (0.5,0.0))		
public:
	void				setSkeletonVisiable(bool isVisiable);			 //设置骨骼可视状态
    cocos2d::CCPoint    getRolePosition();								 //获取当前Root结点的坐标 不能改名为setPosition 因为继承CCNode 会冲突
	int					getNodeZOrder();								 //获得Root的结点的Z序列
	void				setNodeZOrder(int zOrder);						 //修改Root的结点的Z序列
	void				setFlipX(bool isflip=true);						 //设置骨骼X轴水平方向的翻转  true为正常翻转
	bool                isVisible();									 //获得当前Root结点是否隐藏
	bool				isRoleAtInitXPos();								 //判断角色是否处于初始X坐标位置
	bool				isRoleAtInitYPos();								 //判断角色是否处于初始Y坐标位置
	bool				isRoleAtTargetXPos();							 //判断角色是否处于攻击者X坐标位置
	bool				isRoleAtTargetYPos();							 //判断角色是否处于攻击者Y坐标位置
	void				setInitPosition(cocos2d::CCPoint position);     //设定角色Root的初始位置
	cocos2d::CCPoint    getInitPosition();							     //获得角色的初始配置位置
	void				setTargetPosition(cocos2d::CCPoint targetPos);//设置角色目标攻击配置位置
	cocos2d::CCPoint    getTargetPosition();							 //获得角色的目标配置位置
	float				getInitXPos();									 //获得角色X初始配置位置
    float				getInitYPos();							         //获得角色Y初始配置位置
	void				forceMoveToTargetPosition();					 //强制设置角色到目标位置
	void				forceMoveToInitPosition();						 //强制设置角色到初始位置 				
	void				setFlipForAction(bool isHomeDirection=true);	 //设置角色的Flip方向
    VariableSpeedSequenceAction * runMoveToAction(bool isToTarget,float durationTime,float fSpeedScale,CallFunctionProtocol * pDelegate,int eventType);
	  
    //获取角色对象布局位置
    bool                isFightAtLeft();								 //获取当前角色位于结点的左右
	void                SetFightAtLeft(bool isFightLeft);
public:
	bool                hadPlayedDeadAnimation();
	bool				checkCurAnimationWithID(int actionID);

    //角色自身状态动画 
	void                onPlayDeadAnimation();							//播放角色死亡动画 之后会修改
	void				onPlayeWinAnimation();							//播放胜利动画
	void                onPlayBringAnimation();							//播放复活动画 
	bool				isAnimationComplete(int actionID);				//判断指定动作是否播放完毕
	 
    //获得当前角色非循环的特效数目
    size_t   GetUnLoopCommonEffectCount();

	//判断当前所有数字特效是否已经触发数值更新
	bool     GetAllNumberEffectTriggered();

	//获得当前角色持续特效的数目
	size_t   GetLoopCommonEffectCount();
 
	//启动  循环播放指定角色动作
	void    OnPlayRoleResidesActionByID(int actionID);
 
	//取消  角色指定循环持续动作
	void    OnStopRoleResidesAction();
 
	//设置角色特效动画的速度系数
	void   SetRoleEffectAnimationSpeedScale(float speedScale);
 
	//角色普通Effect动画接口  //加载人物的EffectID
	void	OnPlayCommonEffect(int compositeEffectID,int effectType,int effectID);
	 
	//播放骨骼绑定特效
	void	OnPlayCommonEffectWithBone(int compositeEffectID,int effetType,int effectID,cocos2d::extension::Bone * pBindBone);

	//播放启动驻留特效   
	void    OnPlayCommonEffect(int commpositeEffectID);   
	 
	//附加EffectBuffer
	void    OnPlayCommonEffect(CommonEffect * pCommonEffect);

	//结束Effect动画接口
	void    OnStopCommonEffect(int compositeEffectID);
	  
	//角色数字Effect动画接口
	void	OnPlayNumberBufferByID(int numberEventType, int numberEffectID,int numberical);
	
	//关闭非持续粒子特效
	void	OnStopUnLoopParticleEffect();
	  
	//关闭角色所有特效
	void	OnStopAllEffect();

	//重置关闭当前骨骼所有回调
	void	OnStopAllSkeletonCallBack();
	  
	//获得Plist中帧动画的帧数目
	int     GetAnimationFrameCount(std::string animationName);	

    //骨骼定时回调接口
	void    skeletonTriggerCallHandler(int eventType,int animationID,cocos2d::extension::PSkeletonCallBack_Node  pSkeletonCallBackNode);

	//骨骼绑点回调接口
	void    boneBindEffectCallHandler(int eventType,BoneEfectData & boneEffectData);
 
	/*
	获取当前空闲动作名称
	*/
	std::string  getIdleActionName();
	
	/*
	获取动作ID对应的动作名称
	*/
	std::string  getSkillActionNameByID(int ActionID);	

	/*
	获得动作名称对应的动作ID
	*/
	int			 getSkillActionIDByName(std::string ActionName);

protected:
	//内部访问方法  
	/*
	  角色动作表
	*/
	ActionSetDataManager *  getRoleActionSetData();					 

	/*
	发送骨骼完成回调通知
	*/
	void     postAnimateCompNotification(int eventType,int attachParam);
 
	/*
	注册角色骨骼动作融合
	*/
	void      setAnimationStateMixByName(cocos2d::extension::CCSkeletonAnimation* SkeletonNode,
		cocos2d::extension::CCSkeletonAnimation* EffectSkeletonNodeUp,
		cocos2d::extension::CCSkeletonAnimation* EffectSkeletonNodeDown);
	 
protected:
	int   roleLevelValue;											  //角色等级
	int   curRoleHPValue;											  //当前血量
	int   initRoleHPValue;											  //角色总血量
	int   curRoleMPValue;											  //当前蓝量
	int   initRoleMPValue;											  //角色总蓝量
	int   preHpValue;												  //上次血量
	int   preMpValue;												  //上次蓝量
	bool  isRoleFightLeft;											  //是否位于左战斗区域
	cocos2d::CCSprite	*  heroRoleShadowSprite;					  //英雄阴影纹理
	cocos2d::extension::CCSkeletonAnimation* heroicRoleSkeletonNode;  //英雄主骨骼动画
	cocos2d::extension::CCSkeletonAnimation* heroicEffectNodeUp;	  //英雄特效动画人前
	cocos2d::extension::CCSkeletonAnimation* heroicEffectNodeDown;	  //英雄特效动画人后　
protected:
	/*
	   内部属性数据
	*/
	char   roleType;												  //角色类型
	int	   roleShapeID;												  //角色外形ID
	int    roleIconID;												  //角色头像ID
	std::string  roleName;											  //角色名称
	  
    bool   isAdmittanceFinish;										  //判断入场动画是否结束

	CommonNumberEffectManager * pCommonNumberEffectManager;			  //角色的数值特效管理器
	CommonEffectManager   *     pCommonEffectManager;				  //角色Effect特效管理器
 
	cocos2d::CCPoint   roleInitPosition;							  //角色的初始位置
	cocos2d::CCPoint   roleTargetPosition;							  //角色的攻击位置
	 
	bool   isInSpecifyAction;										  //角色是否处于循环特殊动作中
	int    specifyActionID;											  //角色特殊状态动作ID (当前为眩晕)
 	int    curRoleState;											  //当前角色复合状态
  
	bool   hadPlayDeadAnimate;										  //是否播放死亡动画 
	std::set<BaseObject *>			 	m_lSkeNotificationList;		  //骨骼动作完毕回调代理队列

	ActionSetDataManager* pActionData;								  //骨骼动作访问器

};
 
 

#endif