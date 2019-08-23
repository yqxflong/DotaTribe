#include   <cocos2d.h>
#include   "../include/ArenaRankDataHandler.h"

 
void ArenaRankData::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet.read(rankCount);
	unsigned short tmp_len=0;
	char * tmpChar=NULL;
	for(short rankIndex=0;rankIndex<rankCount;rankIndex++)
	{ 
		PRoleRankInfo pRoleRankInfo=new RoleRankInfo();
		if(pRoleRankInfo!=NULL)
		{ 
		    packet.read(pRoleRankInfo->roleID);
			packet.read(pRoleRankInfo->roleIconID);
			packet>>tmp_len;
			tmpChar=new char[tmp_len+1];
			packet.read(tmpChar,tmp_len);
			tmpChar[tmp_len]='\0';
			pRoleRankInfo->roleName.assign(tmpChar); 
			delete [] tmpChar;
			tmpChar=NULL;
			packet.read(pRoleRankInfo->roleLevel);
			packet.read(pRoleRankInfo->roleRankScore);
			packet.read(pRoleRankInfo->roleBltScore);
			if(pRoleRankInfo->roleRankScore>10)
			{ 
				delete pRoleRankInfo;
				pRoleRankInfo=NULL;
				continue;
			} 
			rankListVec.push_back(pRoleRankInfo);
		}
	}	 
 	
}


template<> ArenaRankDataHandler * cobra_win::Singleton2<ArenaRankDataHandler>::m_pMySelf = NULL;

ArenaRankDataHandler::ArenaRankDataHandler()
{ 
	m_pArenaRankData=NULL;
}

ArenaRankDataHandler::~ArenaRankDataHandler()
{ 
	 if(m_pArenaRankData!=NULL)
	 {
		  delete m_pArenaRankData;
		  m_pArenaRankData=NULL;
	 }
}

bool ArenaRankDataHandler::init()
{
	m_pArenaRankData=NULL;
	return true;
}


void  ArenaRankDataHandler::onDestroy()
{
	if(m_pArenaRankData!=NULL)
	{
	    delete m_pArenaRankData;
		m_pArenaRankData=NULL;
	}
}

 
void ArenaRankDataHandler::handlePacket(IPacket* packet)
{

}

