#include "../include/CTimeLabel.h"
#include "../include/TimeSystem.h"

 
const std::string  LongFormatTemplate	=	 "%02d:%02d:%02d";
const std::string  shortFormatTemplate	=	 "%02d:%02d";
const std::string  longInitTimeStr		=	 "00:00:00";
const std::string  shortInitTimeStr		=	 "00::00";

using namespace cocos2d;


CTimeLabel::CTimeLabel()
{
	m_nHoursValue=0;
	m_nMinutesValue=0;
	m_nSecondsValue=0;
	m_lStartMicroSecond=0l;
	m_nTimerMicroSecond=0l;
	memset(m_timeStr,0,sizeof(m_timeStr));
	m_nAttachParam = "0";
	m_sFormatTemplate="%02d:%02d:%02d";
	m_nTemplateStrTxtID=0;
	m_pEventDelegate = NULL;
}

CTimeLabel::~CTimeLabel()
{  
}

CTimeLabel *  CTimeLabel::CreateWithTimeType(IByte timeType,std::string formatTemplate)
{
	CTimeLabel * pTimeLabel=new CTimeLabel();
	if(pTimeLabel&&pTimeLabel->InitWithTimeType(timeType,formatTemplate))
	{
		pTimeLabel->autorelease();
		return  pTimeLabel;
	}
	CC_SAFE_DELETE(pTimeLabel);
	return  NULL;
}

CTimeLabel *  CTimeLabel::CreateWithTimeType(IByte timeType)
{ 
	CTimeLabel * pTimeLabel=new CTimeLabel();
	if(pTimeLabel&&pTimeLabel->InitWithTimeType(timeType))
	{
		pTimeLabel->autorelease();
		return  pTimeLabel;
	}
	CC_SAFE_DELETE(pTimeLabel);
	return  NULL;
}

void   CTimeLabel::StartTimer(int distanceTime)  //单位秒
{
	m_nDistanceTime=distanceTime;
	SetTimerScheduler();
	UpdateTimer(0.0f);
}

void   CTimeLabel::StartTimer()
{
	//to do 
}

void   CTimeLabel::StartActivityMiniteTimer(int minuteDistance)
{
	StopTimer(false);
    m_nActivityMinuteDistance = minuteDistance;
	SetTimerScheduler();
	UpdateTimer(0.0f);
}

void   CTimeLabel::StopTimer(bool bToInit)
{
	m_lStartMicroSecond=0l;
	unscheduleAllSelectors();
	if(bToInit)
	{  
		switch(m_cTimeType)
		{
		case _COUNTDOWN_TIME_SHORT_TYPE_:
			cocos2d::CCLabelTTF::setString(shortInitTimeStr.c_str());
			break;
		default:
			cocos2d::CCLabelTTF::setString(longInitTimeStr.c_str());
			break;
		}
	} 
}

bool	CTimeLabel::InitWithTimeType(IByte timeType,std::string formatTemplate)
{
	 if(cocos2d::CCLabelTTF::init())
	 {
		 m_cTimeType = timeType;
		 m_sFormatTemplate = formatTemplate;
		 return true;
	 }
	 return false;
}
bool    CTimeLabel::InitWithTimeType(IByte timeType)
{
	if(cocos2d::CCLabelTTF::init())
	{
		m_cTimeType = timeType;
		return true;
	}
	return false;
}
void    CTimeLabel::UpdateTimer(float time)
{   
	m_nTimerMicroSecond = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	m_nDurationSecond = (int)((m_nTimerMicroSecond-m_lStartMicroSecond)/Microsecond_TIME_UNIT);
	FormatTimeData(m_nDurationSecond);
}


void   CTimeLabel::FormatTimeData(int seondCount)
{   
	switch(m_cTimeType)
	{
	case _COUNTDOWN_TIME_LONG_TYPE_:
		{ 
			if(GetLongFormatFromSecond(m_nDistanceTime-seondCount))
			CCLabelTTF::setString(m_timeStr);
			break;
		}
	case _COUNTDOWN_TIME_SHORT_TYPE_:
		{
			if(GetShortFormatFromSecond(m_nDistanceTime-seondCount))
			CCLabelTTF::setString(m_timeStr);
			break;
		}
	case _ACTIVITY_TIME_TYPE_:
		{
			FormatActivityTimeFromSecond(seondCount);
		    break;
		}
	case _NORMAL_TIME_TYPE_:
		{
			//to do
			break;
		}  
	default:
		break;
	}  
}

 
bool  CTimeLabel::GetLongFormatFromSecond(int second)
{  
	if(second<=0)
	{
		sprintf(m_timeStr,LongFormatTemplate.c_str(),0,0,0);
		cocos2d::CCLabelTTF::setString(m_timeStr);
		if(m_pEventDelegate)
		{
			m_pEventDelegate->TimerEventHandler(CTimerEventProtocol::_COUNTDONW_END_TYPE_,m_nAttachParam);
			StopTimer(true);
		}
		return false;
	}
	else
	{
		m_nSecondsValue = second%60;
		m_nMinutesValue = second/60%60;
		m_nHoursValue = second/60/60;
		sprintf(m_timeStr,LongFormatTemplate.c_str(),m_nHoursValue,m_nMinutesValue,m_nSecondsValue);
		return true;
	}
}
 
  
bool   CTimeLabel::GetShortFormatFromSecond(int second)
{  
	if(second<=0)
	{
		sprintf(m_timeStr,shortInitTimeStr.c_str(),0,0);
		cocos2d::CCLabelTTF::setString(m_timeStr);
		if(m_pEventDelegate)
		{
			m_pEventDelegate->TimerEventHandler(CTimerEventProtocol::_COUNTDONW_END_TYPE_,m_nAttachParam);
			StopTimer(true);
		}
		return false;
	}
	else
	{
		m_nSecondsValue = second%60;
		m_nMinutesValue = second/60%60;
		m_nHoursValue = second/60/60;
		sprintf(m_timeStr,shortFormatTemplate.c_str(),m_nMinutesValue + m_nHoursValue*60 ,m_nSecondsValue);
		return true;
	} 
}


void   CTimeLabel::FormatActivityTimeFromSecond(int second)
{  
	int  leftActivityMinuste = m_nActivityMinuteDistance - second/60;
	if(leftActivityMinuste<=0)
	{
		m_nActivityDaysValue = 0;
		m_nActivityHoursValue = 0;
		m_nActivityMinutesValue = 0; 
		char bufferStr[256]={0};
		sprintf(bufferStr,SysLangDataManager::get_instance2()->GetSysLangById(m_nTemplateStrTxtID).c_str(),m_nActivityDaysValue,m_nActivityHoursValue,m_nActivityMinutesValue);
		cocos2d::CCLabelTTF::setString(bufferStr);
		if(m_pEventDelegate)
		{
			m_pEventDelegate->TimerEventHandler(CTimerEventProtocol::_COUNTDONW_END_TYPE_,m_nAttachParam);
			StopTimer(false);
		} 
	}
	else
	{
		int  dayValue = leftActivityMinuste/60/24;
		int  hourValue = leftActivityMinuste/60%24;
		int  minuteValue = leftActivityMinuste%60;
		//分钟转化为 天  小时  分钟
		if(m_nActivityDaysValue!=dayValue || m_nActivityHoursValue!=hourValue ||m_nActivityMinutesValue!=minuteValue)
		{
			m_nActivityDaysValue = dayValue;
			m_nActivityHoursValue = hourValue;
			m_nActivityMinutesValue = minuteValue; 
			//to do 
			char bufferStr[256]={0};
			sprintf(bufferStr,SysLangDataManager::get_instance2()->GetSysLangById(m_nTemplateStrTxtID).c_str(),m_nActivityDaysValue,m_nActivityHoursValue,m_nActivityMinutesValue);
			cocos2d::CCLabelTTF::setString(bufferStr);
		} 
	} 
} 
/*
设置定时间隔
*/
void   CTimeLabel::SetTimerScheduler(float interTime)
{  
	m_lStartMicroSecond = TimeSystem::get_instance2()->GetCurrentMicroSecond(); 
	schedule(schedule_selector(CTimeLabel::UpdateTimer),interTime);
}


