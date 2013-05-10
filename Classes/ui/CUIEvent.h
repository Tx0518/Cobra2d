#ifndef _CUIEVENT_H_
#define _CUIEVENT_H_

#include "CPlatFormDefine.h"
#include "CGeometry.h"
/************************************************************************/
/*
	CMouseClickEvent
*/
#if(COBRA_TARGET_RENDEENQINE == COBRA_RENDEENQINE_COCOS2DX)
class CMouseClickEvent : public CCTouchDelegate
{
public:
	CMouseClickEvent(void){}
	virtual ~CMouseClickEvent(void){}
	//override
	virtual bool isInRegion(const CPoint& point) { return false;}
};
#endif
/************************************************************************/

#endif	//_CUIEVENT_H_