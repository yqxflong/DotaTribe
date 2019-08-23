/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  置灰精灵  
//date:   2013/12/09
///////////////////////////////////////////////// 
#include "../include/CCGrapSprite.h"
using namespace cocos2d; 

CCGrapSprite::CCGrapSprite()
{
	m_bIsGrapTexute=false;
	m_bIsCreateWithFileName=false;
	m_sFileName="";
	m_sFrameName="";
}
CCGrapSprite::~CCGrapSprite()
{ 

}
CCGrapSprite* CCGrapSprite::createGrapSpriteWithFileName(std::string pszFileName,bool isGrapSprite)
{ 
	CCGrapSprite * pGrapSprite=new CCGrapSprite();
	if(pGrapSprite&&pGrapSprite->initGrapSpriteWithFileName(pszFileName,isGrapSprite))
	{
		pGrapSprite->autorelease();
		return pGrapSprite;
	}
	CC_SAFE_DELETE(pGrapSprite);
	return NULL;
}

CCGrapSprite* CCGrapSprite::createGrapSpriteWithFrameName(std::string frameNames,bool isGrapSprite)
{
	CCGrapSprite * pGrapSprite=new CCGrapSprite();
	if(pGrapSprite&&pGrapSprite->initGrapSpriteWithFrameName(frameNames,isGrapSprite))
	{
		return pGrapSprite;
	}
	CC_SAFE_DELETE(pGrapSprite);
	return NULL;
}

bool CCGrapSprite::initWithTexture(CCTexture2D* texture, const CCRect&  rect)
{ 
	if(CCSprite::initWithTexture(texture, rect) )
	{ 
		if(m_bIsGrapTexute)
		{
			CCSize s = getTexture()->getContentSizeInPixels();
			this->initProgram();
		}
		return true;
	} 
	return false;
}

void CCGrapSprite::draw()
{
	if(m_bIsGrapTexute)  
	{
		ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
		ccBlendFunc blend = getBlendFunc();
		ccGLBlendFunc(blend.src, blend.dst);

		getShaderProgram()->use();
		getShaderProgram()->setUniformsForBuiltins();

		ccGLBindTexture2D( getTexture()->getName());

		//
		// Attributes
		//
#define kQuadSize sizeof(m_sQuad.bl)
		long offset = (long)&m_sQuad;

		// vertex
		int diff = offsetof( ccV3F_C4B_T2F, vertices);
		glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

		// texCoods
		diff = offsetof( ccV3F_C4B_T2F, texCoords);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

		// color
		diff = offsetof( ccV3F_C4B_T2F, colors);
		glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		CC_INCREMENT_GL_DRAWS(1);
	}
	else
	{
		CCSprite::draw();
	}
	
}
void CCGrapSprite::initProgram()
{
	if(!m_bIsGrapTexute)
	return ;

	const  GLchar * pfrag =    "#ifdef GL_ES \n \
							   precision mediump float; \n \
							   #endif \n\
							   uniform sampler2D u_texture; \n \
							   varying vec2 v_texCoord; \n \
							   varying vec4 v_fragmentColor; \n \
							   void main(void) \n \
							   { \n \
							   float alpha = texture2D(u_texture, v_texCoord).a; \n \
							   float grey = dot(texture2D(u_texture, v_texCoord).rgb, vec3(0.299,0.587,0.114)); \n \
							   gl_FragColor = vec4(grey, grey, grey,alpha); \n \
							   } ";

	CCGLProgram* pProgram = new CCGLProgram();
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pfrag);
	setShaderProgram(pProgram);
	pProgram->release();

	CHECK_GL_ERROR_DEBUG();

	getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	CHECK_GL_ERROR_DEBUG();

	getShaderProgram()->link();

	CHECK_GL_ERROR_DEBUG();

	getShaderProgram()->updateUniforms();

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(CCGrapSprite::listenBackToForeground),
		EVNET_COME_TO_FOREGROUND,NULL);
	  
}
void CCGrapSprite::listenBackToForeground(CCObject *obj)
{
	if(!m_bIsGrapTexute)
	return ;
	setShaderProgram(NULL);
	initProgram();
}



 
void CCGrapSprite::setGrapTexture(bool isGrapEnable)
{
	if(m_bIsGrapTexute!=isGrapEnable)
	{
		m_bIsGrapTexute=isGrapEnable;
		this->initProgram();
		if(!m_bIsGrapTexute)
		{   
			updateInterTexture();
		}
	}
} 

void CCGrapSprite::setProperty(std::string nameType,std::string textureName,bool isGrapTexture)
{
	m_bIsGrapTexute=isGrapTexture;
	if(nameType=="File")
	{
		m_bIsCreateWithFileName=true;
	    m_sFileName=textureName;
	}
	else if(nameType=="Frame")
	{
		m_bIsCreateWithFileName=false;
		m_sFrameName=textureName;
	}
	updateInterTexture();
	if(isGrapTexture)
	{
		this->initProgram();
	}
}


bool  CCGrapSprite::initGrapSpriteWithFileName(std::string pszFileName,bool isGrapSprite)
{  
	if(pszFileName=="0")
	{
		return cocos2d::CCSprite::init();
	}  
	m_bIsGrapTexute=isGrapSprite;
	if(cocos2d::CCSprite::initWithFile(pszFileName.c_str()))
	{  
		m_sFileName=pszFileName;
		m_bIsCreateWithFileName=true;
		return true;
	}
	return false;
}


bool  CCGrapSprite::initGrapSpriteWithFrameName(std::string frameName,bool isGrapSprite)
{
	if(frameName=="0")
	{
		return cocos2d::CCSprite::init();
	}  
	m_bIsGrapTexute=isGrapSprite;
	if(cocos2d::CCSprite::initWithSpriteFrameName(frameName.c_str()))
	{
		m_sFrameName=frameName;
		m_bIsCreateWithFileName=false;
		return true;
	}
	return false;
}

void  CCGrapSprite::updateInterTexture()
{
	if(m_bIsCreateWithFileName)
	{ 
		this->initWithFile(m_sFileName.c_str());
	}
	else
	{
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_sFrameName.c_str());
		this->setDisplayFrame(pFrame); 
	}
}