#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include "../include/CSMapTable.h"
#include "../include/NFControlsManager.h"
void Attribute::decodePacketData_ChangeEquip(cobra_win::DPacket & packet, int heroindex)
{
	unsigned char tmp_clen = 0;
	packet >> tmp_clen;
	mapPropertyList_.clear();
	for (int i = 0; i < tmp_clen; i++)
	{
		unsigned char atype;	//0~13
		packet >> atype;
		int avalue;
		packet >> avalue;
		mapPropertyList_.insert(std::map<int, int>::value_type(atype, avalue));
	}
}