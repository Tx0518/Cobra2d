#ifndef _CBUTTON_H_
#define _CBUTTON_H_

#include "CComponent.h"
#include "CUIEvent.h"
#include <string>

typedef enum
{
	BUTTON_DEFAULT = 1,
	BUTTON_OVER,
	BUTTON_OUT,
	BUTTON_DOWN,
	BUTTON_SELECTED,
	BUTTON_DISABLE
}cButtonState;

class CLabel;
class CSprite;

/*
	CButton
*/
class CButton : public CComponent,public CMouseClickEvent
{
public:
	static CButton* createButton(const char* normalKey,const char* selectedKey,const char* disabledKey);
	static CButton* createButton(CSprite* normalObj,CSprite* selectedObj,CSprite* disabled);
public:
	CButton(void);
	CButton(std::string label);
	virtual ~CButton(void);
	
	virtual void onRender();
	virtual void onRelease();
	virtual void onInvalidate();

	void initButton(const char* normalKey,const char* selectedKey,const char* disabledKey);
	void initButton(CSprite* normalObj,CSprite* selectedObj,CSprite* disabled);
	
	virtual bool isInRegion(const CPoint& point);
	virtual void setSelected(bool var);

	void setTouchClickEnable(bool var);

#if (COBRA_TARGET_RENDEENQINE == COBRA_RENDEENQINE_COCOS2DX)
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pvent);
#endif
	
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bDisabled,Disabeld)
	COBRA_CREATE_PROPERTY(cButtonState,m_iState,ButtonState)

protected:
	virtual void onClickHander(CComponent* sender,int tag);
protected:
	CSprite* m_pNormal;
	CSprite* m_pSelected;
	CSprite* m_pDisabled;
	CLabel* m_pLabel;
	std::string m_strLabel;
};
#endif	//_CBUTTON_H_