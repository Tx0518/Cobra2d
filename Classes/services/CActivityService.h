#ifndef _CACTIVITYSERVICE_H_
#define _CACTIVITYSERVICE_H_

#include "CService.h"

class CActivity;


class CActivityService : public CService
{
public:
	CActivityService(void);
	~CActivityService(void);
	virtual void onStart();
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();
public:
	COBRA_CREATE_PROPERTY_READONLY(int,m_iCurrentObjID,CurrentObjID)
};

#endif //_CACTIVITYSERVICE_H_