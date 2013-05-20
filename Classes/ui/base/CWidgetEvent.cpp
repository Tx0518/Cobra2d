#include "CGeometry.h"
#include "CWidgetEvent.h"


CWidgetEvent::CWidgetEvent(CBaseWidget* pSrc,int iType)
{
	m_pSrc = pSrc;
	m_iType = iType;
	m_bHandled = false;
}


CWidgetEvent::~CWidgetEvent(void)
{

}

void CWidgetEvent::setType(int var)
{
	m_iType = var;
}

int CWidgetEvent::getType()
{
	return m_iType;
}

void CWidgetEvent::setHandled(bool var)
{
	m_bHandled = var;
}

bool CWidgetEvent::isHandled()
{
	return m_bHandled;
}

void CWidgetEvent::setPt(CPoint var)
{
	m_pt = var;
}

CPoint CWidgetEvent::getPt()
{
	return m_pt;
}