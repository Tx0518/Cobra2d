#include "CBaseContainer.h"
#include "CPanel.h"
#include "CGraphic.h"
//////////////////////////////////////////////////////////////////////////
const std::string CPanel::PANEL_TYPE	    = "panel";
const std::string CPanel::PANEL_BK_PIC		= "panelBkPic";
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CPanel);
//////////////////////////////////////////////////////////////////////////
CPanel::CPanel(void)
{
	m_strType = CPanel::PANEL_TYPE;
}


CPanel::~CPanel(void)
{
}

void CPanel::draw(CGraphic* pGraphic)
{	
	//draw self
	//draw background
	pGraphic->setColor(this->getBkColor());
	pGraphic->fillRectangle(this->getChildRect());
	//draw children
	CBaseContainer::draw(pGraphic);
}