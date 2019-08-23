/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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
package com.cyou.mrd.DOTATribe;

import java.util.HashMap;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxEventTyper;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxSystem;
import com.umeng.analytics.MobclickAgent;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.WindowManager;
import android.widget.Toast;

public class DOTATribe extends Cocos2dxActivity{

	private static final int ANDROID_BUILD_GINGERBREAD = 9;
	private static final int SCREEN_ORIENTATION_SENSOR_LANDSCAPE = 6;
	private Activity ctx;
	private boolean m_bIsAppForeground = true;//是否前台显示
	
	protected void onCreate(Bundle savedInstanceState){
		ctx = this;
		initPlatform();
		super.onCreate(savedInstanceState);
		setCocos2dxEventHandler(tempEventHandler);
	
		//保持常亮
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		//屏幕方向
		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.GINGERBREAD)
		{
			setRequestedOrientation( ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
		}
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		//友盟
		MobclickAgent.onResume(this);
		
		if(!m_bIsAppForeground)
		{
			m_bIsAppForeground = true;
			pausePlatform();
		}
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();		
		//友盟
		MobclickAgent.onPause(this);
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
		if(!isAppOnForeground())
		{
			//进入后台
			m_bIsAppForeground = false;
		}
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub

		destroyPlatform();
		
		super.onDestroy();
	}
	
    //判断App是否在前台运行
	public boolean isAppOnForeground() {
		ActivityManager activityManager = (ActivityManager) getApplicationContext()
				.getSystemService(Context.ACTIVITY_SERVICE);
		String packageName = getApplicationContext().getPackageName();
		List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
		if (appProcesses == null)
			return false;
		for (RunningAppProcessInfo appProcess : appProcesses) {
			if (appProcess.processName.equals(packageName)
					&& appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
				return true;
			}
		}
		return false;
	} 

	public void setCocos2dxEventHandler(Handler handler)
	{
		super.myEventHandler = handler;
	}
	
	public static void gameSoCrashed()
	{
		Toast.makeText(DOTATribe.getContext(), "gameSoCrashed", 0).show();
	}
	
	public Handler tempEventHandler = new Handler()
	{
		public void handleMessage(Message msg)
		{
			switch (msg.what)
			{
			case Cocos2dxEventTyper._TYPED_AD_SHOW_ADMOB_:
			{// 显示广告
				;				
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_HIDE_ADMOB_:
			{// 隐藏广告
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SHOW_YOUMI_OFFERWALL_:
			{// 显示YOUMI积分墙
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SHOW_DIANJOY_OFFERWALL_:
			{// 显示DianJoy积分墙
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SHOW_IMMOB_OFFERWALL_:
			{// 显示Immob积分墙
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SHOW_TAPJOY_OFFERWALL_:
			{// 显示Tapjoy积分墙
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SHOW_DOMOB_OFFERWALL_:
			{// 显示Domob积分墙
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SHOW_91_OFFERWALL_:
			{// 显示91积分墙
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_QUERY_YOUMI_POINTS_:
			{// 查询YOUMI积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_QUERY_DIANJOY_POINTS_:
			{// 查询DianJoy积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_QUERY_IMMOB_POINTS_:
			{// 查询Immob积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_QUERY_TAPJOY_POINTS_:
			{// 查询Tapjoy积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_QUERY_DOMOB_POINTS_:
			{// 查询Domob积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_QUERY_91_POINTS_:
			{// 查询91积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SPEND_YOUMI_POINTS_:
			{// 消耗YOUMI积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SPEND_DIANJOY_POINTS_:
			{// 消耗DianJoy积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SPEND_IMMOB_POINTS_:
			{// 消耗Immob积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SPEND_TAPJOY_POINTS_:
			{// 消耗Tapjoy积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SPEND_DOMOB_POINTS_:
			{// 消耗Domob积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_SPEND_91_POINTS_:
			{// 消耗91积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_UPDATE_YOUMI_POINTS_:
			{// 更新YOUMI积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_UPDATE_DIANJOY_POINTS_:
			{// 更新DianJoy积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_UPDATE_IMMOB_POINTS_:
			{// 更新Immob积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_UPDATE_TAPJOY_POINTS_:
			{// 更新Tapjoy积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_UPDATE_DOMOB_POINTS_:
			{// 更新Domob积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_AD_UPDATE_91_POINTS_:
			{// 更新91积分墙点数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_LOGIN_RENN_:
			{// 登陆人人
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_RENN_:
			{// 人人文字分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_RENN_:
			{// 人人图文分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_LOGIN_WEIBO_:
			{// 登陆微博
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_WEIBO_:
			{// 微博文字分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_WEIBO_:
			{// 微博图文分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_LOGIN_QQ_:
			{// 登陆QQ微博
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_QQ_:
			{// QQ微博文字分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_QQ_:
			{// QQ微博图文分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_LOGIN_FACEBOOK_:
			{// 登陆Facebook
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_FACEBOOK_:
			{// Facebook文字分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_FACEBOOK_:
			{// Facebook图文分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_LOGIN_TWITTER_:
			{// 登陆Twitter
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_TWITTER_:
			{// Twitter文字分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_TWITTER_:
			{// Twitter图文分享
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_PAYMENT_PAY_:
			{// 开始购买
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_PAYMENT_VERIFY_:
			{// 购买校验
				;
			}
			break;
			case Cocos2dxEventTyper._TYPD_SYS_OPEN_URL_:
			{// 打开指定网页
				;
			}
			break;
			case Cocos2dxEventTyper._TYPD_SYS_SET_SYSLANG_:
			{// 设置系统语言
				;
			}
			break;
			case Cocos2dxEventTyper._TYPD_SYS_OPEN_PENGYOU_:
			{// 打开朋游
				;
			}
			break;
			case Cocos2dxEventTyper._TYPD_SYS_OPEN_MOREGAME_:
			{// 打开更多游戏（交叉推广）
				;
			}
			break;
			case Cocos2dxEventTyper._TYPD_SYS_OPEN_WEBDIALOG_:
			{// 打开webdialog
				Bundle b = msg.getData();
				int type = b.getInt("type");
				String url = b.getString("url");
			}break;
			case Cocos2dxEventTyper._TYPD_SYS_FORCE_UPDATE_:
			{// 强制更新
				Bundle b = msg.getData();
				String url = b.getString("url");
			}break;
			case Cocos2dxEventTyper._TYPED_SYS_ANDROID_APPEXIT_:
			{// 收到消息android应用要停止
				DOTATribe.this.exitPlatform();
				DOTATribe.this.finish();
				Cocos2dxGLSurfaceView.onAppExit();
			}break;
			case Cocos2dxEventTyper._TYPED_BEHAVIOR_BEGIN_EVENT_:
			{// 开始统计
				Bundle bundle = msg.getData();
				String eventId = bundle.getString("eventId");
				String text = bundle.getString("text");
				//友盟
				MobclickAgent.onEventBegin(ctx, eventId, text);
				//MBI
			}
			break;
			case Cocos2dxEventTyper._TYPED_BEHAVIOR_END_EVENT_:
			{// 结束统计
				Bundle bundle = msg.getData();
				String eventId = bundle.getString("eventId");
				String text = bundle.getString("text");
				//友盟
				MobclickAgent.onEventEnd(ctx, eventId, text);
				//MBI
				
			}
			break;
			case Cocos2dxEventTyper._TYPED_BEHAVIOR_LOG_EVENT_:
			{// 统计日志
				Bundle bundle = msg.getData();
				String eventId = bundle.getString("eventId");
				String text = bundle.getString("text");
				//友盟
				MobclickAgent.onEvent(ctx, eventId, text);
				//MBI
			}
			break;
			case Cocos2dxEventTyper._TYPED_BEHAVIOR_LOG_EVENT_WITH_LABEL_:
			{// 统计日志
				Bundle bundle = msg.getData();
				String eventId = bundle.getString("eventId");
				String text = bundle.getString("text");
				String label = bundle.getString("label");
				HashMap<String, String> map = new HashMap<String, String>();
				map.put("text", text);
				map.put("label", label);
				//友盟
				MobclickAgent.onEvent(ctx, eventId, map);
				//MBI
				
			}
			break;
			case Cocos2dxEventTyper._TYPED_FEEDBACK_SHOW_:
			{// 打开用户反馈
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_GAMECENTER_IS_AVALIABLE_:
			{// 判断GameCenter是否可用
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_GAMECENTER_AUTHENTICATE_:
			{// 登陆GameCenter
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_GAMECENTER_SHOW_LEADERBOARD_:
			{// 显示GameCenter排行榜
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_GAMECENTER_REPORT_SCORE__:
			{// 汇报GameCenter分数
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_GAMECENTER_SUBMIT_ACHIEVEMENT_:
			{// 提交GameCenter成就信息
				;
			}
			break;
			case Cocos2dxEventTyper._TYPED_PLATFORM_LOGIN_:{
				System.out.println("DOTATribe.java --- Login");
				loginPlatform();
			}break;
			case Cocos2dxEventTyper._TYPED_PLATFORM_LOGOUT_:{
				System.out.println("DOTATribe.java --- Logout");
				logoutPlatform();
			}break;
			case Cocos2dxEventTyper._TYPED_PLATFORM_COMPANYLOGOFINISHED_:{
				System.out.println("DOTATribe.java --- companyLogoFinished");
			}break;
			case Cocos2dxEventTyper._TYPED_PLATFORM_SHOWSDKCENTER_:{
				System.out.println("DOTATribe.java --- showSdkCenter");
				showCenterPlatform();
			}break;
			case Cocos2dxEventTyper._TYPED_PLATFORM_SHOWSUSPENDWINDOW_:{
				System.out.println("DOTATribe.java --- showSuspendWindow");
				Bundle b = msg.getData();
				showSuspendWindowPlatform(b.getBoolean("status"));
			}break;
			case Cocos2dxEventTyper._TYPED_PLATFORM_PAYGOODS_:{
				System.out.println("DOTATribe.java --- payGoods");
				Bundle b = msg.getData();
				payGoodsPlatform(b.getFloat("price"), b.getString("param0"), b.getString("param1"), b.getString("param2")
						, b.getString("param3"), b.getString("param4"), b.getString("param5"), b.getString("param6")
						, b.getString("param7"), b.getString("param8"), b.getString("param9"));
			}break;
			}
			
			super.handleMessage(msg);
		}
	};
	
    static {
         System.loadLibrary("game");
    }
    
    //初始化平台
    private void initPlatform()
    {
    	
    }
    
    
    //登陆平台
    private void loginPlatform()
    {
		System.out.println("java loginPlatform -- begin");
		
		System.out.println("java loginPlatform -- end");
    }
    
    
    //暂停
    private void pausePlatform()
    {

    }
    
    
    //登出平台
    private void logoutPlatform()
    {
		System.out.println("java logoutPlatform -- begin");

		System.out.println("java logoutPlatform -- end");
    }
    
    
    //平台退出，用于游戏退出
    public void exitPlatform()
    {

    }
    
    //显示SDK中心
    private void showCenterPlatform()
    {
		System.out.println("java showCenterPlatform -- begin");
		
		System.out.println("java showCenterPlatform -- end");    	
    }
    
    //显示悬浮窗
    private void showSuspendWindowPlatform(boolean status)
    {

    }
    
    //支付
    private void payGoodsPlatform(float price, String param0, String param1, String param2, String param3, String param4, String param5
    		, String param6, String param7, String param8, String param9)//param0订单号，param1商品Id，param2商品名，param3商品数量, param4玩家Id，param5服务器Id
    {
    	System.out.println("java payGoodsPlatform -- begin");
		
    	System.out.println("java payGoodsPlatform -- end");
    }
    
    //销毁平台
    private void destroyPlatform()
    {
		System.out.println("java destroyPlatform -- begin");
    	
		System.out.println("java destroyPlatform -- end");
    }
    
    
	private void onNetworkChanged()
	{// change
		Cocos2dxSystem.onNetworkChanged();
	}

	private void onNetworkDisConnected()
	{// disconnect
		Cocos2dxSystem.onNetworkDisConnected();
	}
	
}
