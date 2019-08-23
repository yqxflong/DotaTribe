//Name：EmailDataHandler
//Function：邮箱数据
//Written By：尹强

#ifndef _DOTATRIBE_EmailDataHandler_H_
#define _DOTATRIBE_EmailDataHandler_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <list>
#include <vector>
#include <string>


class EmailListDataObject{
public:
	EmailListDataObject();
	~EmailListDataObject();

public:
	int count_;			//数量<br>
	unsigned char type_;	//类型 0物品 1金钱 2经验 3钻石 4声望 5体力 <br>
	unsigned char catogory; //物品类型
	int itemId_;			//物品ID<br>
	int templateId_;	//物品模板ID<br>
	unsigned char quality_;		//品质<br>
	int iconId_;			//图标ID<br>
};

enum{
	kSYSTEM = 0,
	kPERSONAL,
};

enum
{
	_TYPE_NOT_READ_ = 0,   //未读信件
	_TYPE_ALREADY_READ_,   //已读信件
	
};

/**
	 * 玩家邮件信息返回<br>
	 * short count 数量<br>
	 * for(count){<br>
	 * int id<br>
	 * byte type 类型 0系统 1个人<br>
	 * byte hasread 是否读过 0未读1已读<br>
	 * String title 标题<br>
	 * }<br>
	 */
class EmailListData{
public:
	EmailListData();
	~EmailListData();
public:
		int mailID_;						//邮件ID
		unsigned char type_;		//类型<br>
		unsigned char hasread;		//是否读过 0未读1已读<br>
		std::string title_;						//标题<br>
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

/**
	 * 发送邮件请求<br>
	 * int id 收件人ID<br>
	 * String targetName 收件人名称<br>
	 * String title 标题<br>
	 * String content 内容<br>
	 * byte attachmentCount 附件数量<br>
	 * for(attachmentCount){<br>
	 * byte type 类型 0物品 1金钱 2经验<br>
	 * int amount 数量<br>
	 * int itemId 物品ID<br>
	 * int templateId 模板ID<br>
	 * }<br>
	 */
class EmailWriteDataObject{
public:
	 unsigned char type_;	//类型 0物品 1金钱 2经验<br>
	 int amount_;				//数量<br>
	 int itemId_;					//物品ID<br>
	 int templateId_;			//模板ID<br>
};

class EmailWriteData{
public:
	EmailWriteData();
	~EmailWriteData();
public:
	 int id_;		//收件人ID<br>	没有则传-1
	 std::string targetName_;	//收件人名称<br>
	 std::string  title_;		//标题<br>
	 std::string content_;		//内容<br>
	 unsigned char attachmentCount_;	//附件数量<br>
	 std::list<EmailWriteDataObject*> attlist_;		//附件列表
};


/**
	 * 查看邮件返回<br>
	 * int id<br>
	 * byte type 类型 0系统 1个人<br>
	 * byte hasread 是否读过 0未读1已读<br>
	 * String title 标题<br>
	 * int sourceId 发件人ID<br>
	 * String sourceName 发件人名称<br>
	 * String time 发送时间<br>
	 * String content 内容<br>
	 * byte attachmentCount 附件数量<br>
	 * for(attachmentCount){<br>
	 * byte type 类型 0物品 1金钱<br>
	 * int count 数量<br>
	 * if(type == 物品){<br>
	 * byte catogory 物品类型<br>
	 * int itemId 物品ID<br>
	 * int templateId 物品模板ID<br>
	 * byte quality 品质<br>
	 * int iconId 图标ID<br>
	 * }<br>
	 * }<br>
	 */

/************************************************************************/
/*   查看邮件信息                                                        */
/************************************************************************/
class EmailInfoData
{
public:
	EmailInfoData();
	~EmailInfoData();
public:
	int mailID_;
	unsigned char type_;			// 类型 0系统 1个人<br>
	unsigned char hasread;			//  是否读过 0未读1已读<br>
	std::string title;			//  标题<br>
	int sourceId;					//  发件人ID<br>
	std::string sourceName;			//  发件人名称<br>
	std::string time;			//  发送时间<br>
	std::string content;			//  内容<br>
	unsigned char attachmentCount;			//  附件数量<br>
	std::vector<EmailListDataObject*> attachmentlist;
public:
	void decodePacketData(cobra_win::DPacket & packet);

	void ClearAttachmentList();
};

/************************************************************************/
/*   邮箱数据句柄                                                        */
/************************************************************************/
enum{
	_ENUM_UPDATE_EMAILLIST_TYPE_ = 0,			//更新邮件列表
	_ENUM_UPDATE_EMAILINFO_TYPE_,				//更新邮件内容
	_ENUM_UPDATE_GETATTACHMENTINFO_TYPE_,		//获得附件之后更新
	_ENUM_UPDATE_SENDEMAIL_TYPE_,				//发送邮件更新
	_ENUM_UPDATE_EMAILREMOVE_TYPE_				//删除邮件

};

class EmailDataHandler : public IDataHandler, public cobra_win::Singleton2<EmailDataHandler>{
public:
	std::vector<EmailListData*> m_vecSystemEmail;	//系统邮件列表
	std::vector<EmailListData*> m_vecPersonalEmail;	//个人邮件列表

	EmailInfoData *m_pEmailInfo;
private:
	int m_EmilId;			//要邮件的id
	int m_EmailType;		//邮件类型
public:
	bool m_isGettingAtt;			//是否正在进行一键收取过程
	bool m_isGettingAttSending;		//是否正在等待回复
	int m_getAllAttIndex;			//
	int m_getAllAttPerStep;			//Check 0 Get 1
	int m_HasAttMailNum;			//
	bool m_IsGetAllMaillist;		//是否是因为一件获取附件而获取邮件列表
public:
	EmailDataHandler();
	virtual ~EmailDataHandler();
public:
	void decodePacketData(cobra_win::DPacket & packet);
	virtual void handlePacket(IPacket* packet);
	virtual void onDestroy();
	virtual bool init();

	/*
		一键收取全部邮件步骤
	*/
	void GetAllATTStep();
	void GetAllAttStepBegin();
	void GetAllATTStepDone();
	void GetAllStop();
	/*
		清理数据
	*/
	void ClearEmailDataList();

	/*
		重载系统与个人邮件列表	
	*/
	void reloadSystemAndPersonalEmail();
	/*
		写邮件
	*/
	void WriteEmail(EmailWriteData* emailData);
	/*
		写邮件反馈
	*/
	void FeedBack_WriteEmail(bool result);

	/*
		查询邮件
	*/
	void QueryEmail();
	/*
		查询邮件反馈
	*/
	void FeedBack_QueryEmail();

	/*
		一键获取附件	
	*/
	void GetATT(int mailID);
	/*
		一键获取附件反馈
	*/
	void FeedBack_GetATT(bool result);
	/*
		* 删除邮件请求<br>
	*/
	void RemoveEmail(int mailId,int type);
	/*
		*删除邮件返回<br>
	*/
	void FeedBack_RemoveEmail(bool result);

	/*
		点击查看邮件
	*/
	void CheckEmailToServer(int emailid);

	/*
		接收邮件信息
	*/
	void ReceiveCheckEmailInfo(cobra_win::DPacket & packet);
private:
	/*
		删除系统链表信件
	*/
	void RemoveSystemEmailList();
	/*
		删除个人链表信件
	*/
	void RemovePersonalEmailList();
public:
	/*
		获得当前未读系统读信件
	*/
	int GetSystemEmailUnreadNum();
	/*
		获得当前未读个人信件
	*/
	int GetProsonEmailUnreadNum();
};
#define EMAILDATAHANDLER (EmailDataHandler::get_instance2())

#endif

