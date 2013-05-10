#ifndef _CACTIVITYSERVICE_H_
#define _CACTIVITYSERVICE_H_

#include "CSingleton.h"
#include "CService.h"

class CIntent;
class CActivity;

class CActivityService : public CService,public CSingleton<CActivityService>
{
public:
	virtual void onStart();
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();
	COBRA_CREATE_PROPERTY_READONLY(int,m_iCurrentObjID,CurrentObjID)
private:
	friend class CSingleton<CActivityService>;
	CActivityService(void);
	~CActivityService(void);
};

#endif //_CACTIVITYSERVICE_H_