

#ifndef _DOTATRIBE_BAGTEMPLATEBASEHANDLER_H_11
#define _DOTATRIBE_BAGTEMPLATEBASEHANDLER_H_11

#include <include/mem/DPacket.h>
#include "../include/BagOtherObjecthandler.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/CSMapTable.h"
#include <include/common/Singleton.h>
#include "../include/BagTemplateBase.h"
#include "../include/IDataHandler.h"


class BagTemplateBaseHandler : public IDataHandler, public cobra_win::Singleton2<BagTemplateBaseHandler>
{
public:
	virtual void handlePacket(IPacket* packet){}

	virtual void onDestroy(){}

	virtual bool init(){
		return true;

	}


	//解包模版,只负责解包模版
	BagTemplateBase * decodeTemplatePacket(cobra_win::DPacket & packet)
	{
		unsigned char catogory;
		BagTemplateBase * te = NULL;

		packet>>catogory;
		if(catogory == kBAGOBJECT)
		{
			te = new ObjectTemplate();
			ObjectTemplate * mask = (ObjectTemplate *)te;
			mask->catogory_ = catogory;
			if(! mask->decodeTemplatePacketData(packet))
				return NULL;
		}
		else if (catogory == kBAGEQUIP)
		{
			te = new EquipTemplate();
			EquipTemplate * mask = (EquipTemplate *)te;
			mask->catogory_ = catogory;
			if(! mask->decodeTemplatePacketData(packet))
				return NULL;
		}
		else if(catogory == kBAGSKIN)
		{
			te = new SkinTemplate();
			SkinTemplate * mask = (SkinTemplate *)te;
			mask->catogory_ = catogory;
			if(! mask->decodeTemplatePacketData(packet))
				return NULL;
		}

		return te;

	}

};


#define BAGTEMPLATEBASEHANDLER	BagTemplateBaseHandler::get_instance2()

#endif