/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef SPINE_CCSKELETONANIMATION_H_
#define SPINE_CCSKELETONANIMATION_H_

#include <spine/spine.h>
#include <spine/CCSkeleton.h>
#include "cocos2d.h"

namespace cocos2d { namespace extension {

/**
Draws an animated skeleton, providing a simple API for applying one or more animations and queuing animations to be played later.
*/
class CCSkeletonAnimation: public CCSkeleton {
public:
	//@存储状态序列
	std::vector<AnimationState*> states;

	//@通过SkeletonData创建
	static CCSkeletonAnimation* createWithData (SkeletonData* skeletonData);
	//@通过json文件，altas数据创建
	static CCSkeletonAnimation* createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	//@通过json，altas文件创建
	static CCSkeletonAnimation* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	//@构造函数的重载
	CCSkeletonAnimation (SkeletonData* skeletonData);	
	CCSkeletonAnimation (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	CCSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	virtual ~CCSkeletonAnimation ();

	virtual void update (float deltaTime);

	void addAnimationState (AnimationStateData* stateData = 0);
	void setAnimationStateData (AnimationStateData* stateData, int stateIndex = 0);
	void setMix (const char* fromAnimation, const char* toAnimation, float duration, int stateIndex = 0);

	//@设置当前的动画
	//#name: 指令名称
	void setAnimation (const char* name, bool loop, int configAnimationID=-1,int stateIndex = 0);
	
	//@增加动画
	void addAnimation (const char* name, bool loop, float delay = 0, int stateIndex = 0);

	//@清除指定动画
	void clearAnimation (int stateIndex = 0);

	//@清除全部动画
	void clearAllAnimation();

	//@当前动画是否完成
	bool isAnimationComplete();

protected:
	CCSkeletonAnimation ();

private:
	typedef CCSkeleton super;
	std::vector<AnimationStateData*> stateDatas;

	void initialize ();
};

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_CCSKELETONANIMATION_H_ */
