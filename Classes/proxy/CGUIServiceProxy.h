#ifndef _CGUISERVICEPROXY_H_
#define _CGUISERVICEPROXY_H_

#include "CService.h"


class CLoadUIProxy : public IServiceProxy
{
public:
	CLoadUIProxy(CService* content);
	virtual ~CLoadUIProxy();

	virtual void executeCommand( CIntent* intent,CResponse* response );

};


class CUnloadUIProxy : public IServiceProxy
{
public:
	CUnloadUIProxy(CService* content);
	virtual ~CUnloadUIProxy();

	virtual void executeCommand( CIntent* intent,CResponse* response );
};

#endif	//_CGUISERVICEPROXY_H_