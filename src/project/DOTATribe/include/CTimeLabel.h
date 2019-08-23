#ifndef  _DOTATIBE_CTIMELABEL_H
#define  _DOTATIBE_CTIMELABEL_H
#include  <cocos2d.h>
#include "../include/CPublicVarReader.h" 

////////////////////////////////////////////////////////////////
//Name:	 CTimerLabel
//Auchor: 	xiaobo.wu
//Func:	 时间标签
//Maintainer: 	xiaobo.wu
//date:   2014/02/10
////////////////////////////////////////////////////////////////
 
//时间计时回调事件
class  CTimerEventProtocol
{
public:
	enum
	{
		_UNKOWN_TIMER_EVENT_TYPE_,	//未知类型
		_COUNTDONW_END_TYPE_,		//倒计时结束类型
	};
public:
	virtual void  TimerEventHandler(int eventType,std::string attachParam)=0;
};


class   CTimeLabel : public cocos2d::CCLabelTTF 
{ 
public:
	enum
	{
		_UNKONW_TIME_TYPE_,			     //未知时间类型
		_COUNTDOWN_TIME_LONG_TYPE_,		 //倒计时间标签类型  格式%02d:%02d:%02d
		_COUNTDOWN_TIME_SHORT_TYPE_,     //倒计时间标签类型  格式%02d:%02d
		_NORMAL_TIME_TYPE_,			     //正常时间标签类型  格式%02d:%02d:%02d
		_ACTIVITY_TIME_TYPE_,			 //活动截止时间类型  格式%d天%d小时%d分钟
	};
   default_construct_vdestroy(CTimeLabel)
public:
   /*
    注意格式模板  比如: 当前时间:%t
   */
   static CTimeLabel *  CreateWithTimeType(IByte timeType,std::string formatTemplate);
   static CTimeLabel *  CreateWithTimeType(IByte timeType);
   void   StartTimer(int distanceTime); 	//单位秒
   void   StartTimer();
   void   StartActivityMiniteTimer(int minuteDistance);
   void   StopTimer(bool bToInit=true);    
   property_unit_rw(CTimerEventProtocol *,m_pEventDelegate,TimerEventDelegate)
   property_unit_rw(IByte,m_cTimeType,TimeType)
   property_unit_rw(std::string,m_sFormatTemplate,FormatTemplate)
   property_unit_rw(int,m_nDistanceTime,DistanceTime)
   property_unit_rw(std::string,m_nAttachParam,AttachParams)
   property_unit_rw(int,m_nTemplateStrTxtID,TemplateStrTxtID)
protected:
   bool	  InitWithTimeType(IByte timeType,std::string formatTemplate);
   bool   InitWithTimeType(IByte timeType);
   void   UpdateTimer(float time);
   void   FormatTimeData(int seondCount);
   void   SetTimerScheduler(float interTime=1.0f);	
   bool   GetLongFormatFromSecond(int second);
   bool   GetShortFormatFromSecond(int second);
   void   FormatActivityTimeFromSecond(int second);
private:
   int				m_nHoursValue;
   int				m_nMinutesValue;
   int			    m_nSecondsValue;
   long	long		m_lStartMicroSecond;
   long long		m_nTimerMicroSecond;
   int				m_nDurationSecond;
   char				m_timeStr[16];
   //////////////////////////////////////////////////////////////////////////
   int				m_nActivityMinuteDistance;
   int				m_nActivityDaysValue;
   int				m_nActivityHoursValue;
   int				m_nActivityMinutesValue; 
};



#endif