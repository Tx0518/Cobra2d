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
	m_pBkPic  = NULL;
}


CPanel::~CPanel(void)
{
	CC_SAFE_RELEASE(m_pBkPic);
}

void CPanel::draw(CGraphic* pGraphic)
{	
	//draw self
	//draw background
	pGraphic->setColor(this->getBkColor());
	if (m_pBkPic)
	{
		CRectange  rc = this->getRect();
		pGraphic->drawImage(m_pBkPic,0,0,0,0,rc.size.width,rc.size.height,this->getBkColor());
	}
	else
	{
		pGraphic->fillRectangle(this->getChildRect());
	}
	//draw children
	CBaseContainer::draw(pGraphic);
}

void CPanel::setBkPic(CCTexture2D* var)
{
	CC_SAFE_RETAIN(var);
	CC_SAFE_RELEASE(m_pBkPic);
	m_pBkPic = var;
#if 0//todo check me this may be wrong
	if (m_pBkPic)
	{
		m_contentSize = CreateCSize(m_pBkPic->getContentSize().width,m_pBkPic->getContentSize().height);
	}
#endif
}

CCTexture2D* CPanel::getBkPic()
{
	return m_pBkPic;
}
