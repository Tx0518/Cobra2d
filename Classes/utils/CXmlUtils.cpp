#include "CXmlUtils.h"


static const int INT_32_TYPE = 1;
static const int UNSIGNED_INT_32_TYPE = 2;
static const int INT_64_TYPE = 3;
static const int UNSIGNED_INT_64_TYPE = 4;
static const int FLOAT_TYPE = 5;

#define FLOAT_ERROR  99999.9f;
#define INT_ERROR		 -999999;
#define STRING_ERROR	""

namespace Xml_Utils
{

	bool getElementNumber(const pugi::xml_node curEle, int nNumType, void* pOutNumber)
	{
		if( pOutNumber)
		{
			const char* szValue = curEle.value();
			if(szValue)
			{
				if(INT_32_TYPE == nNumType)
					sscanf(szValue, "%d", (int*)pOutNumber);
				else if(UNSIGNED_INT_32_TYPE == nNumType)
					sscanf(szValue, "%u", (unsigned int*)pOutNumber);
				else if(INT_64_TYPE == nNumType)
					sscanf(szValue, "%lld", (long long*)pOutNumber);
				else if(UNSIGNED_INT_64_TYPE == nNumType)
					sscanf(szValue, "%llu", (unsigned long long*)pOutNumber);
				else
					sscanf(szValue, "%f", (float*)pOutNumber);
				return true;
			}
		}
		return false;
	}

	bool getChildrenElementNumber(const pugi::xml_node parentEle, const char* szTag,  int nNumType, void* pOutNumber)
	{
		if( szTag && pOutNumber)
		{
			const pugi::xml_node childEle = parentEle.child(szTag);
			if(childEle)
			{
				const char* szValue = childEle.value();
				if(szValue)
				{
					if(INT_32_TYPE == nNumType)
						sscanf(szValue, "%d", (int*)pOutNumber);
					else if(UNSIGNED_INT_32_TYPE == nNumType)
						sscanf(szValue, "%u", (unsigned int*)pOutNumber);
					else if(INT_64_TYPE == nNumType)
						sscanf(szValue, "%lld", (long long*)pOutNumber);
					else if(UNSIGNED_INT_64_TYPE == nNumType)
						sscanf(szValue, "%llu", (unsigned long long*)pOutNumber);
					else
						sscanf(szValue, "%f", (float*)pOutNumber);
					return true;
				}
			}
			return false;
		}
		return false;
	}

	bool getAttributeNumber(const pugi::xml_node curEle, const char* szAttr, int nNumType, void* pOutNumber)
	{
		if(szAttr && pOutNumber)
		{
			const char* szValue = curEle.attribute(szAttr).value();
			if(szValue)
			{
				if(INT_32_TYPE == nNumType)
					sscanf(szValue, "%d", (int*)pOutNumber);
				else if(UNSIGNED_INT_32_TYPE == nNumType)
					sscanf(szValue, "%u", (unsigned int*)pOutNumber);
				else if(INT_64_TYPE == nNumType)
					sscanf(szValue, "%lld", (long long*)pOutNumber);
				else if(UNSIGNED_INT_64_TYPE == nNumType)
					sscanf(szValue, "%llu", (unsigned long long*)pOutNumber);
				else
					sscanf(szValue, "%f", (float*)pOutNumber);
				return true;
			}
			return false;
		}
		return false;
	}

	std::string getElementText( const pugi::xml_node node )
	{
		return std::string(node.child_value());
	}

	int getElementInt( const pugi::xml_node node )
	{
		int iIntNum = 0;
		if(getElementNumber(node, INT_32_TYPE, &iIntNum))
			return iIntNum;
		return INT_ERROR;
	}

	float getElementFloat( const pugi::xml_node node )
	{
		float fNum = 0;
		if(getElementNumber(node, FLOAT_TYPE, &fNum))
			return fNum;
		return FLOAT_ERROR;
	}
	
	std::string getAttributeText( const pugi::xml_node node,const char* attrName )
	{
		if(attrName == NULL) return STRING_ERROR;
		return node.attribute(attrName).as_string();
	}

	int getAttributeInt( const pugi::xml_node node,const char* attrName )
	{
		int iIntNum = 0;
		if( getAttributeNumber(node, attrName, INT_32_TYPE, &iIntNum) )
			return iIntNum;
		return INT_ERROR;
	}
	
	float getAttributeFloat( const pugi::xml_node node,const char* attrName )
	{
		float fNum = 0;
		if(getAttributeNumber(node, attrName, FLOAT_TYPE, &fNum))
			return fNum;
		return FLOAT_ERROR;
	}
	
	std::string getChildrenElementText( const pugi::xml_node node,const char* szTag )
	{
		if(szTag == NULL) return STRING_ERROR;
		return node.child_value(szTag);
	}

	int getChildrenElementInt( const pugi::xml_node node,const char* szTag )
	{
		int iIntNum = 0;
		if(getChildrenElementNumber(node, szTag, INT_32_TYPE, &iIntNum))
			return iIntNum;
		return INT_ERROR;
	}
}