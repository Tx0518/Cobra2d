#include "CCobraObjectPool.h"
#include "CSTLHelper.h"

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

void CCobraObjectPool::addCobraObject( int objKey,CCobraObject* obj )
{
	if(obj == NULL) return;
	m_CobraObjectSet[objKey] = obj;
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

void CCobraObjectPool::removeCobraObject( int objKey )
{
	std::map<int,CCobraObject*>::iterator itor;
	itor = m_CobraObjectSet.find(objKey);
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
	if(containsCobraObject(objId))
		return m_CobraObjectSet[objId];
	return NULL;
}

bool CCobraObjectPool::containsCobraObject( int objId )
{
	return m_CobraObjectSet.find(objId) != m_CobraObjectSet.end();
}

unsigned int CCobraObjectPool::capacity()
{
	return m_CobraObjectSet.size();
}

std::map<int,CCobraObject*> CCobraObjectPool::getObjectPool()
{
	return m_CobraObjectSet;
}

void CCobraObjectPool::clearAll()
{
	stl_helper::clearMap(m_CobraObjectSet);
}

unsigned int CCobraObjectPool::capacityOfKey( int key )
{
	return m_CobraObjectSet.count(key);
}
