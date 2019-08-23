//Name:DotaPacket
//Function:提供dota项目的基础包方法,简化使用
//Date:20131210

#ifndef  _DOTATRIBE_DOTAPACKET_H_
#define  _DOTATRIBE_DOTAPACKET_H_

#include "../include/IPacket.h"
#include <include/mem/MemNode.h>
#include <vector>
#include "../include/NetSystem.h"


//template <class _DATA_TYPE_>

class DotaPacket : public IPacket
{
private:
	std::vector<char> paramVector;
public:
	void PushData(char data)
	{
		paramVector.push_back(data);
	};
	void PushData(unsigned char data)
	{
		PushData((char)data);
	};
	void PushData(int data)
	{
		char temp = 0;
		temp = (data >> 0) & 0x000000ff;
		PushData(temp);
		temp = (data >> 8) & 0x000000ff;
		PushData(temp);
		temp = (data >> 16) & 0x000000ff;
		PushData(temp);
		temp = (data >> 24) & 0x000000ff;
		PushData(temp);
	};
	void PushData(unsigned int data)
	{
		PushData((int)data);
	};
	void PushData(short data)
	{
		char temp = 0;
		temp = (data >> 0) & 0x00ff;
		PushData(temp);
		temp = (data >> 8) & 0x00ff;
		PushData(temp);
	};
	void PushData(unsigned short data)
	{
		PushData((short)data);
	};
	void PushData(std::string data)
	{
		unsigned short size = data.length();
		PushData(size);
		const char * buffer = data.c_str();
		for(int i = 0; i < size; ++i)
		{
			PushData(buffer[i]);
		}
	};
	void PushData(const char * data)
	{
		unsigned short size = 0;
		while(data[size++] != '\0');

		PushData(size);

		for(int i = 0; i < size; ++i)
		{
			PushData(data[i]);
		}
	};

	virtual  bool  Read(char* pBuffer, unsigned int iLen)
	{
		return false;
	};

	virtual void Send()
	{
		m_PacketTyper = GetPacketType();
		m_PacketLength = GetPacketLength();

		MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
		pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
		pNode->push(m_PacketLength);
		pNode->push(m_PacketTyper);
		for(int i = 0; i < (int)paramVector.size(); ++i)
		{
			pNode->push(paramVector[i]);	
		}
		NETSYSTEM->SendPacket(pNode);
	};

	virtual void SendHttp()
	{
		m_PacketTyper = GetPacketType();
		m_PacketLength = GetPacketLength();
		//减掉头ZR和长度len的size
		m_PacketLength-=sizeof(m_PacketPrefix)+sizeof(m_PacketLength);
		MemNode * pNode = NETSYSTEM->QueryMemNode(m_PacketLength);
		pNode->push(m_PacketTyper);
		for(int i = 0; i < (int)paramVector.size(); ++i)
		{
			pNode->push(paramVector[i]);	
		}
		NETSYSTEM->SendHTTPPacket(pNode);
	};

	virtual  unsigned  int  GetPacketLength()
	{
		int length = sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
		for(int i = 0; i < (int)paramVector.size(); ++i)
		{
			length += sizeof(paramVector[i]);
		}
		return length;
	}

public:
	DotaPacket()
	{
		m_PacketPrefix[0] = 'Z';
		m_PacketPrefix[1] = 'R';

	}
	~DotaPacket()
	{
		paramVector.clear();
	}


};

#endif
