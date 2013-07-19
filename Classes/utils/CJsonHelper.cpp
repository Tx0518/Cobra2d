#include "CJsonHelper.h"
#include <stdlib.h>

namespace json_helper
{
	
	int32 getJsonInt( const Json::Value& json_object,const char* tag )
	{
		const Json::Value& value = json_object[tag];
		if(value.isNull() || !(value.isInt()) || value.isUInt())
			return 0;
		return value.asInt();
	}

	uInt32 getJsonUInt( const Json::Value& json_object,const char* tag )
	{
		const Json::Value& value = json_object[tag];
		if(value.isNull() || !(value.isInt()) || value.isUInt())
			return 0;
		return value.asUInt();
	}


	float getJsonFloat( const Json::Value& json_object,const char* tag )
	{
		const Json::Value& value = json_object[tag];
		if(value.isNull())
			return 0.0f;
		return value.asDouble();
	}

	std::string getJsonString( const Json::Value& json_object,const char* tag )
	{
		const Json::Value& value = json_object[tag];
		if(value.isNull() || !value.isString())
			return "";
		return value.asString();
	}

	bool getJsonBoolean( const Json::Value& json_object,const char* tag,bool _default /*= false*/ )
	{
		const Json::Value& value = json_object[tag];
		if(value.isNull() || !value.isBool())
			return _default;
		return value.asBool();
	}

	int32 getJsonIntEx( const Json::Value& json_object,const char* tag )
	{
		const Json::Value& value = json_object[tag];
		if(value.isNull())
			return 0;
		if(value.isInt() || value.isUInt())
			return value.asUInt();
		if(value.isString())
		{
			int32 nVal = atoi((value.asString()).c_str());
			return nVal;
		}
		return 0;
	}



}