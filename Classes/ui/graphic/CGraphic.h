#ifndef __C_GRAPHIC_H__
#define __C_GRAPHIC_H__
#include <stack>
#include "CClipRect.h"
#include "thread/zthread/Singleton.h"
/************************************************************************/
/* this file is used for driver the graphic
*/
/************************************************************************/
#include "cocos2d.h"
USING_NS_CC;
class CGraphic :public ZThread::Singleton<CGraphic>
{
public:
	 CGraphic();
	 ~CGraphic();
	 //////////////////////////////////////////////////////////////////////////
	 void setTargetPlane(int iWidth,int iHeight);
	//////////////////////////////////////////////////////////////////////////
	 void setColor(CColor4B& color);
	 //draw function
	 //if you pass width/2,height/2
	 //the image will be half of the original one

	 //@in image texture
	 //@in srcX  start draw point in src x-axis
	 //@in srcY  start draw point in src y-axis
	 //@in dstX  draw position in dest x-axis
	 //@in dstY  draw position in dest y-axis
	 //@in width draw width
	 //@in height draw height
	 //@in CColor4B color
	 void drawImage(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height,CColor4B& color= CreateCColor(255,255,255,255));
	 void drawPoint(int x, int y);

	 void drawLine(int x1, int y1, int x2, int y2);

	 void drawRectangle(const CRectange& rectangle);

	 void fillRectangle(const CRectange& rectangle);
	//////////////////////////////////////////////////////////////////////////
	 void drawImageEx(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height,CColor4B& color= CreateCColor(255,255,255,255),float fRotate = 0);
	 //////////////////////////////////////////////////////////////////////////
	//clip area operation
	 bool pushClipArea(CRectange area);
	 void popClipArea(void);
	 const CClipRect& getCurrentClipArea(void);
	 void reset(void);
	//////////////////////////////////////////////////////////////////////////
public:
	void beginDraw();
	void endDraw();
private:
	//////////////////////////////////////////////////////////////////////////
	bool pushClipAreaInner(CRectange rc);
	std::stack<CClipRect> m_ClipStack;
	int m_Width;
	int m_Height;
	//used for reader image
	cocos2d::CCGLProgram* m_pShader;
    CColor4B   m_Color;
};

#endif //__C_GRAPHIC_H__