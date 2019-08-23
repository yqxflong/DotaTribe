#ifndef   _DOTATRIBE_CAMERASHAKEDATAMANAGER_H
#define   _DOTATRIBE_CAMERASHAKEDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   CameraShakeData: public IData
{
public:
      int    shakeItemID_;                     //��ID
	  int    halfCircleTime_;					//������ʱ��
	  int    shakeItemType_;                   //������
	  float  shakeX_;           //���ҵ����
      float  shakeY_;           //�������
      int    containTime_;					   //�𶯳���ʱ��
	 
public:
	CameraShakeData();
	~CameraShakeData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class CameraShakeDataManager : public IDataManager, public cobra_win::Singleton2<CameraShakeDataManager>
{
public:
	std::map<int, CameraShakeData*>  m_CameraShakeDataMap_;

public:
	CameraShakeDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~CameraShakeDataManager();

public:
	
    CameraShakeData * GetCamerShakeDataByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<CameraShakeDataManager>;

};
  
#endif