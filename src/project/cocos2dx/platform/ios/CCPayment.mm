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
#include "CCPayment.h"
#include "Cocos2dEventTyper.h"
#include "CCDirector.h"
#include "ccMacros.h"
#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>
#import <Foundation/Foundation.h>
#import <Foundation/NSValue.h>
#include <stdio.h>


namespace cocos2d
{
    CCPayment::CCPayment() : m_pPayDelegate(NULL)
    {
    }

    CCPayment::~CCPayment() 
    {

    }

    void CCPayment::setDelegate(CCPaymentDelegate* pDelegate) 
    {
        m_pPayDelegate = pDelegate;
    }

	void CCPayment::init()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_REGISTER_PAYMENT_EVENT_NAME_ object:nil];
	}

	void CCPayment::destroy()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_REMOVE_PAYMENT_EVENT_NAME_ object:nil];
	}

	bool CCPayment::isAvailable()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		
		NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:0],@"isAvailable",nil];
		[center postNotificationName:_TYPED_COCOS2D_CHECK_PAYMENT_EVENT_NAME_ object:nil userInfo:dict];
		
		NSNumber* num = [dict objectForKey:@"isAvailable"];
		return [num intValue]==1;
	}

	bool CCPayment::hasPayment(std::string IAPId)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		
		NSString* IAPIdString = [NSString stringWithUTF8String:IAPId.c_str()];
		NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:0],@"isHave",IAPIdString,@"IAPId",nil];
		[center postNotificationName:_TYPED_COCOS2D_HAVE_PAYMENT_EVENT_NAME_ object:nil userInfo:dict];
		
		NSNumber* num = [dict objectForKey:@"isHave"];
		return [num intValue]==1;
	}

	void CCPayment::restorePayment()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_RESTORE_PAYMENT_EVENT_NAME_ object:nil];
	}

	void CCPayment::deletePayment(std::string IAPId)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:IAPId.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"IAPId"];
		[center postNotificationName:_TYPED_COCOS2D_DELETE_PAYMENT_EVENT_NAME_ object:nil userInfo:dict];
	}

	void CCPayment::pay(std::string productId, std::string productName, std::string productDesc, float productMoney, int chargePoint, std::string IAPId)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* productIdString = [NSString stringWithUTF8String:productId.c_str()];
		NSString* productNameString = [NSString stringWithUTF8String:productName.c_str()];
		NSString* productDescString = [NSString stringWithUTF8String:productDesc.c_str()];
		NSNumber* productMoneyString = [NSNumber numberWithFloat:productMoney];
		NSNumber* chargePointString = [NSNumber numberWithInt:chargePoint];
		NSString* IAPIdString = [NSString stringWithUTF8String:IAPId.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:productIdString,@"ProductId",productNameString,@"ProductName",productDescString,@"ProductDesc",productMoneyString,@"ProductMoney",chargePointString,@"ChargePoint",IAPIdString,@"IAPId",nil];
		[center postNotificationName:_TYPED_COCOS2D_START_PAYMENT_EVENT_NAME_ object:nil userInfo:dict];
	}

	void CCPayment::verify(std::string IAPId)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* textString = [NSString stringWithUTF8String:IAPId.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObject:textString forKey:@"IAPId"];
		[center postNotificationName:_TYPED_COCOS2D_VERIFY_PAYMENT_EVENT_NAME_ object:nil userInfo:dict];
	}

	void CCPayment::end()
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
		[center postNotificationName:_TYPED_COCOS2D_END_PAYMENT_EVENT_NAME_ object:nil];
	}

	void CCPayment::onServerSureOrder(std::string productId,std::string productName,float productMoney,std::string IAPId)
	{
		NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	
		NSString* productIdString = [NSString stringWithUTF8String:productId.c_str()];
		NSString* productNameString = [NSString stringWithUTF8String:productName.c_str()];
		NSNumber* productMoneyString = [NSNumber numberWithFloat:productMoney];
		NSString* IAPIdString = [NSString stringWithUTF8String:IAPId.c_str()];
		NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:productIdString,@"ProductId",productNameString,@"ProductName",productMoneyString,@"ProductMoney",IAPIdString,@"IAPId",nil];
		[center postNotificationName:_TYPED_COCOS2D_SERVERSUREORDER_PAYMENT_EVENT_NAME_ object:nil userInfo:dict];
	}

	void CCPayment::onPayFailed(std::string IAPId, std::string error)
	{
		if (m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->onPayFailed(IAPId, error);
	}

	void CCPayment::onPaySuccess(std::string Id, std::string transactionId, std::string transactionReceipt)
	{
		if (m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->onPaySuccess(Id, transactionId, transactionReceipt);
	}

	void CCPayment::onVerifyFailed(std::string IAPId, std::string error)
	{
		if (m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->onVerifyFailed(IAPId, error);
	}

	void CCPayment::onVerifySuccess(std::string IAPId)
	{
		if (m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->onVerifySuccess(IAPId);
	}

	void CCPayment::onRestoreSuccess(std::string Id)
	{
		if (m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->onRestoreSuccess(Id);
	}

	void CCPayment::insertPayment(std::string productId,std::string transactionId)
	{
		if (m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->insertPayment(productId, transactionId);
	}

} // end of namespace cococs2d

