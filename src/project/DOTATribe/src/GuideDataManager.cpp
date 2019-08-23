#include "../include/GuideDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>
#include <vector>


GuideItemData::GuideItemData()
{
	mGuideType      = 0;
	mGuideIndex     = 0;
	mMaskAlphaColor = 0;
	mMaskStartXPos  = 0.0f;
	mMaskStartYPos  = 0.0f;
	mMaskEndXPos    = 0.0f;
	mMaskEndYPos    = 0.0f;
	mFlipGuideArrow	=false;
	mArrowXPos      = 0.0f;
	mArrowYPos      = 0.0f;
	mArrowDstX		=0.0f;
	mArrowDstY		=0.0f;
	mArrowRotation  = 0.0f;
	mGuiderXPos     = 0.0f;
	mGuiderYPos     = 0.0f;
	mGuiderIconXPos = 0.0f;
	mGuiderIconYPos = 0.0f;
	mFinishButtonXPos        = 0.0f;
	mFinishButtonYPos        = 0.0f;
	mShowGuider              = false;
	mClickAnyWhereToNextStep = false;
	mShowGuideArrow          = false;
	mShowFinishButton        = true;
	mShowGuiderIcon          = false;
	mArrowType=0;
	memset(mArrowOrder, 0, sizeof(mArrowOrder));
	memset(mSoundName, 0, sizeof(mSoundName));
	mNextModuleID=-1;
}

GuideItemData::~GuideItemData()
{

}

bool GuideItemData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mGuideType))
		return false;

	if (!parser.parser_int_value(mGuideIndex))
		return false;

	if (!parser.parser_int_value(mMaskAlphaColor))
		return false;

	if (!parser.parser_float_value(mMaskStartXPos))
		return false;

	if (!parser.parser_float_value(mMaskStartYPos))
		return false;

	if (!parser.parser_float_value(mMaskEndXPos))
		return false;

	if (!parser.parser_float_value(mMaskEndYPos))
		return false;

	if (!parser.parser_bool_value(mClickAnyWhereToNextStep))
		return false;

	if (!parser.parser_bool_value(mShowGuideArrow))
		return false;

	if (!parser.parser_int_value(mArrowType))
		return false;

	parser.parser_string_value(mArrowOrder, sizeof(mArrowOrder));

	if (!parser.parser_bool_value(mFlipGuideArrow))
		return false;
	
	if (!parser.parser_float_value(mArrowXPos))
		return false;

	if (!parser.parser_float_value(mArrowYPos))
		return false;

	if (!parser.parser_float_value(mArrowDstX))
		return false;

	if (!parser.parser_float_value(mArrowDstY))
		return false;

	if (!parser.parser_float_value(mArrowRotation))
		return false;

	if (!parser.parser_bool_value(mShowGuider))
		return false;

	if (!parser.parser_float_value(mGuiderXPos))
		return false;

	if (!parser.parser_float_value(mGuiderYPos))
		return false;

	if (!parser.parser_bool_value(mShowGuiderIcon))
		return false;

	if (!parser.parser_float_value(mGuiderIconXPos))
		return false;

	if (!parser.parser_float_value(mGuiderIconYPos))
		return false;

	int tipsID=0;
	if (!parser.parser_int_value(tipsID))
		return false;

	if (tipsID>0)
	{
		//TODO:注意多语言
		mTips=SysLangDataManager::get_instance2()->GetSysLangById(tipsID);
	}

	if (!parser.parser_bool_value(mShowFinishButton))
		return false;

	if (!parser.parser_float_value(mFinishButtonXPos))
		return false;

	if (!parser.parser_float_value(mFinishButtonYPos))
		return false;

	parser.parser_string_value(mSoundName, sizeof(mSoundName));

	if (!parser.parser_int_value(mNextModuleID))
		return false;
	
	return true;
}

template<> GuideDataManager* cobra_win::Singleton2<GuideDataManager>::m_pMySelf = NULL;

GuideDataManager::GuideDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_GuideStepList.clear();
}	

GuideDataManager::~GuideDataManager()
{

}

int GuideDataManager::GetGuideStepNumberByType(int guideType)
{
	int count = 0;
	std::list<GuideItemData*>::iterator iter   = m_GuideStepList.begin();
	std::list<GuideItemData*>::iterator iter_e = m_GuideStepList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if ((*iter)->mGuideType == guideType)
			count++;
	}

	return count;
}

GuideItemData* GuideDataManager::GetGuideStepInfoByIndex(int guideType, int guideIdx)
{
	std::vector<GuideItemData*> temp;
	std::list<GuideItemData*>::iterator iter   = m_GuideStepList.begin();
	std::list<GuideItemData*>::iterator iter_e = m_GuideStepList.end();
	for (; iter!=iter_e; ++iter)
	{
		if ((*iter)->mGuideType==guideType)
			temp.push_back((*iter));
	}

	if (temp.size() <= (unsigned int)guideIdx)
		return NULL;

	return temp[guideIdx];
}

std::string GuideDataManager::GetName()
{
	if (!m_bLoadFromDB)
	{
		if (EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_IPHONE_)
		{
			return "resource/data/guide_data.txt";
		}
		else if (EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_IPHONE5_)
		{
			return "resource/data/guide_data_iphone5.txt";
		}
		else if(EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_IPAD_)
		{
			return "resource/data/guide_data_ipad.txt";
		}else if(EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_ANDROID_){
			if(EngineSystem::IsAndroid_3_2())
			{//phone4
				CCLOG("dota Load guide is resource/data/guide_data.txt");
				return "resource/data/guide_data.txt";
			}
			else if(EngineSystem::IsAndroid_4_3())
			{
				CCLOG("dota Load guide is resource/data/guide_data_ipad.txt");
				return "resource/data/guide_data_ipad.txt";
			}
			else if(EngineSystem::IsAndroid_15_9() || EngineSystem::IsAndroid_1024_600() || EngineSystem::IsAndroid_1184_720() || EngineSystem::IsAndroid_1196_720())
			{
				CCLOG("dota Load guide is resource/data/guide_data_android159.txt");
				return "resource/data/guide_data_android159.txt";
			}
			else if(EngineSystem::IsAndroid_16_10())
			{//android 1610
				CCLOG("dota Load guide is resource/data/guide_data_android1610.txt");
				return "resource/data/guide_data_android1610.txt";
			}
			else if(EngineSystem::IsAndroid_16_9() || EngineSystem::IsAndroid_1136_640())
			{//phone5
				CCLOG("dota Load guide is resource/data/guide_data_iphone5.txt");
				return "resource/data/guide_data_iphone5.txt";
			}
			else
			{
				CCLOG("dota Load guide is resource/data/guide_data.txt");
				return "resource/data/guide_data.txt";
			}
		}
	}
	
	if (EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_IPHONE_)
	{
		return "guide_data";
	}
	else if (EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_IPHONE5_)
	{
		return "guide_data_iphone5";
	}
	else if(EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_IPAD_)
	{
		return "guide_data_ipad";
	}else if(EngineSystem::GetDeviceType() == EngineSystem::_TYPED_IOS_DEVICE_ANDROID_){
		if(EngineSystem::IsAndroid_3_2())
		{//phone4
			CCLOG("dota Load guide is guide_data");
			return "guide_data";
		}
		else if(EngineSystem::IsAndroid_4_3())
		{
			CCLOG("dota Load guide is guide_data_ipad");
			return "guide_data_ipad";
		}
		else if(EngineSystem::IsAndroid_15_9() || EngineSystem::IsAndroid_1024_600() || EngineSystem::IsAndroid_1184_720() || EngineSystem::IsAndroid_1196_720())
		{//android 15_9
			CCLOG("dota Load guide is guide_data_android159");
			return "guide_data_android159";
		}
		else if(EngineSystem::IsAndroid_16_10())
		{//android 16_10
			CCLOG("dota Load guide is guide_data_android1610");
			return "guide_data_android1610";
		}
		else if(EngineSystem::IsAndroid_16_9() || EngineSystem::IsAndroid_1136_640())
		{//phone5
			CCLOG("dota Load guide is guide_data_iphone5");
			return "guide_data_iphone5";
		}
		else
		{
			CCLOG("dota Load guide is guide_data");
			return "guide_data";
		}
	}

	return "";
}

unsigned  int GuideDataManager::GetSize()
{
	return m_GuideStepList.size()*sizeof(GuideItemData);
}

bool  GuideDataManager::Init()
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

void  GuideDataManager::Tick()
{

}

void  GuideDataManager::Destroy()
{
	std::list<GuideItemData*>::iterator iter   = m_GuideStepList.begin();
	std::list<GuideItemData*>::iterator iter_e = m_GuideStepList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete (*iter);
	}
	m_GuideStepList.clear();
}

bool  GuideDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	GuideItemData* pButtonItem = (GuideItemData*)pData;
	assert(pButtonItem != NULL);

	return true;
}

bool  GuideDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  GuideDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	GuideItemData* pItemData = new GuideItemData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_GuideStepList.push_back(pItemData);
	return true;
}
