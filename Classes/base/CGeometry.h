#ifndef _CGEOMETRY_H_
#define _CGEOMETRY_H_

/*
	CPoint
*/
class CPoint
{
public:
	CPoint(void);
	CPoint(float x, float y);
	CPoint(const CPoint& other);
	~CPoint(void);
	CPoint& operator= (const CPoint& other);
	void setPoint(float x, float y);
	bool equals(const CPoint& target) const;
public:
	float x;
	float y;
};

/*
	CSize
*/
class CSize
{
public:
	CSize(void);
	~CSize(void);
	CSize(float width,float height);
	CSize(const CSize& other);
	CSize& operator=(const CSize& other);
	void setSize(float width,float heigth);
	bool equals(const CSize& size) const;
public:
	float width;
	float height;
};


/*
	CRectange
*/
class CRectange
{
public:
	CRectange(void);  
	CRectange(float x, float y, float width, float height);
	CRectange(const CRectange& other);
	CRectange& operator= (const CRectange& other); 
	void setRect(float x, float y, float width, float height);
	float getMinX() const;
	float getMidX() const;
	float getMaxX() const; 
	float getMinY() const;
	float getMidY() const; 
	float getMaxY() const;
	bool equals(const CRectange& rect) const;   
	bool containsPoint(const CPoint& point) const;
	bool intersectsRect(const CRectange& rect) const;

	~CRectange(void);
public:
	CPoint origin;
	CSize  size;
};


#define CreateCPoint(x, y)							CPoint((float)(x), (float)(y))
#define CreateCSize(width, height)			CSize((float)(width), (float)(height))
#define CreateCRect(x, y, width, height)	CRectange((float)(x), (float)(y), (float)(width), (float)(height))

const CPoint PointZero = CreateCPoint(0,0);
const CSize SizeZero = CreateCSize(0,0);
const CRectange RectZero = CreateCRect(0,0,0,0);

#endif //_CGEOMETRY_H_