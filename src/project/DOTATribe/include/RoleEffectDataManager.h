#ifndef  _DOTATRIBE_ROLEEFFECTDATAMANAGER_H_
#define  _DOTATRIBE_ROLEEFFECTDATAMANAGER_H_
 
#include <include/common/Singleton.h>
#include <cocos2d.h>
#include "IDataManager.h"
#include <string>
#include <map> 
  
#pragma pack(push, 1)
class RoleEffectData : public IData
{
public: 
     int   roleEffectID;
	 char  roleEffectColorStr[16];
	 float roleEffectFadeInTime;
	 float roleEffectDurationTime;
	 float roleEffectFadeOutTime;

public:
	RoleEffectData();
	virtual ~RoleEffectData();

	cocos2d::ccColor4B  GetRoleEffectColor();

public:
	/*
		��������
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class RoleEffectDataManager : public IDataManager, public cobra_win::Singleton2<RoleEffectDataManager>
{
public:
	std::map<int, RoleEffectData*>  m_roleEffectDataMapList; 

public:
	RoleEffectDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~RoleEffectDataManager();

public: 
	RoleEffectData* GetRoleEffectDataByID(int roleEffectID);

public:
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
	friend   class   cobra_win::Singleton2<RoleEffectDataManager>;
};


#endif
