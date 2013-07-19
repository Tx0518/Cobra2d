#ifndef _CCOBRAOBJECT_H_
#define _CCOBRAOBJECT_H_

#include "CMarcos.h"
#include "CBaseDefine.h"
#include "CPlatFormDefine.h"
#include <string>

/*
	CCobraObject
*/
class CCobraObject
{
public:
	CCobraObject(void);
	virtual ~CCobraObject(void);
	COBRA_CREATE_PROPERTY(int,m_iObjectID,ObjectID)
	COBRA_CREATE_PROPERTY(cCobraObjType,m_iObjType,ObjType)
	COBRA_CREATE_PROPERTY_BY_REF(std::string,m_strComName,ComponentName)
};


typedef void (CCobraObject::*COBRA_SELECTOR_CALLFUN)(CCobraObject*);
#define cobra_callBack(_SELECTOR)  (COBRA_SELECTOR_CALLFUN)(&_SELECTOR)

#endif //_CCOBRAOBJECT_H_