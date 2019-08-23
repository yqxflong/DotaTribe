#ifndef   _SPINECALLBACKEVENT_H_
#define   _SPINECALLBACKEVENT_H_
/////////////////////////////////////////////////
//title:  骨骼回调系统接口 
//author:  xiaobo.wu
//version:1.0
//description:   支持骨骼动作定时回调 
//date:   2013/08/08
//version:2.0
//description:   支持骨骼绑点回调 
//date:   2013/09/19
///////////////////////////////////////////////// 

#include "spine.h"
#include "cocos2d.h"

namespace cocos2d { namespace extension {

//extern struct BoneEfectData;

#define   FOR_EACH_CALL_BEGIN(count)     for(size_t  index=0;index<count;index++) {
#define   FOR_EACH_CALL_END              }
#define   PIX2							(2*3.1415926535897932385)
#define   PI						     3.1415926535897932385


//SpineCall专用事件通知类型 
#define    _Skeleton_Animation_Change_Event_    0x10001     //动作切换通知

#define   _DEFULAT_INIT_BONE_EFFECT_SIZE		5			//初始创建骨骼挂点数				
#define   _DEFULAT_INIT_SKELETON_CALL_SIZE		7			//初始创建骨骼事件通知数
 
//骨骼挂点特效事件通知
enum
{
	_BONEEFFECT_UNKONW_TYPE_,			  //未知指令
	_BONEEFFECT_CREATE_EFFECT_TYPE_,	  //创建指令
	_BONEEFFECT_UPDATE_EFFECT_TYPE_,	  //更新指令
}; 

typedef struct  boneeffectdata_tag
{
	bool   isValid;			  //是否回收利用
	bool   isCreate;		  //是否创建完成
	bool   isLoopBoneEffect;  //是否持续特效
	bool   isFollowBoneEffect;//是否伴随
	int    boneEffectID;      //骨骼特效ID
	int    boneEffectType;	  //特效类型
	int    compositeEffectID; //母特效ID
	std::string  boneName;    //绑定骨骼名称
	Bone * parentBone;        //骨骼
public:
	boneeffectdata_tag()
	{
		resetData(); 
	}
	void  resetData()
	{
		isValid=false;
		isCreate=false;
		boneEffectID=0;
		boneName="";
		boneEffectType=0;
		parentBone=NULL;
		isLoopBoneEffect=false;
		isFollowBoneEffect=true;
	}
}BoneEfectData,*PBoneEffectData;



typedef struct attachparam_tag		//骨骼回调附加参数
{
	bool isBoneBindEffect;			//是否为骨骼绑点特效
	bool isFollowBoneEffect;		//是否为跟随骨骼特效(只对骨骼绑点特效作用)
	bool isDurationBoneEffect;      //是否为持续特效(只对骨骼绑点特效作用)
	int  effectID;					//附加特效ID
	int  compositeEffectID;			//母特效ID
	std::string boneName;           //绑定的骨骼名称
public:
	attachparam_tag()
	{  resetData(); }
	void  resetData()				//重置数据
	{
		effectID=0;
		compositeEffectID=0;
		isBoneBindEffect=false;
		isFollowBoneEffect=false;
		isDurationBoneEffect=false;
		boneName="";
	}
}AttachParam,*PAttachParam;

typedef struct   skeletoncallback_node_tag
{
	bool   isValid;					   //是否已经回收
	bool   isTrigger;				   //是否已经触发回调
	int    eventType;				   //事件类型
	float  triggerTime;				   //回调时间点 单位S
	PAttachParam  pAttachParam;		   //附加参数

public:
	skeletoncallback_node_tag()
	{
		isValid=false;
		isTrigger=false;
		eventType=0;
		triggerTime=0.0f;
		pAttachParam=new AttachParam();
		assert(pAttachParam!=NULL);
	}
	~skeletoncallback_node_tag()
	{
		destroy();
	}
	void  resetData()
	{
		isValid=false;
		isTrigger=false;
		eventType=0;
		triggerTime=0.0f;
		if(pAttachParam!=NULL)
		pAttachParam->resetData();
	}
	void destroy()
	{
		if(pAttachParam!=NULL)
		{
			delete pAttachParam;
			pAttachParam=NULL;
		}
	}

}SkeletonCallBack_Node,*PSkeletonCallBack_Node;


/*
  加载动作回调配置项接口
  param1: skeletonUUID  骨骼的UID
  param2: animationID   动作配置表索引ID
  param3: pcallBackVec  回调点数组	
*/
typedef void (*PLoadSkeletonCallBackHandler)(std::string skeletonUUID,int animationID,std::vector<PSkeletonCallBack_Node> * pcallBackVec);

/*
  注册骨骼配置加载接口
*/
void   RegisterSkeletonCallBackEventHandler(PLoadSkeletonCallBackHandler handler);

/*
  检验骨骼配置加载接口是否合法
*/
bool   CheckSkeletonCallBackHandlerValid();

/*
内部使用 骨骼动作配置加载接口
*/
void   OnSkeletonCallBackEventHandler(std::string skeletonUUID,int animationID,std::vector<PSkeletonCallBack_Node> * pcallBackVec);

/*
  骨骼事件通知回调协议
*/
class  SkeletonCallBackProtocol
{
public:
  /*
    骨骼动作定时回调通知接口
    param1: 事件通知类型
	param2: 动作配置表索引ID
	param3: 回调数据结点
  */
  virtual  void   skeletonTriggerCallHandler(int eventType,int animationID,PSkeletonCallBack_Node  pSkeletonCallBackNode)=0;

  /*
    骨骼绑点通知接口
	param1: 事件通知类型
	param2: 骨骼特效ID
	param3: 绑定的骨骼结点
  */
  virtual  void   boneBindEffectCallHandler(int eventType,BoneEfectData & boneEffectData)=0;

   
};

}}  


#endif


 
 
