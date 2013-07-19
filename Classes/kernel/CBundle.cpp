#include "CBundle.h"
#include "CPropertyHelper.h"
#include "CJsonHelper.h"


CBundle::CBundle( void )
	:m_eBundleDataType(BUNDLE_JSON)
{
}

CBundle::CBundle( cBunldeDataType type )
	:m_eBundleDataType(type)
{

}

CBundle::CBundle(const std::string& jsonStr)
{
	Json::Reader jRead;
	jRead.parse(jsonStr.c_str(),root);
}

CBundle::CBundle(const char* jsonStr)
{
	Json::Reader jRead;
	jRead.parse(jsonStr,root);
}

CBundle::~CBundle( void )
{
	root.clear();
}

int32 CBundle::getJsonInt( const char* tag )
{
	return json_helper::getJsonInt(root,tag);
}

bool CBundle::getJsonBool( const char* tag )
{
	return json_helper::getJsonBoolean(root,tag);
}

std::string CBundle::getJsonString( const char* tag )
{
	return json_helper::getJsonString(root,tag);
}

uInt32 CBundle::getJsonUint( const char* tag )
{
	return json_helper::getJsonUInt(root,tag);
}

float CBundle::getJsonFloat( const char* tag )
{
	return json_helper::getJsonFloat(root,tag);
}

void CBundle::addJsonValue( const char* key,int32 val )
{
	root[key] = Json::Value(val);
}

void CBundle::addJsonValue( const char* key,uInt32 val )
{
	root[key] = Json::Value(val);
}

void CBundle::addJsonValue( const char* key,float val )
{
	root[key] = Json::Value(val);
}


void CBundle::addJsonValue( const char* key,bool val )
{
	root[key] = Json::Value(val);
}

void CBundle::addJsonValue( const char* key,const char* val )
{
	root[key] = Json::Value(val);
}

bool CBundle::isEmpty()
{
	return root.isNull();
}

void CBundle::addStringValue( std::string key,std::string val)
{
	m_pStringSet[key] = val;
}

void CBundle::addStringValue( std::string key,int32 val )
{
	m_pStringSet[key] = CPropertyHelper::intToString(val);
}

void CBundle::addStringValue( std::string key,uInt32 val )
{
	m_pStringSet[key] = CPropertyHelper::uintToString(val);
}

void CBundle::addStringValue( std::string key,float val )
{
	m_pStringSet[key] = CPropertyHelper::floatToString(val);
}


const std::string CBundle::toJsonFormat()
{
	Json::FastWriter fastWrite;
	return fastWrite.write(root);
}

const std::string CBundle::toHttpFormat()
{
	if(m_eBundleDataType != BUNDLE_HTTP) return COBRA_STRING_DEFAULT_VALULE;
	if(m_pStringSet.empty()) return COBRA_STRING_DEFAULT_VALULE;
	std::string http_result_string = COBRA_STRING_DEFAULT_VALULE;
	std::map<std::string,std::string>::const_iterator itor;
	std::string connector = "&";
	std::string lineValue = COBRA_STRING_DEFAULT_VALULE;
	for (itor = m_pStringSet.begin();itor!=m_pStringSet.end();itor++)
	{
		lineValue = itor->first + "=" + itor->second;
		http_result_string += lineValue;
		http_result_string += connector;
	}

	if(http_result_string.compare(COBRA_STRING_DEFAULT_VALULE))
		return http_result_string.substr(0,http_result_string.length()- 1);
	return http_result_string;
}
