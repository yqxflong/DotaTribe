#include "../include/DOTATribeApp.h"
#include "../include/NumberBufferDataManager.h"
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


NumberBufferData::NumberBufferData()
{
    numberBufferFormatID=0;					     //数字Buffer格式ID
	numberBufferFontType=0;						 //数字字体库ID
    numberBufferScale=0.0f;						 //数字Buffer的缩放比例
	numberBufferMaxScale=0.0f;					 
	numberBufferScaleDurationTime=0.0f;	
	numberBufferInitHeigh=0.0f;
	numberBufferEndHeigh=0.0f;
	numberBufferDurationTime=0.0f;
	numberBufferTriggerFadeOutTime=0.0f; 
	numberBufferIsNeedScale=false;
}

NumberBufferData::~NumberBufferData()
{

}

bool  NumberBufferData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(numberBufferFormatID))
		return false;

	if (!parser.parser_int_value(numberBufferFontType))
		return false;

	if (!parser.parser_float_value(numberBufferScale))
		return false;

	if (!parser.parser_float_value(numberBufferMaxScale))
		return false;
	 
	if (!parser.parser_float_value(numberBufferScaleDurationTime))
		return false;
	 
	if (!parser.parser_float_value(numberBufferInitHeigh))
		return false;
 
	if (!parser.parser_float_value(numberBufferEndHeigh))
		return false;

	if (!parser.parser_float_value(numberBufferDurationTime))
		return false;

	if (!parser.parser_float_value(numberBufferTriggerFadeOutTime))
		return false;
  
	if(numberBufferScale==numberBufferMaxScale||numberBufferScaleDurationTime<0.01f)
	numberBufferIsNeedScale=false;
	else
	numberBufferIsNeedScale=true; 

	return true; 
}





//
//cocos2d::ccColor4B  NumberBufferData::GetNumberBufferColor()
//{ 
//	 std::string totalValue=numnerBufferColor;
//	 int   delimiterPos=totalValue.find('-');
//	 std::string rValue=totalValue.substr(0,delimiterPos);
//	 int   delemiterPos2=delimiterPos;
//     delimiterPos=totalValue.find('-',delimiterPos+1);
//	 std::string gValue=totalValue.substr(delemiterPos2+1,delimiterPos-delemiterPos2-1);
//	 int   delemiterPos3=delimiterPos;
//	 delemiterPos2=totalValue.find('-',delimiterPos+1);
//	 std::string bValue=totalValue.substr(delemiterPos3+1,delemiterPos2-delemiterPos3-1);
//
//	 std::string aValue=totalValue.substr(delemiterPos2+1, totalValue.size()-delemiterPos2);
// 
//	 cocos2d::ccColor4B  bufferColor;
//	 bufferColor.r=atoi(rValue.c_str());
//	 bufferColor.g=atoi(gValue.c_str());
//	 bufferColor.b=atoi(bValue.c_str());
//	 bufferColor.a=atoi(aValue.c_str());
//	 return  bufferColor;
//}




template<> NumberBufferDataManager* cobra_win::Singleton2<NumberBufferDataManager>::m_pMySelf = NULL;

NumberBufferDataManager::NumberBufferDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_numberBufferMapList.clear();
}

NumberBufferDataManager::~NumberBufferDataManager()
{

}


NumberBufferData * NumberBufferDataManager::GetNumberBufferDataByID(int numberBufferID)
{

	std::map<int,NumberBufferData*>::iterator shapeIter=m_numberBufferMapList.find(numberBufferID);
	if(shapeIter!=m_numberBufferMapList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}

std::string   NumberBufferDataManager::GetName()
{ 
	if (!m_bLoadFromDB)
		return "resource/data/numberbufferdata.txt";

	return "numberbufferdata";
} 


unsigned  int NumberBufferDataManager::GetSize()
{
	return m_numberBufferMapList.size()*sizeof(NumberBufferData);
}


bool  NumberBufferDataManager::Init()
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


void  NumberBufferDataManager::Tick()
{

}


void  NumberBufferDataManager::Destroy()
{
	std::map<int, NumberBufferData*>::iterator iter   = m_numberBufferMapList.begin();
	std::map<int, NumberBufferData*>::iterator iter_e = m_numberBufferMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_numberBufferMapList.clear();
} 


bool  NumberBufferDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	NumberBufferData* pRoleItem = (NumberBufferData*)pData;
	assert(pRoleItem != NULL);


	return true;
}

bool  NumberBufferDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  NumberBufferDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	NumberBufferData* pItemData = new NumberBufferData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_numberBufferMapList.insert(std::map<int, NumberBufferData*>::value_type(pItemData->numberBufferFormatID, pItemData));

	return true;
}