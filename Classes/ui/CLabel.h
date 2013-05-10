#ifndef _CLABEL_H_
#define _CLABEL_H_

#include "CComponent.h"
#include <string>

class CSprite;

class GLabel : public CComponent
{
public:
	GLabel(std::string label);
	GLabel(std::string label,std::string fontName,float fontSize);
	~GLabel(void);

	virtual void setString(const std::string& label);
	virtual const std::string& getString();

	CCTextAlignment getHorizontalAlignment();
	void setHorizontalAlignment(CCTextAlignment alignment);

	CCVerticalTextAlignment getVerticalAlignment();
	void setVerticalAlignment(CCVerticalTextAlignment verticalAlignment);

	const CCSize& getDimensions();
	void setDimensions(const CSize &dim);

	float getFontSize();
	void setFontSize(float fontSize);

	const std::string& getFontName();
	void setFontName(const std::string& fontName);

	void invalidate();
	const CRectange& getTextureRect();

	void updateColor(const ccColor3B& color);

	void setBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void setBorder(bool var);
	bool isBorder();

	void setSize(float width,float height);
protected:
	void renderBorder();
protected:
	CSize m_tDimensions;
	CCTextAlignment         m_hAlignment;
	CCVerticalTextAlignment m_vAlignment;
	std::string  m_strFontName;
	float m_fFontSize;
	std::string m_strLabel;
	CSprite* m_pLabel;
	CCRect m_textureRect;	
	bool m_fIsBorder;
	CComponent* m_pBackground;
};
#endif	//_CLABEL_H_