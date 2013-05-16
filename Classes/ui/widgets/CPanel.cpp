#include "CPanel.h"
#include "CGraphic.h"

CPanel::CPanel(void)
{
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