#ifndef __C_BASE_WIDGET_H__
#define __C_BASE_WIDGET_H__
#include "IHandleUIEvent.h"
#include "IUILoader.h"
#include "CDynObj.h"
#include "CMarcos.h"
class CGraphic;
class CPoint;
class CRectange;
class CActionInterval;
class CBaseWidget:public IHandleUIEvent,public IUILoader,public CDynObj
{
public:
	DECLARE_DYNCREATE(CBaseWidget);
	CBaseWidget(void);
	virtual ~CBaseWidget(void);

	static const std::string BASE_WIDGET_TYPE;
	//////////////////////////////////////////////////////////////////////////
	//property
	static const std::string RECT;
	static const std::string TYPE;
	static const std::string BK_COLOR;
	static const std::string VISIBLE;
	static const std::string ENABLE;
	//////////////////////////////////////////////////////////////////////////
	//do some logic in ui thread
	virtual void logic(float dt);
	//////////////////////////////////////////////////////////////////////////
	//IHandleUIEvent
	virtual void handlePenDown(CWidgetEvent& event);
	virtual void handlePenUp(CWidgetEvent& event);
	virtual void handlePenClick(CWidgetEvent& event);
	virtual void handlePenMoveIn(CWidgetEvent& event);
	virtual void handlePenMove(CWidgetEvent& event);
	virtual void handlePenMoveOut(CWidgetEvent& event);
	///////////////////////////////////////////////////////////////////////////
	//IUILoader
	bool load(std::string& str);
	bool setPorperty(const std::string& key,const std::string& strvalue);
	/////////////////////////////////////////////////////////////////////////
	//draw function
	virtual void draw(CGraphic* pGraphic);
	//////////////////////////////////////////////////////////////////////////
	//invoked when this widget be add into a parent
	virtual void onAdd(CBaseWidget* pParent);
	//////////////////////////////////////////////////////////////////////////
	//update content size 
	virtual void updateContentSize(void);
	//////////////////////////////////////////////////////////////////////////
	void runAction(CActionInterval* pAction);
	//////////////////////////////////////////////////////////////////////////
	CRectange getChildRect(void);
	CPoint converToNodeSpace(const CPoint& pt);
	//////////////////////////////////////////////////////////////////////////
	//
	void setRect(int x,int y,int width,int height);
	void setBkColor(int iColor);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY(int,m_id,ID);//id
	COBRA_CREATE_PROPERTY(std::string,m_strType,Type);//type
	COBRA_CREATE_PROPERTY(CBaseWidget*,m_pParent,Parent);//hold a pointer of parent
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(CRectange,m_rect,Rect);//rect
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bEnable,Enable);//bEnable
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bVisible,Visble);//bVisble
	COBRA_CREATE_PROPERTY(char,m_zOrder,ZOrder);//ZOrder  [-255,255] the widget draw first if it's value is smaller than others'
	COBRA_CREATE_PROPERTY(CColor4B,m_bkColor,BkColor);//background color
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(float,m_scale,Scale);//scale factor
	//if when user set rect with WRAP_CONTENT or fill_parent
	//this variable can help to compute the right size
	//other cases it just hold the rectangle's size property
	COBRA_CREATE_PROPERTY(CSize,m_contentSize,ContentSize);
public:
	//bool operator<(const CBaseWidget& other) const;
	bool   m_bDirty;
private:
	void updateContentSizeInner(void);
};

#endif //__C_BASE_WIDGET_H__