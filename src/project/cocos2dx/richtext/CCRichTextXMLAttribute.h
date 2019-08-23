#ifndef  _RICHTEXTLOADER_XMLATTRIBUTE_H_
#define  _RICHTEXTLOADER_XMLATTRIBUTE_H_


#include <string>
#include <map>

namespace  cocos2d
{


class CCRichTextXMLAttribute
{
private:
	std::map<std::string, std::string> m_Attributes;

public:
	CCRichTextXMLAttribute();
	~CCRichTextXMLAttribute();

public:
	/*
		得到属性的个数
	*/
	int   GetCount();
	/*
		增加指定的属性(KEY-VALUE)
	*/
	void  Add(std::string attrName, std::string attrValue);
	/*
		删除指定名称的属性值
	*/
	void  Remove(std::string attrName);
	/*
		是否存在指定名称的属性值
	*/
	bool  IsExist(std::string attrName);

public:
	/*
		得到指定索引下标的属性名称
	*/
	std::string GetName(int index);
	/*
		得到指定索引下标的属性数值
	*/
	std::string GetValue(int index);
	/*
		得到指定属性名称的属性值
	*/
	std::string GetValue(std::string attrName);

public:
	/*
		返回字符串类型的属性值
	*/
	std::string GetValueAsString(std::string attrName);
	/*
		返回BOOL类型的属性值
	*/
	bool        GetValueAsBool(std::string attrName);
	/*
		返回FLOAT类型的属性值
	*/
	float       GetValueAsFloat(std::string attrName);
	/*
		返回INT类型的属性值
	*/
	int         GetValueAsInt(std::string attrName);
};


}


#endif
