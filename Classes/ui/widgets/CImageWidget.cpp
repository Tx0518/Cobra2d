#include "CImageWidget.h"
#include "CGraphic.h"
//////////////////////////////////////////////////////////////////////////
const std::string CImageWidget::IMAGE_PIC = "pic";
const std::string CImageWidget::IMAGE_WIDGET_TYPE = "CImageWidget";
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CImageWidget);
//////////////////////////////////////////////////////////////////////////
CImageWidget::CImageWidget(void)
{
	m_pPic    = NULL;
	m_strType = IMAGE_WIDGET_TYPE;
	this->setBkColor(CreateCColor(255,255,255,255));
}


CImageWidget::~CImageWidget(void)
{
	CC_SAFE_RELEASE_NULL(m_pPic);
}


void CImageWidget::draw(CGraphic* pGraphic)
{
	CRectange rc = this->getChildRect();
	if (m_pPic)
	{
		pGraphic->drawImage(m_pPic,0,0,0,0,rc.size.width,rc.size.height,this->getBkColor());
	}
	else
	{
		CBaseWidget::draw(pGraphic);
	}
}

void CImageWidget::setPic(CCTexture2D* var)
{
	CC_SAFE_RETAIN(var);
	CC_SAFE_RELEASE(m_pPic);
	m_pPic = var;
}

CCTexture2D* CImageWidget::getPic()
{
	return m_pPic;
}

void CImageWidget::updateContentSize(void)
{
	if(m_pPic)
	{
		this->setContentSize(CreateCSize(m_pPic->getContentSize().width,m_pPic->getContentSize().height));
	}
}

bool CImageWidget::setPorperty( const std::string& key,const std::string& strvalue )
{
	bool ret = true;
	do 
	{
		ret = CBaseWidget::setPorperty(key,strvalue);
		if (ret)
		{
			break;
		}

		if (key == CImageWidget::IMAGE_PIC)
		{
			CCTextureCache* pCache = CCTextureCache::sharedTextureCache();
			CCTexture2D* pPic = pCache->addImage(strvalue.c_str());
			this->setPic(pPic);
		}
		else
		{
			ret = false;
		}
	} while (0);

	return ret;
}