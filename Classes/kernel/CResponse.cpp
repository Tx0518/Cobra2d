#include "CResponse.h"

CResponse::CResponse( void )
{
}

CResponse::~CResponse( void )
{
}   

void CResponse::setRespCode(int var)
{
	m_eRespCode = var;
}

int CResponse::getRespCode()
{
	return m_eRespCode;
}

void CResponse::setRespTarget(CCobraObject* var)
{
	m_pTarget = var;
}

CCobraObject* CResponse::getRespTarget()
{
	return m_pTarget;
}
