//name:FAnimationButton
//function:带播放动画的按钮
//author:fangjun
//date:20131206

#include "../include/FAnimationButton.h"
#include "../include/NFControlsManager.h"
#include "../include/EngineSystem.h"
#include "../include/ProfSystem.h"

FAnimationButton* FAnimationButton::create(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite,cocos2d:: CCObject* target
	, cocos2d::SEL_MenuHandler selector)
{
	FAnimationButton * fa = new FAnimationButton();
	if(fa && fa->initWithNormalSprite(normalSprite, selectedSprite, NULL, target, selector))
	{
		fa->autorelease();
	}
	else
	{
		delete fa;
		fa = NULL;
	}

	return fa;
}


bool FAnimationButton::initWithNormalSprite(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCNode* disabledSprite
	, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector)
{
	if (CCMenuItemSprite::initWithNormalSprite(normalSprite,selectedSprite,disabledSprite,target,selector))
	{
		if (normalSprite&&selectedSprite)
		{
			float scale_nor=normalSprite->getScale();
			float scale_sel=selectedSprite->getScale();
			const CCSize &sz_nor=normalSprite->getContentSize();
			const CCSize &sz_sel=selectedSprite->getContentSize();
			selectedSprite->setPosition(ccp((sz_nor.width*scale_nor-sz_sel.width*scale_sel)/2,(sz_nor.height*scale_nor-sz_sel.height*scale_sel)/2));

		}
		return true;
	}
	return false;
}

FAnimationButton* FAnimationButton::create(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector)
{
	FAnimationButton* cc=new FAnimationButton();
	if (cc&&cc->initWithNormalImage(nor,sel,target,selector))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return NULL;
}

bool FAnimationButton::initWithNormalImage(const char* nor, const char* sel,cocos2d:: CCObject* target, cocos2d::SEL_MenuHandler selector){
	CCSprite* cc_nor=NULL;
	if (strcmp(nor,"0")!=0)
	{
		cc_nor=CCSprite::create();
		cc_nor->setProperty("File",nor);
	}
	CCSprite* cc_sel=NULL;
	if (strcmp(sel,"0")!=0)
	{
		cc_sel=CCSprite::create();
		cc_sel->setProperty("File",sel);
	}
	return initWithNormalSprite(cc_nor,cc_sel,NULL,target,selector);
}

void FAnimationButton::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	std::cout<<"effect call back"<<std::endl;
	m_bIsPlaying = false;

	if(m_pAnimationPlayNode)
	{
		m_pAnimationPlayNode->setVisible(false);
	}

	if(m_pAnimationEffectCallBack_Extra)
	{
		m_pAnimationEffectCallBack_Extra->EffectCallBackEventHandler(eventType, animationNode, ptr);
	}
}

void FAnimationButton::InitAnimation()
{
	if(m_pAnimationPlayNode == NULL)
		m_pAnimationPlayNode = cocos2d::CCSprite::create();

	this->addChild(m_pAnimationPlayNode);

}

void FAnimationButton::PlayAnimation()
{
	_BEGIN_PROF_CHUNK_("FAnimationButton::PlayAnimation()")

	if(m_bIsPlaying)
		return;

	if(m_iAnimationId <= 0)
		return;

	m_pAnimationPlayNode->setPosition(ccp(m_fAnimationPosX, m_fAnimationPosY));

	m_pAnimationFileData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(m_iAnimationId);

	m_pAnimation = EngineSystem::get_instance2()->GetAnimtionByName(m_pAnimationFileData->mAnimationName);

	m_pAnimationPlayNode->setDisplayFrameWithAnimationName(m_pAnimationFileData->mAnimationName, 0);
	m_pAnimationPlayNode->setScale(m_pAnimationFileData->mAnimationScale);
	m_pAnimationPlayNode->setVisible(false);

	if(m_pAnimation)
	{
		CCAnimationEffect * pAnimationEffect = CCAnimationEffect::create(m_pAnimationPlayNode, m_pAnimation, this);
		if(pAnimationEffect)
		{
			m_pAnimationPlayNode->setVisible(true);
			m_pAnimationPlayNode->runAction(pAnimationEffect);

			m_bIsPlaying = true;
		}
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(m_pAnimationFileData->mAnimationUISoundID));
	_END_PROF_CHUNK_()
}

void FAnimationButton::StopAnimation()
{

}

void FAnimationButton::PlayTouchSound()
{
	NFC_playSoundByID(this->m_nSoundID);
}

bool FAPriorityMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !m_bEnabled)
	{
		return false;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem&&m_bEnabled)
	{
		m_eState = kCCMenuStateTrackingTouch;
		FAnimationButton* item=dynamic_cast<FAnimationButton*>(m_pSelectedItem);
		if(item)
		{
			item->PlayAnimation();
			item->PlayTouchSound();

			if(!m_bTreatAsTabMenu)
			{
				item->selected(true);
			}
		}
		else
		{
			if(!m_bTreatAsTabMenu)
			{
				m_pSelectedItem->selected(true);
			}
		}
		return true;
	}
	return false;
}

void FAPriorityMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem&&m_bEnabled)
	{
		FAnimationButton* item=dynamic_cast<FAnimationButton*>(m_pSelectedItem);
		if (item)
		{
			item->StopAnimation();
			if(!m_bTreatAsTabMenu)
			{
				item->unselected();
			}
		}	
		else
		{
			if(!m_bTreatAsTabMenu)
			{
				m_pSelectedItem->unselected();
			}
		}
		item->activate();
	}
	m_eState = kCCMenuStateWaiting;
}

void FAPriorityMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
	if (m_pSelectedItem&&m_bEnabled)
	{
		FAnimationButton* item=dynamic_cast<FAnimationButton*>(m_pSelectedItem);
		if (item)
		{
			item->StopAnimation();
			item->unselected();
		}
		else
		{
			m_pSelectedItem->unselected();
		}
	}
	m_eState = kCCMenuStateWaiting;
}

void FAPriorityMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		if(m_bTreatAsTabMenu)
		{
			m_pSelectedItem = currentItem;
		}
		else
		{
			if (m_pSelectedItem&&m_bEnabled)
			{
				FAnimationButton* item=dynamic_cast<FAnimationButton*>(m_pSelectedItem);
				if (item)
				{
					item->StopAnimation();
					item->unselected();
				}
				else
				{
					m_pSelectedItem->unselected();
				}
			}
			m_pSelectedItem = currentItem;
			if (m_pSelectedItem&&m_bEnabled)
			{
				FAnimationButton* item=dynamic_cast<FAnimationButton*>(m_pSelectedItem);
				if(item)
				{
					item->PlayAnimation();
					item->unselected();
				}
				else
				{
					m_pSelectedItem->selected(true);
				}
			}
		}
	}
}

void FAPriorityMenu::SetTreatAsTabMenu(bool treat)
{
	m_bTreatAsTabMenu = treat;
}

FrameAnimationNode::FrameAnimationNode()
{
	m_iTotalFrames = 0;
	m_iFpsInAnimation = 12;
	m_lFrameIntercepts.clear();
	m_pDelegate = NULL;
	m_iFrameCount = -1;
	m_bStartTick = false;
}

FrameAnimationNode * FrameAnimationNode::create(int totalFrames, int fpsInAnimation, int fpsInGame)
{
	FrameAnimationNode* node=new FrameAnimationNode;
	if (node)
	{
		node->autorelease();
		node->m_iFpsInAnimation = fpsInAnimation;
		node->m_iFpsInGame = fpsInGame;
		node->m_iFpsInAnimation > 0 ? node->m_iFpsInAnimation = node->m_iFpsInAnimation : node->m_iFpsInAnimation = 1;
		node->m_iTotalFrames = totalFrames * node->m_iFpsInGame / fpsInAnimation;

		return node;
	}
	delete node;
	node = NULL;
	return node;
}

void FrameAnimationNode::InsertFrameIntercept(int frameId)
{
	m_lFrameIntercepts.push_back(frameId);
}

void FrameAnimationNode::ClearAllIntercepts()
{
	m_lFrameIntercepts.clear();
}

void FrameAnimationNode::AddDelegate(FrameAnimationDelegate * dlg)
{
	m_pDelegate = dlg;
}

void FrameAnimationNode::Tick()
{
	if(m_bStartTick)
	{
		m_iFrameCount++;

		if(m_lFrameIntercepts.size() > 0 && m_lFrameIntercepts.front() * m_iFpsInGame / m_iFpsInAnimation == m_iFrameCount)
		{
			if(m_pDelegate)
			{
				m_pDelegate->FrameAnimationIntercept(m_lFrameIntercepts.front(), this);
				m_lFrameIntercepts.pop_front();
			}
		}

		if(m_iFrameCount >= m_iTotalFrames)
		{
			m_bStartTick = false;
			m_iFrameCount = -1;
			return;
		}
	}
	else
	{
		m_iFrameCount = -1;
	}
}

void FrameAnimationNode::Start()
{
	m_bStartTick = true;
	
	//重新排序拦截帧中的顺序
	m_lFrameIntercepts.sort();

}
