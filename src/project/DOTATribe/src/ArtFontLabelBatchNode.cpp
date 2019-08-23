/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  艺术字符标签  (用于战斗数值动画)
//date:   2013/08/26
///////////////////////////////////////////////// 
#include <cocos2d.h>
#include   "../include/ArtFontLabelBatchNode.h"
#include   "../include/ResourceIDDataManager.h"
 
using namespace cocos2d;

#define  DEFAULT_ANCHOR  ccp(0,0)
#define  MIDDLE_ANCHOR	 ccp(0.5f,0.5f)


ArtFontLabelBatchNode::ArtFontLabelBatchNode()
{ 
	m_PlabelBatchNode=NULL;
     Init();
}

ArtFontLabelBatchNode::~ArtFontLabelBatchNode()
{
    // Destroy();
}

ArtFontLabelBatchNode *  ArtFontLabelBatchNode::CreateArtFontWithArray(std::vector<int> & fontArray)
{
	ArtFontLabelBatchNode * pArtFontLabelBatchNode=new ArtFontLabelBatchNode();
	if(pArtFontLabelBatchNode&&pArtFontLabelBatchNode->InitNumberLabelBatchNode(fontArray))
	{ 
	     return  pArtFontLabelBatchNode;
	}
    return NULL;
} 

bool  ArtFontLabelBatchNode::InitNumberLabelBatchNode(std::vector<int> & fontArray)
{    
	 return SetLabelWithArray(fontArray);
}
 
//暂时废弃
std::string  ArtFontLabelBatchNode::GetTexturePathNameFromPlist(char * plistName)
{
	std::string plistPrexName=plistName;
	int  preFileNameCharCount=plistPrexName.find('.');
	if(preFileNameCharCount>=128)
	{
		plistPrexName+=".png";
		return plistPrexName;
	}
	else
	{
		plistPrexName=plistPrexName.substr(0,preFileNameCharCount);
		plistPrexName+=".png";
		return plistPrexName;
	}
}
 

bool  ArtFontLabelBatchNode::SetLabelWithArray(std::vector<int> & fontArray)
{   
	//清除之前的Label
	if(m_PlabelBatchNode)
	{   
		m_PlabelBatchNode->removeAllChildrenWithCleanup(true);
		m_PlabelBatchNode->removeFromParentAndCleanup(true);
		m_PlabelBatchNode=NULL;
	}  
	if(!fontArray.empty())
	{ 
		size_t arrayCount=fontArray.size();
		float  maxHeight=0.0f; 
		float  tmpHeight=0.0f;
		cocos2d::CCSprite * pSprite=NULL;
		std::vector<cocos2d::CCSprite *> spriteVector;
		for(size_t index=0;index<arrayCount;index++)
		{ 
			pSprite=ResourceIDDataManager::get_instance2()->GetSpriteFromID(fontArray.at(index));
			if(pSprite)
			{
				pSprite->setAnchorPoint(DEFAULT_ANCHOR);
				pSprite->setPosition(ccp(totoalWidth,0.0f));
				totoalWidth+=pSprite->getContentSize().width;
				tmpHeight=pSprite->getContentSize().height;
				maxHeight=tmpHeight > maxHeight? tmpHeight: maxHeight; 
				spriteVector.push_back(pSprite);
			}
		} 
		cocos2d::CCRenderTexture * pRenderCache=cocos2d::CCRenderTexture::create(totoalWidth,maxHeight,cocos2d::kCCTexture2DPixelFormat_RGBA4444);
		pRenderCache->getSprite()->getTexture()->setAntiAliasTexParameters();
		pRenderCache->begin();
		pRenderCache->setAnchorPoint(DEFAULT_ANCHOR);
		arrayCount = spriteVector.size();
		for(size_t index=0;index<arrayCount;index++)
		{
			spriteVector.at(index)->visit();
		} 
		pRenderCache->end();
		
		spriteVector.clear();
	
		m_PlabelBatchNode=cocos2d::CCSprite::createWithTexture(pRenderCache->getSprite()->getTexture());
		m_PlabelBatchNode->setAnchorPoint(DEFAULT_ANCHOR);
		m_PlabelBatchNode->setFlipY(true);
		return true;
	}
	return false;
}

 
 void ArtFontLabelBatchNode::setColor(const ccColor3B& color) 			//设置颜色接口
 {
	 if(m_PlabelBatchNode!=NULL)
	 { 
		 m_PlabelBatchNode->setColor(color);
	 }
 }

 const ccColor3B& ArtFontLabelBatchNode::getColor(void) 				//获得颜色
 {
	 if(m_PlabelBatchNode!=NULL)
	 { 
		 return m_PlabelBatchNode->getColor();
	 }
     return ccWHITE;
 }
  
GLubyte ArtFontLabelBatchNode::getOpacity(void) 						//获得透明度
{
    if(m_PlabelBatchNode!=NULL)
	{
		 return  m_PlabelBatchNode->getOpacity();
	}
	return 255;
}

void ArtFontLabelBatchNode::setOpacity(GLubyte opacity) 				//设置透明度
{
	if(m_PlabelBatchNode!=NULL)
	{
		 m_PlabelBatchNode->setOpacity(opacity);
	}
}

void ArtFontLabelBatchNode::setOpacityModifyRGB(bool bValue) 			//设置透明与颜色同步
{

}

bool ArtFontLabelBatchNode::isOpacityModifyRGB(void) 					//获得当前颜色是否与透明度
{
   return false;
}



void  ArtFontLabelBatchNode::SetAnchorPoint(cocos2d::CCPoint anchorPositon)
{
     if(m_PlabelBatchNode!=NULL)
	 {
		 m_PlabelBatchNode->setAnchorPoint(anchorPositon);
	 }
}

void  ArtFontLabelBatchNode::SetPosition(cocos2d::CCPoint position)
{
	if(m_PlabelBatchNode!=NULL)
	{
		m_PlabelBatchNode->setPosition(position);
	}
    
}

void   ArtFontLabelBatchNode::SetScale(float & fscale)
{
	if(m_PlabelBatchNode!=NULL)
	{
		m_PlabelBatchNode->setScale(fscale);
	}

}


float ArtFontLabelBatchNode::GetLabelTotalWidth()
{
	return totoalWidth;
}
 
cocos2d::CCPoint   ArtFontLabelBatchNode::GetAnchorPosition() 
{
	if(m_PlabelBatchNode!=NULL)
	{
		return  m_PlabelBatchNode->getAnchorPoint();
	}
     return CCPointZero;
}

cocos2d::CCPoint ArtFontLabelBatchNode::GetPosition()
{

	if(m_PlabelBatchNode!=NULL)
	{
		return  m_PlabelBatchNode->getPosition();
	}
	 return CCPointZero;
}

bool  ArtFontLabelBatchNode::GetVisible()
{

	if(m_PlabelBatchNode!=NULL)
	{
		return  m_PlabelBatchNode->isVisible();
	}
     return true;
}

 

void   ArtFontLabelBatchNode::SetVisible(bool isVisible)
{
     if(m_PlabelBatchNode!=NULL)
	 {
		 m_PlabelBatchNode->setVisible(isVisible);
	 }
}

 
cocos2d::CCSprite *  ArtFontLabelBatchNode::GetBatchNodeLabel()
{
     return m_PlabelBatchNode;
}

void ArtFontLabelBatchNode::Init()
{
    //to do nothing
	objectType_=ART_LABEL_OBJECT_TYPE;
	objectSubID_=0;
	m_PlabelBatchNode=NULL;
	fontIDArray.clear();
	labelPosition=CCPointZero;
	labelAnchor=CCPointZero;
	totoalWidth=0.0f;

}


//销毁接口
void ArtFontLabelBatchNode::Destroy()
{
	if(!IsValid())
		return ;
	totoalWidth=0.0f;
	fontIDArray.clear();
	if(m_PlabelBatchNode!=NULL)
	{  
		m_PlabelBatchNode->removeAllChildrenWithCleanup(true);
		m_PlabelBatchNode->removeFromParentAndCleanup(true);
		m_PlabelBatchNode=NULL;
	}
}
 

//事件通知消息接口
void ArtFontLabelBatchNode::OnCommandHanlder(int EventTypeID)
{
  
}







