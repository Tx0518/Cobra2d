#ifndef _CNOTIFICATIONSERVICE_H_
#define _CNOTIFICATIONSERVICE_H_

#include "CService.h"
#include "CSingleton.h"

class CNotificationService : public CService,public CSingleton<CNotificationService>
{
public:
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();

private:
	CNotificationService(void);
	~CNotificationService(void);
	friend class CSingleton<CNotificationService>;
};

#endif //_CNOTIFICATIONSERVICE_H_