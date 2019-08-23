#ifndef  _DOTATRIBE_PACKETFACTORYMANAGER_H_
#define  _DOTATRIBE_PACKETFACTORYMANAGER_H_


#include <include/common/Singleton.h>
#include <map>
using  namespace  cobra_win;

class IPacketFactory;
class PacketFactoryManager : public cobra_win::Singleton<PacketFactoryManager>
{
public:
	std::map<int, IPacketFactory*> m_PacketFactoryList;

public:
	PacketFactoryManager();
	~PacketFactoryManager();

public:
	/*
		注册网络数据包管理器
	*/
	void  RegisterFactory(IPacketFactory* pPacketFactory);
	/*
		根据类型得到对应的数据包管理器
	*/
	IPacketFactory* GetPacketFactoryByType(unsigned int type);

public:
	/*
		初始化网络数据包处理管理器
	*/
	bool  Init();
	/*
		网络数据包处理管理器帧更新
	*/
	void  Tick();
	/*
		销毁网络数据包处理管理器
	*/
	void  Destroy();

public:
	friend  class  cobra_win::Singleton<PacketFactoryManager>;
};

#define  PACKETFACTORYMANAGER  (PacketFactoryManager::get_instance())


#endif
