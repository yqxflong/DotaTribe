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
#include <algorithm>
#include <cocos2d.h>
#include <spine/CCSkeleton.h>
#include <spine/spine-cocos2dx.h>

USING_NS_CC;
using std::min;
using std::max;

/////////////////////////////////////////////////
//author:  xiaobo.wu
//function:  Modify For Spine Call  System
//date:   2013/09/01
///////////////////////////////////////////////// 


namespace cocos2d { namespace extension {

CCSkeleton* CCSkeleton::createWithData (SkeletonData* skeletonData, bool ownsSkeletonData) {
	CCSkeleton* node = new CCSkeleton(skeletonData, ownsSkeletonData);
	node->autorelease();
	return node;
}

CCSkeleton* CCSkeleton::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	CCSkeleton* node = new CCSkeleton(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

CCSkeleton* CCSkeleton::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	CCSkeleton* node = new CCSkeleton(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

void CCSkeleton::initialize () {
	m_scriptEventHandler = 0;
	atlas = 0;
	debugSlots = false;
	debugBones = false;
	isSkeletonFinish=false;
	timeScale = 1;

	blendFunc.src = GL_ONE;
	blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	setOpacityModifyRGB(true);

	m_ObjectUUID="";
	pCallBackDelegate=NULL ;
	pCurAnimation=NULL;
	pSkeletonCallBackVec=new std::vector<PSkeletonCallBack_Node>; 
	FOR_EACH_CALL_BEGIN(_DEFULAT_INIT_SKELETON_CALL_SIZE)
	    PSkeletonCallBack_Node pSkeletonCallNode=new SkeletonCallBack_Node();
	    if(pSkeletonCallNode!=NULL)
	    pSkeletonCallBackVec->push_back(pSkeletonCallNode);
	FOR_EACH_CALL_END
	  
	m_AnimationID=-1;
	skeletonLoopCount=0l;

	FOR_EACH_CALL_BEGIN(_DEFULAT_INIT_BONE_EFFECT_SIZE)
		BoneEfectData   effectData;
	boneEffectDataVec.push_back(effectData);
	FOR_EACH_CALL_END
	 
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
	scheduleUpdate();
}

void CCSkeleton::setSkeletonData (SkeletonData *skeletonData, bool ownsSkeletonData) {
	skeleton = Skeleton_create(skeletonData);
	rootBone = skeleton->bones[0];
	this->ownsSkeletonData = ownsSkeletonData;	
}

CCSkeleton::CCSkeleton () {
	initialize();
}

CCSkeleton::CCSkeleton (SkeletonData *skeletonData, bool ownsSkeletonData) {
	initialize();

	setSkeletonData(skeletonData, ownsSkeletonData);
}

CCSkeleton::CCSkeleton (const char* skeletonDataFile, Atlas* atlas, float scale) {
	initialize();

	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
	CCAssert(skeletonData, json->error ? json->error : "Error reading skeleton data.");
	SkeletonJson_dispose(json);

	setSkeletonData(skeletonData, true);
}

CCSkeleton::CCSkeleton (const char* skeletonDataFile, const char* atlasFile, float scale) {
	initialize();	  
	atlas = Atlas_readAtlasFile(atlasFile);
	CCAssert(atlas, "Error reading atlas file."); 
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonDataFile);
	CCAssert(skeletonData, json->error ? json->error : "Error reading skeleton data file.");
	SkeletonJson_dispose(json); 
	setSkeletonData(skeletonData, true);
}

CCSkeleton::~CCSkeleton () {
	if (ownsSkeletonData) SkeletonData_dispose(skeleton->data);
	if (atlas) Atlas_dispose(atlas);
	Skeleton_dispose(skeleton);
	m_scriptEventHandler = 0;
	if(pSkeletonCallBackVec!=NULL)
	{
		size_t sizeCallCount=pSkeletonCallBackVec->size();
		FOR_EACH_CALL_BEGIN(sizeCallCount)
			pSkeletonCallBackVec->at(index)->destroy();
			delete  pSkeletonCallBackVec->at(index);
		FOR_EACH_CALL_END
		pSkeletonCallBackVec->clear();
		delete  pSkeletonCallBackVec;
		pSkeletonCallBackVec=NULL;
	}
	pCallBackDelegate=NULL;
	pCurAnimation=NULL;
	skeletonLoopCount=0l;
	isSkeletonFinish=false;
	boneEffectDataVec.clear();


}

void CCSkeleton::update (float deltaTime) {
	Skeleton_update(skeleton, deltaTime * timeScale);
}

void CCSkeleton::draw () {
	CC_NODE_DRAW_SETUP();

	ccGLBlendFunc(blendFunc.src, blendFunc.dst);
	ccColor3B color = getColor();
	skeleton->r = color.r / (float)255;
	skeleton->g = color.g / (float)255;
	skeleton->b = color.b / (float)255;
	skeleton->a = getOpacity() / (float)255;
	if (premultipliedAlpha) {
		skeleton->r *= skeleton->a;
		skeleton->g *= skeleton->a;
		skeleton->b *= skeleton->a;
	}

 
	CCTextureAtlas* textureAtlas = 0;
	ccV3F_C4B_T2F_Quad quad;
	quad.tl.vertices.z = 0;
	quad.tr.vertices.z = 0;
	quad.bl.vertices.z = 0;
	quad.br.vertices.z = 0;
	for (int i = 0, n = skeleton->slotCount; i < n; i++) {
		Slot* slot = skeleton->slots[i];
		if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
		RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
		CCTextureAtlas* regionTextureAtlas = getTextureAtlas(attachment);
		if (regionTextureAtlas != textureAtlas) {
			if (textureAtlas) {
				textureAtlas->drawQuads();
				textureAtlas->removeAllQuads();
			}
		}
		textureAtlas = regionTextureAtlas;
		if (textureAtlas->getCapacity() == textureAtlas->getTotalQuads() &&
			!textureAtlas->resizeCapacity(textureAtlas->getCapacity() * 2)) return;
		RegionAttachment_updateQuad(attachment, slot, &quad, premultipliedAlpha);
		textureAtlas->updateQuad(&quad, textureAtlas->getTotalQuads());
	}
	if (textureAtlas) {
		textureAtlas->drawQuads();
		textureAtlas->removeAllQuads();
	}

	if (debugSlots) {
		// Slots.
		ccDrawColor4B(0, 0, 255, 255);
		glLineWidth(1);
		CCPoint points[4];
		ccV3F_C4B_T2F_Quad quad;
		for (int i = 0, n = skeleton->slotCount; i < n; i++) {
			Slot* slot = skeleton->slots[i];
			if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
			RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
			RegionAttachment_updateQuad(attachment, slot, &quad);
			points[0] = ccp(quad.bl.vertices.x, quad.bl.vertices.y);
			points[1] = ccp(quad.br.vertices.x, quad.br.vertices.y);
			points[2] = ccp(quad.tr.vertices.x, quad.tr.vertices.y);
			points[3] = ccp(quad.tl.vertices.x, quad.tl.vertices.y);
			ccDrawPoly(points, 4, true);
		}
	}
	if (debugBones) {
		// Bone lengths.
		glLineWidth(2);
		ccDrawColor4B(255, 0, 0, 255);
		for (int i = 0, n = skeleton->boneCount; i < n; i++) {
			Bone *bone = skeleton->bones[i];
			float x = bone->data->length * bone->m00 + bone->worldX;
			float y = bone->data->length * bone->m10 + bone->worldY;
			ccDrawLine(ccp(bone->worldX, bone->worldY), ccp(x, y));
		}
		// Bone origins.
		ccPointSize(4);
		ccDrawColor4B(0, 0, 255, 255); // Root bone is blue.
		for (int i = 0, n = skeleton->boneCount; i < n; i++) {
			Bone *bone = skeleton->bones[i];
			ccDrawPoint(ccp(bone->worldX, bone->worldY));
			if (i == 0) ccDrawColor4B(0, 255, 0, 255);
		}
	}
}

CCTextureAtlas* CCSkeleton::getTextureAtlas (RegionAttachment* regionAttachment) const {
	return (CCTextureAtlas*)((AtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
}

CCRect CCSkeleton::boundingBox () {
	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;
	float scaleX = getScaleX();
	float scaleY = getScaleY();
	float vertices[8];
	for (int i = 0; i < skeleton->slotCount; ++i) {
		Slot* slot = skeleton->slots[i];
		if (!slot->attachment || slot->attachment->type != ATTACHMENT_REGION) continue;
		RegionAttachment* attachment = (RegionAttachment*)slot->attachment;
		RegionAttachment_computeVertices(attachment, slot->skeleton->x, slot->skeleton->y, slot->bone, vertices);
		minX = min(minX, vertices[VERTEX_X1] * scaleX);
		minY = min(minY, vertices[VERTEX_Y1] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X1] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y1] * scaleY);
		minX = min(minX, vertices[VERTEX_X4] * scaleX);
		minY = min(minY, vertices[VERTEX_Y4] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X4] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y4] * scaleY);
		minX = min(minX, vertices[VERTEX_X2] * scaleX);
		minY = min(minY, vertices[VERTEX_Y2] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X2] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y2] * scaleY);
		minX = min(minX, vertices[VERTEX_X3] * scaleX);
		minY = min(minY, vertices[VERTEX_Y3] * scaleY);
		maxX = max(maxX, vertices[VERTEX_X3] * scaleX);
		maxY = max(maxY, vertices[VERTEX_Y3] * scaleY);
	}
	CCPoint position = getPosition();
	return CCRectMake(position.x + minX, position.y + minY, maxX - minX, maxY - minY);
}

// --- Convenience methods for Skeleton_* functions.

void CCSkeleton::updateWorldTransform () {
	Skeleton_updateWorldTransform(skeleton,this);
}

void CCSkeleton::setToSetupPose () {
	Skeleton_setToSetupPose(skeleton);
}
void CCSkeleton::setBonesToSetupPose () {
	Skeleton_setBonesToSetupPose(skeleton);
}
void CCSkeleton::setSlotsToSetupPose () {
	Skeleton_setSlotsToSetupPose(skeleton);
}

Bone* CCSkeleton::findBone (const char* boneName) const {
	return Skeleton_findBone(skeleton, boneName);
}

Slot* CCSkeleton::findSlot (const char* slotName) const {
	return Skeleton_findSlot(skeleton, slotName);
}

bool CCSkeleton::setSkin (const char* skinName) {
	return Skeleton_setSkinByName(skeleton, skinName) ? true : false;
}

Attachment* CCSkeleton::getAttachment (const char* slotName, const char* attachmentName) const {
	return Skeleton_getAttachmentForSlotName(skeleton, slotName, attachmentName);
}
bool CCSkeleton::setAttachment (const char* slotName, const char* attachmentName) {
	return Skeleton_setAttachment(skeleton, slotName, attachmentName) ? true : false;
}

// --- CCBlendProtocol

ccBlendFunc CCSkeleton::getBlendFunc () {
    return blendFunc;
}

void CCSkeleton::setBlendFunc (ccBlendFunc blendFunc) {
    this->blendFunc = blendFunc;
}

void CCSkeleton::setOpacityModifyRGB (bool value) {
	premultipliedAlpha = value;
}

bool CCSkeleton::isOpacityModifyRGB () {
	return premultipliedAlpha;
}


void CCSkeleton::registerCallBackDelegate(SkeletonCallBackProtocol * pSkeletonCallBackDelegate)
{
	if(pCallBackDelegate!=pSkeletonCallBackDelegate)
	{
		pCallBackDelegate=pSkeletonCallBackDelegate;
	}
}

void CCSkeleton::registerScriptEventDelegate(int scripeEventHandler)
{
	m_scriptEventHandler = scripeEventHandler;
}

void CCSkeleton::removeAllCallBackNode()
{
	if(pSkeletonCallBackVec!=NULL)
	{
		size_t sizeCallCount=pSkeletonCallBackVec->size();
		FOR_EACH_CALL_BEGIN(sizeCallCount)
			delete  pSkeletonCallBackVec->at(index);
		FOR_EACH_CALL_END
			pSkeletonCallBackVec->clear();
	}
}

void CCSkeleton::resetAllCallBackNode()
{
	 
	if(pSkeletonCallBackVec!=NULL)
	{
		size_t sizeCallCount=pSkeletonCallBackVec->size();
		FOR_EACH_CALL_BEGIN(sizeCallCount)
		   pSkeletonCallBackVec->at(index)->resetData();
		FOR_EACH_CALL_END
	}
}


std::vector<PSkeletonCallBack_Node> *  CCSkeleton::getCallBackEventVec()
{
	 return pSkeletonCallBackVec;
}

SkeletonCallBackProtocol *	 CCSkeleton::getCallBackEventDelegate()
{
	 return pCallBackDelegate;
}

void   CCSkeleton::postSkeletonActionFinish()
{
	if(!isSkeletonFinish)
	{
		isSkeletonFinish=true;
		if(pCallBackDelegate)
		{
			pCallBackDelegate->skeletonTriggerCallHandler(_Skeleton_Animation_Change_Event_,m_AnimationID,NULL);
		}
		if(m_scriptEventHandler)
		{
			char animationId[128];
			sprintf(animationId, "%d", m_AnimationID);
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_scriptEventHandler, "skeletonTriggerCallHandler", _Skeleton_Animation_Change_Event_, animationId, this, "CCSkeleton");
		}
	} 
}


void  CCSkeleton::resetSkeletonActionFinish()
{
	isSkeletonFinish=false;
}


 
void  CCSkeleton::removeAllBoneEffect() 				          //移除所有骨骼绑定特效
{
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
		boneEffectDataVec.at(index).resetData();
	FOR_EACH_CALL_END
}
void  CCSkeleton::removeAllLoopEffect() 						  //删除所有循环骨骼绑定特效
{
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
		if(boneEffectDataVec.at(index).isValid&&boneEffectDataVec.at(index).isLoopBoneEffect)
			boneEffectDataVec.at(index).resetData();
	FOR_EACH_CALL_END
}
void  CCSkeleton::removeAllUnLoopEffect() 						  //删除所有非循环骨骼绑定特效
{
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
		if(boneEffectDataVec.at(index).isValid&&!boneEffectDataVec.at(index).isLoopBoneEffect)
			boneEffectDataVec.at(index).resetData();
	FOR_EACH_CALL_END
}
void  CCSkeleton::removeBoneEffectByName(std::string boneName)    //删除指定的骨骼绑定特效
{
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
		if(boneEffectDataVec.at(index).isValid&&boneEffectDataVec.at(index).boneName==boneName)
			boneEffectDataVec.at(index).resetData();
	FOR_EACH_CALL_END
}
void  CCSkeleton::removeBoneEffectByID(int boneEffectID) 		  //删除指定ID的骨骼特效
{
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
		if(boneEffectDataVec.at(index).isValid&&boneEffectDataVec.at(index).boneEffectID==boneEffectID)
			boneEffectDataVec.at(index).resetData();
	FOR_EACH_CALL_END
}


void  CCSkeleton::removeBoneEffect(int boneEffectID,std::string boneName)     //删除指定的ID和绑定的骨骼的特效
{
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
		if(boneEffectDataVec.at(index).isValid&&boneEffectDataVec.at(index).boneEffectID==boneEffectID&&boneEffectDataVec.at(index).boneName==boneName)
		boneEffectDataVec.at(index).resetData();
	FOR_EACH_CALL_END
}



void  CCSkeleton::addBoneEffectWithData(PSkeletonCallBack_Node pSkeletonCallData,Bone * pBindBone)  //根据骨骼回调数据加载骨骼绑点特效
{
	if(pSkeletonCallData!=NULL&&pBindBone!=NULL)
	{
		size_t  boneEffectCount=boneEffectDataVec.size();
		FOR_EACH_CALL_BEGIN(boneEffectCount)
			if(!boneEffectDataVec.at(index).isValid)
			{
				boneEffectDataVec.at(index).isValid=true;
				boneEffectDataVec.at(index).boneEffectID=pSkeletonCallData->pAttachParam->effectID;
				boneEffectDataVec.at(index).compositeEffectID=pSkeletonCallData->pAttachParam->compositeEffectID;
				boneEffectDataVec.at(index).boneEffectType=pSkeletonCallData->eventType;
				boneEffectDataVec.at(index).boneName=pSkeletonCallData->pAttachParam->boneName;
				boneEffectDataVec.at(index).parentBone=pBindBone;
				boneEffectDataVec.at(index).isLoopBoneEffect=pSkeletonCallData->pAttachParam->isDurationBoneEffect;
				boneEffectDataVec.at(index).isFollowBoneEffect=pSkeletonCallData->pAttachParam->isFollowBoneEffect;
				return ;
			}
		FOR_EACH_CALL_END
		 BoneEfectData  effectData;
		 effectData.isValid=true;
		 effectData.boneEffectID=pSkeletonCallData->pAttachParam->effectID;
		 effectData.compositeEffectID=pSkeletonCallData->pAttachParam->compositeEffectID;
		 effectData.boneEffectType=pSkeletonCallData->eventType;
		 effectData.boneName=pSkeletonCallData->pAttachParam->boneName;
		 effectData.parentBone=pBindBone;
		 effectData.isLoopBoneEffect=pSkeletonCallData->pAttachParam->isDurationBoneEffect;
		 effectData.isFollowBoneEffect=pSkeletonCallData->pAttachParam->isFollowBoneEffect;
		 boneEffectDataVec.push_back(effectData);
	}
}

void  CCSkeleton::addBoneEffectWithData(BoneEfectData & boneEffectData)
{  
	size_t  boneEffectCount=boneEffectDataVec.size();
	FOR_EACH_CALL_BEGIN(boneEffectCount)
	if(!boneEffectDataVec.at(index).isValid)
	{
		boneEffectDataVec.at(index).isValid=true;
		boneEffectDataVec.at(index).boneEffectID=boneEffectData.boneEffectID;
		boneEffectDataVec.at(index).compositeEffectID=boneEffectData.compositeEffectID;
		boneEffectDataVec.at(index).boneEffectType=boneEffectData.boneEffectType;
		boneEffectDataVec.at(index).boneName=boneEffectData.boneName;
		boneEffectDataVec.at(index).parentBone=boneEffectData.parentBone;
		boneEffectDataVec.at(index).isLoopBoneEffect=boneEffectData.isLoopBoneEffect;
		boneEffectDataVec.at(index).isFollowBoneEffect=boneEffectData.isFollowBoneEffect;
		return ;
	}
	FOR_EACH_CALL_END

	BoneEfectData  effectData;
	effectData.isValid=true;
	effectData.boneEffectID=boneEffectData.boneEffectID;
	effectData.compositeEffectID=boneEffectData.compositeEffectID;
	effectData.boneEffectType=boneEffectData.boneEffectType;
	effectData.boneName=boneEffectData.boneName;
	effectData.parentBone=boneEffectData.parentBone;
	effectData.isLoopBoneEffect=boneEffectData.isLoopBoneEffect;
	effectData.isFollowBoneEffect=boneEffectData.isFollowBoneEffect;
	boneEffectDataVec.push_back(effectData);

}
 

void  CCSkeleton::updateBoneEffect()
{
	if(pCallBackDelegate!=NULL)
	{
		size_t   boneEffectCount=boneEffectDataVec.size();
		FOR_EACH_CALL_BEGIN(boneEffectCount)
			if(boneEffectDataVec.at(index).isValid)
			{
				if(!boneEffectDataVec.at(index).isCreate)
				{
					boneEffectDataVec.at(index).isCreate=true;
					pCallBackDelegate->boneBindEffectCallHandler(_BONEEFFECT_CREATE_EFFECT_TYPE_,boneEffectDataVec.at(index));
					if(!boneEffectDataVec.at(index).isFollowBoneEffect)
					{
						boneEffectDataVec.at(index).resetData();
					}
					continue;
				}
				else
				pCallBackDelegate->boneBindEffectCallHandler(_BONEEFFECT_UPDATE_EFFECT_TYPE_,boneEffectDataVec.at(index));
			}
		FOR_EACH_CALL_END
	}
}

 

}} // namespace cocos2d { namespace extension {
