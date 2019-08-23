#ifndef  _DOTATRIBE_NPCTALKVIEW_H_
#define  _DOTATRIBE_NPCTALKVIEW_H_
 
////////////////////////////////////////////////////////////////
//Name:	 NPCTalkView
//Auchor: 	xiaobo.wu
//Func:	 NPC对话窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include   "../include/UIBaseDialog.h"
#include   "../include/EventTyper.h"
#include   "../include/NpcTalkDataManager.h"
#include	"cocos-ext.h"
 
class  NpcTalkView:  public  UIBaseDialog
{
public:  
	enum
	{
		_UNKONW_NPCTALK_TYPE_,
		_BEFOR_NPCTALK_TYPE_,
		_WIN_NPCTALK_TYPE_,
		_FAIL_NPCTALK_TYPE_,
	};

	 //数据配置文件
	enum
	{
	   _NPC_TALK_VIEW_BG_TAG_,
	   _NPC_TALK_VIEW_NAME_TAG_,
	   _NPC_TALK_VIEW_CONTENT_TAG_,
	   _NCP_TALK_VIEW_SHAPEICON_TAG_,
	   _NCP_TALK_VIEW_ARROW_TAG_,
	   _NPC_TALK_VIEW_MASK_TAG_,
	};
	NpcTalkView();
	~NpcTalkView();
public:
	static NpcTalkView * createNpcTalkView(int priority);					 

    virtual bool  checkIsTouchInUnClose(cocos2d::CCPoint touchPoint);
public:
	void    SetNpcTalkConfigData(NpcTalkData *  npcTalkData);
    bool    SetNpcTalkState(char npcTalkState,std::string pName,int pIconID,std::string nName,int nIconID);
	bool    ShowPageWithIndex(int pageIndex);
    bool    ToNextPage(char & talkState);
	bool    isFinishTalkCur();
protected:
	void   SetRoleTalkName(std::string roleName);
	void   SetRoleTalkShapeIcon(int iconID);
	void   SetRoleTalkContent(std::string  talkContent);
	void   AutoLayoutWithConfig();
	bool   InitNpcTalkView(int priority);

protected:
	bool      isFinishWithCurState;
	std::vector<TalkNode>  npcTalkVect;
	char			curNpcTalkState;
	NpcTalkData  *  pNpcTalkData;
	int			    curTalkPageIndex;
	std::string     playerName;
	int				playerIconID;
	std::string     npcName;
	int			    npcIconID;

};

#endif