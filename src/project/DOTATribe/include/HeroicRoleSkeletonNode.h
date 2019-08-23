//Name£ºHeroicRoleSkletonNode
//Function£º½ÇÉ«¹Ç÷À½áµã
//Author:	Johny

#ifndef   _TODAOTRIBE_HEROICROLESKELETONNODE_H
#define   _TODAOTRIBE_HEROICROLESKELETONNODE_H

#include "cocos2d.h"
#include  "../../extensions/spine/spine-cocos2dx.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class HeroicRoleSkeletonNode
{
private:
	cocos2d::extension::CCSkeletonAnimation* HeroicSkeleton;
	cocos2d::extension::CCSkeletonAnimation* HeroicEffectSkeletonUp;
	cocos2d::extension::CCSkeletonAnimation* HeroicEffectSkeletonDown;


public:
	HeroicRoleSkeletonNode();
	~HeroicRoleSkeletonNode();
	virtual bool init (const char* skeletonDataFile,
						const char* atlasFile,
						const char* effectDataFileUp = NULL,
						const char* effectAtlasFileUp = NULL,
						const char* effectDataFileDown = NULL,
						const char* effectAtlasFileDown = NULL,
						float scale = 1);
	virtual void update (float deltaTime);
	cocos2d::extension::CCSkeletonAnimation* GetSkeletonNode(){return HeroicSkeleton;}
	cocos2d::extension::CCSkeletonAnimation* GetEffectNodeUp(){return HeroicEffectSkeletonUp;}
	cocos2d::extension::CCSkeletonAnimation* GetEffectNodeDown(){return HeroicEffectSkeletonDown;}
};

#endif 