#include "CButton.h"
#include "CSprite.h"
#include "CLabel.h"

CButton::CButton( void )
	:m_strLabel("")
{
}

CButton::CButton(std::string label)
	:m_strLabel(label)
{
}

CButton::~CButton(void)
{

}

void CButton::onRender()
{
}

void CButton::onRelease()
{
}

void CButton::onInvalidate()
{
}

void CButton::setButtonState(cButtonState var)
{
	m_iState = var;
}

cButtonState CButton::getButtonState()
{
	return m_iState;
}

void CButton::setDisabeld(bool var)
{
	m_iState =(var == true)?BUTTON_DISABLE:BUTTON_DEFAULT;
	onInvalidate();
}

bool CButton::isDisabeld()
{
	return m_bDisabled;
}

bool CButton::isInRegion( const CPoint& point )
{
	CRectange conRect;
	conRect = UI::assembleToRectange(m_pNormal->convertToWorldSpace(ccp(0,0)),m_pNormal->getContentSize());
	return conRect.containsPoint(point);
}

void CButton::onClickHander( CComponent* sender,int tag )
{
	if(m_pClickHandler != NULL)
		(this->*m_pClickHandler)(sender,tag);
}

#if (COBRA_TARGET_RENDEENQINE == COBRA_RENDEENQINE_COCOS2DX)
bool CButton::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_iState == BUTTON_DISABLE) return false;
	if(isInRegion(UI::convertToPoint(pTouch->getLocation())))
	{
		setSelected(true);
		return true;
	}
	return false;
}

void CButton::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	//do nothing
}

void CButton::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_iState == BUTTON_DISABLE) return;
	setSelected(false);
	onClickHander(this,this->getObjectID());
	CCLOG("ccTouchEnded");
}

#endif

void CButton::setSelected( bool var )
{
	m_bIsSelected = var;
	m_iState = (m_bIsSelected == true)?BUTTON_SELECTED:BUTTON_DEFAULT;
	onInvalidate();
}

void CButton::setTouchClickEnable( bool var )
{
#if (COBRA_TARGET_RENDEENQINE == COBRA_RENDEENQINE_COCOS2DX)
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,rand() * 10,false);
#endif
}
