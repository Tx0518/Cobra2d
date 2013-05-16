#include "CBaseWidget.h"
#include "CPropertyHelper.h"
IMPLEMENT_DYNCREATE(CBaseWidget);
CBaseWidget::CBaseWidget(void)
{
	m_strType = "CBaseWidget";
	m_bVisible = true;
	m_bEnable = true;
	m_bkColor = ccc4(128,128,128,0);
}


CBaseWidget::~CBaseWidget(void)
{
}


 void CBaseWidget::handlePenDown(CWidgetEvent& event)
 {
	event.setHandled(true);
 }

 void CBaseWidget::handlePenUp(CWidgetEvent& event)
 {
	 event.setHandled(true);
 }

 void CBaseWidget::handlePenClick(CWidgetEvent& event)
 {
	 event.setHandled(true);
 }
 void CBaseWidget::handlePenMoveIn(CWidgetEvent& event)
 {
	 event.setHandled(true);
 }

 void CBaseWidget::handlePenMove(CWidgetEvent& event)
 {
	 event.setHandled(true);
 }

 void CBaseWidget::handlePenMoveOut(CWidgetEvent& event)
 {
	event.setHandled(true);
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

 void CBaseWidget::setRect(CCRect var)
 {
	 m_rect = var;
 }

 CCRect CBaseWidget::getRect()
 {
	 return m_rect;
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

 CCRect CBaseWidget::getChildRect(void)
 {
	 CCRect rc = this->getRect();
	 rc.origin = CCPointZero;
	 return rc;
 }

 void CBaseWidget::setBkColor(ccColor4B var)
 {
	 m_bkColor = var;
 }

 ccColor4B CBaseWidget::getBkColor()
 {
	 return m_bkColor;
 }