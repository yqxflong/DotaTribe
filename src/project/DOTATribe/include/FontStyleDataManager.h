//Name��FontStyleDataManager
//Func:		���ڶ�ȡ������ʽ
//Written By����ǿ

#ifndef   _DOTATRIBE_FontStyleDataManager_H
#define   _DOTATRIBE_FontStyleDataManager_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class   FSData: public IData
{
public:
	int idx_;
	char fontname_[128];
	float fontsize_;
	int colorR_;
	int colorG_;
	int colorB_;
public:
	FSData();
	virtual ~FSData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class FontStyleDataManager : public IDataManager, public cobra_win::Singleton2<FontStyleDataManager>
{
public:
	std::map<int,FSData*> m_map;
public:
	FontStyleDataManager(bool bLoadFromDB, bool bEncryption):IDataManager(bLoadFromDB, bEncryption){};
	virtual ~FontStyleDataManager(){};

public:
	FSData* getDataByID(int idx);
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
	friend   class   cobra_win::Singleton2<FontStyleDataManager>;
};

#define  FONTSTYLEDATAMANAGER  FontStyleDataManager::get_instance2()
  
#endif