#include <cocos2d.h>
#include "../include/NotifySystem.h"
#include "../include/LoggerSystem.h"
#include "../include/LocalNotificationDataManager.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#include <EAGLView.h>
#include <Foundation/NSFileManager.h>
#include <UIKit/UIKit.h>


void NotifySystem::ClearAllNotification()
{
	// 应用右上数字清零
	[UIApplication sharedApplication].applicationIconBadgeNumber = 0; 
	// 取消所有通知
	[[UIApplication sharedApplication] cancelAllLocalNotifications];
}

void NotifySystem::RegisterAllNotification()
{
	if (LocalNotificationDataManager::get_instance2() == NULL)
		return;
		
	// 得到当前的语言类型
	int type = SysLangDataManager::_TYPED_SYSLANG_CN_;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "SYS", "SysLangType", type);

	NSDate*     date  = [NSDate date];  
	NSCalendar* sys   = [NSCalendar  currentCalendar];  
	NSUInteger  flags = NSYearCalendarUnit|NSMonthCalendarUnit|NSDayCalendarUnit|NSHourCalendarUnit|NSMinuteCalendarUnit|NSSecondCalendarUnit;  
	NSDateComponents* sysComps = [sys components:flags fromDate:date];
	int sysYear = [sysComps year];
	int sysHour = [sysComps hour];
	int sysMinute = [sysComps minute];

	NSCalendar* calendar = [NSCalendar autoupdatingCurrentCalendar];
	unsigned int number = LocalNotificationDataManager::get_instance2()->GetLocalNotifyNumber();
	for (unsigned int i=0; i<number; i++)
	{
		LocalNotificationItemData* pNotifyInfo = LocalNotificationDataManager::get_instance2()->GetLocalNotifyByPos(i);
		assert(pNotifyInfo != NULL);

		if (pNotifyInfo->mNotifyType == _TYPED_NOTIFY_DAILY_)
		{
			UILocalNotification* pNotification = [[UILocalNotification alloc] init];
			if (pNotification != nil)
			{//判断系统是否支持本地通知
				int hour   = pNotifyInfo->mNotifyIntervalHour;
				int minute = pNotifyInfo->mNotifyIntervalMinite;
				int second = 0;

				NSDateComponents* dateComps = [[NSDateComponents alloc] init];
				[dateComps setHour:hour];
				[dateComps setMinute:minute];
				[dateComps setSecond:second];
				pNotification.fireDate       = [calendar dateFromComponents:dateComps];//本次开启立即执行的周期
				pNotification.repeatInterval = kCFCalendarUnitDay;                     //循环周期
				pNotification.timeZone       = [NSTimeZone defaultTimeZone];
				pNotification.soundName      = UILocalNotificationDefaultSoundName;    //本地化通知的声音
				pNotification.alertAction    = NSLocalizedString(@"打开", nil);        //弹出的提示框按钮
				pNotification.applicationIconBadgeNumber = 1;                          //应用程序的右上角小数字
				pNotification.alertBody = [NSString stringWithUTF8String:pNotifyInfo->mHint.c_str()];//弹出的提示信息

				[[UIApplication sharedApplication] scheduleLocalNotification:pNotification];
			}    
		}
		else if (pNotifyInfo->mNotifyType == _TYPED_NOTIFY_TIME_)
		{
			UILocalNotification* pNotification = [[UILocalNotification alloc] init];
			if (pNotification != nil)
			{//判断系统是否支持本地通知
				int addTime = pNotifyInfo->mNotifyIntervalDay*24*60*60+pNotifyInfo->mNotifyIntervalHour*60*60+pNotifyInfo->mNotifyIntervalMinite*60;
				NSDate* now                  = [NSDate new]; 
				pNotification.fireDate       = [now addTimeInterval:addTime];        //本次开启立即执行的周期
				pNotification.timeZone       = [NSTimeZone defaultTimeZone];
				pNotification.soundName      = UILocalNotificationDefaultSoundName;  //本地化通知的声音
				pNotification.alertAction    = nil;
				pNotification.applicationIconBadgeNumber = 1;                        //应用程序的右上角小数字
				pNotification.alertBody = [NSString stringWithUTF8String:pNotifyInfo->mHint.c_str()];//弹出的提示信息
				
				[[UIApplication sharedApplication] scheduleLocalNotification:pNotification];
			}
		}else if(pNotifyInfo->mNotifyType == _TYPED_NOTIFY_FULLTL_){
			UILocalNotification* pNotification = [[UILocalNotification alloc] init];
			if (pNotification != nil)
			{//判断系统是否支持本地通知
				int addTime = ROLEINFODATAHANDLER->GetRestTimeToFullTL();
				if(addTime==0)
					return;
				NSDate* now                  = [NSDate new]; 
				pNotification.fireDate       = [now addTimeInterval:addTime];        //本次开启立即执行的周期
				pNotification.timeZone       = [NSTimeZone defaultTimeZone];
				pNotification.soundName      = UILocalNotificationDefaultSoundName;  //本地化通知的声音
				pNotification.alertAction    = nil;
				pNotification.applicationIconBadgeNumber = 1;                        //应用程序的右上角小数字
				pNotification.alertBody = [NSString stringWithUTF8String:pNotifyInfo->mHint.c_str()];//弹出的提示信息
				
				[[UIApplication sharedApplication] scheduleLocalNotification:pNotification];
			}
		}
	}
}


#endif
