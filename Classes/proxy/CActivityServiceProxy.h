#ifndef _C_ACTIVITYSERVICEPROXY_H_
#define _C_ACTIVITYSERVICEPROXY_H_

#include "CService.h"

class CStartActivityProxy : public IServiceProxy
{
public:
	CStartActivityProxy(CService* content);
	virtual ~CStartActivityProxy(void);
	virtual void executeCommand( CIntent* intent,CResponse* response );
};


class CFinishActivityProxy : public IServiceProxy
{
 public:
 	CFinishActivityProxy(CService* content);
 	virtual ~CFinishActivityProxy(void);
 	virtual void executeCommand( CIntent* intent,CResponse* response );
};


/************************************************************************/
/* 
	CBindServiceProxy
*/
/************************************************************************/
class CBindServiceProxy : public IServiceProxy
{
 public:
 	CBindServiceProxy(CService* content);
 	virtual ~CBindServiceProxy(void);
 	virtual void executeCommand( CIntent* intent,CResponse* response );
};


/************************************************************************/
/* 
	CFetchActivityProxy
*/
/************************************************************************/
class CFetchActivityProxy : public IServiceProxy
{
public:
	CFetchActivityProxy(CService* content);
 	virtual ~CFetchActivityProxy();
 	virtual void executeCommand( CIntent* intent,CResponse* response );
 };

/************************************************************************/
/*
	CRegisterControllerProxy
*/
class CRegisterControllerProxy : public IServiceProxy
{
public:
	CRegisterControllerProxy(CService* content);
	virtual ~CRegisterControllerProxy();
	virtual void executeCommand( CIntent* intent,CResponse* response );
};

/************************************************************************/

/************************************************************************/
/*
	CUpdateDataStreamControllerProxy
*/
class CUpdateDataStreamControllerProxy : public IServiceProxy
{
public:
	CUpdateDataStreamControllerProxy(CService* content);
	virtual ~CUpdateDataStreamControllerProxy();
	virtual void executeCommand( CIntent* intent,CResponse* response );
};
/************************************************************************/

/************************************************************************/
/* 
	CRegisterObserverProxy
*/
class CRegisterObserverProxy : public IServiceProxy
{
public:
	CRegisterObserverProxy(CService* content);
	virtual ~CRegisterObserverProxy();
	virtual void executeCommand( CIntent* intent,CResponse* response );
};

/************************************************************************/

#endif	//_C_ACTIVITYSERVICEPROXY_H_