#ifndef  _RICHTEXTLOADER_RICHTEXTLOADER_H_
#define  _RICHTEXTLOADER_RICHTEXTLOADER_H_


#include "ccTypes.h"
#include <string>
#include <list>

namespace  cocos2d
{


struct _RICHTEXT_NODE_
{
public:
	enum
	{
		_TYPED_NODE_TEXT_,       // 文字
		_TYPED_NODE_BUTTON_,     // 按钮
		_TYPED_NODE_IMAGE_,      // 图片
		_TYPED_NODE_ANIMATION_,  // 动画
	};

public:
	int         mNodeType;          // 节点类型
	std::string mFontName;          // 字体名称
	float       mFontSize;          // 字体大小
	bool        mHasFontColor;      // 是否字体颜色
	ccColor3B   mFontColor;         // 字体颜色
	std::string mText;              // 节点文字
	std::string mButtonName;        // 按钮名称
	std::string mImageName;         // 图片名称
	std::string mAnimationName;     // 动画名称
	int         mAnimationCount;    // 动画个数
	float       mAnimationInterval; // 动画播放间隔
	bool        mLineBreak;         // 是否换行

public:
	_RICHTEXT_NODE_()
	{
		mNodeType = _TYPED_NODE_TEXT_;
		mFontSize = 0.0f;
		mAnimationCount = 0;
		mAnimationInterval = 0.2f;
		mHasFontColor   = false;
		mLineBreak      = false;
	}
};

class CCRichTextLoader
{
protected:
	std::string m_DefaultFontName;    // 默认字体名称
	float       m_DefaultFontSize;    // 默认字体大小
	ccColor3B   m_DefaultFontColor;   // 默认字体颜色
	float       m_DefaultAnimationInterval;// 默认的动画播放间隔

protected:
	CCRichTextLoader();

public:
	/*
		设置默认的字体
	*/
	void setDefaultFontName(std::string fontName);
	/*
		得到默认的字体
	*/
	std::string getDefaultFontName();
	/*
		设置默认的字体大小
	*/
	void setDefaultFontSize(float size);
	/*
		得到默认的字体大小
	*/
	float getDefaultFontSize();
	/*
		设置默认的字体颜色
	*/
	void setDefaultFontColor(ccColor3B color);
	/*
		得到默认的字体颜色
	*/
	ccColor3B getDefaultFontColor();
	/*
		设置默认的动画播放间隔
	*/
	void setDefaultAnimationInterval(float interval);
	/*
		得到默认的动画播放间隔
	*/
	float getDefaultAnimationInterval();

public:
	/*
		从内存加载指定的富文本
	*/
	std::list<_RICHTEXT_NODE_> loadFromBuffer(std::string text);

public:
	/*
		获得单例数据
	*/
	static  CCRichTextLoader*  sharedRichTextLoader();
};


}


#endif
