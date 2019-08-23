#ifndef   _DOTATRIBE_SKILLTABLEDATAMANAGER_H
#define   _DOTATRIBE_SKILLTABLEDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#define    CHARARRAYSIZE   128

#pragma pack(push, 1)

class   SkillTableData: public IData
{
public:
     int   skillItemID_;							 //����ID
	 int   skillItemNameSYSID;						 //��������ID
	 int   skillItemIconID;							 //����ͼ��ID
	 int   skillItemActionsID;						 //���ܶ�����
	 char  skillItemLaunchTime[CHARARRAYSIZE];		 //���ܷ���ʱ��
	 char  skillItemHurt[CHARARRAYSIZE];
	 char  skillItemDesc[CHARARRAYSIZE];
	 char  skillItemDurationTime[CHARARRAYSIZE];
	 char  skillItemLaunchLimitDesc[CHARARRAYSIZE];
	 char  skillItemProficientDesc[CHARARRAYSIZE];
     int   skillItemClientXPos;
	 int   skillItemClientYPos;
	 int   skillItemHurtCallTime;					//��λΪ ms
	 float skillItemEffetCallTime;					//��λΪ ms
	 int   skillItemResidesEffectID;

public:
	SkillTableData();
	~SkillTableData();

	std::string   GetSkillItemName();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SkillTableDataManager : public IDataManager, public cobra_win::Singleton2<SkillTableDataManager>
{
public:
	std::map<int, SkillTableData*>  m_skillTableMapList;

public:
	SkillTableDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SkillTableDataManager();

public:
	
    SkillTableData * GetSkillTableDataByID(int skillItemID);

	size_t  GetSkillTableCount(); 

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
	friend   class   cobra_win::Singleton2<SkillTableDataManager>;

};
  
#endif