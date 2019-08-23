#ifndef  _DOTATRIBE_INPUTCOMMAND_H_
#define  _DOTATRIBE_INPUTCOMMAND_H_


enum InputCommand
{
	_TYPED_INPUT_COMMAND_UNKOWN_,                           // 未知的输入事件类型
	_TYPED_INPUT_COMMAND_SELECTED_,                         // 对象选择Selected
	_TYPED_INPUT_COMMAND_UNSELECTED_,                       // 对象被取消选择UnSelected

	
	_TYPED_INPUT_COMMAND_SKILLEFFECT_END_,					// 特效技能动画播放结束事件类型
 
	_TYPED_INPUT_COMMAND_ROLEBUFFER_END_,					// 角色Buffer播放完毕事件类型

	_TYPED_INPUT_COMMAND_ATHLETICS_SUCESS_,					// 角色战斗胜利事件类型

	_TYPED_INPUT_COMMAND_ROLEADMISSION_END_,				// 角色入场完成事件类型

	_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_,		// 恢复战斗指令运行状态 

	_TYPEF_INPUT_COMMAND_REPLAY_ATHLETICSINSTRUCTION_,		// 重播战斗指令系统

	_TYPED_INPUT_COMMAND_SKILLACTION_END_,					 //技能动画结束事件类型

	_TYPED_INPUT_COMMAND_STOP_ROLEBUFFER_,					 //结束角色Buffer事件类型

	_TYPED_INPUT_COMMAND_DRAGNODE_DRAGEND_,		             //技能面板 公共面板 拖拽结束事件类型
 
	_TYPED_INPUT_COMMAND_DRAGNODE_CLICK_,			         //技能面板 公共面板 拖拽点击事件类型

	_TYPED_INPUT_COMMAND_LOADCOMMONSKILLDATA_END_,			 //加载选择技能面板数据完成

	_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_,			 //选择技能面板数据修改

	_TYPED_INPUT_COMMAND_DESTOY_ATHLETICSDATA_,				 //删除战斗信息包

	_TYPED_INPUT_COMMAND_BASEDIALOG_CLOSE_,					 //关闭公共对话框

	_TYPED_INPUT_COMMAND_NUMBER_,                           // 输入事件类型个数
};


#endif
