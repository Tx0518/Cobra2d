#include "CGeometry.h"
#include "CPropertyHelper.h"

#include <cstdio>
#include <cstdlib>

#include <cstdio>
#include <sstream>
#include "CStringTokenizer.h"
#ifdef WIN32
#define snprintf _snprintf
#endif

/////////////////////////////////////////////////////////////////////////////
float	CPropertyHelper::stringToFloat(const std::string& str)
{
	float val = 0;
	std::sscanf(str.c_str(), "%g", &val);
	return val;
}

unsigned int	CPropertyHelper::stringToUint(const std::string& str)
{
	unsigned int val = 0;
	std::sscanf(str.c_str(), "%u", &val);
	return val;
}

int		CPropertyHelper::stringToInt(const std::string& str)
{
	int val = 0;
	std::sscanf(str.c_str(), "%d", &val);
	return val;
}

int		CPropertyHelper::stringToIntOX(const std::string& str)
{
	int val = 0;
	std::sscanf(str.c_str(), "%x", &val);
	return val;
}

bool	CPropertyHelper::stringToBool(const std::string& str)
{
	if ((str == "True") || (str == "true"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

char    CPropertyHelper::stringToChar(const std::string& str)
{
	char var = 0;
	std::sscanf(str.c_str(),"%c",&var);
	return var;
}

unsigned char    CPropertyHelper::stringToUnsignedChar(const std::string& str)
{
	unsigned char  var = CPropertyHelper::stringToChar(str);
	return var;
}

long    CPropertyHelper::stringToLong(const std::string& str)
{
	long var = 0;
	std::sscanf(str.c_str(),"%l",&var);
	return var;
}

//////////////////////////////////////////////////////////////////////////

std::string	CPropertyHelper::floatToString(float val)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%g", val);

	return std::string(buff);
}

std::string	CPropertyHelper::floatToString1(float val)
{
	char buff[64];
	snprintf(buff,sizeof(buff),"%.1f",val);

	return std::string(buff);
}
std::string	CPropertyHelper::floatToString2(float val)
{
	char buff[64];
	snprintf(buff,sizeof(buff),"%.2f",val);

	return std::string(buff);
}
std::string	CPropertyHelper::uintToString(unsigned int val)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%u", val);

	return std::string(buff);
}

std::string	CPropertyHelper::intToString(int val)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%d", val);

	return std::string(buff);
}

std::string	CPropertyHelper::oxToString(int val)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "0x%x", val);

	return std::string(buff);
}
std::string	CPropertyHelper::boolToString(bool val)
{
	if (val)
	{
		return std::string("True");
	}
	else
	{
		return std::string("False");
	}
}

std::string  CPropertyHelper::longToString(long val)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%l", val);

	return std::string(buff);
}

std::string  CPropertyHelper::ulongToString(unsigned long val)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%ul", val);

	return std::string(buff);
}

CPoint CPropertyHelper::stringToPoint( const std::string& str )
{
	CPoint ret = PointZero;
	vector<string> vcResult;
	CTokenizer<CIsFromString>::Tokenize(vcResult, str, CIsFromString(","));
	if (vcResult.size() >= 2)
	{
		ret.x = CPropertyHelper::stringToFloat(vcResult.at(0));
		ret.y = CPropertyHelper::stringToFloat(vcResult.at(1));
	}
	else
	{
		;//do nothing
	}
	return ret;
}

CRectange CPropertyHelper::stringToRect( const std::string& str )
{
	CRectange ret = RectZero;
	vector<string> vcResult;
	CTokenizer<CIsFromString>::Tokenize(vcResult, str, CIsFromString(","));
	if (vcResult.size() >= 4)
	{
		ret.origin.x = CPropertyHelper::stringToFloat(vcResult.at(0));
		ret.origin.y = CPropertyHelper::stringToFloat(vcResult.at(1));
		ret.size.width  = CPropertyHelper::stringToFloat(vcResult.at(2));
		ret.size.height = CPropertyHelper::stringToFloat(vcResult.at(3));
	}
	else
	{
		;//do nothing
	}
	return ret;
}

CColor4B CPropertyHelper::stringToColor4B( const std::string& str )
{
	CColor4B ret = CreateCColor(255,255,255,255);
	vector<string> vcResult;
	CTokenizer<CIsFromString>::Tokenize(vcResult, str, CIsFromString(","));
	if (vcResult.size() >= 4)
	{
		ret.r = CPropertyHelper::stringToFloat(vcResult.at(0));
		ret.g = CPropertyHelper::stringToFloat(vcResult.at(1));
		ret.b = CPropertyHelper::stringToFloat(vcResult.at(2));
		ret.a = CPropertyHelper::stringToFloat(vcResult.at(3));
	}
	else
	{
		;//do nothing
	}
	return ret;
}
//CCPoint	CPropertyHelper::stringToPoint(const std::string& str)
//{
//	CCPoint val(0, 0) ;
//	std::sscanf(str.c_str(), " x:%g y:%g", &val.x, &val.y);
//	return val;
//}
//
//CCRect	CPropertyHelper::stringToRect(const std::string& str)
//{
//	CCRect val(0, 0, 0, 0);
//	std::sscanf(str.c_str(), "%g%g%g%g", &val.origin.x, &val.origin.y, &val.size.width, &val.size.height);
//	return val;
//}
//
//std::string	CPropertyHelper::pointToString(const CCPoint& val)
//{
//	char buff[128];
//	snprintf(buff, sizeof(buff), "%g %g", val.x, val.y);
//	return std::string(buff);
//}
//
//std::string	CPropertyHelper::rectToString(const CCRect& val)
//{
//	char buff[256];
//	snprintf(buff, sizeof(buff), "%g %g %g %g",
//		val.origin.x, val.origin.y, val.size.width, val.size.height);
//
//	return std::string(buff);
//}
