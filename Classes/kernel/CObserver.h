#ifndef _COBSERVER_H_
#define _COBSERVER_H_

#include <map>
#include "CCobraObject.h"

class CResponse;
class CActivity;

/*
	CCommand
*/
class CCommand : public CCobraObject
{
public:
	CCommand(CCobraObject* target);
	virtual ~CCommand(void);
	virtual void execute() = 0;
protected:
	CCobraObject* m_pTarget;
};

/*
	CObserver
*/
class CObserver : public CCobraObject
{	
public:
	CObserver(void);
	virtual ~CObserver(void);
	virtual void onResponseHandler(CResponse* reponse) = 0;
	virtual void registerReceiver(CActivity* activity) = 0;
	virtual void addCommand(CCommand* command);
	virtual void removeCommand(CCommand* command);
	virtual void dispatchCommand(int cmdKey);
	virtual void onHandlerDataStream(void* pMsg);
protected:
	std::map<int,CCommand*> m_pCommandSet;
};

#endif //_COBSERVER_H_