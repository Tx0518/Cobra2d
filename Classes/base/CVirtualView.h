#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "CGeometry.h"

class CVirtualView
{
public:
	static CRectange getVisibleRect();

	static CPoint left();
	static CPoint right();
	static CPoint top();
	static CPoint bottom();
	static CPoint center();
	static CPoint leftTop();
	static CPoint rightTop();
	static CPoint leftBottom();
	static CPoint rightBottom();
private:
	static void lazyInit();
	static CRectange s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */
