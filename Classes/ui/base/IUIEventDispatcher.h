#ifndef __I_UI_EVENT_DISPATCHER_H__
#define __I_UI_EVENT_DISPATCHER_H__
/************************************************************************/
/* this file is used for define interface to dispatch ui  event
*/
/************************************************************************/
#include "CWidgetEvent.h"
class IUIEventDispatcher
{
	virtual void DispatchWidgetEvent(CWidgetEvent& event) = 0;
};
#endif //__I_UI_EVENT_DISPATCHER_H__