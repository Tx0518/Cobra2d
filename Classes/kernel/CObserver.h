#ifndef _COBSERVER_H_
#define _COBSERVER_H_

#include <map>
#include <queue>
#include "CCobraObject.h"
#include "CPattern.h"
#include "CDynObj.h"

class CResponse;
class CActivity;

/*
	CController
*/
class CController : public CCobraObject,public CDynObj
{
public:
	DECLARE_DYNCREATE(CController);
	CController();
	virtual ~CController(void);
	virtual void execute(void* data);
	void assign();
	COBRA_CREATE_PROPERTY(int,m_iObserverId,ObserverID)
};


/*
	CObserver
*/
class CObserver : public CCobraObject
{	
public:
	CObserver(void);
	virtual ~CObserver(void);
	virtual void addController(CController* control);
	virtual void removeController(CController* control);
	virtual void dispatchController(void* data);
	virtual void onHandlerDataStream(void* pMsg);
	virtual void restart();
 	void flushNetMsg();
	bool containsController(int objId);
	bool hasNetMsgUnPost();

	COBRA_CREATE_PROPERTY(int,m_iReceiverId,Receiver)
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bReceiverIsActive,ReceiverState)
	
	bool hasReceiver();
protected:
	void pushNetMsg(void* pMsg);
protected:
	std::map<int,CController*> m_pControllerSet;
	typedef std::map<int,CController*>::iterator pControllItorSet;
	//cache network msg in each observer
	std::queue<void*> m_pNetMsgList;
	typedef std::vector<void*>::iterator pNetMsgItorSet;
};


#endif //_COBSERVER_H_