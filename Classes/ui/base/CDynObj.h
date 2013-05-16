#ifndef __DYN_OBJ__
#define __DYN_OBJ__
#include "cocos2d.h"
class CDynObj;
//class RuntimeClassInfo;

struct RuntimeClassInfo
{
	const char* m_lpszClassName;
	int m_nObjectSize;
	CDynObj* (* m_pfnCreateObject)();
	//RuntimeClassInfo* m_pBaseClass;
	RuntimeClassInfo* m_pNextClass;

	static RuntimeClassInfo* pFirstClass;

	CDynObj* createObject();

	static RuntimeClassInfo* load(const char *szClassName);    
};

struct RuntimeClassInfoInitList
{
	RuntimeClassInfoInitList(RuntimeClassInfo* pNewClass)
	{
		pNewClass->m_pNextClass = RuntimeClassInfo::pFirstClass;
		RuntimeClassInfo::pFirstClass = pNewClass;
	}
};

class CDynObj
{
public:
	CDynObj(){};
	virtual ~CDynObj(){};
	virtual RuntimeClassInfo* GetRuntimeClass() const;
	//bool isKindOf(const RuntimeClassInfo* pClass) const;
private:
	CDynObj(const CDynObj& objectSrc);
	void operator=(const CDynObj& objectSrc);
public:
	static RuntimeClassInfo classDynObj;
};


#define RUNTIME_INFO(class_name) ((RuntimeClassInfo*)(&class_name::class##class_name))

#define DECLARE_DYNCREATE(class_name)\
public:\
	static RuntimeClassInfo class##class_name;\
	virtual RuntimeClassInfo* GetRuntimeClass() const;\
	static CDynObj* createObject();


#define IMPLEMENT_DYNCREATE(class_name) \
	CDynObj* class_name::createObject() \
	{ return new class_name; } \
	RuntimeClassInfo class_name::class##class_name = { \
	#class_name, \
	sizeof(class_name), \
	&class_name::createObject, \
	NULL }; \
	static RuntimeClassInfoInitList _init_##class_name(&class_name::class##class_name);   \
	RuntimeClassInfo* class_name::GetRuntimeClass() const \
	{ return RUNTIME_INFO(class_name); } 

#define CreateDynObject(class_name) \
	(RuntimeClassInfo::load(class_name) == NULL ? NULL : RuntimeClassInfo::load(class_name)->createObject())

#endif