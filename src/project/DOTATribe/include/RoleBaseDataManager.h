#ifndef   _DOTATRIBE_ROLEBASEDATAMANAGER_H
#define   _DOTATRIBE_ROLEBASEDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   RoleBaseData: public IData
{
public:
	  int  roleUniqueID_;                    //��ɫID
	  int  roleShapeID_;                     //����ID
	  char roleHeadIcon_[128];				 //ͷ��
	  int  roleInitLevel_;                   //��ʼ�ȼ�
      int  roleTypeId_;                      //����
	  int  roleWeaponID_;                    //����             
	  int  roleInitHP_;                      //Ѫ��
	  int  roleAttackValue_;                 //������
	  int  roleSpeedValue_;                  //�ٶ�
	  int  roleSkillTacticsID_;              //���ܲ���
      int  roleForceValue_;                  //����֮
	  int  roleAgilityValue_;                //����ֵ
	  int  roleIntelligenceValue_;           //����ֵ
      int  roleArmorValue_;                  //����ֵ 
	  int  roleSunderValue_;                 //�Ƽ�ֵ     
	  int  roleCritValue_;                   //����ֵ
	  int  roleToughnessValue_;              //����ֵ          
	  int  roleHitValue_;                    //����ֵ
	  int  roleDodgeValue_;                  //����ֵ
public:
	RoleBaseData();
	~RoleBaseData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);

};

#pragma pack(pop)
 


class RoleBaseDataManager : public IDataManager, public cobra_win::Singleton2<RoleBaseDataManager>
{
public:
	std::map<int, RoleBaseData*> m_RoleBaseDataMapList;

public:
	RoleBaseDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~RoleBaseDataManager();

public:
	
    RoleBaseData * GetRoleBaseDataByID(int roleUniqueId);

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
	friend   class   cobra_win::Singleton2<RoleBaseDataManager>;

};
  
#endif