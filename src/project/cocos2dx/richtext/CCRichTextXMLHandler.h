#ifndef  _RICHTEXTLOADER_RICHTEXTXMLHANDLER_H_
#define  _RICHTEXTLOADER_RICHTEXTXMLHANDLER_H_


#include "CCRichTextLoader.h"
#include <string>
#include <vector>

namespace  cocos2d
{


class CCRichTextXMLAttribute;
class CCRichTextXMLHandler
{
public:
	static const std::string NodeElement;				//!< Tag name for Window elements.
	static const std::string PropertyElement;			//!< Tag name for Property elements.
	static const std::string NodeTypeAttribute;			//!< Attribute name that stores the type of Window to create.
	static const std::string NodeFontNameAttribute;		//!< Attribute name that stores the name of the window to create.
	static const std::string NodeFontSizeAttribute;		//!< Attribute name that stores the name of the window to create.
	static const std::string NodeFontColorAttribute;	//!< Attribute name that stores the name of the window to create.
	static const std::string NodeTextAttribute;			//!< Attribute name that stores the name of the window to create.
	static const std::string NodeButtonNameAttribute;	//!< Attribute name that stores the zorder of the window to create.
	static const std::string NodeImageNameAttribute;	//!< Attribute name that stores the zorder of the window to create.
	static const std::string NodeAnimationNameAttribute;//!< Attribute name that stores the zorder of the window to create.
	static const std::string NodeAnimationCountAttribute;//!< Attribute name that stores the zorder of the window to create.
	static const std::string NodeAnimationIntervalAttribute;//!< Attribute name that stores the zorder of the window to create.

private:
	std::list<_RICHTEXT_NODE_> m_NodeList;

public:
	CCRichTextXMLHandler();
	~CCRichTextXMLHandler();

public:
	/*
		得到当前布局文件的根窗口对象
	*/
	std::list<_RICHTEXT_NODE_> GetNodeList();

public:
	/*
		开始解析的回调处理
	*/
	void StartElement(std::string element, CCRichTextXMLAttribute* pAttribute);
	/*
		结束解析的回调处理
	*/
	void EndElement(std::string element);

public:
	/*
		Node元素开始解析回调处理
	*/
	void ElementNodeStart(CCRichTextXMLAttribute* pAttribute);
	/*
		Window元素结束解析回调处理
	*/
	void ElementNodeEnd();
};


}


#endif
