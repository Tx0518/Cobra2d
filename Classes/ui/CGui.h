#ifndef __C_GUI_H__
#define __C_GUI_H__
#include "CBaseContainer.h"
#include "IUIEventDispatcher.h"
#include "cocos2d.h"
USING_NS_CC;
/************************************************************************/
/* this class is used to port with cocos2d-x
convert touch to ui event
*/
/************************************************************************/
class CGraphic;
class CGui:public CBaseContainer,public IUIEventDispatcher,public CCTouchDelegate,public CCObject
{
public:
	CGui(int width,int height);
	~CGui(void);
	//////////////////////////////////////////////////////////////////////////
	//CCTouchDelegate
	 bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	 void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	 void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	 void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	//////////////////////////////////////////////////////////////////////////
	 //IUIEventDispatcher
	 void DispatchWidgetEvent(CWidgetEvent& event); 
	 //////////////////////////////////////////////////////////////////////////
	 void draw(void);
private:
	CGraphic* m_pGraphic;
};
#endif //__C_GUI_H__
