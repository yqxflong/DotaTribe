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

import android.content.Context;
import android.os.Bundle;
import android.os.Message;

public class Cocos2dxPlatform {

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxPlatform(final Context pContext) {
		this.mContext = pContext;
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void login() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PLATFORM_LOGIN_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void logout(){
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PLATFORM_LOGOUT_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	
	public void showSdkCenter()
	{
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PLATFORM_SHOWSDKCENTER_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
		
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	
	public void showSuspendWindow(boolean status)
	{
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PLATFORM_SHOWSUSPENDWINDOW_;
		Bundle b = new Bundle();
		b.putBoolean("status", status);
		message.setData(b);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
		
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void payGoods(int price, String param0, String param1, String param2, String param3, String param4, String param5
			, String param6, String param7, String param8, String param9)
	{
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PLATFORM_PAYGOODS_;
		Bundle b = new Bundle();
		b.putInt("price", price);
		b.putString("param0", param0);
		b.putString("param1", param1);
		b.putString("param2", param2);
		b.putString("param3", param3);
		b.putString("param4", param4);
		b.putString("param5", param5);
		b.putString("param6", param6);
		b.putString("param7", param7);
		b.putString("param8", param8);
		b.putString("param9", param9);
		message.setData(b);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginResultHandler(final int sdkType,final Boolean bSuccess, final String param0, final String param1, final String param2, final String param3, final String param4
			, final String param5, final String param6, final String param7, final String param8, final String param9);	
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLogoutCallBack(final int sdkType,final Boolean bSuccess, final String param0, final String param1, final String param2, final String param3, final String param4
			, final String param5, final String param6, final String param7, final String param8, final String param9);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onPayResultCallBack(final int sdkType, final int resultCode, final String param0, final String param1);
	
}
