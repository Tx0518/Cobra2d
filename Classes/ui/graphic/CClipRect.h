#ifndef __C_CLIP_RECT_H__
#define __C_CLIP_RECT_H__
/************************************************************************/
/* for clip                                                                     */
/************************************************************************/
#include "cocos2d.h"
USING_NS_CC;
class CClipRect:public CCRect
{
public:
	CClipRect(void);
	CClipRect(float x, 
		float y, 
		float width, 
		float height,
		float xOffset, 
		float yOffset);
	~CClipRect(void);
	const CClipRect& operator=(const CCRect& other);
	float m_fXoffset;
	float m_fYoffset;
};
#endif //__C_CLIP_RECT_H__
