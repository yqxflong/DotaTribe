// Name :		SelectMissionProcedure.h
// Function:	�ؿ�ѡ������
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_SELECTMISSIONPROCEDUER_H_
#define  _DOTATRIBE_SELECTMISSIONPROCEDUER_H_


#include "IProcedure.h"

class  SelectMissionProcedure: public IProcedure
{
public:
	SelectMissionProcedure();
	virtual ~SelectMissionProcedure();

	int m_showWindow;
	int m_skipWindow;
	int m_skipTabNum;
public:
	/*
		�л������ͼ
	*/
	void ChangeProcedureTo(IProcedure* procedure);

	/*
		�л����ؿ�ѡ��
	*/
	void ChangeToSelectSonMissionProcedure();

public:
	/*
		��ʼ������
	*/
	virtual      bool     Init();
	/*
		�߼��崦��
	*/
	virtual      void     Tick();
	/*
		��������
	*/
	virtual      void     Destroy();

public:
	/*
		ϵͳ������Ϣ��Ӧ����
	*/
	virtual      void     OnInputEventHandler();

public:
	/*
		ϵͳ�����̨�¼���Ӧ����
	*/
	virtual      void     OnSystemEnterBackEventHandler();
	/*
		ϵͳ����ǰ̨�¼���Ӧ����
	*/
	virtual      void     OnSystemEnterFrontEventHandler();
	/* 
		ϵͳ��ͣ�¼���Ӧ����
	*/
	virtual      void     OnSystemPauseEventHandler();
	/*
		ϵͳ�ָ��¼���Ӧ����
	*/
	virtual      void     OnSystemResumeEventHandler();

	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
};

#endif
