#include "CHttpAdapter.h"
#include "CHttpResponse.h"
#include "CCobraArray.h"

#include <stdio.h>

const static int HTTP_STATUE_OK = 200;

static unsigned long s_asyncRequestCount = 0;

static CCobraArray* m_pRequestQueue = NULL;

static CCobraArray* m_pResponseQueue = NULL;

static char m_arrErrorBuffer[CURL_ERROR_SIZE];

size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t sizes = size * nmemb;
	return sizes;
}


size_t writeDatatoFile(void* ptr,size_t size,size_t nmemb,void* stream)
{
	int written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

CHttpAdapter::CHttpAdapter( void )
	:m_iTimeOutConnect(30),
	m_iTimeOutRead(60),
	m_pHead(NULL)
{

}

CHttpAdapter::~CHttpAdapter( void )
{
	m_pRequestQueue->clearAll();
	m_pResponseQueue->clearAll();
	COBRA_SAFE_DELETE(m_pRequestQueue);
	COBRA_SAFE_DELETE(m_pResponseQueue);
}

void* CHttpAdapter::onHttpThread( void* data )
{
	CHttpRequest *request = NULL;
	while (true) 
	{
		request = NULL;

		if (0 != m_pRequestQueue->capacity())
		{
			request = dynamic_cast<CHttpRequest*>(m_pRequestQueue->getCobraObjectAtIndex(0));
			m_pRequestQueue->removeCobraObjectAtIndex(0);
		}

		if (NULL == request)
			continue;

		CHttpResponse *response = new CHttpResponse(request);

		int responseCode = -1;
		int retValue = 0;

		switch (request->getRequestType())
		{
		case CHttpRequest::kHttpGet: // HTTP GET
			retValue = HttpAdapterShare->processGetTask(request, 
				writeData, 
				response->getResponseData(), 
				&responseCode);
			break;

		case CHttpRequest::kHttpPost: // HTTP POST
			retValue = HttpAdapterShare->processPostTask(request, 
				writeData, 
				response->getResponseData(), 
				&responseCode);
			break;
		default:
			COBRA_LOG("CCHttpClient: unkown request type, only GET and POSt are supported");
			break;
		}

		// write data to HttpResponse
		response->setResponseCode(responseCode);

		if (retValue != 0) 
		{
			response->setSucceed(false);
			response->setErrorBuffer(m_arrErrorBuffer);
		}
		else
		{
			response->setSucceed(true);
		}
		m_pResponseQueue->addCobraObject(response);
	}

	m_pRequestQueue->clearAll();
	s_asyncRequestCount -= m_pRequestQueue->capacity();
	return 0;
}


int CHttpAdapter::processGetTask( CHttpRequest* request,write_callback callBack,void* stream,int* responseCode )
{
	CURLcode code = CURL_LAST;
	CURL* curl = curl_easy_init();
	do 
	{
		if(!configureCURL(curl))
		{
			break;
		}
		/*
			getHeaderData
		*/
		getHeaderData(curl,request);

		code = curl_easy_setopt(curl,CURLOPT_URL,request->getRequestUrl().c_str());
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBack);
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_setopt(curl,CURLOPT_WRITEDATA,stream);
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_perform(curl);
		COBRA_BREAK_IF(code != CURLE_OK);

		curl_slist_free_all(m_pHead);
		COBRA_SAFE_DELETE(m_pHead);

		code = curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,responseCode);
		if( code != CURLE_OK || *responseCode != HTTP_STATUE_OK)
		{
			code = CURLE_HTTP_RETURNED_ERROR;
		}
	} while (0);
	
	clearCurl(curl);
	return (code == CURLE_OK ?0:1);
}


int CHttpAdapter::processPostTask( CHttpRequest* request,write_callback callBack,void* stream,int* responseCode )
{
	CURLcode code = CURL_LAST;
	CURL* curl = curl_easy_init();
	do 
	{
		if(!configureCURL(curl))
			break;
		/*
			getHeaderData
		*/
		getHeaderData(curl,request);

		code = curl_easy_setopt(curl,CURLOPT_URL,request->getRequestUrl().c_str());
		COBRA_BREAK_IF(code != CURLE_OK);

		code  = curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,callBack);
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_setopt(curl,CURLOPT_POST,1);
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_setopt(curl,CURLOPT_POSTFIELDS,request->getRequestData());
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,request->getRequestSize());
		COBRA_BREAK_IF(code != CURLE_OK);

		code = curl_easy_perform(curl);
		if(code != CURLE_OK || *responseCode != HTTP_STATUE_OK)
			code = CURLE_HTTP_RETURNED_ERROR;

	} while (0);

	clearCurl(curl);

	return (code == CURLE_OK?0:1);
}

bool CHttpAdapter::lazyInitThread()
{
	m_pRequestQueue  = new CCobraArray();
	m_pResponseQueue = new CCobraArray();
	
	return true;
}

void CHttpAdapter::clearCurl( CURL* curl )
{
	if(curl)
		curl_easy_cleanup(curl);
}

bool CHttpAdapter::configureCURL(CURL *handle)
{
	if (!handle) 
		return false;

	int code;
	code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, m_arrErrorBuffer);
	if (code != CURLE_OK) 
		return false;

	code = curl_easy_setopt(handle, CURLOPT_TIMEOUT,getTimeOutRead());
	if (code != CURLE_OK) 
		return false;

	code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, getTimeOutConnect());
	if (code != CURLE_OK) 
		return false;

	return true;
}

void CHttpAdapter::sendRequest( CHttpRequest* request )
{
// 	COBRA_RETURN_IF(false == lazyInitThread());
// 	COBRA_RETURN_IF(!request);
// 
// 	++s_asyncRequestCount;
// 	m_pRequestQueue->addCobraObject(request);	
// 	int responseCode = -1;
// 	CHttpResponse response(request);
// 	processGetTask(request,writeData,response.getResponseData(),&responseCode);


#if 1
	CURL *curl;
	CURLcode res;
	void* data = NULL;
	curl = curl_easy_init();
	if (curl)
	{
		const char* url = "http://113.196.94.59/cluster_server/index.php?act=1088&session=90051051&sttActivityCopy=999&sttGeneral=999&sttGeneralList=999&sttMainCopy=999&sttUser=999&uid=411377";
		curl_easy_setopt(curl, CURLOPT_URL,url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, data); //将返回的http头输出到fp指向的文件
		res = curl_easy_perform(curl);   // 执行
		if (res != 0) 
		{
			curl_easy_cleanup(curl);
		}
	}
#endif
}


void CHttpAdapter::getHeaderData( CURL* handler,CHttpRequest* request )
{
	if(!configureCURL(handler))
		return;
	CURLcode code = CURL_LAST;
	m_pHead = NULL;
	std::vector<std::string> heads = request->getHeader();
	if(!heads.empty())
	{
		for(std::vector<std::string>::iterator it = heads.begin();it != heads.end();it++)
		{
			m_pHead = curl_slist_append(m_pHead,it->c_str());
		}
		code = curl_easy_setopt(handler,CURLOPT_HTTPHEADER,m_pHead);
		COBRA_RETURN_IF(code != CURLE_OK);
	}
	COBRA_LOG("getHeaderData request->getHeader() failure");
}
