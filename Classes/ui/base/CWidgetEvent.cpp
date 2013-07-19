#include "CGeometry.h"
#include "CWidgetEvent.h"

CWidgetEvent::CWidgetEvent(CBaseWidget* pSrc,int iType)
{
	m_pSrc = pSrc;
	m_iType = iType;
	m_bHandled = false;
	m_bCanceld = false;
}

CWidgetEvent::~CWidgetEvent(void)
{
}
