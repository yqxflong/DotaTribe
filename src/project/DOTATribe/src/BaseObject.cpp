//Name£ºAthleticsUIManager
//Function£ºÕ½¶·Âß¼­¶ÔÏó
//Author:	Johny

#include "../include/BaseObject.h"

BaseObject::BaseObject()
{
   objectType_=UNKOWN_OBJECT_TYPE;
   m_LogicTickCount_=0;
   isValid_=true;
   objectSubID_=0;
}

BaseObject::~BaseObject()
{
    objectType_=UNKOWN_OBJECT_TYPE;
}

int BaseObject::GetObjectType()
{
	return objectType_;
}
 
void   BaseObject::SetObjectType(int ObjectType)
{
   if(objectType_!=ObjectType)
   {
	   objectType_=ObjectType;
   }
}

void BaseObject::Tick()
{
	++m_LogicTickCount_;
}

void BaseObject::SetSpeedScale(float speedScale)
{
	//to do
}
 
bool   BaseObject::IsValid()
{
	return isValid_;
}

void   BaseObject::SetIsValid(bool isValid)
{
    if(isValid_!=isValid)
	{
		isValid_=isValid;
	}
}

void   BaseObject::SetSubObjectID(int subObjectId)
{
    if(objectSubID_!=subObjectId)
	{
		objectSubID_=subObjectId;
	}
}


int    BaseObject::GetSubObjectID()
{
   return  objectSubID_;
}

 