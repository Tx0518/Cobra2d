#include "CMemoryCache.h"
#include "CCobraObject.h"
#include "CCobraObjectPool.h"
#include "CSTLHelper.h"

CMemoryCache::CMemoryCache( void )
{
}

CMemoryCache::~CMemoryCache( void )
{
}

void CMemoryCache::putExtra( cCobraObjType objType,CCobraObject* obj )
{
	CCobraObjectPool* objPool = (CCobraObjectPool*)(m_MemCache[objType]);
	if(objPool == NULL)
	{
		m_MemCache[objType] = new CCobraObjectPool();
		objPool = m_MemCache[objType];
	}
	objPool->addCobraObject(obj);
}

void CMemoryCache::putExtra( cCobraObjType objType,int objKey,CCobraObject* obj )
{
	CCobraObjectPool* objPool = (CCobraObjectPool*)(m_MemCache[objType]);
	objPool->addCobraObject(objKey,obj);
}

CCobraObject* CMemoryCache::getExtra( cCobraObjType objType,int objKey )
{
	CCobraObjectPool* objPool = (CCobraObjectPool*)(m_MemCache[objType]);
	if(objPool == NULL) return NULL;
	return objPool->getCobraObjectById(objKey);
}

void CMemoryCache::deleteExtra( cCobraObjType objType,CCobraObject* obj )
{
	CCobraObjectPool* objPool = (CCobraObjectPool*)(m_MemCache[objType]);
	if(objPool == NULL) return;
	return objPool->removeCobraObject(obj);
}

void CMemoryCache::deleteExtra( cCobraObjType objType,int objKey )
{
	CCobraObjectPool* objPool = (CCobraObjectPool*)(m_MemCache[objType]);
	COBRA_CHECK_NULL(objPool);
	objPool->removeCobraObject(objKey);
}

CCobraObjectPool* CMemoryCache::getCobraObjectPool( cCobraObjType objType )
{
	return (CCobraObjectPool*)(m_MemCache[objType]);
}

bool CMemoryCache::containsExtra( cCobraObjType objType,int objKey )
{
	CCobraObjectPool* objPool = (CCobraObjectPool*)(m_MemCache[objType]);
	if(objPool == NULL) return false;
	return objPool->containsCobraObject(objKey);
}


void CMemoryCache::clearAllData()
{
	stl_helper::clearMap(m_MemCache);
}
