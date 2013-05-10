#include "CService.h"
#include "CIntent.h"
#include "CResponse.h"

CService::CService( void )
	:m_bIsRunning(false)
{

}

CService::~CService( void )
{

}

void CService::onAcceptIntent( CIntent* intent )
{
	//override
}

void CService::onSynchResponse( CResponse* response )
{
	//override
}

void CService::addCobraObject( CCobraObject* obj )
{
	m_cobraPool.addCobraObject(obj);
}

CCobraObject* CService::getCobraObjectById( int objId )
{
	return m_cobraPool.getCobraObjectById(objId);
}

void CService::removeCobraObject( CCobraObject* obj )
{
	m_cobraPool.removeCobraObject(obj);
}

void CService::onFinish()
{
	//override
	setRunning(false);
}

void CService::onStart()
{
	//override
	setRunning(true);
}

void CService::setRunning(bool var)
{
	m_bIsRunning = var;
}

bool CService::isRunning()
{
	return m_bIsRunning;
}
