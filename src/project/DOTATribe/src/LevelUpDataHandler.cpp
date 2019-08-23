// Name :		LevelUpDataHandler.h
// Function:	角色升级数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan


#include "../include/LevelUpDataHandler.h"

using namespace std;

LevelUpDataHandler::LevelUpDataHandler(){
	m_showIsNeed =true;
	m_showFlag =true;
}

LevelUpDataHandler::~LevelUpDataHandler(){

	if (LevelUpDataList.size()>0)
	{
		std::vector<LevelUpData*>::iterator iter = LevelUpDataList.begin();
		std::vector<LevelUpData*>::iterator iter_end = LevelUpDataList.end();
		for (;iter!=iter_end;++iter)
		{
			delete (*iter);
		}
		LevelUpDataList.clear();
	}
}

void LevelUpDataHandler::handlePacket(IPacket* packet){

}

bool LevelUpDataHandler::init(){
	return true;
}

void LevelUpDataHandler::onDestroy(){
	std::vector<LevelUpData*>::iterator iter = LevelUpDataList.begin();
	std::vector<LevelUpData*>::iterator iter_end = LevelUpDataList.end();
	for (;iter!=iter_end;++iter)
	{
		delete (*iter);
	}
	LevelUpDataList.clear();
	m_showFlag = true;
	m_showIsNeed = true;
}
 

bool  LevelUpDataHandler::isEmpty()
{
	return LevelUpDataList.empty();
}
 