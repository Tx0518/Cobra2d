#ifndef __C_LINEAR_LAYOUT_H__
#define __C_LINEAR_LAYOUT_H__
/************************************************************************/
/*how to use:
CLinearLayout* layout = new CLinearLayout();
layout->setRect(0,0,200,200);
layout->setOrientation(CLinearLayout::HORIZONTAL);
layout->setPadding(10,10,10,10);
///////////////////////////////////////////////
//then you just need to add children to this layout
layout->add(pWidget);
......
//////////////////////////////////////////////////////////////////////////
*/
/************************************************************************/
class CSorllPanel;
class CLinearLayout :public CSorllPanel
{
public:
	//linear layout type
	enum 
	{
		HORIZONTAL = 0,
		VERTICAL
	};
	//////////////////////////////////////////////////////////////////////////
	//
	static const int LINEAR_HORI_GRAVITY_CENTER = 6;//Ë®Æ½¾ÓÖÐ

	CLinearLayout(void);
	virtual ~CLinearLayout(void);
	//////////////////////////////////////////////////////////////////////////
	void onAdd(CBaseWidget* pParent);
	//////////////////////////////////////////////////////////////////////////
	//set orientation
	void setOrientation(int iOrientation);
	//set gravity type
	void setGravityType(int iGravityType);
	//set padding for this layout
	void setPadding(int iLeft,int iTop,int iRight,int iBottom);


private:
	//////////////////////////////////////////////////////////////////////////
	void doLayOut(void);
	//////////////////////////////////////////////////////////////////////////
	bool m_bLayoutDone;
	int m_iOrientation;
	int m_iGravityType;
	int m_iLeftPadding;
	int m_iRightPadding;
	int m_iTopPadding;
	int m_iBottomPadding;
};

#endif//__C_LINEAR_LAYOUT_H__