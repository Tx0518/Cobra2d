#ifndef __C_CONTAINER_H__
#define __C_CONTAINER_H__
#include "CBaseWidget.h"
#include <list>
class CGraphic;
class CBaseContainer :public CBaseWidget
{
public:
	CBaseContainer(void);
	virtual ~CBaseContainer(void);
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
	//////////////////////////////////////////////////////////////////////////
	void add(CBaseWidget* pWidget);
	void add(CBaseWidget* pWidget,int x,int y);
	void remove(CBaseWidget* pWidget);
	CBaseWidget* getByID(int ID);
	CBaseWidget* getByPosition(int x,int y);
	//////////////////////////////////////////////////////////////////////////
	void handlePenDown(CWidgetEvent& event);
	void handlePenUp(CWidgetEvent& event);
	void handlePenClick(CWidgetEvent& event);
	void handlePenMoveIn(CWidgetEvent& event);
	void handlePenMove(CWidgetEvent& event);
	void handlePenMoveOut(CWidgetEvent& event);
	//////////////////////////////////////////////////////////////////////////
protected:
	void clear(void);
	typedef std::list<CBaseWidget*> WidgetList;
	typedef std::list<CBaseWidget*>::iterator  WidgetListIter;
	typedef std::list<CBaseWidget*>::reverse_iterator  WidgetListReverseIter;
	WidgetList* m_pList;
	CBaseWidget* m_pCurrentSelWidget;
};
#endif //__C_CONTAINER_H__

