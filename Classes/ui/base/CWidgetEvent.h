#ifndef __C_WIDGET_EVENT_H__
#define __C_WIDGET_EVENT_H__
#include "CMarcos.h"
#include "CGeometry.h"
class CBaseWidget;
class CWidgetEvent
{
public:
	enum
	{
		W_EVENT_PEN_DOWN,
		W_EVENT_PEN_UP,
		W_EVENT_PEN_CLICK,
		W_EVENT_PEN_MOVE_IN,
		W_EVENT_PEN_MOVE,
		W_EVENT_PEN_DOWN_OUT
	};
	CWidgetEvent(CBaseWidget* pSrc,int iType);
	~CWidgetEvent(void);

	COBRA_CREATE_PROPERTY_BY_BOOL(m_bHandled,Handled);
	COBRA_CREATE_PROPERTY(CPoint,m_pt,Pt);
	COBRA_CREATE_PROPERTY(int,m_iType,Type);
private:
	CBaseWidget* m_pSrc;
};
#endif //__C_WIDGET_EVENT_H__
