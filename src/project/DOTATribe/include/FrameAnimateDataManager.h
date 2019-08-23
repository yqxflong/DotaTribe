#ifndef   _DOTATRIBE_FRAMEANIMATEDATAMANAGER_H_
#define   _DOTATRIBE_FRAMEANIMATEDATAMANAGER_H_
 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)


  
class   FrameAnimateData : public IData
{
public:
    int   frameAnimateEffectID;					//֡���� ��Ч����ID
	short frameAnimateEffectPlayType;			//֡���� ��Ч���ŷ�ʽ
	int   frameAnimateEffectZOrder;				//֡���� ��ЧZOrder�㼶
	int   frameAnimateEffectAnimationID;		//֡���� ��Ч���Ŷ���ID
	char  frameAnimateEffectBoneName[64];		//֡���� ��Ч���Ű󶨹�������
	float frameAnimateEffectXOffSet;			//֡���� ��Ч����Xƫ��
	float frameAnimateEffectYOffSet;			//֡���� ��Ч����Yƫ��
	float frameAnimateEffectAngleOffSet;		//֡���� �Ƕ�ƫ��
	short frameAnimateIsLocationFollow;			//֡����	 �Ƿ�λ�ø���
	short frameAnimateIsAngleFollow;			//֡��Ч �Ƕȸ���
	bool  frameAnimateIsBoneBindEffect;			//֡���� �Ƿ�Ϊ������Ч
public:
	FrameAnimateData();
	~FrameAnimateData();
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class  FrameAnimateDataManager : public IDataManager, public cobra_win::Singleton2<FrameAnimateDataManager>
{
public:
	std::map<int, FrameAnimateData*>  m_frameAnimateDataMap;

public:
	FrameAnimateDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~FrameAnimateDataManager();

public:
	
    FrameAnimateData * GetFrameAnimateDataByID(int frameAniamtionEffectID);

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
	friend   class   cobra_win::Singleton2<FrameAnimateDataManager>;

};
  
#endif