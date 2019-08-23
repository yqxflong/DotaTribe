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

public class Cocos2dxAd {
	// ===========================================================
	// Constants
	// ===========================================================

	private final Context mContext;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxAd(final Context pContext) {
		this.mContext = pContext;
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void showAdmob(boolean bShow) {
		Message message = new Message();
		if (bShow)
			message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_ADMOB_;
		else
			message.what = Cocos2dxEventTyper._TYPED_AD_HIDE_ADMOB_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void showYoumiOfferWall() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_YOUMI_OFFERWALL_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void showDianjoyOfferWall() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_DIANJOY_OFFERWALL_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void showImmobOfferWall() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_IMMOB_OFFERWALL_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================	
	public void showTapjoyOfferWall() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_TAPJOY_OFFERWALL_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================	
	public void showDomobOfferWall() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_DOMOB_OFFERWALL_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================	
	public void show91OfferWall() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SHOW_91_OFFERWALL_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void queryYoumiPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_QUERY_YOUMI_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void queryDianjoyPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_QUERY_DIANJOY_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void queryImmobPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_QUERY_IMMOB_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void queryTapjoyPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_QUERY_TAPJOY_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void queryDomobPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_QUERY_DOMOB_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void query91Points() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_QUERY_91_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void updateYoumiPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_UPDATE_YOUMI_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void updateDianjoyPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_UPDATE_DIANJOY_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void updateImmobPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_UPDATE_IMMOB_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void updateTapjoyPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_UPDATE_TAPJOY_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void updateDomobPoints() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_UPDATE_DOMOB_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void update91Points() {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_UPDATE_91_POINTS_;
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void spendYoumiPoints(int amount) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SPEND_YOUMI_POINTS_;
		Bundle bundle = new Bundle();
		bundle.putInt("value", amount);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void spendDianjoyPoints(int amount) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SPEND_DIANJOY_POINTS_;
		Bundle bundle = new Bundle();
		bundle.putInt("value", amount);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void spendImmobPoints(int amount) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SPEND_IMMOB_POINTS_;
		Bundle bundle = new Bundle();
		bundle.putInt("value", amount);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void spendTapjoyPoints(int amount) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SPEND_TAPJOY_POINTS_;
		Bundle bundle = new Bundle();
		bundle.putInt("value", amount);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void spendDomobPoints(int amount) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SPEND_DOMOB_POINTS_;
		Bundle bundle = new Bundle();
		bundle.putInt("value", amount);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// methond
	// ===========================================================
	public void spend91Points(int amount) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_AD_SPEND_91_POINTS_;
		Bundle bundle = new Bundle();
		bundle.putInt("value", amount);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onReceiveYouMiPoint(final int amount);

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onReceiveDianJoyPoint(final int amount);

	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onReceiveImmobPoint(final int amount);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onReceiveTapjoyPoint(final int amount);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onReceiveDomobPoint(final int amount);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onReceive91Point(final int amount);
}
