#include "CGraphic.h"
#include "CLabel.h"
#include "CMarcos.h"
#include "CLayoutParam.h"
#include "CommandHandlerMgr.h"
#include "CPropertyHelper.h"
//////////////////////////////////////////////////////////////////////////
const std::string  CLabel::LABEL_TYPE = "CLabel";
//////////////////////////////////////////////////////////////////////////
 const std::string CLabel::LABEL_STR  = "str";
 const std::string CLabel::LABEL_FONT = "font";
 const std::string CLabel::LABEL_SIZE = "size";
 const std::string CLabel::LABEL_COLOR = "color";
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CLabel);
//////////////////////////////////////////////////////////////////////////
CLabel::CLabel(void)
{
	m_iFontSize = 0;
	m_strFontName = "";
	m_pTexture = NULL;
	//default label can not be clicked
	m_bEnable = false;
	m_iType = E_TXT_TYPE_RAW;
	m_strType = LABEL_TYPE;
	m_cmdID = 0;
}

CLabel::CLabel(int iSize,CColor4B& color,std::string strFontName,int iType)
{
	m_iFontSize = iSize;
	m_strFontName = strFontName;
	m_pTexture = NULL;
	m_iType = iType;
	if (E_TXT_TYPE_LINK == iType
	|| E_TYPE_CLICKABLE == iType)
	{
		m_bEnable = true;
	}
	else
	{
		//default label can not be clicked
		m_bEnable = false;
	}
	m_cmdID = 0;
	this->setTextColor(color);
}

CLabel::CLabel(int iSize,int iColor, std::string strFontName,int iType)
{
	m_iFontSize = iSize;
	m_strFontName = strFontName;
	m_pTexture = NULL;
	m_iType = iType;
	if (E_TXT_TYPE_LINK == iType
		|| E_TYPE_CLICKABLE == iType)
	{
		m_bEnable = true;
	}
	else
	{
		//default label can not be clicked
		m_bEnable = false;
	}
	m_cmdID = 0;
	this->setTextColor(iColor);
}

CLabel::~CLabel(void)
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
}


void CLabel::measureCharacter(const char* pStr,std::string& strFontName,int iSize,int* pWidth,int* pHeight)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static CCLabelTTF* g_pTempLabel = NULL;
	if (NULL == g_pTempLabel)
	{
		g_pTempLabel = new CCLabelTTF();
	}
	//win32 just create a label to measure width and height
	CCSize dimension;
	dimension.width = 0;
	dimension.height = 0;
	g_pTempLabel->initWithString(pStr,strFontName.c_str(),iSize,dimension,kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter); 
	if (pWidth)
	{
		*pWidth = g_pTempLabel->getContentSize().width;
	}

	if (pHeight)
	{
		*pHeight = g_pTempLabel->getContentSize().height;
	}
	//reset it
	g_pTempLabel->setString("");
#endif
	//TODO implement others
}

void CLabel::draw(CGraphic* pGraphic)
{
	if (m_pTexture)
	{
		CRectange  rc = this->getRect();
		pGraphic->drawImage(m_pTexture,0,0,0,0,rc.size.width,rc.size.height,this->getBkColor());
	}
	else
	{
		CBaseWidget::draw(pGraphic);
	}
}

void CLabel::updateContentSize(void)
{
	if (m_pTexture)
	{
		this->setContentSize(CreateCSize(m_pTexture->getContentSize().width,m_pTexture->getContentSize().height));
	}
}

//////////////////////////
void CLabel::setString(std::string& str,int iSize,CColor4B& color,std::string& strFontName)
{
	if (0 != color.r && 0 != color.g && 0 != color.b && 0 != color.a)
	{
		this->setBkColor(color);
	}
	m_str = str;
	if (strFontName.length())
	{
		m_strFontName = strFontName;
	}
	
	if (0 < iSize)
	{
		m_iFontSize = iSize;
	}
	
	COBRA_SAFE_DELETE(m_pTexture);
	m_pTexture = NULL;
	m_pTexture = new CCTexture2D();
	m_pTexture->initWithString( str.c_str(),
		strFontName.c_str(),
		m_iFontSize * CC_CONTENT_SCALE_FACTOR(),
		CCSizeMake(0,0),
		kCCTextAlignmentLeft,
		kCCVerticalTextAlignmentCenter);
	m_bDirty = true;
}

void CLabel::setPos(int x,int y)
{
	this->setRect(CreateCRect(x,y,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
}

void CLabel::setTextColor(CColor4B& color)
{
	this->setBkColor(color);
}

void CLabel::setTextColor( int iColor )
{
	CColor4B tempColor = CreateCColor(255,255,255,255);
	tempColor.r = (iColor >> 24) & 0xff;
	tempColor.g = (iColor >> 16) & 0xff;
	tempColor.b = (iColor >> 8) & 0xff;
	tempColor.a = iColor & 0xff;
	this->setTextColor(tempColor);
}


void CLabel::handlePenDown(CWidgetEvent& event)
{
	this->setScale(1.5f);
	event.setHandled(true);
}

void CLabel::handlePenUp(CWidgetEvent& event)
{
	this->setScale(1.0f);
	event.setHandled(true);
}

void CLabel::handlePenClick(CWidgetEvent& event)
{
	CUICommand cmd;
	cmd.setSource(this);
	cmd.setCmdID(this->getcmdID());
	CCommandHandlerMgr::instance()->postCmd(cmd);
}

void CLabel::setTxtSize( int iSize )
{
	m_iFontSize = iSize;
}

void CLabel::setTxtFont( std::string& strFontName )
{
	m_strFontName = strFontName;
}

bool CLabel::setPorperty( const std::string& key,const std::string& strvalue )
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
	   std::string strValue = strvalue;
	   if (key == CLabel::LABEL_STR)
	   {
		   this->setString(strValue);
	   }
	   else if (key ==  CLabel::LABEL_FONT)
	   {
		   this->setTxtFont(strValue);
	   }
	   else if (key == CLabel::LABEL_SIZE)
	   {
		   this->setTxtSize(CPropertyHelper::stringToInt(strValue));
	   }
	   else if (key == CLabel::LABEL_COLOR)
	   {
			this->setTxtSize(CPropertyHelper::stringToInt(strValue));
	   }
	   else
	   {
		   ret = false;
	   }
	} while (0);
	return ret;
}