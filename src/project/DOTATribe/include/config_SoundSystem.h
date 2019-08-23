//Name：config_SoundSystem
//Function：SoundSystem配置表
//Written By：尹强

#ifndef  _DOTATRIBE_config_SoundSystem_
#define  _DOTATRIBE_config_SoundSystem_

//=======声音播放枚举======
enum{
	kSOUND_PLAY_TYPE_UNKNOWN=0,
	kSOUND_PLAY_TYPE_BACKGROUND,
	kSOUND_PLAY_TYPE_EFFECT,		//eg.
};

//=======声音停止枚举======
enum{
	kSOUND_STOP_TYPE_UNKNOWN=0,
	kSOUND_STOP_TYPE_BACKGROUND,
	kSOUND_STOP_TYPE_EFFECT,
	kSOUND_STOP_TYPE_EFFECT_ALL,
	kSOUND_STOP_TYPE_EFFECT_AND_BACKGROUND,
};


#endif