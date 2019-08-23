#ifndef   _DOTATRIBE_ROLESHAEPROPERTYDATA_H
#define   _DOTATRIBE_ROLESHAEPROPERTYDATA_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   RoleShapePropertyData: public IData
{
public:
	  int  roleShapeID_;
	  char roleImageName[64];
	  char roleXiuXianActionName[64];
	  char roleXingZouActionName[64];
	  char roleNormalAttackActionName[64];
	  char roleRemoteAttackActionName[64];
	  char roleHurtActionName[64];
	  char roleDeadActionName[64];
	  char roleDodgeActionName[64];
	  char roleCritActionName[64];
	  char roleWinActionName[64];
public:
	RoleShapePropertyData();
	~RoleShapePropertyData();

public:
	/*
		��������
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class RoleShapePropertyDataManager : public IDataManager, public cobra_win::Singleton2<RoleShapePropertyDataManager>
{
public:
	std::map<int, RoleShapePropertyData*> m_RoleShapePropertyList;

public:
	RoleShapePropertyDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~RoleShapePropertyDataManager();

public:
	
    RoleShapePropertyData * GetRoleShapeDateById(int roleShapeId);

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
	friend   class   cobra_win::Singleton2<RoleShapePropertyDataManager>;

};




#endif