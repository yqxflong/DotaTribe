//Name£ºHeroicRoleSkletonNode
//Function£º½ÇÉ«¹Ç÷À½áµã
//Author:	Johny

#include <cocos2d.h>
#include  "../include/HeroicRoleSkeletonNode.h"
 

HeroicRoleSkeletonNode::HeroicRoleSkeletonNode()
{
	HeroicSkeleton = NULL;
	HeroicEffectSkeletonUp = NULL;
	HeroicEffectSkeletonDown = NULL;
}


HeroicRoleSkeletonNode::~HeroicRoleSkeletonNode()
{

}

bool HeroicRoleSkeletonNode::init(const char* skeletonDataFile,
								  const char* atlasFile,
								  const char* effectDataFileUp,
								  const char* effectAtlasFileUp,
								  const char* effectDataFileDown,
								  const char* effectAtlasFileDown,
								  float scale)
{
	HeroicSkeleton = CCSkeletonAnimation::createWithFile(skeletonDataFile,atlasFile,scale);
	std::string temp = "-1";
	if (temp.compare(effectDataFileUp) != 0 && temp.compare(effectAtlasFileUp) != 0)
	{
		HeroicEffectSkeletonUp = CCSkeletonAnimation::createWithFile(effectDataFileUp,effectAtlasFileUp,scale);
		HeroicEffectSkeletonUp->setVisible(false);
	}
	if (temp.compare(effectDataFileDown) != 0 && temp.compare(effectAtlasFileDown) != 0)
	{
		HeroicEffectSkeletonDown = CCSkeletonAnimation::createWithFile(effectDataFileDown,effectAtlasFileDown,scale);
		HeroicEffectSkeletonDown->setVisible(false);
	}
	if (HeroicSkeleton)
		return true;

	return false;
}

void HeroicRoleSkeletonNode::update(float deltaTime)
{

}