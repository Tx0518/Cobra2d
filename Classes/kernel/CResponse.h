#ifndef _CRESPONSE_H_
#define _CRESPONSE_H_

#include "CCobraObject.h"

typedef enum
{
	RESPONSE_UNKOWN,
	RESPONSE_CREATEACTIVITY_SUCCESS,
	RESPONSE_CREATEACTIVITY_FAILURE,
	RESPONSE_CODE_SUCCESS,
	RESPONSE_CODE_ERROR,
} bResponseCode;


class CResponse : public CCobraObject
{
public:
	CResponse(void);
	virtual ~CResponse(void);

	COBRA_CREATE_PROPERTY(int,m_eRespCode,RespCode)
	COBRA_CREATE_PROPERTY(CCobraObject*,m_pTarget,RespTarget)
};

#endif