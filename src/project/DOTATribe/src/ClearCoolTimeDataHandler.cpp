#include  "../include/ClearCoolTimeDataHandler.h"
#include   "../include/IDataHandler.h" 
 
ClearCoolTimeDataHandler::ClearCoolTimeDataHandler()
{
	init();
}

ClearCoolTimeDataHandler::~ClearCoolTimeDataHandler()
{

}

void ClearCoolTimeDataHandler::handlePacket(IPacket* packet)
{

}

void ClearCoolTimeDataHandler::onDestroy()
{
	clearResult=-1;
}
bool ClearCoolTimeDataHandler::init()
{
	clearResult=-1;
	return true;
} 