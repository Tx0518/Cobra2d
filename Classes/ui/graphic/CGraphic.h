#ifndef __C_GRAPHIC_H__
#define __C_GRAPHIC_H__
#include <stack>
#include "CClipRect.h"
#include "thread/zthread/Singleton.h"
/************************************************************************/
/* this file is used for driver the graphic
*/
/************************************************************************/
class CGraphic :public ZThread::Singleton<CGraphic>
{
public:
	 ~CGraphic();
	 //////////////////////////////////////////////////////////////////////////
	 void setTargetPlane(int iWidth,int iHeight);
	//////////////////////////////////////////////////////////////////////////
	 void setColor(cocos2d::ccColor4B& color);
	 //draw function
	 void drawImage(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height);

	 void drawPoint(int x, int y);

	 void drawLine(int x1, int y1, int x2, int y2);

	 void drawRectangle(const CCRect& rectangle);

	 void fillRectangle(const CCRect& rectangle);
	 //////////////////////////////////////////////////////////////////////////
	//clip area operation
	 bool pushClipArea(CCRect area);
	 void popClipArea(void);
	 const CClipRect& getCurrentClipArea(void);
	 void reset(void);
	//////////////////////////////////////////////////////////////////////////
public:
	void beginDraw();
	void endDraw();
private:
	//////////////////////////////////////////////////////////////////////////
	bool pushClipAreaInner(CCRect rc);
	std::stack<CClipRect> m_ClipStack;
	int m_Width;
	int m_Height;
	//used for reader image
	cocos2d::CCGLProgram* m_pShader;
	cocos2d::ccColor4B    m_Color;
};

#endif //__C_GRAPHIC_H__