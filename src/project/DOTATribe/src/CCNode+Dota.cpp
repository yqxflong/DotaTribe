#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include "../include/LoggerSystem.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

void CCNode::setProperty(std::string name, std::string value, void* pPtr){
	if (name.compare("File")==0){
		//@判断是否为打包贴图的key
		if (value.find_last_of("/")==-1){
			CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(value.c_str());
			if (!frame){
				LOGGERSYSTEM->LogInfo("[ERROR]Can not find frame: %s",value.c_str());
				assert(frame!=NULL);
			}
			_setFrame(frame);
		}else{
			CCTexture2D* tex=CCTextureCache::sharedTextureCache()->addImage(value.c_str());
			if (!tex){
				LOGGERSYSTEM->LogInfo("[ERROR]Can not find file: %s",value.c_str());
				assert(tex!=NULL);
			}
			_setTexture(tex);
		}
	}
}

//@CCSprite,CC9ScaleSprite
void CCNode::_setTexture(CCTexture2D* tex){
	CCSprite* cc=dynamic_cast<CCSprite*>(this);
	if (cc!=NULL)
	{
		cc->setTexture(tex);
		cc->setTextureRect(CCRectMake(0,0,tex->getContentSize().width,tex->getContentSize().height));
	}else{
		CCScale9Sprite* cc9=dynamic_cast<CCScale9Sprite*>(this);
		if (cc9!=NULL)
		{
			CCSpriteFrame* frame=CCSpriteFrame::createWithTexture(tex,CCRectMake(0,0,tex->getContentSize().width,tex->getContentSize().height));
			cc9->setSpriteFrame(frame);
		}
	}
}

//@CCSprite,CC9ScaleSprite
void CCNode::_setFrame(CCSpriteFrame* frame){
	CCSprite* cc=dynamic_cast<CCSprite*>(this);
	if (cc!=NULL)
	{
		cc->setDisplayFrame(frame);
	}else{
		CCScale9Sprite* cc9=dynamic_cast<CCScale9Sprite*>(this);
		if (cc9!=NULL)
		{
			cc9->setSpriteFrame(frame);
		}
	}
}