// Name :		ChatDataHandler.h
// Function:	聊天数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan, shaobing

#include <cocos2d.h>
#include "../include/ChatDataHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/TimeSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/SysLangDataManager.h"
#include "../include/ChatPushDataManager.h"
#include "cocos-ext.h"
#include "../include/Common.h"
#include <string>
using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

#define  MaxNum 20
#define  MaxWidth 670  
#define  MaxWidthForPersonal 420
#define	 SystemMaxWidth 670
ChatDataHandler::ChatDataHandler()
{
	m_LastChatData = new ChatData;
}

ChatDataHandler::~ChatDataHandler()
{
	if (World_Chat_List.size()>0)
	{
		std::vector<ChatData*>::iterator iter1 =  World_Chat_List.begin();
		std::vector<ChatData*>::iterator iter1_end =  World_Chat_List.end();
		for (;iter1!=iter1_end;++iter1)
		{
			delete (*iter1);
		}
		World_Chat_List.clear();
	}

	if (World_Show_Chat_List.size()>0)
	{
		std::vector<ShowChatData*>::iterator iter2 =  World_Show_Chat_List.begin();
		std::vector<ShowChatData*>::iterator iter2_end =  World_Show_Chat_List.end();
		for (;iter2!=iter2_end;++iter2)
		{
			delete (*iter2);
		}
		World_Show_Chat_List.clear();
	}

	if (Personal_Chat_List.size()>0)
	{
		std::vector<ChatData*>::iterator iter3 = Personal_Chat_List.begin();
		std::vector<ChatData*>::iterator iter3_end = Personal_Chat_List.end();
		for (;iter3!=iter3_end;++iter3)
		{
			delete (*iter3);
		}
		Personal_Chat_List.clear();
	}

	if (Personal_Show_Chat_List.size()>0)
	{
		std::vector<ShowChatData*>::iterator iter4 = Personal_Show_Chat_List.begin();
		std::vector<ShowChatData*>::iterator iter4_end = Personal_Show_Chat_List.end();
		for (;iter4!=iter4_end;++iter4)
		{
			delete (*iter4);
		}
		Personal_Show_Chat_List.clear();
	}

	if (PlayerInfoList.size()>0)
	{
		std::vector<PlayerInfo*>::iterator iter5 = PlayerInfoList.begin();
		std::vector<PlayerInfo*>::iterator iter5_end = PlayerInfoList.end();
		for (;iter5!=iter5_end;++iter5)
		{
			delete (*iter5);
		}
		PlayerInfoList.clear();
	}

	
	if(m_LastChatData != NULL)
		delete m_LastChatData;
}

void ChatDataHandler::InsertChatData(ChatData* chatData)
{
	m_LastChatData->m_receivePlayerID = chatData->m_receivePlayerID;
	m_LastChatData->m_receivePlayerName = chatData->m_receivePlayerName;
	m_LastChatData->m_sendPlayerID = chatData->m_sendPlayerID;
	m_LastChatData->m_sendPlayerName = chatData->m_sendPlayerName;
	m_LastChatData->m_text = chatData->m_text;
	m_LastChatData->m_time = chatData->m_time;
	m_LastChatData->m_Type = chatData->m_Type;

	switch(chatData->m_Type)
	{
	case _Type_World_:
		{ 
			bool flag =false;
			World_Chat_List.push_back(chatData);
			if (World_Chat_List.size() > MaxNum)
			{
				std::vector<ChatData*>::iterator itor= World_Chat_List.begin();
				delete(*itor);
				World_Chat_List.erase(itor);
				flag = true;
			}
			//UpdateChatData(_Type_World_,chatData,flag);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_CHATVIEW_);
			break;
		}
	case _Type_Personal_:
		{
			//私聊的在世界上也显示
			bool flag =false;
			World_Chat_List.push_back(chatData);
			if (World_Chat_List.size() > MaxNum)
			{
				std::vector<ChatData*>::iterator itor= World_Chat_List.begin();
				delete(*itor);
				World_Chat_List.erase(itor);
				flag = true;
			}
			//UpdateChatData(_Type_World_,chatData,flag);

			flag =false;
			ChatData* pchatData = new ChatData();
			pchatData->m_receivePlayerID = chatData->m_receivePlayerID; 
			pchatData->m_receivePlayerName = chatData->m_receivePlayerName;
			pchatData->m_sendPlayerID = chatData->m_sendPlayerID;
			pchatData->m_sendPlayerName = chatData->m_sendPlayerName;
			pchatData->m_text = chatData->m_text;
			pchatData->m_time = chatData->m_time;
			pchatData->m_Type = chatData->m_Type;
			Personal_Chat_List.push_back(pchatData);
			if (Personal_Chat_List.size() > MaxNum)
			{
				std::vector<ChatData*>::iterator itor= Personal_Chat_List.begin();
				delete(*itor);
				Personal_Chat_List.erase(itor);
				flag =true;
			}
			//UpdateChatData(_Type_Personal_,pchatData,flag);
			
			if (chatData->m_sendPlayerID == RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_)
				ChatDataHandler::get_instance2()->InsertPlayerInfo(chatData->m_receivePlayerID,chatData->m_receivePlayerName);

			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_CHATVIEW_);
			break;
		}
	default:
		break;
	}

}

void ChatDataHandler::InsertPlayerInfo(int id,std::string name)
{

	std::vector<PlayerInfo*>::iterator itor= PlayerInfoList.begin();
	for (;itor!=PlayerInfoList.end();++itor)
	{
		if ((*itor)->m_id == id)
		{
			PlayerInfo* pInfo = new PlayerInfo();
			pInfo->m_id =(*itor)->m_id;
			pInfo->m_name =(*itor)->m_name;

			delete(*itor);
			PlayerInfoList.erase(itor);

			PlayerInfoList.push_back(pInfo);
			return;
		}	
	}

	PlayerInfo* pInfo = new PlayerInfo();
	pInfo->m_id =id;
	pInfo->m_name =name;
	PlayerInfoList.push_back(pInfo);

	if (PlayerInfoList.size() >4)
	{
		std::vector<PlayerInfo*>::iterator itor= PlayerInfoList.begin();
		delete(*itor);
		PlayerInfoList.erase(itor);
	}
		
}
void ChatDataHandler::UpdateChatData(int type,ChatData* data,bool flag, float tabView_Width, std::string fontName, float fontSize) 
{
	ShowChatData* pData = new ShowChatData();
	pData->m_Type = 0;
	pData->m_ChatType = data->m_Type;
	pData->m_sendPlayerID =data->m_sendPlayerID;
	pData->m_sendPlayerName = data->m_sendPlayerName;
	pData->m_time = data->m_time;
	pData->m_receivePlayerID = data->m_receivePlayerID;
	pData->m_receivePlayerName = data->m_receivePlayerName;
	ShowChatData* pData2 = NULL;
	CCImage pImage;
	float timeSize,channelSize,nameSize,otherSize,textSize,totalSize;
	// 时间所占字符长度
	pImage.getStringSize(data->m_time.c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);	
	timeSize = pImage.getWidth();
	if(pData->m_sendPlayerID == -1)							//系统消息
	{
		// 【系统】XXXXXXXXX
		pImage.getStringSize(SysLangDataManager::get_instance2()->GetSysLangById(178).c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		channelSize = pImage.getWidth();
		nameSize = 0;
		otherSize = 0;
	}
	else if(pData->m_ChatType == _Type_World_){				//世界消息
		// 【世界】XXX：
		pImage.getStringSize(SysLangDataManager::get_instance2()->GetSysLangById(176).c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		channelSize = pImage.getWidth();
		pImage.getStringSize(data->m_sendPlayerName.c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		nameSize = pImage.getWidth();
		char other[128] = {0};
		sprintf(other,":");
		pImage.getStringSize(other,0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		otherSize = pImage.getWidth();
	}
	else if(pData->m_ChatType == _Type_Personal_){			//私人消息、
		// 【私聊】XXX对XXX说：
		pImage.getStringSize(SysLangDataManager::get_instance2()->GetSysLangById(177).c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		channelSize = pImage.getWidth();
		pImage.getStringSize(data->m_sendPlayerName.c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		nameSize = pImage.getWidth();
		char other[128] = {0};
		sprintf(other,":%s%s%s", SysLangDataManager::get_instance2()->GetSysLangById(159).c_str(), SysLangDataManager::get_instance2()->GetSysLangById(160).c_str(), SysLangDataManager::get_instance2()->GetSysLangById(161).c_str());
		pImage.getStringSize(other,0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		otherSize = pImage.getWidth();
	}
	// 聊天正文长度
	pImage.getStringSize(data->m_text.c_str(),0,0, CCImage::kAlignTopLeft,fontName.c_str(), fontSize);
	textSize = pImage.getWidth(); 
	totalSize = timeSize + channelSize + textSize + nameSize + otherSize;
	CCLOG("TimeSize:%f ChannelSize:%f NameSize:%f TextSize:%f OtherSize:%f TotalSize:%f.",timeSize,channelSize,nameSize,textSize,otherSize,totalSize);
	// 总长度超过tabview宽度，需要换行生成两个ShowChatData
	if(totalSize > tabView_Width)
	{
		float disWidth = totalSize - tabView_Width;
		std::list<std::string> templist = parser_utf8_string(data->m_text);
		float showPercent = 1.0 - disWidth / textSize;
		std::list<std::string>::iterator itor = templist.begin();
		std::list<std::string>::iterator iend = templist.end();
		int index = 0;
		int totalLength = 0;
		string temp1 = "";
		string temp2 = "";
		// chSize 一个汉字长度 enSize 一个英文字母长度 pbSize 过滤关键字长度
		pImage.getStringSize(SysLangDataManager::get_instance2()->GetSysLangById(159).c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		int chSize = pImage.getWidth();
		int chLength = SysLangDataManager::get_instance2()->GetSysLangById(159).length();
		pImage.getStringSize("a",0,0,CCImage::kAlignTopLeft,fontName.c_str(),fontSize);
		int enSize = pImage.getWidth(); 
		std::list<string> pbText = parser_utf8_string(SysLangDataManager::get_instance2()->GetSysLangById(12021).c_str());
		pImage.getStringSize(SysLangDataManager::get_instance2()->GetSysLangById(12021).c_str(),0,0,CCImage::kAlignTopLeft,fontName.c_str(), fontSize);
		int pbSize = pImage.getWidth();


		for(; itor != iend;){
			// 遍历
			std::list<string>::iterator current = itor;
			std::list<string>::iterator _itor = pbText.begin();
			bool isPb = false;
			// 检查是否有过滤字符,将过滤字符视为一个整体处理
			while( (*current).compare((*_itor).c_str()) == 0 ){
				current++;
				_itor++;
				if(_itor == pbText.end()){
					isPb = true;
					break;
				}
			}

			if(isPb){
				totalLength += pbSize;
				if( totalLength > tabView_Width - timeSize - channelSize - nameSize - otherSize){
					temp2 += SysLangDataManager::get_instance2()->GetSysLangById(12021);
				}
				else{
					temp1 += SysLangDataManager::get_instance2()->GetSysLangById(12021);
				}
				itor = current;
			}
			else
			{
				if( (*itor).length() == 1){
					totalLength += enSize;
				}
				else{
					totalLength += chSize;
				}
				if( totalLength > (tabView_Width - timeSize - channelSize - nameSize - otherSize)){
					temp2 += (*itor);
				}
				else{
					temp1 += (*itor);
				}
				++itor;
			}
		}
		//得到temp1,temp2两个string

		pData->m_text = temp1;

		pData2 = new ShowChatData();
		pData2->m_Type = 1;
		pData2->m_ChatType = data->m_Type;
		pData2->m_sendPlayerID =data->m_sendPlayerID;
		pData2->m_sendPlayerName = data->m_sendPlayerName;
		pData2->m_time = data->m_time;
		pData2->m_receivePlayerID = data->m_receivePlayerID;
		pData2->m_receivePlayerName = data->m_receivePlayerName;
		pData2->m_text = temp2;
	}
	else{
		pData->m_text = data->m_text;
	}
	// 将ShowChatData添加到List中
	if( type == _Type_World_){
		if(pData != NULL)
			World_Show_Chat_List.push_back(pData);
		if(pData2 != NULL)
			World_Show_Chat_List.push_back(pData2);
		while(World_Show_Chat_List.size()>MaxNum)
		{
			std::vector<ShowChatData*>::iterator itor= World_Show_Chat_List.begin();
			delete(*itor);
			World_Show_Chat_List.erase(itor);
		}
	}
	else if( type == _Type_Personal_)
	{
		if(pData != NULL)
			Personal_Show_Chat_List.push_back(pData);
		if(pData2 != NULL)
			Personal_Show_Chat_List.push_back(pData2);
		while (Personal_Show_Chat_List.size() >MaxNum)
		{
			std::vector<ShowChatData*>::iterator itor= Personal_Show_Chat_List.begin();
			delete(*itor);
			Personal_Show_Chat_List.erase(itor);
		}
	}
}

void ChatDataHandler::handlePacket(IPacket* packet){

}

bool ChatDataHandler::init(){
	return true;
}

void ChatDataHandler::onDestroy(){
	std::vector<ChatData*>::iterator iter1 =  World_Chat_List.begin();
	std::vector<ChatData*>::iterator iter1_end =  World_Chat_List.end();
	for (;iter1!=iter1_end;++iter1)
	{
		delete (*iter1);
	}
	World_Chat_List.clear();

	std::vector<ShowChatData*>::iterator iter2 =  World_Show_Chat_List.begin();
	std::vector<ShowChatData*>::iterator iter2_end =  World_Show_Chat_List.end();
	for (;iter2!=iter2_end;++iter2)
	{
		delete (*iter2);
	}
	World_Show_Chat_List.clear();


	std::vector<ChatData*>::iterator iter3 = Personal_Chat_List.begin();
	std::vector<ChatData*>::iterator iter3_end = Personal_Chat_List.end();
	for (;iter3!=iter3_end;++iter3)
	{
		delete (*iter3);
	}
	Personal_Chat_List.clear();


	std::vector<ShowChatData*>::iterator iter4 = Personal_Show_Chat_List.begin();
	std::vector<ShowChatData*>::iterator iter4_end = Personal_Show_Chat_List.end();
	for (;iter4!=iter4_end;++iter4)
	{
		delete (*iter4);
	}
	Personal_Show_Chat_List.clear();

	std::vector<PlayerInfo*>::iterator iter5 = PlayerInfoList.begin();
	std::vector<PlayerInfo*>::iterator iter5_end = PlayerInfoList.end();
	for (;iter5!=iter5_end;++iter5)
	{
		delete (*iter5);
	}
	PlayerInfoList.clear();

	m_LastChatData->m_text = "";
}

// 推送本地消息
void ChatDataHandler::PushLocalChatData(int sysid){
	std::string msg = SysLangDataManager::get_instance2()->GetSysLangById(sysid);

	ChatData* pChatData = new ChatData();
	pChatData->m_Type = _Type_World_;
	pChatData->m_sendPlayerID = -1;
	pChatData->m_sendPlayerName = SysLangDataManager::get_instance2()->GetSysLangById(5008);
	pChatData->m_receivePlayerID = RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_;
	pChatData->m_receivePlayerName = RoleInfoDataHandler::get_instance2()->m_pRIData->name_;
	time_t _time;
	time(&_time);
	struct tm *p = localtime(&_time); 
	int sec = p->tm_sec;
	int min = p->tm_min;
	int hour = p->tm_hour;
	
	char time_c[10];
	sprintf(time_c,"%02d:%02d:%02d",hour,min,sec);
	pChatData->m_time = time_c;
	pChatData->m_text = msg;

	CCLOG("%s(%d) send to %s(%d) [%s]: %s",(pChatData->m_sendPlayerName).c_str(),
		pChatData->m_sendPlayerID, (pChatData->m_receivePlayerName).c_str(), pChatData->m_receivePlayerID,
		(pChatData->m_time).c_str(), (pChatData->m_text).c_str());

	InsertChatData(pChatData);
}

// 检查登录时就要推送的本地消息
void ChatDataHandler::CheckLoginLocalChatData(){
	int index = 0;
	ChatPushData *pPushData;
	while( (pPushData = ChatPushDataManager::get_instance2()->getDataByID(++index)) != NULL){
		if( pPushData->m_isLoginPush ){
			PushLocalChatData(pPushData->m_messageId[rand()%pPushData->m_messageNum]);
		}
	}
}