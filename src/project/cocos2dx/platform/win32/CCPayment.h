/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __PLATFORM_WIN32_CCPAYMENT_H__
#define __PLATFORM_WIN32_CCPAYMENT_H__

#include "platform/CCCommon.h"
#include "platform/CCPaymentDelegate.h"

namespace   cocos2d {

class CC_DLL CCPayment
{
private:
	CCPaymentDelegate* m_pPayDelegate;

public:
    CCPayment();
    ~CCPayment();

public:
    void setDelegate(CCPaymentDelegate* pDelegate);

public:
	void init();
	void destroy();

public:
	bool isAvailable();
	bool hasPayment(std::string IAPId);
	void restorePayment();
	void deletePayment(std::string IAPId);
	void pay(std::string productId, std::string productName, std::string productDesc, float productMoney, int chargePoint, std::string IAPId);
	void verify(std::string IAPId);
	void end();
	void onServerSureOrder(std::string productId,std::string productName,float productMoney,std::string IAPId);
public:
	virtual void onPayFailed(std::string IAPId, std::string error);
	virtual void onPaySuccess(std::string IAPId, std::string transactionId, std::string transactionReceipt);
	virtual void onVerifyFailed(std::string IAPId, std::string error);
	virtual void onVerifySuccess(std::string IAPId);
	virtual void onRestoreSuccess(std::string Id);
	virtual void insertPayment(std::string productId,std::string transactionId);
};

}//namespace cocos2d

#endif
