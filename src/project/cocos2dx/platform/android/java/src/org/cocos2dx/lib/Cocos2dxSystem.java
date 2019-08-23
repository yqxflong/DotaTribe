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

public class Cocos2dxSystem {

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxSystem(final Context pContext) {
		this.mContext = pContext;
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void openURL(String url) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPD_SYS_OPEN_URL_;
		Bundle bundle = new Bundle();
		bundle.putString("url", url);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void setSysLang(final int type){
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPD_SYS_SET_SYSLANG_;
		Bundle bundle = new Bundle();
		bundle.putInt("type", type);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void openPengYou(){
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPD_SYS_OPEN_PENGYOU_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void openMoreGame(){
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPD_SYS_OPEN_MOREGAME_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void openWebDialog(int type, String url) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPD_SYS_OPEN_WEBDIALOG_;
		Bundle bundle = new Bundle();
		bundle.putInt("type", type);
		bundle.putString("url", url);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void forceUpdate(String url) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPD_SYS_FORCE_UPDATE_;
		Bundle bundle = new Bundle();
		bundle.putString("url", url);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onAppExit();

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onWebDialogClose(final int type);

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onNetworkChanged();

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onNetworkDisConnected();

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onQueryAppServerPushId(final String pushId);
}
