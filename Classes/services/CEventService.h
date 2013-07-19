#ifndef _CEVENTSERVICE_H_
#define _CEVENTSERVICE_H_

#include "CService.h"

class CEventService : public CService
{
public:
	CEventService(void);
	virtual ~CEventService(void);

	virtual void onStart();
	virtual void onAcceptIntent( CIntent* intent );
	virtual void onSynchResponse( CResponse* response );
	virtual void onFinish();

};

#endif	//_CEVENTSERVICE_H_