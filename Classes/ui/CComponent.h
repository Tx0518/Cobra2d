#ifndef _CCOMPONENT_H_
#define _CCOMPONENT_H_

#include "CSprite.h"
#include "CGeometry.h"

class CComponent;

typedef void (CComponent::*LP_CLICK_CALLBACK)(CComponent*,int tag);

typedef enum
{
	UI_BUTTON = 1,
	UI_LABLE,
	UI_TEXT,
	UI_WINDOW,
	UI_FRAME,
	UI_TEXTURE,
	UI_LIST,
	UI_SLIDER,
	UI_RADIOBOX,
	UI_CHECKBOX,
	UI_TAB
} cUIType;

/*
	CComponent
*/
class CComponent : public CSprite
{
public:
	CComponent(void);
	CComponent(CGraphics2D* texture);
	virtual ~CComponent(void);

	virtual void onRender();
	virtual void onRelease();
	virtual void onInvalidate();
	void addOnClickEventListener(LP_CLICK_CALLBACK reCallFun);
	void removeOnClickEventListener();
public:
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bIsSelected,Selected)
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bIsEnabled,Enabled)
	COBRA_CREATE_PROPERTY(CComponent*,m_pRefCom,RefComponent)
protected:
	LP_CLICK_CALLBACK m_pClickHandler;
};

#endif //_CCOMPONENT_H_