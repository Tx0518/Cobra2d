#include "CBaseWidget.h"
#include "cocos2d.h"
USING_NS_CC;
#include "CPushButton.h"
#include "CGraphic.h"
#include "CommandHandlerMgr.h"
#include "CPropertyHelper.h"
//////////////////////////////////////////////////////////////////////////
 const std::string CPushButton::PUSH_BTN_TYPE = "CPushButton";
 const std::string CPushButton::PB_NORMAL_PIC = "btnNormalPic";
 const std::string CPushButton::PB_CLICK_PIC  = "btnSelPic";
 const std::string CPushButton::PB_CMD_ID = "btnCmdId";
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
	m_bSupportLongClick = false;
	m_iPenDownTime = 0;
	m_iPenUpTime   = 0;
}


CPushButton::~CPushButton(void)
{
	CC_SAFE_RELEASE_NULL(m_pPicNormal);
	CC_SAFE_RELEASE_NULL(m_pPicClick);
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
	CRectange rc = this->getChildRect();
	if (m_pCurrentPic)
	{
		pGraphic->drawImage(m_pCurrentPic,0,0,0,0,rc.size.width,rc.size.height,this->getBkColor());
	}
	else
	{
		
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
	 m_iPenDownTime = 0;
	 m_iPenUpTime   = 0;
	 m_iPenDownTime = clock();
 }

 void CPushButton::handlePenUp(CWidgetEvent& event)
 {
	 if (m_pPicNormal)
	 {
		 m_pCurrentPic = m_pPicNormal;
	 }
	 event.setHandled(true);
	 m_iPenUpTime = clock();
 }

 void CPushButton::handlePenClick(CWidgetEvent& event)
 {
	 LOG("button [%d] is clicked",this->getID());
	 CUICommand cmd;
	 cmd.setSource(this);
	 //one second has one thousand millisecond
	 LOG("time elapsed = [%f]",(float)(m_iPenUpTime - m_iPenDownTime) / CLOCKS_PER_SEC);
	 if (m_bSupportLongClick && (float)(m_iPenUpTime - m_iPenDownTime) / CLOCKS_PER_SEC >=  ((float)m_iMilliSencondInterval/1000.0f))
	 {
		 //trigger long press event
		 LOG("trigger long press event");
		 cmd.setCmdID(this->m_iCmdLongPress);
	 }
	 else
	 {
		 //post cmd to handler manager
		 cmd.setCmdID(this->getcmdID());
	 }
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

 void CPushButton::computeContentSize(CCTexture2D* pPic)
 {
	 if (pPic)
	 {
		 CCSize size = pPic->getContentSize();
		 m_contentSize.width = comax(size.width,m_contentSize.width);
		 m_contentSize.height = comax(size.height,m_contentSize.height);
	 }
	 else
	 {
		 ;//do nothing
	 }
 }

 void CPushButton::updateContentSize(void)
 {
	 this->computeContentSize(m_pPicNormal);
	 this->computeContentSize(m_pPicClick);
 }

 void CPushButton::setlongClick( bool bSupport,int iCmdIDLongPress,int iMilliSencond /*= PUSH_BTN_LONG_PRESS_INTERVAL*/ )
 {
	 m_bSupportLongClick = bSupport;
	 m_iCmdLongPress     = iCmdIDLongPress;
	 m_iMilliSencondInterval = iMilliSencond;
 }

 bool CPushButton::setPorperty( const std::string& key,const std::string& strvalue )
 {
	 bool ret = true;
	 do 
	 {
		 ret = CBaseWidget::setPorperty(key,strvalue);
		 if (ret)
		 {
			 break;
		 }
		 //////////////////////////////////////////////////////////////////////////
		 CCTextureCache* pCache = CCTextureCache::sharedTextureCache();
		 if (key == CPushButton::PB_NORMAL_PIC)
		 {
			 CCTexture2D* pPic = pCache->addImage(strvalue.c_str());
			 this->setNormalPic(pPic);
		 }
		 else if (key == CPushButton::PB_CLICK_PIC)
		 {
			 CCTexture2D* pPic = pCache->addImage(strvalue.c_str());
			 this->setClickPic(pPic);
		 }
		 else if (key == CPushButton::PB_CMD_ID)
		 {
			 this->setcmdID(CPropertyHelper::stringToInt(strvalue));
		 }
		 else
		 {
			 ret = false;
		 }
	 } while (0);
	 return ret;
 }