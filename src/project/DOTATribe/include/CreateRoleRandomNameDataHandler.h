// Name :		CreateRoleRandomNameDataHandler.h
// Function:	角色随机姓名数据
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef   _DOTATRIBE_CREATEROLERANDOMNAMEDATAHANDLER_H
#define   _DOTATRIBE_CREATEROLERANDOMNAMEDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>

class CreateRoleRandomNameDataHandler:public IDataHandler,public cobra_win::Singleton2<CreateRoleRandomNameDataHandler>{
public:

	std::string m_PlayerName;
public:
	CreateRoleRandomNameDataHandler();
	virtual ~CreateRoleRandomNameDataHandler();
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	void SetPlayerName(std::string name){m_PlayerName = name;};
	std::string GetPlayerName(){return m_PlayerName;};
};
#endif