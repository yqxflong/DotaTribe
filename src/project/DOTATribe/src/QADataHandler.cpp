#include  "../include/QADataHandler.h"


void QAData::decodePacketData(cobra_win::DPacket & packet)
{
	unsigned short  tmp_len=0;
	char * tmpChar=NULL;
	std::string tmpParamStr="";

	packet.read(qatype);
	packet.read(qadurationtime);
	packet.read(qaBtnNumber);
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0'; 
	prompt.assign(tmpChar);
	delete [] tmpChar;
	tmpChar=NULL;
	tmp_len=0;

	packet.read(paramCount);

	for(short paramIndex=0;paramIndex<paramCount;paramIndex++)
	{
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0'; 
		tmpParamStr.assign(tmpChar);
		delete [] tmpChar;
		tmpChar=NULL;
		tmp_len=0;
	    paramVec.push_back(tmpParamStr);
	} 
}


QADataHandler::QADataHandler()
{
	init();
} 
QADataHandler::~QADataHandler()
{
	if(pQAdata!=NULL)
	{ 
		delete  pQAdata;
		pQAdata=NULL;
	}
}

 void QADataHandler::handlePacket(IPacket* packet)
 {

 }
	 
/*
	销毁接口
*/
void QADataHandler::onDestroy()
{

}

void   QADataHandler::DestroyMemData()
{
	if(pQAdata!=NULL)
	{ 
		delete  pQAdata;
		pQAdata=NULL;
	}
}


/*
	初始化接口
*/
 bool QADataHandler::init()
 {
	  pQAdata=NULL;
	  return true;
 }
 