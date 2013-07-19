#ifndef _CACTIVITY_H_
#define _CACTIVITY_H_

#include "CCobraObject.h"
#include "CBaseDefine.h"
#include "CMsgSubject.h"
#include "CPattern.h"
#include "CHandler.h"

class CIntent;
class CResponse;
class CGui;
class CBundle;
class CController;

/*
	CActivity
*/
class CActivity : public CCobraObject,public IMsgObserver,public IResponseReciver
{
public:
	CActivity(void);
	virtual ~CActivity(void);
	virtual void onCreate();
	virtual void onFinish();
	virtual void onDestory();
	
	virtual void startActivity(CIntent* intent);
	virtual void startActivity(int activityId);
	virtual void getActivityByID(int activityID);
	virtual void addController(const std::string& controlName);
	virtual void loadGUI(CBundle* bundle);
	virtual void releaseGUI();
	virtual void updateGUI(CBundle* bundle);
	virtual void bindService(CIntent* service);
	virtual void unBindService(CIntent* service);
	virtual void onResponseHandler(CResponse* response);
	virtual void onUpdate( void* pMsgHead );

	//////////////////////////////////////////////////////////////////////////
	//inner class CActivityHandler
	class CActivityHandler : public CHandler
	{
	public:
		CActivityHandler(void){}
		~CActivityHandler(void){}
		virtual void handlerMessage( CMessage* msg );
	};
protected:
	virtual void onDispatcher(CIntent* intent);
protected:
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bisActive,Active)
	COBRA_CREATE_PROPERTY(CGui*,m_pGui,GUI)
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(int,m_iObserverId,ObserverId)
	CActivityHandler mHandler;
};

#endif //_CACTIVITY_H_