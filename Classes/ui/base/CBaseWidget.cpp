#include "CBaseWidget.h"
#include "CPropertyHelper.h"
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
	m_strType = "CBaseWidget";
	m_bVisible = true;
	m_bEnable = true;
	m_bkColor = CColor4B::makeC4B(128,128,128,0);
	m_zOrder  = 0;
	m_id      = 0;
	m_scale   = 1.0f;
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
	 //first hash key then set value
// 	 switch()
// 	 {
// 
// 	 }
	 //TODO
	 //hash_new<std::string>(key);
	 return true;
 }

 void CBaseWidget::draw(CGraphic* pGraphic)
 {
	 ;//do nothing here
 }

 void CBaseWidget::setID(int id)
 {
	 m_id = id;
 }

 int CBaseWidget::getID()
 {
	 return m_id;
 }

 void CBaseWidget::setType(std::string var)
 {
	 m_strType = var;
 }

 std::string CBaseWidget::getType()
 {
	 return m_strType;
 }

 void CBaseWidget::setRect(CRectange var)
 {
	 m_rect = var;
 }

 CRectange CBaseWidget::getRect()
 {
	 CRectange ret = m_rect;
	 ret.size.width *= m_scale;
	 ret.size.height *= m_scale;
	 return ret;
 }

 void CBaseWidget::setEnable(bool var)
 {
	 m_bEnable = var;
 }

 bool CBaseWidget::isEnable()
 {
	 return m_bEnable;
 }

 void CBaseWidget::setVisble(bool var)
 {
	 m_bVisible = var;
 }

 bool CBaseWidget::isVisble()
 {
	 return m_bVisible;
 }

 void CBaseWidget::setZOrder(char var)
 {
	 m_zOrder = var;
 }

 char CBaseWidget::getZOrder()
 {
	 return m_zOrder;
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

 void CBaseWidget::setBkColor(CColor4B var)
 {
	 m_bkColor = var;
 }

 CColor4B CBaseWidget::getBkColor()
 {
	 return m_bkColor;
 }


 void CBaseWidget::setScale(float var)
 {
	 m_scale = var;
 }

 float CBaseWidget::getScale()
 {
	 return m_scale;
 }