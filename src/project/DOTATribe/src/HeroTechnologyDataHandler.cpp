// Name :		HeroTechnologyDataHandler.h
// Function:	ÐÅÑöÊý¾Ý
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/HeroTechnologyDataHandler.h"
using namespace std;

HeroTechnologyDataHandler::HeroTechnologyDataHandler(){

	Lasttime = 0;
	m_View_PosY = 1;
	IsAsk = true;
	IsFirstAsk =true;
	m_TabNum = 0;
	m_ReturnWindow = 0;
	m_HideWindow = 0;
	m_ReturnTabNum = 0;
	m_free_pray_times = 0;
	m_pray_cost = 0;
}

HeroTechnologyDataHandler::~HeroTechnologyDataHandler()
{
	if (HeroTechnologyList.size()>0)
	{
		std::vector<HeroTechnology*>::iterator iter =  HeroTechnologyList.begin();
		std::vector<HeroTechnology*>::iterator iter_end =  HeroTechnologyList.end();
		for(;iter!=iter_end;++iter)
		{
			delete *(iter);
		}
		HeroTechnologyList.clear();
	}

}

void HeroTechnologyDataHandler::handlePacket(IPacket* packet){

}

HeroTechnology* HeroTechnologyDataHandler::GetTechnologyByID(int id)
{
	std::vector<HeroTechnology*>::iterator iter_begin = HeroTechnologyList.begin();
	std::vector<HeroTechnology*>::iterator iter_end = HeroTechnologyList.end();

	for (;iter_begin!=iter_end;++iter_begin)
	{
		if ((*iter_begin)->id == id)
			return *iter_begin;
	}
	return NULL;
}
bool HeroTechnologyDataHandler::init(){
	return true;
}

void HeroTechnologyDataHandler::onDestroy()
{
	std::vector<HeroTechnology*>::iterator iter =  HeroTechnologyList.begin();
	std::vector<HeroTechnology*>::iterator iter_end =  HeroTechnologyList.end();
	for(;iter!=iter_end;++iter)
	{
		delete *(iter);
	}
	HeroTechnologyList.clear();
}

