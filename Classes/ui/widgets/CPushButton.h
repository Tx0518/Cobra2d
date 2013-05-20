#ifndef __C_PUSH_BUTTON_H__
#define __C_PUSH_BUTTON_H__
/************************************************************************/
/* this file is used to implement a simple push button widget
*/
/************************************************************************/
class CBaseWidget;
class CPushButton :public CBaseWidget
{
public:
	DECLARE_DYNCREATE(CPushButton);
	CPushButton(void);
	~CPushButton(void);
	//////////////////////////////////////////////////////////////////////////
	//property
	static const std::string PUSH_BTN_TYPE;
	static const std::string PB_NORMAL_PIC;
	static const std::string PB_CLICK_PIC;
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
	//////////////////////////////////////////////////////////////////////////
	void handlePenDown(CWidgetEvent& event);
	void handlePenUp(CWidgetEvent& event);
	void handlePenClick(CWidgetEvent& event);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY(CCTexture2D*,m_pPicNormal,NormalPic);
	COBRA_CREATE_PROPERTY(CCTexture2D*,m_pPicClick,ClickPic);
	COBRA_CREATE_PROPERTY(int,m_cmdID,cmdID);
private:
	CCTexture2D* m_pCurrentPic;
};
#endif //__C_PUSH_BUTTON_H__
