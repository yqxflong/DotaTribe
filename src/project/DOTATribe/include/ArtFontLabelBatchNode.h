#ifndef  _DOTATRIBE_ARTFONTLABELBATCHNODE_H_
#define  _DOTATRIBE_ARTFONTLABELBATCHNODE_H_

#include  <cocos2d.h>
#include  "../include/BaseObject.h"
#include  "../include/ArtFontDataManager.h"
#include  <string>

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  艺术字符标签  (用于战斗数值动画)
//date:   2013/08/26
///////////////////////////////////////////////// 
  
using namespace cocos2d;

class  ArtFontLabelBatchNode: public BaseObject,public cocos2d::CCRGBAProtocol
{
public:
 	ArtFontLabelBatchNode();
	~ArtFontLabelBatchNode();
public:
	static ArtFontLabelBatchNode *  CreateArtFontWithArray(std::vector<int> & fontArray);
	bool   InitNumberLabelBatchNode(std::vector<int> & fontArray);
	bool   SetLabelWithArray(std::vector<int> & fontArray);
	void   SetAnchorPoint(cocos2d::CCPoint anchorPositon);
	void   SetPosition(cocos2d::CCPoint position);
	void   SetScale(float & fscale);
	float  GetLabelTotalWidth();
	cocos2d::CCPoint GetAnchorPosition();
	cocos2d::CCPoint GetPosition();
	virtual void setColor(const ccColor3B& color);			//设置颜色接口
	virtual const ccColor3B& getColor(void);				//获得颜色
	virtual GLubyte getOpacity(void);						//获得透明度
	virtual void setOpacity(GLubyte opacity);				//设置透明度
	virtual void setOpacityModifyRGB(bool bValue);			//设置透明与颜色同步
	virtual bool isOpacityModifyRGB(void);					//获得当前颜色是否与透明度

   //Modify  Begin
	virtual bool isCascadeColorEnabled(void) {return false;}
	virtual void setCascadeColorEnabled(bool cascadeColorEnabled) {}
	virtual void updateDisplayedColor(const ccColor3B& color) {}
	virtual bool isCascadeOpacityEnabled(void) {return false;}
	virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled){}
	virtual void updateDisplayedOpacity(GLubyte opacity) {}
	virtual const ccColor3B& getDisplayedColor(void) {  return ccWHITE; }
	virtual GLubyte getDisplayedOpacity(void) {return 255;}


	//Modify End 
	void   SetVisible(bool isVisible);
	bool   GetVisible();

	cocos2d::CCSprite *  GetBatchNodeLabel();    
	virtual   void Init();
	virtual   void Destroy();
	virtual   void OnCommandHanlder(int EventTypeID);
protected:
	std::string  GetTexturePathNameFromPlist(char * plistName);
protected: 
    cocos2d::CCSprite *  m_PlabelBatchNode;
	std::vector<int>	fontIDArray;		  
	cocos2d::CCPoint	labelPosition;  
	cocos2d::CCPoint    labelAnchor; 
	float               totoalWidth;
};


#endif