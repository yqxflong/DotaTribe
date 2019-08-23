


#ifndef   _DOTATRIBE_SCENEINFODATAMANAGER_H
#define   _DOTATRIBE_SCENEINFODATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   SceneInfoData: public IData
{
public:
	int  mId; 									//ID
	char mSceneInfoPicture[128];				//����ͼƬ
	char mSceneInfoPicture_tab[128];			//����Сͼ
	char mSceneInfoPicture_mission[128];		//�����ؿ�Сͼ
	char mSceneInfoPicture_mission_boss[128];	//BOSS�ؿ�Сͼ
	char mSceneInfoPicture_mission_reward[128];	//3�ǽ���Сͼ
	int  mEffectId1; 							//��Ч1
	int  mEffectId2; 							//��Ч2
	int  mEffectId3; 							//��Ч3
	int  mSoundID;								//��������ID
	int  mSceneName;							//��������
public:
	SceneInfoData();
	~SceneInfoData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SceneInfoDataManager: public IDataManager, public cobra_win::Singleton2<SceneInfoDataManager>
{
public:
	std::map<int, SceneInfoData*> m_SceneInfoDataList;

public:
	SceneInfoDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SceneInfoDataManager();

public:
	/*
	��ȡ�ؿ�������Ϣ���
	*/
    SceneInfoData * GetCustomPassDataByID(int customsPassUniqueId);

	/*
	��ȡ�ؿ�����
	*/
	std::string     GetCustomNameByID(int missionID);

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
	friend   class   cobra_win::Singleton2<SceneInfoData>;

};
  
#endif