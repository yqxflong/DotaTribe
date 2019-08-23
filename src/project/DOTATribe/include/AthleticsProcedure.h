//Name��AthleticsProcedure
//Function��ս������
//Author:	Johny

#ifndef _DOTATRIBE_ATHLETICSPROCEDURE_H_
#define _DOTATRIBE_ATHLETICSPROCEDURE_H_

#include "../include/IProcedure.h"

#include <cocos2d.h>
#include <string>


class  AthleticsProcedure: public IProcedure
{
public:
	 enum
	 {
		 _TYPE_ATHLETICSPROCUDURE_UNKONW_,
		 _TYPE_ATHLETICSPROCUDURE_BEGIN_,         //ս����ʼ
		 _TYPE_ATHLETICSPROCUDURE_FIGHT_,         //ս��������
		 _TYPE_ATHLETICSPROCUDURE_PAUSE,          //ս����ͣ
		 _TYPE_ATHLETICSPROCUDURE_END_,           //ս������
		 _TYPE_ATHLETICSPROCUDURE_NUMBER_,        //ս���¼�
	 };
protected:
	int  m_SubType;						// ��ǰ����������
	bool m_bInputEnabled;				// �Ƿ��ڿ�����״̬
	bool m_bReStartProcedure;
	bool m_bStartGame;					//��ʼ��Ϸ
	bool m_bSycLoadFinish;
protected:
	long long m_LogicTickCounter;	    // ��ʱ��
	int  m_preLoadTextureCount;		    // Ԥ��������ͼƬ��Ŀ
public:
	AthleticsProcedure();
	virtual ~AthleticsProcedure();

public:
	/*
		�õ���ǰ������
	*/
	int   GetSubType();

public:
	 
    //�л���ѡ�񸱱�����
	void  OnChangeProcedureToSceneLobbyProcure();

	//�л�����������
	void  OnChangeProcedureToMission();
   
	//�л���home��������
	void OnChangeProcedureToHome(int windowEventType);

	//�л����������
	void OnChangeProcedureToTeamBattle();
  
	//��ʼ�첽�����ͼ�������
	void  StartAnalysisEffectPool();
	  
	//�첽����Texture/Plist�ص�
	void  SycLoadFinishCallHandler(cocos2d::CCObject * pSender); 

protected:
	/*
	 �����е������Ч������Ч��
	*/
	void  PushEffectsPoolFromSkills();
	/*
	 ���⶯���е���Ч������Ч��
	*/
	void  PushEffectsPoolFromExtAction();
	/*
	 �����е���Ч������Ч�� 
	*/
	void  PushEffectsPoolFromScene();
	/*
	 ����Ч���е�֡�����������Ԥ���������
	*/
	void  PushPreFrameTextureFromEffects();
	/*
	 ����ɫƤ���������Ԥ���������
	*/
	void  PushPreFrameTextureFromRoleShape();
	/*
	�����첽�������������
	*/
	void  StartSyncLoadTextureAndPlist();
	/*
	Ԥ������Ч����
	*/
	void  PushPreLoadSoundEffectQueue(); 
	/*
	�Ӽ��ܶ����л�ȡ�����Ч
	*/
	int   GetCompositeEffectFromShape_Skill(int shapeID,int actionID);
	/*
	�������Ч�е�֡��������Ԥ��������
	*/
    void  PushFrameAnimationPlistFromComEffectID(int compositeEffectID);
	/*
	��֡��������Ԥ��������
	*/
	void  PushFrameAnimationPlistFromEffectID(int frameAnimateEffectID);
	/*
	����ɫƤ���͹�����ЧƤ�����������
	*/
	void  PushPreTextureImageWithRoleShapeID(int roleShapeID);
	/*
	��Ϸ��ʼ֪ͨ
	*/
	void  PostStartGameNotification();
public:
	virtual      bool     Init();
	virtual      void     Tick();
	virtual      void     Destroy();
	virtual      void     DestroyWithOutAthleticsData();

	void Init_Sub();
public:
	virtual      void     OnInputEventHandler(){};
	virtual      void     OnSystemEnterBackEventHandler();
	virtual      void     OnSystemEnterFrontEventHandler();
	virtual      void     OnSystemPauseEventHandler();
	virtual      void     OnSystemResumeEventHandler();


	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
	 
};

#endif