#ifndef _CGUISERVICE_H_
#define _CGUISERVICE_H_

#include "CService.h"

/*
	CGuiService
	TODO:UI render service 
*/
class CGuiService : public CService
{
public:
	CGuiService(void);
	~CGuiService(void);

	virtual void onStart();
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();
};

#endif	//_CGUISERVICE_H_