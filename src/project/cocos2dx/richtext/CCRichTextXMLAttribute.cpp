#include "CCRichTextXMLAttribute.h"
#include <sstream>
#include <iterator>
#include <assert.h>
using  namespace  cocos2d;


CCRichTextXMLAttribute::CCRichTextXMLAttribute()
{
	m_Attributes.clear();
}

CCRichTextXMLAttribute::~CCRichTextXMLAttribute()
{

}

int CCRichTextXMLAttribute::GetCount()
{
	return m_Attributes.size();
}

void CCRichTextXMLAttribute::Add(std::string attrName, std::string attrValue)
{
	m_Attributes[attrName] = attrValue;
}

void CCRichTextXMLAttribute::Remove(std::string attrName)
{
	std::map<std::string, std::string>::iterator iter = m_Attributes.find(attrName);
	if (iter != m_Attributes.end())
		m_Attributes.erase(iter);
}

bool CCRichTextXMLAttribute::IsExist(std::string attrName)
{
	return m_Attributes.find(attrName) != m_Attributes.end();
}

std::string CCRichTextXMLAttribute::GetName(int index)
{
	if (index >= GetCount())
	{
		assert(0);
	}

	std::map<std::string, std::string>::const_iterator iter = m_Attributes.begin();
	std::advance(iter, index);
	return (*iter).first;
}

std::string CCRichTextXMLAttribute::GetValue(int index)
{
	if (index >= GetCount())
	{
		assert(0);
	}

	std::map<std::string, std::string>::const_iterator iter = m_Attributes.begin();
	std::advance(iter, index);
	return (*iter).second;
}

std::string CCRichTextXMLAttribute::GetValue(std::string attrName)
{
	std::map<std::string, std::string>::const_iterator iter = m_Attributes.find(attrName);
	if (iter == m_Attributes.end())
	{
		assert(0);
	}

	return (*iter).second;
}

std::string CCRichTextXMLAttribute::GetValueAsString(std::string attrName)
{
	if (!IsExist(attrName))
		return "";

	return GetValue(attrName);
}

bool CCRichTextXMLAttribute::GetValueAsBool(std::string attrName)
{
	if (!IsExist(attrName))
		return false;

	std::string value = GetValue(attrName);
	if (value=="false" || value=="0")
		return false;

	if (value=="true" || value=="1")
		return true;

	assert(0);
	return false;
}

float CCRichTextXMLAttribute::GetValueAsFloat(std::string attrName)
{
	if (!IsExist(attrName))
		return 0.0f;

	float value = 0.0f;
	std::istringstream str(GetValue(attrName).c_str());
	str >> value;
	if (str.fail())
		assert(0);

	return value;
}

int CCRichTextXMLAttribute::GetValueAsInt(std::string attrName)
{
	if (!IsExist(attrName))
		return 0;

	int value = 0;
	std::istringstream str(GetValue(attrName).c_str());
	str >> value;
	if (str.fail())
		assert(0);

	return value;
}
