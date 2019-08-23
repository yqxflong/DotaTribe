#include <cocos2d.h>
#include "../include/ChatPushLogic.h"
#include "../include/LoggerSystem.h"
#include <platform/platform.h>
#include "../include/TimeSystem.h" 
#include "../include/ChatPushDataManager.h"
#include "../include/ChatDataHandler.h"
#include "../include/ChatWindow.h"

using namespace std;

template<> ChatPushLogic* cobra_win::Singleton2<ChatPushLogic>::m_pMySelf = NULL;

ChatPushLogic::ChatPushLogic(){
	isPushing = false;
	m_startTime.clear();
}

ChatPushLogic::~ChatPushLogic(){
	isPushing = false;
	m_startTime.clear();
}

bool ChatPushLogic::Init(){
	return true;
}

void ChatPushLogic::Tick(){
	if( !isPushing ){
		return;
	}
	int index = 0;
	ChatPushData* pData;
	long long currentSecond = TIMESYSTEM->GetCurrentSecond();
	while( (pData = CHATPUSHDATAMANAGER->getDataByID(++index)) != NULL){
		if( currentSecond - m_startTime[index] >= pData->m_interval * 60){
			ChatDataHandler::get_instance2()->PushLocalChatData(pData->m_messageId[rand() % pData->m_messageNum]);
			m_startTime[index] = currentSecond;
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_CHATVIEW_);
		}
	}
}

void ChatPushLogic::Destroy(){
	m_startTime.clear();
	isPushing = false;
}

void ChatPushLogic::ResetTime(){
	m_startTime.clear();
	int length = CHATPUSHDATAMANAGER->GetDataLength();
	long long currentSecond = TIMESYSTEM->GetCurrentSecond();
	for(int i = 0; i < length; i++){
		m_startTime.insert(std::map<int,long long>::value_type(i + 1,currentSecond));
	}
}

void ChatPushLogic::StartPushMsg(bool isFirstLogin){
	if(isFirstLogin)
		ChatDataHandler::get_instance2()->CheckLoginLocalChatData();
	ResetTime();
	isPushing = true;

}