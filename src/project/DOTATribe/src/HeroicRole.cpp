//Name：HeroicRole
//Function：战斗人物
//Author:	Johny

#include  "../include/HeroicRole.h"
#include  "../include/EngineSystem.h"
#include  "../include/DOTATribeApp.h"
#include  "../include/AthleticsSceneManager.h"
#include  "../include/AnimationFileDataManager.h"
#include  "../include/InputCommand.h"
#include  "../include/RoleShapeDataManager.h"
#include  "../include/HeroicRoleSkeletonNode.h"
#include  "../include/ActionSetDataManager.h"
#include  "../include/DBSystem.h"
#include  "../include/SoundDataManager.h"
#include  "../include/ResourceIDDataManager.h"
#include  "../include/CompositeEffectDataManager.h"
#include  "../include/ProfSystem.h"
#include  "../include/EventSystem.h"
#include  "../include/EventTyper.h"
#include  "../include/NFAnimationController.h"
 
#include  <string>
#include  <map>

#define    DEAULTSHOWROLETIME    0.000001f				//入场动画回调
#define    DEFAULTNODEANCHOR     ccp(0.5f,0.0f)			//默认的角色描点
#define    REVERSE_ANGLE		 180.0f					//反向旋转角度
#define    NORMAL_ANGLE			 0.0f					//正向旋转角度

#define    SHADOW_EFFECT_ZORDER	 -1						//阴影层级
#define	   DOWN_EFFECT_ZORDER	 0						//人后骨骼特效相对层级
#define    NORAML_EFFECT_ZORDER	 2						//人物骨骼层级
#define    UP_EFFECT_ZORDER		 4						//人后骨骼层级

 
using namespace cocos2d;

HeroicRole::HeroicRole()
{
	  roleType=_ATHLETICS_UNKONW_ROLE_TYPE_;			 //角色类型
	  objectType_=	HEROICROLE_OBJECT_TYPE;				 //对象类型

	  curRoleState=0;									 //当前人物持续状态	
             
      curRoleHPValue=-1;							     //当前血量
      initRoleHPValue=0;								 //总血量

	  initRoleMPValue=0;								 //当前蓝值
      curRoleMPValue=-1;								 //总蓝值
 
	  preHpValue=-1;									 //上次血量
	  preMpValue=-1;									 //上次蓝量
	   
	  isRoleFightLeft=true;								 //是否位于左战斗区
  
	  pCommonNumberEffectManager=NULL;					 //数值特效管理器
	  pCommonEffectManager=NULL;						 //战斗特效管理器

	  hadPlayDeadAnimate=false;							 //是否播放死亡动画
  
	  heroRoleShadowSprite=NULL;						//角色阴影结点
	  heroicRoleSkeletonNode = NULL;					//角色骨骼结点
	  heroicEffectNodeUp = NULL;						//角色人前骨骼特效结点
	  heroicEffectNodeDown = NULL;						//角色人后骨骼特效结点
	  pActionData=NULL;

	  roleInitPosition=cocos2d::CCPointZero;			//角色初始位置坐标
	  roleTargetPosition=cocos2d::CCPointZero;			//角色攻击位置坐标

	  isAdmittanceFinish=false;							//是否入场完毕
	  isInSpecifyAction=false;							//是否处于Debuffer眩晕装备

	  roleLevelValue=0;									//当前等级
	  specifyActionID=-1;								//特殊循环动作ID	
	  roleShapeID=0;									//角色外形ID
	  roleIconID=0;										//角色头像ID
	  roleName="";										//角色名称
	  m_lSkeNotificationList.clear();					//骨骼事件通知队列
	    
}


HeroicRole::~HeroicRole()
{
      //do to
	CCLog("HeroicRole Destroy Handler ");
}
 
int     HeroicRole::getHeroicShapeID()
{
    return roleShapeID;
}
 
bool  HeroicRole::IsRoleLive()
{
	return  curRoleHPValue>0 ? true:false;
}

void   HeroicRole::setRoleType(char type) 
{
    roleType = type;
}
char   HeroicRole::getRoleType() 						 
{
	return roleType;
}
 

void   HeroicRole::reduceRoleHPValue(int hpValue)
{
	if(hpValue>0)
	{ 
		if(curRoleHPValue-hpValue<=0)
		{
			curRoleHPValue=0;
		}
		else
		{
			curRoleHPValue-=hpValue;
		}
		if(0==curRoleHPValue&&!hadPlayDeadAnimate)
		{ 
		   onPlayDeadAnimation();
		}
	}
}

void   HeroicRole::increaseRoleHPValue(int hpValue)
{ 
	if(hpValue>0)
	{
		if(curRoleHPValue+hpValue>=initRoleHPValue)
		{
			curRoleHPValue=initRoleHPValue;
			return ;
		}
		curRoleHPValue+=hpValue;
	}
}
void   HeroicRole::updateRoleHPValue(int hpValue)           //更新角色血量
{
    if(hpValue>=initRoleHPValue)
	{
		curRoleHPValue= initRoleHPValue;
	}
	else if(hpValue<initRoleHPValue&&hpValue>0)
	{
		curRoleHPValue=	hpValue;
	}
	else
	{
		curRoleHPValue=	0; 
	}
}

 

void   HeroicRole::reduceRoleMPValue(int mpValue)
{
	if(mpValue>0)
	{ 
		if(curRoleMPValue-mpValue<0)
		{
			curRoleMPValue=0;
		}
		else
		{
			curRoleMPValue-=mpValue;
		}
	}

}
void   HeroicRole::increaseRoleMPValue(int mpValue)
{
	if(mpValue>0)
	{
		if(curRoleMPValue+mpValue>=initRoleMPValue)
		{
			curRoleMPValue=initRoleMPValue;
			return ;
		}
		curRoleMPValue+=mpValue;
	}
}


void   HeroicRole::updateRoleMPValue(int mpValue) 			//更新角色蓝量
{
	if(mpValue>initRoleMPValue)
	{
		curRoleMPValue=initRoleMPValue;
	}
	else if(mpValue>0&&mpValue<=initRoleMPValue)
	{
		curRoleMPValue=mpValue;
	}
	else
	{
		curRoleMPValue=0;
	}
}

 

int    HeroicRole::getCurHPValue()
{
	return   curRoleHPValue;
}
int    HeroicRole::getCurMpValue()
{
    return   curRoleMPValue;
}

int    HeroicRole::getInitHpValue()
{
	return   initRoleHPValue;
}

int    HeroicRole::getInitMPValue()
{
    return   initRoleMPValue;
}
 
void   HeroicRole::setInitHpValue(int initHpValue)
{
     if(initRoleHPValue!=initHpValue)
	 {
		 initRoleHPValue=initHpValue;
		 curRoleHPValue=initRoleHPValue;
		 preHpValue=-1; 
	 }
}

void   HeroicRole::setInitMpValue(int initMpValue)
{
	if(initRoleMPValue!=initMpValue)
	{
		initRoleMPValue=initMpValue;
		curRoleMPValue=initRoleMPValue;
		preMpValue=-1;					 
	}
}

void   HeroicRole::reSetRoleHPAndMPValue()
{
	 curRoleHPValue=initRoleHPValue;
	 curRoleMPValue=initRoleMPValue;
	 preHpValue=-1;
	 preMpValue=-1;		
}


bool   HeroicRole::isRoleHPChange()
{
	if(preHpValue!=curRoleHPValue)
	{
		preHpValue=curRoleHPValue;
		return  true;
	}
	return false;
}


bool   HeroicRole::isRoleMPChange()
{
	if(preMpValue!=curRoleMPValue)
	{
		preMpValue=curRoleMPValue;
		return true;
	}
	return false; 
}
 

bool     HeroicRole::isFightAtLeft()
{
    return isRoleFightLeft;
}

void     HeroicRole::SetFightAtLeft(bool isFightLeft)
{ 
	isRoleFightLeft=isFightLeft;
}
 
void   HeroicRole::setRoleIconID(int iconID) 			 
{
	 roleIconID=iconID;
}
int    HeroicRole::getRoleIconID() 
{
	 return roleIconID;
}

void   HeroicRole::setRoleName(std::string name)
{
	 roleName=name;
}
std::string HeroicRole::getRoleName()
{
	 return roleName;
}

//@初始化角色  
void   HeroicRole::InitRole(int shapeID)
{
	//初始基类结点
	CCNode::init();

	roleShapeID=shapeID;
	  
	pActionData=getRoleActionSetData();

	//创建英雄骨骼节点
	HeroicRoleSkeletonNode * pHeroicRole = new HeroicRoleSkeletonNode();
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	pHeroicRole->init(pData->mShapeAnimationFile,pData->mShapeAnimationImage,
		pData->mShapeAnimationEffectFileUp,pData->mShapeAnimationEffectImageUp,
		pData->mShapeAnimationEffectFileDown,pData->mShapeAnimationEffectImageDown);
	heroicRoleSkeletonNode = pHeroicRole->GetSkeletonNode(); 

	//角色骨骼结点
	if(heroicRoleSkeletonNode)
	{ 
		heroicRoleSkeletonNode->registerCallBackDelegate(this);
		heroicRoleSkeletonNode->m_ObjectUUID=_to_event_param_(roleShapeID);
	} 

	//特效骨骼节点 
	if (pHeroicRole->GetEffectNodeUp() != NULL)
		heroicEffectNodeUp = pHeroicRole->GetEffectNodeUp();
	if (pHeroicRole->GetEffectNodeDown() != NULL)
		heroicEffectNodeDown = pHeroicRole->GetEffectNodeDown();

	CC_SAFE_DELETE(pHeroicRole);
   
	heroicRoleSkeletonNode->setAnchorPoint(DEFAULTNODEANCHOR);

	if(!isRoleFightLeft)
	{
		if(heroicRoleSkeletonNode)
		{
			heroicRoleSkeletonNode->setRotationY(REVERSE_ANGLE);
		}
		if(heroicEffectNodeUp)
		{
			heroicEffectNodeUp->setRotationY(REVERSE_ANGLE);
		}
		if(heroicEffectNodeDown)
		{
			heroicEffectNodeDown->setRotationY(REVERSE_ANGLE);
		}
	}

	//设置动画平滑过渡区间
	setAnimationStateMixByName(heroicRoleSkeletonNode,heroicEffectNodeUp,heroicEffectNodeDown);

	if(heroicEffectNodeDown)
	CCNode::addChild(heroicEffectNodeDown,DOWN_EFFECT_ZORDER);
	if(heroicRoleSkeletonNode)
	CCNode::addChild(heroicRoleSkeletonNode,NORAML_EFFECT_ZORDER);
	if(heroicEffectNodeUp)
	CCNode::addChild(heroicEffectNodeUp,UP_EFFECT_ZORDER);

	//创建英雄Shadow结点  暂时直接使用图片纹理路径  之后将做打包处理  
	heroRoleShadowSprite=cocos2d::CCSprite::create();
	heroRoleShadowSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(156));
	if(heroRoleShadowSprite)
	{ 
		heroRoleShadowSprite->setOpacity(160);
		CCNode::addChild(heroRoleShadowSprite,SHADOW_EFFECT_ZORDER);
	}
  
	pCommonNumberEffectManager=CommonNumberEffectManager::CreateNumberEffectManager(this);
	pCommonEffectManager=CommonEffectManager::CreateCommonEffectManager(this);
}
 

void   HeroicRole::Tick()
{ 
	if(!IsValid())
		return ;

	 BaseObject::Tick(); 

	 UpdateEffectManager();

	 roleAdmissonEndCallBack();  //to do
}	



bool   HeroicRole::isRoleInState(int state)
{
	if((curRoleState >> state & 0x00000001)  == 1)
	{
		return true;
	}
	return false;
}
 
 
//清空角色当前状态
void   HeroicRole::setRoleNoneState() 	
{ 
	if(pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->RemoveAllLoopCommonEffect();
	}
	 removeRoleAllState();
	 curRoleState=0;
}

 
void   HeroicRole::addRoleState(int roleState)
{
     switch(roleState)
	 {
	 case  _ROLE_DIZZY_STATE_:
		 {
			  curRoleState|=1<<_ROLE_DIZZY_STATE_; 
			  break;
		 }
	 case  _ROLE_SILENCE_STATE_:
		 {
			  curRoleState|=1<<_ROLE_SILENCE_STATE_; 
			 break;
		 }
	 case  _ROLE_INVINCIBIE_STATE_:
		 {
			 curRoleState|=1<<_ROLE_INVINCIBIE_STATE_; 
			 break;
		 }
	 case  _ROLE_CASTING_STATE_:
		 {
			 curRoleState|=1<<_ROLE_CASTING_STATE_; 
			 break;
		 }
	 case  _ROLE_DECISIVE_STATE_:
		 {
			 curRoleState|=1<<_ROLE_DECISIVE_STATE_; 
			 break;
		 }
	 case  _ROLE_XUWU_STATE_:
		 {
		    curRoleState|=1<<_ROLE_XUWU_STATE_; 
			 break;
		 }
	 case _ROLE_DISAPPEAR_STATE_:
		 {
			 if(pCommonEffectManager!=NULL)
			 pCommonEffectManager->SetAllBindBoneEffectVisible(false);
			 heroicRoleSkeletonNode->setVisible(false);
		     curRoleState|=1<<_ROLE_DISAPPEAR_STATE_; 
			 break;
		 }
	 default: 
		 break;
	 }
}

 
void   HeroicRole::removeRoleState(int roleState)
{
	switch(roleState)
	{
	case  _ROLE_DIZZY_STATE_:
		{
			curRoleState&=~(1<<_ROLE_DIZZY_STATE_);
		    OnStopRoleResidesAction();
			break;
		}
	case  _ROLE_SILENCE_STATE_:
		{
			curRoleState&=~(1<<_ROLE_INVINCIBIE_STATE_);
			break;
		}
	case  _ROLE_INVINCIBIE_STATE_:
		{
		    curRoleState&=~(1<<_ROLE_INVINCIBIE_STATE_);
			break;
		}
	case  _ROLE_CASTING_STATE_:
		{
			 curRoleState&=~(1<<_ROLE_CASTING_STATE_);
			break;
		}
	case  _ROLE_DECISIVE_STATE_:
		{
			 curRoleState&=~(1<<_ROLE_DECISIVE_STATE_);
			 break;
		}
	case _ROLE_XUWU_STATE_:
		{
			 curRoleState&=~(1<<_ROLE_XUWU_STATE_);
			 break;
		}
	case _ROLE_DISAPPEAR_STATE_:
		{
			 heroicRoleSkeletonNode->setVisible(true);
			 if(pCommonEffectManager!=NULL)
			 pCommonEffectManager->SetAllBindBoneEffectVisible(true);
			 curRoleState&=~(1<<_ROLE_DISAPPEAR_STATE_);
			 break;
		}
	default: 
		break;
	}
}

 

/*
  to do For Remove Other State 
*/
void   HeroicRole::removeRoleAllState()
{
    if(isRoleInState(_ROLE_DIZZY_STATE_))
	{
	    OnStopRoleResidesAction();
	}
	if(isRoleInState(_ROLE_DISAPPEAR_STATE_))
	{ 
		heroicRoleSkeletonNode->setVisible(true);
		if(pCommonEffectManager!=NULL)
		pCommonEffectManager->SetAllBindBoneEffectVisible(true);
	}
}


/*
更新状态所绑定的动作 主要是为了在受击后播放
*/
void   HeroicRole::excuteRoleStateAction()
{
	if(isRoleInState(_ROLE_DIZZY_STATE_))
	{
	    OnPlayRoleResidesActionByID(XuanYun);    //to do  Modify
	}

	//在此暂时废弃隐身状态
	/*if(isRoleInState(_ROLE_DISAPPEAR_STATE_))
	{
		heroicRoleSkeletonNode->setVisible(false);
	}*/
 
}

  
void   HeroicRole::Destroy()
{
	if(pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->Destroy();
		delete  pCommonEffectManager;
		pCommonEffectManager=NULL;
	} 

	if(pCommonNumberEffectManager!=NULL)
	{
		pCommonNumberEffectManager->Destroy();
		pCommonNumberEffectManager=NULL;
	}
	
	heroicRoleSkeletonNode =NULL;
	heroicEffectNodeUp =NULL;
	heroicEffectNodeDown =NULL;

	m_lSkeNotificationList.clear();

	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	  

}
  

/*
事件通知接口
*/
void   HeroicRole::OnCommandHanlder(int EventTypeID)
{

}

void   HeroicRole::OnCommandHanlder(int EventTypeID,std::string attachParam)
{

}


//更新角色Effect管理器
void    HeroicRole::UpdateEffectManager()
{
	if(pCommonNumberEffectManager!=NULL)
	{
		pCommonNumberEffectManager->Tick();
	}
	 if(pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->Tick();
	} 
       
}

cocos2d::extension::CCSkeletonAnimation* HeroicRole::getRoleSkeletonNode()
{
	return  heroicRoleSkeletonNode;
}
  
void   HeroicRole::runExtAction(cocos2d::CCFiniteTimeAction * pAction) 		  //运行额外动画指令
{
	CCNode::runAction(pAction);
}


bool   HeroicRole::setAnimationTimaScale(float timeScale)				   //设置动画速度系数
{
   if(heroicRoleSkeletonNode!=NULL)
   {
		heroicRoleSkeletonNode->timeScale=timeScale;

		if(heroicEffectNodeUp)
		{
			 heroicEffectNodeUp->timeScale = timeScale;
		}
		if(heroicEffectNodeDown)
		{
			heroicEffectNodeDown->timeScale = timeScale;
		}
		return true;
   }
   return  false;
	 
}
bool   HeroicRole::isCurAnimationLoop()										    //判断当前动画是否循环
{
   if(heroicRoleSkeletonNode!=NULL)
   {
	   return heroicRoleSkeletonNode->states[0]->loop >0 ? true:false;
   }
   return false;

}
std::string  HeroicRole::getCurAnimationName()								    //获得当前骨骼动画名称
{
	if(heroicRoleSkeletonNode!=NULL)
	{
		return  heroicRoleSkeletonNode->states[0]->animation->name;
	}
	return "";
}
 
void   HeroicRole::setAnimationByID(int actionID,bool isLoop)
{   
	if(actionID!=HeroicRole::SiWang)
	hadPlayDeadAnimate=false;
	 
	std::string animationName=getSkillActionNameByID(actionID);
	if(heroicRoleSkeletonNode!=NULL)
	{
		if(getCurAnimationName()==animationName)
			return ;
		if(!animationName.empty())
		{  
			heroicRoleSkeletonNode->setAnimation(animationName.c_str(),isLoop,actionID); 
			if (heroicEffectNodeUp != NULL)
			{
				if (checkHeroicEffect(heroicEffectNodeUp,animationName))
				{
					heroicEffectNodeUp->setVisible(true);
					heroicEffectNodeUp->setAnimation(animationName.c_str(),isLoop); 
				}
				else
					heroicEffectNodeUp->setVisible(false);
			}

			if (heroicEffectNodeDown != NULL)
			{
				if (checkHeroicEffect(heroicEffectNodeDown,animationName))
				{
					heroicEffectNodeDown->setVisible(true);
					heroicEffectNodeDown->setAnimation(animationName.c_str(),isLoop); 
				}
				else
					heroicEffectNodeDown->setVisible(false);
			}
		} 
	}
 }

void   HeroicRole::setAnimationByName(std::string animationName,bool isLoop)    //暂时请不要使用此接口 请优先使用 setAnimationByID
{
	if(heroicRoleSkeletonNode!=NULL)
	{
		if(getCurAnimationName()==animationName)
			return ;
		if(Death_Action_Name!=animationName)
		hadPlayDeadAnimate=false;	 

		if(!animationName.empty())
		{  
			heroicRoleSkeletonNode->setAnimation(animationName.c_str(),isLoop);
			if (heroicEffectNodeUp != NULL)
			{
				heroicEffectNodeUp->setVisible(true);
				if (checkHeroicEffect(heroicEffectNodeUp,animationName))
					heroicEffectNodeUp->setAnimation(animationName.c_str(),isLoop); 
				else
					heroicEffectNodeUp->setVisible(false);
			}

			if (heroicEffectNodeDown != NULL)
			{
				heroicEffectNodeDown->setVisible(true);
				if (checkHeroicEffect(heroicEffectNodeDown,animationName))
					heroicEffectNodeDown->setAnimation(animationName.c_str(),isLoop); 
				else
					heroicEffectNodeDown->setVisible(false);
			}
		} 
	} 
}

bool   HeroicRole::checkHeroicEffect(CCSkeletonAnimation* pEffectNode ,std::string animationName)
{
	AnimationState* pState =  pEffectNode->states[0];
	for(int i=0;i<pState->data->skeletonData->animationCount;i++)
	{
		std::string _name = pState->data->skeletonData->animations[i]->name;
		if (_name == animationName)
			return true;
	}
	return false;
}

int    HeroicRole::getAnimationCount()										  //获得当前骨骼所有动画个数
{
	if(heroicRoleSkeletonNode!=NULL)
	return  heroicRoleSkeletonNode->skeleton->data->animationCount;
	return 0;
}


float HeroicRole::getCurAnimationTime()
{
	if(heroicRoleSkeletonNode!=NULL)
	return heroicRoleSkeletonNode->states[0]->time;
	return 0.0f;
}

float  HeroicRole::getCurAnimationDuration()
{
	if(heroicRoleSkeletonNode!=NULL)
	return  heroicRoleSkeletonNode->states[0]->animation->duration;
	return 0.0f;
}


void   HeroicRole::changeToIdleAnimation(bool isLoop)
{ 
	if(!hadPlayDeadAnimate)
	setAnimationByName(this->getIdleActionName(),isLoop);
}



void   HeroicRole::playAdmissonAnimation() 
{
	setAnimationByID(ChuChang); 
	//注册回调事件
}


void   HeroicRole::roleAdmissonEndCallBack() 
{
    if(!isAdmittanceFinish)
	{
		if(getCurAnimationName()==getSkillActionNameByID(ChuChang)&&getCurAnimationTime()>DEAULTSHOWROLETIME)
		{
			getRoleSkeletonNode()->setVisible(true); 
		}
		if(getCurAnimationName()==getSkillActionNameByID(ChuChang)&&getCurAnimationTime()>=getCurAnimationDuration())
		{
			isAdmittanceFinish=true;
		 	setAnimationByID(DaiJi,true);
			AthleticsSceneManager::get_instance2()->OnCommandHanlder(_TYPED_INPUT_COMMAND_ROLEADMISSION_END_,NULL);
		}
	}

}

/*
重置角色入场之前的状态
*/
void  HeroicRole::reInitRoleAdmissonState()
{ 
	if(pCommonEffectManager)
	{
		pCommonEffectManager->RemoveAllCommonEffect();
	}
 	isInSpecifyAction=false;
	isAdmittanceFinish=false;
	hadPlayDeadAnimate=false;
	setRoleNoneState(); 
}
 

float    HeroicRole::getPositionX()
{
	return CCNode::getPositionX();
}

float    HeroicRole::getPositionY()
{ 
	return CCNode::getPositionY();
}

cocos2d::CCPoint   HeroicRole::getRolePosition()
{   
    return getPosition();
}

void     HeroicRole::setPositionX(float x)
{ 
	CCNode::setPositionX(x);
	/*if(pCommonEffectManager)
	{
		pCommonEffectManager->UpdatePosition(getPosition());
	} */
	  
}

void     HeroicRole::setPositionY(float y)
{  
	//to do
	CCNode::setPositionY(y);
}

void	HeroicRole::setVisible(bool visible)	  //设置结点的可视状态
{
	//to do
	if(visible)
	{
		heroicRoleSkeletonNode->setVisible(false);
	} 
	//if(heroicRoleSkeletonNode)
	//heroicRoleSkeletonNode->setVisible(visible);
	CCNode::setVisible(visible);
}

void	HeroicRole::setSkeletonVisiable(bool isVisiable) 			 //设置骨骼可视状态
{
	if(heroicRoleSkeletonNode)
	heroicRoleSkeletonNode->setVisible(isVisiable);
}



void     HeroicRole::setPosition(const CCPoint& newPosition)
{ 
	CCNode::setPosition(newPosition);
	if(pCommonEffectManager)
	{
		pCommonEffectManager->UpdatePosition(getPosition());
	}  
}

int		HeroicRole::getNodeZOrder()
{
   return  CCNode::getZOrder();
}

void	HeroicRole::setNodeZOrder(int zOrder)
{ 
	if(CCNode::getParent())
	{
		CCNode::getParent()->reorderChild(this,zOrder);
	}
}
 
void	HeroicRole::setFlipX(bool isflip)
{
	if(heroicRoleSkeletonNode!=NULL)
	{
		if(isflip)
		heroicRoleSkeletonNode->setRotationY(180.0f);
		else
		heroicRoleSkeletonNode->setRotationY(0.0f);
	}
}


bool	HeroicRole::isRoleAtInitXPos() 								 //判断角色是否处于初始X坐标位置
{
     if(getPositionX()==roleInitPosition.x)
	 {
	     return true;
	 }
	 return false;

}
bool	HeroicRole::isRoleAtInitYPos() 								 //判断角色是否处于初始Y坐标位置
{
     if(getPositionY()==roleInitPosition.y)
	 {
		 return true;
	 }
	 return false;
}

bool	HeroicRole::isRoleAtTargetXPos() 							 //判断角色是否处于攻击者X坐标位置
{
	if(getPositionX()==roleTargetPosition.x)
	return true;
	return false;
}
bool	HeroicRole::isRoleAtTargetYPos() 							 //判断角色是否处于攻击者Y坐标位置
{ 
	if(getPositionY()==roleTargetPosition.y)
	return true;
	return false;
}


cocos2d::CCPoint  HeroicRole::getInitPosition() 				     //获得角色的初始位置
{
    return  roleInitPosition;
}

float	HeroicRole::getInitXPos() 									 //获得角色X初始位置
{
	return  roleInitPosition.x;
}

float	HeroicRole::getInitYPos() 							         //获得角色Y初始位置
{
    return  roleInitPosition.y;
}
 
void	HeroicRole::forceMoveToTargetPosition()						 //强制设置角色为目标位置
{
	setPositionX(roleTargetPosition.x);
}

void	HeroicRole::forceMoveToInitPosition()						//强制设定角色为初始位置
{
	setPositionX(roleInitPosition.x);	
}

  
void	HeroicRole::setFlipForAction(bool isHomeDirection)			 //定位角色的方向根据 角色的运动轨迹
{
	if(isHomeDirection)
	setFlipX(isRoleFightLeft);
	else
	setFlipX(!isRoleFightLeft);
}

/*
控制角色的运动轨迹,并且设定回调通知接口
*/
VariableSpeedSequenceAction *	HeroicRole::runMoveToAction(bool isToTarget,float durationTime,float fSpeedScale,CallFunctionProtocol * pDelegate,int eventType)
{  
	VariableSpeedSequenceAction *  pVariableAction=NULL;
	if(isToTarget)
	{ 
		pVariableAction=NFC_getTransimissionMoveComAction(durationTime,fSpeedScale,roleTargetPosition,pDelegate,eventType);
	}
	else
	{
		pVariableAction=NFC_getTransimissionMoveComAction(durationTime,fSpeedScale,roleInitPosition,pDelegate,eventType);
	}
	cocos2d::CCNode::runAction(pVariableAction);
	return  pVariableAction;
}

 
void	HeroicRole::setTargetPosition(cocos2d::CCPoint targetPos)
{
	 roleTargetPosition=targetPos;
}
cocos2d::CCPoint    HeroicRole::getTargetPosition()
{
	return roleTargetPosition;
}
 
void	HeroicRole::setInitPosition(cocos2d::CCPoint position)
{
	 roleInitPosition=position;
     setPosition(position);
}

void	HeroicRole::setAnimationStateMixByName(cocos2d::extension::CCSkeletonAnimation* SkeletonNode,cocos2d::extension::CCSkeletonAnimation* EffectSkeletonNodeUp,cocos2d::extension::CCSkeletonAnimation* EffectSkeletonNodeDown)
{ 
	// Begin
	std::string  actionName = pActionData->GetActionNameByActionId(DaiJi);
	std::string  mixActionName="";
	std::string  admittanceName=pActionData->GetActionNameByActionId(ChuChang);
	
	////所有动作和待机融合
	int actionNum = pActionData->GetSize()/sizeof(ActionSetData);
	for(int i=1;i<=actionNum;i++)
	{
		mixActionName = pActionData->GetActionNameByActionId(i);
		if (actionName != mixActionName&&mixActionName!=admittanceName&&!mixActionName.empty())
		{
	         SkeletonNode->setMix(actionName.c_str(),mixActionName.c_str(),Animation_Mix_Time);
			 SkeletonNode->setMix(mixActionName.c_str(),actionName.c_str(),Animation_Mix_Time); 
		} 
	}

	////所有动作和行走融合
	actionName = pActionData->GetActionNameByActionId(Walk);
	for(int i=1;i<=actionNum;i++)
	{
		mixActionName = pActionData->GetActionNameByActionId(i);
		if (actionName != mixActionName&&!mixActionName.empty())
		{
			SkeletonNode->setMix(actionName.c_str(),mixActionName.c_str(),Animation_Mix_Time);
			SkeletonNode->setMix(mixActionName.c_str(),actionName.c_str(),Animation_Mix_Time); 
		}
	}
	//end
	SkeletonNode->setAnimation(pActionData->GetActionNameByActionId(DaiJi).c_str(),false);
	SkeletonNode->setVisible(false);
	SkeletonNode->timeScale = AthleticsSceneManager::get_instance2()->AthleticsSpeed;

	if (EffectSkeletonNodeUp)
	{
		EffectSkeletonNodeUp->setAnimation(pActionData->GetActionNameByActionId(DaiJi).c_str(),true); 
		EffectSkeletonNodeUp->timeScale = AthleticsSceneManager::get_instance2()->AthleticsSpeed;
	}

	if (EffectSkeletonNodeDown)
	{
		EffectSkeletonNodeDown->setAnimation(pActionData->GetActionNameByActionId(DaiJi).c_str(),true); 
		EffectSkeletonNodeDown->timeScale = AthleticsSceneManager::get_instance2()->AthleticsSpeed;
	}
}

bool     HeroicRole::isVisible()
{ 
	//to do
	return CCNode::isVisible();
}

 
//获取配置中帧动画的帧数目 暂时废弃次接口
int   HeroicRole::GetAnimationFrameCount(std::string animationName)
{
	 if(animationName.empty())
	 return 0;
	 AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByName(animationName);
	 if(pAnimationData)
	 {
		 return   pAnimationData->mAnimationFrameCount;
	 }
	 return 0;
}

void   HeroicRole::registerSkeletonEventDelegate(BaseObject *  pActionCompleteDelegate)  //设置骨骼动作完毕回调代理	 
{ 
	if(pActionCompleteDelegate!=NULL)
	{
		m_lSkeNotificationList.insert(pActionCompleteDelegate);
	}
}


void   HeroicRole::unRegisterSkeletonEventDelegate(BaseObject * pActionCompleteDelegate)   //注销骨骼动作完毕回调代理
{  
    std::set<BaseObject *>::iterator event_iter=m_lSkeNotificationList.begin();
	while(event_iter!=m_lSkeNotificationList.end())
	{ 
		if((*event_iter)==pActionCompleteDelegate)
		{
			m_lSkeNotificationList.erase(event_iter);
		    return ;
		}
		++event_iter;
	}
}
 
void  HeroicRole::removeAllSkeletonEventDelegate() 							  //移除所有的骨骼注册代理
{
	 m_lSkeNotificationList.clear();
}



/*
骨骼动画回调事件
*/
void  HeroicRole::skeletonTriggerCallHandler(int eventType,int animationID,cocos2d::extension::PSkeletonCallBack_Node pSkeletonCallBackNode)
{ 
	switch(eventType)
	{
	case _Skeleton_Animation_Change_Event_:
		{  
			//动作播放完毕  关闭瞬时 动作特效
			OnStopUnLoopParticleEffect();
			postAnimateCompNotification(eventType,animationID);
			break;
		}
	case _CompositeEffect_SoundEffect_Type_:
		{
		    EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(pSkeletonCallBackNode->pAttachParam->effectID));  
			break;
		}
	default:
		{
			if(pSkeletonCallBackNode!=NULL)
			{
			  	OnPlayCommonEffect(pSkeletonCallBackNode->pAttachParam->compositeEffectID,eventType,pSkeletonCallBackNode->pAttachParam->effectID);
			}
			break;
		} 
	}
}

//骨骼绑定结点事件通知接口
void   HeroicRole::boneBindEffectCallHandler(int eventType,BoneEfectData & boneEffectData)
{ 
	if(eventType==_BONEEFFECT_CREATE_EFFECT_TYPE_)
	{ 
		  OnPlayCommonEffectWithBone(boneEffectData.compositeEffectID,boneEffectData.boneEffectType,
			   boneEffectData.boneEffectID,boneEffectData.parentBone);
	}
	else if(eventType==_BONEEFFECT_UPDATE_EFFECT_TYPE_)
	{
		if(pCommonEffectManager!=NULL)
		{
		   pCommonEffectManager->UpdateWithBone(boneEffectData.compositeEffectID,boneEffectData.boneEffectID,
			   boneEffectData.boneEffectType,boneEffectData.boneName,boneEffectData.parentBone);
		}
	}
}
 

bool     HeroicRole::hadPlayedDeadAnimation()
{
	return hadPlayDeadAnimate;
}


bool	 HeroicRole::checkCurAnimationWithID(int actionID)
{ 
	if(getCurAnimationName()==getSkillActionNameByID(actionID))
	{
         return true;
	}
	return false;
}
 
/*
判断指定动作是否播放完毕
*/
bool	HeroicRole::isAnimationComplete(int actionID) 			 
{
	if(checkCurAnimationWithID(actionID))
	{ 
	    return  heroicRoleSkeletonNode->isAnimationComplete();
	}
	return false;
}


void  HeroicRole::onPlayDeadAnimation()
{    
	if(pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->RemoveAllLoopCommonEffect();
	}
	heroicRoleSkeletonNode->setVisible(true);
	isInSpecifyAction=false;
	specifyActionID=-1;
	setRoleNoneState();				//清除角色当前所有状态

	if(!hadPlayDeadAnimate)
	{
		hadPlayDeadAnimate=true;
		setAnimationByID(SiWang);	
	}
}

void HeroicRole::onPlayeWinAnimation()
{ 
	hadPlayDeadAnimate=false;
	isInSpecifyAction=false;
	specifyActionID=-1;
	setAnimationByID(ShengLi,true);
}

void   HeroicRole::onPlayBringAnimation()
{
	hadPlayDeadAnimate=false;
	//to do 清除之前的Buffer状态
	setAnimationByID(FuHuo);
}


//启动 角色循环播角色动作    用于角色进入 眩晕状态动作
void   HeroicRole::OnPlayRoleResidesActionByID(int actionID)
{ 
	if(actionID!=-1&&!isInSpecifyAction)
	{
		isInSpecifyAction=true;
		specifyActionID=actionID;
		changeToIdleAnimation();
	}
}

//取消  角色指定循环持续动作
void   HeroicRole::OnStopRoleResidesAction()
{
	isInSpecifyAction=false;
	specifyActionID=-1;
	if(!hadPlayDeadAnimate)
	changeToIdleAnimation();
}


size_t   HeroicRole::GetUnLoopCommonEffectCount()
{
	size_t  allUnLoopEffectCount=0;
	if(pCommonEffectManager!=NULL)
	{
 	  allUnLoopEffectCount+=pCommonEffectManager->GetUnLoopCommonEffectCount();
	}
	if(pCommonNumberEffectManager!=NULL)
	{
	allUnLoopEffectCount+=pCommonNumberEffectManager->GetCurNumberEffectCount();
	}
	return allUnLoopEffectCount;
}

bool    HeroicRole::GetAllNumberEffectTriggered()
{
	if(pCommonNumberEffectManager!=NULL)
	{
		return pCommonNumberEffectManager->HadAllEffectTriggeredNumberUpdate();
	} 
	return true;
}


size_t   HeroicRole::GetLoopCommonEffectCount()
{ 
	if(pCommonEffectManager!=NULL)
	{
	  return pCommonEffectManager->GetLoopCommonEffectCount();
	} 
	return 0;
}


void   HeroicRole::SetRoleEffectAnimationSpeedScale(float speedScale)
{
	if(pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->SetAnimationSpeedScale(speedScale);
	}
	if(pCommonNumberEffectManager!=NULL)
	{
		pCommonNumberEffectManager->SetAnimationSpeedScale(speedScale);
	}
}
 
/*
  之前 播放角色的Buffer接口
*/ 

void 	HeroicRole::OnPlayCommonEffect(int compositeEffectID,int effectType,int effectID)
{
	if(effectID>=0&&pCommonEffectManager!=NULL)
	{
	    pCommonEffectManager->CommonEffectFactory(compositeEffectID,effectType,effectID);
	} 
}

void    HeroicRole::OnPlayCommonEffectWithBone(int compositeEffectID,int effetType,int effectID,cocos2d::extension::Bone * pBindBone)
{
	if(effectID>=0&&pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->CommonEffectFactoryWithBone(compositeEffectID,effetType,effectID,pBindBone);
	} 
}

void    HeroicRole::OnPlayCommonEffect(int commpositeEffectID)
{
	if(commpositeEffectID>=0&&pCommonEffectManager!=NULL)
	{
		pCommonEffectManager->AddCompositeEffect(commpositeEffectID);
	}
} 

void    HeroicRole::OnPlayCommonEffect(CommonEffect * pCommonEffect)
{
	if(pCommonEffect!=NULL&&pCommonEffectManager!=NULL)
	{
	    pCommonEffectManager->AddCommonEffect(pCommonEffect);
	}
}

 
/*
 停止播放角色的Buffer接口
*/
void     HeroicRole::OnStopCommonEffect(int compositeEffectID)
{
	if(pCommonEffectManager)
	{
	   pCommonEffectManager->RemoveCompositeEffectWithID(compositeEffectID);
	} 
}


//@播放数值效果
void	HeroicRole::OnPlayNumberBufferByID(int numberEventType, int numberEffectID,int numberical)
{
    if(pCommonNumberEffectManager)
	{ 
		pCommonNumberEffectManager->AddNumberEffect(this,numberEventType,numberical,numberEffectID);
	} 
}

 

void	HeroicRole::OnStopUnLoopParticleEffect()
{
	if(pCommonEffectManager)
	{
		pCommonEffectManager->RemoveAllUnLoopBindBoneEffect();
	}
}


void	HeroicRole::OnStopAllEffect()
{
	if(heroicEffectNodeUp)
	{
		heroicEffectNodeUp->setVisible(false);
	}
	if(heroicEffectNodeDown)
	{
		heroicEffectNodeDown->setVisible(false);
	}
	if(pCommonEffectManager)
	{
		pCommonEffectManager->RemoveAllCommonEffect();
	}
	if(pCommonNumberEffectManager!=NULL)
	{
		pCommonNumberEffectManager->StopAllActions();
	}
}

void	HeroicRole::OnStopAllSkeletonCallBack()
{
	if(heroicRoleSkeletonNode)
	{
		heroicRoleSkeletonNode->resetAllCallBackNode();
	}
	removeAllSkeletonEventDelegate();
}

 

std::string  HeroicRole::getIdleActionName()
{
	if (pActionData)
	{
		if(!isInSpecifyAction)
		{ 
            return pActionData->GetActionNameByActionId(DaiJi);
		}
		else
		{
			return pActionData->GetActionNameByActionId(specifyActionID);
		}
	}
	return "";
}

 
 
std::string  HeroicRole::getSkillActionNameByID(int ActionID)
{ 
	if (pActionData)
	return pActionData->GetActionNameByActionId(ActionID);
	return "";
}


int		HeroicRole::getSkillActionIDByName(std::string ActionName)
{
	if (pActionData)
	return pActionData->GetActionIDFromActionName(ActionName); 
	return 0;
}
 
  

ActionSetDataManager*  HeroicRole::getRoleActionSetData()
{
	//获得角色ID
	RoleShapeData* pShapeData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(roleShapeID);
	if(pShapeData)
	{
		return pShapeData->mActionSetDataManager;
	}
	return NULL;
}
 
void     HeroicRole::postAnimateCompNotification(int eventType,int attachParam)
{
	std::set<BaseObject *>::iterator event_iter=m_lSkeNotificationList.begin();
	while(event_iter!=m_lSkeNotificationList.end())
	{    
	    if((*event_iter)->IsValid())
		(*(event_iter++))->OnCommandHanlder(eventType,_to_event_param_(attachParam));
	}
}

