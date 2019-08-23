// Name :		CreateRoleDataManager.h
// Function:	��ɫ����������
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef   _DOTATRIBE_CreateRoleDATAMANAGER_H
#define   _DOTATRIBE_CreateRoleDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   CreateRoleData: public IData
{
public:
	int	mRoleIndexID;								//��ɫ����ID
	int	mRoleModelID;								//��ɫģ��ID
	int mRoleShapeID;								//��ɫ����ID
	int	mRoleSelectedAnimationID;					//ѡ�ж���ID
	int	mRoleDisabledAnimationID;					//δѡ�ж���ID
	int	mRoleEntranceAnimationID;					//��������ID
	int	mRoleLeaveAnimationID;						//�볡����ID
	int	mRoleDescribeInfoID;						//��ɫ������ϢID       

public:
	CreateRoleData();
	~CreateRoleData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class CreateRoleDataManager : public IDataManager, public cobra_win::Singleton2<CreateRoleDataManager>
{
public:
	std::map<int, CreateRoleData*> m_CreateRoleDataMapList;

public:
	CreateRoleDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~CreateRoleDataManager();

public:
	
    CreateRoleData * GetCreateRoleDataByID(int roleIndexId);

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
	friend   class   cobra_win::Singleton2<CreateRoleDataManager>;

};
  
#endif