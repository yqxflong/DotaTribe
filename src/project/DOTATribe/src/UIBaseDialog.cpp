/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:    基类对话框  (自带遮罩层)
//date:   2013/07/21
///////////////////////////////////////////////// 
#include  "../include/UIBaseDialog.h"
#include  "../include/InputCommand.h"
  

UIBaseDialog::UIBaseDialog()
{
   priority_=_UIBASEDIALOG_NORMAL_PRIORITY_;
   unCloseRect_=CCRectZero;
   markColor_.r=0;
   markColor_.g=0;
   markColor_.b=0;
   opacity_=170;
   pDelegate_=0;
}
 
UIBaseDialog::~UIBaseDialog()
{
  
}

UIBaseDialog * UIBaseDialog::createUIBaseDialog(int priority/* =_UIBASEDIALOG_NORMAL_PRIORITY_ */)
{
	UIBaseDialog * pUIBaseDialog=new UIBaseDialog();
	if(pUIBaseDialog&&pUIBaseDialog->initUIBaseDialog(priority))
	{
		pUIBaseDialog->autorelease();
		return pUIBaseDialog;
	}
	if(pUIBaseDialog!=NULL)
	{ 
		delete pUIBaseDialog;
		pUIBaseDialog=NULL;
	}
	return NULL;
}

 
bool  UIBaseDialog::initUIBaseDialog(int priority)
{ 
	if(CCLayerMask::init())
	{
		priority_=priority;
		setSwallowsTouches(true);
		setPriorityFromParent(false);
		setPriority(priority);
		setColor(markColor_);
		setOpacity(opacity_);
		return true;
	}
    return false;
}
  

void   UIBaseDialog::setTouchUnCloseRect(cocos2d::CCRect rect)
{
    unCloseRect_=rect;
}


void   UIBaseDialog::setDelegatePrototy(UIBaseDialogProtory * delegatePtr)
{
    pDelegate_=delegatePtr;
}


bool   UIBaseDialog::checkIsTouchInUnClose(cocos2d::CCPoint touchPoint)
{ 
	if(unCloseRect_.size.width==0||unCloseRect_.size.height==0)
	return true; 

	if(touchPoint.x>=unCloseRect_.origin.x&&touchPoint.x<=unCloseRect_.origin.x+unCloseRect_.size.width&&touchPoint.y>=unCloseRect_.origin.y&&touchPoint.y<=unCloseRect_.origin.y+unCloseRect_.size.height)
	{
		return true;
	}
	return false;
  
}

void  UIBaseDialog::setDialogBgColor(ccColor3B  & color)
{
	setColor(color);
}

void  UIBaseDialog::setDialogOpacity(GLubyte & opacity)
{
	setOpacity(opacity);
}

bool UIBaseDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (this->isVisible())
	{
		CCPoint touchLocation = pTouch->getLocationInView();
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
		CCPoint local = this->convertToNodeSpace(touchLocation);
		CCRect r = this->rect();
		r.origin = CCPointZero;
		if (r.containsPoint(local))
		{
           if(!checkIsTouchInUnClose(touchLocation))
		   {
			   //关闭对话框
			    if(pDelegate_!=NULL)
				{
					pDelegate_->BaseDialogCallBackHandler(_TYPED_INPUT_COMMAND_BASEDIALOG_CLOSE_,NULL);
				}
			    return true;
		   }
		}
		return true;
	}
	return false;
}

void UIBaseDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
   
}

void UIBaseDialog::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void UIBaseDialog::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

} 

cocos2d::CCRect  UIBaseDialog::rect()
{
	return CCRectMake( m_obPosition.x - m_obContentSize.width * m_obAnchorPoint.x, 
		m_obPosition.y - m_obContentSize.height * m_obAnchorPoint.y,
		m_obContentSize.width, m_obContentSize.height);
}
