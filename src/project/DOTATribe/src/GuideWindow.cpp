//Name：GuideWindow
//Function：新手引导窗口
//Written By：尹强

#include <cocos2d.h>
#include "../include/GuideWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/ClientConstDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/GuideSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/SysLangDataManager.h"
#include <string>
#include "../include/MessageBoxWindow.h"
#include "../include/DOTATribeApp.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;


GuideWindow::GuideWindow()
	: IWindow()
	,m_pRoot(0)
	,m_pArrow(0)
	,m_pThumb(0)
	,m_pThumb_shadow(0)
{
	m_WindowType   = _TYPED_WINDOW_GUIDE_;
	m_bModelWindow = true;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_HIGH_;
	m_pArrow=NULL;
}

GuideWindow::~GuideWindow()
{

}

bool  GuideWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_GUIDEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_GUIDEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_NEXT_GUIDESTEP_,true);
	RegisterEvent(_TYPED_EVENT_UPDATE_UI_TEXT_, true);

	return IWindow::Init();
}

bool  GuideWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		m_pRoot=m_pRootNode;
		//重新注册触摸优先级
		if (m_bModelWindow)
		{
			m_pRoot->setPriorityFromParent(false);
			m_pRoot->setPriority(kPRIORITYGUIDEWINDOW);
			NFC_ReRegisterTouchPriority(this,m_pRoot->getPriority(),true);
		}
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGUIDEWINDOW,m_pRoot);
			
		CCMenu* menu =(CCMenu*)m_pRoot->getChildByTag(kSKIP);
		CMenuItemSprite* cc =(CMenuItemSprite*)menu->getChildByTag(0);
		cc->setTarget(this, menu_selector(GuideWindow::OnFinishGuideButtonClick));
		//将文字放到文字背景上
		CCNode* textbg=m_pRoot->getChildByTag(kBOARD);
		CCLabelTTF* text=(CCLabelTTF*)m_pRoot->getChildByTag(kTEXT);
		text->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		text->removeFromParent();
		textbg->addChild(text);
	
		return true;
	} 
	while (false);

	return false;
}

void  GuideWindow::Tick()
{

}

void  GuideWindow::Destroy()
{
	_clearArrow();
	IWindow::Destroy();
}

void  GuideWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_GUIDEWINDOW_)
	{
		OnShowGuideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_GUIDEWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_NEXT_GUIDESTEP_)
	{
		OnNextGuideStepEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_UI_TEXT_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
}

bool GuideWindow::ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	int guideType  = GUIDESYSTEM->GetModuleID();
	int guideIndex = GUIDESYSTEM->GetStepID();
	GuideItemData* pGuideStep = GuideDataManager::get_instance2()->GetGuideStepInfoByIndex(guideType, guideIndex);
	if (pGuideStep == NULL)
		return true;

	if (pGuideStep->mClickAnyWhereToNextStep)
		return true;

	cocos2d::CCPoint touchLocation = touche->getLocation();
	if (touchLocation.x>=pGuideStep->mMaskStartXPos && touchLocation.x<=pGuideStep->mMaskEndXPos
		&& touchLocation.y>=pGuideStep->mMaskStartYPos && touchLocation.y<=pGuideStep->mMaskEndYPos)
	{
		//GUIDESYSTEM->Next();
		return false;
	}

	return true;
}

void GuideWindow::ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	int guideType  = GUIDESYSTEM->GetModuleID();
	int guideIndex = GUIDESYSTEM->GetStepID();
	GuideItemData* pGuideStep = GuideDataManager::get_instance2()->GetGuideStepInfoByIndex(guideType, guideIndex);
	if (pGuideStep == NULL)
		return ;

}

void GuideWindow::ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	int guideType  = GUIDESYSTEM->GetModuleID();
	int guideIndex = GUIDESYSTEM->GetStepID();
	GuideItemData* pGuideStep = GuideDataManager::get_instance2()->GetGuideStepInfoByIndex(guideType, guideIndex);
	if (pGuideStep == NULL)
		return ;

	if (pGuideStep->mClickAnyWhereToNextStep)
	{
		GUIDESYSTEM->Next();
		return ;
	}
}

void GuideWindow::ccTouchCancel(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{

}

//Time Label Call Back
void GuideWindow::TimerEventHandler(int eventType,std::string attachParam){
	NFC_setEnabledForMenuItem(kSKIP,m_pRoot,true);
	NFC_setNodeVisable(kTIMELABEL,m_pRoot,false);
}

void GuideWindow::OnShowGuideWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	_checkSetting();
}

void GuideWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{
	
}

void GuideWindow::OnNextGuideStepEventHandler(std::list<std::string>& paramList)
{
	_checkSetting();
}

void GuideWindow::OnFinishGuideButtonClick(cocos2d::CCObject* pSender)
{
	string str=SysLangDataManager::get_instance2()->GetSysLangById(573);
	NFC_showMessageBox(kGUIDESKIP,str);
}

	/*
		根据数据表设置当前步骤界面情况
		每一个步骤都会走这里，重新加载界面
	*/
void GuideWindow::_checkSetting(){
	float height = (float)DOTATribeApp::get_instance2()->GetAppHeight();
	float width = (float)DOTATribeApp::get_instance2()->GetAppWidth();

	// 设置Mask块
	cocos2d::CCLayerColor* pLeftLayer   = (cocos2d::CCLayerColor*)m_pRoot->getChildByTag(kMASK1);
	cocos2d::CCLayerColor* pTopLayer    = (cocos2d::CCLayerColor*)m_pRoot->getChildByTag(kMASK2);
	cocos2d::CCLayerColor* pRightLayer  =  (cocos2d::CCLayerColor*)m_pRoot->getChildByTag(kMASK3);
	cocos2d::CCLayerColor* pBottomLayer = (cocos2d::CCLayerColor*)m_pRoot->getChildByTag(kMASK4);

	int guideType  = GUIDESYSTEM->GetModuleID();
	int guideIndex = GUIDESYSTEM->GetStepID();
	GuideItemData* pGuideStep = GuideDataManager::get_instance2()->GetGuideStepInfoByIndex(guideType, guideIndex);
	if (pGuideStep == NULL)
		return;

	pLeftLayer->setOpacity(pGuideStep->mMaskAlphaColor);
	pLeftLayer->changeWidthAndHeight(pGuideStep->mMaskStartXPos, height);
	pLeftLayer->setPosition(0, 0);

	pRightLayer->setOpacity(pGuideStep->mMaskAlphaColor);
	pRightLayer->changeWidthAndHeight(width-pGuideStep->mMaskEndXPos, height);
	pRightLayer->setPosition(pGuideStep->mMaskEndXPos, 0);

	pTopLayer->setOpacity(pGuideStep->mMaskAlphaColor);
	pTopLayer->changeWidthAndHeight(pGuideStep->mMaskEndXPos-pGuideStep->mMaskStartXPos, height-pGuideStep->mMaskEndYPos);
	pTopLayer->setPosition(pGuideStep->mMaskStartXPos, pGuideStep->mMaskEndYPos);

	pBottomLayer->setOpacity(pGuideStep->mMaskAlphaColor);
	pBottomLayer->changeWidthAndHeight(pGuideStep->mMaskEndXPos-pGuideStep->mMaskStartXPos, pGuideStep->mMaskStartYPos);
	pBottomLayer->setPosition(pGuideStep->mMaskStartXPos, 0);

	// 是否显示引导员图片
	CCSprite* pGuideSprite = (cocos2d::CCSprite*)m_pRoot->getChildByTag(kNPC);
	if (pGuideStep->mShowGuider)
	{
		pGuideSprite->setVisible(true);
		pGuideSprite->setPositionX(pGuideStep->mGuiderXPos);
		pGuideSprite->setPositionY(pGuideStep->mGuiderYPos);
	}
	else
	{
		pGuideSprite->setVisible(false);
	}

	// 是否显示引导文字背景
	pGuideSprite = (cocos2d::CCSprite*)m_pRoot->getChildByTag(kBOARD);
	if (pGuideStep->mShowGuiderIcon)
	{
		pGuideSprite->setVisible(true);
		pGuideSprite->setPositionX(pGuideStep->mGuiderIconXPos);
		pGuideSprite->setPositionY(pGuideStep->mGuiderIconYPos);
		//文字描述
		NFC_setLabelString(kTEXT,pGuideSprite,pGuideStep->mTips.c_str());
	}
	else
	{
		pGuideSprite->setVisible(false);
	}

	// 是否显示引导箭头
	_setArrow(pGuideStep);

	_checkSkipButton(pGuideStep);
}

void GuideWindow::_clearArrow(){
	if(m_pArrow){ 
		m_pArrow->removeFromParentAndCleanup(true); 
		m_pArrow=NULL;
	}
	if(m_pThumb){ 
		m_pThumb->removeFromParentAndCleanup(true); 
		m_pThumb=NULL;
	}
	if(m_pThumb_shadow){ 
		m_pThumb_shadow->removeFromParentAndCleanup(true); 
		m_pThumb_shadow=NULL;
	}
}

/*
		显示箭头根据设置
	*/
void GuideWindow::_showArrowBySettings(int type,GuideItemData* guideData,CCNode* logicnode){
	//箭头
	CCPoint cp_before;
	if(m_pArrow){ 
		cp_before=m_pArrow->getPosition();
		m_pArrow->removeFromParentAndCleanup(true); 
	}
	m_pArrow = CCSkeletonAnimation::createWithFile(SPINE_GUIDE_ARROW_JSON,SPINE_GUIDE_ARROW_ALTAS);
	assert(m_pArrow!=NULL);
	m_pArrow->setRotation(guideData->mArrowRotation);
	m_pRoot->addChild(m_pArrow,logicnode->getZOrder());
	if (strcmp(guideData->mArrowOrder,SPINE_GUIDE_ARROW_MOVE)==0){
		m_pArrow->setAnimation(guideData->mArrowOrder,false);
		m_pArrow->setPosition(cp_before);
		CCMoveTo* moveto=CCMoveTo::create(1,ccp(guideData->mArrowXPos,guideData->mArrowYPos));
		CCCallFunc* aftermove=CCCallFunc::create(this,callfunc_selector(GuideWindow::CallBack_Arrow_Moveto));
		CCSequence* seq=CCSequence::createWithTwoActions(moveto,aftermove);
		m_pArrow->runAction(seq);
	}else{
		m_pArrow->setAnimation(guideData->mArrowOrder, true);
		m_pArrow->setPosition(ccp(guideData->mArrowXPos,guideData->mArrowYPos));
	}
	if (guideData->mFlipGuideArrow)
		m_pArrow->setRotationY(180);
}

void GuideWindow::_setArrow(GuideItemData* guideData){
	_clearArrow();
	CCNode* node=m_pRoot->getChildByTag(kARROW);
	if (guideData->mShowGuideArrow)
	{
		if(guideData->mArrowType==kARROW_NORMAL){
			_showArrowBySettings(kARROW_NORMAL,guideData,node);
		}else if(guideData->mArrowType==kARROW_THUMB){
			//手指滑动
			m_cpSrc_thumb=ccp(guideData->mArrowXPos,guideData->mArrowYPos);
			m_cpDst_thumb=ccp(guideData->mArrowDstX,guideData->mArrowDstY);
			//
			m_pThumb=CCSprite::create();
			m_pThumb->setProperty("File",GUIDE_THUMB_IMG);
			m_pThumb->setPosition(m_cpSrc_thumb);
			m_pRoot->addChild(m_pThumb,node->getZOrder()+1);
			m_pThumb_shadow=CCSprite::create();
			m_pThumb_shadow->setProperty("File",GUIDE_THUMB_VIRTUAL_IMG);
			m_pThumb_shadow->setVisible(false);
			m_pThumb_shadow->setPosition(m_cpDst_thumb);
			m_pRoot->addChild(m_pThumb_shadow,node->getZOrder());
			if (guideData->mFlipGuideArrow){
				m_pThumb->setRotationY(180);
				m_pThumb_shadow->setRotationY(180);
			}
			m_fThumbDuring=0.0;
			if (guideData->mGuideType==1&&guideData->mGuideIndex==5)
			{
				int during=CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_GUIDE_THUMB_EQUIP_DURING);
				m_fThumbDuring=(float)(during*1.0/1000);
			}else if(guideData->mGuideType==3&&guideData->mGuideIndex==4){
				int during=CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_GUIDE_THUMB_SKILL_DURING);
				m_fThumbDuring=(float)(during*1.0/1000);
			}
			_thumbAction();
		}else if(guideData->mArrowType==kARROW_SMALL){
			_showArrowBySettings(kARROW_SMALL,guideData,node);
		}
	}
}

void GuideWindow::_thumbAction(){
	CCMoveTo* moveto=CCMoveTo::create(m_fThumbDuring,m_cpDst_thumb);
	CCCallFunc* callfunc=CCCallFunc::create(this,callfunc_selector(GuideWindow::CallBack_Thumb_ReachDST));
	CCSequence* seq=CCSequence::createWithTwoActions(moveto,callfunc);
	m_pThumb->runAction(seq);
}

//检查跳过按钮
void GuideWindow::_checkSkipButton(GuideItemData* data){
	// 是否显示跳过按钮
	CCMenu* menu = (cocos2d::CCMenu*)m_pRoot->getChildByTag(kSKIP);
	CTimeLabel* lb=(CTimeLabel*)m_pRoot->getChildByTag(kTIMELABEL);
	lb->StopTimer(true);
	if (data->mShowFinishButton)
	{
		menu->setVisible(true);
		menu->setPositionX(data->mFinishButtonXPos);
		menu->setPositionY(data->mFinishButtonYPos);
		//按钮于3秒内置灰
		CMenuItemSprite* item=(CMenuItemSprite*)menu->getChildByTag(0);
		item->setEnabled(false);
		//设置倒计时
		lb->setVisible(true);
		lb->StartTimer(3);
		lb->setTimerEventDelegate(this);
	}
	else
	{
		menu->setVisible(false);
		lb->setVisible(false);
	}


}

	/*
		箭头移动完之后
	*/
void GuideWindow::CallBack_Arrow_Moveto(){
	m_pArrow->setAnimation(SPINE_GUIDE_ARROW_DAIJI,true);
}

void GuideWindow::CallBack_Thumb_ReachDST(){
	m_pThumb_shadow->setVisible(true);
	m_pThumb->setPosition(m_cpSrc_thumb);
	_thumbAction();
}