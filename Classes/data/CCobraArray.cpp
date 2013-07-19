#include "CCobraArray.h"
#include "CSTLHelper.h"


CCobraArray::CCobraArray( void )
{
}

CCobraArray::~CCobraArray( void )
{
}

void CCobraArray::addCobraObject( CCobraObject* obj )
{
	if(!containsCobraObject(obj))
		m_vArray.push_back(obj);
}

void CCobraArray::removeCobraObject( CCobraObject* obj )
{
	pItorSet itor;
	for (itor =m_vArray.begin();itor!=m_vArray.end();itor++)
	{
		if((CCobraObject*)(*itor) == obj)
		{
			delete (*itor);
			m_vArray.erase(itor);
		}
	}
}

void CCobraArray::removeCobraObjectAtIndex(unsigned int index )
{
	if(index <=0 || index >= capacity()) return;
	int count = 0;
	pItorSet itor;
	for (itor = m_vArray.begin();itor!=m_vArray.end();itor++)
	{
		if(count == index)
		{
			delete (*itor);
			m_vArray.erase(itor);
		}
		count++;
	}
}

void CCobraArray::insertCobraObjectIndex( CCobraObject* obj,int index )
{
	if(!isOutBound(index))
	{
		int count = 0;
		pItorSet itor;
		for (itor = m_vArray.begin();itor!=m_vArray.end();itor++)
		{
			if(count == index)
			{
				m_vArray.insert(itor,obj);
				return;
			}
			count++;
		}
	}
}


CCobraObject* CCobraArray::getCobraObjectAtIndex( int index )
{
	if(!isOutBound(index))
	{
		int count = 0;
		pItorSet itor;
		for (itor = m_vArray.begin();itor!=m_vArray.end();itor++)
		{
			if(count == index)
				return *itor;
			count++;
		}
	}
	return NULL;
}

bool CCobraArray::containsCobraObject( CCobraObject* obj )
{
	pItorSet itor;
	for (itor = m_vArray.begin();itor!=m_vArray.end();itor++)
	{
		if((CCobraObject*)(*itor) == obj)
			return true;
	}
	return false;
}

unsigned int CCobraArray::capacity()
{
	return m_vArray.size();
}

unsigned int CCobraArray::indexOf( CCobraObject* obj )
{
	int index = 0;
	pItorSet itor;
	for (itor = m_vArray.begin();itor!=m_vArray.end();itor++)
	{
		if((CCobraObject*)(*itor) == obj)
			return index;
		index++;
	}
	return index;
}

CCobraObject* CCobraArray::lastCobraObject()
{
	return m_vArray.back();
}

bool CCobraArray::isOutBound( unsigned int index )
{
	return (index <0 || index>= capacity());
}

void CCobraArray::clearAll()
{
	stl_helper::clearVector(m_vArray);
}

bool CCobraArray::isEmpty()
{
	return m_vArray.empty();
}


