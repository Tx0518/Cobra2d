#ifndef __C_IMAGE_WIDGET_H__
#define __C_IMAGE_WIDGET_H__
#include "CBaseWidget.h"
#include "cocos2d.h"
USING_NS_CC;
/************************************************************************/
/* this file is  a simple image widget
only render a image to screen at m_rect
how to use:
CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("CloseSelected.png");
CImageWidget* pImage = new CImageWidget();
pImage->setPic(pPicSel);
pImage->setRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT);
*/
/************************************************************************/
class CImageWidget :public CBaseWidget
{
public:
	DECLARE_DYNCREATE(CImageWidget);
	static const std::string IMAGE_WIDGET_TYPE;
	//////////////////////////////////////////////////////////////////////////
	//property
	static const std::string IMAGE_PIC;
	//////////////////////////////////////////////////////////////////////////
	CImageWidget(void);
	~CImageWidget(void);
	void draw(CGraphic* pGraphic);
	void updateContentSize(void);
	//////////////////////////////////////////////////////////////////////////
	bool setPorperty(const std::string& key,const std::string& strvalue);
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(CCTexture2D*,m_pPic,Pic)
	//////////////////////////////////////////////////////////////////////////
};
#endif //__C_IMAGE_WIDGET_H__
