#include "CService.h"
#include "CIntent.h"
#include "CResponse.h"
#include "CActivity.h"
#include "CObserver.h"
#include "CSTLHelper.h"


CService::CService(void)
	:m_bIsRunning(false),
	m_bIsBroadcast(false)
{
}

CService::~CService( void )
{
	m_bIsRunning = false;
	m_bIsBroadcast = false;
}

/*
	accept Intent and response
*/
void CService::onAcceptIntent( CIntent* intent )
{
	COBRA_CHECK_NULL(intent);
	CResponse resp;
	onDispatchServiceProxy(intent,&resp);
	onSynchResponse(&resp);
}

void CService::onSynchResponse( CResponse* response )
{
	//override do something
	didResponse(response);
}

void CService::didResponse( CResponse* response )
{
	COBRA_CHECK_NULL(response);
	COBRA_CHECK_NULL(response->getRespTarget());
	CActivity* activity = dynamic_cast<CActivity*>(response->getRespTarget());
	COBRA_CHECK_NULL(activity);
	activity->onResponseHandler(response);
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

bool CService::ishasBinded(int objId)
{
	return m_cobraPool.containsCobraObject(objId);
}

void CService::addServiceProxy( int cmdKey,IServiceProxy* proxy )
{
	m_pServiceProxySet[cmdKey] = proxy;
}

void CService::removeServiceProxy( int cmdKey )
{
	pServiceProxyItor itor;
	for (itor = m_pServiceProxySet.begin();itor != m_pServiceProxySet.end();itor++)
	{
		if(itor->first == cmdKey)
		{
			delete itor->second;
			m_pServiceProxySet.erase(itor);
		}
	}
}

IServiceProxy* CService::getServiceProxy( int cmdKey )
{
	if(m_pServiceProxySet.empty()) return NULL;
	return m_pServiceProxySet[cmdKey];
}

void CService::clearAllCommandProxy()
{
	stl_helper::clearMap(m_pServiceProxySet);
}

void CService::onDispatchServiceProxy(CIntent* intent,CResponse* resp)
{
	COBRA_CHECK_NULL(intent);
	COBRA_CHECK_NULL(resp);
	IServiceProxy* cmdProxy = getServiceProxy(intent->getIntentAction());
	COBRA_CHECK_NULL(cmdProxy);
	cmdProxy->executeCommand(intent,resp);
}
