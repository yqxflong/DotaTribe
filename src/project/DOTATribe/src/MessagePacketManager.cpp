#include  <cocos2d.h>
#include "../include/LoggerSystem.h"
#include  "../include/MessagePacketManager.h"
#include  "../include/AthleticsSceneManager.h"
#include  "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>


MessagePacketManager::MessagePacketManager()
{
	m_ObjectList.clear(); 
}

MessagePacketManager::~MessagePacketManager()
{

}

bool  MessagePacketManager::Init()
{
	m_ObjectList.clear();
	return true;
}

void MessagePacketManager::Tick()
{
	//if(ATHLETICSSCENEMANAGER->IsGameOver())
	//{
	//	Destroy(); 
	//	return ;
	//}
	std::list<MessagePacket *>::iterator beginIter=m_ObjectList.begin();
	while(beginIter!=m_ObjectList.end())
	{
		if((*beginIter)->IsValid())
		{
			(*beginIter)->Tick();
		}
		else
		{
			//销毁
			beginIter=DeleteObject(*beginIter);
		}
		if(beginIter==m_ObjectList.end())
		{
			return ;
		}
		beginIter++;
	}
}

void  MessagePacketManager::Destroy()
{
	if(m_ObjectList.size()>0)
	{
		std::list<MessagePacket *>::iterator baseIter=m_ObjectList.begin();
		while(baseIter!=m_ObjectList.end())
		{
			(*baseIter)->Destroy();
			delete (*baseIter);
			baseIter++;
		}
		m_ObjectList.clear();
	}
}

MessagePacket* MessagePacketManager::GetObjectById(int  objectId)
{
	return NULL;
}

bool  MessagePacketManager::PushCommand(int EventTypeID,void * ptr)
{
	std::list<MessagePacket *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		if((*baseIter)->IsValid())
		{
			(*baseIter)->OnCommandHanlder(EventTypeID,ptr);
		}
		baseIter++;
	}
	return true;
}


int   MessagePacketManager::GetObjectCount()
{
	return m_ObjectList.size();
}



std::list<MessagePacket*>& MessagePacketManager::GetObjectList()
{
	return  m_ObjectList;
}


void  MessagePacketManager::RemoveAlBaseObject()
{
	std::list<MessagePacket *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		(*baseIter)->Destroy();
		delete (*baseIter);
		baseIter++;
	}
	m_ObjectList.clear();
}

void  MessagePacketManager::InsertObject(MessagePacket* pObject)
{
	if(pObject!=NULL)
	{
		m_ObjectList.push_back(pObject);
	}
}


void  MessagePacketManager::PurgeAllChildren()
{

	std::list<MessagePacket *>::iterator baseIter=m_ObjectList.begin();
	while(baseIter!=m_ObjectList.end())
	{
		if((*baseIter)!=NULL)
		{
			(*baseIter)->SetIsValid(false);
		}
		baseIter++;
	}  
}


std::list<MessagePacket *>::iterator    MessagePacketManager::DeleteObject(MessagePacket* pObject)
{
	std::list<MessagePacket *>::iterator  objectIter=m_ObjectList.begin();
	while(objectIter!=m_ObjectList.end())
	{
		if((*objectIter)==pObject)
		{
			(*objectIter)->Destroy();
			delete (*objectIter);
			objectIter=m_ObjectList.erase(objectIter);
			CCLOG("success Delete Object!");
			return objectIter;
		}
		objectIter++;
	}
	return  m_ObjectList.end();
}

void  MessagePacketManager::DeleteAllObject()
{

}

char *MessagePacketManager::ParserDataFromServer()
{
	char*        pBuffer = NULL;
	unsigned int iLength = 0;
	// 加载文件
	if (!EngineSystem::LoadAppFile((char*)GetName().c_str(), pBuffer, iLength))
		return false;

	// 构建DPacket解包器
	DPacket packet(pBuffer, iLength+1);

	// 跳过第一行
	char   buffer[10240] = "";
	size_t pos = 0;
	do 
	{
		if (pos == sizeof(buffer))
			return false;

		if (packet.get_read_pos() >= packet.size())
			return false;

		packet.read(buffer+pos, 1);
		if (pos>0 && *(buffer+pos)=='\r')
			break;

		pos++;
	}
	while(true);

	// 逐行读取解析
	do 
	{
		char   buffer[10240] = "";
		size_t num           = 0;
		bool   reset         = false;

		{
			size_t pos = 0;
			do 
			{
				if (pos == sizeof(buffer))
				{
					reset = true;
					break;
				}

				if (packet.get_read_pos() >= packet.size())
					break;

				packet.read(buffer+pos, 1);
				if (pos>0 && *(buffer+pos)=='\n')
				{
					if (*(buffer+pos-1) == '\r')
					{
						*(buffer+pos-1) = '\0';
					}

					*(buffer+pos) = '\0';
					num = pos;
					break;
				}

				pos++;
			}
			while(true);
		}

		if (reset || num<=2)
			break;

		if (!LoadData(buffer, num-1))
			return pBuffer;

	}
	while (true);

	delete []pBuffer;
	return NULL;
}

std::string MessagePacketManager::GetName()
{
	return NULL;
}

bool MessagePacketManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	return true;
}

