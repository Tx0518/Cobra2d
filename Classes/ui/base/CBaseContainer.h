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
	static const std::string BASE_CONTAINER_TYPE;
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
	//////////////////////////////////////////////////////////////////////////
	virtual void add(CBaseWidget* pWidget);
	virtual void add(CBaseWidget* pWidget,int x,int y);
	//this op will remove this pWidget and delete it 
	//if bDelete is true
	void remove(CBaseWidget* pWidget,bool bDelete = true);
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
	//override
	void setScale(float var);
	void setBkColor(int iColor);
	void setBkColor(CColor4B var);
	//void logic(float dt);
	//////////////////////////////////////////////////////////////////////////
	void updateContentSize(void);
protected:
	void clear(void);
	void computeContentSize(CRectange& rc,CSize& size);
	typedef std::list<CBaseWidget*> WidgetList;
	typedef std::list<CBaseWidget*>::iterator  WidgetListIter;
	typedef std::list<CBaseWidget*>::reverse_iterator  WidgetListReverseIter;
	WidgetList* m_pList;
	CBaseWidget* m_pCurrentSelWidget;
};
#endif //__C_CONTAINER_H__

