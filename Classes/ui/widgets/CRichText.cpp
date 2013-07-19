#include "CGeometry.h"
#include "CBaseContainer.h"
#include "CPanel.h"
#include "CLabel.h"
#include "CRichText.h"
#include "CUTF8.h"
#include "CJsonHelper.h"
#include "pcrecpp.h"
using namespace json_helper;
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 
richtext
{
"default_font":"",
"default_size":"",
"default_color":"",
"default_link_font":"",
"default_link_size":"",
"default_link_color":"",
"content":"[textcontent0,textcontent1,textcontent2,textcontent3,textcontent4]"
}


content
{
"type"="",//int
"str"="",//str
"size"="",//int
"color"="",//int
"br"="",//bool
"font"="",//str
}                                                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
 const std::string CRichTxtFormater::TXT_FORMATER_DEFAULT_FONT = "default_font";
 const std::string CRichTxtFormater::TXT_FORMATER_DEFAULT_SIZE = "default_size";
 const std::string CRichTxtFormater::TXT_FORMATER_DEFAULT_COLOR = "default_color";
 const std::string CRichTxtFormater::TXT_FORMATER_DEFAULT_LINK_FONT = "default_link_font";
 const std::string CRichTxtFormater::TXT_FORMATER_DEFAULT_LINK_SIZE = "default_link_size";
 const std::string CRichTxtFormater::TXT_FORMATER_DEFAULT_LINK_COLOR = "default_link_color";
  const std::string CRichTxtFormater::TXT_FORMATER_CONTENT = "content";
 
 //////////////////////////////////////////////////////////////////////////
 const std::string CRichTxtFormater::TXT_TYPE = "type";
 const std::string CRichTxtFormater::TXT_SIZE = "size";
 const std::string CRichTxtFormater::TXT_COLOR = "color";
 const std::string CRichTxtFormater::TXT_STR   = "str";
 const std::string CRichTxtFormater::TXT_NEW_LINE = "br";
 const std::string CRichTxtFormater::TXT_FONT  = "font";
//////////////////////////////////////////////////////////////////////////
CRichTxtFormater::CRichTxtFormater(std::string strDefaultFont,int iDefaultSize,int iDefaultColor,
	std::string strDefaultLinkFont,int iDefaultLinkSize,int iDefaultLinkColor)
{
	m_strDefaultFont = strDefaultFont;
	m_iDefaultSize   = iDefaultSize;
	m_iDefaultColor  = iDefaultColor;
	m_strDefaultLinkFont = strDefaultLinkFont;
	m_iDefaultLinkSize  = iDefaultLinkSize;
	m_iDefaultLinkColor = iDefaultLinkColor;
	if (0 == m_iDefaultLinkSize)
	{
		m_iDefaultLinkSize = m_iDefaultSize;
	}

	if (0 == m_iDefaultLinkColor)
	{
		m_iDefaultLinkColor = m_iDefaultColor;
	}
	m_jValue[TXT_FORMATER_DEFAULT_FONT]  = m_strDefaultFont;
	m_jValue[TXT_FORMATER_DEFAULT_SIZE]  = m_iDefaultSize;
	m_jValue[TXT_FORMATER_DEFAULT_COLOR] = iDefaultColor;
	m_jValue[TXT_FORMATER_DEFAULT_FONT]  = m_strDefaultLinkFont;
	m_jValue[TXT_FORMATER_DEFAULT_SIZE]  = m_iDefaultLinkSize;
	m_jValue[TXT_FORMATER_DEFAULT_COLOR] = m_iDefaultLinkColor;
}


CRichTxtFormater::~CRichTxtFormater()
{
}

void CRichTxtFormater::addJsonTxt(std::string str)
{
	ENTERFUNC();
	Json::Reader read;
	if (!read.parse(str,m_jValue))
	{
		LOG("json txt is invalid");
	}
	LVFUNC();
}

void CRichTxtFormater::addText( int iType,std::string& str,int iSize,int iColor,bool bForceBreak,std::string strFont )
{
	ENTERFUNC();
	Json::Value content;
	content[TXT_TYPE] = iType;
	content[TXT_STR]  = str;
	switch (iType)
	{
	case CLabel::E_TXT_TYPE_RAW:
	case CLabel::E_TYPE_CLICKABLE:
		{
			if (0 < iSize)
			{
				content[TXT_SIZE] = iSize;
			}
			else
			{
				content[TXT_SIZE] = m_iDefaultSize;
			}

			if (0 != iColor)
			{
				content[TXT_COLOR] = iColor;
			}
			else
			{
				content[TXT_COLOR] = m_iDefaultColor;
			}

			if (0 < strFont.length())
			{
				content[TXT_FONT] = strFont;
			}
			else
			{
				content[TXT_FONT] = m_strDefaultFont;
			}
			break;
		}
	case CLabel::E_TXT_TYPE_LINK:
		{
			if (0 < iSize)
			{
				content[TXT_SIZE] = iSize;
			}
			else
			{
				content[TXT_SIZE] = m_iDefaultLinkSize;
			}

			if (0 != iColor)
			{
				content[TXT_COLOR] = iColor;
			}
			else
			{
				content[TXT_COLOR] = m_iDefaultLinkColor;
			}

			if (0 < strFont.length())
			{
				content[TXT_FONT] = strFont;
			}
			else
			{
				content[TXT_FONT] = m_strDefaultLinkFont;
			}
			break;
		}
	default:
		{
			break;
		}
	}

	content[TXT_NEW_LINE] = bForceBreak;
	m_jValue[TXT_FORMATER_CONTENT].append(content);
	LVFUNC();
}

const Json::Value& CRichTxtFormater::getRichText()
{
	return m_jValue;
}
//////////////////////////////////////////////////////////////////////////

CRichTxtLayOut::CTxtLineInfo::CTxtLineInfo()
{
	m_iLineHeight  = 0;
}

CRichTxtLayOut::CTxtLineInfo::~CTxtLineInfo()
{
	;//
}

void CRichTxtLayOut::CTxtLineInfo::addCLabel( CLabel* pLabel )
{
	m_vcLabels.push_back(pLabel);
}

std::vector<CLabel*>& CRichTxtLayOut::CTxtLineInfo::getCLabels(void)
{
	return m_vcLabels;
}

void CRichTxtLayOut::CTxtLineInfo::doLayout(int iAlignType)
{
	//compute line height
	this->getLineHeight();
	//align children
	switch(iAlignType)
	{
	case E_TXT_TOP:
		{
			;//do nothing default compute is top
			break;
		}
	case E_TXT_MIDDLE:
		{
			std::vector<CLabel*>::iterator iter = m_vcLabels.begin();
			while (iter != m_vcLabels.end())
			{
				CRectange rc = (*iter)->getRect();
				rc.origin.y += (m_iLineHeight - (*iter)->getRect().size.height)/2;
				(*iter)->setRect(rc);
				iter++;
			}
			break;
		}
	case E_TXT_BOTTOM:
		{
			std::vector<CLabel*>::iterator iter = m_vcLabels.begin();
			while (iter != m_vcLabels.end())
			{
				CRectange rc = (*iter)->getRect();
				rc.origin.y += m_iLineHeight - (*iter)->getRect().size.height;
				(*iter)->setRect(rc);
				iter++;
			}
			break;
		}
	default:
		{
			LOG("unknown txt align type = [%d]",iAlignType);
			break;
		}
	}
}

CRichTxtLayOut::CTxtLineInfo& CRichTxtLayOut::CTxtLineInfo::operator=( const CTxtLineInfo& other )
{
	CTxtLineInfo& infoOhter = (CTxtLineInfo&)other;
	this->m_iLineHeight  = infoOhter.getLineHeight();
	this->m_vcLabels     = infoOhter.getCLabels();
	return *this;
}

void CRichTxtLayOut::CTxtLineInfo::reset(void)
{
	m_iLineHeight = 0;
	m_vcLabels.clear();
}


void CRichTxtLayOut::CTxtLineInfo::setLineHeight(int var)
{
	m_iLineHeight = var;
}

int CRichTxtLayOut::CTxtLineInfo::getLineHeight()
{
	int ret = m_iLineHeight;
	if (0 == ret)
	{
		int index = 0;
		int count = m_vcLabels.size();
		CLabel* pTemp = NULL;
		for (;index < count;index++)
		{
			pTemp = m_vcLabels.at(index);
			if (pTemp)
			{
				ret = comax(ret,pTemp->getRect().size.height);
			}
		}
		m_iLineHeight = ret;
	}

	return ret;
}
//////////////////////////////////////////////////////////////////////////
CRichTxtLayOut::CRichTxtLayOut()
{
	m_iLineInterval = 0;
	m_iMaxWidth    = 0;
	//default align type is bottom
	m_iAlignType   = CTxtLineInfo::E_TXT_BOTTOM;
	m_txtFormat    = 0;
	m_iCurrentXPos = 0;
	m_iCurrentYPos = 0;

	m_iHeight = -1;
	m_iWidth  = -1;
}

CRichTxtLayOut::~CRichTxtLayOut()
{

}

void CRichTxtLayOut::init( int iMaxWidth,int iLineInterval /*= 0*/ ,int iAlignType)
{
	m_iMaxWidth = iMaxWidth;
	m_iLineInterval = iLineInterval;
	m_iAlignType = iAlignType;
}

int CRichTxtLayOut::getHeight( void )
{
	int ret = 0;
	if (-1 != m_iHeight)
	{
		ret = m_iHeight;
	}
	else
	{
		int index = 0;
		int count = m_vcTxtLines.size();
		float iTemp = 0;
		m_iHeight = 0;
		for (;index < count;index++)
		{
			m_iHeight += iTemp;
			iTemp = 0;
			CTxtLineInfo& infoTemp = m_vcTxtLines.at(index);
			std::vector<CLabel*>& vcLabel = infoTemp.getCLabels();
			std::vector<CLabel*>::iterator iter = vcLabel.begin();
			while(iter != vcLabel.end())
			{
				iTemp = comax(iTemp,(*iter)->getContentSize().height);
				iter++;
			}
		}
		m_iHeight += iTemp;
		ret = m_iHeight;
	}
	return ret;
}

int CRichTxtLayOut::getWidth( void )
{
	int ret = 0;
	if (-1 != m_iWidth)
	{
		ret = m_iWidth;
	}
	else
	{
		int index = 0;
		int count = m_vcTxtLines.size();
		float iTemp = 0;
		for (;index < count;index++)
		{
			m_iWidth = comax(iTemp,m_iWidth);
			iTemp = 0;
			CTxtLineInfo& infoTemp = m_vcTxtLines.at(index);
			std::vector<CLabel*>& vcLabel = infoTemp.getCLabels();
			std::vector<CLabel*>::iterator iter = vcLabel.begin();
			while(iter != vcLabel.end())
			{
				iTemp += (*iter)->getContentSize().width;
				iter++;
			}
		}
		m_iWidth = comax(iTemp,m_iWidth);
		ret = m_iWidth;
	}
	return ret;
}

int CRichTxtLayOut::getMaxWidth( void )
{
	return m_iMaxWidth;
}

void CRichTxtLayOut::setTxt( const Json::Value& txtFormat )
{
	m_txtFormat = txtFormat;
	this->doTxtLayout(m_txtFormat);
}

void CRichTxtLayOut::attachToPanel( CPanel* pPanel )
{
	ENTERFUNC();
	if (pPanel)
	{
		int index = 0;
		int count = m_vcTxtLines.size();
		CTxtLineInfo infoTemp;
		for (;index < count;index++)
		{
			infoTemp = m_vcTxtLines.at(index);
			std::vector<CLabel*>& vcLabel = infoTemp.getCLabels();
			std::vector<CLabel*>::iterator iter = vcLabel.begin();
			while(iter != vcLabel.end())
			{
				pPanel->add(*iter);
				iter++;
			}
		}
	}
	else
	{
		LOG("parameter is null");
	}
	LVFUNC();
}

bool CRichTxtLayOut::isEnglishCharacter(char* pStr)
{
	bool ret = false;
	if (0x41 <= *pStr && *pStr <= 0x5A)
	{
		ret = true;
	}

	if (0x60 <= *pStr && *pStr <= 0x7A)
	{
		ret = true;
	}
	return ret;
}

bool CRichTxtLayOut::isPunctuation(char* pStr)
{
	bool ret = false;
#if 0
	std::string strExp = "[,\\.\\*\\?\"'%\\$\\^&@\\#]";
	pcrecpp::RE matchExp(strExp);
	ret = matchExp.FullMatch(pStr);
#endif
	return ret;
}

bool CRichTxtLayOut::isWhiteSpace(char* pStr)
{
	return (*pStr == ' ');
}

void CRichTxtLayOut::doTxtLayout( const Json::Value& txt )
{
	ENTERFUNC();
	if (m_iMaxWidth <= getJsonInt(txt,CRichTxtFormater::TXT_FORMATER_DEFAULT_SIZE.c_str()))
	{
		LOG("width of CRichTxtLayOut is too small do nothing");
	}
	else
	{
		Json::Value defaultValue = 0;
		Json::Value contentArray = txt.get(CRichTxtFormater::TXT_FORMATER_CONTENT,defaultValue);
		if (contentArray != 0)
		{
			if (contentArray.isArray())
			{
				int index = 0;
				int count = contentArray.size();

				int iStrType = CLabel::E_TXT_TYPE_RAW;
				int iSize    = 0;
				int iColor   = 0;
				std::string str = "";
				std::string strFont = "";
				bool bNewLine = false;

				for (;index < count;index++)
				{
					Json::Value defaultContent = 0;
					Json::Value content = contentArray.get(index,defaultContent);
					if (content != 0)
					{
						iStrType = getJsonInt(content,CRichTxtFormater::TXT_TYPE.c_str());
						iSize    = getJsonInt(content,CRichTxtFormater::TXT_SIZE.c_str());
						iColor   = getJsonInt(content,CRichTxtFormater::TXT_COLOR.c_str());
						str = getJsonString(content,CRichTxtFormater::TXT_STR.c_str());
						strFont = getJsonString(content,CRichTxtFormater::TXT_FONT.c_str());
						bNewLine = getJsonBoolean(content,CRichTxtFormater::TXT_NEW_LINE.c_str());
						this->caculateTxt(str,iSize,iColor,strFont,bNewLine,iStrType);
					}
				}
				//add the last line here
				m_currentTxtInfo.doLayout(CTxtLineInfo::E_TXT_BOTTOM);
				m_vcTxtLines.push_back(m_currentTxtInfo);
			}
			else
			{
				LOG("error read txt json");
			}
		}
	}
	LVFUNC();
}

void CRichTxtLayOut::addCurrentLineInfo(void)
{
	ENTERFUNC();
	std::vector<CLabel*>& vc = m_currentTxtInfo.getCLabels();
	if (vc.size())
	{
		m_currentTxtInfo.doLayout(CTxtLineInfo::E_TXT_BOTTOM);
		m_vcTxtLines.push_back(m_currentTxtInfo);
	}
	LVFUNC();
}

void CRichTxtLayOut::splitTxt(std::list<std::pair<std::string,int>>& vcCharacterInfo,std::string& str,std::string& strFont,int iSize)
{
	char* pStr = (char*)str.c_str();
	int index  = 0;
	int iCount = u8_strlen(pStr);
	int iTotalOffset = 0;
	int iOffset = 0;
	int iPreOffset = 0;
	int iTempWidth = 0;
	int iTempHeight = 0;

	std::string strTemp = "";
	while(index < iCount)
	{
		index++;
		u8_inc(pStr,&iTotalOffset);
		strTemp.assign(pStr + iPreOffset,iTotalOffset - iPreOffset);
		if (this->isEnglishCharacter((char*)strTemp.c_str()))
		{
			;//do nothing
		}
		else
		{
			strTemp.assign(pStr,iTotalOffset);
			//if the char is '\n' add a placeholder
			if (strTemp == "\n")
			{
				vcCharacterInfo.push_back(std::make_pair<std::string,int>(strTemp,0));
			}
			else
			{
				CLabel::measureCharacter(strTemp.c_str(),strFont,iSize,&iTempWidth,&iTempHeight);
				vcCharacterInfo.push_back(std::make_pair<std::string,int>(strTemp,iTempWidth));
				//this is a '\n' attach to the last english char
				//just add a placeholder
				if (strTemp.at(strTemp.length() - 1) == '\n')
				{
					vcCharacterInfo.push_back(std::make_pair<std::string,int>("\n",0));
				}
			}
			pStr += iTotalOffset;
			iTempWidth = 0;
			iTotalOffset = 0;
			iPreOffset = 0;
		}
		iPreOffset = iTotalOffset;
	}

	//add the last one
	strTemp.assign(pStr,iTotalOffset);
	CLabel::measureCharacter(strTemp.c_str(),strFont,iSize,&iTempWidth,NULL);
	vcCharacterInfo.push_back(std::make_pair<std::string,int>(strTemp,iTempWidth));
}

void CRichTxtLayOut::addNewLine(std::vector<std::pair<std::string,int>>& vcCurrentLine,int& iCurrentWidth,
								std::string& strFont,int iColor,int iFontSize,bool bNewLine,int iStrType)
{
	//add a new line
	std::vector<std::pair<std::string,int>>::iterator iterCurrentLine = vcCurrentLine.begin();
	std::string strCurrentLine = "";
	int iCurrentLineWidth = 0;
	while(iterCurrentLine != vcCurrentLine.end())
	{
		strCurrentLine += iterCurrentLine->first;
		iCurrentLineWidth += iterCurrentLine->second;
		iterCurrentLine++;
	}
	CLabel* pLabel = NULL;
	pLabel = new CLabel(iFontSize,iColor,strFont,iStrType);
	pLabel->setString(strCurrentLine);
	pLabel->setPos(m_iCurrentXPos,m_iCurrentYPos);
	m_currentTxtInfo.addCLabel(pLabel);
	m_iCurrentXPos += iCurrentLineWidth;
	vcCurrentLine.clear();
	if(bNewLine)
	{
		this->addCurrentLineInfo();
		//update x ,y position
		m_iCurrentYPos += m_currentTxtInfo.getLineHeight();
		m_iCurrentXPos = 0;
		m_currentTxtInfo.reset();
		iCurrentWidth = 0;
	}
	
}

void CRichTxtLayOut::caculateTxt(std::string str,int iFontSize,int iColor,std::string strFont,bool bNewLine,int iStrType)
{
	ENTERFUNC();
	std::list<std::pair<std::string,int>>  vcCharacterInfo;
	std::string strTemp = "";
	int iTempWidth = 0;
	int iTotalOffset = 0;
	//get width of "-"
	int iWidthHyphen = 0;
	int iHeightHyphen = 0;
	CLabel::measureCharacter("-",strFont,iFontSize,&iWidthHyphen,&iHeightHyphen);
	//split the txt first
	this->splitTxt(vcCharacterInfo,str,strFont,iFontSize);
	//////////////////////////////////////////////////////////////////////////
	//do layout here
	int iCurrentWidth = 0;
	std::vector<std::pair<std::string,int>> vcCurrentLine;
	std::list<std::pair<std::string,int>>::iterator iter = vcCharacterInfo.begin();
	while(iter != vcCharacterInfo.end())
	{
		iCurrentWidth += m_iCurrentXPos;
		std::pair<std::string,int>&  info = *iter;
		if (info.first == "\n")
		{
			//force add a new line
			//TODO:this code is so ugly modify it later!!!
			std::string strCurrentLine = "";
			int iCurrentLineWidth = 0;
			std::vector<std::pair<std::string,int>>::iterator iterCurrentLine = vcCurrentLine.begin();
			while(iterCurrentLine != vcCurrentLine.end())
			{
				strCurrentLine += iterCurrentLine->first;
				iCurrentLineWidth += iterCurrentLine->second;
				iterCurrentLine++;
			}

			if (0 < strCurrentLine.length())
			{
				CLabel* pLabel = NULL;
				pLabel = new CLabel(iFontSize,iColor,strFont,iStrType);
				pLabel->setString(strCurrentLine);
				pLabel->setPos(m_iCurrentXPos,m_iCurrentYPos);
				m_currentTxtInfo.addCLabel(pLabel);
				m_iCurrentXPos += iCurrentLineWidth;
			}
			else
			{
				LOG("only a '\n' just move to next line");
				//todo check me:this line's height may be silly
				int iTempHeight = 0;
				if (iter != vcCharacterInfo.begin())
				{
					std::pair<std::string,int>&  info = *(--iter);
					CLabel::measureCharacter((char*)info.first.c_str(),strFont,iFontSize,NULL,&iTempHeight);
					++iter;
				}
				else
				{
					LOG("the '\n' is the first character using height of hyphen");
					iTempHeight = iHeightHyphen;
				}
				m_currentTxtInfo.setLineHeight(iTempHeight);
			}
			vcCurrentLine.clear();
			this->addCurrentLineInfo();
			//update x ,y position
			m_iCurrentYPos += m_currentTxtInfo.getLineHeight();
			m_iCurrentXPos = 0;
			m_currentTxtInfo.reset();
			iCurrentWidth = 0;
			iter++;
		}
		else
		{
			bool bGoNext = true;
			iCurrentWidth += info.second;
			if (iCurrentWidth  > m_iMaxWidth)
			{
				iCurrentWidth -= info.second;
				//a new line here if current is a english word
				if (this->isEnglishCharacter((char*)info.first.c_str()))
				{
					strTemp = "";
					char* pStrTemp = (char*)info.first.c_str();
					//try to find a substr which can add to this line
					int iExtraChar = 0;
					iTotalOffset = 0;
					iTempWidth = 0;
					iCurrentWidth += iWidthHyphen;
					while(true)
					{
						u8_inc(pStrTemp,&iTotalOffset);
						strTemp.assign(pStrTemp,iTotalOffset);
						pStrTemp += iTotalOffset;
						iTotalOffset = 0;
						CLabel::measureCharacter(strTemp.c_str(),strFont,iFontSize,&iTempWidth,NULL);
						if (iTempWidth + iCurrentWidth <= m_iMaxWidth)
						{
							iCurrentWidth += iTempWidth;
							++iExtraChar;
						}
						else
						{

							break;
						}
					}

					if (0 >= iExtraChar)
					{
						iExtraChar = 0;
						if (iter != vcCharacterInfo.begin())
						{
							iter--;//minus one
						}
						else
						{
							bGoNext = false;
						}
						
					}
					else
					{//split string to two parts one will be add to this line 
						//other will insert to list
						strTemp = info.first;
						iTotalOffset = u8_offset((char*)strTemp.c_str(),iExtraChar);
						
						std::string subString0 = strTemp.substr(0,iTotalOffset);
						std::string subString1 = strTemp.substr(iTotalOffset,strTemp.length());
						//////////////////////////////////////////////////////////////////////////
						subString0 += "-";
						vcCurrentLine.push_back(std::make_pair<std::string,int>(subString0,iCurrentWidth));
						//////////////////////////////////////////////////////////////////////////
						CLabel::measureCharacter(subString1.c_str(),strFont,iFontSize,&iTempWidth,NULL);
						iter = vcCharacterInfo.erase(iter);
						vcCharacterInfo.insert(iter,std::make_pair<std::string,int>(subString1,iTempWidth));
						iter--;
						bGoNext = false;
						//////////////////////////////////////////////////////////////////////////
						
					}
					
				}
				else 
				{
					iter--;//minus one
				}

				//add a new line
				this->addNewLine(vcCurrentLine,iCurrentWidth,strFont,iColor,iFontSize,true,iStrType);
				if (bGoNext)
				{
					iter++;
				}
			}
			else
			{
				vcCurrentLine.push_back(*iter);
				iter++;
			}
		}
		
	}
	//////////////////////////////////////////////////////////////////////////
	if (!vcCurrentLine.empty())
	{
		this->addNewLine(vcCurrentLine,iCurrentWidth,strFont,iColor,iFontSize,bNewLine,iStrType);
	}
	//////////////////////////////////////////////////////////////////////////
	LVFUNC();
}
//////////////////////////////////////////////////////////////////////////
const std::string CRichText::RICH_TXT_TYPE = "CRichText";
//////////////////////////////////////////////////////////////////////////
CRichText::CRichText(void)
{

}


CRichText::~CRichText(void)
{
}
//////////////////////////////////////////////////////////////////////////