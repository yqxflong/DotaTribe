//Name��CTipsViewDelegate
//Function��ͳһ��tips����ӿ�
//Written By����ǿ
//
#ifndef __PUBLIC__CTIPSVIEWDELEGATE__
#define __PUBLIC__CTIPSVIEWDELEGATE__

enum{
	kPESEQUIPSUBVIEW,	//Ӣ��װ��
};
//
class CTipsViewDelegate{
public:
	virtual void cancelTipsLayer()=0;
};
#endif