#include "CCobraObject.h"

CCobraObject::CCobraObject( void )
{
}

CCobraObject::~CCobraObject( void )
{
}

void CCobraObject::setObjectID(int var)
{
	m_iObjectID = var;
}

int CCobraObject::getObjectID()
{
	return m_iObjectID;
}

void CCobraObject::setObjType(int var)
{
	m_iObjType = var;
}

int CCobraObject::getObjType()
{
	return m_iObjType;
}