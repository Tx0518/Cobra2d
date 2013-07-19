#include "CGraphic.h"


CGraphic::CGraphic(void)
{
	m_pShader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
	CC_SAFE_RETAIN(m_pShader);
}

CGraphic::~CGraphic(void)
{
	CC_SAFE_RELEASE_NULL(m_pShader);
}

void CGraphic::setTargetPlane(int iWidth,int iHeight)
{
	m_Width  = iWidth;
	m_Height = iHeight;
}

void CGraphic::beginDraw()
{
	glEnable(GL_SCISSOR_TEST);
	pushClipArea(CreateCRect(0, 0, m_Width, m_Height));
}
void CGraphic::endDraw()
{
	glDisable(GL_SCISSOR_TEST);
	popClipArea();
}

bool CGraphic::pushClipArea(CRectange area)
{
	bool result =  false;
	//////////////////////////////////////////////////////////////////////////
	//compute clip area
	result = pushClipAreaInner(area);
	//////////////////////////////////////////////////////////////////////////
	cocos2d::CCEGLView::sharedOpenGLView()->setScissorInPoints(m_ClipStack.top().origin.x,
		m_Height - m_ClipStack.top().origin.y - m_ClipStack.top().size.height,
		m_ClipStack.top().size.width,
		m_ClipStack.top().size.height);
	return true;
}

void CGraphic::popClipArea(void)
{
	if (!m_ClipStack.empty())
	{
		m_ClipStack.pop();

		if (!m_ClipStack.empty())
		{
			CClipRect& topClip = m_ClipStack.top();
			cocos2d::CCEGLView::sharedOpenGLView()->setScissorInPoints(topClip.origin.x,
				m_Height - topClip.origin.y - topClip.size.height,
				topClip.size.width,
				topClip.size.height);
		}
		else
		{
			;//do nothing
		}
	}
}

const CClipRect& CGraphic::getCurrentClipArea(void)
{
	return m_ClipStack.top();
}
void CGraphic::reset(void)
{
	;//do nothing
}


bool CGraphic::pushClipAreaInner(CRectange area)
{
	if (area.size.width < 0 || area.size.height < 0)
	{
		CClipRect carea;
		m_ClipStack.push(carea);
		return true;
	}

	if (m_ClipStack.empty())
	{
		CClipRect carea;
		carea = area;
		carea.m_fXoffset = area.origin.x;
		carea.m_fYoffset = area.origin.y;
		m_ClipStack.push(carea);
		return true; 
	}

	const CClipRect &top = m_ClipStack.top();
	CClipRect carea;
	carea = area;
	carea.m_fXoffset = top.m_fXoffset + carea.origin.x;
	carea.m_fYoffset = top.m_fYoffset + carea.origin.y;
	carea.origin.x += top.m_fXoffset;
	carea.origin.y += top.m_fYoffset;

	// Clamp the pushed clip rectangle.
	if (carea.origin.x < top.origin.x)
	{
		carea.origin.x = top.origin.x;
	}

	if (carea.origin.y < top.origin.y)
	{
		carea.origin.y = top.origin.y;            
	}

	if (carea.origin.x + carea.size.width > top.origin.x + top.size.width)
	{
		carea.size.width = top.origin.x + top.size.width - carea.origin.x;

		if (carea.size.width < 0)
		{
			carea.size.width = 0;
		}
	}

	if (carea.origin.y + carea.size.height > top.origin.y + top.size.height)
	{
		carea.size.height = top.origin.y + top.size.height - carea.origin.y;

		if (carea.size.height < 0)
		{
			carea.size.height = 0;
		}
	}
	bool result = carea.intersectsRect(top);
	m_ClipStack.push(carea);
	return result;
}

//////////////////////////////////////////////////////////////////////////
 void CGraphic::setColor(CColor4B& color)
 {
	 m_Color = color;
 }
void CGraphic::drawImage(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height,CColor4B& color)
{
	if(image && ! m_ClipStack.empty())
	{
		const CClipRect& topRect = m_ClipStack.top();

		dstX += topRect.m_fXoffset;
		dstY += topRect.m_fYoffset;
		ccV3F_C4B_T2F_Quad sQuad = {0};
		//////////////////////////////////////////////////////////////////////////
		ccColor4B color4 = ccc4(color.r,color.g,color.b,color.a);
		sQuad.bl.colors = color4;
		sQuad.br.colors = color4;
		sQuad.tl.colors = color4;
		sQuad.tr.colors = color4;
		//////////////////////////////////////////////////////////////////////////
		float x1 = dstX;
		float y1 = m_Height - dstY;
		float x2 = x1 + width;
		float y2 = y1 - height;
		// Don't update Z.
		sQuad.tl.vertices = vertex3(x1, y1, 0);

		sQuad.bl.vertices = vertex3(x1, y2, 0);

		sQuad.br.vertices = vertex3(x2, y2, 0);


		sQuad.tr.vertices = vertex3(x2, y1, 0);
		//////////////////////////////////////////////////////////////////////////
		//update 
		float atlasWidth = (float)((CCTexture2D*)image)->getPixelsWide();
		float atlasHeight = (float)((CCTexture2D*)image)->getPixelsHigh();
		float left, right, top, bottom;
		left	= srcX/atlasWidth;
		right	= (((CCTexture2D*)image)->getContentSize().width)/atlasWidth;
		top		= srcY/atlasHeight;
		bottom	= (((CCTexture2D*)image)->getContentSize().height)/atlasHeight;


		sQuad.bl.texCoords.u = left;
		sQuad.bl.texCoords.v = bottom;
		sQuad.br.texCoords.u = right;
		sQuad.br.texCoords.v = bottom;
		sQuad.tl.texCoords.u = left;
		sQuad.tl.texCoords.v = top;
		sQuad.tr.texCoords.u = right;
		sQuad.tr.texCoords.v = top;
		//////////////////////////////////////////////////////////////////////////


	

#define kQuadSize sizeof(sQuad.bl)
		m_pShader->use();
		m_pShader->setUniformsForBuiltins();
		ccGLBindTexture2D(((CCTexture2D*)image)->getName());
		ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
		long offset = (long)&sQuad;

		// vertex
		int diff = offsetof( ccV3F_C4B_T2F, vertices);
		glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

		// texCoods
		diff = offsetof( ccV3F_C4B_T2F, texCoords);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

		// color
		diff = offsetof( ccV3F_C4B_T2F, colors);
		glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		//////////////////////////////////////////////////////////////////////////
		// draw bounding box
		//for clip rect ,modify this position
		this->setColor(CreateCColor(0,0,0,255));
		CRectange rc(dstX - topRect.m_fXoffset + 1,
			dstY - topRect.m_fYoffset + 1,
			width - 2,height - 2);
		this->drawRectangle(rc);
	}
}

void CGraphic::drawPoint(int x, int y)
{
	if (!m_ClipStack.empty())
	{
		const CClipRect& top = m_ClipStack.top();

		x += top.m_fXoffset;
		y += top.m_fYoffset;

		cocos2d::CCPoint pt;
		pt.x = x;
		pt.y = m_Height - y;
		ccDrawPoint(pt);
	}
}

void CGraphic::drawLine(int x1, int y1, int x2, int y2)
{
	if (!m_ClipStack.empty())
	{
		const CClipRect& top = m_ClipStack.top();

		x1 += top.m_fXoffset;
		y1 += top.m_fYoffset;
		x2 += top.m_fXoffset;
		y2 += top.m_fYoffset;

		cocos2d::CCPoint ptStart;
		ptStart.x = x1;
		ptStart.y = m_Height - y1;
		cocos2d::CCPoint ptEnd;
		ptEnd.x = x2;
		ptEnd.y = m_Height - y2;
		cocos2d::ccDrawLine(ptStart,ptEnd);	
	}
}


void CGraphic::drawRectangle(const CRectange& rectangle)
{
	if (!m_ClipStack.empty())
	{

		const CClipRect& top = m_ClipStack.top();

		cocos2d::CCPoint pt;
		pt.x = rectangle.origin.x + top.m_fXoffset;
		pt.y = m_Height - (rectangle.origin.x+ top.m_fYoffset);
		//////////////////////////////////////////////////////////////////////////
		cocos2d::CCPoint ptDemesion;
		ptDemesion.x = pt.x + rectangle.size.width;
		ptDemesion.y = pt.y - rectangle.size.height;
		ccDrawColor4B(m_Color.r,m_Color.g,m_Color.b,m_Color.a);
		ccDrawRect(pt,ptDemesion);
	}
}

void CGraphic::fillRectangle(const CRectange& rectangle)
{
	if (!m_ClipStack.empty())
	{
		const CClipRect& top = m_ClipStack.top();
		cocos2d::CCPoint pt;
		pt.x = rectangle.origin.x + top.m_fXoffset;
		pt.y = m_Height - (rectangle.origin.y + top.m_fYoffset);
		//////////////////////////////////////////////////////////////////////////
		cocos2d::CCPoint ptDemesion;
		ptDemesion.x = pt.x + rectangle.size.width;
		ptDemesion.y = pt.y - rectangle.size.height;
		cocos2d::ccColor4F  color;
		color.r = m_Color.r/255.0f;
		color.g = m_Color.g/255.0f;
		color.b = m_Color.b/255.0f;
		color.a = m_Color.a/255.0f;
		ccDrawSolidRect(pt,ptDemesion,color);
	}
}


#if 1//this is for rotation
//do not implement all the logic
void CGAffineToGL(const CCAffineTransform *t, GLfloat *m)
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
 void CGraphic::drawImageEx(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height,CColor4B& color,float fRotate)
 {
	 if(image && ! m_ClipStack.empty())
	 {
		 const CClipRect& topRect = m_ClipStack.top();

		 dstX += topRect.m_fXoffset;
		 dstY += topRect.m_fYoffset;
	 kmGLPushMatrix();

	 float cx = 1, sx = 0, cy = 1, sy = 0;
	 float m_fRotationX = 0,m_fRotationY = 0;
	 m_fRotationX = fRotate;
	 m_fRotationY = fRotate;
	 if (m_fRotationX || m_fRotationY)
	 {
		 float radiansX = -CC_DEGREES_TO_RADIANS(m_fRotationX);
		 float radiansY = -CC_DEGREES_TO_RADIANS(m_fRotationY);
		 cx = cosf(radiansX);
		 sx = sinf(radiansX);
		 cy = cosf(radiansY);
		 sy = sinf(radiansY);
	 }
	 float m_fScaleY = 1.0f;
	 float m_fScaleX = 1.0f;
	 // Build Transform Matrix
	 // Adjusted transform calculation for rotational skew
	 CCAffineTransform m_sTransform;     ///< transform

	 float x = dstX;
	 float y = m_Height - dstY;

	 CCPoint ptAnchor(0,1); 
	 CCPoint m_obAnchorPointInPoints;
	 m_obAnchorPointInPoints.x = ptAnchor.x * width;
	 m_obAnchorPointInPoints.y = ptAnchor.y * height;
	

	 x += cy * -m_obAnchorPointInPoints.x * m_fScaleX + -sx * -m_obAnchorPointInPoints.y * m_fScaleY;
	 y += sy * -m_obAnchorPointInPoints.x * m_fScaleX +  cx * -m_obAnchorPointInPoints.y * m_fScaleY;


	 m_sTransform = CCAffineTransformMake( cy * m_fScaleX,  sy * m_fScaleX,
		-sx * m_fScaleY, cx * m_fScaleY,x,y);


	 kmMat4 transfrom4x4;

	 CGAffineToGL(&m_sTransform, transfrom4x4.mat);

	 // Update Z vertex manually
	 transfrom4x4.mat[14] = 0.0f;

	 kmGLMultMatrix( &transfrom4x4 );



	 ccV3F_C4B_T2F_Quad sQuad = {0};
	 //////////////////////////////////////////////////////////////////////////
	 ccColor4B color4 = { 255, 255, 255,255 };

	 sQuad.bl.colors = color4;
	 sQuad.br.colors = color4;
	 sQuad.tl.colors = color4;
	 sQuad.tr.colors = color4;
	 //////////////////////////////////////////////////////////////////////////
 	 float x1 = 0 ;
 	 float y1 = 0 ;
 	 float x2 = width;
 	 float y2 = height;
 
 	 // Don't update Z.
 	 sQuad.bl.vertices = vertex3(x1, y1, 0);
 	 sQuad.br.vertices = vertex3(x2, y1, 0);
 	 sQuad.tl.vertices = vertex3(x1, y2, 0);
 	 sQuad.tr.vertices = vertex3(x2, y2, 0);

	 //////////////////////////////////////////////////////////////////////////
	 //update 
	 float atlasWidth = (float)((CCTexture2D*)image)->getPixelsWide();
	 float atlasHeight = (float)((CCTexture2D*)image)->getPixelsHigh();
	 float left, right, top, bottom;
	 left	= srcX/atlasWidth;
	 right	= (((CCTexture2D*)image)->getContentSize().width)/atlasWidth;
	 top		= srcY/atlasHeight;
	 bottom	= (((CCTexture2D*)image)->getContentSize().height)/atlasHeight;


	 sQuad.bl.texCoords.u = left;
	 sQuad.bl.texCoords.v = bottom;
	 sQuad.br.texCoords.u = right;
	 sQuad.br.texCoords.v = bottom;
	 sQuad.tl.texCoords.u = left;
	 sQuad.tl.texCoords.v = top;
	 sQuad.tr.texCoords.u = right;
	 sQuad.tr.texCoords.v = top;
	 //////////////////////////////////////////////////////////////////////////


	 ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(sQuad.bl)
	 m_pShader->use();
	 m_pShader->setUniformsForBuiltins();
	 ccGLBindTexture2D(((CCTexture2D*)image)->getName());
	 ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
	 long offset = (long)&sQuad;

	 // vertex
	 int diff = offsetof( ccV3F_C4B_T2F, vertices);
	 glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	 // texCoods
	 diff = offsetof( ccV3F_C4B_T2F, texCoords);
	 glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	 // color
	 diff = offsetof( ccV3F_C4B_T2F, colors);
	 glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	 kmGLPopMatrix();
 }
 }
#endif
//////////////////////////////////////////////////////////////////////////