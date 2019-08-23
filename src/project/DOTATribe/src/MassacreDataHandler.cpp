// Name :		MassacreDataHandler.h
// Function:	扫荡数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/MassacreDataHandler.h"
#include "../include/MassacrePacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

using namespace std;

MassacreDataHandler::MassacreDataHandler()
:MassacreCount(0)
,EndType(0){
	MassacreDataList.clear();
	MassacreCanForceClose  = false;
}

bool MassacreDataHandler::init(){
	return true;
}

void MassacreDataHandler::onDestroy()
{
	std::vector<MassacreData*>::iterator iter =  MassacreDataHandler::get_instance2()->MassacreDataList.begin();
	std::vector<MassacreData*>::iterator iter_end =  MassacreDataHandler::get_instance2()->MassacreDataList.end();
	for(;iter!=iter_end;++iter)
	{
		std::vector<ItemData*>::iterator iter2 =  (*iter)->ItemDataList.begin();
		std::vector<ItemData*>::iterator iter2_end = (*iter)->ItemDataList.end();
		for (;iter2!=iter2_end;++iter2)
		{
			delete *(iter2);
		}
		(*iter)->ItemDataList.clear();
		delete *(iter);
	}
	MassacreDataHandler::get_instance2()->MassacreDataList.clear();
	MassacreCanForceClose = true;
}

void MassacreDataHandler::ToServerPacket(int missionid,int stateid){
	C2SMassacrePacket packet(missionid,stateid);
	packet.Send();
}

void MassacreDataHandler::decodePacketData(cobra_win::DPacket & packet){
	//收信息
	unsigned short tmp_len=0;
	char *tmpChar=0;
	std::vector<MassacreData*>::iterator iter =  MassacreDataHandler::get_instance2()->MassacreDataList.begin();
	std::vector<MassacreData*>::iterator iter_end =  MassacreDataHandler::get_instance2()->MassacreDataList.end();
	for(;iter!=iter_end;++iter)
	{
		std::vector<ItemData*>::iterator iter2 =  (*iter)->ItemDataList.begin();
		std::vector<ItemData*>::iterator iter2_end = (*iter)->ItemDataList.end();
		for (;iter2!=iter2_end;++iter2)
		{
			delete *(iter2);
		}
		(*iter)->ItemDataList.clear();
		delete *(iter);
	}
	MassacreDataHandler::get_instance2()->MassacreDataList.clear();

	packet>>MassacreDataHandler::get_instance2()->EndType;
	if (MassacreDataHandler::get_instance2()->EndType == 0)
	{
		packet>>MassacreDataHandler::get_instance2()->MassacreCount;
		for (int i=0;i<MassacreDataHandler::get_instance2()->MassacreCount;i++)
		{
			MassacreData* pMassacreData = new MassacreData();
			packet>>pMassacreData->money;
			packet>>pMassacreData->roleExp;
			packet>>pMassacreData->shapeExp;
			packet>>pMassacreData->itemCount;
			for (int j=0;j<pMassacreData->itemCount;j++)
			{
				ItemData* pItemData = new ItemData();

				packet>>tmp_len;
				tmpChar=new char[tmp_len+1];
				packet.read(tmpChar,tmp_len);
				tmpChar[tmp_len]='\0';
				pItemData->itemName.assign(tmpChar);
				delete[] tmpChar;tmpChar=0;

				packet>>pItemData->itemCount;
				packet>>pItemData->itemID;
				packet>>pItemData->iconID;
				packet>>pItemData->quality;
				packet>>pItemData->isEquip;
				pMassacreData->ItemDataList.push_back(pItemData);
			}

			MassacreDataHandler::get_instance2()->MassacreDataList.push_back(pMassacreData);
		}
	}

	AfterDecodePacket();
}
void MassacreDataHandler::AfterDecodePacket(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEDATA_MASSACREWINDOW_);
}

bool MassacreDataHandler::getCanForceCloseState()
{
	return MassacreCanForceClose;
}
void MassacreDataHandler::setToForceCloseInitState()
{
	MassacreCanForceClose = false;
}