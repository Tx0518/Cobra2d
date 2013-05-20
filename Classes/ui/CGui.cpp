#include "CGui.h"
CGui::CGui(int width,int height)
{
	m_pGraphic = CGraphic::instance();
	m_pGraphic->setTargetPlane(width,height);
	//////////////////////////////////////////////////////////////////////////
	m_pCommandHandlerMgr =  CCommandHandlerMgr::instance();
}


CGui::~CGui(void)
{
	ENTERFUNC();
	LVFUNC();
}

//////////////////////////////////////////////////////////////////////////
bool CGui::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	bool ret = false;
	CCPoint ptCococs2dx = pTouch->getLocationInView();
	CPoint  touchLocation;
	touchLocation.x = ptCococs2dx.x;
	touchLocation.y = ptCococs2dx.y;
	touchLocation = this->converToNodeSpace(touchLocation);
	if (this->getChildRect().containsPoint(touchLocation))
	{
		CWidgetEvent event(this,CWidgetEvent::W_EVENT_PEN_DOWN);
		event.setPt(touchLocation);
		this->DispatchWidgetEvent(event);
		ret = true;
	}	
	return ret;
}

void CGui::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint ptCococs2dx = pTouch->getLocationInView();
	CPoint  touchLocation;
	touchLocation.x = ptCococs2dx.x;
	touchLocation.y = ptCococs2dx.y;
	CWidgetEvent event(this,CWidgetEvent::W_EVENT_PEN_DOWN);
	event.setPt(touchLocation);
	this->DispatchWidgetEvent(event);
}

void CGui::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint ptCococs2dx = pTouch->getLocationInView();
	CPoint  touchLocation;
	touchLocation.x = ptCococs2dx.x;
	touchLocation.y = ptCococs2dx.y;
	touchLocation = this->converToNodeSpace(touchLocation);
	CWidgetEvent event(this,CWidgetEvent::W_EVENT_PEN_UP);
	event.setPt(touchLocation);
	this->DispatchWidgetEvent(event);
}

void CGui::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	;//do nothing
}
//////////////////////////////////////////////////////////////////////////
void CGui::DispatchWidgetEvent(CWidgetEvent& event)
{
	//TODO dispatch event to targets
	switch (event.getType())
	{
	case CWidgetEvent::W_EVENT_PEN_DOWN:
		{
			this->handlePenDown(event);
			break;
		}
	case CWidgetEvent::W_EVENT_PEN_UP:
		{
			this->handlePenUp(event);
			break;
		}
	case CWidgetEvent::W_EVENT_PEN_MOVE_IN:
		{
			this->handlePenMoveIn(event);
			break;
		}
	case CWidgetEvent::W_EVENT_PEN_MOVE:
		{
			this->handlePenMove(event);
			break;
		}
	case CWidgetEvent::W_EVENT_PEN_DOWN_OUT:
		{
			this->handlePenMoveOut(event);
			break;
		}
	default:
		{
			LOG("unknown event type encountered [%d]",event.getType());
			break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CGui::draw(void)
{
	m_pGraphic->beginDraw();
	m_pGraphic->pushClipArea(this->getRect());
	//draw background
	m_pGraphic->setColor(this->getBkColor());
	m_pGraphic->fillRectangle(this->getChildRect());
	//draw children
	CBaseContainer::draw(m_pGraphic);
	m_pGraphic->popClipArea();	
	m_pGraphic->endDraw();
}


 void CGui::logic(float dt)
 {
	m_pCommandHandlerMgr->handleCmd();
 }