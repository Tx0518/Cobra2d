#include "CActivityService.h"
#include "CActivity.h"
#include "CIntent.h"
#include "CResponse.h"
#include "CObserver.h"

CActivityService::CActivityService( void )
	:m_iCurrentObjID(-1)
{
	this->setObjectID(ACTIVIE_SERVICE);
}

CActivityService::~CActivityService(void)
{
	m_iCurrentObjID = -1;
}

void CActivityService::onStart()
{
}

void CActivityService::onAcceptIntent( CIntent* intent )
{
	if(intent == NULL) return;
	int itnAction = intent->getIntentAction();
	m_iCurrentObjID = intent->getTargetKey();
	CResponse* resp = new CResponse();
	if( itnAction ==  INTENT_START_ACTIVITY)
	{	
		CActivity* activity = new CActivity();
		activity->onCreate();
		resp->setRespCode(RESPONSE_CREATEACTIVITY_SUCCESS);
		resp->setRespTarget(activity);
	}
	else if(itnAction == INTENT_FINLISH_ACTIVITY)
	{
		if(m_iCurrentObjID == -1) return;
		CActivity* curActivity = dynamic_cast<CActivity*>(m_cobraPool.getCobraObjectById(m_iCurrentObjID));
		if(curActivity == NULL) return;
		curActivity->onFinish();
	}
	if(resp->getRespCode() == RESPONSE_UNKOWN) return;
	onSynchResponse(resp);
}

void CActivityService::onSynchResponse( CResponse* response )
{
	if(response->getRespTarget())
	{
		CActivity* activity = dynamic_cast<CActivity*>(response->getRespTarget());
		activity->getObserver()->onResponseHandler(response);
	}
}

void CActivityService::onFinish()
{
	
}

