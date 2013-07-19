#include "CHttpService.h"
#include "CIntent.h"
#include "CResponse.h"

CHttpService::CHttpService( void )
{
}

CHttpService::~CHttpService( void )
{
}

void CHttpService::onStart()
{
}

void CHttpService::onAcceptIntent( CIntent* intent )
{
	COBRA_CHECK_NULL(intent);
	cIntentAction action = intent->getIntentAction();
	CHttpRequest* request = dynamic_cast<CHttpRequest*>(intent->getTargetObj());
	COBRA_CHECK_NULL(request);
	CResponse response;
	int http_code;
	if(action == INTENT_HTTP_GET)
	{
		http_code = doHttpGet(request);
	}
	else if(action == INTENT_HTTP_POST)
	{
		http_code = doHttpPost(request);
	}
	if(http_code == ERROR_FAIL)
		response.setRespCode(RESPONSE_CODE_FAILURE);
	else
		response.setRespCode(RESPONSE_CODE_SUCCESS);
	response.setRespTarget(request);
	if(response.getRespCode() == RESPONSE_UNKOWN) return;
	onSynchResponse(&response);
}

void CHttpService::onSynchResponse( CResponse* response )
{
	CService::onSynchResponse(response);
}

void CHttpService::onFinish()
{
	clearupCurl();
}

int CHttpService::doHttpGet( CHttpRequest* request )
{
	curl_easy_reset( m_pCURL );
	const char* url = request->getRequestUrl().c_str();
	size_t urllen = strlen( url );
	size_t datalen = strlen(request->getUserData());
	
	if(url == NULL)
		return ERROR_FAIL;

	char* surl = new char[ urllen + datalen + 1 + 1];
	if( !surl )
	{
		fprintf( stderr, "doHttpGet failed, unable to malloc memery\n" ); 
		return ERROR_FAIL;
	}
	strncpy( surl, url, urllen );
	surl[ urllen ] = '?';
	strcpy( surl + urllen + 1, request->getUserData());
	curl_easy_setopt( m_pCURL, CURLOPT_URL, surl );
	curl_easy_setopt( m_pCURL, CURLOPT_HTTPGET, 1 );
	//curl_easy_setopt( m_pCURL, CURLOPT_HEADER, withheader );
	curl_easy_setopt( m_pCURL, CURLOPT_TIMEOUT, request->getTimeOut());
	curl_easy_setopt( m_pCURL, CURLOPT_WRITEFUNCTION, CHttpService::processFunc ); 
	curl_easy_setopt( m_pCURL, CURLOPT_WRITEDATA, this ); 

	CURLcode res = curl_easy_perform( m_pCURL);
	delete [] surl;
	return ( CURLE_OK == res ) ? CURLE_OK : ERROR_FAIL;
}


int CHttpService::doHttpPost( CHttpRequest* request )
{	
	curl_easy_reset( m_pCURL );
	//curl_easy_setopt( m_pCURL, CURLOPT_HEADER, withheader );
	curl_easy_setopt( m_pCURL, CURLOPT_URL, request->getRequestUrl().c_str());
	curl_easy_setopt( m_pCURL, CURLOPT_POST, 1 );
	curl_easy_setopt( m_pCURL, CURLOPT_POSTFIELDS, request->getUserData());
	curl_easy_setopt( m_pCURL, CURLOPT_TIMEOUT, request->getTimeOut());
	curl_easy_setopt( m_pCURL, CURLOPT_WRITEFUNCTION, CHttpService::processFunc); 
	curl_easy_setopt( m_pCURL, CURLOPT_WRITEDATA, this );
	CURLcode res = curl_easy_perform( m_pCURL);
	return ( CURLE_OK == res ) ? CURLE_OK : ERROR_FAIL;
}

size_t CHttpService::processFunc( void* ptr, size_t size, size_t nmemb, void *usrptr )
{
	CHttpService* p =(CHttpService*) usrptr;
	return p->ondidProcessFunc( ptr, size, nmemb );
}

int CHttpService::ondidProcessFunc( void* data, size_t size, size_t nmemb )
{
	printf( "\n ===== CHttpService::processFunc( void* data, size_t size, size_t nmemb ) ===== \n" ); 
	return size * nmemb; 
}

void CHttpService::clearupCurl()
{
	if(m_pCURL)
		curl_easy_cleanup(m_pCURL);
}
