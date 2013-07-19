#include "CActivity.h"
#include "CResponse.h"
#include "CObserver.h"
#include "CIntent.h"
#include "CService.h"
#include "CHandler.h"
#include "CGui.h"
#include "CBundle.h"

CActivity::CActivity( void )
	:m_bisActive(false),
	m_pGui(NULL),
	m_iObserverId(COBRA_UNKNOWN)
{
	setObjType(COBRA_ACTIVITY);
}

CActivity::~CActivity( void )
{
}

void CActivity::onCreate()
{
	//do something
}

void CActivity::startActivity( CIntent* intent )
{
	onDispatcher(intent);
}

void CActivity::startActivity( int activityId )
{
	CIntent intent(INTENT_START_ACTIVITY,activityId,SERVICE_ACTIVITY);
	onDispatcher(&intent);
}

void CActivity::bindService( CIntent* service )
{
	onDispatcher(service);
}

void CActivity::unBindService( CIntent* service )
{
	onDispatcher(service);
}

void CActivity::loadGUI(CBundle* bundle)
{
	CIntent intent(INTENT_LOAD_UI,getObjectID(),SERVICE_GUI,bundle);
	onDispatcher(&intent);
}

void CActivity::updateGUI( CBundle* bundle )
{
	CIntent intent(INTENT_UPDATE_UI,getObjectID(),SERVICE_GUI,bundle);
	onDispatcher(&intent);
}

void CActivity::setObserverId(int var)
{
	m_iObserverId = var;
	COBRA_CHECK_UNKNOWN(m_iObserverId);
	CIntent intent(INTENT_REGISTER_OBSERVER,m_iObserverId,SERVICE_ACTIVITY,this);
	onDispatcher(&intent);
}

int CActivity::getObserverId()
{
	return m_iObserverId;
}

void CActivity::addController(const std::string& controlName)
{
	CIntent intent(INTENT_REGISTER_CONTROLLER,m_iObserverId,SERVICE_ACTIVITY);
	intent.setTargetName(controlName);
	onDispatcher(&intent);
}

void CActivity::releaseGUI()
{
	COBRA_CHECK_NULL(m_pGui);
	m_pGui->release();
	delete m_pGui;
}

void CActivity::getActivityByID( int activityID )
{
	CIntent intent(INTENT_GET_ACTIVITY,activityID,SERVICE_ACTIVITY);
	onDispatcher(&intent);
}

//override
void CActivity::onResponseHandler( CResponse* response )
{
	COBRA_RETURN_IF(response->getRespTarget() != this);
	int respCode = response->getRespCode();
	//override
}

void CActivity::onUpdate( void* pMsgHead )
{
	COBRA_CHECK_UNKNOWN(m_iObserverId);
	CIntent intent(INTENT_UPDATE_DATASTREAM,m_iObserverId,SERVICE_ACTIVITY);
	intent.setData(pMsgHead);
	onDispatcher(&intent);
}

void CActivity::onDispatcher( CIntent* intent )
{
	COBRA_CHECK_NULL(intent);
	CHandler::onHandler(intent);
}

void CActivity::onFinish()
{
	CIntent intent(INTENT_FINLISH_ACTIVITY,getObjectID(),SERVICE_ACTIVITY,this);
	onDispatcher(&intent);
}

void CActivity::onDestory()
{
	//override 
	//TODO: destory all object memory of activity
}

/************************************************************************/
/* 
	CActivityHandler
*/
void CActivity::CActivityHandler::handlerMessage( CMessage* msg )
{
	CHandler::handlerMessage(msg);
}

/************************************************************************/
