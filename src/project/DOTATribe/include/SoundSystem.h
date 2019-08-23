#ifndef  _DOTATRIBE_SOUNDSYSTEM_H_
#define  _DOTATRIBE_SOUNDSYSTEM_H_

#include "../include/config_SoundSystem.h"
#include <include/common/Singleton.h>
#include <string>
#include <list>
#include <set>
using  namespace  cobra_win;

class SoundSystem : public cobra_win::Singleton2<SoundSystem>
{
public:
	enum
	{
		_TYPED_EFFECTSOUND_UNKOWN_,        // 未知音效类型
		_TYPED_EFFECTSOUND_COMMONBUTTON_,  // 按钮点击音效
		_TYPED_EFFECTSOUND_ITEM_,          // 道具音效
		_TYPED_EFFECTSOUND_EFFECT_,        // 特效音效
		_TYPED_EFFECTSOUND_MONSTER_,       // 怪物死亡音效
		_TYPED_EFFECTSOUND_OTHER_,         // 其他音效类型
		_TYPED_EFFECTSOUND_NUMBER_,        // 音效总数
	};

public:
	struct _EFFECT_INFO_
	{
		int       mEffectType;     // 音效类型
		char      mSoundName[128]; // 音效名称
		int       mSoundId;        // 音效索引Id
		long long mStartTime;      // 音效开始时间
		bool      mLoop;           // 是否循环

		_EFFECT_INFO_()
		{
			memset(this, 0, sizeof(_EFFECT_INFO_));
		}
	};

private:
	long long   m_MyTimer;
	std::string m_BackSoundName;
	std::list<_EFFECT_INFO_> m_EffectList;
	std::list<std::string>   m_preLoadSoundEffectList;
	bool m_isBackgroundSound;		//背景音乐是否关闭
	bool m_isEffectSound;			//音效是否关闭
private:
	inline void _registerEvent();
	inline void _unRegisterEvent();
public:
	SoundSystem();
	virtual ~SoundSystem();

public:
	//@设置背景音乐静音
	void   MuteBackgroundMusic(bool bMute);
	//@设置特效音效静音
	void   MuteEffectSound(bool bMute);
	//@是否背景音乐静音
	bool   IsBackgroundMusicMute();
	//@是否特效音效静音
	bool   IsEffectSoundMute();

public:
	//@播放指定音效类型和名称的音效
	void   PlayEffect(int effectID, std::string soundName, bool bLoop, float fPitch = 1.0f);
	//@停止指定类型的音效
	void   StopEffect(int effectID);
	//@停止所有音效
	void StopAllEffect();
	//@播放背景音效
	void   PlayBackgroundMusic(std::string soundName,int soundVolume=10);
	//@停止背景音效
	void   StopBackgroundMusic();
	
	//@预加载音效队列
	void   PreLoadSoundEffectQueue(std::set<int> & soundEffectVec);

	//@卸载预加载音效队列
	void   UnLoadSoundEffectQueue();

public:
	/*
		设置背景音效音量(0.0-1.0)
		仅在真机上有效
	*/
	void   SetBackgroundMusicVolume(float volume);
	/*
		获得背景音效音量
		仅在真机上有效
	*/
	float  GetBackgroundMusicVolume();

public:
	//@标配
	bool   Init();
	void   Tick();
	void   Destroy();

private:
	//@是否可以播放
	bool   IsCanPlay(int effectID);
	//@播放特效音效
	void   InsertEffectInfo(int effectID, std::string soundName, int soundId, bool bLoop);
	//@暂停所有特效
	void   PauseAllEffectSound();
	//@恢复音效
	void   ResumeAllEffectSound();

public:
	//@程序失去焦点回调处理
	void   OnPauseEventHandler();
	//@程序获得焦点回调处理
	void   OnResumeEventHandler();
	//@程序进入后台回调处理
	void   OnEnterBackgroundEventHandler();
	//@程序进入前台回调处理
	void   OnEnterForegroundEventHandler();

public:
	//@处理声音播放事件
	static void On_SoundEvent_Handle_Play(int iEventType, std::string owerData, std::list<std::string>& paramList);
	//@处理声音停止事件
	static void On_SoundEvent_Handle_Stop(int iEventType, std::string owerData, std::list<std::string>& paramList);

	SoundSystem* GetLuaInstance(){
		return SoundSystem::get_instance2();
	}
};

#define  SOUNDSYSTEM  (SoundSystem::get_instance2())


#endif
