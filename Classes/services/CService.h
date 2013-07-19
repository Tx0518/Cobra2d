#ifndef _CSERVICE_H_
#define _CSERVICE_H_ 

#include "CCobraObject.h"
#include "CCobraObjectPool.h"
#include <map>

class CIntent;
class CResponse;
class IServiceProxy;

class CService : public CCobraObject
{
public:
	CService(void);
	virtual ~CService(void);
	virtual void onStart();
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();
public:
	void addCobraObject(CCobraObject* obj);
	bool ishasBinded(int objId);
	CCobraObject* getCobraObjectById(int objId);
	void removeCobraObject(CCobraObject* obj);
	void addServiceProxy(int cmdKey,IServiceProxy* proxy);
	IServiceProxy* getServiceProxy(int cmdKey);
	void removeServiceProxy(int cmdKey);
	void clearAllCommandProxy();
protected:
	CCobraObjectPool m_cobraPool;
	void didResponse(CResponse* response);
	void onDispatchServiceProxy(CIntent* intent,CResponse* resp);
protected:
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bIsBroadcast,BroadCast)
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bIsRunning,Running)

private:
	std::map<int,IServiceProxy*> m_pServiceProxySet;
	typedef std::map<int,IServiceProxy*>::iterator pServiceProxyItor;
};


/************************************************************************/
/* 
	IServiceProxy
*/
class IServiceProxy
{
public:
	IServiceProxy(CService* context)
		:m_pContext(context)
	{}
	virtual ~IServiceProxy(void){ m_pContext = NULL;}
	virtual void executeCommand(CIntent* intent,CResponse* response) = 0;
protected:
	CService* m_pContext;
};


/************************************************************************/

#endif	//_CSERVICE_H_