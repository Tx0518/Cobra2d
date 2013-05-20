#include "CClipRect.h"


CClipRect::CClipRect(void)
{
	origin.x = 0;
	origin.y = 0;
	size.width = 0;
	size.height = 0;
	m_fXoffset = 0;
	m_fYoffset = 0;
}


CClipRect::~CClipRect(void)
{
}



CClipRect::CClipRect(float x, float y, float width, float height, float xOffset, float yOffset)
{
	origin.x = x;
	origin.y = y;
	size.width = width;
	size.height = height;
	m_fXoffset = xOffset;
	m_fYoffset = yOffset;
}

const CClipRect& CClipRect::operator=(const CRectange& other)
{
	origin = other.origin;
	size   = other.size;
	return *this;
}