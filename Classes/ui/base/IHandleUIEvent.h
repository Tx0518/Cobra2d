#ifndef __I_HANDLE_UI_EVENT_H__
#define __I_HANDLE_UI_EVENT_H__
/************************************************************************/
/* this class is used to define the interface of ui
*/
/************************************************************************/
#include "cocos2d.h"
#include "CWidgetEvent.h"
USING_NS_CC;
class IHandleUIEvent
{
public:
	virtual void handlePenDown(CWidgetEvent& event) = 0;
	virtual void handlePenUp(CWidgetEvent& event) = 0;
	virtual void handlePenClick(CWidgetEvent& event) = 0;
	virtual void handlePenMoveIn(CWidgetEvent& event) = 0;
	virtual void handlePenMove(CWidgetEvent& event) = 0;
	virtual void handlePenMoveOut(CWidgetEvent& event) = 0;
};
#endif //__I_HANDLE_UI_EVENT_H__

