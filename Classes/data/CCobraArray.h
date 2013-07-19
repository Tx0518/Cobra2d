#ifndef _CCOBRAARRAY_H_
#define _CCOBRAARRAY_H_

#include "CCobraObject.h"
#include <vector>

class CCobraArray : public CCobraObject
{
public:
	CCobraArray(void);
	virtual ~CCobraArray(void);
	
	void addCobraObject(CCobraObject* obj);
	void removeCobraObject(CCobraObject* obj);
	void removeCobraObjectAtIndex(unsigned int index);
	bool containsCobraObject(CCobraObject* obj);
	void insertCobraObjectIndex(CCobraObject* obj,int index);
	CCobraObject* getCobraObjectAtIndex(int index);
	unsigned int capacity();
	unsigned int indexOf(CCobraObject* obj);
	CCobraObject* lastCobraObject();
	bool isOutBound(unsigned int index);
	bool isEmpty();
	void clearAll();
protected:
	std::vector<CCobraObject*> m_vArray;
	typedef std::vector<CCobraObject*>::iterator pItorSet;
};

#endif //_CCOBRAARRAY_H_