//Name : ����IDά����
//Function : ID��string�Ķ�Ӧ
//Author : ����
//Data : 2013-7-29


#ifndef   _DOTATRIBE_IDSTRINGDATAMANAGER_H
#define   _DOTATRIBE_IDSTRINGDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <vector>

#pragma pack(push, 1)

class   IDStringData: public IData
{
public:
	int mTag;
	int mSubTag;
	std::string mString;
public:
	IDStringData();
	~IDStringData(){};

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class IDStringDataManager: public IDataManager, public cobra_win::Singleton2<IDStringDataManager>
{
public:
	std::map<int, std::vector<std::string> > m_IDStringDataList;

public:
	IDStringDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~IDStringDataManager();

public:
	
	std::string GetIDStringByID(int tag, int subTag);

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
	friend   class   cobra_win::Singleton2<IDStringDataManager>;

};

#define IDSTRINGDATAMANAGER (IDStringDataManager::get_instance2())

#endif