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
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
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

	}

	void CCPayment::destroy()
	{

	}

	bool CCPayment::isAvailable()
	{
		return true;
	}

	bool CCPayment::hasPayment(std::string IAPId)
	{
		return true;
	}

	void CCPayment::restorePayment()
	{
		return;
	}

	void CCPayment::deletePayment(std::string IAPId)
	{
		return ;
	}

	void CCPayment::pay(std::string productId, std::string productName, std::string productDesc, float productMoney, int chargePoint, std::string IAPId)
	{
		payJNI(productId.c_str(), productName.c_str(), productDesc.c_str(), productMoney, chargePoint, IAPId.c_str());
	}

	void CCPayment::verify(std::string IAPId)
	{
		verifyJNI(IAPId.c_str());
	}

	void CCPayment::end()
	{

	}

	void CCPayment::onServerSureOrder(std::string productId,std::string productName,float productMoney,std::string IAPId)
	{

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

	void CCPayment::onInsertPayment(std::string productId,std::string transactionId)
	{
		if(m_pPayDelegate == NULL)
			return;

		m_pPayDelegate->insertPayment(productId, transactionId);
	}

} // end of namespace cococs2d

