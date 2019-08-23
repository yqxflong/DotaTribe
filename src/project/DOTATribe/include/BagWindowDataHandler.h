//Name:BagWindowDataHandler.H
//Function:�������ݹ�����
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
		֪ͨ����������������
	*/
	void ToServerOpenLockBag(int bagType, int bagindex);
	

public:
	/*
		�����Ƿ�����
	*/
	int IsBagFull();

	/*
		����رձ�����Ӧ����
	*/
	void HandleCloseBag();
};

#define BAGWINDOWDATAHANDLER (BagWindowDataHandler::get_instance2())


#endif