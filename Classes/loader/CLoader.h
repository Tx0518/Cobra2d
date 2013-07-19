#ifndef _CLOADER_H_
#define _CLOADER_H_

#include "CCobraObject.h"
#include "CHttpRequest.h"
#include "CEvent.h"
#include "CPattern.h"

#define MAX_BUFFER_SIZE				4096
#define MAX_TIMEOUTCONNECT			1500
#define MAX_TIMEOUTREAD				1500
#define MAX_LOAD_FILE_NUMBER		10

class CCobraArray;
class CResponse;
/* 
	CLoader
*/
class CLoader : public CCobraObject,public CEventDispather,public IResponseReciver
{
public:
	CLoader(void);
	virtual ~CLoader(void);

	virtual void load(CHttpRequest* request);
	virtual void load(CCobraArray* loadList);

	virtual void onResponseHandler( CResponse* response );
protected:
	void didLoadConnect();
	void didLoadProgress(double currentByte,double totalBytes,float percent);
	void didLoadCompleted();
	void didLoadError();
	void invalidateCode(int code);
private:
	static size_t on_getContentLength_func(void *buffer, size_t size, size_t nmemb, void* stream);
	static size_t on_progress_data_recv(void* prgBar,double t, double d,double ultotal,double ulnow);
	static size_t on_process_write_data_to_buffer(void* buffer,size_t size,size_t nmemb,void* stream);
	static size_t on_process_write_data_to_file(void* buffer,size_t size,size_t nmemb,void* stream);

	virtual void onDispatcher( CEvent* evt );

	

protected:
	char m_buffer[MAX_BUFFER_SIZE];
};

#endif //_CLOADER_H_