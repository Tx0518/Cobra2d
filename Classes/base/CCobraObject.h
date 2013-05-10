#ifndef _CCOBRAOBJECT_H_
#define _CCOBRAOBJECT_H_

#include "CMarcos.h"

class CCobraObject
{
public:
	CCobraObject(void);
	virtual ~CCobraObject(void);

	COBRA_CREATE_PROPERTY(int,m_iObjectID,ObjectID)
	COBRA_CREATE_PROPERTY(int,m_iObjType,ObjType)
};


#endif //_CCOBRAOBJECT_H_