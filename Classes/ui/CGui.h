#ifndef __C_GUI_H__
#define __C_GUI_H__
/************************************************************************/
/* this class is used to port with cocos2d-x
convert touch to ui event
*/
/************************************************************************/
#include "CBaseContainer.h"
#include "IUIEventDispatcher.h"
#include "CGraphic.h"
#include "CommandHandlerMgr.h"
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
	 //////////////////////////////////////////////////////////////////////////
	 void logic(float dt);
private:
	CGraphic* m_pGraphic;
	CCommandHandlerMgr* m_pCommandHandlerMgr;
};
#endif //__C_GUI_H__
