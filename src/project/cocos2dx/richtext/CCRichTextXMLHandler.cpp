#include "CCRichTextXMLHandler.h"
#include "CCRichTextXMLAttribute.h"
#include <assert.h>
using  namespace  cocos2d;



const std::string CCRichTextXMLHandler::NodeElement("a");
const std::string CCRichTextXMLHandler::NodeTypeAttribute("type");
const std::string CCRichTextXMLHandler::NodeTextAttribute("text");
const std::string CCRichTextXMLHandler::NodeFontNameAttribute("fontname");
const std::string CCRichTextXMLHandler::NodeFontSizeAttribute("fontsize");
const std::string CCRichTextXMLHandler::NodeFontColorAttribute("fontcolor");
const std::string CCRichTextXMLHandler::NodeButtonNameAttribute("buttonname");
const std::string CCRichTextXMLHandler::NodeImageNameAttribute("imagename");
const std::string CCRichTextXMLHandler::NodeAnimationNameAttribute("animationname");
const std::string CCRichTextXMLHandler::NodeAnimationCountAttribute("animationcount");
const std::string CCRichTextXMLHandler::NodeAnimationIntervalAttribute("animationinterval");

CCRichTextXMLHandler::CCRichTextXMLHandler()
{

}

CCRichTextXMLHandler::~CCRichTextXMLHandler()
{

}

std::list<_RICHTEXT_NODE_> CCRichTextXMLHandler::GetNodeList()
{
	return m_NodeList;
}

void CCRichTextXMLHandler::StartElement(std::string element, CCRichTextXMLAttribute* pAttribute)
{
	if (element == NodeElement)
	{
		ElementNodeStart(pAttribute);
	}
}

void CCRichTextXMLHandler::EndElement(std::string element)
{
	if (element == NodeElement)
	{
		ElementNodeEnd();
	}
}

static  std::string  _rich_text_parser_(std::string text)
{
	static  std::map<std::string, std::string>  sEscapeSequenceList;
	if (sEscapeSequenceList.size() == 0)
	{
		sEscapeSequenceList.insert(std::map<std::string, std::string>::value_type("<br>", "\r"));
		sEscapeSequenceList.insert(std::map<std::string, std::string>::value_type("&apos;", "'"));
		sEscapeSequenceList.insert(std::map<std::string, std::string>::value_type("&quot;", "\""));
	}

	std::string str = text;
	std::map<std::string, std::string>::iterator iter   = sEscapeSequenceList.begin();
	std::map<std::string, std::string>::iterator iter_e = sEscapeSequenceList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		std::string key   = iter->first;
		std::string value = iter->second;

		do 
		{
			std::string::size_type pos = str.find(key, 0);
			if (pos == str.npos)
				break;

			std::string::iterator tempIter = str.begin();
			tempIter = tempIter+pos;

			str.replace(tempIter, tempIter+key.size(), value);
		} 
		while (true);
	}

	return str;
}

void CCRichTextXMLHandler::ElementNodeStart(CCRichTextXMLAttribute* pAttribute)
{
	do 
	{
		_RICHTEXT_NODE_ node;

		std::string nodeType = pAttribute->GetValueAsString(NodeTypeAttribute);
		if (nodeType.compare("text") == 0)
		{
			node.mNodeType = _RICHTEXT_NODE_::_TYPED_NODE_TEXT_;
			if (!pAttribute->IsExist(NodeTextAttribute))
				break;

			if (pAttribute->IsExist(NodeFontNameAttribute))
				node.mFontName = pAttribute->GetValueAsString(NodeFontNameAttribute);

			if (pAttribute->IsExist(NodeFontSizeAttribute))
				node.mFontSize = pAttribute->GetValueAsFloat(NodeFontSizeAttribute);

			if (pAttribute->IsExist(NodeFontColorAttribute))
			{
				node.mHasFontColor = true;

				int red = 0;
				int green = 0;
				int blue = 0;
				std::string color = pAttribute->GetValueAsString(NodeFontColorAttribute);
				sscanf(color.c_str(), "{%d,%d,%d}", &red, &green, &blue);
				node.mFontColor  = ccc3(red, green, blue);
			}
			else
			{
				node.mHasFontColor = false;
			}

			node.mText     = pAttribute->GetValueAsString(NodeTextAttribute);
			node.mText     = _rich_text_parser_(node.mText);
		}
		else if (nodeType.compare("button") == 0)
		{
			node.mNodeType = _RICHTEXT_NODE_::_TYPED_NODE_BUTTON_;
			if (!pAttribute->IsExist(NodeButtonNameAttribute))
				break;

			if (pAttribute->IsExist(NodeFontNameAttribute))
				node.mFontName = pAttribute->GetValueAsString(NodeFontNameAttribute);

			if (pAttribute->IsExist(NodeFontSizeAttribute))
				node.mFontSize = pAttribute->GetValueAsFloat(NodeFontSizeAttribute);

			if (pAttribute->IsExist(NodeFontColorAttribute))
			{
				node.mHasFontColor = false;

				int red = 0;
				int green = 0;
				int blue = 0;
				std::string color = pAttribute->GetValueAsString(NodeFontColorAttribute);
				sscanf(color.c_str(), "{%d,%d,%d}", &red, &green, &blue);
				node.mFontColor  = ccc3(red, green, blue);
			}
			else
			{
				node.mHasFontColor = true;
			}

			node.mButtonName = pAttribute->GetValueAsString(NodeButtonNameAttribute);
			node.mButtonName = _rich_text_parser_(node.mButtonName);
		}
		else if (nodeType.compare("image") == 0)
		{
			node.mNodeType = _RICHTEXT_NODE_::_TYPED_NODE_IMAGE_;
			if (!pAttribute->IsExist(NodeImageNameAttribute))
				break;

			node.mImageName = pAttribute->GetValueAsString(NodeImageNameAttribute);
		}
		else if (nodeType.compare("animation") == 0)
		{
			node.mNodeType = _RICHTEXT_NODE_::_TYPED_NODE_ANIMATION_;
			if (!pAttribute->IsExist(NodeAnimationNameAttribute))
				break;

			if (!pAttribute->IsExist(NodeAnimationCountAttribute))
				break;

			if (pAttribute->IsExist(NodeAnimationIntervalAttribute))
			{
				node.mAnimationInterval = pAttribute->GetValueAsFloat(NodeAnimationIntervalAttribute);
			}
			else
			{
				node.mAnimationInterval = CCRichTextLoader::sharedRichTextLoader()->getDefaultAnimationInterval();
			}
			
			node.mAnimationName  = pAttribute->GetValueAsString(NodeAnimationNameAttribute);
			node.mAnimationCount = pAttribute->GetValueAsInt(NodeAnimationCountAttribute);
		}
		else
		{
			break;
		}

		m_NodeList.push_back(node);
	} 
	while (false);
}

void CCRichTextXMLHandler::ElementNodeEnd()
{

}
