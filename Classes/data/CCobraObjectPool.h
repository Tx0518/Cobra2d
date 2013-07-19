#ifndef _CCOBRAOBJECTPOOL_H_
#define _CCOBRAOBJECTPOOL_H_

#include "CCobraObject.h"
#include <map>

class CCobraObjectPool : public CCobraObject
{
public:
	CCobraObjectPool(void);
	~CCobraObjectPool(void);
	void addCobraObject(int objKey,CCobraObject* obj);
	void addCobraObject(CCobraObject* obj);
	void removeCobraObject(CCobraObject* obj);
	void removeCobraObject(int objKey);
	CCobraObject* getCobraObjectById(int objId);
	bool containsCobraObject(int objId);
	std::map<int,CCobraObject*> getObjectPool();
	bool isEmpty();
	unsigned int capacity();
	unsigned int capacityOfKey(int key);
	void clearAll();
private:
	std::map<int,CCobraObject*> m_CobraObjectSet;
};

#endif //_CCOBRAOBJECTPOOL_H_