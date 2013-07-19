#include "CBaseContainer.h"
#include "CPanel.h"
#include "CSorllPanel.h"
#include "CLinearLayout.h"


CLinearLayout::CLinearLayout(void)
{
	 m_bLayoutDone = false;
	//default is horizontal
	 m_iOrientation  = HORIZONTAL;
	 m_iGravityType  = 0;
	 m_iLeftPadding  = 0;
	 m_iRightPadding = 0;
	 m_iTopPadding   = 0;
	 m_iBottomPadding = 0;
}


CLinearLayout::~CLinearLayout(void)
{

}

void CLinearLayout::onAdd(CBaseWidget* pParent)
{
	COBRA_ASSERT(pParent != NULL,"parent can not be null");
	this->doLayOut();
}

void CLinearLayout::setOrientation( int iOrientation )
{
	m_iOrientation = iOrientation;
}

void CLinearLayout::setGravityType(int iGravityType)
{
	m_iGravityType = iGravityType;
}

void CLinearLayout::setPadding( int iLeft,int iTop,int iRight,int iBottom )
{
	m_iLeftPadding = iLeft;
	m_iTopPadding  = iTop;
	m_iRightPadding = iRight;
	m_iBottomPadding = iBottom;
}

void CLinearLayout::doLayOut( void )
{
	if (!m_bLayoutDone)
	{
		m_bLayoutDone  = true;
		CRectange rcThis = this->getRect();
		int iCurrentXOffset = m_iLeftPadding;
		int iCurrentYOffset = m_iTopPadding;
		float fTotalWidth = 0;
		float fTotalHeight = 0;

		WidgetListIter iter = m_pList->begin();
		while(iter != m_pList->end())
		{
			fTotalWidth += (*iter)->getContentSize().width;
			fTotalHeight += (*iter)->getContentSize().height;
			iter++;
		}

		switch(m_iGravityType)
		{
		case LINEAR_HORI_GRAVITY_CENTER:
			{//gravity center compute the left and right padding 
			 //ignore the passed value
				m_iLeftPadding = (rcThis.size.width - fTotalWidth)/2;
				m_iRightPadding = m_iLeftPadding;
				break;
			}
		default:
			{//add other gravity type here TODO
				break;
			}
		}

		//Horizontal
		int iIntervalHorizontal = 0;
		//VERTICAL
		int iIntervalVertical = 0;
		if (m_pList->size() > 1)
		{
			iIntervalHorizontal = (rcThis.size.width - m_iLeftPadding - m_iRightPadding - fTotalWidth)/(m_pList->size() - 1);
			iIntervalVertical   = (rcThis.size.height - m_iTopPadding - m_iBottomPadding - fTotalHeight)/(m_pList->size() - 1);  
		}
		

		iIntervalHorizontal = comax(iIntervalHorizontal,0);
		iIntervalVertical   = comax(iIntervalVertical,0);
		//calculate
		CBaseWidget* pWidget = NULL;
		
		CRectange rcTemp;
		iter = m_pList->begin();
		while(iter != m_pList->end())
		{
			pWidget = *iter;
			if (pWidget)
			{
				switch(m_iOrientation)
				{
				case HORIZONTAL:
					{
						rcTemp = pWidget->getRect();
						//update x offset and y offset
						//if the current add widget is outer of parent
						//move to next line
#if 1
						if (iCurrentXOffset + rcTemp.size.width + iIntervalHorizontal > rcThis.size.width && m_pList->size() > 1)
						{
							iCurrentXOffset = m_iLeftPadding;
							iCurrentYOffset += rcTemp.size.height + iIntervalVertical;
							//update x,y position
							rcTemp.origin.x = iCurrentXOffset;
							rcTemp.origin.y = iCurrentYOffset;
						}
						else
#endif
						{//add this widget here
							//update x,y position
							rcTemp.origin.x = iCurrentXOffset;
							rcTemp.origin.y = iCurrentYOffset;
							iCurrentXOffset += rcTemp.size.width + iIntervalHorizontal;
						}
						pWidget->setRect(rcTemp);
						break;
					}
				case VERTICAL:
					{
						rcTemp = pWidget->getRect();
						rcTemp.origin.x = iCurrentXOffset;
						rcTemp.origin.y = iCurrentYOffset;
						pWidget->setRect(rcTemp);
						iCurrentYOffset += rcTemp.size.height;
						break;
					}
				default:
					{
						LOG("unknown orientation = [%d]",m_iOrientation);
						break;
					}
				}
			}
			iter++;
		}

		//update cursor for the reason that the layout changes
		iter = m_pList->begin();
		while(iter != m_pList->end())
		{
			pWidget = *iter;
			if (pWidget)
			{
				this->updateCursor(pWidget);
			}
			iter++;
		}	
	}
}