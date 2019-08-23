#ifndef  _COMPONENT_SCROLLSPRITELAYER_H
#define  _COMPONENT_SCROLLSPRITELAYER_H
#include "cocos2d.h"
#include "vector"
using namespace  cocos2d;

#define   SCROLLNODELAYERITEM     7   //���ӽڵ�

////////////////////////////////////////////////////////////////
//Name:	 UIScrollNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 ��������
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

class  UIScrollNodeLayer: public cocos2d::CCLayer
{
public:
	enum
	{
		KCCScrollNodeLayerStateIdle,    //��ǰScrollLayer���ڿ���״̬
		KCCScrollNodeLayerStateSliding, //��ǰScrollLayer���ڻ���״̬
	};

	//layOut �������
	typedef struct  _nodeData_Tag_
	{
		int   roleIndex_;				 //ģ��ID
		float scaleParam_;				 //�Ŵ�ϵ��
		cocos2d::CCPoint potionParam_;   //�������
	public:
		_nodeData_Tag_()
		{
			roleIndex_=0;
			scaleParam_=0.0f;
			potionParam_=CCPointZero; 
		}
	}NODEDATA,*PNODEDATA;
	 


public:
	UIScrollNodeLayer();
	~UIScrollNodeLayer();
public:
	static  UIScrollNodeLayer *  CreateScrollNodeLayerWithArray(cocos2d::CCArray * pnodeArray,cocos2d::CCPoint=CCPointZero,cocos2d::CCSize contenSize=CCSizeZero);
private:
	bool   InitWithScrollNodeLayerWithArray(cocos2d::CCArray * pnodeArray,cocos2d::CCPoint=CCPointZero,cocos2d::CCSize contenSize=CCSizeZero);
public:
	virtual void  onEnter();
	virtual void  onExit();
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	//virtual	void visit();         //Ĭ�ϵ��û����������
private:
	void  claimTouch(cocos2d::CCTouch * pTouch);
	void  cancelAndStoreTouch(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
private:
	void   initNodeLayOut();
	void   initWaitShowNodeArray();
	void   nextWaitShowNodeArrayForLeft();
	void   nextWaitShowNodeArrayForRight();
	
    void   OnInitShowNode();
	void   OnShowNodeLeft();
	void   OnshowNodeRight();
public:
	int GetMiddleSelectRoleIndex();   //��ȡѡ����������

protected:
	GLfloat  startSwipe_;			             //�û���ʼ����ʱ��Ĵ�����
	GLfloat  minmumTouchLengthToSlider_;         //��С�ƶ�ʹ�� ����
    int      state_;                             //��ǰScroll��״̬
	cocos2d::CCRect  scissorRect_;               //�ü�����
    std::vector<NODEDATA>    nodeLayOutVector_;  //��㲼��vector
	float middleWidth; 
	float midldleHeight;
	int   initWaitShowRoleIndex[SCROLLNODELAYERITEM];   //��ʼ��ʱ�����ʾ�Ľ�ɫ����
	int   nextWaitShowRoleIndex[SCROLLNODELAYERITEM];   //һ��������Ҫ��ʾ�Ľ�ɫ����
	int   middleSelectRoleIndex_;

	unsigned int   childrenCount_;  

private:
    int   touchPriority_;     //���������ȼ���
	bool  isMoveEnable_;      //�����ƶ�ʹ��
};

 
 



#endif



