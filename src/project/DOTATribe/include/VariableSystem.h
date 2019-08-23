//Name: VariableSystem
//Func: 读写Xml文件
//Author: CY
#ifndef  _DOTATRIBE_VARIABLESYSTEM_H_
#define  _DOTATRIBE_VARIABLESYSTEM_H_

#include <include/common/Singleton.h>
#include <string>
#include <map>
using  namespace  cobra_win;

class VariableSystem : public cobra_win::Singleton2<VariableSystem>
{
public:
	/*
		配置文件类型
	*/
	enum ConfigType
	{
		_TYPED_CONFIG_UNKOWN_, // 未知类型的配置文件
		_TYPED_CONFIG_LOGGER_, // 日志对应的配置文件
		_TYPED_CONFIG_SYSTEM_, // 系统对应的配置文件
		_TYPED_CONFIG_ACCOUNT_,// 帐号对应的配置文件
		_TYPED_CONFIG_MEM_,    // 内存数据配置文件
	};

public:
	/*
		变量结构体定义
	*/
	struct _VARIBLE_
	{
		ConfigType  mFileType;     // 所属配置文件类型
		char        mSection[256]; // 所属标签页名称
		char        mKey[256];     // 所属Key值名称
		char        mValue[256];   // 对应的Value数值
		_VARIBLE_()
		{
			memset(this, 0, sizeof(_VARIBLE_));
		}
	};

private:
	std::map<ConfigType, std::string>      m_ConfigFileList;// 配置文件列表
	std::multimap<std::string, _VARIBLE_*> m_VaribleList;   // 配置变量列表

public:
	VariableSystem();
	virtual ~VariableSystem();

public:
	/*
		得到对应类型配置文件的名称
	*/
	char*    GetConfigName(ConfigType FileType);
	/*
		动态加载制定的配置文件
	*/
	bool     LoadConfigByType(ConfigType FileType, char* pFileName);
	/*
		动态卸载制定的配置文件(保存到文件)
	*/
	void     UnLoadConfigByType(ConfigType FileType);

public:
	/*
		得到对应配置文件中标签的数值(bool)
	*/
	bool     GetVariable(ConfigType FileType, char* pSection, char* pKey, bool& bValue);
	/*
		得到对应配置文件中标签的数值(int)
	*/
	bool     GetVariable(ConfigType FileType, char* pSection, char* pKey, int& iValue);
	/*
		得到对应配置文件中标签的数值(long long)
	*/
	bool     GetVariable(ConfigType FileType, char* pSection, char* pKey, long long& iValue);
	/*
		得到对应配置文件中标签的数值(float)
	*/
	bool     GetVariable(ConfigType FileType, char* pSection, char* pKey, float& fValue);
	/*
		得到对应配置文件中标签的数值(byte)
	*/
	bool     GetVariable(ConfigType FileType, char* pSection, char* pKey, char& value);
	/*
		得到对应配置文件中标签的数值(string)
	*/
	bool     GetVariable(ConfigType FileType, char* pSection, char* pKey, char* pValue, unsigned int iValueLen);
	/*
		设置对应配置文件中标签的数值(bool)
	*/
	bool     SetVariable(ConfigType FileType, char* pSection, char* pKey, bool bValue);
	/*
		设置对应配置文件中标签的数值(int)
	*/
	bool     SetVariable(ConfigType FileType, char* pSection, char* pKey, int iValue);
	/*
		设置对应配置文件中标签的数值(long long)
	*/
	bool     SetVariable(ConfigType FileType, char* pSection, char* pKey, long long iValue);
	/*
		设置对应配置文件中标签的数值(float)
	*/
	bool     SetVariable(ConfigType FileType, char* pSection, char* pKey, float fValue);
	/*
		设置对应配置文件中标签的数值(byte)
	*/
	bool     SetVariable(ConfigType FileType, char* pSection, char* pKey, char value);
	/*
		设置对应配置文件中标签的数值(string)
	*/
	bool     SetVariable(ConfigType FileType, char* pSection, char* pKey, char* pValue);

public:
	//@标配
	bool     Init();
	void     Tick();
	void     Destroy();

private:
	/*
		保存指定类型的配置文件
	*/
	void     SaveConfigByType(ConfigType FileType);
	/*
		加载制定类型的配置文件
	*/
	bool     LoadConfigFile(ConfigType FileType, std::string FileName);
	/*
		保存制定类型的配置文件信息(暂定传入参加的方式，后续需要改进，提升性能)
	*/
	void     SaveConfigFile(ConfigType FileType, std::string FileName);

public:
	VariableSystem* GetLuaInstance(){
		return VariableSystem::get_instance2();
	}
};

#define  VARIABLESYSTEM  (VariableSystem::get_instance2())


#endif
