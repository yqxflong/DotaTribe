//Name:BagWindowDataHandler.H
//Function:背包数据管理器
//Author:fangjun
//date:20130903
#ifndef _DOTATRIBE_BAGWINDOW_DATAHANDLER_H_
#define _DOTATRIBE_BAGWINDOW_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include "../include/CSMapTable.h"
#include "../include/CPageScroll.h"
#include "../include/BagWindow.h"


class BagWindowDataHandler : public IDataHandler, public cobra_win::Singleton2<BagWindowDataHandler>{
public:
	CPageScroll* DATA_RightPanel;//use for pool only
	BagWindow * DATA_Window;//use for pool only

private:


public:
	BagWindowDataHandler();
	virtual ~BagWindowDataHandler();

	void SetData(CPageScroll * page, BagWindow * window);
protected:

	virtual void handlePacket(IPacket* packet);

	virtual void onDestroy();

	virtual bool init();

public:
	/*
		通知服务器，解锁包格
	*/
	void ToServerOpenLockBag(int bagType, int bagindex);
	

public:
	/*
		背包是否已满
	*/
	int IsBagFull();

	/*
		处理关闭背包响应操作
	*/
	void HandleCloseBag();
};

#define BAGWINDOWDATAHANDLER (BagWindowDataHandler::get_instance2())


#endif