#include "CCSingleLineLabelTTF.h"
#include "misc_nodes/CCRenderTexture.h"
#include "platform/CCImage.h"
#include "richtext/CCRichTextLoader.h"
#include "textures/CCTextureCache.h"
#include "sprite_nodes/CCSprite.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCAnimation.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
using namespace cocos2d;


CCSingleLineLabelTTF::CCSingleLineLabelTTF()
{
	m_hAlignment = kCCTextAlignmentCenter;
	m_vAlignment = kCCVerticalTextAlignmentCenter;
}

CCSingleLineLabelTTF::~CCSingleLineLabelTTF()
{

}

CCSingleLineLabelTTF * CCSingleLineLabelTTF::create()
{
	CCSingleLineLabelTTF * pRet = new CCSingleLineLabelTTF();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void CCSingleLineLabelTTF::setAnchorPoint(const CCPoint& anchor)
{
	CCPoint temp = anchor;
	if (m_hAlignment == kCCTextAlignmentLeft)
		temp.x = 0.0f;
	else if (m_hAlignment == kCCTextAlignmentCenter)
		temp.x = 0.5f;
	else if (m_hAlignment == kCCTextAlignmentRight)
		temp.x = 1.0f;
	
	CCLabelTTF::setAnchorPoint(temp);
}

bool CCSingleLineLabelTTF::updateTexture()
{
	// 删除附加的所有富文本文字节点
	std::list<CCNode*>::iterator iter2   = m_RichLabelList.begin();
	std::list<CCNode*>::iterator iter2_e = m_RichLabelList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		this->removeChild(*iter2, true);
	}
	m_RichLabelList.clear();

	// 删除附加的动画节点
	iter2   = m_AniSpriteList.begin();
	iter2_e = m_AniSpriteList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		this->removeChild(*iter2, true);
	}
	m_AniSpriteList.clear();

	if (m_RichTextList.size() > 1)
	{
		return updateSingleLineTexture();
	}

	return CCLabelTTF::updateTexture();
}
