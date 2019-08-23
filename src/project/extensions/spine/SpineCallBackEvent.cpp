#include  "SpineCallBackEvent.h"
#include  "extension.h"
USING_NS_CC; 

namespace cocos2d { namespace extension {
   
	static  PLoadSkeletonCallBackHandler   pLoadSkeletonCallBackHandler=NULL;

	void RegisterSkeletonCallBackEventHandler(PLoadSkeletonCallBackHandler handler)
	{
		pLoadSkeletonCallBackHandler = handler;
	}

	bool   CheckSkeletonCallBackHandlerValid()
	{
		if(pLoadSkeletonCallBackHandler==NULL)
			return false;
		return true;
	}

	void   OnSkeletonCallBackEventHandler(std::string skeletonUUID,int animationID,std::vector<PSkeletonCallBack_Node> * pcallBackVec)
	{
		if(pLoadSkeletonCallBackHandler==NULL)
			return ;
		pLoadSkeletonCallBackHandler(skeletonUUID,animationID,pcallBackVec);
	}
}}
