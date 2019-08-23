//Name：BaseObject
//Function：战斗逻辑对象
//Author:	Johny

#ifndef   _DOTATRIBE_BASEOBJECT_H
#define   _DOTATRIBE_BASEOBJECT_H

#include  <list>
#include  <string>

class  BaseObject
{
public:
	//@对象类型
    enum
	{
		 UNKOWN_OBJECT_TYPE,									
		 HEROICROLE_OBJECT_TYPE,							//英雄对象类型
		 COMMONSKILLITEMPROCEDURE_OBJECT_TYPE,				//公共技能流程对象类型
		 COMMONSKILLACTIONPROCEDURE_OBJECT_TYPE,			//公共技能动画流程对象类型
		 COMMON_UNSKILLPROCEDUER_OBJECT_TYPE,				//公共非技能流程对象类型
		 SKILLATTACHLOGIC_OBJECT_TYPE,						//技能附加逻辑对象类型
		 COMMON_SKILLEFFECT_OBJECT_TYPE,					//公共技能特效动画对象类型		
		 COMMON_NUMBEREFFECT_OBJECT_TYPE,					//公共数值特效动画对象类型
		 ART_LABEL_OBJECT_TYPE,								//艺术字标签对象类型
		 LISTEN_PROXY_OBJECT_TYPE,							//监听代理对象类型
	};

public:
	BaseObject();
	virtual ~BaseObject();
	//@标配
	virtual   void Init(){};
	virtual   void Tick();
	virtual   void Destroy()=0;

	//@设置战斗速度
	virtual   void SetSpeedScale(float speedScale);

	//@命令解析处理
	virtual   void OnCommandHanlder(int EventTypeID){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2,std::string attachParam3){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2,std::string attachParam3,std::string attachParam4){};
public:
	//@对象类型
	void   SetObjectType(int ObjectType);
	int    GetObjectType();
	//@是否有效
	bool   IsValid();
	void   SetIsValid(bool isValid);
	//@该对象的ID
    void   SetSubObjectID(int subObjectId);
	int    GetSubObjectID();
protected:
	int    objectType_;                        //对象类型
	int    objectSubID_;					   //对象子对象ID
	long long    m_LogicTickCount_;			   //对象的逻辑帧
	bool   isValid_;						   //对象是否合法
};

#endif