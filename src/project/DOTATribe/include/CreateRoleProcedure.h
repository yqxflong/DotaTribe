// Name :		CreateRoleProcedure.h
// Function:	��ɫ��������
// Author :		zhoushaonan
// Maintainer:  zhoushaona

#ifndef  _DOTATRIBE_CREATEROLEPROCEDURE_H_
#define  _DOTATRIBE_CREATEROLEPROCEDURE_H_


#include "IProcedure.h"

class  CreateRoleProcedure: public IProcedure
{
public:
	CreateRoleProcedure();
	virtual ~CreateRoleProcedure();

public:
	/*
		�л�����½����
	*/
	void ChangeProcedureTo(IProcedure* procedure);

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
