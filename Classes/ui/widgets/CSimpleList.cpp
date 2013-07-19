#include "CBaseContainer.h"
#include "CPanel.h"
#include "CSorllPanel.h"
#include "CSimpleAdapter.h"
#include "CSimpleList.h"
#include "CLayoutParam.h"
#include "CPushButton.h"
#include "CLabel.h"
#include "CImageWidget.h"
#include "CGraphic.h"
//////////////////////////////////////////////////////////////////////////
CListCell::CListCell()
{
	m_bCellClickAble = false;
	m_pBkPicSel = NULL;
	m_bClicked = false;
}

CListCell::~CListCell()
{
	CC_SAFE_RELEASE(m_pBkPicSel);
}



void CListCell::handlePenDown(CWidgetEvent& event)
{
	CPanel::handlePenDown(event);
	if (!event.isHandled() && m_bCellClickAble)
	{
		event.setHandled(true);
		m_bClicked = true;
	}
}

void CListCell::handlePenUp(CWidgetEvent& event)
{
	CPanel::handlePenUp(event);
	if (!event.isHandled() && m_bCellClickAble)
	{
		event.setHandled(true);
		m_bClicked = false;
	}
}

void CListCell::handlePenClick(CWidgetEvent& event)
{
	CPanel::handlePenClick(event);
	if (!event.isHandled() && m_bCellClickAble)
	{
		event.setHandled(true);
		//send cmd id
		CUICommand cmd;
		cmd.setSource(this);
		cmd.setCmdID(this->getcmdID());
		CCommandHandlerMgr::instance()->postCmd(cmd);
	}
}


void CListCell::draw(CGraphic* pGraphic)
{
	//draw self
	//draw background
	pGraphic->setColor(this->getBkColor());
	CCTexture2D* pCurrentBkPic = NULL;
	//if this cell can be clicked 
	//and is in clicked mode set the bk pic 
	if (this->m_bCellClickAble && this->m_bClicked)
	{
		pCurrentBkPic = m_pBkPicSel;
	}
	else
	{
		pCurrentBkPic = m_pBkPic;
	}
	//////////////////////////////////////////////////////////////////////////
	if (pCurrentBkPic)
	{
		CRectange  rc = this->getRect();
		pGraphic->drawImage(pCurrentBkPic,0,0,0,0,rc.size.width,rc.size.height,this->getBkColor());
	}
	else
	{
		pGraphic->fillRectangle(this->getChildRect());
	}
	//draw children
	CBaseContainer::draw(pGraphic);
}

void CListCell::setClicked(bool var)
{
	if (m_bCellClickAble)
	{
		m_bClicked = var;
	}
	else
	{
		LOG("cell can not be clicked,do nothing");
	}
}


bool CListCell::isClicked()
{
	return m_bClicked;
}

void CListCell::setBkPicSelected(CCTexture2D* var)
{
	CC_SAFE_RETAIN(var);
	CC_SAFE_RELEASE(m_pBkPicSel);
	m_pBkPicSel = var;
}

CCTexture2D* CListCell::getBkPicSelected()
{
	return m_pBkPicSel;
}
//////////////////////////////////////////////////////////////////////////
CSimpleList::CSimpleList(void)
{
	m_bCanClickCell = false;
	m_iCellCmdID    = 0;
	m_pAdapter = NULL;
	m_bOwnedAdapter = true;
	m_pCellBkNormal = NULL;
	m_pCellBkSel    = NULL;
	this->setSorllType(CSorllPanel::E_SORLL_TYPE_VERTI);
}


CSimpleList::~CSimpleList(void)
{
	this->clearAdataper();
}

bool CSimpleList::setAdataper( CSimpleAdapter* pAdapter,bool bOwnData /*= true*/ )
{
	ENTERFUNC();
	this->clearAdataper();
	m_pAdapter = pAdapter;
	m_bOwnedAdapter = bOwnData;
	this->layoutChildren();
	return true;
	LVFUNC();
}

void CSimpleList::clearAdataper(void)
{
	if (m_bOwnedAdapter)
	{
		COBRA_SAFE_DELETE(m_pAdapter);
	}
}


void CSimpleList::layoutChildren(void)
{
	ENTERFUNC();
	//////////////////////////////////////////////////////////////////////////
	if (m_pAdapter)
	{
		int iLineNumber = 0;
		int iOffsetY    = 0;
		//create a cell
		CListCell* pCell = NULL;
		CSimpleAdapter::AdapterDataIter iter = m_pAdapter->m_Data.begin();
		while(iter != m_pAdapter->m_Data.end())
		{
			pCell = new CListCell();
			if (pCell)
			{
				pCell->setCellClickAble(m_bCanClickCell);
				pCell->setcmdID(m_iCellCmdID);
				pCell->setID(iLineNumber);
				pCell->setBkPic(m_pCellBkNormal);
				pCell->setBkPicSelected(m_pCellBkSel);
				pCell->setRect(0,iOffsetY,CLayoutParam::FILL_PARENT,CLayoutParam::WRAP_CONTENT);
				//////////////////////////////////////////////////////////////////////////
				//add sub children to cell
				CSimpleAdapter::AdapterLayoutInfoIter iterLayoutInfo = m_pAdapter->m_layoutInfo.begin();
				CLayoutInfo* pLayoutInfo = NULL;
				while(iterLayoutInfo != m_pAdapter->m_layoutInfo.end())
				{
					//create a sub widget
					pLayoutInfo = *iterLayoutInfo;
					CBaseWidget* pWidget = dynamic_cast<CBaseWidget*>(CreateDynObject(pLayoutInfo->getWidgetType().c_str()));
					pWidget->setID(pLayoutInfo->getWidgetID());
					pWidget->setRect(pLayoutInfo->getWidgetRc());
					if (pWidget->getType() == CPushButton::PUSH_BTN_TYPE)
					{
						CLayoutBtnInfo* pBtnInfo = (CLayoutBtnInfo*)pLayoutInfo;
						((CPushButton*)pWidget)->setcmdID(pBtnInfo->getCmdID());
					}
					else if (pWidget->getType() == CLabel::LABEL_TYPE)
					{
						CLayoutLabelInfo* pLabelInfo = (CLayoutLabelInfo*)pLayoutInfo;
						CLabel* pLabel = (CLabel*)pWidget;
						pLabel->setTextColor(pLabelInfo->getFontColor());
						pLabel->setTxtSize(pLabelInfo->getFontSize());
						pLabel->setTxtFont(pLabelInfo->getFontName());
					}
					else if (pWidget->getType() == CImageWidget::IMAGE_WIDGET_TYPE)
					{
						;//do nothing
					}
					else
					{
						LOG("unknown info widget type = [%s]",pLayoutInfo->getWidgetType().c_str());
					}
					//////////////////////////////////////////////////////////////////////////
					pCell->add(pWidget);
					iterLayoutInfo++;
				}

				//////////////////////////////////////////////////////////////////////////
				//set parameter
				CSimpleAdapter::FromKeySetIter iterKeySet = m_pAdapter->m_from.begin();
				CSimpleAdapter::ToPropertySetIter iterToSet = m_pAdapter->m_to.begin();
				//here m_from  m_to MUST have same size
				std::string strValue = "";
				while(iterKeySet != m_pAdapter->m_from.end() && iterToSet != m_pAdapter->m_to.end())
				{
					strValue = iter->at(iterKeySet->c_str());
					CBaseWidget* pWidget = pCell->getByID(iterToSet->first);
					if (pWidget)
					{
						pWidget->setPorperty(iterToSet->second,strValue);
					}
					else
					{
						LOG("error can not find widget with id = [%d]",iterToSet->first);
					}
					iterKeySet++;
					iterToSet++;
				}
				this->add(pCell);
				iOffsetY += pCell->getContentSize().height;
				pCell = NULL;
				iter++;
			}
			else
			{
				LOG("create cell failed,may be there is no enough memory");
			}
		}

	}
	else
	{
		LOG("adapter is null,do nothing");
	}
	//////////////////////////////////////////////////////////////////////////
	LVFUNC();
}

void CSimpleList::setCellProperty( bool bCellClickAble,int iCellCmdID )
{
	m_bCanClickCell = bCellClickAble;
	m_iCellCmdID = iCellCmdID;
}

void CSimpleList::setCellBk(CCTexture2D* pPicNormal,CCTexture2D* pPicSel/* = NULL*/)
{
	m_pCellBkNormal = pPicNormal;
	m_pCellBkSel    = pPicSel;
}