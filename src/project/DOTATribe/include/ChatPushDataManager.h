//Name��ChatPushDataManager
//Written By���۱�

#ifndef   _DOTATRIBE_CHATPUSHDATAMANAGER_H
#define   _DOTATRIBE_CHATPUSHDATAMANAGER_H

#include <cocos2d.h>
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <vector>

class   ChatPushData: public IData
{
public:
	int		m_id;	
	int		m_interval;	
	bool	m_isLoginPush;
	int		m_messageNum;
	std::vector<int>	m_messageId;
public:
	ChatPushData();
	virtual ~ChatPushData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
 

class ChatPushDataManager : public IDataManager, public cobra_win::Singleton2<ChatPushDataManager>
{
public:
	std::map<int,ChatPushData *>  m_chatPushDataMap;
public:
	ChatPushDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){
		m_chatPushDataMap.clear();
	};

	virtual ~ChatPushDataManager(){};

public:
	/*
		ͨ��ID�õ�����
	*/	
	ChatPushData* getDataByID(int idx);
	/*
		�õ����ݵĸ���
	*/
	int GetDataLength();
	/*
		�õ���Ӧ�����ݹ���������
	*/
	virtual  std::string   GetName();
	/*
		�õ���Ӧ�����ݹ������ڴ�ռ�ô�С
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		��ʼ�����ݹ�����
	*/
	virtual  bool  Init();
	/*
		���ݹ�����֡���´���
	*/
	virtual  void  Tick();
	/*
		�������ݹ�����
	*/
	virtual  void  Destroy();
	//
	//
public:
	/*
		У����ص�����(�������ݵ���Ч��У��)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		У����ص�����(�������ݼ�����֮����еı���������У��)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		����ָ����ItemData����
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<ChatPushDataManager>;
};

#define  CHATPUSHDATAMANAGER  ChatPushDataManager::get_instance2()
  
#endif