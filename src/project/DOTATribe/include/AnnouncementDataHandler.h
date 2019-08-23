#ifndef   _DOTATRIBE_ANNOUNCEMENT_DATA_HANDLER_H_
#define   _DOTATRIBE_ANNOUNCEMENT_DATA_HANDLER_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  公告内存数据 
//date:   2013/11/18
///////////////////////////////////////////////// 
#include   <cocos2d.h>
#include   <include/common/Singleton.h>
#include   <string>
#include   <queue>
#include   <include/mem/DPacket.h>
#include   "../include/CPublicVarReader.h" 


 
class AnnoucementMemData
{
protected:
	unsigned char annoucementCSSType;
	std::string annoucementContent;
public:
	AnnoucementMemData();
	virtual ~AnnoucementMemData();
    void decodePacketData(cobra_win::DPacket & packet);
	unsigned char getAnnoucementCSSType()
	{
		return annoucementCSSType;
	}
	void setAnnoucementCSSType(unsigned char t)
	{
		annoucementCSSType = t;
	}

	std::string getAnnoucementContent()
	{
		return annoucementContent;
	}
	void setAnnoucementContent(std::string t)
	{
		annoucementContent = t;
	}
};

class  AnnoucementDataHandler: public IDataHandler, public cobra_win::Singleton2<AnnoucementDataHandler>
{
protected:
	std::queue<AnnoucementMemData>          m_dAnnouceCacheMemDataQueue;		  //广播信息Cache队列
public:
	AnnoucementDataHandler();
	virtual ~AnnoucementDataHandler();
public:
	virtual void handlePacket(IPacket* packet); 
	virtual void onDestroy();
	virtual bool init();
public:
	void	         decodePacket(cobra_win::DPacket & packet);
	/*
	 * 检测当期队列是否为空
	 */
	bool			 IsAnnoucementQueueEmpty();
	/*
	 *	导出栈低元素
	 */
    bool			 TopAnnoucementItem(AnnoucementMemData & topItem);
	/*
	 *	删除栈低元素
	 */
	bool			 PopAnnoucementItem();
   /*
    *	清空队里
    */ 
	void			 RemoveAllCacheItem();

	/*
	 *	测试 广播队列
    */
	void		 PushTeshItem(std::string content);
	 
public:
	friend   class   cobra_win::Singleton2<AnnoucementDataHandler>;
};

#define ANNOUCEMENTDATAHANDLER    (AnnoucementDataHandler::get_instance2())

  
#endif