#ifndef   _DOTATRIBE_BULLETDATAMANAGER_H
#define   _DOTATRIBE_BULLETDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   BulletData: public IData
{
public:
	  int    bulletItemID_;					 //�ӵ�ID
	  float  bulletStartRelativelyXPos_;     //�ӵ���ʼ���λ��
      float  bulletStartRelativelyYPos_;     //�ӵ���ʼ���λ��
	  int    bulletAnimationID;              //�ӵ�����ID
	  int    bulletAnimationInterval_;       //�ӵ�����֡���
	  float  bulletMoveSpeed_;               //�ӵ��ƶ��ٶ�
	  float  bulletEndRelativelyXPos_;       //�ӵ�����ʱ���λ��
	  float  bulletEndRelativelyYPos_;       //�ӵ�����ʱ�����λ��
	  char   bulletExplosionName[128];       //�ӵ���ը�Ķ���
	  float  bulletExplosionInterval_;       //�ӵ���ը֡�ļ��
	 
public:
	BulletData();
	~BulletData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class BulletDataManager : public IDataManager, public cobra_win::Singleton2<BulletDataManager>
{
public:
	std::map<int, BulletData*>  m_bulletMapList;

public:
	BulletDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~BulletDataManager();

public:
	
    BulletData * GetBulletDataByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<BulletDataManager>;

};
  
#endif