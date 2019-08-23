#ifndef   _DOTATRIBER_QADATAHANDLER_H_ 
#define   _DOTATRIBER_QADATAHANDLER_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器提问数据
//date:   2013/07/22
///////////////////////////////////////////////// 
#include   <include/common/Singleton.h>
#include   "../include/IDataHandler.h"
#include   "../include/AthleticProcedureDataType.h"
#include   <string>

typedef struct qadata_tag
{
	enum
	{
	  QADATA_SINGLE_TYPE_,
	  QADATA_DOUBLE_TYPE_,
	};
	int  qatype;
	int  qadurationtime;
	char qaBtnNumber;
	std::string prompt;
	char paramCount;
	std::vector<std::string> paramVec;
public:
	qadata_tag()
	{
		qatype=0;
		qadurationtime=-1;
		qaBtnNumber=0;
		prompt="";
		paramCount=0;
		paramVec.clear();
	}
	void decodePacketData(cobra_win::DPacket & packet);
}QAData,*PQAData;
 
 class   QADataHandler: public IDataHandler,public cobra_win::Singleton2<QADataHandler>
{
public: 
    PQAData pQAdata;
public:
	QADataHandler();
	~QADataHandler();
	
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet); 
	 
	/*
		销毁接口
	*/
	virtual void onDestroy();

	/*
		初始化接口
	*/
	virtual bool init();

	/*
	销毁内存数据
	*/
	void   DestroyMemData();

public:
	friend   class   cobra_win::Singleton2<QADataHandler>;
};

#define   QADATAHANDLER			(QADataHandler::get_instance2())
 
#endif