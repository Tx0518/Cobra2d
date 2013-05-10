#ifndef _CSERVICE_H_
#define _CSERVICE_H_ 

#include "CCobraObject.h"
#include "CCobraObjectPool.h"

typedef enum
{
	ACTIVIE_SERVICE = 0x900000,
	NOTIFICATION_SERVICE,
	NET_SERVICE,
} cServiceType;

class CIntent;
class CResponse;

class CService : public CCobraObject
{
public:
	CService(void);
	virtual ~CService(void);
	virtual void onStart();
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);

	virtual void addCobraObject(CCobraObject* obj);
	virtual CCobraObject* getCobraObjectById(int objId);
	virtual void removeCobraObject(CCobraObject* obj);
	virtual void onFinish();
protected:
	CCobraObjectPool m_cobraPool;
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bIsRunning,Running)
};


#endif	//_CSERVICE_H_