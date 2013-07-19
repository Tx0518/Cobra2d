#ifndef __C_LABEL_H__
#define __C_LABEL_H__
#include "CBaseWidget.h"
#include "cocos2d.h"
USING_NS_CC;
/************************************************************************/
/* how to use:
CLabel* pLabel = new CLabel();
pLabel->setString(std::string("HelloWorld"),20,CreateCColor(255,0,0,255),std::string("ËÎÌו"));
pLabel->setPos(100,0);
*/
/************************************************************************/
class CLabel :public CBaseWidget
{
public:
	DECLARE_DYNCREATE(CLabel);
	static const std::string LABEL_TYPE;
	static const std::string LABEL_STR;
	static const std::string LABEL_FONT;
	static const std::string LABEL_SIZE;
	static const std::string LABEL_COLOR;
	//////////////////////////////////////////////////////////////////////////
	enum
	{
		E_TXT_TYPE_RAW,//raw type
		E_TXT_TYPE_LINK,//link type
		E_TYPE_CLICKABLE,//clickable
		E_TYPE_TOTAL,//
	};
	//////////////////////////////////////////////////////////////////////////
	virtual void handlePenDown(CWidgetEvent& event);
	virtual void handlePenUp(CWidgetEvent& event);
	virtual void handlePenClick(CWidgetEvent& event);
	//////////////////////////////////////////////////////////////////////////
	//you should NOT measure width of a too long string
	//and for the reason that system should not have the right font for iSize
	//so the width and height will not equals the iSize given by you
	static void measureCharacter(const char* pStr,std::string& strFontName,int iSize,int* pWidth,int* pHeight);
	//////////////////////////////////////////////////////////////////////////
	CLabel(void);
	CLabel(int iSize,CColor4B& color, std::string strFontName,int iType = E_TXT_TYPE_RAW);
	CLabel(int iSize,int iColor, std::string strFontName,int iType = E_TXT_TYPE_RAW);
	~CLabel(void);
	//////////////////
	void draw(CGraphic* pGraphic);
	void updateContentSize(void);
	bool setPorperty(const std::string& key,const std::string& strvalue);
	//////////////////////////
	void setString(std::string& str,int iSize=0,CColor4B& color = CreateCColor(0,0,0,255),std::string& strFontName=std::string(""));
	void setPos(int x,int y);
	//
	void setTextColor(CColor4B& color);
	//
	void setTxtSize(int iSize);
	void setTxtFont(std::string& strFontName);
	//////////////////////////////////////////////////////////////////////////
	//RGBA
	void setTextColor(int iColor);

	//if the label is a clickable or link type,this cmd will be send when you click this label
	COBRA_CREATE_PROPERTY(int,m_cmdID,cmdID);
private:
	std::string  m_str;
	std::string  m_strFontName;
	int          m_iFontSize;
	int          m_iType;
	CCTexture2D* m_pTexture;
};

#endif //__C_LABEL_H__