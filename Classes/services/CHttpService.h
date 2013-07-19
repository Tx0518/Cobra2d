#ifndef _CHTTPSERVICE_H_
#define _CHTTPSERVICE_H_

#include "CService.h"
#include "curl/curl.h"
#include "CHttpRequest.h"

class CHttpService : public CService
{
public:
	CHttpService(void);
	virtual ~CHttpService(void);

	virtual void onStart();
	virtual void onAcceptIntent( CIntent* intent );
	virtual void onSynchResponse( CResponse* response );
	virtual void onFinish();
protected:
	virtual int doHttpGet( CHttpRequest* request);
	virtual int doHttpPost( CHttpRequest* request);

	void clearupCurl();
	virtual int ondidProcessFunc( void* data, size_t size, size_t nmemb );
	static size_t processFunc( void* ptr, size_t size, size_t nmemb, void *usrptr );
protected:
	CURL* m_pCURL;
};

#endif	//_CHTTPSERVICE_H_