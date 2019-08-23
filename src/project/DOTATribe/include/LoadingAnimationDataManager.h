// Name :		LoadingAnimationDataManager.h
// Function:	Loading�������ݹ���
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_LOADINGANIMATIONDATAMANAGER_H
#define   _DOTATRIBE_LOADINGANIMATIONDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   LoadingAnimationData: public IData
{
public:
	int  mId; 									//ID
	int  mProcedureId; 							//����ID
	int  mIsNeedAnimation;						//�Ƿ���Ҫ����
	int  mBackgroundSuondID; 					//��������ID

public:
	LoadingAnimationData();
	~LoadingAnimationData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class LoadingAnimationManager: public IDataManager, public cobra_win::Singleton2<LoadingAnimationManager>
{
public:
	std::map<int, LoadingAnimationData*> m_LoadingAnimationList;

public:
	LoadingAnimationManager(bool bLoadFromDB, bool bEncryption);
	virtual ~LoadingAnimationManager();

public:
	
    LoadingAnimationData * GeLoadingAnimationDataByID(int Id);

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
	friend   class   cobra_win::Singleton2<LoadingAnimationData>;

};
  
#endif