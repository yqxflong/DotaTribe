#ifndef   _DOTATRIBER_PARTICLEDATAMANAGER_H_
#define   _DOTATRIBER_PARTICLEDATAMANAGER_H_

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   ParticleData : public IData
{
public:
     int   particleEffectID;		
	 short particleEffectPlayType;  //(0 ���ӹ���ʱ��  1 �󶨶���ʱ��  2 ����ʱ��)
	 int   particleEffectZOrder;
	 char  particleEffectFileName[128];
	 char  particleEffectBoneName[64];
	 float particleEffectXOffSet;
	 float particleEffectYOffSet;
	 float particleEffectAngleOffSet;
	 short particleEffectIsLocationFollow;
	 short particleEffectIsAngleFollow;
	 short particleEffectIsHangover;
	 short particleEffectIsBlendMode;	//�Ƿ����û��ģʽ
	 float particleEffectVarianceX;		//����X�ֲ����� -1 Ϊ��ȡPlistĬ��ֵ
	 float particleEffectVarianceY;     //����Y�ֲ����� -1 Ϊ��ȡPlistĬ��ֵ
	 bool  particleEffectIsBindBone; 
public:
	ParticleData();
	~ParticleData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class ParticleDataManager : public IDataManager, public cobra_win::Singleton2<ParticleDataManager>
{
public:
	std::map<int, ParticleData*>  m_particleDataMap;

public:
	ParticleDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~ParticleDataManager();

public:
	
    ParticleData * GetParticleDataByID(int particleEffectID);

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
	friend   class   cobra_win::Singleton2<ParticleDataManager>;

};
  
#endif