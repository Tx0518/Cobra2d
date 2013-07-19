#ifndef __C_PANEL_H__
#define __C_PANEL_H__ 
/************************************************************************/
/* this file is used to implement a simple panel widget
you can add child widget to it
example:
CPanel* pPanel = new CPanel();
pPanel->setBkColor(CreateCColor(0,255,0,255));
pPanel->setRect(CreateCRect(200,200,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
*/
/************************************************************************/
#include "cocos2d.h"
USING_NS_CC;
class CBaseContainer;
class CPanel:public CBaseContainer
{
public:
	DECLARE_DYNCREATE(CPanel);
	//////////////////////////////////////////////////////////////////////////
	CPanel(void);
	virtual ~CPanel(void);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//property
	static const std::string PANEL_TYPE;
	static const std::string PANEL_BK_PIC;
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(CCTexture2D*,m_pBkPic,BkPic)
};
#endif//__C_PANEL_H__
