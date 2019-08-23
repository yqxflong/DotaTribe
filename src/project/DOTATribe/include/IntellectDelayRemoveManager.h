//Name：IntellectDelayRemoveManager
//Function： 指令计时器
//Author:	Johny

#ifndef  _DOTATRIBE_INTELLECTDELAYREMOVEMANAGER_H_
#define  _DOTATRIBE_INTELLECTDELAYREMOVEMANAGER_H_
 
#include  <cocos2d.h>
#include  <include/common/Singleton.h>
#include  <map>

using  namespace  cobra_win;

class  IntellectDelayRemoveManager: public cobra_win::Singleton2<IntellectDelayRemoveManager>
{
public:
	IntellectDelayRemoveManager();
	~IntellectDelayRemoveManager();
public:
	virtual void  Init();
	virtual void  Destroy();
	virtual void  OnCommandHandler(int eventType,void * ptr){};
public:
	void  InsertDelayRemoveManager(int loopEffectID);
    void  UpdateDelayRemoveManager();
	void  RemoveDelayRemoveManager(int loopEffectID);
	bool  IsDelayRemoveAtInterval(int loopEffectID);
	void  RemoveAllDelayElement();
protected:
	std::map<int,int>::iterator GetDelayRemvoeElement(int loopEffectID);
	std::map<int,int>  m_delayRemoveMap;
public:
	friend  class  cobra_win::Singleton2<IntellectDelayRemoveManager>;
};

#define   INTELDELAYREMOVEMANGER    (IntellectDelayRemoveManager::get_instance2())
  

#endif
