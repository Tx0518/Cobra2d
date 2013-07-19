#ifndef _CHTTPADAPTER_H_
#define _CHTTPADAPTER_H_

#include "CCobraObject.h"
#include "CSingleton.h"
#include "CHttpRequest.h"
#include "curl/curl.h"

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

class CHttpAdapter : public CCobraObject,public CSingleton<CHttpAdapter>
{
public:
	int getTimeOutRead() { return m_iTimeOutRead;};
	int getTimeOutConnect() {return m_iTimeOutConnect;};	
	void setTimeOutRead(int value) { m_iTimeOutRead = value;};
	void setTimeOutConnect(int value) { m_iTimeOutConnect = value;};
	void sendRequest(CHttpRequest* request);
	
protected:
	static void* onHttpThread(void* data);

	bool configureCURL(CURL* handle);
	bool lazyInitThread();
	void getHeaderData(CURL* handler,CHttpRequest* request);
	void clearCurl(CURL* curl);
	int processGetTask(CHttpRequest* request,write_callback callBack,void* stream,int* responseCode);
	int processPostTask(CHttpRequest* request,write_callback callBack,void* stream,int* responseCode);
	
private:
	friend class CSingleton<CHttpAdapter>;
	CHttpAdapter(void);
	virtual ~CHttpAdapter(void);

private:
	int m_iTimeOutConnect;
	int m_iTimeOutRead;
	curl_slist* m_pHead;
};

#define HttpAdapterShare CHttpAdapter::getInstance()

#endif	//_CHTTPADAPTER_H_