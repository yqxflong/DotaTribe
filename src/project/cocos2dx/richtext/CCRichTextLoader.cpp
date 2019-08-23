#include "CCRichTextLoader.h"
#include "CCRichTextXMLHandler.h"
#include "CCRichTextXMLAttribute.h"
#include "../support/tinyxml2/tinyxml2.h"
#include <assert.h>
using  namespace  cocos2d;


namespace  cocos2d
{


struct _RICHTEXT_TEMP_NODE_
{
	bool mXMLNode;
	std::string mText;
	_RICHTEXT_TEMP_NODE_()
	{
		mXMLNode = false;
	}
};

class CCRichTextXMLDocument
{
protected:
	CCRichTextXMLHandler* m_pXMLHandler;

public:
	CCRichTextXMLDocument(CCRichTextXMLHandler* pXMLHandler);
	virtual ~CCRichTextXMLDocument();

public:
	/*
		解析指定的Layout布局字节流
	*/
	bool  ParserXMLBuffer(char* pBuffer, unsigned int iBufferLen);

public:
	/*
		解析文件
	*/
	void ProcessElement(tinyxml2::XMLElement* pElement);
};


}


CCRichTextXMLDocument::CCRichTextXMLDocument(CCRichTextXMLHandler* pXMLHandler)
{
	assert(pXMLHandler != NULL);

	m_pXMLHandler = pXMLHandler;
}

CCRichTextXMLDocument::~CCRichTextXMLDocument()
{

}

bool CCRichTextXMLDocument::ParserXMLBuffer(char* pBuffer, unsigned int iBufferLen)
{
	assert(pBuffer != NULL);
	assert(strlen(pBuffer) != 0);

	do 
	{
		tinyxml2::XMLDocument doc;
		if (tinyxml2::XML_NO_ERROR != doc.Parse(pBuffer, iBufferLen))
		{
			break;
		}

		tinyxml2::XMLElement* pElement = doc.RootElement();
		if (pElement)
		{
			try
			{
				ProcessElement(pElement);
			}
			catch(...)
			{
				break;
			}
		}

		return true;
	} 
	while(false);

	return false;
}

void CCRichTextXMLDocument::ProcessElement(tinyxml2::XMLElement* pElement)
{
	CCRichTextXMLAttribute attr;
	const tinyxml2::XMLAttribute* pAttr = pElement->FirstAttribute();
	while (pAttr)
	{
		attr.Add(pAttr->Name(), pAttr->Value());
		pAttr = pAttr->Next();
	}

	m_pXMLHandler->StartElement(pElement->Value(), &attr);
	tinyxml2::XMLNode* pChildNode = pElement->FirstChild();
	while (pChildNode)
	{
		if (dynamic_cast<tinyxml2::XMLElement*>(pChildNode) != NULL)
		{
			ProcessElement(pChildNode->ToElement());
		}

		pChildNode = pChildNode->NextSibling();
	}

	m_pXMLHandler->EndElement(pElement->Value());
}


CCRichTextLoader::CCRichTextLoader()
{
	m_DefaultFontName  = "Heiti SC";
	m_DefaultFontSize  = 24.0f;
	m_DefaultFontColor = ccBLACK;
	m_DefaultAnimationInterval = 0.2f;
}

void CCRichTextLoader::setDefaultFontName(std::string fontName)
{
	m_DefaultFontName = fontName;
}

std::string CCRichTextLoader::getDefaultFontName()
{
	return m_DefaultFontName;
}

void CCRichTextLoader::setDefaultFontSize(float size)
{
	m_DefaultFontSize = size;
}

float CCRichTextLoader::getDefaultFontSize()
{
	return m_DefaultFontSize;
}

void CCRichTextLoader::setDefaultFontColor(ccColor3B color)
{
	m_DefaultFontColor = color;
}

ccColor3B CCRichTextLoader::getDefaultFontColor()
{
	return m_DefaultFontColor;
}

std::list<_RICHTEXT_NODE_> CCRichTextLoader::loadFromBuffer(std::string text)
{
	// 首先解析字符串，因为字符串会包含正常的文字，内部会嵌套<a></a>
	// ，所以先自己过滤一遍
	std::list<_RICHTEXT_TEMP_NODE_> tempList;
	do 
	{
		if (text.size() <= 0)
			break;

		// 先开始找开头<a >
		size_t npos = text.find("<a");
		if (npos == std::string::npos)
		{
			_RICHTEXT_TEMP_NODE_ temp;
			temp.mXMLNode = false;
			temp.mText    = text;
			tempList.push_back(temp);
			break;
		}

		// 提取之前的字符
		if (npos > 0)
		{
			std::string preText = text.substr(0, npos);

			text = (text.c_str()+npos);

			_RICHTEXT_TEMP_NODE_ temp;
			temp.mXMLNode = false;
			temp.mText    = preText;
			tempList.push_back(temp);
		}

		// 开始找</a>
		npos = text.find("</a>");
		if (npos == std::string::npos)
		{// 居然没有找到，异常了，直接跳出
			break;
		}

		// 提出Xml字符串
		std::string preText = text.substr(0, npos+strlen("</a>"));
		_RICHTEXT_TEMP_NODE_ temp;
		temp.mXMLNode = true;
		temp.mText    = preText;
		tempList.push_back(temp);

		text = (text.c_str()+npos+strlen("</a>"));
	} 
	while (true);

	// 解析分割的字符串列表
	std::list<_RICHTEXT_NODE_> myList;
	std::list<_RICHTEXT_TEMP_NODE_>::iterator iter   = tempList.begin();
	std::list<_RICHTEXT_TEMP_NODE_>::iterator iter_e = tempList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (!(*iter).mXMLNode)
		{
			_RICHTEXT_NODE_ temp;
			temp.mNodeType = _RICHTEXT_NODE_::_TYPED_NODE_TEXT_;
			temp.mFontSize = 0.0f;
			temp.mFontName = "";
			temp.mFontColor= this->getDefaultFontColor();
			temp.mText     = (*iter).mText;
			myList.push_back(temp);
		}
		else
		{
			// 解析XML内存字节流
			CCRichTextXMLHandler xmlHandler;
			CCRichTextXMLDocument doc(&xmlHandler);
			if (!doc.ParserXMLBuffer((char*)((*iter).mText.c_str()), (*iter).mText.size()))
				break;

			// 插入Xml富文本列表
			std::list<_RICHTEXT_NODE_> myList2 = xmlHandler.GetNodeList();
			std::list<_RICHTEXT_NODE_>::iterator iter2   = myList2.begin();
			std::list<_RICHTEXT_NODE_>::iterator iter2_e = myList2.end();
			for ( ; iter2!=iter2_e; ++iter2)
			{
				myList.push_back(*iter2);
			}
		}
	}

	// 如果本身为单行，则不需要进行换行处理
	if (myList.size() <= 1)
		return myList;

	// 自行检查换行处理
	std::list<_RICHTEXT_NODE_>::iterator iter2   = myList.begin();
	std::list<_RICHTEXT_NODE_>::iterator iter2_e = myList.end();
	for ( ; iter2!=iter2_e; )
	{
		// 如果非文本，则直接跳过
		if ((*iter2).mNodeType != _RICHTEXT_NODE_::_TYPED_NODE_TEXT_)
		{
			++iter2;
			continue;
		}

		// 查找第一个换行符
		size_t bytes = (*iter2).mText.find("\r");
		if (bytes == 0)
		{
			if ((*iter2).mText.size() == strlen("\r"))
			{// 只剩下换行符
				(*iter2).mLineBreak = true;
				++iter2;
			}
			else
			{
				// 先插入一个换行符节点
				_RICHTEXT_NODE_ temp = (*iter2);
				temp.mText = "\r";
				temp.mLineBreak = true;
				myList.insert(iter2, temp);

				// 当前节点截掉换行符
				(*iter2).mText = (*iter2).mText.c_str()+strlen("\r");
			}
		}
		else if (bytes != std::string::npos)
		{
			std::list<_RICHTEXT_NODE_>::iterator tempIter = iter2;

			// 插入换行符之后的数据
			_RICHTEXT_NODE_ temp = (*iter2);
			temp.mText = (*iter2).mText.c_str()+bytes;
			myList.insert(++tempIter, temp);

			// 当前节点截掉换行符
			(*iter2).mText = (*iter2).mText.substr(0, bytes);
		}
		else
		{
			// 没有找到，则直接跳过
			++iter2;
		}
	}

	return myList;
}

void CCRichTextLoader::setDefaultAnimationInterval(float interval)
{
	m_DefaultAnimationInterval = interval;
}

float CCRichTextLoader::getDefaultAnimationInterval()
{
	return m_DefaultAnimationInterval;
}

CCRichTextLoader* CCRichTextLoader::sharedRichTextLoader()
{
	static CCRichTextLoader loader;
	return &loader;
}
