//Name：GuideSystem
//Function：新手引导系统
//Written By：尹强

#ifndef  _DOTA_GUIDESYSTEM_H_
#define  _DOTA_GUIDESYSTEM_H_

#include <include/common/Singleton.h>
#include <string>
#include <list>
using  namespace  cobra_win;

class GuideSystem : public cobra_win::Singleton2<GuideSystem>
{
public:
	enum
	{
//======新手引导========
		_TYPED_GUIDE_NONE_=0,				//无新手引导
		_TYPED_GUIDE_1_,					//模块1
		_TYPED_GUIDE_2_,					//模块2
//======新功能开启========
		_TYPED_NEWFUNC_1_HEROBAR=3,			//模块1
		_TYPED_NEWFUNC_2_AREANA,			//模块2
		_TYPED_NEWFUNC_3_LABOR,				//模块3
		_TYPED_NEWFUNC_4_HEROTECH,			//模块4
		_TYPED_NEWFUNC_5_TOWER,				//模块5
		_TYPED_NEWFUNC_6_TEAMPVE,			//模块6
		_TYPED_NEWFUNC_7_MINERAL,			//模块7
		_TYPED_NEWFUNC_8_GOLDMINE,			//模块8
	};

private:
	int  m_GuideModuleID;  // 新手引导类型
	int  m_GuideStepID; // 当前新手引导索引
	bool m_bIsNeedGuide;	//是否需要引导
	bool m_bIsPaused;			//暂停的标示
	bool m_isRunning;			//新手引导进行中标示
	bool m_isGuideTriggered;
public:
	GuideSystem();
	virtual ~GuideSystem(){};

public:
	/*
		是否需要新手引导
	*/
	bool  IsNeedGuide();
	/*
		得到当前新手引导类型
	*/
	int   GetModuleID();
	/*
		得到当前新手引导步骤
	*/
	int   GetStepID();

	/*
		检查是否暂停
	*/
	bool isPaused() const{
		return m_bIsPaused;
	}
	/*
		检查是否进行中
	*/
	bool isRunning()const{
		return m_isRunning;
	}
public:
	/*
		开启一个新功能的引导
	*/
	void StartGuide4NewFunc(int moduleID);
	/*
		开始指定类型的新手引导
	*/
	void  StartGuide();
	/*
		下一个模块
	*/
	void NextModule();

	/*
		下一步，当在新手引导中切换Procedure时使用
	*/
	void NextBegin();
	void NextDone();

	/*
		下一步
	*/
	void  Next();
	/*
		结束
	*/
	void  Finish();

	/*
		暂停引导
	*/
	void PauseGuide();

	/*
		恢复引导
	*/
	void RestoreGuide();

	/*
		停止引导
	*/
	void StopGuide();

	/*
		告诉服务器下一个模块ID
		isSkip===0:正常   1：跳过
	*/
	void sendToServerFinishOneStep(int moduleID,int stepID,unsigned char isSkip=0);

	/*
		告诉服务器跳过新手引导
	*/
	void ToServerSkipGuide();
	
public:
	/*
		初始化新手引导系统管理器
	*/
	bool  Init();
	/*
		新手引导系统逻辑桢更新
	*/
	void  Tick();
	/*
		销毁新手引导系统管理器
	*/
	void  Destroy();

private:
	/*
		检查特殊步骤
	*/
	void _checkSpecialStep();
	/*
		reset Var
	*/
	void _resetVariable();

public:
	void CheckAndStartGuide(); 
};

#define  GUIDESYSTEM  (GuideSystem::get_instance2())


#endif
