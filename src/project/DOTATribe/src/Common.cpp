#include "../include/Common.h"
#include <climits> 
#include <include/common/Declare.h>
using  namespace  cobra_win;


float SquaredLength(cocos2d::CCPoint x1a)
{
	return x1a.x*x1a.x + x1a.y*x1a.y;
}

float Length(cocos2d::CCPoint x1a)
{
	return sqrt(x1a.x*x1a.x + x1a.y*x1a.y);
}

float Normalise(cocos2d::CCPoint& x1a)
{
	float fLength = sqrt( x1a.x*x1a.x + x1a.y*x1a.y);
	if (fLength > 1e-08)
	{
		float fInvLength = 1.0f/fLength;
		x1a.x *= fInvLength;
		x1a.y *= fInvLength;
	}

	return fLength;
}

bool IsCirlceCollisionRect(float circleXPos, float circleYPos, float radius, float rectX, float rectY, float rectW, float rectH)
{
	float arcR  = radius;
	float arcOx = circleXPos;
	float arcOy = circleYPos;

	//分别判断矩形4个顶点与圆心的距离是否<=圆半径；如果<=，说明碰撞成功   
	if(((rectX-arcOx) * (rectX-arcOx) + (rectY-arcOy) * (rectY-arcOy)) <= arcR * arcR)   
		return true;   
	if(((rectX+rectW-arcOx) * (rectX+rectW-arcOx) + (rectY-arcOy) * (rectY-arcOy)) <= arcR * arcR)   
		return true;   
	if(((rectX-arcOx) * (rectX-arcOx) + (rectY+rectH-arcOy) * (rectY+rectH-arcOy)) <= arcR * arcR)   
		return true;   
	if(((rectX+rectW-arcOx) * (rectX+rectW-arcOx) + (rectY+rectH-arcOy) * (rectY+rectH-arcOy)) <= arcR * arcR)   
		return true;

	//判断当圆心的Y坐标进入矩形内时X的位置，如果X在(rectX-arcR)到(rectX+rectW+arcR)这个范围内，则碰撞成功   
	float minDisX = 0;   
	if(arcOy >= rectY && arcOy <= rectY + rectH)
	{   
		if(arcOx < rectX)   
			minDisX = rectX - arcOx;   
		else if(arcOx > rectX + rectW)   
			minDisX = arcOx - rectX - rectW;   
		else    
			return true;   
		if(minDisX <= arcR)   
			return true;   
	}

	//判断当圆心的X坐标进入矩形内时Y的位置，如果X在(rectY-arcR)到(rectY+rectH+arcR)这个范围内，则碰撞成功
	float minDisY = 0;   
	if(arcOx >= rectX && arcOx <= rectX + rectW)
	{   
		if(arcOy < rectY)   
			minDisY = rectY - arcOy;   
		else if(arcOy > rectY + rectH)   
			minDisY = arcOy - rectY - rectH;   
		else  
			return true;   
		if(minDisY <= arcR)   
			return true;   
	}

	return false; 
}

bool IsLineCollisionLine(cocos2d::CCPoint p1, cocos2d::CCPoint p2, cocos2d::CCPoint p3, cocos2d::CCPoint p4)
{
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) 
		return false;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

	// Check if the x and y coordinates are within both lines
	if ( x < MIN(x1, x2) || x > MAX(x1, x2) ||
		x < MIN(x3, x4) || x > MAX(x3, x4) )
		return false;

	if ( y < MIN(y1, y2) || y > MAX(y1, y2) ||
		y < MIN(y3, y4) || y > MAX(y3, y4) ) 
		return false;

	return true;
}

static float mult(cocos2d::CCPoint a, cocos2d::CCPoint b, cocos2d::CCPoint c)
{
	return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}

bool IsLineCollisionLine2(cocos2d::CCPoint aa, cocos2d::CCPoint bb, cocos2d::CCPoint cc, cocos2d::CCPoint dd)
{
	if ( MAX(aa.x, bb.x)<MIN(cc.x, dd.x) )
		return false;

	if ( MAX(aa.y, bb.y)<MIN(cc.y, dd.y) )
		return false;

	if ( MAX(cc.x, dd.x)<MIN(aa.x, bb.x) )
		return false;

	if ( MAX(cc.y, dd.y)<MIN(aa.y, bb.y) )
		return false;

	if (mult(cc, bb, aa)*mult(bb, dd, aa)<0.0001f)
		return false;

	if (mult(aa, dd, cc)*mult(dd, bb, cc)<0.0001f)
		return false;

	return true;
}

bool IsLineCollisionRect(cocos2d::CCPoint lineStartPoint, cocos2d::CCPoint lineEndPoint, cocos2d::CCPoint rectleftBottomPoint, float width, float height)
{
	// 因为这个方法专门进行射线光束的碰撞检测，所以暂不进行线段在矩形内的碰撞检测
	cocos2d::CCPoint leftLineStartPoint = rectleftBottomPoint;
	cocos2d::CCPoint leftLineEndPoint   = cocos2d::CCPoint(leftLineStartPoint.x, leftLineStartPoint.y+height);

	cocos2d::CCPoint rightLineStartPoint= cocos2d::CCPoint(leftLineStartPoint.x+width, leftLineStartPoint.y);
	cocos2d::CCPoint rightLineEndPoint  = cocos2d::CCPoint(leftLineStartPoint.x+width, leftLineStartPoint.y+height);

	cocos2d::CCPoint topLineStartPoint  = cocos2d::CCPoint(leftLineStartPoint.x, leftLineStartPoint.y+height);
	cocos2d::CCPoint topLineEndPoint    = cocos2d::CCPoint(leftLineStartPoint.x+width, leftLineStartPoint.y+height);

	cocos2d::CCPoint bottomLineStartPoint= cocos2d::CCPoint(leftLineStartPoint.x, leftLineStartPoint.y);
	cocos2d::CCPoint bottomLineEndPoint  = cocos2d::CCPoint(leftLineStartPoint.x+width, leftLineStartPoint.y);
	
	cocos2d::CCPoint leftBottomLineStartPoint= rectleftBottomPoint;
	cocos2d::CCPoint rightTopLineEndPoint    = rightLineEndPoint;

	cocos2d::CCPoint leftTopLineStartPoint   = leftLineEndPoint;
	cocos2d::CCPoint rightBottomLineEndPoint = rightLineStartPoint;


	do 
	{
		if (IsLineCollisionLine2(lineStartPoint, lineEndPoint, leftLineStartPoint, leftLineEndPoint))
			break;

		if (IsLineCollisionLine2(lineStartPoint, lineEndPoint, rightLineStartPoint, rightLineEndPoint))
			break;

		if (IsLineCollisionLine2(lineStartPoint, lineEndPoint, topLineStartPoint, topLineEndPoint))
			break;

		if (IsLineCollisionLine2(lineStartPoint, lineEndPoint, bottomLineStartPoint, bottomLineEndPoint))
			break;

		if (IsLineCollisionLine2(lineStartPoint, lineEndPoint, leftBottomLineStartPoint, rightTopLineEndPoint))
			break;

		if (IsLineCollisionLine2(lineStartPoint, lineEndPoint, leftTopLineStartPoint, rightBottomLineEndPoint))
			break;

		return false;
	} 
	while (false);

	return true;
}

static  bool  IsRectCollisionRect2(cocos2d::CCPoint rect1CenterPoint, float rect1W, float rect1H, cocos2d::CCPoint rect2CenterPoint, float rect2W, float rect2H)
{
	cocos2d::CCPoint leftTopPoint     = cocos2d::CCPoint(rect2CenterPoint.x-rect2W/2.0f, rect2CenterPoint.y+rect2H/2.0f);
	cocos2d::CCPoint leftBottomPoint  = cocos2d::CCPoint(rect2CenterPoint.x-rect2W/2.0f, rect2CenterPoint.y-rect2H/2.0f);
	cocos2d::CCPoint rightTopPoint    = cocos2d::CCPoint(rect2CenterPoint.x+rect2W/2.0f, rect2CenterPoint.y+rect2H/2.0f);
	cocos2d::CCPoint rightBottomPoint = cocos2d::CCPoint(rect2CenterPoint.x+rect2W/2.0f, rect2CenterPoint.y-rect2H/2.0f);

	if ( (leftTopPoint.x>(rect1CenterPoint.x-rect1W/2.0f)) && (leftTopPoint.x<(rect1CenterPoint.x+rect1W/2.0f)) 
		&& (leftTopPoint.y>(rect1CenterPoint.y-rect1H/2.0f)) && (leftTopPoint.y<(rect1CenterPoint.y+rect1H/2.0f)))
		return true;

	if ( (leftBottomPoint.x>(rect1CenterPoint.x-rect1W/2.0f)) && (leftBottomPoint.x<(rect1CenterPoint.x+rect1W/2.0f)) 
		&& (leftBottomPoint.y>(rect1CenterPoint.y-rect1H/2.0f)) && (leftBottomPoint.y<(rect1CenterPoint.y+rect1H/2.0f)))
		return true;

	if ( (rightTopPoint.x>(rect1CenterPoint.x-rect1W/2.0f)) && (rightTopPoint.x<(rect1CenterPoint.x+rect1W/2.0f)) 
		&& (rightTopPoint.y>(rect1CenterPoint.y-rect1H/2.0f)) && (rightTopPoint.y<(rect1CenterPoint.y+rect1H/2.0f)))
		return true;

	if ( (rightBottomPoint.x>(rect1CenterPoint.x-rect1W/2.0f)) && (rightBottomPoint.x<(rect1CenterPoint.x+rect1W/2.0f)) 
		&& (rightBottomPoint.y>(rect1CenterPoint.y-rect1H/2.0f)) && (rightBottomPoint.y<(rect1CenterPoint.y+rect1H/2.0f)))
		return true;

	return false;
}

bool  IsRectCollisionRect(cocos2d::CCPoint rect1CenterPoint, float rect1W, float rect1H, cocos2d::CCPoint rect2CenterPoint, float rect2W, float rect2H)
{
	if (IsRectCollisionRect2(rect1CenterPoint, rect1W, rect1H, rect2CenterPoint, rect2W, rect2H))
		return true;
	
	if (IsRectCollisionRect2(rect2CenterPoint, rect2W, rect2H, rect1CenterPoint, rect1W, rect1H))
		return true;

	return false;
}

std::list<std::string> parser_utf8_string(std::string text)
{
	std::list<std::string> temp;

	do 
	{
		if (text.length() <= 0)
			break;

		std::string::const_iterator begin = text.begin();
		std::string::const_iterator end   = text.end();
		while (begin != end)
		{
			unsigned char c = *begin;
			int n = 0;

			if ((c & 0x80) == 0)    
				n = 1;
			else if ((c & 0xE0) == 0xC0) 
				n = 2;
			else if ((c & 0xF0) == 0xE0) 
				n = 3;
			else if ((c & 0xF8) == 0xF0) 
				n = 4;
			else if ((c & 0xFC) == 0xF8) 
				n = 5;
			else if ((c & 0xFE) == 0xFC) 
				n = 6;
			else 
				break;

			if (end - begin < n) 
				break;

			std::string substring;
			substring += *begin;

			bool isError = false;
			for (int i=1; i<n; ++i)
			{
				if ((begin[i] & 0xC0) != 0x80) 
				{
					isError = true;
					break;
				}

				substring += begin[i];
			}

			if (isError)
				break;

			temp.push_back(substring);
			begin += n;
		}
	} 
	while (false);

	return temp;
}



std::string GetPngPathFromPlist(std::string plistPath)
{
	if(!plistPath.empty())
	{
		size_t startPos = plistPath.find_last_of("."); 
		if(startPos>SHRT_MAX)
			return "";
		plistPath = plistPath.erase(startPos);
		// append .png
		plistPath = plistPath.append(".png");
		return plistPath;
	}
	return "";
}

//获取png对应的plist //仅限png和plist前缀相同
std::string GetPlistPathFromPng(std::string pngPath)
{
	if(!pngPath.empty())
	{
		size_t startPos = pngPath.find_last_of("."); 
		if(startPos>SHRT_MAX)
			return "";
		pngPath = pngPath.erase(startPos);
		// append .plist
		pngPath = pngPath.append(".plist");
		return pngPath;
	}
	return "";
}

//获得png或者plist的AnimationName
std::string GetAnimationNameFromPlistOrPng(std::string fileName)
{
	if(!fileName.empty())
	{
		size_t startPos = fileName.find_last_of("."); 
		if(startPos>SHRT_MAX)
			return ""; 
		//@删除startPos之后的string
		fileName = fileName.erase(startPos);

		startPos = fileName.find_last_of("/"); 
		if(startPos>SHRT_MAX)
			return "";
		//@取startPos+1之后的string
		fileName=fileName.substr(startPos+1,fileName.length()-startPos);
		 
		return fileName;
	}
	return "";
}

FILETYPE  GetFileTypeFromName(std::string fileName)
{  
	if(!fileName.empty())
	{
		do 
		{
			if(std::string::npos!=fileName.find("plist"))
			{
				return  _PLIST_FILE_TYPE_;
			}
			else if(std::string::npos!=fileName.find("png"))
			{
				return _IMAGE_FILE_TYPE_;
			}
			else if(std::string::npos!=fileName.find("json"))
			{
				return  _JSON_FILE_TYPE_;
			}
			else if(std::string::npos!=fileName.find("atlas"))
			{
				return  _ATLAS_FILE_TYPE_;
			} 
			break;
		} while (false);
	}
	return  _UNKONW_FILE_TYPE_;
}

