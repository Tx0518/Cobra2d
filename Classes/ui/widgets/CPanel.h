#ifndef __C_PANEL_H__
#define __C_PANEL_H__ 
#include "CBaseContainer.h"
class CPanel:public CBaseContainer
{
public:
	CPanel(void);
	virtual ~CPanel(void);
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
};
#endif//__C_PANEL_H__
