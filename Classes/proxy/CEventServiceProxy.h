#ifndef _CEVENTSERVICEPROXY_H_
#define _CEVENTSERVICEPROXY_H_

#include "CService.h"


class CRegisterEventProxy : public IServiceProxy
{
public:
	CRegisterEventProxy(CService* content);
	virtual ~CRegisterEventProxy(void);

	virtual void executeCommand( CIntent* intent,CResponse* response );
};



class CUnRegisterEventProxy : public IServiceProxy
{
public:
	CUnRegisterEventProxy(CService* content);
	virtual ~CUnRegisterEventProxy(void);

	virtual void executeCommand( CIntent* intent,CResponse* response );
};



class CExecEventProxy : public IServiceProxy
{
public:
	CExecEventProxy(CService* content);
	virtual ~CExecEventProxy(void);

	virtual void executeCommand( CIntent* intent,CResponse* response );

};


#endif	//_CEVENTSERVICEPROXY_H_