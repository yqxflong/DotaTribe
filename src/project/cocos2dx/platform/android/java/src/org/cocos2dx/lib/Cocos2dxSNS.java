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

public class Cocos2dxSNS {

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;
	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxSNS(final Context pContext) {
		this.mContext = pContext;
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void loginRenn() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_LOGIN_RENN_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void shareTextInRenn(String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_RENN_;
		Bundle bundle = new Bundle();
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void sharePictureInRenn(String file, String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_RENN_;
		Bundle bundle = new Bundle();
		bundle.putString("file", file);
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void loginWeibo() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_LOGIN_WEIBO_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void shareTextInWeibo(String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_WEIBO_;
		Bundle bundle = new Bundle();
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void sharePictureInWeibo(String file, String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_WEIBO_;
		Bundle bundle = new Bundle();
		bundle.putString("file", file);
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void loginQQ() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_LOGIN_QQ_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void shareTextInQQ(String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_QQ_;
		Bundle bundle = new Bundle();
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void sharePictureInQQ(String file, String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_QQ_;
		Bundle bundle = new Bundle();
		bundle.putString("file", file);
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void loginFacebook() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_LOGIN_FACEBOOK_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void shareTextInFacebook(String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_FACEBOOK_;
		Bundle bundle = new Bundle();
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void sharePictureInFacebook(String file, String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_FACEBOOK_;
		Bundle bundle = new Bundle();
		bundle.putString("file", file);
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void loginTwitter() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_LOGIN_TWITTER_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void shareTextInTwitter(String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_TEXT_IN_TWITTER_;
		Bundle bundle = new Bundle();
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void sharePictureInTwitter(String file, String text) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_SNS_SHARE_PICTURE_IN_TWITTER_;
		Bundle bundle = new Bundle();
		bundle.putString("file", file);
		bundle.putString("text", text);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginRennSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginRennFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInRennSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInRennFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInRennSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInRennFailed(final String error);
	
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginWeiboSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginWeiboFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInWeiboSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInWeiboFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInWeiboSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInWeiboFailed(final String error);
	
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginQQSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginQQFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInQQSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInQQFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInQQSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInQQFailed(final String error);
	
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginFacebookSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginFacebookFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInFacebookSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInFacebookFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInFacebookSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInFacebookFailed(final String error);
	
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginTwitterSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onLoginTwitterFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInTwitterSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onShareTextInTwitterFailed(final String error);
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInTwitterSuccess();
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onSharePictureInTwitterFailed(final String error);
}
