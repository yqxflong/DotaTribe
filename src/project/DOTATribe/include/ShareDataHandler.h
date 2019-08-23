//Name：ShareDataHandler
//Function：分享管理器
//Written By：尹强

#ifndef  _DOTATRIBE_SHAREDATAHANDLER_H_
#define  _DOTATRIBE_SHAREDATAHANDLER_H_

#include "../include/IDataHandler.h"
#include <include/common/Singleton.h>
#include <include/mem/DPacket.h>

class ShareDataHandler: public IDataHandler, public cobra_win::Singleton2<ShareDataHandler>{
public:
	ShareDataHandler(){};
	virtual ~ShareDataHandler(){};
	virtual void onDestroy();
	virtual bool init(); 
public:
	void ShareTo_WeChat_PengYouQuan();	//调用微信SDK
	void ToServer_FinishShare();
	void decodePacket(cobra_win::DPacket & packet);
};

#endif