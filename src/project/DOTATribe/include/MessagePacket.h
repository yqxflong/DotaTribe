
#ifndef   _DOTATRIBE_MESSAGEPACKET_H
#define   _DOTATRIBE_MESSAGEPACKET_H


class  MessagePacket
{
public:
	enum
	{
		UNKOWN_MESSAGEPACKET_TYPE,
		PALYERROLE_MESSAGEPACKET_TYPE,				//�����Ϣ����
	};

public:
	MessagePacket();
	virtual ~MessagePacket();

	virtual bool Init()=0;
	virtual void Tick();
	virtual void Destroy()=0;
	virtual void OnCommandHanlder(int EventTypeID,void * ptr)=0;

public:
	void   SetObjectType(int ObjectType);			//������Ϣ����
	int    GetObjectType();
	bool   IsValid();
	void   SetIsValid(bool isValid);
	void   SetSubObjectID(int subObjectId);
	int    GetSubObjectID();

protected:
	int				m_ObjectType;                   //��������
	int				m_ObjectSubID;					//�����Ӷ���ID
	long long		m_LogicTickCount;
	bool			m_isValid;
};

#endif