//Name：CTipsViewDelegate
//Function：统一的tips界面接口
//Written By：尹强
//
#ifndef __PUBLIC__CTIPSVIEWDELEGATE__
#define __PUBLIC__CTIPSVIEWDELEGATE__

enum{
	kPESEQUIPSUBVIEW,	//英雄装备
};
//
class CTipsViewDelegate{
public:
	virtual void cancelTipsLayer()=0;
};
#endif