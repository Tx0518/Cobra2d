#include "CActivity.h"
#include "CResponse.h"
#include "CObserver.h"
#include "CIntent.h"
#include "CService.h"
CActivity::CActivity( void )
	:m_bisActive(false),
	m_bHasObserver(false),
	m_Observer(NULL),
	m_Service(NULL),
	m_pViewPort(NULL)
{
	setObjType(COBRA_ACTIVITY);
}

CActivity::~CActivity( void )
{
}

void CActivity::setActive(bool var)
{
	m_bisActive = var;
}

bool CActivity::isActive()
{
	return m_bisActive;
}

void CActivity::onCreate()
{
}

void CActivity::onFinish()
{
	COBRA_SAFE_DELETE(m_Service);
	COBRA_SAFE_DELETE(m_Observer);
	COBRA_SAFE_DELETE(m_pViewPort);
}

void CActivity::sethasObserver(bool var)
{
	m_bHasObserver = var;
}

bool CActivity::ishasObserver()
{
	return m_bHasObserver;
}

void CActivity::sethasService(bool var)
{
	m_bHasService = var;
}

bool CActivity::ishasService()
{
	return m_bHasService;
}

void CActivity::startActivity( CIntent* intent )
{
	if(intent == NULL) return;
	if(ishasService() && getService()->isRunning())
		getService()->onAcceptIntent(intent);
}

void CActivity::setObserver(CObserver* var)
{
	if(m_Observer == var) return;
	m_Observer = var;
	m_bHasObserver = (var != NULL)?true:false;
	if(m_Observer)
		m_Observer->registerReceiver(this);
}

CObserver* CActivity::getObserver()
{
	return m_Observer;
}

void CActivity::setService(CService* var)
{
	if(m_Service == var) return;
	m_Service = var;
	m_bHasService = (var != NULL)?true:false;
	if(m_Service)
		m_Service->addCobraObject(this);
}

CService* CActivity::getService()
{
	return m_Service;
}

void CActivity::setViewPort(CViewPort* var)
{
	m_pViewPort = var;
}

CViewPort* CActivity::getViewPort()
{
	return m_pViewPort;
}

//override
void CActivity::onResponseHandler( CResponse* reponse )
{
	if(reponse->getRespTarget() != this)
		return;
	if(ishasObserver())
		getObserver()->onResponseHandler(reponse);
}

void CActivity::onUpdate( void* pMsgHead )
{
	if(ishasObserver())
		getObserver()->onHandlerDataStream(pMsgHead);
}
