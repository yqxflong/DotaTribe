/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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

import java.io.UnsupportedEncodingException;
import java.util.Locale;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.res.AssetManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.WindowManager;

public class Cocos2dxHelper {
	// ===========================================================
	// Constants
	// ===========================================================
	private static final String PREFS_NAME = "Cocos2dxPrefsFile";

	// ===========================================================
	// Fields
	// ===========================================================

	private static Cocos2dxMusic sCocos2dMusic;
	private static Cocos2dxSound sCocos2dSound;
	private static AssetManager sAssetManager;
	private static Cocos2dxAccelerometer sCocos2dxAccelerometer;
	private static Cocos2dxAd sCocos2dxAd;
	private static Cocos2dxSNS sCocos2dxSNS;
	private static Cocos2dxPayment sCocos2dxPayment;
	private static Cocos2dxSystem sCocos2dxSystem;
	private static Cocos2dxBehavior sCocos2dxBehavior;
	private static Cocos2dxFeedback sCocos2dxFeedback;
	private static Cocos2dxGameCenter sCocos2dxGameCenter;
	private static Cocos2dxPlatform sCocos2dxPlatform;
	
	private static boolean sAccelerometerEnabled;
	private static String sPackageName;
	private static String sFileDirectory;
	private static Context sContext = null;
	private static Cocos2dxHelperListener sCocos2dxHelperListener;

	// ===========================================================
	// Constructors
	// ===========================================================

	public static void init(final Context pContext, final Cocos2dxHelperListener pCocos2dxHelperListener) {
		final ApplicationInfo applicationInfo = pContext.getApplicationInfo();
		
		Cocos2dxHelper.sContext = pContext;
		Cocos2dxHelper.sCocos2dxHelperListener = pCocos2dxHelperListener;

		// 获得设备信息
		TelephonyManager tm = (TelephonyManager)((Cocos2dxActivity)pContext).getSystemService(Cocos2dxActivity.TELEPHONY_SERVICE);  
		WifiManager wifi = (WifiManager)((Cocos2dxActivity)pContext).getSystemService(Context.WIFI_SERVICE);    
		WifiInfo info = wifi.getConnectionInfo();
		Cocos2dxHelper.nativeSetAndroidMacAddr(info.getMacAddress());
				
		Cocos2dxHelper.sPackageName = applicationInfo.packageName;
		Cocos2dxHelper.sFileDirectory = pContext.getFilesDir().getAbsolutePath();
		Cocos2dxHelper.nativeSetApkPath(applicationInfo.sourceDir);
		Cocos2dxHelper.nativeSetAndroidIMEI(tm.getDeviceId());

		Cocos2dxHelper.sCocos2dxAccelerometer = new Cocos2dxAccelerometer(pContext);
		Cocos2dxHelper.sCocos2dMusic = new Cocos2dxMusic(pContext);
		Cocos2dxHelper.sCocos2dSound = new Cocos2dxSound(pContext);
		

		Cocos2dxHelper.sCocos2dxAd = new Cocos2dxAd(pContext);
		Cocos2dxHelper.sCocos2dxSNS = new Cocos2dxSNS(pContext);
		Cocos2dxHelper.sCocos2dxPayment = new Cocos2dxPayment(pContext);
		Cocos2dxHelper.sCocos2dxSystem = new Cocos2dxSystem(pContext);
		Cocos2dxHelper.sCocos2dxFeedback = new Cocos2dxFeedback(pContext);
		Cocos2dxHelper.sCocos2dxBehavior = new Cocos2dxBehavior(pContext);
		Cocos2dxHelper.sCocos2dxGameCenter = new Cocos2dxGameCenter(pContext);
		Cocos2dxHelper.sCocos2dxPlatform = new Cocos2dxPlatform(pContext);

		Cocos2dxHelper.sAssetManager = pContext.getAssets();
		Cocos2dxBitmap.setContext(pContext);
		Cocos2dxETCLoader.setContext(pContext);
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	private static native void nativeSetApkPath(final String pApkPath);

	private static native void nativeSetEditTextDialogResult(final byte[] pBytes);

	private static native void nativeSetAndroidIMEI(final String imei);

	private static native void nativeSetAndroidMacAddr(final String macAddr);
	
	public static String getCocos2dxPackageName() {
		return Cocos2dxHelper.sPackageName;
	}

	public static String getCocos2dxWritablePath() {
		return Cocos2dxHelper.sFileDirectory;
	}

	public static String getCurrentLanguage() {
		return Locale.getDefault().getLanguage();
	}
	
	public static String getDeviceModel(){
		return Build.MODEL;
    }

	public static AssetManager getAssetManager() {
		return Cocos2dxHelper.sAssetManager;
	}

	public static void enableAccelerometer() {
		Cocos2dxHelper.sAccelerometerEnabled = true;
		Cocos2dxHelper.sCocos2dxAccelerometer.enable();
	}


	public static void setAccelerometerInterval(float interval) {
		Cocos2dxHelper.sCocos2dxAccelerometer.setInterval(interval);
	}

	public static void disableAccelerometer() {
		Cocos2dxHelper.sAccelerometerEnabled = false;
		Cocos2dxHelper.sCocos2dxAccelerometer.disable();
	}

	public static void preloadBackgroundMusic(final String pPath) {
		Cocos2dxHelper.sCocos2dMusic.preloadBackgroundMusic(pPath);
	}

	public static void playBackgroundMusic(final String pPath, final boolean isLoop) {
		Cocos2dxHelper.sCocos2dMusic.playBackgroundMusic(pPath, isLoop);
	}

	public static void resumeBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.resumeBackgroundMusic();
	}

	public static void pauseBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.pauseBackgroundMusic();
	}

	public static void stopBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.stopBackgroundMusic();
	}

	public static void rewindBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.rewindBackgroundMusic();
	}

	public static boolean isBackgroundMusicPlaying() {
		return Cocos2dxHelper.sCocos2dMusic.isBackgroundMusicPlaying();
	}

	public static float getBackgroundMusicVolume() {
		return Cocos2dxHelper.sCocos2dMusic.getBackgroundVolume();
	}

	public static void setBackgroundMusicVolume(final float volume) {
		Cocos2dxHelper.sCocos2dMusic.setBackgroundVolume(volume);
	}

	public static void preloadEffect(final String path) {
		Cocos2dxHelper.sCocos2dSound.preloadEffect(path);
	}

	public static int playEffect(final String path, final boolean isLoop, final float pitch, final float pan, final float gain) {
		return Cocos2dxHelper.sCocos2dSound.playEffect(path, isLoop, pitch, pan, gain);
	}

	public static void resumeEffect(final int soundId) {
		Cocos2dxHelper.sCocos2dSound.resumeEffect(soundId);
	}

	public static void pauseEffect(final int soundId) {
		Cocos2dxHelper.sCocos2dSound.pauseEffect(soundId);
	}

	public static void stopEffect(final int soundId) {
		Cocos2dxHelper.sCocos2dSound.stopEffect(soundId);
	}

	public static float getEffectsVolume() {
		return Cocos2dxHelper.sCocos2dSound.getEffectsVolume();
	}

	public static void setEffectsVolume(final float volume) {
		Cocos2dxHelper.sCocos2dSound.setEffectsVolume(volume);
	}

	public static void unloadEffect(final String path) {
		Cocos2dxHelper.sCocos2dSound.unloadEffect(path);
	}

	public static void pauseAllEffects() {
		Cocos2dxHelper.sCocos2dSound.pauseAllEffects();
	}

	public static void resumeAllEffects() {
		Cocos2dxHelper.sCocos2dSound.resumeAllEffects();
	}

	public static void stopAllEffects() {
		Cocos2dxHelper.sCocos2dSound.stopAllEffects();
	}

	public static void end() {
		Cocos2dxHelper.sCocos2dMusic.end();
		Cocos2dxHelper.sCocos2dSound.end();
	}

	public static void onResume() {
		if (Cocos2dxHelper.sAccelerometerEnabled) {
			Cocos2dxHelper.sCocos2dxAccelerometer.enable();
		}
	}

	public static void onPause() {
		if (Cocos2dxHelper.sAccelerometerEnabled) {
			Cocos2dxHelper.sCocos2dxAccelerometer.disable();
		}
	}

	public static void terminateProcess() {
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	private static void showDialog(final String pTitle, final String pMessage) {
		Cocos2dxHelper.sCocos2dxHelperListener.showDialog(pTitle, pMessage);
	}

	private static void showEditTextDialog(final String pTitle, final String pMessage, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) {
		Cocos2dxHelper.sCocos2dxHelperListener.showEditTextDialog(pTitle, pMessage, pInputMode, pInputFlag, pReturnType, pMaxLength);
	}

	public static void setEditTextDialogResult(final String pResult) {
		try {
			final byte[] bytesUTF8 = pResult.getBytes("UTF8");

			Cocos2dxHelper.sCocos2dxHelperListener.runOnGLThread(new Runnable() {
				@Override
				public void run() {
					Cocos2dxHelper.nativeSetEditTextDialogResult(bytesUTF8);
				}
			});
		} catch (UnsupportedEncodingException pUnsupportedEncodingException) {
			/* Nothing. */
		}
	}

    public static int getDPI()
    {
		if (sContext != null)
		{
			DisplayMetrics metrics = new DisplayMetrics();
			WindowManager wm = ((Activity)sContext).getWindowManager();
			if (wm != null)
			{
				Display d = wm.getDefaultDisplay();
				if (d != null)
				{
					d.getMetrics(metrics);
					return (int)(metrics.density*160.0f);
				}
			}
		}
		return -1;
    }
    
    // ===========================================================
 	// Functions for CCUserDefault
 	// ===========================================================
    
    public static boolean getBoolForKey(String key, boolean defaultValue) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	return settings.getBoolean(key, defaultValue);
    }
    
    public static int getIntegerForKey(String key, int defaultValue) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	return settings.getInt(key, defaultValue);
    }
    
    public static float getFloatForKey(String key, float defaultValue) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	return settings.getFloat(key, defaultValue);
    }
    
    public static double getDoubleForKey(String key, double defaultValue) {
    	// SharedPreferences doesn't support saving double value
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	return settings.getFloat(key, (float)defaultValue);
    }
    
    public static String getStringForKey(String key, String defaultValue) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	return settings.getString(key, defaultValue);
    }
    
    public static void setBoolForKey(String key, boolean value) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	SharedPreferences.Editor editor = settings.edit();
    	editor.putBoolean(key, value);
    	editor.commit();
    }
    
    public static void setIntegerForKey(String key, int value) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	SharedPreferences.Editor editor = settings.edit();
    	editor.putInt(key, value);
    	editor.commit();
    }
    
    public static void setFloatForKey(String key, float value) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	SharedPreferences.Editor editor = settings.edit();
    	editor.putFloat(key, value);
    	editor.commit();
    }
    
    public static void setDoubleForKey(String key, double value) {
    	// SharedPreferences doesn't support recording double value
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	SharedPreferences.Editor editor = settings.edit();
    	editor.putFloat(key, (float)value);
    	editor.commit();
    }
    
    public static void setStringForKey(String key, String value) {
    	SharedPreferences settings = ((Activity)sContext).getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
    	SharedPreferences.Editor editor = settings.edit();
    	editor.putString(key, value);
    	editor.commit();
    }
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	public static interface Cocos2dxHelperListener {
		public void showDialog(final String pTitle, final String pMessage);
		public void showEditTextDialog(final String pTitle, final String pMessage, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength);

		public void runOnGLThread(final Runnable pRunnable);
	}
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	public static void enableAd() {
		sCocos2dxAd.showAdmob(true);
	}

	public static void disableAd() {
		sCocos2dxAd.showAdmob(false);
	}

	public static void showYoumiOfferWall() {
		sCocos2dxAd.showYoumiOfferWall();
	}

	public static void showDianjoyOfferWall() {
		sCocos2dxAd.showDianjoyOfferWall();
	}

	public static void showImmobOfferWall() {
		sCocos2dxAd.showImmobOfferWall();
	}

	public static void showTapjoyOfferWall() {
		sCocos2dxAd.showTapjoyOfferWall();
	}

	public static void showDomobOfferWall() {
		sCocos2dxAd.showDomobOfferWall();
	}

	public static void show91OfferWall() {
		sCocos2dxAd.show91OfferWall();
	}

	public static void queryYoumiPoints() {
		sCocos2dxAd.queryYoumiPoints();
	}

	public static void queryDianjoyPoints() {
		sCocos2dxAd.queryDianjoyPoints();
	}

	public static void queryImmobPoints() {
		sCocos2dxAd.queryImmobPoints();
	}

	public static void queryTapjoyPoints() {
		sCocos2dxAd.queryTapjoyPoints();
	}

	public static void queryDomobPoints() {
		sCocos2dxAd.queryDomobPoints();
	}

	public static void query91Points() {
		sCocos2dxAd.query91Points();
	}

	public static void updateYoumiPoints() {
		sCocos2dxAd.updateYoumiPoints();
	}

	public static void updateDianjoyPoints() {
		sCocos2dxAd.updateDianjoyPoints();
	}

	public static void updateImmobPoints() {
		sCocos2dxAd.updateImmobPoints();
	}

	public static void updateTapjoyPoints() {
		sCocos2dxAd.updateTapjoyPoints();
	}

	public static void updateDomobPoints() {
		sCocos2dxAd.updateDomobPoints();
	}

	public static void update91Points() {
		sCocos2dxAd.update91Points();
	}

	public static void spendYoumiPoints(final int amount) {
		sCocos2dxAd.spendYoumiPoints(amount);
	}

	public static void spendDianjoyPoints(final int amount) {
		sCocos2dxAd.spendDianjoyPoints(amount);
	}

	public static void spendImmobPoints(final int amount) {
		sCocos2dxAd.spendImmobPoints(amount);
	}

	public static void spendTapjoyPoints(final int amount) {
		sCocos2dxAd.spendTapjoyPoints(amount);
	}

	public static void spendDomobPoints(final int amount) {
		sCocos2dxAd.spendDomobPoints(amount);
	}

	public static void spend91Points(final int amount) {
		sCocos2dxAd.spend91Points(amount);
	}

	public static void behaviorLogEvent(final String eventId, final String text) {
		sCocos2dxBehavior.behaviorLogEvent(eventId, text);
	}
	
	public static void behaviorLogEventWithLabel(final String eventId, final String text, final String label) {
		sCocos2dxBehavior.behaviorLogEventWithLabel(eventId, text, label);
	}
	
	public static void behaviorBeginLogEvent(final String eventId, final String text) {
		sCocos2dxBehavior.behaviorBeginLogEvent(eventId, text);
	}
	
	public static void behaviorEndLogEvent(final String eventId, final String text) {
		sCocos2dxBehavior.behaviorEndLogEvent(eventId, text);
	}

	public static void showFeedbackDialog(){
		sCocos2dxFeedback.showFeedbackDialog();
	}

	public static void pay(final String productId, final String productName, final String productDesc, final String IAPId, final int productMoney, final int chargePoint, final int giveGold) {
		sCocos2dxPayment.pay(productId, productName, productDesc, productMoney, chargePoint, giveGold, IAPId);
	}

	public static void verify(final String IAPId){
		sCocos2dxPayment.verify(IAPId);
	}
	
	public static void loginRenn() {
		sCocos2dxSNS.loginRenn();
	}

	public static void shareTextInRenn(final String text) {
		sCocos2dxSNS.shareTextInRenn(text);
	}

	public static void sharePictureInRenn(final String file, final String text) {
		sCocos2dxSNS.sharePictureInRenn(file, text);
	}

	public static void loginWeibo() {
		sCocos2dxSNS.loginWeibo();
	}

	public static void shareTextInWeibo(final String text) {
		sCocos2dxSNS.shareTextInWeibo(text);
	}

	public static void sharePictureInWeibo(final String file, final String text) {
		sCocos2dxSNS.sharePictureInWeibo(file, text);
	}

	public static void loginQQ() {
		sCocos2dxSNS.loginQQ();
	}

	public static void shareTextInQQ(final String text) {
		sCocos2dxSNS.shareTextInQQ(text);
	}

	public static void sharePictureInQQ(final String file, final String text) {
		sCocos2dxSNS.sharePictureInQQ(file, text);
	}

	public static void loginFacebook() {
		sCocos2dxSNS.loginFacebook();
	}

	public static void shareTextInFacebook(final String text) {
		sCocos2dxSNS.shareTextInFacebook(text);
	}

	public static void sharePictureInFacebook(final String file, final String text) {
		sCocos2dxSNS.sharePictureInFacebook(file, text);
	}

	public static void loginTwitter() {
		sCocos2dxSNS.loginTwitter();
	}

	public static void shareTextInTwitter(final String text) {
		sCocos2dxSNS.shareTextInTwitter(text);
	}

	public static void sharePictureInTwitter(final String file, final String text) {
		sCocos2dxSNS.sharePictureInTwitter(file, text);
	}

	public static void openURL(final String url) {
		sCocos2dxSystem.openURL(url);
	}

	public static void forceUpdate(final String url) {
		sCocos2dxSystem.forceUpdate(url);
	}

	public static void androidAppExit(){
		sCocos2dxSystem.androidAppExit();
	}
	
	public static void setSysLang(final int type){
		sCocos2dxSystem.setSysLang(type);
	}

	public static void openPengYou(){
		sCocos2dxSystem.openPengYou();
	}

	public static void openMoreGame(){
		sCocos2dxSystem.openMoreGame();
	}

	public static void openWebDialog(final int type, final String url) {
		sCocos2dxSystem.openWebDialog(type, url);
	}

	public static void isGameCenterAvailable() {
		sCocos2dxGameCenter.isGameCenterAvailable();
	}

	public static void authenticateGameCenter() {
		sCocos2dxGameCenter.authenticateGameCenter();
	}

	public static void showLeaderBoard(final String category) {
		sCocos2dxGameCenter.showLeaderBoard(category);
	}

	public static void reportGameScore(final String category, final long score) {
		sCocos2dxGameCenter.reportGameScore(category, score);
	}

	public static void submitAchievement(final String identifier, final double percentComplete) {
		sCocos2dxGameCenter.submitAchievement(identifier, percentComplete);
	}
	
	public static void loginPlatform(){
		sCocos2dxPlatform.login();
	}
	
	public static void logoutPlatform(){
		sCocos2dxPlatform.logout();
	}
	
	public static void companyLogoFinished(){
		sCocos2dxPlatform.companyLogoFinished();
	}
	
	public static void showSDKCenter(){
		sCocos2dxPlatform.showSdkCenter();
	}
	
	public static void showSuspendWindow(final boolean status)
	{
		sCocos2dxPlatform.showSuspendWindow(status);
	}
	
	public static void payGoods(final String param0, final String param1, final String param2, final String param3
			, final String param4, final String param5, final String param6, final String param7
			,final String param8, final String param9,final float price)
	{
		sCocos2dxPlatform.payGoods(price, param0, param1, param2, param3, param4, param5, param6, param7, param8, param9);
	}
}
