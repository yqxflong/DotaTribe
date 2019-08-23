#include <cocos2d.h>
#include "../include/AnimationFileDataManager.h"
#include "../include/DBSystem.h"
#include "../include/EngineSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/String.h>
#include <include/common/Parser.h>
#include <assert.h>


AnimationFileData::AnimationFileData()
{
	mAnimationIndex =0;
	mAnimationIntervalTime = 0.0f;
	mAnimationFrameCount   = 0;
	mAnimationScale = 0.0f; 
	memset(mAnimationName, 0, sizeof(mAnimationName));
	memset(mAnimationPrefix, 0, sizeof(mAnimationPrefix));
	memset(mAnimationFileName, 0, sizeof(mAnimationFileName));
	mAnimationUISoundID=0;
}

AnimationFileData::~AnimationFileData()
{

}

bool AnimationFileData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	// 解析字符串
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(mAnimationIndex))
		return false;

	if (!parser.parser_string_value(mAnimationName, sizeof(mAnimationName)))
		return false;

	if (!parser.parser_string_value(mAnimationPrefix, sizeof(mAnimationPrefix)))
		return false;

	if (!parser.parser_int_value(mAnimationFrameCount))
		return false;

	if (!parser.parser_float_value(mAnimationIntervalTime))
		return false;

	if (!parser.parser_string_value(mAnimationFileName, sizeof(mAnimationFileName)))
		return false;

	if (!parser.parser_float_value(mAnimationScale))
		return false;

	if (!parser.parser_int_value(mAnimationUISoundID))
		return false; 

	return true;
}

template<> AnimationFileDataManager* cobra_win::Singleton2<AnimationFileDataManager>::m_pMySelf = NULL;

AnimationFileDataManager::AnimationFileDataManager(bool bLoadFromDB, bool bEncryption) : IDataManager(bLoadFromDB, bEncryption)
{
	m_AnimationFileList.clear();
}	

AnimationFileDataManager::~AnimationFileDataManager()
{

}

unsigned int AnimationFileDataManager::GetAnimationNumber()
{
	return m_AnimationFileList.size();
}

AnimationFileData* AnimationFileDataManager::GetAnimationByIdx(unsigned int index)
{
	std::map<int , AnimationFileData*>::iterator  iter_animation = m_AnimationFileList.find(index);
	if(iter_animation!=m_AnimationFileList.end())
	{	
		return iter_animation->second;
	}
	return NULL;
 }

AnimationFileData* AnimationFileDataManager::GetAnimationByName(std::string name)
{
	std::map<int , AnimationFileData*>::iterator iter   = m_AnimationFileList.begin();
	std::map<int , AnimationFileData*>::iterator iter_e = m_AnimationFileList.end();
	for (int i=0; iter!=iter_e; ++iter, ++i)
	{
		if (name == iter->second->mAnimationName)
			return iter->second;
	}

	return NULL;
}


std::string     AnimationFileDataManager::GetAnimationPlistNameByID(int animationID)
{ 
	std::map<int , AnimationFileData*>::iterator  iter_animation = m_AnimationFileList.find(animationID);
	if(iter_animation!=m_AnimationFileList.end())
	{	
		return iter_animation->second->mAnimationFileName;
	}
	return "";
}


std::string AnimationFileDataManager::GetName()
{
	if (!m_bLoadFromDB)
		return "resource/data/animationfile.txt";

	return "animationfile";
}

unsigned  int AnimationFileDataManager::GetSize()
{
	return m_AnimationFileList.size()*sizeof(AnimationFileData);
}

bool  AnimationFileDataManager::Init()
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

void  AnimationFileDataManager::Tick()
{

}

void  AnimationFileDataManager::Destroy()
{
	std::map<int, AnimationFileData*>::iterator iter   = m_AnimationFileList.begin();
	std::map<int, AnimationFileData*>::iterator iter_e = m_AnimationFileList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	return m_AnimationFileList.clear();
}

bool  AnimationFileDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	AnimationFileData* pAnimation = (AnimationFileData*)pData;
	assert(pAnimation != NULL);

	return true;
}

bool  AnimationFileDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  AnimationFileDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{
	AnimationFileData* pItemData = new AnimationFileData;
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
		return false;

	if (!Varify(pItemData))
		return false;

	m_AnimationFileList.insert(std::map<int , AnimationFileData*>::value_type(pItemData->mAnimationIndex, pItemData));
	return true;
}
