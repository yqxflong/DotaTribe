#ifndef  _DOTATRIBE_COMMONDATADEF_H_
#define  _DOTATRIBE_COMMONDATADEF_H_

#include "../include/CPublicVarReader.h"
#include "../include/NFToolController.h"

////////////////////////////////////////////////////////////////
//Name:	 CommonDataDef
//Auchor: 	xiaobo.wu
//Func:	 公共通用的数据类型定义
//Maintainer: 	xiaobo.wu
//date:   2014/02/13
////////////////////////////////////////////////////////////////

//公共奖励数据定义

typedef  struct  rewarditemnode_tag
{  
	IByte rewardItemType;						//奖励类型 0 物品
	int	  rewardItemCount;						//		
	IByte rewardCatagory;
	int   rewardTemplateID;
	std::string   rewardRewardName;
	IByte rewardQuality;
	int	  rewardIconID; 
public:
	rewarditemnode_tag()
	{
		rewardItemType=0;
		rewardItemCount=0;
		rewardCatagory=0;
		rewardTemplateID=0;
		rewardRewardName="";
		rewardQuality=0;
		rewardIconID=0;
	}
	void decodePacketData(cobra_win::DPacket & packet)
	{
		packet.read(rewardItemType);
		packet.read(rewardItemCount);
		if(rewardItemType == 0)
		{
			packet.read(rewardCatagory);
			packet.read(rewardTemplateID);
			NFC_ParsePacketString(packet,rewardRewardName);
			packet.read(rewardQuality);
			packet.read(rewardIconID);
		}  
 	}
}RewardItemNode,*PRewardItemNode;

#endif

 