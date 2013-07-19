#include "CLoader.h"
#include "curl/curl.h"
#include <stdio.h>
#include "CBaseHelper.h"
#include "CCobraArray.h"
#include "CHandler.h"
#include "CResponse.h"
#include <stdlib.h>
#include <sys/stat.h>

CLoader::CLoader( void )
{
	setObjType(COBRA_LOADER);
}


CLoader::~CLoader( void )
{
}

/*	
	fetch size from remote file
*/
size_t CLoader::on_getContentLength_func(void *buffer, size_t size, size_t nmemb, void* stream) 
{
	int r;
	long len = 0;
	r = sscanf((const char *)buffer, "Content-Length: %ld\n", &len);
	if (r)
		*((long *) stream) = len;
	return size * nmemb;
}


/*
	download file and save location file
*/
size_t CLoader::on_process_write_data_to_file(void* buffer,size_t size,size_t nmemb,void* stream)
{
	FILE *fp = (FILE *)stream;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	return return_size;
}

/*
	download file and write to buffer
*/
size_t CLoader::on_process_write_data_to_buffer(void* buffer,size_t size,size_t nmemb,void* stream)
{
	strcat((char*)stream, (char*)buffer);
	return size * nmemb;
}

/*
	on_progress_data_reciver
*/
size_t CLoader::on_progress_data_recv(void* progBar,double t,double d, double ultotal,double ulnow)
{
 	COBRA_LOG("%d,%d",d,t);
	//didLoadProgress(t,d,0.0f);
	return 0;
}


/*
	loader on start
*/
void CLoader::load( CHttpRequest* request )
{
	COBRA_CHECK_NULL(request);
	
	struct stat file_info;
	int use_resume = 0;
	curl_off_t local_file_len = -1 ;
	long filesize =0 ;
	const char* remote_url = request->getRequestUrl().c_str();
	if(stat(remote_url, &file_info) == 0) 
	{
		local_file_len =  file_info.st_size;
		use_resume  = 1;
	}

	CURL* curl;
	CURLcode code = CURL_LAST;
	curl = curl_easy_init();
	curl_global_init(CURL_GLOBAL_ALL);

	COBRA_CHECK_NULL(curl);

	code = curl_easy_setopt(curl,CURLOPT_NOSIGNAL,1L);
	COBRA_RETURN_IF(code!=CURLE_OK);

	code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, m_buffer);
	COBRA_RETURN_IF(code!=CURLE_OK);

	code = curl_easy_setopt(curl, CURLOPT_TIMEOUT,MAX_TIMEOUTREAD);
	COBRA_RETURN_IF(code!=CURLE_OK);

	code = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_TIMEOUTCONNECT);
	COBRA_RETURN_IF(code!=CURLE_OK);
	
	curl_easy_setopt(curl, CURLOPT_URL,remote_url);
	if(request->getRequestFileType() == CHttpRequest::kDownloadSave)
	{
		FILE* file = fopen(request->getSaveTargetFileAddr().c_str(),"ab+");
		COBRA_CHECK_NULL(file);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,CLoader::on_process_write_data_to_file);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	}
	else if(request->getRequestFileType() == CHttpRequest::kDownloadRead)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,CLoader::on_process_write_data_to_buffer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, m_buffer);
	}
	//set http head function
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, on_getContentLength_func);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, &filesize);

	// set libcurl resume file position
	curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, use_resume?local_file_len:0);

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	curl_easy_setopt(curl,CURLOPT_PROGRESSFUNCTION,CLoader::on_progress_data_recv);
 	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	code = curl_easy_perform(curl);

	if (code != CURLE_OK) 
	{
		didLoadError();
		curl_easy_cleanup(curl);
	}
	else
	{
		didLoadCompleted();
	}
}

/*
	 batch loader
*/
void CLoader::load( CCobraArray* loadList )
{
	if(loadList->isEmpty()) return;
	unsigned int count = 0;
	unsigned int maxLen = loadList->capacity();
	while(count< maxLen)
	{
		CHttpRequest* request = dynamic_cast<CHttpRequest*>(loadList->getCobraObjectAtIndex(count));
		load(request);
		count++;
	}
}

void CLoader::didLoadConnect()
{
	COBRA_LOG("didLoadConnect");
	CLoadEvent loadEvt(EVENT_LOAD_CONNECT,this);
	onDispatcher(&loadEvt);
}

void CLoader::didLoadProgress(double currentByte,double totalBytes,float percent)
{
	COBRA_LOG("didLoadProgress");
	CLoadEvent loadEvt(EVENT_LOADER_PROGRESS_DATA);
	loadEvt.setCurrentByte(currentByte);
	loadEvt.setTotleBytes(totalBytes);
	loadEvt.setPercent(percent);
	onDispatcher(&loadEvt);
}


void CLoader::didLoadCompleted()
{
	COBRA_LOG("didLoadCompleted");
	CLoadEvent loadEvt(EVENT_LOAD_COMPLETE,this);
	onDispatcher(&loadEvt);
}

void CLoader::didLoadError()
{
	COBRA_LOG("didLoadError");
	CLoadEvent loadEvt(EVENT_LOAD_ERROR,this);
	onDispatcher(&loadEvt);
}

void CLoader::invalidateCode( int code )
{
	if(code != CURLE_OK)
		didLoadError();
}

void CLoader::onDispatcher( CEvent* evt )
{
	COBRA_CHECK_NULL(evt);
	CHandler::onHandler(evt);
}

void CLoader::onResponseHandler( CResponse* response )
{
	COBRA_CHECK_NULL(response);
}
