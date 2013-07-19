#ifndef __PROPERTY_HELPER_H__
#define __PROPERTY_HELPER_H__
#include <string>
#include "CMarcos.h"
#include "CGeometry.h"
class CPropertyHelper
{
public:
	static	float	stringToFloat(const std::string& str);
	//static  double  stringToDouble(const std::string& str);
	static	unsigned int	stringToUint(const std::string& str);
	static	int		stringToInt(const std::string& str);

	//16进制
	static	int		stringToIntOX(const std::string& str);
	static	bool	stringToBool(const std::string& str);
	static  char    stringToChar(const std::string& str);
	static  unsigned char    stringToUnsignedChar(const std::string& str);
	static  long    stringToLong(const std::string& str);
	//////////////////////////////////////////////////////////////////////////

	static	CPoint	  stringToPoint(const std::string& str);
	static	CRectange stringToRect(const std::string& str);
	static  CColor4B  stringToColor4B(const std::string& str);
	//////////////////////////////////////////////////////////////////////////
	static std::string	floatToString(float val);
	static std::string	floatToString1(float val);//保留1位小数
	static std::string	floatToString2(float val);//保留2位小数
	static std::string	uintToString(unsigned int val);
	static std::string	intToString(int val);
	static std::string  oxToString(int val);
	static std::string	boolToString(bool val);
	static std::string  longToString(long val);
	static std::string  ulongToString(unsigned long val);
	//static std::string	pointToString(const CCPoint& val);
	//static std::string	rectToString(const CCRect& val);
};
#endif//__PROPERTY_HELPER_H__