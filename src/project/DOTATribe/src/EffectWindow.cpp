//Name：EffectWindow
//Function：用于展现效果的窗口，暂时用于获得物品时
//Written By：尹强

#include "../include/EffectWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
//
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/EffectDataHandler.h"
#include "../include/ArtFontLabelBatchNode.h"
#include <list>
//
static float TIME_DIS_CUR=0.0f;
static float TIME_DIS=0.0f;

using namespace std;

USING_NS_CC;

EffectWindow::EffectWindow()
:m_pRoot(0)
{
	m_WindowType   = _TYPED_WINDOW_EFFECTWINDOW_;
	m_bModelWindow = true;
}

bool EffectWindow::Init()
{
	RegisterEvent(_TYPEF_EVENT_SHOW_EFFECTWINDOW_);
	RegisterEvent(_TYPEF_EVENT_HIDE_EFFECTWINDOW_, true);
	EFFECTDATAHANDLER->OpenEffectHandler();
	return IWindow::Init();
}

void EffectWindow::_initLayout(){
	m_pRoot= m_pRootNode;
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEFFECTWINDOW,m_pRoot);
	TIME_DIS=(float)(ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_GETITEM_EFFECT_DIS)*1.0/1000);
}

bool EffectWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		return true;
	} 
	while (false);

	return false;
}

void EffectWindow::Tick()
{
	//轮询，发现需要展示的效果
	if(m_pRootNode->isVisible())
	{
		if (TIME_DIS_CUR>=TIME_DIS)
		{
			TIME_DIS_CUR=0.0f;
			list<EffectData*>::iterator it=EFFECTDATAHANDLER->effectList_.begin();
			list<EffectData*>::iterator it_end=EFFECTDATAHANDLER->effectList_.end();
			if (it!=it_end){
				EffectData* dd=*it;
				CCNode* cc=CCNode::create();
				cc->setPositionY(dd->beginPosY_);
				m_pRoot->addChild(cc);
				_createICON(cc,dd);
				_createLabel(cc,dd);
				_showEffect(cc,dd);
				delete *it;
				EFFECTDATAHANDLER->effectList_.erase(it);
			}
		}
		TIME_DIS_CUR+=(float)(1.0/30);
	} 
	IWindow::Tick();
}

void EffectWindow::_createICON(cocos2d::CCNode* effectNode,EffectData* dd){
	CCNode* node=m_pRoot->getChildByTag(udICON);
	CCSprite* cc=CCSprite::create();
	cc->setProperty("File",dd->iconPath_);
	cc->setAnchorPoint(node->getAnchorPoint());
	cc->setPositionX(node->getPositionX());
	effectNode->addChild(cc);
}

void EffectWindow::_createLabel(cocos2d::CCNode* effectNode,EffectData* dd){
	CCNode* node=m_pRoot->getChildByTag(udNUMLABEL);
	ArtFontLabelBatchNode* Label=ArtFontLabelBatchNode::CreateArtFontWithArray(dd->vecFonts_);
	assert(Label!=NULL);
	Label->SetPosition(ccp(node->getPositionX(),0));
	Label->GetBatchNodeLabel()->setScale(dd->scale_);
	effectNode->addChild(Label->GetBatchNodeLabel()); 
	delete Label;
	Label = NULL;
}

void EffectWindow::_createBJLabel(cocos2d::CCNode* effectNode,EffectData* dd){
	CCNode* node=m_pRoot->getChildByTag(udNUMBJLABEL);
	ArtFontLabelBatchNode* Label=ArtFontLabelBatchNode::CreateArtFontWithArray(dd->vecFonts_BJ_);
	Label->SetPosition(ccp(node->getPositionX(),0));
	Label->GetBatchNodeLabel()->setScale(dd->scale_);
	effectNode->addChild(Label->GetBatchNodeLabel());
	delete Label;
	Label = NULL;
}

void EffectWindow::_showEffect(cocos2d::CCNode* effectNode,EffectData* dd){
	CCMoveTo* moveto=CCMoveTo::create(dd->animaTime_,ccp(effectNode->getPositionX(),dd->endPosY_));
	CCCallFuncN* callfunc=CCCallFuncN::create(this,callfuncN_selector(EffectWindow::On_Animation_CallBack));
	CCSequence* seq=CCSequence::createWithTwoActions(moveto,callfunc);
	effectNode->runAction(seq);
	//渐隐效果
	CCDelayTime* delay=CCDelayTime::create(dd->fadeoutStartTime_);
	float fadeouttime=dd->animaTime_-dd->fadeoutStartTime_;
	if(fadeouttime>0){
		CCFadeOut* fadeout=CCFadeOut::create(fadeouttime);
		CCSequence* seq2=CCSequence::createWithTwoActions(delay,fadeout);
		effectNode->runAction(seq2);
	}
}

void EffectWindow::Destroy()
{
	IWindow::Destroy();
}

void EffectWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPEF_EVENT_SHOW_EFFECTWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPEF_EVENT_HIDE_EFFECTWINDOW_)
	{
		Destroy();
	}
}

void EffectWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if(!m_pRootNode->isVisible())
	{
		_initLayout();
		Show(true);
	}
}

void EffectWindow::On_Animation_CallBack(cocos2d::CCNode* pSender){
	pSender->removeAllChildrenWithCleanup(true);
	pSender->removeFromParentAndCleanup(true);
}
