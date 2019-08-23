#ifndef  _DOTATRIBE_COMMON_H_
#define  _DOTATRIBE_COMMON_H_

//公共物理检测组件

#include <cocos2d.h>
#include <string>
#include <list>

// PI
#define  _PI (3.14159f)
// 重力加速度系数
#define  _G  (9.8f)

// 计算平方长度
extern  float  SquaredLength(cocos2d::CCPoint x1a);

// 计算长度
extern  float  Length(cocos2d::CCPoint x1a);

// 归一
extern  float  Normalise(cocos2d::CCPoint& x1a);

// 矩形和圆形碰撞检测
extern  bool  IsCirlceCollisionRect(float circleXPos, float circleYPos, float radius, float rectX, float rectY, float rectW, float rectH);

// 线段和线段碰撞检测
extern  bool  IsLineCollisionLine(cocos2d::CCPoint line1StartPoint, cocos2d::CCPoint line1EndPoint, cocos2d::CCPoint line2StartPoint, cocos2d::CCPoint line2EndPoint);

// 线段和矩形碰撞检测
extern  bool  IsLineCollisionRect(cocos2d::CCPoint lineStartPoint, cocos2d::CCPoint lineEndPoint, cocos2d::CCPoint rectleftBottomPoint, float width, float height);

// 矩形和矩形碰撞检测
extern  bool  IsRectCollisionRect(cocos2d::CCPoint rect1CenterPoint, float rect1W, float rect1H, cocos2d::CCPoint rect2CenterPoint, float rect2W, float rect2H);


// 解析指定utf8字符串，返回单个字符列表
std::list<std::string> parser_utf8_string(std::string text);

//获得Plist对应的png
std::string GetPngPathFromPlist(std::string plistPath);

//获取png对应的plist //仅限png和plist前缀相同
std::string GetPlistPathFromPng(std::string pngPath);

//获得png或者plist的AnimationName
std::string GetAnimationNameFromPlistOrPng(std::string fileName);

enum  FILETYPE
{
	_UNKONW_FILE_TYPE_,    //未知文件类型
	_PLIST_FILE_TYPE_,	   //Plist文件
	_IMAGE_FILE_TYPE_,     //图片文件
	_JSON_FILE_TYPE_,	   //JSON文件
	_ATLAS_FILE_TYPE_,     //纹理配置文件
};

FILETYPE  GetFileTypeFromName(std::string fileName);

 

#endif
