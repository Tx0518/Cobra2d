#ifndef __C_LAYOUT_H__
#define __C_LAYOUT_H__
class CLayoutParam
{
public:
	CLayoutParam();
	~CLayoutParam();
	//////////////////////////////////////////////////////////////////////////
	//const for some easy using 
	//no clip
	static const int NO_CLIP     = -4;
	//wrap content when set this for m_rect's width or height
	static const int WRAP_CONTENT = -2;
	//fill parent
	static const int FILL_PARENT = -1;
	//////////////////////////////////////////////////////////////////////////
};
#endif //__C_LAYOUT_H__