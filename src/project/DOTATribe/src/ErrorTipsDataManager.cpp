#include "../include/DOTATribeApp.h"
#include "../include/ErrorTipsDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/TimeSystem.h"
#include "../include/DBSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/common/FileLoader.h>
#include <include/common/Parser.h>
#include <include/common/String.h>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/common/MD5Crypto.h>
using  namespace  cobra_win;


ErrorTipsData::ErrorTipsData()
{  
	errorFontStyleID=0;
	memset(errorBackImageFilePath,0,sizeof(errorBackImageFilePath));
	errorWidth=0.0f;
	errorHeight=0.0f;
	errorAnchorX=0.5f;
	errorAnchorY=0.5f;
	errorRelateY=0.0f;
	errorAddHeight=0.0f;
	errorMaxLevel=0;
	errorDurationTime=0.0f;
	errorFadeOutTime=0.0f;
}

ErrorTipsData::~ErrorTipsData()
{

}
 

bool  ErrorTipsData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(errorFontStyleID))
		return false;

	if (!parser.parser_string_value(errorBackImageFilePath,sizeof(errorBackImageFilePath)))
		return false;

	if (!parser.parser_float_value(errorWidth))
		return false;

	if (!parser.parser_float_value(errorHeight))
		return false;

	if (!parser.parser_float_value(errorAnchorX))
		return false;

	if (!parser.parser_float_value(errorAnchorY))
		return false;

	if (!parser.parser_float_value(errorRelateY))
		return false;

	if (!parser.parser_float_value(errorAddHeight))
		return false;

	if (!parser.parser_int_value(errorMaxLevel))
		return false;

	if (!parser.parser_float_value(errorDurationTime))
		return false;

	if (!parser.parser_float_value(errorFadeOutTime))
		return false;
  
	return true; 
}



template<> ErrorTipsDataManager* cobra_win::Singleton2<ErrorTipsDataManager>::m_pMySelf = NULL;

ErrorTipsDataManager::ErrorTipsDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_pErrorTipsData=NULL;
}

ErrorTipsDataManager::~ErrorTipsDataManager()
{

}
 
ErrorTipsData *  ErrorTipsDataManager::GetErrorTipsData()
{
	return   m_pErrorTipsData;
}

std::string   ErrorTipsDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/errortipsdata.txt";

	return "errortipsdata";
} 


unsigned  int ErrorTipsDataManager::GetSize()
{
	return  sizeof(ErrorTipsData);
}


bool  ErrorTipsDataManager::Init()
{
	do 
	{
		if (m_bLoadFromDB)
		{
			if (!LoadFromDB())
				break;
		}
		else
		{
			if (!LoadFromFile())
				break;
		}

		return true;
	} 
	while(false);
	return false;
}


void  ErrorTipsDataManager::Tick()
{

}


void  ErrorTipsDataManager::Destroy()
{ 
	if(m_pErrorTipsData!=NULL)
	{
		delete m_pErrorTipsData;
		m_pErrorTipsData=NULL;
	}
} 


bool  ErrorTipsDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	ErrorTipsData* pRoleItem = (ErrorTipsData*)pData;
	assert(pRoleItem != NULL);
	return true;

}

bool  ErrorTipsDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  ErrorTipsDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{ 
	ErrorTipsData* pItemData = new ErrorTipsData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_pErrorTipsData=pItemData;
	 
	return true;
}












