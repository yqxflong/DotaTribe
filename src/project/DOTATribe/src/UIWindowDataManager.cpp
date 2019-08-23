#include <cocos2d.h>
#include "../include/UIWindowDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>


UIWindowItemData::UIWindowItemData()
{
	mWindowType    = -1;
	mWindowZOrder  = -1;
	mIsModelWindow = false;
	mIsBGImageReleaseWhenWindowDestroy = false;
	mIsUIImageReleaseWhenWindowDestroy = false;

	memset(mWindowName, 0, sizeof(mWindowName));
	memset(mBGImageResourceName, 0, sizeof(mBGImageResourceName));
	memset(mUIResourceName, 0, sizeof(mUIResourceName));
}

UIWindowItemData::~UIWindowItemData()
{

}

bool UIWindowItemData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mWindowType))
		return false;

	if (!parser.parser_string_value(mWindowName, sizeof(mWindowName)))
		return false;

	if (!parser.parser_int_value(mWindowZOrder))
		return false;

	if (!parser.parser_bool_value(mIsModelWindow))
		return false;

	parser.parser_string_value(mBGImageResourceName, sizeof(mBGImageResourceName));
	parser.parser_bool_value(mIsBGImageReleaseWhenWindowDestroy);
	parser.parser_string_value(mUIResourceName, sizeof(mUIResourceName));
	parser.parser_bool_value(mIsUIImageReleaseWhenWindowDestroy);

	if (!parser.parser_int_value(mSoundOpen))
		return false;
	if (!parser.parser_int_value(mSoundClose))
		return false;

	return true;
}

template<> UIWindowDataManager* cobra_win::Singleton2<UIWindowDataManager>::m_pMySelf = NULL;

UIWindowDataManager::UIWindowDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_WindowList.clear();
}

UIWindowDataManager::~UIWindowDataManager()
{

}

UIWindowItemData* UIWindowDataManager::GetWindowByType(int type)
{
	std::map<int, UIWindowItemData*>::iterator iter = m_WindowList.find(type);
	if (iter == m_WindowList.end())
		return NULL;

	return iter->second;
}

unsigned  int  UIWindowDataManager::GetWindowNumber()
{
	return m_WindowList.size();
}

UIWindowItemData* UIWindowDataManager::GetWindowByPos(unsigned int pos)
{
	assert(pos >= 0);
	assert(pos < m_WindowList.size());

	std::map<int, UIWindowItemData*>::iterator iter = m_WindowList.begin();
	for (int i=0; i>=0; i++)
	{
		if (pos == i)
			break;

		++iter;
	}

	return iter->second;
}

std::string UIWindowDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/uiwindow.txt";

	return "uiwindow";
}

unsigned  int  UIWindowDataManager::GetSize()
{
	return m_WindowList.size()*sizeof(UIWindowItemData);
}

bool  UIWindowDataManager::Init()
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

void  UIWindowDataManager::Tick()
{

}

void  UIWindowDataManager::Destroy()
{
	std::map<int, UIWindowItemData*>::iterator iter   = m_WindowList.begin();
	std::map<int, UIWindowItemData*>::iterator iter_e = m_WindowList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_WindowList.clear();
}

bool  UIWindowDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	UIWindowItemData* pWindowItem = (UIWindowItemData*)pData;
	assert(pWindowItem != NULL);

	return true;
}

bool  UIWindowDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  UIWindowDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	UIWindowItemData* pItemData = new UIWindowItemData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_WindowList.insert(std::map<int, UIWindowItemData*>::value_type(pItemData->mWindowType, pItemData));
	return true;
}
