// Name :		ActivityDataManager.h
// Function:	����ݹ�����
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_ACTIVITYDATAMANAGER_H
#define   _DOTATRIBE_ACTIVITYDATAMANAGER_H
 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   Activity: public IData
{
public:
	int  m_nActivityType; 							//�����
	int  m_nActivityWindowID;				  		//����ID  
	int m_nUseLua;				//�����Ƿ�ʹ����lua
	int m_nShowEventId;			//������ʾ�¼�
	int m_nHideEventId;			//���������¼�
	int m_nShowActivityBg;		//�Ƿ���ʾ����ڵı���ͼ
public:
	Activity();
	~Activity(); 
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class ActivityManager: public IDataManager, public cobra_win::Singleton2<ActivityManager>
{
public:
	std::map<int,  Activity*> m_ActivityList; 
public:
	ActivityManager(bool bLoadFromDB, bool bEncryption);
	virtual ~ActivityManager();

public:
	
    Activity * GetDataByType(int Id);

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
	friend   class   cobra_win::Singleton2<Activity>;

};
  
#endif