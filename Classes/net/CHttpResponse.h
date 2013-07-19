#ifndef _CHTTPRESPONSE_H_
#define _CHTTPRESPONSE_H_

#include "CCobraObject.h"
#include "CHttpRequest.h"

class CHttpResponse : public CCobraObject
{
public:
	CHttpResponse(CHttpRequest* request)
		:m_pHttpRequest(request),
		m_bSucceed(false)
	{
		m_strErrorBuffer.clear();
		m_pResponseData.clear();
	}

	virtual ~CHttpResponse(void)
	{
		COBRA_SAFE_DELETE(m_pHttpRequest);
	}

	inline CHttpRequest* getHttpRequest()
	{
		return m_pHttpRequest;
	}

	inline void setSucceed(bool val)
	{
		m_bSucceed = val;
	}

	inline bool isSuceed()
	{
		return m_bSucceed;
	}

	inline void setResponseCode(int code)
	{
		m_iResponseCode = code;
	}

	inline int getResponseCode()
	{
		return m_iResponseCode;
	}

	inline void setErrorBuffer(const char* value)
	{
		m_strErrorBuffer.clear();
		m_strErrorBuffer.assign(value);
	}
	
	inline const std::string& getErrorBuffer()
	{
		return m_strErrorBuffer;
	}

	inline void setResponseData(std::vector<char>* data)
	{
		m_pResponseData = *data;
	}

	inline std::vector<char>* getResponseData()
	{
		return &m_pResponseData;
	}
protected:
	CHttpRequest* m_pHttpRequest;
	bool m_bSucceed;
	std::vector<char>		m_pResponseData;
	int						m_iResponseCode;
	std::string				m_strErrorBuffer;
	
};

#endif	//_CHTTPRESPONSE_H_