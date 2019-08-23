#include "../include/UILayer.h"
#include "../include/LoggerSystem.h"


cyouUILayer::cyouUILayer()
{

}

cyouUILayer::~cyouUILayer()
{

}

void cyouUILayer::onEnter()
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getPriority(), true);
	this->setKeypadEnabled(true);

	cocos2d::CCLayer::onEnter();
}

void cyouUILayer::onExit()
{
	this->setKeypadEnabled(false);
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	cocos2d::CCLayer::onExit();
}	

bool cyouUILayer::ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	cocos2d::CCPoint touchLocation = touche->getLocation();
#if  0
	InputEvent inputEvent;
	inputEvent.mEventID = _TYPED_INPUT_EVENT_TOUCHBEGIN_;
	inputEvent.mXPos    = touchLocation.x;
	inputEvent.mYPos    = touchLocation.y;
	INPUTSYSTEM->AddInputEvent(inputEvent);
	LOGGERSYSTEM->LogTrace("cyouUILayer Touch Begin: xPos=%f, yPos=%f\n", inputEvent.mXPos, inputEvent.mYPos);
#endif
	return true;
}

void cyouUILayer::ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	cocos2d::CCPoint preTouchLocation = touche->getPreviousLocation();
	cocos2d::CCPoint touchLocation    = touche->getLocation();
#if 0
	InputEvent inputEvent;
	inputEvent.mEventID = _TYPED_INPUT_EVENT_TOUCHMOVE_;
	inputEvent.mXPos    = touchLocation.x;
	inputEvent.mYPos    = touchLocation.y;
	inputEvent.mPreXPos = preTouchLocation.x;
	inputEvent.mPreYPos = preTouchLocation.y;

	LOGGERSYSTEM->LogTrace("cyouUILayer Touch Move: xPos=%f, yPos=%f\n", inputEvent.mXPos, inputEvent.mYPos);
	INPUTSYSTEM->AddInputEvent(inputEvent);
#endif
}

void cyouUILayer::ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	cocos2d::CCPoint touchLocation = touche->getLocation();
#if 0
	InputEvent inputEvent;
	inputEvent.mEventID = _TYPED_INPUT_EVENT_TOUCHEND_;
	inputEvent.mXPos    = touchLocation.x;
	inputEvent.mYPos    = touchLocation.y;
	INPUTSYSTEM->AddInputEvent(inputEvent);
	LOGGERSYSTEM->LogTrace("cyouUILayer Touch End: xPos=%f, yPos=%f\n", inputEvent.mXPos, inputEvent.mYPos);
#endif
}

void cyouUILayer::ccTouchCancelled(cocos2d::CCTouch* touche, cocos2d::CCEvent* event)
{
	cocos2d::CCPoint touchLocation = touche->getLocation();
#if 0
	InputEvent inputEvent;
	inputEvent.mEventID = _TYPED_INPUT_EVENT_TOUCHEND_;
	inputEvent.mXPos    = touchLocation.x;
	inputEvent.mYPos    = touchLocation.y;
	INPUTSYSTEM->AddInputEvent(inputEvent);
	LOGGERSYSTEM->LogTrace("cyouUILayer Touch Cancel: xPos=%f, yPos=%f\n", inputEvent.mXPos, inputEvent.mYPos);
#endif
}

void cyouUILayer::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
#if 0
	InputEvent inputEvent;
	inputEvent.mEventID   = _TYPED_INPUT_EVENT_ACCELERATE_;
	inputEvent.mXPos      = (float)pAccelerationValue->x;
	inputEvent.mYPos      = (float)pAccelerationValue->y;
	inputEvent.mZPos      = (float)pAccelerationValue->z;
	inputEvent.mTimeStamp = pAccelerationValue->timestamp;
	INPUTSYSTEM->AddInputEvent(inputEvent);
	LOGGERSYSTEM->LogTrace("cyouUILayer Accelerate: xPos=%f, yPos=%f, zPos=%f, timestamp=%f\n", inputEvent.mXPos, inputEvent.mYPos, inputEvent.mZPos, inputEvent.mTimeStamp);
#endif
}

void cyouUILayer::keyBackClicked()
{
#if 0
	InputEvent inputEvent;
	inputEvent.mEventID = _TYPED_INPUT_EVENT_KEY_BACK_CLICKED_;
	INPUTSYSTEM->AddInputEvent(inputEvent);
	LOGGERSYSTEM->LogTrace("cyouUILayer: key back clicked\n");
#endif
}

void cyouUILayer::keyMenuClicked()
{
#if 0
	InputEvent inputEvent;
	inputEvent.mEventID = _TYPED_INPUT_EVENT_KEY_MENU_CLICKED_;
	INPUTSYSTEM->AddInputEvent(inputEvent);
	LOGGERSYSTEM->LogTrace("cyouUILayer: key menu clicked\n");
#endif
}
