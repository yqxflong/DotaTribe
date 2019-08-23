#include   "../include/AddChallengeDataHandler.h"
#include   "../include/IDataHandler.h" 

AddChallengeDataHandler::AddChallengeDataHandler()
{
	init();
}

AddChallengeDataHandler::~AddChallengeDataHandler()
{

}

void AddChallengeDataHandler::handlePacket(IPacket* packet)
{

}

void AddChallengeDataHandler::onDestroy()
{
	addChallenegeCount=-1;
}
bool AddChallengeDataHandler::init()
{
	addChallenegeCount=-1;
	return true;
} 