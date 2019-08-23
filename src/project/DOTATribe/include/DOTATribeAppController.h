#ifndef  _DOTATRIBE_DOTATRIBEAPPCONTROLLER_H_
#define  _DOTATRIBE_DOTATRIBEAPPCONTROLLER_H_

//===========================APP KEY Config=========================
//umeng
#define  _TYPED_UM_APP_KEY_  @"5277666456240b69020a4b9b"
//wechat
#define  _TYPED_WECHAT_APPID_ @"gh_442675135d7d"
//===========================================================================
#ifdef kSDK_CYOU_ENABEL
#define APPKEY_CY   @"1378783413547"
#define APPSECRET_CY	@"07b5d0a2a20f4c5aa1854ae6e4b7b097"
#define TALKINGDATA_ANALZ_ID     @"2D0175C62F6727C1664731EE3EA28DFC"
#define TALKINGDATA_CPA_KEY      @"a7d1c845e0a04f2095afe857f360b9a1"
#endif
//
#ifdef kSDK_PP_ENABEL
#define APPID_PP    2077
#define APPKEY_PP   @"03a86c1c865e298f2ea0ca50fc3e6362"
#endif
//
#ifdef kSDK_91_ENABEL
#define APPID_91		111284
#define APPKEY_91		@"5e4db4643be747e818375f1c1f0ff5ac179a08af3c9cb082"
#define APPKEY_91_CY	@"1378781747452"		//billing的AppKey
#endif
//
#ifdef kSDK_TONGBUTUI_ENABEL
#define APPID_TBT		140131
#define APPKEY_TBT		@"5Eby#2Livk9HfUr5OEyo#1iXvkSHerB5"
#define APPKEY_TBT_CY	@"1378781747452"		//billing的AppKey
#endif

#ifdef kSDK_CYOU_JBREAK_ENABEL
#define APPID_AIBEI		@"3000468653"
#define APPKEY_AIBEI		@"RTc5NDRFQzZCNDIxMTM1REU4NTlEOEY2NUI1OTk5QjRFQjZFNjlGN01UTXlNVGM1T0RNM05EVTBNVGt5T0RnM05ERXJNVFExTWpNNU9EQTFOVFEwT1RZMU1qUTNPVEkwT1RZMk5qZzNOREV5T1RVME16QXlNRGt6"
#define APPKEY_TBT_CY	@"1378781747452"		//billing的AppKey
#endif

//###################################################################################
#import <UIKit/UIKit.h>
#import <EAGLView.h>

#ifdef kSDK_CYOU_ENABEL
#import "CYMGSDK.h"
#import "Cylib.h"
//#import "TalkingData.h"
#import "TalkingDataAppCpa.h"
#endif
#ifdef kSDK_PP_ENABEL
#import <PPAppPlatformKit/PPAppPlatformKit.h>
#endif
#ifdef kSDK_TONGBUTUI_ENABEL
#import <TBPlatform/TBPlatform.h>
#endif
#ifdef kSDK_CYOU_JBREAK_ENABEL
#import "IPAYiAppPay.h"
static NSString * const IPAY_CP_APPKEY = @"NEVDMkQ3OTRBMTY4ODIzMzkwRUI5MkMzQTQyRTU4NTYwMzJDMjU2OE1UY3lNalkxTWprd01UYzVPVE14TkRNek9Ea3JNVEF5TURjeU1qZzRNVEkzTVRZME9EYzBNalV5TmpnMk1UZ3dOVEV3TmpnME5UVTFNRGt4";

static NSString * const IPAY_CP_APPID = @"10000100000040100001";
#endif

@class DOTATribeViewController;
@interface DOTATribeAppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate, UIApplicationDelegate
#ifdef kSDK_CYOU_ENABEL
	,CYMGUserAccountDelegate
	,CYMGGameInfoDataSource
#endif
#ifdef kSDK_PP_ENABEL
    ,PPAppPlatformKitDelegate
#endif
#ifdef kSDK_TONGBUTUI_ENABEL
	,TBBuyGoodsProtocol
#endif
#ifdef kSDK_CYOU_JBREAK_ENABEL
    ,IPAYiAppPayPaymentDelegate
#endif
    >
{
    UIWindow*    m_pWindow;
    DOTATribeViewController* m_pViewController;
}

-(void) showAd:(NSNotification*)notify;
-(void) hideAd:(NSNotification*)notify;

-(void) logPlayerBehavior:(NSNotification*)notify;
-(void) logPlayerBehaviorWithLabel:(NSNotification*)notify;
-(void) beginLogPlayerBehavior:(NSNotification*)notify;
-(void) endLogPlayerBehavior:(NSNotification*)notify;

-(void) showFeedbackDialog:(NSNotification*)notify;

-(void) isPayAvailable:(NSNotification*)notify;
-(void) initPaymentEnv:(NSNotification*)notify;
-(void) destroyPaymentEnv:(NSNotification*)notify;
-(void) isHavePay:(NSNotification*)notify;
-(void) deletePayment:(NSNotification*)notify;
-(void) appStorePay:(NSString*)productId With:(NSString*)productName;
-(void) endPay:(NSNotification*)notify;
-(void) serversureorder:(NSNotification*)notify;

-(void) checkNetwork:(NSNotification*)notify;
-(void) openPengYou:(NSNotification*)notify;
-(void) openURL:(NSNotification*)notify;
-(void) openWebDialog:(NSNotification*)notify;
-(void) forceUpdate:(NSNotification*)notify;

-(void) closePaymentAlertView;

-(void)_registerPlatform;
-(void)_registerPlatformNotification;
-(void)_registerUMPlatform;
-(void)_registerCYMBIPlatform;
-(void)_registerAppStorePlatform;
-(void)_registerPPPlatform;
-(void)_register91Platform;
-(void)_registerTBTPlatform;
-(void)_registerWeChatPlatform;

-(void) loginPlatform:(NSNotification*)notify;
-(void) logoutPlatform:(NSNotification*)notify;
-(void)showCenterPlatform:(NSNotification*)notify;
-(void)showSDKToolBar:(NSNotification*)notify;
-(void)payGoodsPlatform:(NSNotification*)notify;
-(void)ShareToWeChatPengYouQuan:(NSNotification*)notify;

#ifdef kSDK_CYOU_ENABEL
//===============================CY  SDK============================================
- (void)userLoginSuccessWithToken:(NSString *)token uid:(NSString *)uid andLoginType:(LoginType)type;

- (void)userLoginSuccessWithVerifyData:(NSDictionary *)verifyData;

#ifdef kSDK_CYOU_JBREAK_ENABEL


#endif

- (void)userLogout;

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
 *  第三方渠道平台生成的AppID
 */
- (NSString *)thirdPartyChannel_AppID;

/*
 *  第三方渠道生成的AppKey
 */
- (NSString *)thirdPartyChannel_AppKey;

/*
 *  新浪微博AppKey
 *===========Do not implement it, or will delay about 10 seconds==========
- (NSString *)appKeyForSinaWeibo;
*/

/*
 *  新浪微博重定向地址
 */
- (NSString *)redirectURIForSinaWeibo;

/*
 *  QQ平台的AppID
 */
- (NSString *)appIDForQQ;

#endif

#ifdef kSDK_PP_ENABEL
//===============================PP SDK============================================
/**
 * @brief   浣欓澶т簬鎵€璐拱閬撳叿
 * @param   INPUT   paramPPPayResultCode       鎺ュ彛杩斿洖鐨勭粨鏋滅紪鐮? * @return  鏃犺繑鍥? */
- (void)ppPayResultCallBack:(PPPayResultCode)paramPPPayResultCode;
/**
 * @brief   楠岃瘉鏇存柊鎴愬姛鍚? * @noti    鍒嗗埆鍦ㄩ潪寮哄埗鏇存柊鐐瑰嚮鍙栨秷鏇存柊鍜屾殏鏃犳洿鏂版椂瑙﹀彂鍥炶皟鐢ㄤ簬閫氱煡寮瑰嚭鐧诲綍鐣岄潰
 * @return  鏃犺繑鍥? */
- (void)ppVerifyingUpdatePassCallBack;
/**
 * @brief   鐧诲綍鎴愬姛鍥炶皟銆愪换鍏朵竴绉嶉獙璇佸嵆鍙€? * @param   INPUT   paramStrToKenKey       瀛楃涓瞭oken
 * @return  鏃犺繑鍥? */
- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey;
/**
 * @brief   鐧诲綍鎴愬姛鍥炶皟銆愪换鍏朵竴绉嶉獙璇佸嵆鍙€? * @param   INPUT   paramHexToKen          2杩涘埗token
 * @return  鏃犺繑鍥? */
- (void)ppLoginHexCallBack:(char *)paramHexToKen;

/**
 * @brief   鍏抽棴Web椤甸潰鍚庣殑鍥炶皟
 * @param   INPUT   paramPPWebViewCode    鎺ュ彛杩斿洖鐨勯〉闈㈢紪鐮? * @return  鏃犺繑鍥? */
- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode;
/**
 * @brief   鍏抽棴SDK瀹㈡埛绔〉闈㈠悗鐨勫洖璋? * @param   INPUT   paramPPPageCode       鎺ュ彛杩斿洖鐨勯〉闈㈢紪鐮? * @return  鏃犺繑鍥? */
- (void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode;
/**
 * @brief   娉ㄩ攢鍚庣殑鍥炶皟
 * @return  鏃犺繑鍥? */
- (void)ppLogOffCallBack;
#endif

#ifdef kSDK_91_ENABEL
//===============================91 SDK============================================
//91 Init Result CallBack
-(void)_91InitResultCallBack:(NSNotification*)notify;

//91 leave platform UI
-(void)_91LeaveComplatformUICallBack:(NSNotification*)notify;

//91 loginResult callback
-(void)_91LoginResultCallBack:(NSNotification*)notify;

//91 gamecenter callback
-(void)_91GameCenterCallBack:(NSNotification*)notify;

//91 payresult callback
-(void)_91UniPayAysnResultCallBack:(NSNotification*)notify;

#endif

#ifdef kSDK_TONGBUTUI_ENABEL
//===============================TBT SDK============================================
//TBT Init Result CallBack
-(void)_TBTInitDidFinish:(NSNotification*)notify;

//TBT Init Result CallBack
-(void)_TBTloginResult:(NSNotification*)notify;

/**
* @brief 使⽤用推币直接购买商品成功
* @param order 订单号
*/
- (void)TBBuyGoodsDidSuccessWithOrder:(NSString*)order;
/**
* @brief 使⽤用推币直接购买商品失败
* @param order 订单号
* @param errorType 错误类型，⻅见TB_BUYGOODS_ERROR
*/
- (void)TBBuyGoodsDidFailedWithOrder:(NSString *)order resultCode:
(TB_BUYGOODS_ERROR)errorType;
/**
* @brief 推币余额不⾜足，进⼊入充值⻚页⾯面（开发者需要⼿手动查询订单以获
取充值购买结果）
*
* @param order 订单号
*/
- (void)TBBuyGoodsDidStartRechargeWithOrder:(NSString*)order;
/**
* @brief 跳提⽰示框时，⽤用户取消
*
* @param order 订单号
*/
- (void)TBBuyGoodsDidCancelByUser:(NSString *)order;

#endif


@end


#endif
