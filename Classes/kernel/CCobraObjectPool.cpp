#include "CCobraObjectPool.h"

CCobraObjectPool::CCobraObjectPool( void )
{
}

CCobraObjectPool::~CCobraObjectPool( void )
{
	m_CobraObjectSet.clear();
}

void CCobraObjectPool::addCobraObject( CCobraObject* obj )
{
	if(obj == NULL) return;
	m_CobraObjectSet[obj->getObjectID()] = obj;
}

void CCobraObjectPool::removeCobraObject( CCobraObject* obj )
{
	if(obj == NULL) return;
	std::map<int,CCobraObject*>::iterator itor;
	itor = m_CobraObjectSet.find(obj->getObjectID());
	if(itor != m_CobraObjectSet.end())
	{
		COBRA_SAFE_DELETE(itor->second);
		m_CobraObjectSet.erase(itor);
	}
}

bool CCobraObjectPool::isEmpty()
{
	return m_CobraObjectSet.empty();
}

CCobraObject* CCobraObjectPool::getCobraObjectById( int objId )
{
	if(m_CobraObjectSet.find(objId) != m_CobraObjectSet.end())
		return m_CobraObjectSet[objId];
	return NULL;
}
