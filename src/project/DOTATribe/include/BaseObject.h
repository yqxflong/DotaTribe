//Name��BaseObject
//Function��ս���߼�����
//Author:	Johny

#ifndef   _DOTATRIBE_BASEOBJECT_H
#define   _DOTATRIBE_BASEOBJECT_H

#include  <list>
#include  <string>

class  BaseObject
{
public:
	//@��������
    enum
	{
		 UNKOWN_OBJECT_TYPE,									
		 HEROICROLE_OBJECT_TYPE,							//Ӣ�۶�������
		 COMMONSKILLITEMPROCEDURE_OBJECT_TYPE,				//�����������̶�������
		 COMMONSKILLACTIONPROCEDURE_OBJECT_TYPE,			//�������ܶ������̶�������
		 COMMON_UNSKILLPROCEDUER_OBJECT_TYPE,				//�����Ǽ������̶�������
		 SKILLATTACHLOGIC_OBJECT_TYPE,						//���ܸ����߼���������
		 COMMON_SKILLEFFECT_OBJECT_TYPE,					//����������Ч������������		
		 COMMON_NUMBEREFFECT_OBJECT_TYPE,					//������ֵ��Ч������������
		 ART_LABEL_OBJECT_TYPE,								//�����ֱ�ǩ��������
		 LISTEN_PROXY_OBJECT_TYPE,							//���������������
	};

public:
	BaseObject();
	virtual ~BaseObject();
	//@����
	virtual   void Init(){};
	virtual   void Tick();
	virtual   void Destroy()=0;

	//@����ս���ٶ�
	virtual   void SetSpeedScale(float speedScale);

	//@�����������
	virtual   void OnCommandHanlder(int EventTypeID){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2,std::string attachParam3){};
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2,std::string attachParam3,std::string attachParam4){};
public:
	//@��������
	void   SetObjectType(int ObjectType);
	int    GetObjectType();
	//@�Ƿ���Ч
	bool   IsValid();
	void   SetIsValid(bool isValid);
	//@�ö����ID
    void   SetSubObjectID(int subObjectId);
	int    GetSubObjectID();
protected:
	int    objectType_;                        //��������
	int    objectSubID_;					   //�����Ӷ���ID
	long long    m_LogicTickCount_;			   //������߼�֡
	bool   isValid_;						   //�����Ƿ�Ϸ�
};

#endif