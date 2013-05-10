#ifndef _CCOBRAOBJECTPOOL_H_
#define _CCOBRAOBJECTPOOL_H_

#include "CCobraObject.h"
#include <map>

class CCobraObjectPool : public CCobraObject
{
public:
	CCobraObjectPool(void);
	~CCobraObjectPool(void);
	void addCobraObject(CCobraObject* obj);
	void removeCobraObject(CCobraObject* obj);
	CCobraObject* getCobraObjectById(int objId);
	bool isEmpty();
private:
	std::map<int,CCobraObject*> m_CobraObjectSet;
};

#endif //_CCOBRAOBJECTPOOL_H_