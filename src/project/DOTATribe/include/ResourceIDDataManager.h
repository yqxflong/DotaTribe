//Name��ResourceIDDataManager
//Written By����ǿ

#ifndef   _DOTATRIBE_RESOURCEIDDATAMANAGER_H
#define   _DOTATRIBE_RESOURCEIDDATAMANAGER_H

#include <cocos2d.h>
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class   ResourceIDData: public IData
{
public:
	enum
	{
		_RESOURCETYPE_UNKOWN_TYPE_=-1,
		_RESOURCETYPE_PLIST_TYPE_,
		_RESOURCETYPE_IMAGE_TYPE_,
	};
public:
	int  IconID_;
	short  resourceType;
	char textureName[128];
	char filepath_[128];
public:
	ResourceIDData();
	virtual ~ResourceIDData(){};
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class ResourceIDDataManager : public IDataManager, public cobra_win::Singleton2<ResourceIDDataManager>
{
public:
	std::map<int,ResourceIDData *>  m_resouceDataMap;
public:
	ResourceIDDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){
		m_resouceDataMap.clear();
	};

	virtual ~ResourceIDDataManager(){};

public:
	
	std::string getDataByID(int idx);

	ResourceIDData  * GetResourceDataByID(int idx);
	 
	/*
	 *	����������þ��� Ŀǰ����֧�� ���ͼƬ
	 */
	cocos2d::CCSprite *  GetSpriteFromID(int idx);
 
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
	friend   class   cobra_win::Singleton2<ResourceIDDataManager>;
};

#define  RESOURCEDAIDMANAGER  ResourceIDDataManager::get_instance2()
  
#endif