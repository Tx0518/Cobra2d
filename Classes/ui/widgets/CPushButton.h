#ifndef __C_PUSH_BUTTON_H__
#define __C_PUSH_BUTTON_H__
/************************************************************************/
/* this file is used to implement a simple push button widget
ex:
CCTexture2D* pPicNormal = CCTextureCache::sharedTextureCache()->addImage("CloseNormal.png");
CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("CloseSelected.png");
CPushButton* pBtn = new CPushButton();
pBtn->setNormalPic(pPicNormal);
pBtn->setClickPic(pPicSel);
pBtn->setRect(CreateCRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
//pBtn->setScale(1.0f);
pBtn->setZOrder(1);
pBtn->setcmdID(HelloWorld::CMD_ID_EIXT);
if you want to enable long press event of push button just invoke this method:
int iCmdIdLongPress = 1234567;
pBtn->setlongClick(true,iCmdIdLongPress);
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
	static const std::string PB_CMD_ID;
	//////////////////////////////////////////////////////////////////////////
	//default is 1500 millisecond (1.5 second)
	static const int PUSH_BTN_LONG_PRESS_INTERVAL = 1500;
	//////////////////////////////////////////////////////////////////////////
	void draw(CGraphic* pGraphic);
	//////////////////////////////////////////////////////////////////////////
	void updateContentSize(void);
	bool setPorperty(const std::string& key,const std::string& strvalue);
	//////////////////////////////////////////////////////////////////////////
	void handlePenDown(CWidgetEvent& event);
	void handlePenUp(CWidgetEvent& event);
	void handlePenClick(CWidgetEvent& event);
	//////////////////////////////////////////////////////////////////////////
	void setlongClick(bool bSupport,int iCmdIDLongPress,int iMilliSencond = PUSH_BTN_LONG_PRESS_INTERVAL);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(CCTexture2D*,m_pPicNormal,NormalPic)
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(CCTexture2D*,m_pPicClick,ClickPic)
	COBRA_CREATE_PROPERTY(int,m_cmdID,cmdID)
private:
	void   computeContentSize(CCTexture2D* pPic);
	CCTexture2D* m_pCurrentPic;
	//////////////////////////////////////////////////////////////////////////
	bool    m_bSupportLongClick;
	int     m_iMilliSencondInterval;
	int     m_iCmdLongPress;
	clock_t m_iPenDownTime;
	clock_t m_iPenUpTime;
};
#endif //__C_PUSH_BUTTON_H__
