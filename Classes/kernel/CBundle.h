#ifndef _CBUNDLE_H_
#define _CBUNDLE_H_

#include "CCobraObject.h"
#include "json.h"
#include "CBaseTypes.h"

typedef enum
{
	BUNDLE_JSON,
	BUNDLE_HTTP,
}cBunldeDataType;

/*
	CBundle
	TODO:json 格式数据
*/
class CBundle : public CCobraObject
{
public:
	CBundle(void);
	CBundle(const char* jsonStr);
	CBundle(const std::string& jsonStr);
	CBundle(cBunldeDataType type);
	virtual ~CBundle(void);
	void addJsonValue(const char* key,int32 val);
	void addJsonValue(const char* key,uInt32 val);
	void addJsonValue(const char* key,float val);
	void addJsonValue(const char* key,bool val);
	void addJsonValue(const char* key,const char* val);
	
	int32 getJsonInt(const char* tag);
	bool getJsonBool(const char* tag);
	std::string getJsonString(const char* tag);
	uInt32 getJsonUint(const char* tag);
	float getJsonFloat(const char* tag);

	bool isEmpty();

	void addStringValue(std::string key,std::string val);
	void addStringValue(std::string key,int32 val);
	void addStringValue(std::string key,uInt32 val);
	void addStringValue(std::string key,float val);

	COBRA_CREATE_PROPERTY(cBunldeDataType,m_eBundleDataType,DataType)

	const std::string toJsonFormat();
	const std::string toHttpFormat();
private:
	Json::Value root;
	std::map<std::string,std::string> m_pStringSet;
};

#endif	//_CBUNDLE_H_