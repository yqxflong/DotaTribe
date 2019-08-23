#include <cocos2d.h>
#include "../include/EquipPromoteDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"


using namespace std;

EquipPromoteDataHandler::EquipPromoteDataHandler()
{
}

EquipPromoteDataHandler::~EquipPromoteDataHandler()
{

}


void EquipPromoteDataHandler::onDestroy()
{
	m_Attribute_List.clear();
}
	
bool EquipPromoteDataHandler::init()
{
	return true;
}
