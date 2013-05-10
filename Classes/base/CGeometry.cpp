#include "CGeometry.h"

/************************************************************************/
//CPoint
CPoint::CPoint( void )
{
	setPoint(0.0f,0.0f);
}

CPoint::CPoint( float x, float y )
{
	setPoint(x,y);
}

CPoint::CPoint( const CPoint& other )
{
	setPoint(other.x,other.y);
}

CPoint& CPoint::operator=( const CPoint& other )
{
	setPoint(other.x, other.y);
	return *this;
}

void CPoint::setPoint( float x, float y )
{
	this->x = x;
	this->y = y;
}

bool CPoint::equals( const CPoint& target ) const
{
	return ((this->x == target.x) && (this->y == target.y));
}

CPoint::~CPoint( void )
{

}
/************************************************************************/
//CSize
CSize::CSize( void )
{
	setSize(0.0f,0.0f);
}

CSize::CSize( float width,float height )
{
	setSize(width,height);
}

CSize::CSize( const CSize& other )
{
	setSize(other.width,other.height);
}

CSize::~CSize( void )
{
	setSize(0.0f,0.0f);
}

CSize& CSize::operator=( const CSize& other )
{
	setSize(other.width,other.height);
	return *this;
}

void CSize::setSize( float width,float heigth )
{
	this->width = width;
	this->height = heigth;
}

bool CSize::equals( const CSize& size ) const
{
	return ((this->width == size.width) && (this->height == size.height));
}

/************************************************************************/
//CRectange

CRectange::CRectange( void )
{
	setRect(0.0f,0.0f,0.0f,0.0f);
}

CRectange::CRectange( float x, float y, float width, float height )
{
	setRect(x,y,width,height);
}

CRectange::CRectange( const CRectange& other )
{
	setRect(other.origin.x,other.origin.y,other.size.width,other.size.height);
}

CRectange::~CRectange(void)
{
	setRect(0.0f,0.0f,0.0f,0.0f);
}

CRectange& CRectange::operator=( const CRectange& other )
{
	setRect(other.origin.x,other.origin.y,other.size.width,other.size.height);
	return *this;
}

void CRectange::setRect( float x, float y, float width, float height )
{
	this->origin.setPoint(x,y);
	this->size.setSize(width,height);
}

float CRectange::getMinX() const
{
	return origin.x;
}

float CRectange::getMidX() const
{
	return (origin.x + size.width *.5);
}

float CRectange::getMaxX() const
{
	return origin.x + size.width;
}

float CRectange::getMinY() const
{
	return origin.y;
}

float CRectange::getMidY() const
{
	return origin.y + size.height * 0.5;
}

float CRectange::getMaxY() const
{
	return origin.y + size.height;
}

bool CRectange::equals( const CRectange& rect ) const
{
	return (origin.equals(rect.origin) && size.equals(rect.size));
}

bool CRectange::containsPoint( const CPoint& point ) const
{
	return (point.x >=getMinX() && point.x <=getMaxX() && point.y >=getMinX() && point.y <=getMaxY());
}

bool CRectange::intersectsRect( const CRectange& rect ) const
{
	return !(getMaxX() < rect.getMinX() || 
		rect.getMaxX() < getMinX() ||
		getMaxY() < rect.getMinY() ||
		rect.getMaxY() < getMinY());
}
