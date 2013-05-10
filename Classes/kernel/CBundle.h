#ifndef _CBUNDLE_H_
#define _CBUNDLE_H_

#include "CCobraObject.h"
#include <map>
#include <string>

template<typename T>
class CContentValue
{
public:
	CContentValue(T obj,int Type)
		:data(obj),
		dataObjType(Type){}
	virtual ~CContentValue(){}
	T getData()	{	return data;}
	int getType() {	return dataObjType;	}
protected:
	T data;
	int dataObjType;
};

/*
	CBundle
*/
class CBundle : public CCobraObject
{
public:
	CBundle(void);
	CBundle& operator=(const CBundle& other);
	~CBundle(void);
private:
	std::map<std::string,std::string> m_Parcel;
};

#endif	//_CBUNDLE_H_