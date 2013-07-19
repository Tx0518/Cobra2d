#ifndef _CHTTPREQUEST_H_
#define _CHTTPREQUEST_H_

#include "CCobraObject.h"
#include <vector>

/*
	CHttpRequest
*/
class CHttpRequest : public CCobraObject
{
public:
	typedef enum
	{
		kHttpUnkown,
		kHttpGet,
		kHttpPost,
	} cHttpRequestType;

	typedef enum
	{
		kDownloadSave,
		kDownloadRead,
	} cHttpRequestDataType;

	CHttpRequest(void)
		:m_eRequestType(kHttpUnkown),
		m_eRequestFileType(kDownloadSave)
	{
		setObjType(COBRA_HTTP_REQUEST);
	}

	virtual ~CHttpRequest(void)
	{

	}

	void setRequestType(cHttpRequestType type)
	{
		m_eRequestType = type;
	}

	cHttpRequestType getRequestType()
	{
		return m_eRequestType;
	}

	void setRequestFileType(cHttpRequestDataType type)
	{
		m_eRequestFileType = type;
	}

	cHttpRequestDataType getRequestFileType()
	{
		return m_eRequestFileType;
	}

	void setRequestData(const char* buffer,unsigned int len)
	{
		m_vRequestData.assign(buffer,buffer+len);
	}

	char* getRequestData()
	{
		return &(m_vRequestData.front());
	}

	inline int getRequestSize()
	{
		return m_vRequestData.size();
	}

	void setRequestUrl(const std::string& url)
	{
		m_strUrl = url;
	}

	const std::string& getRequestUrl()
	{
		return m_strUrl;
	}

	void setSaveTargerFileAddr(const std::string& addr)
	{
		m_strTargetAddr = addr;
	}

	const std::string& getSaveTargetFileAddr()
	{
		return m_strTargetAddr;
	}

	std::string& getTag()
	{
		return m_strTag;
	}

	void setTag(const std::string& tag)
	{
		m_strTag = tag;
	}

	void setUserData(char* data)
	{
		m_pUserData = data;
	}

	const char* getUserData()
	{
		return m_pUserData;
	}

	void setHeader(std::vector<std::string> pHeaders)
	{
		m_vHeader = pHeaders;
	}
	
	std::vector<std::string> getHeader()
	{
		return m_vHeader;
	}

	void setTimeOut(long timeOut)
	{
		m_lTimeOut = timeOut;
	}

	long getTimeOut()
	{
		return m_lTimeOut;
	}

	void setTryNum(unsigned int num	)
	{
		m_iTryNum = num;
	}

	unsigned int getTryNum()
	{
		return m_iTryNum;
	}

protected:
	cHttpRequestType				m_eRequestType;
	cHttpRequestDataType			m_eRequestFileType;
	std::vector<char>				m_vRequestData; 
	std::string						m_strUrl;
	std::string						m_strTag;
	char*							m_pUserData;
	std::vector<std::string>		m_vHeader;	
	std::string						m_strTargetAddr;
	long							m_lTimeOut;
	unsigned int					m_iTryNum;
};

#endif	//_CHTTPREQUEST_H_