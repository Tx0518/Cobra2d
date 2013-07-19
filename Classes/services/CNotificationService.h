#ifndef _CNOTIFICATIONSERVICE_H_
#define _CNOTIFICATIONSERVICE_H_

#include "CService.h"

class CNotificationService : public CService
{
public:
	CNotificationService(void);
	~CNotificationService(void);
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();
};

#endif //_CNOTIFICATIONSERVICE_H_