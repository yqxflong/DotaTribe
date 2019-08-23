#ifndef  _DOTATRIBE_TIMESYSTEM_H_
#define  _DOTATRIBE_TIMESYSTEM_H_


#include <include/common/Singleton.h>
#include <cocos2d.h>
#include <list>
#include "../include/ChatPushLogic.h"

using  namespace  cobra_win;

#define   _STANDBJTIME_DISTANCE_UTC_     8			//UTC国际时间距离北京时间时差

// PLIST资源加载耗时统计
#define  _TRACE_LOADING_PLIST_(PLIST) \
{ \
	long long start = TIMESYSTEM->GetCurrentMicroSecond(); \
	\
	cocos2d::CCSpriteFrameCache* pFrameCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache(); \
	pFrameCache->addSpriteFramesWithFile(PLIST); \
	\
	long long end = TIMESYSTEM->GetCurrentMicroSecond();\
	\
	LOGGERSYSTEM->LogTrace("Resource:loading %s, time=%f\n", PLIST, (float)(end-start)/1000000.0f); \
}

// PLIST资源卸载耗时统计
#define  _TRACE_UNLOAD_PLIST_(PLIST) \
{ \
	long long start = TIMESYSTEM->GetCurrentMicroSecond(); \
	\
	cocos2d::CCSpriteFrameCache* pFrameCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache(); \
	pFrameCache->removeSpriteFramesFromFile(PLIST); \
	\
	long long end = TIMESYSTEM->GetCurrentMicroSecond();\
	\
	LOGGERSYSTEM->LogTrace("Resource:unload %s, time=%f\n", PLIST, (float)(end-start)/1000000.0f); \
}

// IMAGE资源卸载耗时统计
#define  _TRACE_UNLOAD_IMAGE_(FILENAME) \
{ \
	long long start = TIMESYSTEM->GetCurrentMicroSecond(); \
	\
	cocos2d::CCTextureCache* pCache = cocos2d::CCTextureCache::sharedTextureCache(); \
	pCache->removeTextureForKey(FILENAME); \
	\
	long long end = TIMESYSTEM->GetCurrentMicroSecond();\
	\
	LOGGERSYSTEM->LogTrace("Resource:unload %s, time=%f\n", FILENAME, (float)(end-start)/1000000.0f); \
}

// IMAGE资源加载耗时统计
#define  _TRACE_LOADING_IMAGE_(IMAGE) \
{ \
	long long start = TIMESYSTEM->GetCurrentMicroSecond(); \
	\
	cocos2d::CCTextureCache* pTextureCache = cocos2d::CCTextureCache::sharedTextureCache(); \
	pTextureCache->addImage(IMAGE); \
	\
	long long end = TIMESYSTEM->GetCurrentMicroSecond();\
	\
	LOGGERSYSTEM->LogTrace("Resource:loading %s, time=%f\n", IMAGE, (float)(end-start)/1000000.0f); \
}

class TimeSystem : public cobra_win::Singleton2<TimeSystem>
{
private:
	float  m_LastTickTime; // 上一帧耗时

	ChatPushLogic * m_pChatPushLogic;

public:
	TimeSystem();
	virtual ~TimeSystem();

public:
	/*
		得到上一桢耗时
	*/
	float GetLastTickTime();

public:
	//@标配
	bool  Init();
	void  Tick(float lastTickTime);
	void  Destroy();

public:
	//@得到当前时间(精确到微秒)
	static long long GetCurrentMicroSecond();
	//@得到当前时间(精确到秒)
	static long long GetCurrentSecond();

public:
	//@得到两个时间相隔的天数
	static int GetIntervalDay(long long start, long long end);

public:
	//@获得当前秒数对应的具体时间 UTC时间
	static struct tm GetNowDateBySecond(long long sec);

	//@根据输入秒数获得标准北京时间 BJTime
	static struct tm GetStandBJDateBySecond(long long sec);
	 
	//@获得当前具体时间对应的秒数
	static long long GetNowSecondByDate(tm time);
	//@得到指定时间对应凌晨时的时间
	static long long GetDateZeroTime(long long sec);

public:
	TimeSystem* GetLuaInstance(){
		return TimeSystem::get_instance2();
	}
};

#define  TIMESYSTEM  (TimeSystem::get_instance2())



//根据秒数得到日，时，分
static std::list<int> TIME_getDayhrmin(int second){
	const int Day = 24,Hours = 60,Minute = 60;
	int z_day = second /( Day * Hours * Minute );   //计算天数
	int z_hr = ( second % ( Day*Hours*Minute )) / ( Hours * Minute );   //计算小时数
	int z_min = ( second % ( Day*Hours*Minute )) % ( Hours * Minute ) / Minute;   //计算分种数

	std::list<int> ll;
	ll.clear();
	ll.push_back(z_day);
	ll.push_back(z_hr);
	ll.push_back(z_min);

	return ll;
}


#endif
