#ifndef _CMEMORYCACHE_H_
#define _CMEMORYCACHE_H_

#include <map>
#include "CBaseDefine.h"
#include "CSingleton.h"

class CCobraObject;
class CCobraObjectPool;

class CMemoryCache : public CSingleton<CMemoryCache>
{	
public:
	void putExtra(cCobraObjType objType,CCobraObject* obj);
	void putExtra(cCobraObjType objType,int objKey,CCobraObject* obj);
	CCobraObject* getExtra(cCobraObjType objType,int objKey);
	CCobraObjectPool* getCobraObjectPool(cCobraObjType objType);
	void deleteExtra(cCobraObjType objType,CCobraObject* obj);
	void deleteExtra(cCobraObjType objType,int objKey);
	bool containsExtra(cCobraObjType objType,int objKey);
	void clearAllData();
private:
	friend class CSingleton<CMemoryCache>;
	CMemoryCache(void);
	~CMemoryCache(void);
	std::map<int,CCobraObjectPool*> m_MemCache;
};


#define MemoryCacheShare CMemoryCache::getInstance()

#endif //_CMEMORYCACHE_H_