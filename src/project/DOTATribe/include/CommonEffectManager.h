//Name：CommonEffectManager
//Function：特效管理器
//Author:	Johny

#ifndef   _DOTATRIBE_COMMONEFFECTMANAGER_H_
#define   _DOTATRIBE_COMMONEFFECTMANAGER_H_

#include <cocos2d.h>
#include <spine/Bone.h>
#include <map>
#include <vector>

class   CommonEffect;
class   HeroicRole;

class   CommonEffectManager
{
public:
	CommonEffectManager();
	~CommonEffectManager();
public:
	//@标配
	virtual  void Init();
	virtual  void Tick();
	virtual  void Destroy();

	static CommonEffectManager *   CreateCommonEffectManager(HeroicRole * pHeroicRole); 
public: 
	void    CommonEffectFactory(int compositeEffectID,int effectType,int commonEffectID);
	void    CommonEffectFactoryWithBone(int compositeEffectID,int effectType,int commonEffectID,cocos2d::extension::Bone * pBindBone);
	void    AddCompositeEffect(int compositeEffectID);
	void    AddCommonEffect(CommonEffect * pCommonEffect);
	void    RemoveCommonEffect(CommonEffect * pCommonEffect);
	void    RemoveScreenEffect();
	void    RemoveRoleEffect();
	void    RemoveScreenShakeEffect();
	size_t  GetLoopCommonEffectCount();
	size_t	GetUnLoopCommonEffectCount();
	void    RemoveAllCommonEffect();
	void    RemoveAllLoopCommonEffect();
	void    RemoveAllUnLoopCommonEffect();
	void    SetAllBindBoneEffectVisible(bool isVisible=false);
	void    RemoveAllUnLoopBindBoneEffect();
	void    RemoveCompositeEffectWithID(int compositeEffectID);
	void    SetAnimationSpeedScale(float speedScale);
	void    UpdatePosition(cocos2d::CCPoint  position);
	void    UpdateWithBone(int compositeEffectID,int commonEffectID,int commoneEffectType, std::string  bindBoneName, cocos2d::extension::Bone * pBindBone);
	 
protected:
	bool   InitCommonEffectManager(HeroicRole * pHeroicRole);
	void   RemoveBoneBindCallBack(CommonEffect * pCommonEffect);
	void   SetBondEffectVisible(CommonEffect * pCommonEffect,bool isVisible=false);
protected:
	std::multimap<int,std::vector<CommonEffect *> > m_loopEffectList;   //(frameAnimateEffect ParticleEffect SkeletonEffect)
	std::multimap<int,std::vector<CommonEffect *> > m_unLoopEffectList;

	std::map<int,CommonEffect *> m_screenEffectList;
	std::map<int,CommonEffect *> m_roleEffectList;

	float  m_fSpeedScale;
	HeroicRole * m_pHeroicRole;

};



#endif

