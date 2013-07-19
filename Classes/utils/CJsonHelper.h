#ifndef __CJSONHELPER_H_
#define __CJSONHELPER_H_

#include "json.h"
#include "CBaseTypes.h"
#include <string>

namespace json_helper
{
	int32 getJsonInt(const Json::Value& json_object,const char* tag);
	uInt32 getJsonUInt(const Json::Value& json_object,const char* tag);
	float getJsonFloat(const Json::Value& json_object,const char* tag);
	std::string getJsonString(const Json::Value& json_object,const char* tag);
	bool getJsonBoolean(const Json::Value& json_object,const char* tag,bool _default = false);
	int32 getJsonIntEx(const Json::Value& json_object,const char* tag);
}

#endif	//__CJSONHELPER_H_