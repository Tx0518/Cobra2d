#include "CDynObj.h"
RuntimeClassInfo* RuntimeClassInfo::pFirstClass = NULL;

CDynObj* RuntimeClassInfo::createObject()
{
	if (m_pfnCreateObject == NULL)
	{
		return NULL;
	}

	CDynObj* pObject = (*m_pfnCreateObject)();
	{
		return pObject;
	}
}


RuntimeClassInfo* RuntimeClassInfo::load(const char *szClassName)
{
	RuntimeClassInfo* pClass;

	for (pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass)
	{
		if (strcmp(szClassName, pClass->m_lpszClassName) == 0)
			return pClass;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
RuntimeClassInfo CDynObj::classDynObj =
{
	(char*)"CDynObj", 
	sizeof(CDynObj), 
	NULL,  
	NULL 
};


static RuntimeClassInfoInitList _init_DynObj(&CDynObj::classDynObj);


RuntimeClassInfo* CDynObj::GetRuntimeClass() const
{
	return &CDynObj::classDynObj;
}



#if 0
bool CDynObj::isKindOf(const RuntimeClassInfo* pClass) const
{
	RuntimeClassInfo* pClassThis = GetRuntimeClass();
	while (pClassThis != NULL)
	{
		if (pClassThis == pClass)
		{
			return true;
		}
		pClassThis = pClassThis->m_pBaseClass;
	}
	return false;
}
#endif
