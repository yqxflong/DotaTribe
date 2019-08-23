//Name£ºChatPushDataManager
//Written By£ºÉÛ±ø

#include "../include/ChatPushDataManager.h"
#include "../include/DBSystem.h"
#include <include/common/Parser.h>
#include "../include/LoggerSystem.h"

using  namespace  cobra_win;
using namespace std;

ChatPushData::ChatPushData()
{
	m_id = -1;
	m_interval = -1;
	m_isLoginPush = false;
	m_messageNum = -1;
	m_messageId.clear();
}

bool  ChatPushData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	bool isErr=false;
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(m_id))
		isErr=true;

	if (!parser.parser_int_value(m_interval))
		isErr=true;

	if (!parser.parser_bool_value(m_isLoginPush))
		isErr=true;

	if (!parser.parser_int_value(m_messageNum))
		isErr=true;

	for( int i = 0; i < m_messageNum; i ++ ){
		int messageid = 0;
		if( !parser.parser_int_value(messageid) ){
			isErr = true;
			break;
		}
		m_messageId.push_back(messageid);
	}

	if (isErr)
	{
		LOGGERSYSTEM->LogInfo("Err: ChatPushData read Error!");
		return false;
	}
	return true; 
}

template<> ChatPushDataManager* cobra_win::Singleton2<ChatPushDataManager>::m_pMySelf = NULL;


ChatPushData* ChatPushDataManager::getDataByID(int idx){

	std::map<int,ChatPushData *>::iterator iter=m_chatPushDataMap.find(idx);
	if(iter!=m_chatPushDataMap.end())
	{
		return iter->second;
	}
	return NULL;
}

int ChatPushDataManager::GetDataLength(){
	return m_chatPushDataMap.size();
}

std::string   ChatPushDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/chatpushdata.txt";

	return "chatpushdata";
} 


unsigned  int ChatPushDataManager::GetSize()
{
	return m_chatPushDataMap.size()*sizeof(ChatPushData);
}


bool  ChatPushDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
		{
			if (!LoadFromDB())
				break;
		}
		else
		{
			if (!LoadFromFile())
				break;
		}

		return true;
	} 
	while(false);
	return false;
}


void  ChatPushDataManager::Tick()
{

}


void  ChatPushDataManager::Destroy()
{
	std::map<int, ChatPushData*>::iterator iter   = m_chatPushDataMap.begin();
	std::map<int, ChatPushData*>::iterator iter_e = m_chatPushDataMap.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	return m_chatPushDataMap.clear();
} 


bool  ChatPushDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ChatPushData* item = (ChatPushData*)pData;
	assert(item != NULL);

	return true;
}

bool  ChatPushDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ChatPushDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	ChatPushData* pItemData = new ChatPushData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;
	m_chatPushDataMap.insert(std::map<int,ChatPushData *>::value_type(pItemData->m_id,pItemData));
	return true;
}