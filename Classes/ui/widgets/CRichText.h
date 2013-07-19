#ifndef __C_RIGH_TEXT_H__
#define __C_RIGH_TEXT_H__
#include "CSorllPanel.h"
#include "cocos2d.h"
#include "json.h"
USING_NS_CC;

/************************************************************************/
/* a formater  for richtxt
!!code format of string is utf-8 
ex:
CRichTxtFormater formater("ËÎÌו",25,0x000000ff);
std::string str=  "\nhello \n \nworld,this is a test string!";
formater.addText(CLabel::E_TXT_TYPE_LINK,str,0,0,false);
std::string str2=  "you are the chosen one";
formater.addText(CLabel::E_TXT_TYPE_RAW,str2,40,0xffff00ff);
//////////////////////////////////////////////////////////////////////////
CRichTxtLayOut layout;
layout.init(200);
layout.setTxt(formater.getRichText());
CSorllPanel* pPanel = new CSorllPanel();
pPanel->setRect(CreateCRect(200,0,200,250));
layout.attachToPanel(pPanel);
*/
/************************************************************************/
class CRichTxtFormater
{
public:
	//////////////////////////////////////////////////////////////////////////
	static const std::string TXT_FORMATER_DEFAULT_FONT;
	static const std::string TXT_FORMATER_DEFAULT_SIZE;
	static const std::string TXT_FORMATER_DEFAULT_COLOR;
	static const std::string TXT_FORMATER_DEFAULT_LINK_FONT;
	static const std::string TXT_FORMATER_DEFAULT_LINK_SIZE;
	static const std::string TXT_FORMATER_DEFAULT_LINK_COLOR;
	static const std::string TXT_FORMATER_CONTENT;
	//////////////////////////////////////////////////////////////////////////
	static const std::string TXT_TYPE;
	static const std::string TXT_SIZE;
	static const std::string TXT_COLOR;
	static const std::string TXT_STR;
	static const std::string TXT_NEW_LINE;
	static const std::string TXT_FONT;
	//////////////////////////////////////////////////////////////////////////
	CRichTxtFormater(std::string strDefaultFont,int iDefaultSize,int iDefaultColor,
		std::string strDefaultLinkFont = "ËÎÌו",int iDefaultLinkSize = 0,int iDefaultLinkColor = 0);
	~CRichTxtFormater();

	void addText(int iType,std::string& str,int iSize = 0,int iColor = 0,bool bForceBreak = false,std::string strFont = "");
	void addJsonTxt(std::string str);
	const Json::Value& getRichText();


	COBRA_CREATE_PROPERTY(std::string,m_strDefaultFont,DefaultFont);
	COBRA_CREATE_PROPERTY(int,m_iDefaultSize,DefaultSize);
	COBRA_CREATE_PROPERTY(int,m_iDefaultColor,DefaultColor);
	COBRA_CREATE_PROPERTY(std::string,m_strDefaultLinkFont,DefaultLinkFont);
	COBRA_CREATE_PROPERTY(int,m_iDefaultLinkSize,DefaultLinkSize);
	COBRA_CREATE_PROPERTY(int,m_iDefaultLinkColor,DefaultLinkColor);
private:
	Json::Value  m_jValue;
	 // declarations only
	CRichTxtFormater();
	CRichTxtFormater(const CRichTxtFormater&);           
	CRichTxtFormater& operator=(const CRichTxtFormater&);
};

/************************************************************************/
/*this class is used to do richttxt layout
*/
/************************************************************************/
class CRichTxtLayOut
{
public:
	//////////////////////////////////////////////////////////////////////////
	//inner class
	class CTxtLineInfo 
	{
	public:
		//align type
		enum
		{
			E_TXT_MIDDLE = 0,
			E_TXT_BOTTOM,
			E_TXT_TOP
		};
		CTxtLineInfo();
		~CTxtLineInfo();
		
		void addCLabel(CLabel* pLabel);
		std::vector<CLabel*>& getCLabels(void);
		void doLayout(int iAlignType);
		void reset(void);
		CTxtLineInfo& operator=(const CTxtLineInfo& other);

		COBRA_CREATE_PROPERTY_UNIMPLEMENT(int,m_iLineHeight,LineHeight)
	private:
		std::vector<CLabel*> m_vcLabels;
	};
	//////////////////////////////////////////////////////////////////////////
	CRichTxtLayOut();
	~CRichTxtLayOut();
	//you must invake this function first
	//@in iMaxWidth the max width of a single line
	//@in iLineInterval the interval between two line
	//@in iAlignType align type of a line
	void init(int iMaxWidth,int iLineInterval = 0,int iAlignType = CTxtLineInfo::E_TXT_BOTTOM);


	int getHeight(void);
	int getWidth(void);
	int getMaxWidth(void);

	//@in iLineInterval:interval between line default is zero
	void setTxt(const Json::Value& txtFormat);
	void attachToPanel(CPanel* pPanel);
private:
	bool isEnglishCharacter(char* pStr);
	bool isPunctuation(char* pStr);
	bool isWhiteSpace(char* pStr);
	void doTxtLayout(const Json::Value& txt);
	//////////////////////////////////////////////////////////////////////////
	void caculateTxt(std::string str,int iFontSize,int iColor,std::string strFont,bool bNewLine,int iStrType);
	void splitTxt(std::list<std::pair<std::string,int>>& vcCharacterInfo,std::string& str,std::string& strFont,int iSize);
	void addNewLine(std::vector<std::pair<std::string,int>>& vcCurrentLine,int& iCurrentWidth,
		std::string& strFont,int iColor,int iFontSize,bool bNewLine,int iStrType);
	//////////////////////////////////////////////////////////////////////////
	void addCurrentLineInfo(void);
	int m_iLineInterval;
	int m_iMaxWidth;
	int m_iAlignType;
	Json::Value m_txtFormat;
	//////////////////////////////////////////////////////////////////////////
	int m_iCurrentXPos;
	int m_iCurrentYPos;
	CTxtLineInfo m_currentTxtInfo;
	//////////////////////////////////////////////////////////////////////////
	//height and width of this txtlayout
	int m_iHeight;
	int m_iWidth;
	//////////////////////////////////////////////////////////////////////////
	std::vector<CTxtLineInfo> m_vcTxtLines;
};

/************************************************************************/
/* a richtxt implement to display text with format information
*/
/************************************************************************/
class CRichText:public CSorllPanel
{
public:
	CRichText(void);
	~CRichText(void);
	//////////////////////////////////////////////////////////////////////////
	static const std::string RICH_TXT_TYPE;
	//////////////////////////////////////////////////////////////////////////
	//@in iLineInterval:interval between line default is zero
	void setTxt(const Json::Value& txtFormat,int iLineInterval = 0);
private:
	void doTxtLayout(const Json::Value& txt);
	void caculateTxt(std::string str,int iFontSize,int iColor,std::string strFont,bool bNewLine);
	int m_iLineInterval;
	Json::Value m_txtFormat;
};

#endif //__C_RIGH_TEXT_H__