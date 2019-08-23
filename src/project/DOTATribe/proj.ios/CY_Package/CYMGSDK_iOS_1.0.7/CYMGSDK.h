//
//  CYMGSDK.h
//  CyouMobileGameSDK
//
//  Created by Jack Cheng on 14-2-18.
//  Copyright (c) 2014年 cyou-inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol CYMGUserAccountDelegate;
@protocol CYMGGameInfoDataSource;
@protocol CYMGPaymentDelegate;

typedef enum {
    LoginType_Changyou = 0,
    LoginType_QQ,
    LoginType_SinaWeibo,
    LoginType_91,
    LoginType_PP,
    LoginType_TB,
    LoginType_KY,
}LoginType;

@interface CYMGSDK : NSObject

/*
 *	@brief	设置是否开启调试模式
 *  @note   发布时请务必改为NO
 *	@param 	nFlag  YES为开启，NO为关闭
 *  @return    无返回
 */
+ (void)setDebugMode:(BOOL)nFlag;

/**
 *	@brief	进入用户中心
 */
+ (void)enterUserCenter;

/*
 *  客服页面
 */
+ (void)showCallCenter;

/*
 *  SDK版本号
 */
+ (NSString *)SDKVersion;

/*
 *  登录平台，进入登录或者注册界面入口，默认自动登录
 */
+(void)startLogin;

/*
 *  登录平台，进入登录或者注册界面入口
 *  @param autoLogin 是否自动登录
 */
+(void)startLogin:(BOOL)autoLogin;

/*
 *  登录平台，进入登录或者注册界面入口
 *  @param  autoLogin   是否自动登录
 *  @param  delegate    登录回调代理
 */
+(void)startLogin:(BOOL)autoLogin withCallBackDelegate:(id<CYMGUserAccountDelegate>) delegate;

/*
 *  注销
 */
+ (void)startLogout;

/*
 *  注销
 *  @param  delegate    登录回调代理
 */
+ (void)startLogoutWithDelegate:(id<CYMGUserAccountDelegate>) delegate;

/*
 *  设置SDK用户登录回调代理
 *  @param  delegate    登录相关操作回调对象的指针
 */
+ (void)setUserAccountCallBackDelegate:(id<CYMGUserAccountDelegate>) delegate;

/*
 *  开始支付流程，进入充值界面入口
 *  @param  roleID      当角色和元宝由畅游BILLING来管理时,此参数不能为空,否则玩家无法充值
 *  @param  groupID     请将此值设置为分区标识,无分区不需要设置
 */
+ (void)startPaymentWithRoleID:(NSString *)roleID andGroupID:(NSString *)groupID;

/*
 *  开始支付流程，进入充值界面入口
 *  @param  delegate    支付回调代理
 *  @param  roleID      当角色和元宝由畅游BILLING来管理时,此参数不能为空,否则玩家无法充值
 *  @param  groupID     请将此值设置为分区标识,无分区不需要设置
 */
+ (void)startPaymentWithDelegate:(id<CYMGPaymentDelegate>) delegate andRoleID:(NSString *)roleID andGroupID:(NSString *)groupID;

/*
 *  设置SDK支付回调代理
 */
+ (void)setPaymentCallBackDelegate:(id<CYMGPaymentDelegate>) delegate;

/*
 *  目前用于第三方登录方式回调URL处理，支持QQ和Sina微博登录的回调处理。如不接入QQ和Sina微博登录功能，可不调用。
 *  需要在AppDelegate中的两个函数中调用。
 *  eg:
         -(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
         {
         return [CYMGSDK handleURL:url];
         
         }
         
         -(BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url{
         
         return [CYMGSDK handleURL:url];
         }
 */
+ (BOOL)handleURL:(NSURL *)url;

/*
 *  设置SDK获取游戏信息的数据源
 *  @param  datasource  数据源对象的指针
 */
+ (void)setGameInfoDataSource:(id<CYMGGameInfoDataSource>) datasource;

@end

@protocol CYMGUserAccountDelegate <NSObject>

@optional
- (void)userLoginSuccessWithVerifyData:(NSDictionary *)verifyData;

@optional
-(void)userLoginSuccessWithToken:(NSString *)token uid:(NSString *)uid andLoginType:(LoginType)type andVeriryData:(NSDictionary*)verirydata;

@optional
- (void)userLogout;

@end

@protocol CYMGGameInfoDataSource <NSObject>


/*
 *  游戏账号
 */
- (NSString *)userAcount;

/*
 *  游戏角色ID。此ID为billing登录成功返回的userID
 */
- (NSString *)userID;

/*
 *  billing生成的AppKey
 */
- (NSString *)appKey;

/*
 *  billing生成的AppSecrect
 */
- (NSString *)appSecrect;

/*
 *  对应渠道号
 *  eg:
        苹果官方渠道channelID = @"2001"
 */
- (NSString *)channelID;

/*
 *  订单的扩展信息，可记录游戏区服，角色信息之类，会在充值成功后发给游戏Server
 */
- (NSString *)orderPushInfo;

/*
 *  第三方渠道平台生成的AppID
 */
@optional
- (NSString *)thirdPartyChannel_AppID;

/*
 *  第三方渠道生成的AppKey
 */
@optional
- (NSString *)thirdPartyChannel_AppKey;

/*
 *  新浪微博AppKey
 */
@optional
- (NSString *)appKeyForSinaWeibo;

/*
 *  新浪微博重定向地址
 */
@optional
- (NSString *)redirectURIForSinaWeibo;

/*
 *  QQ平台的AppID
 */
@optional
- (NSString *)appIDForQQ;

/*
 *  第三方渠道平台生成的登录验证ID，目前只有快用登录需要此ID，传入在快用平台申请的APPID
 */
@optional
- (NSString *)thirdPartyChannel_loginID;

@end

@protocol CYMGPaymentDelegate <NSObject>

@optional
- (void)paymentSuccessedOrderInfo:(NSDictionary *)orderInfo;

@optional
- (void)paymentFailedOrderInfo:(NSDictionary *)orderInfo;

@end