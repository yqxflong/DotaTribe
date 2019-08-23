#include  "../include/CSimpleActionSprite.h"
#include  "../include/PreCCMoveTo.h"



CSimpleActionSprite::CSimpleActionSprite()
{
	m_nActionType=0;
	m_vAttachParam.clear();
}
CSimpleActionSprite::~CSimpleActionSprite()
{
	m_nActionType=0;
	m_vAttachParam.clear();
	this->removeAllChildrenWithCleanup(true);
	cocos2d::CCSprite::stopAllActions();
}

CSimpleActionSprite *  CSimpleActionSprite::create(int actionType,std::vector<float> attachParam)
{
	CSimpleActionSprite* pSimpleActionSprite=new CSimpleActionSprite();
	if(pSimpleActionSprite&&pSimpleActionSprite->init(actionType,attachParam))
	{
		pSimpleActionSprite->autorelease();
		return pSimpleActionSprite;
	}
	CC_SAFE_DELETE(pSimpleActionSprite);
	return NULL;
}


bool  CSimpleActionSprite::init(int actionType,std::vector<float> attachParam)
{
	if(cocos2d::CCSprite::init())
	{ 
		m_nActionType=actionType;
		m_vAttachParam=attachParam;
		return true;
	}
	return false;
}
 
void  CSimpleActionSprite::PlayAction()
{
	runActionType();
	cocos2d::CCSprite::setVisible(true);
}
void  CSimpleActionSprite::StopAction()
{
	cocos2d::CCSprite::stopAllActions();
	size_t childCount=m_vChildArray.size();
	for(size_t childIndex=0;childIndex<childCount;childIndex++)
	{  
		m_vChildArray.at(childIndex)->stopAllActions();
		m_vChildArray.at(childIndex)->setPosition(m_vInitPosition.at(childIndex));
	} 
	setPosition(m_cInitPosition);
	cocos2d::CCSprite::setVisible(false);
}
 
void  CSimpleActionSprite::runActionType()
{
	switch(m_nActionType)
	{
	case _STANDBY_TYPE_:
		{
			break;
		}
	case _FLOAT_UP_AND_DOWN_TYPE_:
		{
			floatUpAndDonwAction();
			break;
		}
	case _FLOAT_LEFT_AND_RIGHT_TYPE_:
		{
			floatLeftAndRightAction();
			break;
		}
	default:
		break;
	}
}

void  CSimpleActionSprite::SetInitPosition(const cocos2d::CCPoint & position)
{ 
	m_vInitPosition.push_back(position);
	cocos2d::CCSprite::setPosition(position);
}
 
void  CSimpleActionSprite::floatUpAndDonwAction()
{  
	if(m_vChildArray.empty())
	{
		PreCCMoveTo * action_move=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(0).x,m_vInitPosition.at(0).y+m_vAttachParam.at(1)));
		PreCCMoveTo * action_reverse=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(0).x,m_vInitPosition.at(0).y-m_vAttachParam.at(1)));
		cocos2d::CCSprite::runAction(cocos2d::CCRepeatForever::create(cocos2d::CCSequence::createWithTwoActions(action_move,action_reverse)));
	}
	else
	{
		size_t childCount=m_vChildArray.size();
		for(size_t childIndex=0;childIndex<childCount;childIndex++)
		{
			PreCCMoveTo * action_move=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(childIndex).x,m_vInitPosition.at(childIndex).y+m_vAttachParam.at(1)));
			PreCCMoveTo * action_reverse=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(childIndex).x,m_vInitPosition.at(childIndex).y-m_vAttachParam.at(1)));
		    m_vChildArray.at(childIndex)->runAction(cocos2d::CCRepeatForever::create(cocos2d::CCSequence::createWithTwoActions(action_move,action_reverse)));
		}
	}
}

void  CSimpleActionSprite::floatLeftAndRightAction(){
	if(m_vChildArray.empty())
	{
		PreCCMoveTo * action_move=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(0).x-m_vAttachParam.at(1),m_vInitPosition.at(0).y));
		PreCCMoveTo * action_reverse=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(0).x+m_vAttachParam.at(1),m_vInitPosition.at(0).y));
		cocos2d::CCSprite::runAction(cocos2d::CCRepeatForever::create(cocos2d::CCSequence::createWithTwoActions(action_move,action_reverse)));
	}
	else
	{
		size_t childCount=m_vChildArray.size();
		for(size_t childIndex=0;childIndex<childCount;childIndex++)
		{
			PreCCMoveTo * action_move=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(0).x-m_vAttachParam.at(1),m_vInitPosition.at(0).y));
			PreCCMoveTo * action_reverse=PreCCMoveTo::create(m_vAttachParam.at(0),ccp(m_vInitPosition.at(0).x+m_vAttachParam.at(1),m_vInitPosition.at(0).y));
			m_vChildArray.at(childIndex)->runAction(cocos2d::CCRepeatForever::create(cocos2d::CCSequence::createWithTwoActions(action_move,action_reverse)));
		}
	}
}

 
void CSimpleActionSprite::addChild(cocos2d::CCNode * child)
{ 
	m_vChildArray.push_back(child);
	m_vInitPosition.push_back(child->getPosition());
	cocos2d::CCSprite::addChild(child);
}
 