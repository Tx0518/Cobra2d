#ifndef __C_ACTION_FADE_IN_H__
#define __C_ACTION_FADE_IN_H__
#include "CGeometry.h"
#include "CActionInterval.h"
class CActionFadeTo:public CActionInterval
{
public:
	static const int CMD_ID_ACTION_FADE_TO = 0x2011;
	CActionFadeTo(void);
	~CActionFadeTo(void);
	void init(float dt,unsigned char opacity);
	void update(float time);
	void startWidthTarget(CBaseWidget* pTarget);
protected:
	unsigned char m_fromOpacity;
	unsigned char m_toOpacity;
};

#endif//__C_ACTION_FADE_IN_H__