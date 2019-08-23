#ifndef   _DOTATRIBE_SKILLEFFECTDATAMANAGER_H
#define   _DOTATRIBE_SKILLEFFECTDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   SkillEffectData : public IData
{
public:
   	  int    skillEffectItemID;					    //��ЧID
	  short  skillEffectZOrder;						//��Ч�Ĳ㼶
	  short  skillEffecIsLoop;						//��Ч�Ƿ�ѭ��
	  float  skillEffectSoundTriggerTime;			//��Ч��Ч����ʱ��	   ��λΪMS
	  int    skillEffectSoundID;					//��Ч����ЧID
	  short  skillEffectAnchorPoint;				//��Ч�����ê��
	  float  skillEffectXOffSet;					//��Ч��X��ƫ��
	  float  skillEffectYOffSet;					//��Ч��Y��ƫ��
	  short  skillEffectIsFollow;					//��Ч�Ƿ����
	  float  skillEffectRoleEffectTime;				//��Ч�����ɫ��Ч������ʱ���  ��λMS
	  int    skillEffectRoleEffectID;				//��Ч��ɫЧ��ID
	  int	 skillEffectAnimationID;				//��Ч����ID
	  float  skillEffectShakeTriggerTime;			//��Ч�𶯴���ʱ���   ��λMS
	  int    skillEffectShakeID;					//��Ч��ID
public:
	SkillEffectData();
	~SkillEffectData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SkillEffectDataManager : public IDataManager, public cobra_win::Singleton2<SkillEffectDataManager>
{
public:
	std::map<int, SkillEffectData*>  m_skillEffectMapList_;

public:
	SkillEffectDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SkillEffectDataManager();

public:
	
    SkillEffectData * GetSkillEffectByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<SkillEffectDataManager>;

};
  
#endif