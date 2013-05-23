#include "CBaseWidget.h"
#include "cocos2d.h"
USING_NS_CC;
#include "CPushButton.h"
#include "CGraphic.h"
#include "CommandHandlerMgr.h"
//////////////////////////////////////////////////////////////////////////
 const std::string CPushButton::PUSH_BTN_TYPE = "btn";
 const std::string CPushButton::PB_NORMAL_PIC = "btnNormalPic";
 const std::string CPushButton::PB_CLICK_PIC  = "btnSelPic";
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CPushButton);
//////////////////////////////////////////////////////////////////////////
CPushButton::CPushButton(void)
{
	m_strType     = CPushButton::PUSH_BTN_TYPE;
	m_pPicNormal  = NULL;
	m_pPicClick   = NULL;
	m_pCurrentPic = NULL;
	m_cmdID       = 0;//
}


CPushButton::~CPushButton(void)
{

}

void CGAffineToGL2(const CCAffineTransform *t, GLfloat *m)
{
	// | m[0] m[4] m[8]  m[12] |     | m11 m21 m31 m41 |     | a c 0 tx |
	// | m[1] m[5] m[9]  m[13] |     | m12 m22 m32 m42 |     | b d 0 ty |
	// | m[2] m[6] m[10] m[14] | <=> | m13 m23 m33 m43 | <=> | 0 0 1  0 |
	// | m[3] m[7] m[11] m[15] |     | m14 m24 m34 m44 |     | 0 0 0  1 |

	m[2] = m[3] = m[6] = m[7] = m[8] = m[9] = m[11] = m[14] = 0.0f;
	m[10] = m[15] = 1.0f;
	m[0] = t->a; m[4] = t->c; m[12] = t->tx;
	m[1] = t->b; m[5] = t->d; m[13] = t->ty;
}


void CPushButton::draw(CGraphic* pGraphic)
{
	if (m_pCurrentPic)
	{
		CCSize size = m_pCurrentPic->getContentSize();
		size.width  *= m_scale;
		size.height *= m_scale;
		pGraphic->drawImage(m_pCurrentPic,0,0,0,0,size.width,size.height,this->getBkColor().a);
	}
	else
	{
		CRectange rc = this->getChildRect();
		pGraphic->setColor(this->getBkColor());
		pGraphic->fillRectangle(rc);
	}
}

 void CPushButton::handlePenDown(CWidgetEvent& event)
 {
	 if (m_pPicClick)
	 {
		 m_pCurrentPic = m_pPicClick;
	 }
	 event.setHandled(true);
 }

 void CPushButton::handlePenUp(CWidgetEvent& event)
 {
	 if (m_pPicNormal)
	 {
		 m_pCurrentPic = m_pPicNormal;
	 }
	 event.setHandled(true);
 }

 void CPushButton::handlePenClick(CWidgetEvent& event)
 {
	 LOG("button [%d] is clicked",this->getID());
	 //post cmd to handler manager
	 CUICommand cmd;
	 cmd.setSource(this);
	 cmd.setCmdID(this->getcmdID());
	 CCommandHandlerMgr::instance()->postCmd(cmd);
 }

 void CPushButton::setNormalPic(CCTexture2D* var)
 {
	 CC_SAFE_RETAIN(var);
	 CC_SAFE_RELEASE_NULL(m_pPicNormal);
	 m_pPicNormal = var;
	 m_pCurrentPic = m_pPicNormal;
 }

 CCTexture2D* CPushButton::getNormalPic()
 {
	 return m_pPicNormal;
 }

 void CPushButton::setClickPic(CCTexture2D* var)
 {
	 CC_SAFE_RETAIN(var);
	 CC_SAFE_RELEASE_NULL(m_pPicClick);
	 m_pPicClick = var;
 }

 CCTexture2D* CPushButton::getClickPic()
 {
	 return m_pPicClick;
 }
 
 void CPushButton::setcmdID(int var)
 {
	 m_cmdID = var;
 }

 int CPushButton::getcmdID()
 {
	 return m_cmdID;
 }