#ifndef   _DOTATRIBE_SELECTSKILLCONTROLLER_H_
#define   _DOTATRIBE_SELECTSKILLCONTROLLER_H_

////////////////////////////////////////////////////////////////
//Name:	 SelectSkillControler
//Auchor: 	xiaobo.wu
//Func:	 技能选择控制器
//Maintainer: 	xiaobo.wu
//date:  2013.06.30 
////////////////////////////////////////////////////////////////
 

#include    "../include/UIDragNode.h"
#include    "../include/SelectSkillMode.h"
#include    "../include/SelectSkillWindow.h"
#include    "../include/SelectSkillDataType.h"
#include    "../include/RoleSkillsDataHandler.h"
#include    "../include/CCDragNodeLayer.h"
#include    <vector>
#include    <cocos2d.h> 
  
class  SelectSkillWindow;
class  SelectSkillMode;


class    SelectSkillController : public cocos2d::CCNode ,public DragDelegateProtocol,public CCDragLayerProtocol
{ 
public: 

  //拖拽结点的对象类型
  enum
  {
	  _UIDRAGNODE_UNKONW_OBJTYPE_,  
	  _UIDRAGNODE_COMMONPANLE_OBJTYPE_,				//公共面板结点
	  _UIDRAGNODE_TARGETPANLE_OBJTYPE_,				//目标面板结点
  };

  enum
  {
	  _SKILLCONTROLLER_UNKONW_STATE_,             //未知控制状态
	  _SKILLCONTROLLER_EQUIPSKILLPANEL_STATE_,    //装备技能状态
	  _SKILLCONTROLLER_SKILLADDPOINTPANEL_STATE_, //技能槽加点状态
  };


  enum
  {
	  _UIDRAGNODE_DEFAULT_VALUE_=-1,        //未知默认参数
  };


public:
       SelectSkillController();
	   virtual ~SelectSkillController();
public:
	 static  SelectSkillController *   createSelectSkillController(SelectSkillWindow * pSelectSkillWindow);
 
	 /*
	 事件通知接口
	 */
	 void    onCommandHandler(int eventType,void * ptr); 

     /*
	 销毁控制器
	 */
	 void    Destroy();

	 /*
	 通知底册数据ModeUpdate 
	 */
	 void    UpdateRoleSkillsModeData();
	   
	 /*
	 事件通知
	 */
	 bool	 delegateDragEndEventHandler(int eventType,CCSignSprite * pSignSprite,cocos2d::CCPoint & touchPoint);

	 /*
	  获得之前技能ID Icon的名称
	 */
	 std::string   GetSkillIconNameFromSkillID(int skillItemID);
 
	 PSkillItem    GetSkillsBagInfoFromID(int skillItemID);

	 PSkillNotoch  GetSkillsTargetInfoFromID(int skillItemID);

public:
	 
	//关闭的选择技能界面回调事件
	void    closeBtnCallBackHandler(cocos2d::CCObject * pSender);

	//关闭技能信息界面回调事件
	void	closeSkillInfoDialogCallBackHandler(cocos2d::CCObject * pSender);

protected:

     /*
	 初始化选择面板控制器
	 */
	 bool    initSelectSkillController(SelectSkillWindow * pSelectSkillWindow);
  
    /*
	 选择技能到技能凹槽中
	*/
	 void    equipSkillToSkillNotch(int skillNotchIndex,int sourceTargeSkillID);

	 /*
	 交换技能凹槽的技能
	 */
	 bool    changeEquipSkillToOtherNotch(int skillNotchIndex,int skillItemID);
	  
	 /*
	 删除技能凹槽的技能
	 */
	 void	 removeEquipSkillWithID(int skillItemID);
 
private:
	/*
	  数据控制器
	*/
	SelectSkillMode *  pSelectSkillMode_;			

	/*
	 视图UI
	*/
	SelectSkillWindow * pSelectSkillWindow_;

    /*
	 当前控制的状态
	*/
	int  curSkillContollerState_;
public:
	unsigned char m_heroIndex;
 
};




#endif