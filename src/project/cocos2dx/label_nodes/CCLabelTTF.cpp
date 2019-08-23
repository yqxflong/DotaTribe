/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCLabelTTF.h"
#include "CCDirector.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "CCApplication.h"
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

NS_CC_BEGIN

#if CC_USE_LA88_LABELS
#define SHADER_PROGRAM kCCShader_PositionTextureColor
#else
#define SHADER_PROGRAM kCCShader_PositionTextureA8Color
#endif



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
/* 二分查找法，找到最合适的显示字符串长度*/
/************************************************************************/
static bool _richtext_split_(std::string text, float width, float height, CCImage::ETextAlign align, std::string fontName, float fontSize, int& bytesNumber)
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
		image.getStringSize(text.c_str(), 0, 0, align, fontName.c_str(), fontSize);
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

//
//CCLabelTTF
//
CCLabelTTF::CCLabelTTF()
: m_hAlignment(kCCTextAlignmentCenter)
, m_vAlignment(kCCVerticalTextAlignmentTop)
, m_pFontName(NULL)
, m_fFontSize(0.0)
, m_string("")
, m_shadowEnabled(false)
, m_strokeEnabled(false)
, m_textFillColor(ccWHITE)
{
	m_lastTextColor = ccWHITE;
}

CCLabelTTF::~CCLabelTTF()
{
    CC_SAFE_DELETE(m_pFontName);
}

CCLabelTTF * CCLabelTTF::create()
{
    CCLabelTTF * pRet = new CCLabelTTF();
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

CCLabelTTF * CCLabelTTF::create(const char *string, const char *fontName, float fontSize)
{
    return CCLabelTTF::create(string, fontName, fontSize,
                              CCSizeZero, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
}

CCLabelTTF * CCLabelTTF::create(const char *string, const char *fontName, float fontSize,
                                const CCSize& dimensions, CCTextAlignment hAlignment)
{
    return CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, kCCVerticalTextAlignmentTop);
}

CCLabelTTF* CCLabelTTF::create(const char *string, const char *fontName, float fontSize,
                               const CCSize &dimensions, CCTextAlignment hAlignment, 
                               CCVerticalTextAlignment vAlignment)
{
    CCLabelTTF *pRet = new CCLabelTTF();
    if(pRet && pRet->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCLabelTTF * CCLabelTTF::createWithFontDefinition(const char *string, ccFontDefinition &textDefinition)
{
    CCLabelTTF *pRet = new CCLabelTTF();
    if(pRet && pRet->initWithStringAndTextDefinition(string, textDefinition))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCLabelTTF::init()
{
	return this->initWithString("", 
								CCDirector::sharedDirector()->getDefaultFontName().c_str(),
								CCDirector::sharedDirector()->getDefaultFontSize());
}

bool CCLabelTTF::initWithString(const char *label, const char *fontName, float fontSize, 
                                const CCSize& dimensions, CCTextAlignment alignment)
{
    return this->initWithString(label, fontName, fontSize, dimensions, alignment, kCCVerticalTextAlignmentTop);
}

bool CCLabelTTF::initWithString(const char *label, const char *fontName, float fontSize)
{
    return this->initWithString(label, fontName, fontSize, 
                                CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
}

bool CCLabelTTF::initWithString(const char *string, const char *fontName, float fontSize,
                                const cocos2d::CCSize &dimensions, CCTextAlignment hAlignment,
                                CCVerticalTextAlignment vAlignment)
{
    if (CCSprite::init())
    {
        // shader program
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));
        
        m_tDimensions = CCSizeMake(dimensions.width, dimensions.height);
        m_hAlignment  = hAlignment;
        m_vAlignment  = vAlignment;
		std::string tt = fontName;
		if(tt == "")
		{
			fontName = CCDirector::sharedDirector()->getDefaultFontName().c_str();
		}
		if(fontSize <= 0.1f)
		{
			fontSize = CCDirector::sharedDirector()->getDefaultFontSize();
		}
        m_pFontName   = new std::string(fontName);
        m_fFontSize   = fontSize;
        
		if (m_hAlignment == kCCTextAlignmentLeft)
			setAnchorPoint(CCPoint(0.0f, getAnchorPoint().y));
		else if (m_hAlignment == kCCTextAlignmentCenter)
			setAnchorPoint(CCPoint(0.5f, getAnchorPoint().y));
		else if (m_hAlignment == kCCTextAlignmentRight)
			setAnchorPoint(CCPoint(1.0f, getAnchorPoint().y));

		if (m_vAlignment == kCCVerticalTextAlignmentTop)
			setAnchorPoint(CCPoint(getAnchorPoint().x, 1.0f));
		else if (m_vAlignment == kCCVerticalTextAlignmentCenter)
			setAnchorPoint(CCPoint(getAnchorPoint().x, 0.5f));
		else if (m_vAlignment == kCCVerticalTextAlignmentBottom)
			setAnchorPoint(CCPoint(getAnchorPoint().x, 0.0f));

        this->setString(string);
        
        return true;
    }
    
    return false;
}

bool CCLabelTTF::initWithStringAndTextDefinition(const char *string, ccFontDefinition &textDefinition)
{
    if (CCSprite::init())
    {
        // shader program
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(SHADER_PROGRAM));
        
        // prepare everythin needed to render the label
        _updateWithTextDefinition(textDefinition, false);
        
        // set the string
        this->setString(string);
        
        //
        return true;
    }
    else
    {
        return false;
    }
}

void CCLabelTTF::setString(const char *string)
{
    CCAssert(string != NULL, "Invalid string");
    
    if (m_string.compare(string))
    {
        m_string = string;
        
		// 解析字符串，进行富文本解析
		if (m_string.size() > 0)
		{
			m_RichTextList = CCRichTextLoader::sharedRichTextLoader()->loadFromBuffer(m_string);
			// 如果富文本解析失败，则直接按照空字符串显示
			if (m_RichTextList.size() <= 0)
				m_string = "";
		}
		else
		{
			m_RichTextList.clear();
		}
		
        this->updateTexture();
    }
}

const char* CCLabelTTF::getString(void)
{
    return m_string.c_str();
}

const char* CCLabelTTF::description()
{
    return CCString::createWithFormat("<CCLabelTTF | FontName = %s, FontSize = %.1f>", m_pFontName->c_str(), m_fFontSize)->getCString();
}

CCTextAlignment CCLabelTTF::getHorizontalAlignment()
{
    return m_hAlignment;
}

void CCLabelTTF::setHorizontalAlignment(CCTextAlignment alignment)
{
	if (alignment != m_hAlignment)
    {
        m_hAlignment = alignment;
        
		if (alignment == kCCTextAlignmentLeft)
			setAnchorPoint(CCPoint(0.0f, getAnchorPoint().y));
		else if (alignment == kCCTextAlignmentCenter)
			setAnchorPoint(CCPoint(0.5f, getAnchorPoint().y));
		else if (alignment == kCCTextAlignmentRight)
			setAnchorPoint(CCPoint(1.0f, getAnchorPoint().y));

        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

CCVerticalTextAlignment CCLabelTTF::getVerticalAlignment()
{
    return m_vAlignment;
}

void CCLabelTTF::setVerticalAlignment(CCVerticalTextAlignment verticalAlignment)
{
    if (verticalAlignment != m_vAlignment)
    {
        m_vAlignment = verticalAlignment;
        
		if (verticalAlignment == kCCVerticalTextAlignmentTop)
			setAnchorPoint(CCPoint(getAnchorPoint().x, 1.0f));
		else if (verticalAlignment == kCCVerticalTextAlignmentCenter)
			setAnchorPoint(CCPoint(getAnchorPoint().x, 0.5f));
		else if (verticalAlignment == kCCVerticalTextAlignmentBottom)
			setAnchorPoint(CCPoint(getAnchorPoint().x, 0.0f));

        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

CCSize CCLabelTTF::getDimensions()
{
    return m_tDimensions;
}

void CCLabelTTF::setDimensions(const CCSize &dim)
{
    if (dim.width != m_tDimensions.width || dim.height != m_tDimensions.height)
    {
        m_tDimensions = dim;
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

float CCLabelTTF::getFontSize()
{
    return m_fFontSize;
}

void CCLabelTTF::setFontSize(float fontSize)
{
    if (m_fFontSize != fontSize)
    {
		if (fontSize<=0.1f)
		{
			fontSize=CCDirector::sharedDirector()->getDefaultFontSize();
		}

        m_fFontSize = fontSize;
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

const char* CCLabelTTF::getFontName()
{
    return m_pFontName->c_str();
}

void CCLabelTTF::setFontName(const char *fontName)
{
    if (m_pFontName->compare(fontName))
    {
		std::string tt=fontName;
		if (tt=="")
		{
			fontName=CCDirector::sharedDirector()->getDefaultFontName().c_str();
		}
		
        delete m_pFontName;
        m_pFontName = new std::string(fontName);
        
        // Force update
        if (m_string.size() > 0)
        {
            this->updateTexture();
        }
    }
}

void CCLabelTTF::setColor(const ccColor3B& color3)
{
	CCNodeRGBA::setColor(ccc3(255, 255, 255));

	updateColor();
	m_lastTextColor = color3;

	do 
	{
		// 如果当前没有文字，则直接跳过
		if (m_RichTextList.size() < 0)
			break;

		if (m_RichTextList.size() == 1)
		{
			// 如果不是使用label自身的颜色，则跳过
			if (m_RichTextList.front().mHasFontColor)
				break;
		}
				
		updateTexture();
		return;
	} 
	while (false);
}

void CCLabelTTF::setColor2(const ccColor3B& color3)
{
	CCNodeRGBA::setColor(color3);

	updateColor();
}

void CCLabelTTF::setColor3(const ccColor3B& color3)
{
	CCNodeRGBA::setColor(ccc3(255, 255, 255));

	updateColor();
	m_lastTextColor = color3;
}

// Helper
bool CCLabelTTF::updateTexture()
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

	// 创建对应的纹理
	setColor3(m_lastTextColor);
	if (m_RichTextList.size() == 0)
	{
		return updateDefaultTexture(m_string);
	}
	else if (m_RichTextList.size() == 1)
	{
		// 判断节点是否为文字
		if (m_RichTextList.front().mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_TEXT_)
		{
			// 如果自己有颜色，则使用自己的颜色
			if (m_RichTextList.front().mHasFontColor)
			{
				setColor2(m_RichTextList.front().mFontColor);
			}
			else
			{
				setColor2(m_lastTextColor);
			}

			return updateDefaultTexture(m_RichTextList.front().mText);
		}
		else
		{
			return updateSingleLineTexture();
		}
	}
	else if (m_tDimensions.width==0.0f && m_tDimensions.height==0.0f)
	{// 单行文本
		return updateSingleLineTexture();
	}
	else
	{// 多行文本
		return updateMultiLineTexture();
	}
	
    //ok
    return true;
}

bool CCLabelTTF::updateDefaultTexture(std::string str)
{
	CCTexture2D *tex;
	tex = new CCTexture2D();

	if (!tex)
		return false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	ccFontDefinition texDef = _prepareTextDefinition(true);
	tex->initWithString( str.c_str(), texDef );

#else

	tex->initWithString( str.c_str(),
		m_pFontName->c_str(),
		m_fFontSize * CC_CONTENT_SCALE_FACTOR(),
		CC_SIZE_POINTS_TO_PIXELS(m_tDimensions),
		m_hAlignment,
		m_vAlignment);

#endif

	// set the texture
	this->setTexture(tex);
	// release it
	tex->release();

	// set the size in the sprite
	CCRect rect =CCRectZero;
	rect.size   = m_pobTexture->getContentSize();
	this->setTextureRect(rect);
	this->setFlipY(false);

	return true;
}

bool CCLabelTTF::updateSingleLineTexture()
{
	// 所有的label
	std::list<CCNode*> nodeList;

	// 按照宽高重排
	float width = 0.0f;
	float height= 0.0f;
	std::list<_RICHTEXT_NODE_>::iterator iter   = m_RichTextList.begin();
	std::list<_RICHTEXT_NODE_>::iterator iter_e = m_RichTextList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		// 如果是换行符，则直接跳过
		if ((*iter).mLineBreak)
			continue;

		// 如果没有包含字体颜色，则使用系统默认的
		if (!(*iter).mHasFontColor)
			(*iter).mFontColor = m_lastTextColor;

		// 如果没有包含字体大小，则使用系统默认的
		if ((*iter).mFontSize == 0.0f)
			(*iter).mFontSize = m_fFontSize;

		// 如果没有包含字体名称，则使用系统默认的
		if ((*iter).mFontName.size() <= 0)
			(*iter).mFontName = *m_pFontName;
		
		
		if ((*iter).mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_TEXT_)
		{// 如果是文本                                                                   
			CCLabelTTF* pLabel = CCLabelTTF::create((*iter).mText.c_str(), (*iter).mFontName.c_str(), (*iter).mFontSize, CCSizeZero, m_hAlignment, m_vAlignment);
			pLabel->setAnchorPoint(CCPoint(0.0f, 0.5f));
			pLabel->setPositionX(width);
			pLabel->setColor2((*iter).mFontColor);
			nodeList.push_back(pLabel);

			width += pLabel->getContentSize().width;
			if (height <= pLabel->getContentSize().height)
				height = pLabel->getContentSize().height;
		}
		else if ((*iter).mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_IMAGE_)
		{// 如果是图片
			CCSprite* pSprite = CCSprite::createWithSpriteFrameName((*iter).mImageName.c_str());
			pSprite->setAnchorPoint(CCPoint(0.0f, 0.5f));
			pSprite->setPositionX(width);
			nodeList.push_back(pSprite);

			width += pSprite->getContentSize().width;
			if (height <= pSprite->getContentSize().height)
				height = pSprite->getContentSize().height;
		}
		else if ((*iter).mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_ANIMATION_)
		{// 如果是动画
			char buffer[128] = "";
			sprintf(buffer, "%s_%02d.png", (*iter).mAnimationName.c_str(), 1);
			CCSprite* pSprite = CCSprite::createWithSpriteFrameName(buffer);
			pSprite->setAnchorPoint(CCPoint(0.0f, 0.5f));
			pSprite->setPositionX(width);
			m_AniSpriteList.push_back(pSprite);

			width += pSprite->getContentSize().width;
			if (height <= pSprite->getContentSize().height)
				height = pSprite->getContentSize().height;

			// 播放动画
			cocos2d::CCArray* pAnimFrames = cocos2d::CCArray::create();
			{
				for(unsigned int i=1; i<=(*iter).mAnimationCount; i++) 
				{
					char buffer[128] = "";
					sprintf(buffer, "%s_%02d.png", (*iter).mAnimationName.c_str(), i);
					cocos2d::CCSpriteFrame* pTemp = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
					pAnimFrames->addObject(pTemp);
				}

				cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(pAnimFrames, (*iter).mAnimationInterval);
				cocos2d::CCAnimate*   pAnimate   = cocos2d::CCAnimate::create(pAnimation);
				cocos2d::CCActionInterval* pSeq = (cocos2d::CCActionInterval*)(cocos2d::CCSequence::create(pAnimate, NULL));
				pSprite->runAction(cocos2d::CCRepeatForever::create(pSeq));
			}
			pAnimFrames->release();
		}
	}

	// 设置所有Node的Y坐标（确保中间对齐）
	std::list<CCNode*>::iterator iter2   = nodeList.begin();
	std::list<CCNode*>::iterator iter2_e = nodeList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		(*iter2)->setPositionY(height/2.0f);
	}

	// 设置所有动画表情的Y坐标
	iter2   = m_AniSpriteList.begin();
	iter2_e = m_AniSpriteList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		(*iter2)->setPositionY(height/2.0f);
	}

	// 将所有的Node纹理渲染到一张纹理上
	CCRenderTexture* pRenderTexture = CCRenderTexture::create(width, height, cocos2d::kCCTexture2DPixelFormat_AI88);
	pRenderTexture->getSprite()->getTexture()->setAntiAliasTexParameters();
	pRenderTexture->begin();
	pRenderTexture->setAnchorPoint(CCPoint(0.0f, 0.0f));
	{
		std::list<CCNode*>::iterator iter   = nodeList.begin();
		std::list<CCNode*>::iterator iter_e = nodeList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			if (dynamic_cast<CCLabelTTF*>(*iter) != NULL)
			{
				m_RichLabelList.push_back(*iter);
			}
			else if (dynamic_cast<CCSprite*>(*iter) != NULL)
			{
				(*iter)->visit();
			}
		}
	}
	pRenderTexture->end();

	// 设置Label的纹理
	CCRect rect = CCRectZero;
	rect.size = pRenderTexture->getSprite()->getTexture()->getContentSize();
	this->setTexture(pRenderTexture->getSprite()->getTexture());
	this->setTextureRect(rect);
	this->setFlipY(true);

	// 加载所有的富文本文字
	iter2   = m_RichLabelList.begin();
	iter2_e = m_RichLabelList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		this->addChild(*iter2);
	}

	// 加载所有的动画表情
	iter2   = m_AniSpriteList.begin();
	iter2_e = m_AniSpriteList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		this->addChild(*iter2);
	}

	return true;
}

bool CCLabelTTF::updateMultiLineTexture()
{
	// 所有的node
	std::list<CCNode*> nodeList;
	// 单行显示的所有node
	std::list<CCNode*> nodeList2;
	// 单行显示的所有动画CCNode
	std::list<CCNode*> spriteList;

	// 防止Width为0
	if (m_tDimensions.width == 0.0f)
		m_tDimensions.width = 500.0f;
	
	// 按照宽高重排
	float renderTextureWidth = m_tDimensions.width;
	float width = 0.0f;
	float height= 0.0f;
	float tempHeight = 0.0f;
	float lastLineHeight = 0.0f;
	std::list<_RICHTEXT_NODE_>::iterator iter   = m_RichTextList.begin();
	std::list<_RICHTEXT_NODE_>::iterator iter_e = m_RichTextList.end();
	for ( ; iter!=iter_e; )
	{
		// 如果没有包含字体颜色，则使用系统默认的
		if (!(*iter).mHasFontColor)
			(*iter).mFontColor = m_lastTextColor;

		// 如果没有包含字体大小，则使用系统默认的
		if ((*iter).mFontSize == 0.0f)
			(*iter).mFontSize = m_fFontSize;

		// 如果没有包含字体名称，则使用系统默认的
		if ((*iter).mFontName.size() <= 0)
			(*iter).mFontName = *m_pFontName;

		// 换行符处理
		if ((*iter).mLineBreak)
		{
			// 如果当前为空行，则直接按照前一个行高度换行
			if (nodeList2.size()==0 && spriteList.size()==0)
			{
				width = 0.0f;
				height= height+lastLineHeight;
				tempHeight = 0.0f;

				++iter;
				continue;
			}
			
			// 设置当前行所有label的Y坐标
			std::list<CCNode*>::iterator iter2   = nodeList2.begin();
			std::list<CCNode*>::iterator iter2_e = nodeList2.end();
			for ( ; iter2!=iter2_e; ++iter2)
			{
				(*iter2)->setPositionY(-height-tempHeight/2.0f);
			}
			nodeList2.clear();

			// 设置当前行所有动画表情的Y坐标
			iter2   = spriteList.begin();
			iter2_e = spriteList.end();
			for ( ; iter2!=iter2_e; ++iter2)
			{
				(*iter2)->setPositionY(-height-tempHeight/2.0f);
				m_AniSpriteList.push_back((*iter2));
			}
			spriteList.clear();

			width = 0.0f;
			height= height+tempHeight;
			lastLineHeight = tempHeight;
			tempHeight = 0.0f;

			++iter;
			continue;
		}

		// 防止插入导致索引错乱，提前创建tempIter
		std::list<_RICHTEXT_NODE_>::iterator tempIter = iter;
		if ((*iter).mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_TEXT_)
		{// 如果是文本
			// 计算文字的渲染方式
			CCImage::ETextAlign eAlign;
			if (kCCVerticalTextAlignmentTop == m_vAlignment)
			{
				eAlign = (kCCTextAlignmentCenter == m_hAlignment) ? CCImage::kAlignTop
					: (kCCTextAlignmentLeft == m_hAlignment) ? CCImage::kAlignTopLeft : CCImage::kAlignTopRight;
			}
			else if (kCCVerticalTextAlignmentCenter == m_vAlignment)
			{
				eAlign = (kCCTextAlignmentCenter == m_hAlignment) ? CCImage::kAlignCenter
					: (kCCTextAlignmentLeft == m_hAlignment) ? CCImage::kAlignLeft : CCImage::kAlignRight;
			}
			else if (kCCVerticalTextAlignmentBottom == m_vAlignment)
			{
				eAlign = (kCCTextAlignmentCenter == m_hAlignment) ? CCImage::kAlignBottom
					: (kCCTextAlignmentLeft == m_hAlignment) ? CCImage::kAlignBottomLeft : CCImage::kAlignBottomRight;
			}
			CCImage image;
			image.getStringSize((*iter).mText.c_str(), 0, 0, eAlign, (*iter).mFontName.c_str(), (*iter).mFontSize);
			if (image.getWidth() >= (renderTextureWidth-width))
			{
				int bytes = 0;
				_richtext_split_((*iter).mText, renderTextureWidth-width, 0, eAlign, (*iter).mFontName, (*iter).mFontSize, bytes);
				if (bytes <= 0)
				{
					// 设置当前行所有label的Y坐标
					std::list<CCNode*>::iterator iter   = nodeList2.begin();
					std::list<CCNode*>::iterator iter_e = nodeList2.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY(-height-tempHeight/2.0f);
					}
					nodeList2.clear();

					// 设置当前行所有动画表情的Y坐标
					iter   = spriteList.begin();
					iter_e = spriteList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY(-height-tempHeight/2.0f);
						m_AniSpriteList.push_back((*iter));
					}
					spriteList.clear();

					width = 0.0f;
					height= height+tempHeight;
					lastLineHeight = tempHeight;
					tempHeight = 0.0f;
				}
				else
				{
					_RICHTEXT_NODE_ temp = (*iter);
					temp.mText = (temp.mText.c_str()+bytes);
					m_RichTextList.insert(++tempIter, temp);

					(*iter).mText = (*iter).mText.substr(0, bytes);
				}
			}
			else
			{
				CCLabelTTF* pLabel = CCLabelTTF::create((*iter).mText.c_str(), (*iter).mFontName.c_str(), (*iter).mFontSize, CCSizeZero, m_hAlignment, m_vAlignment);
				pLabel->setAnchorPoint(CCPoint(0.0f, 0.5f));
				pLabel->setPositionX(width);
				pLabel->setColor2((*iter).mFontColor);
				nodeList.push_back(pLabel);
				nodeList2.push_back(pLabel);

				width = width+pLabel->getContentSize().width;
				if (tempHeight < pLabel->getContentSize().height)
				{
					tempHeight = pLabel->getContentSize().height;
				}

				++iter;
			}
		}
		else if ((*iter).mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_IMAGE_)
		{// 如果是图片
			CCSprite* pSprite = CCSprite::createWithSpriteFrameName((*tempIter).mImageName.c_str());
			if (pSprite->getContentSize().width > renderTextureWidth)
			{// 本身图片就太大了，则不显示图片了
				++iter;
			}
			else if (pSprite->getContentSize().width <= (renderTextureWidth-width))
			{
				pSprite->setAnchorPoint(CCPoint(0.0f, 0.5f));
				pSprite->setPositionX(width);
				nodeList.push_back(pSprite);
				nodeList2.push_back(pSprite);

				width = width+pSprite->getContentSize().width;
				if (tempHeight < pSprite->getContentSize().height)
				{
					tempHeight = pSprite->getContentSize().height;
				}

				++iter;
			}
			else
			{
				// 设置当前行所有label的Y坐标
				std::list<CCNode*>::iterator iter   = nodeList2.begin();
				std::list<CCNode*>::iterator iter_e = nodeList2.end();
				for ( ; iter!=iter_e; ++iter)
				{
					(*iter)->setPositionY(-height-tempHeight/2.0f);
				}
				nodeList2.clear();

				// 设置当前行所有动画表情的Y坐标
				iter   = spriteList.begin();
				iter_e = spriteList.end();
				for ( ; iter!=iter_e; ++iter)
				{
					(*iter)->setPositionY(-height-tempHeight/2.0f);
					m_AniSpriteList.push_back((*iter));
				}
				spriteList.clear();

				width = 0.0f;
				height= height+tempHeight;
				lastLineHeight = tempHeight;
				tempHeight = 0.0f;
			}
		}
		else if ((*iter).mNodeType == _RICHTEXT_NODE_::_TYPED_NODE_ANIMATION_)
		{
			char buffer[128] = "";
			sprintf(buffer, "%s_%02d.png", (*iter).mAnimationName.c_str(), 1);
			CCSprite* pSprite = CCSprite::createWithSpriteFrameName(buffer);
			if (pSprite->getContentSize().width > renderTextureWidth)
			{// 本身图片就太大了，则不显示图片了
				++iter;
			}
			else if (pSprite->getContentSize().width <= (renderTextureWidth-width))
			{
				// 创建图片
				char buffer[128] = "";
				sprintf(buffer, "%s_%02d.png", (*iter).mAnimationName.c_str(), 1);
				CCSprite* pSprite = CCSprite::createWithSpriteFrameName(buffer);
				pSprite->setAnchorPoint(CCPoint(0.0f, 0.5f));
				pSprite->setPositionX(width);
				spriteList.push_back(pSprite);

				width = width+pSprite->getContentSize().width;
				if (tempHeight < pSprite->getContentSize().height)
				{
					tempHeight = pSprite->getContentSize().height;
				}

				// 播放动画
				cocos2d::CCArray* pAnimFrames = cocos2d::CCArray::create();
				{
					for(unsigned int i=1; i<=(*iter).mAnimationCount; i++) 
					{
						char buffer[128] = "";
						sprintf(buffer, "%s_%02d.png", (*iter).mAnimationName.c_str(), i);
						cocos2d::CCSpriteFrame* pTemp = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
						pAnimFrames->addObject(pTemp);
					}

					cocos2d::CCAnimation* pAnimation = cocos2d::CCAnimation::createWithSpriteFrames(pAnimFrames, (*iter).mAnimationInterval);
					cocos2d::CCAnimate*   pAnimate   = cocos2d::CCAnimate::create(pAnimation);
					cocos2d::CCActionInterval* pSeq = (cocos2d::CCActionInterval*)(cocos2d::CCSequence::create(pAnimate, NULL));
					pSprite->runAction(cocos2d::CCRepeatForever::create(pSeq));
				}
				pAnimFrames->release();

				++iter;
			}
			else
			{
				// 设置当前行所有label的Y坐标
				std::list<CCNode*>::iterator iter   = nodeList2.begin();
				std::list<CCNode*>::iterator iter_e = nodeList2.end();
				for ( ; iter!=iter_e; ++iter)
				{
					(*iter)->setPositionY(-height-tempHeight/2.0f);
				}
				nodeList2.clear();

				// 设置当前行所有动画表情的Y坐标
				iter   = spriteList.begin();
				iter_e = spriteList.end();
				for ( ; iter!=iter_e; ++iter)
				{
					(*iter)->setPositionY(-height-tempHeight/2.0f);
					m_AniSpriteList.push_back((*iter));
				}
				spriteList.clear();

				width = 0.0f;
				height= height+tempHeight;
				lastLineHeight = tempHeight;
				tempHeight = 0.0f;
			}
		}
		else
		{// 如果不是文本和图片，则直接跳过
			++iter;
			continue;
		}
	}

	{
		// 设置当前行所有node的Y坐标
		std::list<CCNode*>::iterator iter   = nodeList2.begin();
		std::list<CCNode*>::iterator iter_e = nodeList2.end();
		for ( ; iter!=iter_e; ++iter)
		{
			(*iter)->setPositionY(-height-tempHeight/2.0f);
		}
		nodeList2.clear();

		// 设置当前行所有表情动画的Y坐标
		iter   = spriteList.begin();
		iter_e = spriteList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			(*iter)->setPositionY(-height-tempHeight/2.0f);
			m_AniSpriteList.push_back((*iter));
		}
		spriteList.clear();

		// 所有node合并之后纹理高度
		height= height+tempHeight;

		// 如果没有设置多行文本和图片纹理高度，则直接使用计算出来的即可
		if (m_tDimensions.height == 0.0f)
		{
			iter   = nodeList.begin();
			iter_e = nodeList.end();
			for ( ; iter!=iter_e; ++iter)
			{
				(*iter)->setPositionY((*iter)->getPositionY()+height);
			}

			iter   = m_AniSpriteList.begin();
			iter_e = m_AniSpriteList.end();
			for ( ; iter!=iter_e; ++iter)
			{
				(*iter)->setPositionY((*iter)->getPositionY()+height);
			}
		}
		else
		{
			// 如果算出来的纹理高度小于指定纹理高度
			if (height < m_tDimensions.height)
			{
				if (getAnchorPoint().y == 0.0f)
				{// 底部对齐
					iter   = nodeList.begin();
					iter_e = nodeList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY((*iter)->getPositionY()+height);
					}

					iter   = m_AniSpriteList.begin();
					iter_e = m_AniSpriteList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY((*iter)->getPositionY()+height);
					}
				}
				else if (getAnchorPoint().y == 0.5f)
				{// 中间对齐
					iter   = nodeList.begin();
					iter_e = nodeList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY((*iter)->getPositionY()+(m_tDimensions.height+height)/2.0f);
					}

					iter   = m_AniSpriteList.begin();
					iter_e = m_AniSpriteList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY((*iter)->getPositionY()+(m_tDimensions.height+height)/2.0f);
					}
				}
				else if (getAnchorPoint().y == 1.0f)
				{// 顶部对齐
					iter   = nodeList.begin();
					iter_e = nodeList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY((*iter)->getPositionY()+m_tDimensions.height);
					}

					iter   = m_AniSpriteList.begin();
					iter_e = m_AniSpriteList.end();
					for ( ; iter!=iter_e; ++iter)
					{
						(*iter)->setPositionY((*iter)->getPositionY()+m_tDimensions.height);
					}
				}

				height = m_tDimensions.height;
			}
			else
			{// 如果算出来的纹理高度大于指定纹理高度
				;// 暂不处理了
			}
		}
	}

	// 将所有node渲染到一张纹理上面
	CCRenderTexture* pRenderTexture = CCRenderTexture::create(renderTextureWidth, height, cocos2d::kCCTexture2DPixelFormat_AI88);
	pRenderTexture->getSprite()->getTexture()->setAntiAliasTexParameters();
	pRenderTexture->begin();
	pRenderTexture->setAnchorPoint(CCPoint(0.0f, 0.0f));
	{
		std::list<CCNode*>::iterator iter   = nodeList.begin();
		std::list<CCNode*>::iterator iter_e = nodeList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			if (dynamic_cast<CCLabelTTF*>(*iter) != NULL)
			{
				m_RichLabelList.push_back(*iter);
			}
			else if (dynamic_cast<CCSprite*>(*iter) != NULL)
			{
				(*iter)->visit();
			}
		}
	}
	pRenderTexture->end();

	// 设置label的纹理
	CCRect rect = CCRectZero;
	rect.size = pRenderTexture->getSprite()->getTexture()->getContentSize();
	this->setTexture(pRenderTexture->getSprite()->getTexture());
	this->setTextureRect(rect);
	this->setFlipY(true);

	// 将所有富文本文字增加到当前label上
	std::list<CCNode*>::iterator iter2   = m_RichLabelList.begin();
	std::list<CCNode*>::iterator iter2_e = m_RichLabelList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		this->addChild(*iter2);
	}

	// 将所有表情动画增加到当前label上
	iter2   = m_AniSpriteList.begin();
	iter2_e = m_AniSpriteList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		this->addChild(*iter2);
	}

	return true;
}

void CCLabelTTF::enableShadow(const CCSize &shadowOffset, float shadowOpacity, float shadowBlur, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool valueChanged = false;
        
        if (false == m_shadowEnabled)
        {
            m_shadowEnabled = true;
            valueChanged    = true;
        }
        
        if ( (m_shadowOffset.width != shadowOffset.width) || (m_shadowOffset.height!=shadowOffset.height) )
        {
            m_shadowOffset.width  = shadowOffset.width;
            m_shadowOffset.height = shadowOffset.height;
            
            valueChanged = true;
        }
        
        if (m_shadowOpacity != shadowOpacity )
        {
            m_shadowOpacity = shadowOpacity;
            valueChanged = true;
        }

        if (m_shadowBlur    != shadowBlur)
        {
            m_shadowBlur = shadowBlur;
            valueChanged = true;
        }
        
        
        if ( valueChanged && updateTexture )
        {
            this->updateTexture();
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
    
}

void CCLabelTTF::disableShadow(bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        if (m_shadowEnabled)
        {
            m_shadowEnabled = false;
    
            if (updateTexture)
                this->updateTexture();
            
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
}

void CCLabelTTF::enableStroke(const ccColor3B &strokeColor, float strokeSize, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool valueChanged = false;
        
        if(m_strokeEnabled == false)
        {
            m_strokeEnabled = true;
            valueChanged = true;
        }
        
        if ( (m_strokeColor.r != strokeColor.r) || (m_strokeColor.g != strokeColor.g) || (m_strokeColor.b != strokeColor.b) )
        {
            m_strokeColor = strokeColor;
            valueChanged = true;
        }
        
        if (m_strokeSize!=strokeSize)
        {
            m_strokeSize = strokeSize;
            valueChanged = true;
        }
        
        if ( valueChanged && updateTexture )
        {
            this->updateTexture();
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
    
}

void CCLabelTTF::disableStroke(bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        if (m_strokeEnabled)
        {
            m_strokeEnabled = false;
            
            if (updateTexture)
                this->updateTexture();
        }
    
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
    
}

void CCLabelTTF::setFontFillColor(const ccColor3B &tintColor, bool updateTexture)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (m_textFillColor.r != tintColor.r || m_textFillColor.g != tintColor.g || m_textFillColor.b != tintColor.b)
        {
            m_textFillColor = tintColor;
            
            if (updateTexture)
                this->updateTexture();
        }
    #else
        CCLOGERROR("Currently only supported on iOS and Android!");
    #endif
}

void CCLabelTTF::setTextDefinition(ccFontDefinition *theDefinition)
{
    if (theDefinition)
    {
        _updateWithTextDefinition(*theDefinition, true);
    }
}

ccFontDefinition *CCLabelTTF::getTextDefinition()
{
    ccFontDefinition *tempDefinition = new ccFontDefinition;
    *tempDefinition = _prepareTextDefinition(false);
    return tempDefinition;
}

void CCLabelTTF::_updateWithTextDefinition(ccFontDefinition & textDefinition, bool mustUpdateTexture)
{
    m_tDimensions = CCSizeMake(textDefinition.m_dimensions.width, textDefinition.m_dimensions.height);
    m_hAlignment  = textDefinition.m_alignment;
    m_vAlignment  = textDefinition.m_vertAlignment;
    
	if (m_pFontName != NULL)
	{
		delete m_pFontName;
		m_pFontName = NULL;
	}

    m_pFontName   = new std::string(textDefinition.m_fontName);
    m_fFontSize   = textDefinition.m_fontSize;
    
    
    // shadow
    if ( textDefinition.m_shadow.m_shadowEnabled )
    {
        enableShadow(textDefinition.m_shadow.m_shadowOffset, textDefinition.m_shadow.m_shadowOpacity, textDefinition.m_shadow.m_shadowBlur, false);
    }
    
    // stroke
    if ( textDefinition.m_stroke.m_strokeEnabled )
    {
        enableStroke(textDefinition.m_stroke.m_strokeColor, textDefinition.m_stroke.m_strokeSize, false);
    }
    
    // fill color
    setFontFillColor(textDefinition.m_fontFillColor, false);
    
    if (mustUpdateTexture)
        updateTexture();
}

ccFontDefinition CCLabelTTF::_prepareTextDefinition(bool adjustForResolution)
{
    ccFontDefinition texDef;
    
    if (adjustForResolution)
        texDef.m_fontSize       =  m_fFontSize * CC_CONTENT_SCALE_FACTOR();
    else
        texDef.m_fontSize       =  m_fFontSize;
    
    texDef.m_fontName       = *m_pFontName;
    texDef.m_alignment      =  m_hAlignment;
    texDef.m_vertAlignment  =  m_vAlignment;
    
    
    if (adjustForResolution)
        texDef.m_dimensions     =  CC_SIZE_POINTS_TO_PIXELS(m_tDimensions);
    else
        texDef.m_dimensions     =  m_tDimensions;
    
    
    // stroke
    if ( m_strokeEnabled )
    {
        texDef.m_stroke.m_strokeEnabled = true;
        texDef.m_stroke.m_strokeColor   = m_strokeColor;
        
        if (adjustForResolution)
            texDef.m_stroke.m_strokeSize = m_strokeSize * CC_CONTENT_SCALE_FACTOR();
        else
            texDef.m_stroke.m_strokeSize = m_strokeSize;
        
        
    }
    else
    {
        texDef.m_stroke.m_strokeEnabled = false;
    }
    
    
    // shadow
    if ( m_shadowEnabled )
    {
        texDef.m_shadow.m_shadowEnabled         = true;
        texDef.m_shadow.m_shadowBlur            = m_shadowBlur;
        texDef.m_shadow.m_shadowOpacity         = m_shadowOpacity;
        
        if (adjustForResolution)
            texDef.m_shadow.m_shadowOffset = CC_SIZE_POINTS_TO_PIXELS(m_shadowOffset);
        else
            texDef.m_shadow.m_shadowOffset = m_shadowOffset;
    }
    else
    {
        texDef.m_shadow.m_shadowEnabled = false;
    }
    
    // text tint
    texDef.m_fontFillColor = m_textFillColor;
    
    return texDef;
}

NS_CC_END
