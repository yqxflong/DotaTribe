/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import java.util.HashMap;

import android.content.Context;
import android.graphics.Typeface;

public class Cocos2dxEventTyper {

	public static final int _TYPED_AD_SHOW_ADMOB_                 = 0x101;
	public static final int _TYPED_AD_HIDE_ADMOB_                 = 0x102;
	public static final int _TYPED_AD_SHOW_YOUMI_OFFERWALL_       = 0x103;
	public static final int _TYPED_AD_SHOW_DIANJOY_OFFERWALL_     = 0x104;
	public static final int _TYPED_AD_SHOW_IMMOB_OFFERWALL_       = 0x105;
	public static final int _TYPED_AD_SHOW_TAPJOY_OFFERWALL_      = 0x106;
	public static final int _TYPED_AD_SHOW_DOMOB_OFFERWALL_       = 0x107;
	public static final int _TYPED_AD_SHOW_91_OFFERWALL_          = 0x108;

	public static final int _TYPED_AD_QUERY_YOUMI_POINTS_         = 0x201;
	public static final int _TYPED_AD_QUERY_DIANJOY_POINTS_       = 0x202;
	public static final int _TYPED_AD_QUERY_IMMOB_POINTS_         = 0x203;
	public static final int _TYPED_AD_QUERY_TAPJOY_POINTS_        = 0x204;
	public static final int _TYPED_AD_QUERY_DOMOB_POINTS_         = 0x205;
	public static final int _TYPED_AD_QUERY_91_POINTS_            = 0x206;

	public static final int _TYPED_AD_SPEND_YOUMI_POINTS_         = 0x211;
	public static final int _TYPED_AD_SPEND_DIANJOY_POINTS_       = 0x212;
	public static final int _TYPED_AD_SPEND_IMMOB_POINTS_         = 0x213;
	public static final int _TYPED_AD_SPEND_TAPJOY_POINTS_        = 0x214;
	public static final int _TYPED_AD_SPEND_DOMOB_POINTS_         = 0x215;
	public static final int _TYPED_AD_SPEND_91_POINTS_            = 0x216;
	
	public static final int _TYPED_AD_UPDATE_YOUMI_POINTS_        = 0x221;
	public static final int _TYPED_AD_UPDATE_DIANJOY_POINTS_      = 0x222;
	public static final int _TYPED_AD_UPDATE_IMMOB_POINTS_        = 0x223;
	public static final int _TYPED_AD_UPDATE_TAPJOY_POINTS_       = 0x224;
	public static final int _TYPED_AD_UPDATE_DOMOB_POINTS_        = 0x225;
	public static final int _TYPED_AD_UPDATE_91_POINTS_           = 0x226;

	public static final int _TYPED_SNS_LOGIN_RENN_                = 0x301;
	public static final int _TYPED_SNS_SHARE_TEXT_IN_RENN_        = 0x302;
	public static final int _TYPED_SNS_SHARE_PICTURE_IN_RENN_     = 0x303;
	public static final int _TYPED_SNS_LOGIN_WEIBO_               = 0x304;
	public static final int _TYPED_SNS_SHARE_TEXT_IN_WEIBO_       = 0x305;
	public static final int _TYPED_SNS_SHARE_PICTURE_IN_WEIBO_    = 0x306;
	public static final int _TYPED_SNS_LOGIN_QQ_                  = 0x307;
	public static final int _TYPED_SNS_SHARE_TEXT_IN_QQ_          = 0x308;
	public static final int _TYPED_SNS_SHARE_PICTURE_IN_QQ_       = 0x309;
	public static final int _TYPED_SNS_LOGIN_FACEBOOK_            = 0x310;
	public static final int _TYPED_SNS_SHARE_TEXT_IN_FACEBOOK_    = 0x311;
	public static final int _TYPED_SNS_SHARE_PICTURE_IN_FACEBOOK_ = 0x312;
	public static final int _TYPED_SNS_LOGIN_TWITTER_             = 0x313;
	public static final int _TYPED_SNS_SHARE_TEXT_IN_TWITTER_     = 0x314;
	public static final int _TYPED_SNS_SHARE_PICTURE_IN_TWITTER_  = 0x315;
	
	public static final int _TYPED_PAYMENT_PAY_                   = 0x401;
	public static final int _TYPED_PAYMENT_VERIFY_                = 0x402;
	
	public static final int _TYPD_SYS_OPEN_URL_                   = 0x501;
	public static final int _TYPD_SYS_SET_SYSLANG_                = 0x502;
	public static final int _TYPD_SYS_OPEN_PENGYOU_               = 0x503;
	public static final int _TYPD_SYS_OPEN_MOREGAME_              = 0x504;
	public static final int _TYPD_SYS_OPEN_WEBDIALOG_             = 0x505;
	public static final int _TYPD_SYS_FORCE_UPDATE_               = 0x506;
	public static final int _TYPED_SYS_ANDROID_APPEXIT_			  = 0x507;
	
	public static final int _TYPED_BEHAVIOR_BEGIN_EVENT_          = 0x601;
	public static final int _TYPED_BEHAVIOR_END_EVENT_            = 0x602;
	public static final int _TYPED_BEHAVIOR_LOG_EVENT_            = 0x603;
	public static final int _TYPED_BEHAVIOR_LOG_EVENT_WITH_LABEL_ = 0x604;
	
	public static final int _TYPED_FEEDBACK_SHOW_                 = 0x701;
	
	public static final int _TYPED_GAMECENTER_IS_AVALIABLE_       = 0x801;
	public static final int _TYPED_GAMECENTER_AUTHENTICATE_       = 0x802;
	public static final int _TYPED_GAMECENTER_SHOW_LEADERBOARD_   = 0x803;
	public static final int _TYPED_GAMECENTER_REPORT_SCORE__      = 0x804;
	public static final int _TYPED_GAMECENTER_SUBMIT_ACHIEVEMENT_ = 0x805;

	public static final int _TYPED_PLATFORM_LOGIN_              			= 0x901;
	public static final int _TYPED_PLATFORM_LOGOUT_             			= 0x902;
	public static final int _TYPED_PLATFORM_COMPANYLOGOFINISHED_            = 0x903;
	
	public static final int _TYPED_PLATFORM_SHOWSDKCENTER_			=0x1001;
	public static final int _TYPED_PLATFORM_SHOWSUSPENDWINDOW_		=0x1002;
	public static final int _TYPED_PLATFORM_PAYGOODS_				=0x1003;
	
}
