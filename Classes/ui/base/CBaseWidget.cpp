#include "CommandHandlerMgr.h"
#include "CActionInterval.h"
#include "CBaseWidget.h"
#include "CPropertyHelper.h"
#include "CGraphic.h"
#include "CLayoutParam.h"
//////////////////////////////////////////////////////////////////////////
const std::string CBaseWidget::BASE_WIDGET_TYPE = "CBaseWidget";
//////////////////////////////////////////////////////////////////////////
const std::string CBaseWidget::RECT			= "rect";
const std::string CBaseWidget::TYPE			= "type";
const std::string CBaseWidget::BK_COLOR		= "bkColor";
const std::string CBaseWidget::VISIBLE		= "visible";
const std::string CBaseWidget::ENABLE		= "enable";
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CBaseWidget);
CBaseWidget::CBaseWidget(void)
{
	m_strType = CBaseWidget::BASE_WIDGET_TYPE;
	m_bVisible = true;
	m_bEnable = true;
	m_bkColor = CColor4B::makeC4B(255,255,255,255);
	m_zOrder  = 0;
	m_id      = 0;
	m_scale   = 1.0f;
	m_contentSize = CreateCSize(0,0);
	m_pParent = NULL;
	m_bDirty  = true;
}


CBaseWidget::~CBaseWidget(void)
{
}

void CBaseWidget::logic(float dt)
{
	;//do nothing here
}

 void CBaseWidget::handlePenDown(CWidgetEvent& event)
 {
	
 }

 void CBaseWidget::handlePenUp(CWidgetEvent& event)
 {
	 
 }

 void CBaseWidget::handlePenClick(CWidgetEvent& event)
 {
	 
 }
 void CBaseWidget::handlePenMoveIn(CWidgetEvent& event)
 {
	
 }

 void CBaseWidget::handlePenMove(CWidgetEvent& event)
 {
	 
 }

 void CBaseWidget::handlePenMoveOut(CWidgetEvent& event)
 {
	
 }

 bool CBaseWidget::load(std::string& str)
 {
	 //parser the str
	 //and create widget
	 return true;
 }

 bool CBaseWidget::setPorperty(const std::string& key,const std::string& strvalue)
 {
	 bool ret = true;
	 do 
	 {
		 if (key == CBaseWidget::RECT)
		 {
			 this->setRect(CPropertyHelper::stringToRect(strvalue));
		 }
		 else if (key == CBaseWidget::BK_COLOR)
		 {
			 this->setBkColor(CPropertyHelper::stringToInt(strvalue));
		 }
		 else
		 {
			 ret = false;//do nothing
		 }
	 } while (0);

	 return ret;
 }

 void CBaseWidget::draw(CGraphic* pGraphic)
 {
	 ;//do nothing here
	 pGraphic->drawRectangle(this->getChildRect());
 }


void CBaseWidget::onAdd(CBaseWidget* pParent)
 {
	 ;//do nothing
 }

 void CBaseWidget::setRect(CRectange var)
 {
	 m_rect = var;
	 if (0 == m_contentSize.width && 0 == m_contentSize.height)
	 {
		this->setContentSize(m_rect.size);
	 }
 }


 void CBaseWidget::setRect(int x,int y,int width,int height)
 {
	 m_rect = CreateCRect(x,y,width,height);
	 if (0 == m_contentSize.width && 0 == m_contentSize.height)
	 {
		 this->setContentSize(m_rect.size);
	 }
 }


 CRectange CBaseWidget::getRect()
 {
	 this->updateContentSizeInner();
	 CRectange ret = m_rect;
	 ret.size.width *= m_scale;
	 ret.size.height *= m_scale;
	 return ret;
 }


 CRectange CBaseWidget::getChildRect(void)
 {
	 CRectange rc = this->getRect();
	 rc.origin = PointZero;
	 return rc;
 }

 CPoint CBaseWidget::converToNodeSpace(const CPoint& pt)
 {
	 CPoint ret = pt;
	 ret.x -= m_rect.origin.x;
	 ret.y -= m_rect.origin.y;
	 return ret;
 }

 void CBaseWidget::setBkColor(int iColor)
 {
	 CColor4B tempColor = CreateCColor(255,255,255,255);
	 tempColor.r = (iColor >> 24) & 0xff;
	 tempColor.g = (iColor >> 16) & 0xff;
	 tempColor.b = (iColor >> 8) & 0xff;
	 tempColor.a = iColor & 0xff;
	 this->setBkColor(tempColor);
 }

 void CBaseWidget::setScale(float var)
 {
	 m_scale = var;
	 m_bDirty = true;
 }

 float CBaseWidget::getScale()
 {
	 return m_scale;
 }

 void CBaseWidget::updateContentSize(void)
 {
	 ;//do nothing here
 }

 void CBaseWidget::updateContentSizeInner(void)
 {
	 if (m_bDirty)
	 {
		 this->updateContentSize();
		 do
		 {
			 if (CLayoutParam::WRAP_CONTENT == m_rect.size.width)
			 {
				 m_rect.size.width = m_contentSize.width;
			 }

			 if (CLayoutParam::WRAP_CONTENT == m_rect.size.height)
			 {
				 m_rect.size.height = m_contentSize.height;
			 }

			 if (CLayoutParam::FILL_PARENT == m_rect.size.width)
			 {
				 CBaseWidget* pParent = this->getParent();
				 m_contentSize.width = pParent->getContentSize().width;
				 m_rect.size.width = m_contentSize.width;
			 }

			 if (CLayoutParam::FILL_PARENT == m_rect.size.height)
			 {
				 CBaseWidget* pParent = this->getParent();
				 m_contentSize.height = pParent->getContentSize().height;
				 m_rect.size.height = m_contentSize.height;
			 }
		 }while(0);
		 m_bDirty = false;
	 }
 }

 void CBaseWidget::runAction(CActionInterval* pAction)
 {
	 pAction->startWidthTarget(this);
 }
