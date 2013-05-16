#include "CBaseContainer.h"
#include "CGraphic.h"

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
 	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
 	{
 		if ((*iter)->isVisble())
 		{
 			pGraphic->pushClipArea((*iter)->getRect());
 			(*iter)->draw(pGraphic);
 			pGraphic->popClipArea();
 		}
 	}

	pGraphic->popClipArea();
}

void CBaseContainer::add(CBaseWidget* pWidget)
{
	m_pList->push_back(pWidget);
	m_pList->sort();
}

void CBaseContainer::add(CBaseWidget* pWidget,int x,int y)
{
	CCRect rc = pWidget->getRect();
	rc.origin.x = x;
	rc.origin.y = y;
	pWidget->setRect(rc);
	this->add(pWidget);
}

void CBaseContainer::remove(CBaseWidget* pWidget)
{
	WidgetListIter iter;
	for (iter = m_pList->begin(); iter != m_pList->end(); iter++)
	{
		if ((*iter) == pWidget)
		{
			m_pList->erase(iter);
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
 	CCRect rc = this->getRect();
 	if (rc.containsPoint(ccp(x,y)))
 	{
 		//find the target
 		WidgetListReverseIter iter;
 		for (iter = m_pList->rbegin(); iter != m_pList->rend(); iter++)
 		{
 			if ((*iter)->isVisble() && (*iter)->getRect().containsPoint(ccp(x,y)))
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
void CBaseContainer::handlePenDown(CWidgetEvent& event)
{
	if (this->getRect().containsPoint(event.getPt()))
	{
		WidgetListReverseIter iter = m_pList->rbegin();
		CBaseWidget* pTemp = NULL;
		CCPoint ptTemp = event.getPt();
		while(iter != m_pList->rend())
		{
			pTemp = *iter;
			if (pTemp->getRect().containsPoint(ptTemp))
			{
				pTemp->handlePenDown(event);
			}
			iter++;
			if (event.isHandled())
			{
				m_pCurrentSelWidget = pTemp;
				break;
			}
		}
	}
}

void CBaseContainer::handlePenUp(CWidgetEvent& event)
{
	if (m_pCurrentSelWidget)
	{
		WidgetListReverseIter iter = m_pList->rbegin();
		CBaseWidget* pTemp = NULL;
		CCPoint ptTemp = event.getPt();
		while(iter != m_pList->rend())
		{
			pTemp = *iter;
			if (pTemp->getRect().containsPoint(ptTemp))
			{
				break;
			}
			iter++;
		}

		if (pTemp == m_pCurrentSelWidget)
		{
			m_pCurrentSelWidget->handlePenUp(event);
			event.setHandled(false);
			event.setType(CWidgetEvent::W_EVENT_PEN_CLICK);
			m_pCurrentSelWidget->handlePenClick(event);
		}
		else
		{
			m_pCurrentSelWidget->handlePenUp(event);
		}
	}
}

void CBaseContainer::handlePenClick(CWidgetEvent& event)
{
	if (m_pCurrentSelWidget)
	{
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
		m_pCurrentSelWidget->handlePenMove(event);
	}
}

void CBaseContainer::handlePenMoveOut(CWidgetEvent& event)
{
	;//TODO
}
//////////////////////////////////////////////////////////////////////////