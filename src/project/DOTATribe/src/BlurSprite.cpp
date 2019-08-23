#include "../include/BlurSprite.h"

BlurSprite::BlurSprite()
{

}

BlurSprite::~BlurSprite()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
}

void BlurSprite::setBlurSize(float size)
{
	CCSize s = this->getTexture()->getContentSizeInPixels();
	blur_ = ccp(1 / s.width, 1 / s.height);
	blur_ = ccpMult(blur_, size);

	CCArray * childArray = this->getChildren();
	CCObject * arg;
	BlurSprite * sb;
	CCARRAY_FOREACH(childArray, arg)
	{
		sb = (BlurSprite *)arg;
		s = sb->getTexture()->getContentSizeInPixels();
		sb->blur_ = ccp(1 / s.width, 1 / s.height);
		sb->blur_ = ccpMult(sb->blur_, size);
	}
}

BlurSprite * BlurSprite::create(const char * pszFileName, std::string fshfilepath)
{
	BlurSprite * ret = new BlurSprite();
	ret->fshFilePath = fshfilepath;
	if(ret && ret->initWithFile(pszFileName))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool BlurSprite::initWithTexture(CCTexture2D * texture, const CCRect& rect)
{
	if(CCSprite::initWithTexture(texture, rect))
	{
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BlurSprite::listenBackToForeground), EVNET_COME_TO_FOREGROUND, NULL);
		CCSize s = this->getTexture()->getContentSizeInPixels();
		blur_ = ccp(1 / s.width, 1 / s.height);
		for(int i = 0; i < 4; ++i)
		{
			sub_[i] = 0;
		}
		setBlurSize(0);
		this->initProgram();

		return true;
	}

	return false;
}

void BlurSprite::draw()
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
	ccBlendFunc blend = this->getBlendFunc();
	ccGLBlendFunc(blend.src, blend.dst);

	getShaderProgram()->use();
	getShaderProgram()->setUniformsForBuiltins();
	getShaderProgram()->setUniformLocationWith2f(blurLocation, blur_.x, blur_.y);
	getShaderProgram()->setUniformLocationWith4fv(subLocation, sub_, 1);

	ccGLBindTexture2D(this->getTexture()->getName());

	//
#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;

	//vertex
	int diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void *)(offset + diff));

	//texCoods
	diff = offsetof(ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void *)(offset + diff));

	//color
	diff = offsetof(ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void *)(offset + diff));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CC_INCREMENT_GL_DRAWS(1);
}

void BlurSprite::initProgram()
{
	GLchar * fragSource = (GLchar *)CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(fshFilePath.c_str()).c_str())->getCString();
	CCGLProgram * pProgram = new CCGLProgram();
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
	this->setShaderProgram(pProgram);
	pProgram->release();

	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->link();

	CHECK_GL_ERROR_DEBUG();

	this->getShaderProgram()->updateUniforms();

	CHECK_GL_ERROR_DEBUG();

	this->subLocation = glGetUniformLocation(this->getShaderProgram()->getProgram(), "substract");
	this->blurLocation = glGetUniformLocation(this->getShaderProgram()->getProgram(), "blurSize");

	CHECK_GL_ERROR_DEBUG();
}


void BlurSprite::listenBackToForeground(CCObject * obj)
{
	setShaderProgram(NULL);
	initProgram();
}