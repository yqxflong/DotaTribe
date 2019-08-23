// Name :		ChatDataHandler.h
// Function:	聊天数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan,shaobing

#ifndef   _DOTATRIBE_CHATDATAHANDLER_H
#define   _DOTATRIBE_CHATDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>
#include <map>
struct ChatData
{
	unsigned char m_Type;
	int	m_sendPlayerID;
	std::string m_sendPlayerName;
	std::string m_time;
	int	m_receivePlayerID;
	std::string m_receivePlayerName;
	std::string m_text;
};

struct ShowChatData
{
	int m_Type;					//是否是一整句
	int m_sendPlayerID;	
	std::string m_sendPlayerName;
	std::string m_time;
	int m_ChatType;
	int	m_receivePlayerID;
	std::string m_receivePlayerName;
	std::string m_text;
};

struct PlayerInfo
{
	int m_id;				
	std::string m_name;
	
};


class ChatDataHandler:public IDataHandler,public cobra_win::Singleton2<ChatDataHandler>{
public:
	enum
	{
		_Type_World_,
		_Type_Personal_,
		_Type_System_,
	};
	ChatData* m_LastChatData;
	std::vector<ChatData*> World_Chat_List;
	std::vector<ShowChatData*> World_Show_Chat_List;
	std::vector<ChatData*> Personal_Chat_List;
	std::vector<ShowChatData*> Personal_Show_Chat_List;
	std::vector<PlayerInfo*> PlayerInfoList;
public:
	ChatDataHandler();
	virtual ~ChatDataHandler();
	void InsertChatData(ChatData* chatData);
	void InsertPlayerInfo(int id,std::string name);
	//void UpdateChatData(int type,ChatData* data,bool flag, float SYS_Width, float World_Width, float Person_Width);
	void UpdateChatData(int type,ChatData* data,bool flag, float tabView_Width, std::string fontName, float fontSize);
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();

public:

	void PushLocalChatData(int sysid);

	void CheckLoginLocalChatData();
};
#endif