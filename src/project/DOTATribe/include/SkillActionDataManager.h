#ifndef   _DOTATRIBE_SKILLACTIONDATAMANAGER_H
#define   _DOTATRIBE_SKILLACTIONDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <vector>
#include <map>

#pragma pack(push, 1)

class   SkillActionData: public IData
{
public:
	  int   skillActionsID_;                     //������ID  
	  int   skillSituActionID_;                  //ԭ�ض���ID
	  int   skillSituActionType_;                //ԭ�ض�������
 
	  int   skillAdvanceActionID_;			     //ǰ������ID
	  int   skillAdvanceType_;				  	 //ǰ����������
	  float skillAdvanceSpeed_;					 //ǰ�������ٶ�  ����/֡
 
	  int   skillTargetActionID_;				 //Ŀ�궯��ID	
	  int   skillTargetActionType_;				 //Ŀ�궯������
 
 	  int   skillReturnActionID_;				 //���ض���ID	
	  int   skillReturnActionType_;				 //���ض�������
	  float skillReturnSpeed_;					 //�����ƶ��ٶ�  ����/֡

	  std::vector<int> skillActiveActionVec_;	 //��Ч�Ķ�����
	   
public:
	SkillActionData();
	~SkillActionData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SkillActionDataManager : public IDataManager, public cobra_win::Singleton2<SkillActionDataManager>
{
public:
	std::map<int, SkillActionData*>  m_skillActionMapList_;

public:
	SkillActionDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SkillActionDataManager();

public:
	
    SkillActionData * GetSkillActionItemByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<SkillActionDataManager>;

};
  
#endif