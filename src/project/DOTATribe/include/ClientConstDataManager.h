//Name��ClientConstDataManager
//Written By����ǿ

#ifndef   _DOTATRIBE_ClientConstDataManager_H
#define   _DOTATRIBE_ClientConstDataManager_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class   ClientConstData: public IData
{
public:
	char key_[128];
	int value_;
public:
	ClientConstData();
	virtual ~ClientConstData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)
 


class ClientConstDataManager : public IDataManager, public cobra_win::Singleton2<ClientConstDataManager>
{
private:
	std::map<std::string,int> m_mapList;
public:
	ClientConstDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){};
	virtual ~ClientConstDataManager(){};

public:
	int getValueByKey(const char* key);
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

};

#define  CLIENTCONSTDATAMANGER  ClientConstDataManager::get_instance2()
  
#endif