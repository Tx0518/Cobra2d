#include "CVirtualView.h"
#include "CPlatFormDefine.h"

CRectange CVirtualView::s_visibleRect;

void CVirtualView::lazyInit()
{
	if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
	{
		CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
		s_visibleRect.origin.setPoint(pEGLView->getVisibleOrigin().x,pEGLView->getVisibleOrigin().y);
		s_visibleRect.size.setSize(pEGLView->getVisibleSize().width,pEGLView->getVisibleSize().height);
	}
}

CRectange CVirtualView::getVisibleRect()
{
	lazyInit();
	return CRectange(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
}

CPoint CVirtualView::left()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CPoint CVirtualView::right()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CPoint CVirtualView::top()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CPoint CVirtualView::bottom()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

CPoint CVirtualView::center()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CPoint CVirtualView::leftTop()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CPoint CVirtualView::rightTop()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CPoint CVirtualView::leftBottom()
{
	lazyInit();
	return s_visibleRect.origin;
}

CPoint CVirtualView::rightBottom()
{
	lazyInit();
	return CPoint(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}
