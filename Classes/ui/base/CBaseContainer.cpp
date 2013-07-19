#include "CGeometry.h"
#include "CBaseWidget.h"
#include "CBaseContainer.h"
#include "CGraphic.h"
//////////////////////////////////////////////////////////////////////////
const std::string CBaseContainer::BASE_CONTAINER_TYPE = "CBaseContainer";
//////////////////////////////////////////////////////////////////////////
typedef struct _stCmpBaseWidget 
{
	bool operator() (CBaseWidget* one,CBaseWidget* two) 
	{ 
		return one->getZOrder() < two->getZOrder();
	}
}CCmpBaseWidget ;



CBaseContainer::CBaseContainer(void)
{
	m_pList = new WidgetList();
	m_pCurrentSelWidget = NULL;
	m_strType = BASE_CONTAINER_TYPE;
}


CBaseContainer::~CBaseContainer(void)
{
	clear();
	delete m_pList;
	m_pList = NULL;
}

void CBaseContainer::draw(CGraphic* pGraphic)
{
	COBRA_ASSERT(pGraphic != NULL,"in function draw pGraphic can not be null");
	pGraphic->pushClipArea(this->getChildRect());

 	WidgetListIter iter;
	CRectange rc;
 	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
 	{
 		if ((*iter)->isVisble())
 		{
			rc = (*iter)->getRect();
			//if can not been seen just continue
			if (rc.size.height + rc.origin.y <= 0)
			{
				continue;
			}

			if (rc.origin.y >= this->getRect().size.height)
			{
				continue;
			}

 			pGraphic->pushClipArea((*iter)->getRect());
 			(*iter)->draw(pGraphic);
 			pGraphic->popClipArea();
 		}
 	}

	pGraphic->popClipArea();
}

void CBaseContainer::add(CBaseWidget* pWidget)
{
	COBRA_ASSERT(pWidget != NULL,"pWidget can not be null");
	COBRA_ASSERT(pWidget->getParent() == NULL,"you can not add a widget who already has a parent");
	pWidget->setParent(this);
	//invoke the callback which give a chance to do something when this widget is added to it's parent
	pWidget->onAdd(this);
	m_pList->push_back(pWidget);
	CCmpBaseWidget cmp;
	m_pList->sort(cmp);
}

void CBaseContainer::add(CBaseWidget* pWidget,int x,int y)
{
	CRectange rc = pWidget->getRect();
	rc.origin.x = x;
	rc.origin.y = y;
	pWidget->setRect(rc);
	this->add(pWidget);
}

void CBaseContainer::remove(CBaseWidget* pWidget,bool bDelete)
{
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		if ((*iter) == pWidget)
		{
			m_pList->erase(iter);
			if (bDelete)
			{
				delete (*iter);
			}
			else
			{
				(*iter)->setParent(NULL);
			}
			break;
		}
	}
}

CBaseWidget* CBaseContainer::getByID(int ID)
{
	CBaseWidget* ret = NULL;
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		if ((*iter)->getID() == ID)
		{
			ret = *iter;
			break;
		}
	}
	return ret;
}

CBaseWidget* CBaseContainer::getByPosition(int x,int y)
{
	CBaseWidget* ret = NULL;
 	CRectange rc = this->getRect();
 	if (rc.containsPoint(CreateCPoint(x,y)))
 	{
 		//find the target
 		WidgetListReverseIter iter;
 		for (iter = m_pList->rbegin(); iter != m_pList->rend(); iter++)
 		{
 			if ((*iter)->isVisble() && (*iter)->getRect().containsPoint(CreateCPoint(x,y)))
 			{
 				ret = (*iter);
 				break;
 			}
 		}
 	}
 	else
 	{
 		;//do nothing
 	}
	return ret;

}


void CBaseContainer::clear(void)
{
	CBaseWidget* temp = NULL;
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		temp = *iter;
		COBRA_SAFE_DELETE(temp);
	}
	m_pList->clear();
}
//////////////////////////////////////////////////////////////////////////
void CBaseContainer::setScale(float var)
{
	CBaseWidget* temp = NULL;
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		temp = *iter;
		temp->setScale(var);
	}
	CBaseWidget::setScale(var);
}

 void CBaseContainer::setBkColor(CColor4B var)
 {
	m_bkColor = var;
	CBaseWidget* temp = NULL;
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		temp = *iter;
		temp->setBkColor(var);
	}
 }

 void CBaseContainer::setBkColor(int iColor)
 {
	 CColor4B tempColor = CreateCColor(255,255,255,255);
	 tempColor.r = (iColor >> 24) & 0xff;
	 tempColor.g = (iColor >> 16) & 0xff;
	 tempColor.b = (iColor >> 8) & 0xff;
	 tempColor.a = iColor & 0xff;
	 this->setBkColor(tempColor);
 }
//////////////////////////////////////////////////////////////////////////
void CBaseContainer::handlePenDown(CWidgetEvent& event)
{
	if (this->getChildRect().containsPoint(event.getPt()))
	{
		WidgetListReverseIter iter = m_pList->rbegin();
		CBaseWidget* pTemp = NULL;
		while(iter != m_pList->rend())
		{
			pTemp = *iter;
			//convert pt to node space
			CPoint ptTemp = event.getPt();
			ptTemp = pTemp->converToNodeSpace(ptTemp);
			if (pTemp->isEnable() && pTemp->getChildRect().containsPoint(ptTemp))
			{
				event.setPt(ptTemp);
				pTemp->handlePenDown(event);
				if (event.isHandled())
				{
					m_pCurrentSelWidget = pTemp;
				}
				break;
			}
			iter++;

		}
	}
}

void CBaseContainer::handlePenUp(CWidgetEvent& event)
{
	if (m_pCurrentSelWidget)
	{
		WidgetListReverseIter iter = m_pList->rbegin();
		CBaseWidget* pTemp = NULL;
		while(iter != m_pList->rend())
		{
			pTemp = *iter;
			CPoint ptTemp = event.getPt();
			ptTemp = pTemp->converToNodeSpace(ptTemp);
			if (pTemp->getChildRect().containsPoint(ptTemp))
			{
				break;
			}
			iter++;
		}

		if (pTemp == m_pCurrentSelWidget)
		{
			CPoint ptTemp = event.getPt();
			ptTemp = pTemp->converToNodeSpace(ptTemp);
			event.setPt(ptTemp);
			m_pCurrentSelWidget->handlePenUp(event);
			//if this event is canceled do nothing
			//else send a click event to the current selected widget
			if (!event.isCanceled())
			{
				event.setHandled(false);
				event.setType(CWidgetEvent::W_EVENT_PEN_CLICK);
				m_pCurrentSelWidget->handlePenClick(event);
			}
		}
		else
		{
			m_pCurrentSelWidget->handlePenUp(event);

		}
		m_pCurrentSelWidget = NULL;
	}
}

void CBaseContainer::handlePenClick(CWidgetEvent& event)
{
	if (m_pCurrentSelWidget)
	{
		CPoint ptTemp = event.getPt();
		ptTemp = m_pCurrentSelWidget->converToNodeSpace(ptTemp);
		event.setPt(ptTemp);
		m_pCurrentSelWidget->handlePenClick(event);
	}
}

void CBaseContainer::handlePenMoveIn(CWidgetEvent& event)
{
	;//TODO
}

void CBaseContainer::handlePenMove(CWidgetEvent& event)
{
	if (m_pCurrentSelWidget)
	{
		CPoint ptTemp = event.getPt();
		ptTemp = m_pCurrentSelWidget->converToNodeSpace(ptTemp);
		event.setPt(ptTemp);
		m_pCurrentSelWidget->handlePenMove(event);
	}
}

void CBaseContainer::handlePenMoveOut(CWidgetEvent& event)
{
	;//TODO
}

void CBaseContainer::computeContentSize(CRectange& rc,CSize& size)
{
	CSize tempsize;
	tempsize.width = comax(rc.size.width,size.width);
	tempsize.height = comax(rc.size.height,size.height);
	m_contentSize.width = comax(rc.origin.x + tempsize.width,m_contentSize.width);
	m_contentSize.height = comax(rc.origin.y + tempsize.height,m_contentSize.height);
}

void CBaseContainer::updateContentSize(void)
{
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		this->computeContentSize((*iter)->getRect(),(*iter)->getContentSize());
	}
}
// void CBaseContainer::logic(float dt)
// {
// 	WidgetListReverseIter iter = m_pList->rbegin();
// 	CBaseWidget* pTemp = NULL;
// 	while(iter != m_pList->rend())
// 	{
// 		(*iter)->logic(dt);
// 		iter++;
// 	}
// }
//////////////////////////////////////////////////////////////////////////