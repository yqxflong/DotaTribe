
#ifndef _LUA_BASEHELPER_H_
#define _LUA_BASEHELPER_H_


#include <string>

class BaseHelper
{
public:
	virtual ~BaseHelper(){

	};

public:
	virtual void BuildInstance(std::string name, BaseHelper * helper) = 0;

};

#endif
