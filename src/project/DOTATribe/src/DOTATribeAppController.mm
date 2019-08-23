#include <cocos2d.h>
#include <Cocos2dEventTyper.h>
#include <CDAudioManager.h>
#include <StoreKit/StoreKit.h>
#include "../include/DOTATribeAppController.h"
#include "../include/DOTATribeViewController.h"
#include "../include/DOTATribeApp.h"
#include "../include/EngineSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DotaGameConfig.h"
#include "../include/LocalPlayerDataManager.h"
//===============Umeng header===================
#include "MobClick.h"
#include <IHelper.h>
#ifdef kSDK_91_ENABEL
//===============91 header===================
#import <NdComPlatform/NDComPlatform.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#import <NdComPlatform/NdCPNotifications.h>
#import <NdComPlatform/NdComPlatformError.h>
#endif

/************************************************************************/
/* IOS系统网络状态切换监听器                                            */
/************************************************************************/
class IOSNetworkListener : public ioshelper::IHelper::INetworkListener
{
public:
	IOSNetworkListener()  {}
	virtual ~IOSNetworkListener()  {}
    
public:
	/************************************************************************/
	/* 系统网路切换事件处理                                                 */
	/************************************************************************/
	virtual  void  OnNetworkChangedHandler()
	{
		cocos2d::CCDirector::sharedDirector()->getSystem()->onNetworkChanged();
	}
	/************************************************************************/
	/*系统网络断开事件处理                                                  */
	/************************************************************************/
	virtual  void  OnNetworkDisConnectHandler()
	{
		cocos2d::CCDirector::sharedDirector()->getSystem()->onNetworkDisConnected();
	}
};

/************************************************************************/
/* IOS系统视频播放状态监听器                                            */
/************************************************************************/
class IOSMoviePlayerListener : public ioshelper::IHelper::IMoviePlayerListener
{
public:
	IOSMoviePlayerListener()  {}
	virtual ~IOSMoviePlayerListener()  {}
    
public:
	/************************************************************************/
	/* 视频播放完毕事件处理                                                 */
	/************************************************************************/
	virtual  void  OnMoviePlayerFinishedHandler()
	{
		;
	}
};

/************************************************************************/
/* IOS系统Web页面封装监听器                                             */
/************************************************************************/
class IOSWebListener : public ioshelper::IHelper::IWebListener
{
public:
	IOSWebListener() {}
	virtual ~IOSWebListener() {}
    
public:
	/************************************************************************/
	/* Web窗口关闭事件处理                                                  */
	/************************************************************************/
	virtual  void  OnWebCloseHandler(int type)
	{
		cocos2d::CCDirector::sharedDirector()->getSystem()->onWebDialogClose(type);
	}
};

/************************************************************************/
/* IOS系统IAP支付购买事件监听器                                         */
/************************************************************************/
class IOSIAPListener : public ioshelper::IHelper::IIAPListener
{
public:
	IOSIAPListener() {}
	virtual ~IOSIAPListener() {}
    
public:
	/************************************************************************/
	/* 验证商品Id失败事件回调处理                                           */
	/************************************************************************/
	virtual  void  OnValidProductFailedHandler(std::string productId)
	{
		cocos2d::CCDirector::sharedDirector()->getPayment()->onPayFailed(productId, "");
        cocos2d::CCDirector::sharedDirector()->getPayment()->end();
	}
	/************************************************************************/
	/* 支付失败事件回调处理                                                 */
	/************************************************************************/
	virtual  void  OnPurchaseFailedHandler(std::string productId)
	{
		cocos2d::CCDirector::sharedDirector()->getPayment()->onPayFailed(productId, "");
		cocos2d::CCDirector::sharedDirector()->getPayment()->end();
	}
	/************************************************************************/
	/* 支付成功事件回调处理                                                 */
	/************************************************************************/
	virtual  void  OnPurchaseSucceedHandler(std::string productId, std::string payUUID, std::string payReceipt)
	{
		// 将购买成功消息传递给上层
		// 上层逻辑一定要将订单保存
		cocos2d::CCDirector::sharedDirector()->getPayment()->onPaySuccess(productId, payUUID, payReceipt);
        
		// 从本地删除
		// ioshelper::GetIOSHelper()->DeletePayment(payUUID);
	}
	/************************************************************************/
	/* 找回已购买的Non-Consume商品事件回调处理                              */
	/************************************************************************/
	virtual  void  OnRestoreSucceedHandler(std::string productId)
	{
		cocos2d::CCDirector::sharedDirector()->getPayment()->onRestoreSuccess(productId);
	}
};

// 系统事件监听器
static IOSNetworkListener*     s_pNetworkListener = NULL;
static IOSWebListener*         s_pWebListener     = NULL;
static IOSIAPListener*         s_pIAPListener     = NULL;
static IOSMoviePlayerListener* s_pMoviePlayerListener = NULL;


@implementation DOTATribeAppController

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{   
	NSLog(@"APP:	start didFinishLaunchingWithOptions");

	//disable lock screen
	[UIApplication sharedApplication].idleTimerDisabled=YES;
	
	// register ad event handler
	NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
    
	//register for Ad
    [center addObserver:self selector:@selector(showAd:) name:_TYPED_COCOS2D_SHOW_AD_EVENT_NAME_ object:nil];
    [center addObserver:self selector:@selector(hideAd:) name:_TYPED_COCOS2D_HIDE_AD_EVENT_NAME_ object:nil];

    // register player behavior event handler
    [center addObserver:self selector:@selector(logPlayerBehavior:) name:_TYPED_COCOS2D_LOG_PLAYER_BEHAVIOR_EVENT_NAME_ object:nil];
    [center addObserver:self selector:@selector(logPlayerBehaviorWithLabel:) name:_TYPED_COCOS2D_LOG_PLAYER_BEHAVIOR_EVENT_NAME_WITH_LABEL_ object:nil];
    [center addObserver:self selector:@selector(beginLogPlayerBehavior:) name:_TYPED_COCOS2D_BEGIN_LOG_PLAYER_BEHAVIOR_EVENT_NAME_ object:nil];
    [center addObserver:self selector:@selector(endLogPlayerBehavior:) name:_TYPED_COCOS2D_END_LOG_PLAYER_BEHAVIOR_EVENT_NAME_ object:nil];
    
    // register show feedback dialog event handler
    [center addObserver:self selector:@selector(showFeedbackDialog:) name:_TYPED_COCOS2D_SHOW_FEEDBACK_DIALOG_EVENT_NAME_ object:nil];

    // register system event handler
    [center addObserver:self selector:@selector(checkNetwork:) name:_TYPED_COCOS2D_CHECK_NETWORK_EVENT_NAME_ object:nil];
    [center addObserver:self selector:@selector(openPengYou:) name:_TYPED_COCOS2D_SHOW_PENGYOU_DIALOG_EVENT_NAME_ object:nil];
    [center addObserver:self selector:@selector(openURL:) name:_TYPED_COCOS2D_OPEN_URL_EVENR_NAME_ object:nil];
	[center addObserver:self selector:@selector(openWebDialog:) name:_TYPED_COCOS2D_OPEN_WEBDIALOG_EVENR_NAME_ object:nil];
	[center addObserver:self selector:@selector(forceUpdate:) name:_TYPED_COCOS2D_FORCE_UPDATE_EVENR_NAME_ object:nil];

    // Add the view controller's view to the window and display.
    m_pWindow = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [m_pWindow bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: YES
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0 ];
    m_pViewController = [[DOTATribeViewController alloc] initWithNibName:nil bundle:nil];
    m_pViewController.wantsFullScreenLayout = YES;
	m_pViewController.view = __glView;
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
		[m_pWindow setRootViewController:m_pViewController];
        [m_pWindow addSubview: m_pViewController.view];
    }
    else
    {
        // use this method on ios6
        [m_pWindow setRootViewController:m_pViewController];
    }
    

    [m_pWindow makeKeyAndVisible];
    
    /*
        =========Register For any platform==========
     */
    [self _registerPlatform];
    
    // 注册系统事件处理
	s_pNetworkListener     = new IOSNetworkListener;
	s_pMoviePlayerListener = new IOSMoviePlayerListener;
	s_pWebListener         = new IOSWebListener;
	s_pIAPListener         = new IOSIAPListener;
	ioshelper::GetIOSHelper()->SetNetworkListener(s_pNetworkListener);
	ioshelper::GetIOSHelper()->SetMoviePlayerListener(s_pMoviePlayerListener);
	ioshelper::GetIOSHelper()->SetWebListener(s_pWebListener);
	ioshelper::GetIOSHelper()->SetPayListener(s_pIAPListener);

	// main logic tick
    cocos2d::CCApplication::sharedApplication()->run();
    
    NSLog(@"APP:	end didFinishLaunchingWithOptions");
    return TRUE;
}

//for 91 photo
- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window{
	return UIInterfaceOrientationMaskAll;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	NSLog(@"APP:	start applicationWillResignActive");
    
    DOTATribeApp::get_instance2()->applicationDidPaused();
    
    NSLog(@"APP:	end applicationWillResignActive");
}

- (void)applicationDidBecomeActive:(UIApplication *)application 
{
    NSLog(@"APP:	start applicationDidBecomeActive");

	DOTATribeApp::get_instance2()->applicationDidResumed();
    
    NSLog(@"APP:	end applicationDidBecomeActive");
}

- (void)applicationDidEnterBackground:(UIApplication *)application 
{
	NSLog(@"APP:	start applicationDidEnterBackground");

    DOTATribeApp::get_instance2()->applicationDidEnterBackground();
    
    NSLog(@"APP:	end applicationDidEnterBackground");
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    NSLog(@"APP:	start applicationWillEnterForeground");
#ifdef kSDK_91_ENABEL
	[[NdComPlatform defaultPlatform] NdPause];
#endif

	[[CDAudioManager sharedManager] setResignBehavior:(kAMRBStop) autoHandle:FALSE];
    DOTATribeApp::get_instance2()->applicationWillEnterForeground();
    
    NSLog(@"APP:	end applicationWillEnterForeground");
}

- (void)applicationWillTerminate:(UIApplication *)application 
{
	NSLog(@"APP:	start applicationWillTerminate");

	DOTATribeApp::get_instance2()->Destroy();

	NSLog(@"APP:	end applicationWillTerminate");
}

#pragma mark -
#pragma mark Memory management
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
     NSLog(@"APP:    start applicationDidReceiveMemoryWarning\n");
     
     NSLog(@"APP:    end applicationDidReceiveMemoryWarning\n");
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
     NSLog(@"APP:    start didRegisterForRemoteNotificationsWithDeviceToken\n");
     
     NSLog(@"APP:    end didRegisterForRemoteNotificationsWithDeviceToken\n");
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
     NSLog(@"APP:    start didFailToRegisterForRemoteNotificationsWithError\n");
     
     NSLog(@"APP:    end didFailToRegisterForRemoteNotificationsWithError\n");   
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo 
{
     NSLog(@"APP:    start didReceiveRemoteNotification\n");
     
     NSLog(@"APP:    end didReceiveRemoteNotification\n"); 
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification 
{
	NSLog(@"APP:    start didReceiveLocalNotification\n");

	[UIApplication sharedApplication].applicationIconBadgeNumber = 0; 
	[[UIApplication sharedApplication] cancelAllLocalNotifications];

    NSLog(@"APP:    end didReceiveLocalNotification\n"); 
}

-(void) closePaymentAlertView
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_APPSTOREWAITWINDOW_);
}

- (void)dealloc 
{
    // 销毁系统事件监听处理
	if (s_pNetworkListener != NULL)
	{
		delete s_pNetworkListener;
		s_pNetworkListener = NULL;
	}
	if (s_pMoviePlayerListener != NULL)
	{
		delete s_pMoviePlayerListener;
		s_pMoviePlayerListener = NULL;
	}
	if (s_pWebListener != NULL)
	{
		delete s_pWebListener;
		s_pWebListener = NULL;
	}
	if (s_pIAPListener != NULL)
	{
		delete s_pIAPListener;
		s_pIAPListener = NULL;
	}

	[m_pWindow release];
    [super dealloc];
}

#pragma mark -
#pragma mark Show AD
-(void) showAd:(NSNotification*)notify
{
    NSLog(@"AD: show\n");

	[m_pViewController showAd];
}

-(void) hideAd:(NSNotification*)notify
{
    NSLog(@"AD: hide\n");

	[m_pViewController hideAd];
}

-(void) logPlayerBehavior:(NSNotification*)notify
{
    NSLog(@"BEHAVIOR:  start log player behavior\n");
	NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
    NSString* eventId   = [dict objectForKey:@"EventId"];
    NSString* labelText = [dict objectForKey:@"Text"];
    
    [MobClick event:eventId label:labelText];

    NSLog(@"BEHAVIOR:  end log player behavior\n");
}

-(void) logPlayerBehaviorWithLabel:(NSNotification*)notify
{
    NSLog(@"BEHAVIOR:  start log player behavior with label\n");
    NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
    NSString* eventId = [dict objectForKey:@"EventId"];
    NSString* text  = [dict objectForKey:@"Text"];
    NSString* label = [dict objectForKey:@"Label"];
    
	NSDictionary *dictionary = [NSDictionary dictionaryWithObjectsAndKeys:label, @"info", nil];

    [MobClick event:eventId attributes:dictionary];

    NSLog(@"BEHAVIOR:  end log player behavior with label\n");
}

-(void) beginLogPlayerBehavior:(NSNotification*)notify
{
    NSLog(@"BEHAVIOR:  start begin log player behavior\n");
	NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
    NSString* eventId   = [dict objectForKey:@"EventId"];
    NSString* labelText = [dict objectForKey:@"Text"];

    [MobClick beginEvent:eventId];
    
    NSLog(@"BEHAVIOR:  end begin log player behavior\n");
}

-(void) endLogPlayerBehavior:(NSNotification*)notify
{
    NSLog(@"BEHAVIOR:  start end log player behavior\n");
	NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
    NSString* eventId   = [dict objectForKey:@"EventId"];
    NSString* labelText = [dict objectForKey:@"Text"];
    
    [MobClick endEvent:eventId];
    
    NSLog(@"BEHAVIOR:  end end log player behavior\n");
}

-(void) showFeedbackDialog:(NSNotification*)notify
{
    NSLog(@"BEHAVIOR:  start show feedback dialog\n");

    NSLog(@"BEHAVIOR:  end show feedback dialog\n");
}

-(void) isPayAvailable:(NSNotification*)notify
{
	NSLog(@"PAYMENT:  start check payment\n");
	
	NSMutableDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
        
    if ([SKPaymentQueue canMakePayments])
    {
    	NSNumber* num = [NSNumber numberWithInt:1];
		[dict setObject:num forKey:@"isAvailable"];
    }

	NSLog(@"PAYMENT:  end check payment\n");
}

-(void) initPaymentEnv:(NSNotification*)notify
{
	NSLog(@"PAYMENT:  start init payment env\n");

	ioshelper::GetIOSHelper()->InitPayEnv();

	NSLog(@"PAYMENT:  end init payment env\n");
}

-(void) destroyPaymentEnv:(NSNotification*)notify
{
	NSLog(@"PAYMENT:  start destroy payment env\n");
	
	ioshelper::GetIOSHelper()->DestroyPayEnv();

	NSLog(@"PAYMENT:  end destroy payment env\n");
}

-(void) isHavePay:(NSNotification*)notify
{
	NSLog(@"PAYMENT:  start have payment\n");
	
	NSMutableDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
        
    NSString* IAPIdString = [dict objectForKey:@"IAPId"];
    if (ioshelper::GetIOSHelper()->IsHasPayment([IAPIdString UTF8String]))
    {
        NSNumber* num = [NSNumber numberWithInt:1];
		[dict setObject:num forKey:@"isHave"];
    }
    
	NSLog(@"PAYMENT:  end have payment\n");
}

-(void) deletePayment:(NSNotification*)notify
{
	NSLog(@"PAYMENT:  start delete payment\n");
	
	NSMutableDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
        
    NSString* text = [dict objectForKey:@"IAPId"];
    ioshelper::GetIOSHelper()->DeletePayment([text UTF8String]);
    
	NSLog(@"PAYMENT:  end delete payment\n");
}

-(void) appStorePay:(NSString*)productId With:(NSString*)productName{
    NSLog(@"PAYMENT:  appStorePay\n");
    
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_APPSTOREWAITWINDOW_);

	ioshelper::GetIOSHelper()->StartPay([productId UTF8String]);
	
    NSLog(@"PAYMENT:  end payment\n");
}

-(void) endPay:(NSNotification*)notify
{
    NSLog(@"PAYMENT:  start end payment\n");

	[self closePaymentAlertView];

    NSLog(@"PAYMENT:  end end payment\n");
}

-(void) checkNetwork:(NSNotification*)notify
{
    NSLog(@"PAYMENT:  start check network\n");

	NSMutableDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
        
    if (ioshelper::GetIOSHelper()->GetNetWorkType() != ioshelper::IHelper::_SYS_NETWORK_UNKOWN_)
    {
    	NSNumber* num = [NSNumber numberWithInt:1];
		[dict setObject:num forKey:@"isAvailable"];
    }

    NSLog(@"PAYMENT:  end check network\n");
}

-(void) openPengYou:(NSNotification*)notify
{
    NSLog(@"PAYMENT:  start open pengyou\n");

    NSLog(@"PAYMENT:  end open pengyou\n");
}

-(void) openURL:(NSNotification*)notify
{
    NSLog(@"PAYMENT:  start open url\n");
    
    NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
    NSString* text = [dict objectForKey:@"url"];  
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:text]];  
    NSLog(@"PAYMENT:  end open url\n");
}

-(void) openWebDialog:(NSNotification*)notify
{
    NSLog(@"PAYMENT:  start open web dialog\n");
    NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
	NSNumber* type = [dict objectForKey:@"type"];
    NSString* text = [dict objectForKey:@"url"];


    NSLog(@"PAYMENT:  end open web dialog\n");
}


-(void) forceUpdate:(NSNotification*)notify
{
    NSLog(@"PAYMENT:  start force update\n");
    
    NSDictionary* dict = [notify userInfo];
    if (dict == nil)
        return;
    
    NSString* text = [dict objectForKey:@"url"];  
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:text]];  
    NSLog(@"PAYMENT:  end force update\n");
}


#pragma mark=====================Register Platform=================
-(void)_registerPlatform{
	[self _registerPlatformNotification];
	if(DOTA_CONFIG_MODE==kMODE_RELEASE_REAL){
		//Register Platform For Umeng
		[self _registerUMPlatform];
	}
	//Register Platform For AppStore
	[self _registerAppStorePlatform];
    //Register Platform For PP
    [self _registerPPPlatform];
    //Register Platform For 91
    [self _register91Platform];
    //Register Platform For TBT
    [self _registerTBTPlatform];


	//Register Share Platform For WeChat
	[self _registerWeChatPlatform];
}

-(void)_registerPlatformNotification{
	NSNotificationCenter* center=[NSNotificationCenter defaultCenter];
	[center addObserver:self selector:@selector(loginPlatform:) name:_TYPED_COCOS2D_PLATFORM_LOGIN_ object:nil];
    [center addObserver:self selector:@selector(logoutPlatform:) name:_TYPED_COCOS2D_PLATFORM_LOGOUT_ object:nil];
	[center addObserver:self selector:@selector(showCenterPlatform:) name:_TYPED_COCOS2D_PLATFORM_SHOWCENTER_ object:nil];
	[center addObserver:self selector:@selector(showSDKToolBar:) name:_TYPED_COCOS2D_PLATFORM_SHOWTOOLBAR_ object:nil];
	[center addObserver:self selector:@selector(payGoodsPlatform:) name:_TYPED_COCOS2D_PLATFORM_PAYGOODS_ object:nil];
	[center addObserver:self selector:@selector(ShareToWeChatPengYouQuan:) name:_TYPED_COCOS2D_PLATFORM_SHARETO_WECHAT_PENGYOUQUAN_ object:nil];
}

-(void)_registerUMPlatform{
	NSLog(@"begin==_registerUMPlatform\n");
#ifdef kSDK_CYOU_ENABEL
		[MobClick startWithAppkey:_TYPED_UM_APP_KEY_ reportPolicy:SEND_ON_EXIT channelId:@"AppStore"];
#endif
#ifdef kSDK_PP_ENABEL
		[MobClick startWithAppkey:_TYPED_UM_APP_KEY_ reportPolicy:SEND_ON_EXIT channelId:@"PP助手"];
#endif
#ifdef kSDK_91_ENABEL
		[MobClick startWithAppkey:_TYPED_UM_APP_KEY_ reportPolicy:SEND_ON_EXIT channelId:@"91助手"];
#endif
#ifdef kSDK_TONGBUTUI_ENABEL
		[MobClick startWithAppkey:_TYPED_UM_APP_KEY_ reportPolicy:SEND_ON_EXIT channelId:@"同步推"];
#endif
	NSLog(@"end==_registerUMPlatform\n");
}

-(void)_registerAppStorePlatform{
	NSLog(@"begin==_registerAppStorePlatform\n");

	NSNotificationCenter* center=[NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(isPayAvailable:) name:_TYPED_COCOS2D_CHECK_PAYMENT_EVENT_NAME_ object:nil];
	[center addObserver:self selector:@selector(initPaymentEnv:) name:_TYPED_COCOS2D_REGISTER_PAYMENT_EVENT_NAME_ object:nil];
	[center addObserver:self selector:@selector(destroyPaymentEnv:) name:_TYPED_COCOS2D_REMOVE_PAYMENT_EVENT_NAME_ object:nil];
    [center addObserver:self selector:@selector(isHavePay:) name:_TYPED_COCOS2D_HAVE_PAYMENT_EVENT_NAME_ object:nil];
	[center addObserver:self selector:@selector(deletePayment:) name:_TYPED_COCOS2D_DELETE_PAYMENT_EVENT_NAME_ object:nil];
	[center addObserver:self selector:@selector(endPay:) name:_TYPED_COCOS2D_END_PAYMENT_EVENT_NAME_ object:nil];

#ifdef kSDK_CYOU_ENABEL
	[CYMGSDK setGameInfoDataSource:self];
    
    if (DOTA_CONFIG_MODE == kMODE_RELEASE_REAL) {
        [CYMGSDK setDebugMode: NO];
    }
    else{
        [CYMGSDK setDebugMode: YES];
    }
    
    //接入MBI
    [Cylib onStart:APPKEY_CY withChannelID:@"Appstore"];
    
    //Talkdata
    //[TalkingData sessionStarted:TALKINGDATA_APPID_CY withChannelId:@"Appstore"];
    //TalkingData
    [TalkingDataAppCpa init:TALKINGDATA_CPA_KEY withChannelId:@"Appstore"];
#ifdef kSDK_CYOU_JBREAK_ENABEL
    NSLog(@"start==[[IPAYiAppPay sharediAppPay] kSDK_CYOU_JBREAK_ENABEL\n");
    [[IPAYiAppPay sharediAppPay] initializeWithAppKey: APPKEY_AIBEI
                                             andAppID: APPID_AIBEI
                                           andWaresID: 1
                                     andUIOrientation: UIInterfaceOrientationPortrait
                                        andCPDelegate: nil];       
    NSLog(@"end==[[IPAYiAppPay sharediAppPay] kSDK_CYOU_JBREAK_ENABEL\n");
#endif
    
#endif

	NSLog(@"end==_registerAppStorePlatform\n");
}

-(void)_register91Platform{
#ifdef kSDK_91_ENABEL
	NSLog(@"begin==_register91Platform\n");
    //==============init 91 SDK
    NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
    cfg.appid =APPID_91;
    cfg.appKey =APPKEY_91;
    cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_STRICT;
    cfg.orientation = UIInterfaceOrientationLandscapeLeft;
    [[NdComPlatform defaultPlatform] NdSetAutoRotation:NO];
    [[NdComPlatform defaultPlatform] NdInit:cfg];
	if(DOTA_CONFIG_MODE!=kMODE_RELEASE_REAL){
		[[NdComPlatform defaultPlatform] NdSetDebugMode:0];
	}
	//===============register Notification
    NSNotificationCenter* center=[NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(_91LoginResultCallBack:) name:(NSString *)kNdCPLoginNotification object:nil];
    [center addObserver:self selector:@selector(_91GameCenterCallBack:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
	[center addObserver:self selector:@selector(_91InitResultCallBack:) name:(NSString*)kNdCPInitDidFinishNotification object:nil];
	[center addObserver:self selector:@selector(_91LeaveComplatformUICallBack:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
	[center addObserver:self selector:@selector(_91UniPayAysnResultCallBack:) name:kNdCPBuyResultNotification object:nil];

	NSLog(@"end==_register91Platform\n");
#endif
}

-(void)_registerPPPlatform
{
#ifdef kSDK_PP_ENABEL
    NSLog(@"begin==_registerPPPlatform\n");
    [[PPAppPlatformKit sharedInstance]setAppId:APPID_PP AppKey:APPKEY_PP];
    [[PPAppPlatformKit sharedInstance]setIsLogOutPushLoginView:NO];
    [[PPAppPlatformKit sharedInstance]setIsLongComet:YES];
    [[PPAppPlatformKit sharedInstance]setIsOpenRecharge:YES];
    [[PPAppPlatformKit sharedInstance]setRechargeAmount:CHANEL_PP_RECHARGEAMOUNT_DEFAULT];
    //    [[PPAppPlatformKit sharedInstance]setCloseRechargeAlertMessage:@""];
    if (DOTA_CONFIG_MODE!=kMODE_RELEASE_REAL)
        [[PPAppPlatformKit sharedInstance]setIsNSlogData:YES];
    else
        [[PPAppPlatformKit sharedInstance]setIsNSlogData:NO];
    

    [[PPUIKit sharedInstance] checkGameUpdate];
    [PPUIKit setIsDeviceOrientationLandscapeLeft:YES];
    [PPUIKit setIsDeviceOrientationLandscapeRight:YES];
    [PPUIKit setIsDeviceOrientationPortrait:YES];
    [PPUIKit setIsDeviceOrientationPortraitUpsideDown:YES];
    
    [[PPAppPlatformKit sharedInstance] setDelegate:self];
    
	NSLog(@"end==_registerPPPlatform\n");
#endif
}

-(void)_registerTBTPlatform{
#ifdef kSDK_TONGBUTUI_ENABEL
	NSLog(@"begin==_registerTBTPlatform\n");

	/* 游戏开发者应在游戏启动时优先对平台进⾏行 */
	[[TBPlatform defaultPlatform] TBInitPlatformWithAppID:APPID_TBT screenOrientation:UIInterfaceOrientationLandscapeLeft isContinueWhenCheckUpdateFailed:NO];
	//===============register Notification
    NSNotificationCenter* center=[NSNotificationCenter defaultCenter];
	[center addObserver:self selector:@selector(_TBTInitDidFinish:) name:kTBInitDidFinishNotification object:nil];
	[center addObserver:self selector:@selector(_TBTloginResult:) name:(NSString *)kTBLoginNotification object:nil];
    [center addObserver:self selector:@selector(_TBTlogoutResult:) name:(NSString*)kTBUserLogoutNotification object:nil];
	NSLog(@"end==_registerTBTPlatform\n");
#endif
}

-(void)_registerWeChatPlatform{
	
}


#pragma mark=====================Notify From GamLogic For Login The PlatForm=================
-(void) loginPlatform:(NSNotification*)notify
{
    NSLog(@"#############loginPlatform#####begin\n");
   	NSDictionary* dict = [notify userInfo];
	int isExpired=[[dict valueForKey:@"isExpired"]intValue];
#ifdef kSDK_CYOU_ENABEL
	if(isExpired)
		[CYMGSDK startLogin:NO withCallBackDelegate:self];
	else
		[CYMGSDK startLogin:YES withCallBackDelegate:self];
#endif
    
#ifdef kSDK_PP_ENABEL
    [[PPAppPlatformKit sharedInstance]showLogin];
#endif
    
#ifdef kSDK_91_ENABEL
	[[NdComPlatform defaultPlatform] NdLogin:0];
#endif

#ifdef kSDK_TONGBUTUI_ENABEL  
	[[TBPlatform defaultPlatform] TBLogin:0];
#endif

    NSLog(@"#############loginPlatform#####end\n");
}

-(void) logoutPlatform:(NSNotification*)notify
{
    NSLog(@"#############logoutPlatform#####begin\n");
    
#ifdef kSDK_CYOU_ENABEL
	[CYMGSDK startLogoutWithDelegate:self];
#endif

#ifdef kSDK_PP_ENABEL
    [[PPAppPlatformKit sharedInstance]PPlogout];
#endif
    
#ifdef kSDK_91_ENABEL  
	[[NdComPlatform defaultPlatform] NdLogout:1];
#endif

#ifdef kSDK_TONGBUTUI_ENABEL  
	[[TBPlatform defaultPlatform] TBLogout:0];
#endif
    
    NSLog(@"#############logoutPlatform#####end\n");
}

-(void)showCenterPlatform:(NSNotification*)notify
{
    NSLog(@"#############showCenterPlatform#####begin\n");
    
#ifdef kSDK_CYOU_ENABEL
	[self logoutPlatform:nil];
#endif

#ifdef kSDK_PP_ENABEL
    [[PPAppPlatformKit sharedInstance]showCenter];
#endif
    
#ifdef kSDK_91_ENABEL
	[[NdComPlatform defaultPlatform] NdEnterPlatform:0];
#endif

#ifdef kSDK_TONGBUTUI_ENABEL
	[[TBPlatform defaultPlatform] TBEnterUserCenter:0];
#endif
    
    NSLog(@"#############showCenterPlatform#####end\n");
}

-(void)showSDKToolBar:(NSNotification*)notify{
	NSLog(@"#############showSDKToolBar#####begin\n");
	NSDictionary* dict = [notify userInfo];
	int status=[[dict valueForKey:@"status"]intValue];
	if(status){
#ifdef kSDK_91_ENABEL  
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtMiddleRight];
#endif
	}else{
#ifdef kSDK_91_ENABEL 
		[[NdComPlatform defaultPlatform] NdHideToolBar];
#endif
	}

	NSLog(@"#############showSDKToolBar#####end\n");
}

-(void)payGoodsPlatform:(NSNotification*)notify{
	NSLog(@"#############payGoodsPlatform#####begin\n");

    NSDictionary* dict = [notify userInfo];
	float price=[[dict valueForKey:@"price"]floatValue];
    NSString* transactionId=[dict valueForKey:@"param0"];
    NSString* productName=[dict valueForKey:@"param1"];
    NSString* roleid=[dict valueForKey:@"param2"];
    int zoneid=[[dict valueForKey:@"param3"]intValue];
	NSString* productID=[dict valueForKey:@"param4"];
	int num=[[dict valueForKey:@"param5"]intValue];


#ifdef kSDK_CYOU_ENABEL
#ifdef kSDK_CYOU_JBREAK_ENABEL
    //如果不是畅游SDK，需要提前保存订单
	std::string pID=[productID cStringUsingEncoding:NSUTF8StringEncoding];
	std::string tranID=[transactionId cStringUsingEncoding:NSUTF8StringEncoding];
	cocos2d::CCDirector::sharedDirector()->getPayment()->insertPayment(pID,tranID);
#else
    [self appStorePay:productID With:productName];
    [Cylib onCharge:price withProductId:productID withProductName:productName withPayId:nil withPayName:@"Appstore"];
#endif
#else
	//如果不是畅游SDK，需要提前保存订单
	std::string pID=[productID cStringUsingEncoding:NSUTF8StringEncoding];
	std::string tranID=[transactionId cStringUsingEncoding:NSUTF8StringEncoding];
	cocos2d::CCDirector::sharedDirector()->getPayment()->insertPayment(pID,tranID);
#endif

#ifdef kSDK_CYOU_JBREAK_ENABEL
    IPAYiAppPayOrder* iAppPayOrder = [[IPAYiAppPayOrder alloc] init];
    iAppPayOrder.exorderno = transactionId;
    int intString = [productID intValue];
    iAppPayOrder.waresid = intString;
    iAppPayOrder.notifyurl = nil;
    int uniprice = price;
    iAppPayOrder.price = uniprice*100;
    iAppPayOrder.cppprivateinfo = nil;
    
    NSString * orderSignature = [[IPAYiAppPay sharediAppPay] getOrderSignature: iAppPayOrder
                                                                     withAppID: APPID_AIBEI
                                                                     andAppKey: APPKEY_AIBEI];
    
    [[IPAYiAppPay sharediAppPay] checkoutWithOrder:iAppPayOrder
                                 andOrderSignature:orderSignature
                                andPaymentDelegate:self];
#endif
#ifdef kSDK_PP_ENABEL
    [[PPAppPlatformKit sharedInstance] exchangeGoods:price BillNo:transactionId BillTitle:productName RoleId:roleid ZoneId:zoneid];
#endif

#ifdef kSDK_91_ENABEL
	NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
	NSString* billnum_91=[NSString stringWithFormat:@"%@_%d",transactionId,APPID_91];
	buyInfo.cooOrderSerial = billnum_91;	//订单号必须唯一，推荐为GUID或UUID
	buyInfo.productId = productID; //自定义的产品ID
	buyInfo.productName =productName ; //产品名称
	buyInfo.productPrice = price; //产品现价，价格大等于0.01,支付价格以此为准
	buyInfo.productOrignalPrice = price; //产品原价，价格同现价保持一致
	buyInfo.productCount = 1; //产品数量
	buyInfo.payDescription =APPKEY_91_CY; //服务器分区，不超过20个字符，只允许英文或数字
	//发起请求并检查返回值。注意！该返回值并不是交易结果！
	int res = [[NdComPlatform defaultPlatform] NdUniPayAsyn: buyInfo];
	if (res < 0)
	{
		//输入参数有错！无法提交购买请求
		NSLog(@"error==payGoodsPlatform\n");
	}
#endif

#ifdef kSDK_TONGBUTUI_ENABEL
	/*
		appkey_cy&goodsRegisterId&payment_key&uid
		appkey_cy畅游分配的appkey
		goodsRegisterId 商品注册ID
		appkey_tbt 同步推分配的key
		uid 购买商品的用户ID 
	*/
	NSString* uid_tbt=[[TBPlatform defaultPlatform] userID]; /*⽤用户ID，唯⼀一标识*/
    NSAssert(uid_tbt!=nil,"ERROR: uid_tbt can not be nil!");
	NSString* des=[NSString stringWithFormat:@"%d_%@",APPID_TBT,uid_tbt];
	[[TBPlatform defaultPlatform] TBUniPayForCoin:transactionId needPayRMB:price payDescription:des delegate:self];
#endif
	NSLog(@"#############payGoodsPlatform#####end\n");
}

-(void)ShareToWeChatPengYouQuan:(NSNotification*)notify{
	NSLog(@"#############ShareToWeChatPengYouQuan#####begin\n");

	NSDictionary* dict = [notify userInfo];
	NSString* title=[dict valueForKey:@"title"];
	NSString* description=[dict valueForKey:@"description"];
	NSString* imgPath=[dict valueForKey:@"imgPath"];

	NSLog(@"#############ShareToWeChatPengYouQuan#####end\n");
}


#ifdef kSDK_CYOU_ENABEL
- (void)userLoginSuccessWithToken:(NSString *)token uid:(NSString *)uid andLoginType:(LoginType)type andVeriryData:(NSDictionary*)verirydata
{
//	NSLog(@"token:%@, uid:%@, type:%u", token, uid, type);
//	//调用与GameServer的用户登录操作。
//	//若token过期，请重新调用登录，并将autoLogin参数设置为NO
//	//[CYMGSDK startLogin:NO withCallBackDelegate:self];
//
//    NSLog(@"=====token1=======%@",token);
//	std::string strToken=[token UTF8String];
//    std::string strUID=[uid UTF8String];
//    char tmp[128]="";
//    sprintf(tmp, "%d",type);
//    std::string strType=tmp;
//    printf("=====token====%s",strToken.c_str());
//	cocos2d::CCDirector::sharedDirector()->getPlatform()->onLoginResultHandler(SDKLoginParam::_platform_cyou_,true,strToken,strUID,strType);
//
//	//记录userid
//	[[NSUserDefaults standardUserDefaults] setObject:uid forKey:@"userid"];
//    
//
//    //MBI
//    [Cylib setAccountId:uid];
//    [Cylib setServer:@"Appstore"];
//    [Cylib setRoleName:@"No Body"];
//    [Cylib setRoleId:uid];
//    [Cylib setLevel:0];
//    [Cylib onLogin];
//    
//    //TalkingData APPCPA
//    [TalkingDataAppCpa onLogin:uid];
}

- (void)userLoginSuccessWithVerifyData:(NSDictionary *)verifyData
{
    NSLog(@"%@",verifyData);
    NSString* data=[verifyData objectForKey:@"data"];
    
	std::string strData=[data UTF8String];
    NSLog(@"==userLoginSuccessWithVerifyData=====2===");
    NSData* data_=[NSData dataWithBytes:strData.c_str() length:strData.length()];
    NSLog(@"==userLoginSuccessWithVerifyData=====3=== nsdata; %@",data_);
    
    NSDictionary* dic=[NSJSONSerialization JSONObjectWithData:data_ options:NSJSONReadingMutableLeaves error:nil];
    NSString* uid=[dic objectForKey:@"uid"];
    NSLog(@"==uid: %@",uid);
    
	//记录userid
	[[NSUserDefaults standardUserDefaults] setObject:uid forKey:@"userid"];
    
    //MBI
    [Cylib setAccountId:uid];
    [Cylib onLogin];
    
    //TalkingData APPCPA
    [TalkingDataAppCpa onLogin:uid];
    
    //enter cpp logic
    cocos2d::CCDirector::sharedDirector()->getPlatform()->onLoginResultHandler(SDKLoginParam::_platform_cyou_,true,strData);
}

- (void)userLogout
{
	// 游戏注销后逻辑
    cocos2d::CCDirector::sharedDirector()->getPlatform()->onLogoutCallBack(SDKLoginParam::_platform_cyou_,true);

    //clear uid
	[[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"userid"];
}

- (NSString *)appKey
{
    return APPKEY_CY;
}

- (NSString *)appSecrect
{
    return APPSECRET_CY;
}

- (NSString *)channelID
{
    return @"2001";
}

- (NSString *)thirdPartyChannel_AppID
{
    return @"";
}

- (NSString *)thirdPartyChannel_AppKey
{
    return @"";
}

- (NSString *)userID
{
    return [[NSUserDefaults standardUserDefaults] objectForKey:@"userid"];
}


/*
 *  新浪微博重定向地址
 */
- (NSString *)redirectURIForSinaWeibo{
    return @"";
}

/*
 *  QQ平台的AppID
 */
- (NSString *)appIDForQQ{
    return @"";
}
#endif

#ifdef kSDK_PP_ENABEL
#pragma mark=====================Call Back From PPSDK=================
/**
 * @brief   余额大于所购买道具
 * @param   INPUT   paramPPPayResultCode       接口返回的结果编码
 * @return  无返回
 */
- (void)ppPayResultCallBack:(PPPayResultCode)paramPPPayResultCode{
	if(PPPayResultCodeSucceed==paramPPPayResultCode)
		cocos2d::CCDirector::sharedDirector()->getPlatform()->onPayResultCallBack(SDKLoginParam::_platform_pp_,0);
}
/**
 * @brief   验证更新成功后
 * @noti    分别在非强制更新点击取消更新和暂无更新时触发回调用于通知弹出登录界面
 * @return  无返回
 */
- (void)ppVerifyingUpdatePassCallBack{
    //nothing
}
/**
 * @brief   登录成功回调【任其一种验证即可】
 * @param   INPUT   paramStrToKenKey       字符串token
 * @return  无返回
 */
- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey{
    [[PPAppPlatformKit sharedInstance] getUserInfoSecurity];
	std::string token=[paramStrToKenKey UTF8String];
	cocos2d::CCDirector::sharedDirector()->getPlatform()->onLoginResultHandler(SDKLoginParam::_platform_pp_,true,token);
}


/**
 * @brief   关闭Web页面后的回调
 * @param   INPUT   paramPPWebViewCode    接口返回的页面编码
 * @return  无返回
 */
- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode{
    //nothing
}
/**
 * @brief   关闭SDK客户端页面后的回调
 * @param   INPUT   paramPPPageCode       接口返回的页面编码
 * @return  无返回
 */
- (void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode{
    //nothing
}
/**
 * @brief   注销后的回调
 * @return  无返回
 */
- (void)ppLogOffCallBack{
    cocos2d::CCDirector::sharedDirector()->getPlatform()->onLogoutCallBack(SDKLoginParam::_platform_pp_,true);
}

#endif

#ifdef kSDK_91_ENABEL
#pragma mark=====================Call Back From 91SDK=================
//91 Init Result CallBack
-(void)_91InitResultCallBack:(NSNotification*)notify{
	;
}

//91 leave platform UI
-(void)_91LeaveComplatformUICallBack:(NSNotification*)notify{
	;
}

//91 loginResult callback
-(void)_91LoginResultCallBack:(NSNotification*)notify
{
    NSLog(@"_91LoginResultCallBack:    start login 91\n");
    
    NSDictionary *dict = [notify userInfo];
    BOOL success = [[dict objectForKey:@"result"] boolValue];
    //
    if([[NdComPlatform defaultPlatform] isLogined] && success){
		//登录成功后处理
		NSString* uin = [[NdComPlatform defaultPlatform] loginUin];
		NSString* sid = [[NdComPlatform defaultPlatform] sessionId];
		std::string s_uin = [uin UTF8String];
		std::string s_sid = [sid UTF8String];
		cocos2d::CCDirector::sharedDirector()->getPlatform()->onLoginResultHandler(SDKLoginParam::_platform_91_,true, s_uin, s_sid);
	}else{
		//登录失败后处理
		int error = [[dict objectForKey:@"error"] intValue];
		NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d", error];
		switch (error) {
			case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
				if (([[NdComPlatform defaultPlatform] getCurrentLoginState] ==ND_LOGIN_STATE_GUEST_LOGIN)) {
					strTip = @"当前仍处于游客登录状态";
				}else {
					//叉掉登陆窗口和注销账户都走这
					strTip = @"用户未登录";
					cocos2d::CCDirector::sharedDirector()->getPlatform()->onLogoutCallBack(SDKLoginParam::_platform_pp_,true);
				}
				break;
			case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
				strTip = @"登录失败, 请检查appId/appKey";
				break;
			case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
				strTip = @"登录失败, 无效的应用ID";
				break;
			case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91:
				strTip = @"有关联的91账号，不能以游客方式登录";
				break;
			default:
				//其他类型的错误提示
				break;
		 }
	}
	NSLog(@"_91LoginResultCallBack:    end login 91\n");
}

//91 gamecenter callback
-(void)_91GameCenterCallBack:(NSNotification*)notify
{
	;
}

//91 payresult callback
-(void)_91UniPayAysnResultCallBack:(NSNotification*)notify{
	NSLog(@"begin==_91UniPayAysnResultCallBack");

	NSDictionary* dic = [notify userInfo];
	BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
	NSString* str = bSuccess ? @"购买成功" : @"购买失败";
	if (!bSuccess) {
		//TODO: 购买失败处理
		NSString* strError = nil;
		int nErrorCode = [[dic objectForKey:@"error"] intValue];
		switch (nErrorCode) {
			case ND_COM_PLATFORM_ERROR_USER_CANCEL:
				strError = @"用户取消操作";
				break;
			case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
				strError = @"网络连接错误";
				break;
			case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
				strError = @"服务端处理失败";
				break;
			case ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED:
				//!!!: 异步支付，用户进入充值界面了
				strError = @"支付订单已提交";
				break;
			default:
				strError = @"购买过程发生错误";
				break;
		}
		str = [str stringByAppendingFormat:@"\n%@", strError];
	}
	else {
		//购买成功处理
		cocos2d::CCDirector::sharedDirector()->getPlatform()->onPayResultCallBack(SDKLoginParam::_platform_91_,0);
	}
	//本次购买的请求参数
	NdBuyInfo* buyInfo = (NdBuyInfo*)[dic objectForKey:@"buyInfo"];
	str = [str stringByAppendingFormat:@"\n<productId = %@, productCount = %d, cooOrderSerial= %@>",buyInfo.productId, buyInfo.productCount, buyInfo.cooOrderSerial];
	
	NSLog(@"end==_91UniPayAysnResultCallBack: %@", str);
}
#endif

#ifdef kSDK_TONGBUTUI_ENABEL
#pragma mark=====================Call Back From TBTSDK=================
//TBT Init Result CallBack
-(void)_TBTInitDidFinish:(NSNotification*)notify{
	;
}

//TBT Login Result CallBack
-(void)_TBTloginResult:(NSNotification*)notify{
	if([[TBPlatform defaultPlatform] TBIsLogined]) {
		//登录成功后处理
        TBPlatformUserInfo *userInfo=[[TBPlatform defaultPlatform]TBGetMyInfo];
		NSString* s_uin=[userInfo userID]; /*⽤用户ID，唯⼀一标识*/
		NSString* s_sid=[userInfo sessionID]; /*⽤用户会话ID*/
        std::string s_uin_utf8=[s_uin UTF8String];
        std::string s_sid_utf8=[s_sid UTF8String];
		cocos2d::CCDirector::sharedDirector()->getPlatform()->onLoginResultHandler(SDKLoginParam::_platform_tongbutui_,true, s_uin_utf8, s_sid_utf8);
	}else{
        NSLog(@"Error==_TBTloginResult: No");
	}
}

//TBT Logout Result CallBack
-(void)_TBTlogoutResult:(NSNotification*)notify{
    //注销账户后的处理
    cocos2d::CCDirector::sharedDirector()->getPlatform()->onLogoutCallBack(SDKLoginParam::_platform_tongbutui_,true);
}

/**
* @brief 使⽤用推币直接购买商品成功
* @param order 订单号
*/
- (void)TBBuyGoodsDidSuccessWithOrder:(NSString*)order{
	cocos2d::CCDirector::sharedDirector()->getPlatform()->onPayResultCallBack(SDKLoginParam::_platform_tongbutui_,0);
}
/**
* @brief 使⽤用推币直接购买商品失败
* @param order 订单号
* @param errorType 错误类型，⻅见TB_BUYGOODS_ERROR
*/
- (void)TBBuyGoodsDidFailedWithOrder:(NSString *)order resultCode:(TB_BUYGOODS_ERROR)errorType{
	;
}
/**
* @brief 推币余额不⾜足，进⼊入充值⻚页⾯面（开发者需要⼿手动查询订单以获
取充值购买结果）
*
* @param order 订单号
*/
- (void)TBBuyGoodsDidStartRechargeWithOrder:(NSString*)order{
	;
}
/**
* @brief 跳提⽰示框时，⽤户取消
*
* @param order 订单号
*/
- (void)TBBuyGoodsDidCancelByUser:(NSString *)order{
	;
}
#endif

#ifdef kSDK_CYOU_JBREAK_ENABEL

#pragma mark - IPAYiAppPayPaymentDelegate

- (void)paymentStatusCode: (IPAYiAppPayPaymentStatusCodeType)statusCode
                signature: (NSString *)signature
               resultInfo: (NSString *)resultInfo
{
    if(statusCode == IPAY_PAYMENT_SUCCESS)
    {
        cocos2d::CCDirector::sharedDirector()->getPlatform()->onPayResultCallBack(SDKLoginParam::_platform_cyou_jbreak_,0);
    }
    else if(statusCode == IPAY_PAYMENT_CANCELED)
    {
        ;
    }
    else
    {
        ;
    }
}


#endif
@end
