#include "CCMultiLineLabelTTF.h"
#include "misc_nodes/CCRenderTexture.h"
#include "platform/CCImage.h"
#include "richtext/CCRichTextLoader.h"
#include "sprite_nodes/CCSprite.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCAnimation.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include <vector>
using namespace cocos2d;


/************************************************************************/
/* 解析UTF字符*/
/************************************************************************/
static std::vector<std::string> parse_utf8_string(std::string text)
{
	std::vector<std::string> temp;

	do 
	{
		if (text.length() <= 0)
			break;

		std::string::const_iterator begin = text.begin();
		std::string::const_iterator end   = text.end();
		while (begin != end)
		{
			unsigned char c = *begin;
			int n = 0;

			if ((c & 0x80) == 0)    
				n = 1;
			else if ((c & 0xE0) == 0xC0) 
				n = 2;
			else if ((c & 0xF0) == 0xE0) 
				n = 3;
			else if ((c & 0xF8) == 0xF0) 
				n = 4;
			else if ((c & 0xFC) == 0xF8) 
				n = 5;
			else if ((c & 0xFE) == 0xFC) 
				n = 6;
			else 
				break;

			if (end - begin < n) 
				break;

			std::string substring;
			substring += *begin;

			bool isError = false;
			for (int i=1; i<n; ++i)
			{
				if ((begin[i] & 0xC0) != 0x80) 
				{
					isError = true;
					break;
				}

				substring += begin[i];
			}

			if (isError)
				break;

			temp.push_back(substring);
			begin += n;
		}
	} 
	while (false);

	return temp;
}

/************************************************************************/
/* 获取指定长度的字符*/
/************************************************************************/
static std::string _get_rich_text_(std::vector<std::string>& myList, int start, int end)
{
	std::string text;
	for (int i=start; i<end; i++)
	{
		text += myList[i];
	}

	return text;
}

/************************************************************************/
/* 二分查找法，找到最合适的显示字符串*/
/************************************************************************/
static bool _richtext_split_(std::string text, float width, float height, CCImage::ETextAlign eAlign, std::string fontName, float fontSize, int& bytesNumber)
{
	std::vector<std::string> wordList = parse_utf8_string(text);
	int last  = wordList.size();
	int start = 0;
	int end   = (wordList.size())/2;

	do 
	{
		std::string text = _get_rich_text_(wordList, 0, end);
		if (start == end)
		{
			bytesNumber = text.size();
			return true;
		}

		CCImage image;
		image.getStringSize(text.c_str(), 0, 0, eAlign, fontName.c_str(), fontSize);
		if (image.getWidth() <= width)
		{
			start = end;
			end   = (last-end)/2+end;
		}
		else
		{
			last = end-1;
			end  = (last-start)/2+start;
		}
	}
	while (true);

	bytesNumber = 0;
	return true;
}

CCMultiLineLabelTTF::CCMultiLineLabelTTF()
{
	m_hAlignment = kCCTextAlignmentCenter;
	m_vAlignment = kCCVerticalTextAlignmentCenter;
}

CCMultiLineLabelTTF::~CCMultiLineLabelTTF()
{

}

CCMultiLineLabelTTF * CCMultiLineLabelTTF::create()
{
	CCMultiLineLabelTTF * pRet = new CCMultiLineLabelTTF();
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

CCMultiLineLabelTTF * CCMultiLineLabelTTF::create(float width)
{
	CCMultiLineLabelTTF * pRet = create();
	if (pRet == NULL)
		return NULL;
	
	pRet->setDimensions(CCSizeMake(width, 0.0f));
	return pRet;
}

CCMultiLineLabelTTF * CCMultiLineLabelTTF::create(float width, float height)
{
	CCMultiLineLabelTTF * pRet = create();
	if (pRet == NULL)
		return NULL;

	pRet->setDimensions(CCSizeMake(width, height));
	return pRet;
}

void CCMultiLineLabelTTF::setAnchorPoint(const CCPoint& anchor)
{
	CCPoint temp = anchor;
	if (m_hAlignment == kCCTextAlignmentLeft)
		temp.x = 0.0f;
	else if (m_hAlignment == kCCTextAlignmentCenter)
		temp.x = 0.5f;
	else if (m_hAlignment == kCCTextAlignmentRight)
		temp.x = 1.0f;

	if (m_vAlignment == kCCVerticalTextAlignmentTop)
		temp.y = 1.0f;
	else if (m_vAlignment == kCCVerticalTextAlignmentCenter)
		temp.y = 0.5f;
	else if (m_vAlignment == kCCVerticalTextAlignmentBottom)
		temp.y = 0.0f;

	CCLabelTTF::setAnchorPoint(temp);
}

bool CCMultiLineLabelTTF::updateTexture()
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

	if (m_tDimensions.width==0.0f && m_tDimensions.height==0.0f)
		m_tDimensions.width = 500.0f;

	if (m_RichTextList.size() > 1)
	{
		return updateMultiLineTexture();
	}

	return CCLabelTTF::updateTexture();
}
