#include "CResponse.h"
#include "CBundle.h"

CResponse::CResponse( void )
	:m_eRespCode(RESPONSE_UNKOWN),
	m_pTarget(NULL),
	m_pBundle(NULL)
{
}

CResponse::~CResponse( void )
{
	COBRA_SAFE_DELETE(m_pTarget);
	m_eRespCode = RESPONSE_UNKOWN;
	COBRA_SAFE_DELETE(m_pBundle);
}   
