#include "CComponent.h"

CComponent::CComponent( void )
	:m_pClickHandler(NULL),
	m_pRefCom(NULL)
{
}

CComponent::CComponent( CGraphics2D* texture )
	:m_pClickHandler(NULL),
	m_pRefCom(NULL)
{
}

CComponent::~CComponent( void )
{
}

void CComponent::onRender()
{
	CDisplayObject::onRender();
}

void CComponent::onRelease()
{
	COBRA_SAFE_DELETE(m_pRefCom);
}

void CComponent::onInvalidate()
{
}

void CComponent::setEnabled(bool var)
{
	m_bIsEnabled = var;
}

bool CComponent::isEnabled()
{
	return m_bIsEnabled;
}

void CComponent::setSelected(bool var)
{
	m_bIsSelected = var;
}

bool CComponent::isSelected()
{
	return m_bIsSelected;
}

void CComponent::addOnClickEventListener( LP_CLICK_CALLBACK reCallFun )
{
	m_pClickHandler = reCallFun;
}

void CComponent::removeOnClickEventListener()
{
	m_pClickHandler = NULL;
}

void CComponent::setRefComponent(CComponent* var)
{
	m_pRefCom = var;
}

CComponent* CComponent::getRefComponent()
{
	return m_pRefCom;
}