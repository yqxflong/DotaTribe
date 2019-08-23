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

public class Cocos2dxPayment {
	// ===========================================================
	// Constants
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;

	// ===========================================================
	// Constructors
	// ===========================================================

	public Cocos2dxPayment(final Context pContext) {
		this.mContext = pContext;
	}

	// ===========================================================
	// methond
	// ===========================================================
	public void pay(String productId, String productName, String productDesc, int productMoney, int chargePoint, int giveGold, String IAPId) {
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PAYMENT_PAY_;
		Bundle bundle = new Bundle();
		bundle.putString("productId", productId);
		bundle.putString("productName", productName);
		bundle.putString("productDesc", productDesc);
		bundle.putInt("productMoney", productMoney);
		bundle.putInt("chargePoint", chargePoint);
		bundle.putInt("giveGold", giveGold);
		bundle.putString("IAPId", IAPId);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}

	public void verify(final String IAPId){
		Message message = new Message();
		message.what = Cocos2dxEventTyper._TYPED_PAYMENT_VERIFY_;
		Bundle bundle = new Bundle();
		bundle.putString("IAPId", IAPId);
		message.setData(bundle);
		((Cocos2dxActivity)mContext).myEventHandler.sendMessage(message);
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onPayFailed(final String IAPId, final String error);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onPaySuccess(final String IAPId);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onVerifyFailed(final String IAPId, final String error);
	
	// ===========================================================
	// Methods
	// ===========================================================
	public static native void onVerifySuccess(final String IAPId);
}
