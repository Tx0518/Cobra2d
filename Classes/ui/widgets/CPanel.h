#ifndef __C_PANEL_H__
#define __C_PANEL_H__ 
/************************************************************************/
/* this file is used to implement a simple panel widget
you can add child widget to it
*/
/************************************************************************/
class CBaseContainer;
class CPanel:public CBaseContainer
{
public:
	DECLARE_DYNCREATE(CPanel);
	//////////////////////////////////////////////////////////////////////////
	CPanel(void);
	virtual ~CPanel(void);
	//////////////////////////////////////////////////////////////////////////
	//property
	static const std::string PANEL_TYPE;
	static const std::string PANEL_BK_PIC;
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
};
#endif//__C_PANEL_H__
