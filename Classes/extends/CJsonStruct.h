#ifndef _CJSONSTRUCT_H_
#define _CJSONSTRUCT_H_

#include <string>
#include <map>
#include "json/json.h"
/**
 * @brief 提供一个特殊的结构体类型，可以根据自己的结构成员名称，和JSON字符串进行相互转换
 *
 * 在toJson和fromJson函数中，会将成员名字和地址都存放到map中，再遍历map进行json转换。
 * 目前成员类型只指出string类型
 */

/*
example
struct MyTest : public CJsonStruct
{
    BEGIN_MEMBER_MAP(MyTest)
        ADD_MEMBER_MAP(user_name)
        ADD_MEMBER_MAP(user_info)
    END_MEMBER_MAP()

    std::string user_name;
    std::string user_info;
};

void main()
{
    MyTest json;
    json.fromJson("{\"user_name\":\"test\",\"user_info\":\"good man\"}");
    std::cout << json.user_name << std::endl;
    std::cout << json.user_info << std::endl;
    json.user_name = "TEST";
    json.user_info = "bad man";
    std::string jsonstr = json.toJsonStr();
    std::cout << jsonstr << std::endl;
}
*/

struct CJsonStruct 
{
#define BEGIN_MEMBER_MAP(thisClass) \
	virtual bool DoMemberMap() \
	{ \

#define ADD_MEMBER_MAP(member) \
	member_map_[#member] = &##member;

#define END_MEMBER_MAP() \
	return true;\
}
	BEGIN_MEMBER_MAP(JsonStruct)
	END_MEMBER_MAP()

	Json::Value toJson()
	{
		DoMemberMap();

		Json::Value value;
		for (MEMBER_MAP::iterator it = member_map_.begin(); it != member_map_.end(); ++it)
		{
			std::string member_name = it->first;
			std::string * member = it->second;
			if (member)
				value[member_name] = *member;
		}
		return value;
	}

	std::string toJsonStr()
	{
		Json::Value value = toJson();
		Json::FastWriter writer ;
		std::string ret = writer.write(value);
		return ret;
	}

	bool fromJson(std::string jsonstr)
	{
		Json::Reader reader;
		Json::Value value;

		if (!reader.parse(jsonstr, value))
			return false;

		return fromJson(value);
	}

	bool fromJson(const Json::Value& jsonvalue)
	{
		if (jsonvalue.isNull())
			return false;

		DoMemberMap();

		for (MEMBER_MAP::iterator it = member_map_.begin(); it != member_map_.end(); ++it)
		{
			std::string member_name = it->first;
			std::string * member = it->second;
			if (member && jsonvalue[member_name].isString())
				*member = jsonvalue[member_name].asString();
		}

		return true;
	}

protected:
	typedef std::map<std::string, std::string*> MEMBER_MAP;
	MEMBER_MAP member_map_;
};


#endif	//_CJSONSTRUCT_H_